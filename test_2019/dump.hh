#include <ofstream>

#include "parse.hh"

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
