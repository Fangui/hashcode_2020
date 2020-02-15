#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "dump.hh"
#include "parse.hh"
#include "score.hh"

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
        auto res = std::vector<Photo>{};
        for (const auto& p : photos_h)
            res.emplace_back(p.first);

        auto verts = std::vector<size_t>{};
        for (const auto& p : photos_v)
            verts.emplace_back(p.first);
        std::random_shuffle(verts.begin(), verts.end());

        for (auto i = 0u; i < verts.size(); i += 2)
            res.emplace_back(verts[i], verts[i + 1]);

        std::random_shuffle(res.begin(), res.end());

        return res;
    };

    AlgoGen<entity>::mutation_f mutation =
        [](const std::map<double, entity>& best) {
            std::vector<entity> new_gen;
            for (const auto& gen : best)
            {
                auto new_entity = entity(gen.second);

                size_t nb_mut = 1;
                for (auto i = 0u; i < nb_mut; i++)
                {
                    size_t i_1 = std::rand() % new_entity.size();
                    size_t i_2 = std::rand() % new_entity.size();
                    std::swap(new_entity[i_1], new_entity[i_2]);
                    // if find 2 verticales
                    if (new_entity[i_1].ids_.second != -1 && new_entity[i_2].ids_.second != -1)
                    {
                        if (std::rand() % 2) // if random swap verticales
                        {
                            if (i_1 % 2)
                            {
                                if (i_2 % 2)
                                    std::swap(new_entity[i_1].ids_.second, new_entity[i_2].ids_.second);
                                else
                                    std::swap(new_entity[i_1].ids_.second, new_entity[i_2].ids_.first);
                            }
                            else
                            {
                                if (i_2 % 2)
                                    std::swap(new_entity[i_1].ids_.first, new_entity[i_2].ids_.second);
                                else
                                    std::swap(new_entity[i_1].ids_.first, new_entity[i_2].ids_.first);
                            }
                        }

                    }
                }

                new_gen.push_back(new_entity);
            }
            return new_gen;
        };

    auto gen = AlgoGen<entity>(score, generation, mutation, dump);

    std::cout << gen(10);

    return 0;
}
