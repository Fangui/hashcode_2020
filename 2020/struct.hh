#pragma once

#include <unordered_set>

struct Library
{
    Library(unsigned signup, unsigned efficiency,
            std::unordered_set<unsigned> books)
        : signup(signup)
        , efficiency(efficiency)
        , books(books)
    {}

    unsigned signup;
    unsigned efficiency;

    std::unordered_set<unsigned int> books;
    std::vector<unsigned int> book_scores;
};
