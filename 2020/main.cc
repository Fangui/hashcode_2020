#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

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
        auto books_lib = std::vector<unsigned>(libraries[id_lib].books.begin(),
                                               libraries[id_lib].books.end());
        for (auto it = books_lib.begin(); it != books_lib.end(); it++)
            if (books_marks[*it])
                books_lib.erase(it);

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
            std::cerr << "Couldn't open " << argv[1] << std::endl;
            exit(2);
        }
        file << res;
    };

    auto id_libraries = sort_libraries();

    auto res = compute_result(id_libraries);

    dump(res);

    std::cout << "Score: " << score(res) << std::endl;

    return 0;
}
