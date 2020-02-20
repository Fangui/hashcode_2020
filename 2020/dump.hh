#pragma once

#include <ostream>

#include "parse.hh"

std::ostream& operator<<(std::ostream& o, const result& e)
{
    o << e.size() << std::endl;
    for (const auto& el : e)
    {
        o << el.id_library << " " << el.books.size() << std::endl;
        for (const auto& id : el.books)
            o << id << " ";
        o << std::endl;
    }

    return o;
}
