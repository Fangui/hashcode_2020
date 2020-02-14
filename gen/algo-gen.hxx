#include <limits>
#include <omp.h>

#include "parse.hh"

template <typename T>
AlgoGen<T>::AlgoGen(score_f score, generation_f generation, mutation_f mutation,
                    dump_f dump)
    : score_(score)
    , generation_(generation)
    , mutation_(mutation)
    , dump_(dump)
{}

template <typename T>
T AlgoGen<T>::apply(const unsigned size, const unsigned max_iterations)
{
    auto bests = std::map<double, T>{};
    for (auto i = 0u; i < size; ++i)
    {
        auto entity = generation_();
        bests.emplace(score_(entity), entity);
    }

    double best_score = -std::numeric_limits<double>::infinity();

    //int max_thread = omp_get_max_threads();

    std::vector<entity> new_gens[4];
    for (auto i = 0u; i < max_iterations; ++i)
    {
#pragma omp parallel for
        for (int i = 0; i < 4; ++i) // FIXME nb thread
            new_gens[i] = mutation_(bests);

        for (int i = 0; i < 4; ++i)
        {
            update_bests(bests, new_gens[i]);
            if (bests.rbegin()->first > best_score)
            {
                best_score = bests.rbegin()->first;
                dump_(bests.rbegin()->second);
            }
        }
        std::cerr << "Best Score: " << best_score << std::endl;
    }
    return bests.rbegin()->second;
}

template <typename T>
void AlgoGen<T>::update_bests(std::map<double, T>& bests,
                              const std::vector<T>& pop)
{
    auto entity = pop.begin();
    auto worst_score = bests.begin()->first;

    std::vector<double> score;
    std::transform(pop.begin(), pop.end(), std::back_inserter(score), score_);

    for (const auto& s : score)
    {
        if (s > worst_score)
        {
            bests.emplace(s, *entity);
            bests.erase(bests.begin());
            worst_score = bests.begin()->first;
        }
        entity++;
    }
}
