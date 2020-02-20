#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "dump.hh"
#include "parse.hh"
#include "score.hh"
#include "struct.hh"

int main(int argc, char* argv[])
{
    // Check how the program is called
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " SAVE_FILE" << std::endl;
        return 1;
    }

    // Parse the input
    parse();

    // Wrapper around the dump function
    auto dump = [argv](const result& res) {
        auto file = std::ofstream(argv[1]);
        if (!file.is_open())
        {
            std::cerr << "Couldn't open " << argv[1] << std::endl;
            exit(2);
        }
        file << res;
    };

    result res;
    std::vector<unsigned> books;
    for (const auto& e : libraries[0].books)
        books.push_back(e);
    res.emplace_back(0, books);

    dump(res);

    std::cout << "Score: " << score(res) << std::endl;

    return 0;
}
