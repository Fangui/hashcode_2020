#pragma once

#include <vector>
#include <unordered_map>

struct Video
{
    int video_size;
};

struct Cache
{
    int capacity;
};

struct Connection
{
    int id;
    int latency;
};

struct Endpoint
{
    std::vector<Endpoint> connections;
    int latency_dc;
    std::unordered_map<int, int> videos_watch;
};
