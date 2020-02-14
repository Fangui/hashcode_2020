#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "dump.hh"
#include "parse.hh"
#include "score.hh"

entity create_child(const entity& e1, const entity& e2, size_t start, size_t end) {
    entity child = entity(e1);
    auto segment_start = e2.begin() + start;
    auto segment_end = e2.begin() + end;
    for (auto& it = segment_start; it != segment_end; it++) {
        child.erase(std::find(child.begin(), child.end(), *it));
    }
    child.insert(child.end(), segment_start, segment_end);
    return child;
}


std::vector<entity> cross_over(const entity& e1, const entity& e2) {
    unsigned int nb_segment = 2;
    size_t segment_size = e1.size() / nb_segment;
    std::vector<entity> result;
    for (auto i = 0u; i < nb_segment; i++) {
        result.push_back(create_child(e1, e2, i * segment_size, (i + 1) * segment_size));
        result.push_back(create_child(e2, e1, i * segment_size, (i + 1) * segment_size));
    }
    return result;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " SAVE_FILE" << std::endl;
        return 1;
    }

    parse();

    AlgoGen<entity>::dump_f dump = [argv](const entity& entity) {
        auto file = std::ofstream(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "Couldn't open " << argv[1] << std::endl;
            exit(2);
        }
        file << entity;
    };

    AlgoGen<entity>::generation_f generation = []() {
        auto res = std::vector<std::shared_ptr<Photo>>{};
        for (const auto& p : photos_h)
            res.push_back(Photo::get(p.first));

        auto verts = std::vector<size_t>{};
        for (const auto& p : photos_v)
            verts.push_back(p.first);
        std::random_shuffle(verts.begin(), verts.end());

        for (auto i = 0u; i < verts.size(); i += 2)
            res.push_back(Photo::get(verts[i], verts[i + 1]));

        std::random_shuffle(res.begin(), res.end());

        return res;
    };

    AlgoGen<entity>::mutation_f mutation =
        [](const std::map<double, entity>& best) {
            std::vector<entity> new_gen;
            for (const auto& gen : best)
            {
                auto new_entity = entity(gen.second);
                
                // mutation
                for (auto i = 0u; i < 400; i++)
                {
                    size_t i_1 = std::rand() % new_entity.size();
                    size_t i_2 = std::rand() % new_entity.size();
                    std::swap(new_entity[i_1], new_entity[i_2]);
                }

                new_gen.push_back(new_entity);
            }
            auto cross = cross_over(best.rbegin()->second, (++best.rbegin())->second);
            new_gen.insert(new_gen.end(), cross.begin(), cross.end());
            return new_gen;
        };

    auto gen = AlgoGen<entity>(score, generation, mutation, dump);

    std::cout << gen(10);

    return 0;
}
