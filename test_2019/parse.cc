#include "parse.hh"

std::unordered_map<int, std::unordered_set<size_t>> photos_h;
std::unordered_map<int, std::unordered_set<size_t>> photos_v;

std::shared_ptr<Photo> Photo::get(int id) 
{
    return Photo::get(id, -1);
}


std::shared_ptr<Photo> Photo::get(int id1, int id2) {
    size_t key = id1 * 1000000 + id2 + 1;
    auto index = Photo::cache.find(key);

    if (index == Photo::cache.end()) {
        auto new_photo = std::shared_ptr<Photo>(new Photo(id1, id2));
        cache.emplace(key, new_photo);

        return new_photo;
    }

    return index->second;
}
