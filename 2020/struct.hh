#pragma once

#include <unordered_set>

struct Library
{
    unsigned signup;
    unsigned efficiency;

    std::unordered_set<int> books;
};
