#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "struct.hh"

void parse(const std::string &path, std::vector<Video> &videos, std::vector<Cache> &caches,
           std::vector<Endpoint> &endpoints) {
  std::ifstream file;
  file.open(path);

  int nb_videos, nb_endpoints, nb_requests, nb_caches, cache_size;
  file >> nb_videos;
  file >> nb_endpoints;
  file >> nb_requests;
  file >> nb_caches;
  file >> cache_size;

  std::cerr << "nb_videos: " << nb_videos << "\n";
  std::cerr << "nb_endpoints: " << nb_endpoints << "\n";
  std::cerr << "nb_requests: " << nb_requests << "\n";
  std::cerr << "nb_caches: " << nb_caches << "\n";
  std::cerr << "caches_size: " << cache_size << "\n";

  videos.reserve(nb_videos);
  caches.reserve(nb_caches);
  endpoints.reserve(nb_endpoints);

  for (int i = 0; i < nb_caches; i++) {
    Cache c{};
    c.capacity = cache_size;
    caches.push_back(c);
  }

  for (int i = 0; i < nb_videos; i++) {
    Video v{};
    videos.push_back(v);
    file >> v.video_size;
  }

  for (int i = 0; i < nb_endpoints; i++) {
    Endpoint e{};
    file >> e.latency_dc;
    int connected_caches;
    file >> connected_caches;
    for (int j = 0; j < connected_caches; j++) {
      Connection c{};
      file >> c.idx;
      file >> c.latency;
      e.connections.push_back(c);
    }
    endpoints.push_back(e);
  }

  for (int i = 0; i < nb_requests; i++) {
    int video_id;
    int endpoint_id;
    int request;
    file >> video_id;
    file >> endpoint_id;
    file >> request;
    endpoints[endpoint_id].requests.insert({video_id, request});
  }

  file.close();
}