#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Photo;

using entity = std::vector<std::shared_ptr<Photo>>;


extern std::unordered_map<int, std::unordered_set<size_t>> photos_h;
extern std::unordered_map<int, std::unordered_set<size_t>> photos_v;

inline void parse()
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
    public:

        std::unordered_set<size_t> tags_;
        std::pair<int, int> ids_;

        static std::shared_ptr<Photo> get(int id);
        static std::shared_ptr<Photo> get(int id1, int id2);

    private:
        Photo() = default;

        Photo(const Photo&) = delete;
        Photo& operator=(const Photo&) = delete;

        Photo(int id1, int id2)
        {
            auto tags1 = photos_v.find(id1);
            auto tags2 = photos_v.find(id2);
            if (id2 == -1)
                tags1 = photos_h.find(id1);

            ids_ = std::make_pair(id1, id2);
            if (tags1 == photos_v.end() || (tags2 == photos_v.end() && id2 != -1))
            {
                std::cerr
                    << "Warning, strange behaviour ? tags1 or tags2 not found" << id1 << "  " << id2 << " \n";
                return;
            }


            tags_ = tags1->second;
            if (id2 != -1)
                tags_.insert(tags2->second.begin(), tags2->second.end());
        }

        static inline std::unordered_map<size_t, std::shared_ptr<Photo>> cache;
};
