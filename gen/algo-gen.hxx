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

    for (auto i = 0u; i < max_iterations; ++i)
    {
        auto new_gen = mutation_(bests);
        update_bests(bests, new_gen);
        dump_(bests.end()->second);
    }
    return bests.end()->second;
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
