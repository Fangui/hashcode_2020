#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Photo;

using entity = std::vector<Photo>;

std::unordered_map<int, std::unordered_set<size_t>> photos_h;
std::unordered_map<int, std::unordered_set<size_t>> photos_v;

void parse()
{
    std::unordered_map<std::string, size_t> dict_labels;
    size_t n;
    std::cin >> n;
    std::cerr << "Number photo: " << n << std::endl;
    size_t nb_label = 0;
    for (auto i = 0u; i < n; i++)
    {
        char type;
        std::cin >> type;
        size_t m;
        std::cin >> m;
        std::unordered_set<size_t> labels;
        for (auto j = 0u; j < m; j++)
        {
            std::string label;
            std::cin >> label;
            auto found = dict_labels.find(label);
            if (found == dict_labels.end())
            {
                dict_labels.emplace(label, nb_label);
                labels.insert(nb_label);
                nb_label++;
            } else
            {
                labels.insert(found->second);
            }
        }

        if (type == 'V')
            photos_v.emplace(i, labels);
        else
            photos_h.emplace(i, labels);
    }
    std::cerr << "Number tags: " << nb_label << std::endl;
    std::cerr << "Number vertical photo: " << photos_v.size() << std::endl;
    std::cerr << "Number horizontal photo: " << photos_h.size() << std::endl;
}

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

    std::unordered_set<size_t> tags_;
    std::pair<int, int> ids_;
};
