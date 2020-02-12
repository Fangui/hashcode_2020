#include <fstream>
#include <iostream>
#include <vector>

#include "algo-gen.hh"
#include "parse.hh"

std::unordered_map<int, std::unordered_set<unsigned char>> Photo::photos_h;
std::unordered_map<int, std::unordered_set<unsigned char>> Photo::photos_v;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] <<  " fic.txt \n";
        return 1;
    }


    using entity = std::vector<Photo>;



    parse_input(argv[1], 'H');
    parse_input(argv[1], 'V');

    AlgoGen<entity>::score_f score = [](const entity&) { return 0.; };

    AlgoGen<entity>::generation_f generation = []() { return std::vector<Photo>(); };

    AlgoGen<entity>::mutation_f mutation = [](const std::map<double, entity>&) {
        return std::vector<entity>{};
    };

    auto dump = [](const entity& e) {
        std::ofstream file("res");
        if (!file.is_open())
            std::cerr << "Failed open res file" << std::endl;
        file << e.size() << std::endl;
        for (const auto& i : e)
        {
            if (i.ids_.second >= 0)
                file << i.ids_.first << " " << i.ids_.second << '\n';
            file << i.ids_.first << '\n';
        }
        file.close();
    };

    auto gen = AlgoGen<entity>(score, generation, mutation, dump);
    std::cout << score(gen(50)) << std::endl;
    return 0;
}
