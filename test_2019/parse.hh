#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

struct Photo;

using entity = std::vector<Photo>;

std::unordered_map<int, std::unordered_set<unsigned char>> photos_h;
std::unordered_map<int, std::unordered_set<unsigned char>> photos_v;

void parse();

struct Photo
{
    Photo() = default;

    Photo(int id)
    {
        ids_ = std::make_pair(id, -1);
        auto tags = photos_h.find(id);

        if (tags == photos_h.end())
            tags = photos_v.find(id);

        if (tags == photos_v.end())
        {
            std::cerr << "Warning, strange behaviour ? tags not found \n";
            return;
        }

        tags_ = tags->second;
    }

    Photo(int id1, int id2)
    {
        auto tags1 = photos_v.find(id1);
        auto tags2 = photos_v.find(id2);

        ids_ = std::make_pair(id1, id2);
        if (tags1 == photos_v.end() || tags2 == photos_v.end())
        {
            std::cerr
                << "Warning, strange behaviour ? tags1 or tags2 not found \n";
            return;
        }

        tags_ = tags1->second;
        tags_.insert(tags2->second.begin(), tags2->second.end());
    }

    std::unordered_set<unsigned char> tags_;
    std::pair<int, int> ids_;
};
