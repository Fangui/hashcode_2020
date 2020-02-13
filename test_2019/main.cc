#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "dump.hh"
#include "parse.hh"
#include "score.hh"

int main(void)
{
    parse();

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
