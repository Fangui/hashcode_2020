#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "dump.hh"
#include "heuristic.hh"
#include "parse.hh"
#include "score.hh"
#include "struct.hh"

unsigned int days;
std::vector<unsigned int> books;
std::vector<Library> libraries;

result compute_result(std::vector<unsigned> id_libs)
{
    result res;

    auto time = 0u;

    auto books_marks = std::vector<bool>(books.size(), false);
    for (auto id_lib : id_libs)
    {
        time += libraries[id_lib].signup;
        if (time > days)
            break;

        auto books_lib = std::vector<unsigned>(libraries[id_lib].books.begin(),
                                               libraries[id_lib].books.end());
        auto it = books_lib.begin();
        while (it != books_lib.end())
        {
            if (books_marks[*it])
                it = books_lib.erase(it);
            else
                it++;
        }

        std::sort(books_lib.begin(), books_lib.end(),
                  [](unsigned a, unsigned b) { return books[a] > books[b]; });

        // Remove impossible shipping
        auto possible = (days - time) * libraries[id_lib].efficiency;
        if (possible < books_lib.size())
            books_lib.erase(books_lib.begin() + possible, books_lib.end());

        // Marks shipped books
        for (const auto id_book : books_lib)
            books_marks[id_book] = true;

        res.emplace_back(id_lib, books_lib);
    }
    return res;
}

int main(int argc, char* argv[])
{
    // Check how the program is called
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " SAVE_FILE" << std::endl;
        return 1;
    }

    // Parse the input
    parse();

    // Wrapper around the dump function
    auto dump = [argv](const result& res) {
        auto file = std::ofstream(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "couldn't open " << argv[1] << std::endl;
            exit(2);
        }
        file << res;
    };

    auto id_libraries = sort_libraries();

    // ALGO GEN

    // Dump
    AlgoGen<std::vector<unsigned>>::dump_f dump_bis =
        [argv](const std::vector<unsigned>& res) {
            auto file = std::ofstream(argv[1]);
            if (!file.is_open())
            {
                std::cerr << "couldn't open " << argv[1] << std::endl;
                exit(2);
            }
            file << compute_result(res);
        };

    // Generation
    AlgoGen<std::vector<unsigned>>::generation_f generation =
        [&id_libraries]() { return id_libraries; };

    // Mutation
    AlgoGen<std::vector<unsigned>>::mutation_f mutation =
        [](const std::map<double, std::vector<unsigned>>& best) {
            std::vector<std::vector<unsigned>> new_gen;
            for (auto entity : best)
            {
                auto& new_entity = entity.second;
                for (auto i = 0u; i < 1; i++)
                {
                    size_t i_1 = std::rand() % new_entity.size();
                    size_t i_2 = std::rand() % new_entity.size();
                    std::swap(new_entity[i_1], new_entity[i_2]);
                }
                new_gen.push_back(new_entity);
            }
            return new_gen;
        };

    // Score
    AlgoGen<std::vector<unsigned>>::score_f score_bis =
        [](const std::vector<unsigned>& entity) {
            auto res = compute_result(entity);
            return (double)score(res);
        };

    // Reste
    auto gen = AlgoGen<std::vector<unsigned>>(score_bis, generation, mutation,
                                              dump_bis);
    std::cout << "Start Gen" << std::endl;
    id_libraries = gen(10000);

    // auto best = 0u;
    // for (auto i = 0u; i < id_libraries.size(); ++i)
    // {
    //     for (auto j = i; j < id_libraries.size(); ++j)
    //     {
    //         if (i == j)
    //             continue;
    //         std::swap(id_libraries[i], id_libraries[j]);
    //         auto res = compute_result(id_libraries);
    //         if (score(res) > best)
    //         {
    //             std::cout << score(res) << std::endl;
    //             best = score(res);
    //             dump(res);
    //         } else
    //             std::swap(id_libraries[i], id_libraries[j]);
    //     }
    //     std::cout << i << "/" << id_libraries.size() << std::endl;
    // }

    auto res = compute_result(id_libraries);
    dump(res);
    std::cout << "SCORE FINALE: " << score(res) << std::endl;

    return 0;
}
