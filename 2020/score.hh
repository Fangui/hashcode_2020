#pragma once

#include <algorithm>

#include "parse.hh"

size_t score(const result& res)
{
    size_t result = 0;
    for (const auto& output : res)
        for (const auto& book : output.books)
            result += books[book];
    return result;
}
