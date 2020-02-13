#pragma once

#include <algorithm>
#include <unordered_set>

#include "algo-gen.hh"

AlgoGen<entity>::score_f score = [](const entity& entity) { 
    float result = 0.;
    for (auto i = 0u; i < entity.size() - 1; i++) {
        const auto& tags_1 = entity[i].tags_;
        const auto& tags_2 = entity[i + 1].tags_;
        std::unordered_set<unsigned char> u;
        u.insert(tags_1.begin(), tags_1.end());
        u.insert(tags_2.begin(), tags_2.end());
        auto inter_size = tags_1.size() + tags_2.size() - u.size();
        result += std::min(inter_size,
                std::min(tags_1.size() - inter_size, tags_2.size() - inter_size));
    }
    return result;
};
