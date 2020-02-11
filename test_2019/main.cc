#include "algo-gen.hh"

int main(void)
{
    auto score = [](const int& a) { return (double)a; };

    auto generation = []() { return 42; };

    auto mutation = [](const std::map<double, int>&) {
        return std::vector<int>{};
    };

    auto dump = [](const int&) {};

    auto gen = AlgoGen<int>(score, generation, mutation, dump);
    gen(50);
    return 0;
}
