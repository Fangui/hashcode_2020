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
        return std::vector<Photo>();
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

    auto gen = AlgoGen<entity>(score, generation, mutation, dump);

    std::cout << score(gen(50)) << std::endl;

    return 0;
}
