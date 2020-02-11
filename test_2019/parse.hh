#pragma once

#include <vector>
#include <unordered_set>

#include <iostream>

using pair_v = std::pair<unsigned, unsigned>;

struct Photo
{
    std::unordered_set<size_t> tags;
    std::pair<int, int> ids;
};

std::vector<Photo> parse_input(const std::string &inp, char c);
