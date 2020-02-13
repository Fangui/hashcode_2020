#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "dump.hh"
#include "parse.hh"
#include "score.hh"

int main(void)
{
    parse();

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

    AlgoGen<entity>::mutation_f mutation = [](const std::map<double, entity>& best) {
        std::vector<entity> new_gen;
        for (const auto& gen : best) {
            auto new_entity = entity(gen.second);

            for (auto i = 0u; i < 4; i++) {
                size_t i_1 = std::rand() % new_entity.size();
                size_t i_2 = std::rand() % new_entity.size();
                std::swap(new_entity[i_1], new_entity[i_2]);
            }

            new_gen.push_back(new_entity);
        }
        return new_gen;
    };

    auto gen = AlgoGen<entity>(score, generation, mutation);

    std::cout << gen(50);

    return 0;
}
