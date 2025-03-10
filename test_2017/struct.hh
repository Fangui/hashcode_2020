#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

struct Video
{
    int video_size;
    std::unordered_set<int> caches_id;
};

struct Cache
{
    int capacity;

    std::vector<int> videos_idx;
};

struct Connection
{
    int idx;
    int latency;
};

struct Endpoint
{
    std::vector<Connection> connections;
    int latency_dc;
    std::unordered_map<int, int> requests; // first ->idx videos, second -> nb view
};
