#include <iostream>
#include "parser.hh"

int main() {
  std::vector<Video> videos;
  std::vector<Cache> caches;
  std::vector<Endpoint> endpoints;
  parse("../input/kittens.in", videos, caches, endpoints);
  return 0;
}
