#include <ostream>

#include "algo-gen.hh"
#include "parse.hh"

std::ostream& operator<<(std::ostream& o, const entity& e)
{
    o << e.size() << std::endl;
    for (const auto& i : e)
    {
        if (i.ids_.second >= 0)
            o << i.ids_.first << " " << i.ids_.second << '\n';
        else
            o << i.ids_.first << '\n';
    }
    return o;
}
