#pragma once

#include <functional>
#include <map>
#include <vector>

template <typename T>
class AlgoGen
{
public:
    using score_f = std::function<double(const T&)>;
    using generation_f = std::function<T()>;
    using mutation_f =
        std::function<std::vector<T>(const std::map<double, T>&)>;
    using dump_f = std::function<void(const T&)>;

    AlgoGen(score_f score, generation_f generation, mutation_f mutation,
            dump_f dump);

    T apply(const unsigned size, const unsigned max_iterations = 10000);
    T operator()(const unsigned size, const unsigned max_iterations = 10000)
    {
        return apply(size, max_iterations);
    }

private:
    score_f score_;
    generation_f generation_;
    mutation_f mutation_;
    dump_f dump_;

    void update_bests(std::map<double, T>& bests, const std::vector<T>& pop);
};

#include "algo-gen.hxx"
