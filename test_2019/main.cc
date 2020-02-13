#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "parse.hh"
#include "photo.hh"

std::unordered_map<int, std::unordered_set<unsigned char>> Photo::photos_h;
std::unordered_map<int, std::unordered_set<unsigned char>> Photo::photos_v;

int main(int argc, char* argv[])
{
    using entity = std::vector<Photo>;

    parse();

    AlgoGen<entity>::score_f score = [](const entity&) { return 0.; };

    AlgoGen<entity>::generation_f generation = []() {
        return std::vector<Photo>();
    };

    AlgoGen<entity>::mutation_f mutation = [](const std::map<double, entity>&) {
        return std::vector<entity>{};
    };

    auto gen = AlgoGen<entity>(score, generation, mutation, dump);
    std::cout << score(gen(50)) << std::endl;
    return 0;
}
