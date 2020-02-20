#include <string>
#include <vector>
#include <fstream>
#include "struct.hh"

void output(const std::string &path, const std::vector<Cache> &caches) {
  std::ofstream file;
  file.open(path);

  file << caches.size() << "\n";
  for (int i = 0; i < caches.size(); i++) {
    file << i;
    for (const auto v : caches[i].videos_idx) {
      file << " " << v;
    }
    file << "\n";
  }

  file.close();
}