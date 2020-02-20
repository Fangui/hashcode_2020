#include <iostream>

#include "parser.hh"
#include "utils.hh"
#include "ouput.hh"

int main() {
  std::vector<Video> videos;
  std::vector<Cache> caches;
  std::vector<Endpoint> endpoints;
  parse("../input/kittens.in", videos, caches, endpoints);
  output("out.txt", caches);
  return 0;
}
