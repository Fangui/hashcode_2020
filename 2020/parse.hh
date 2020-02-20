#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "struct.hh"

struct Output
{
    Output(unsigned id_library, std::vector<unsigned> books)
        : id_library(id_library)
        , books(books)
    {}

    unsigned int id_library;
    std::vector<unsigned int> books;
};

using result = std::vector<Output>;

// Declare global variables used to store parsed data.
// You might want to pre-process the data
unsigned int days;
std::vector<unsigned int> books;
std::vector<Library> libraries;

inline void parse()
{
    // Parse STDIN and fill above global variables.
    // Display on STDERR stats about the data (size, proportion...)
    unsigned int nb_books;
    unsigned int nb_libs;
    std::cin >> nb_books >> nb_libs >> days;
    for (auto i = 0u; i < nb_books; ++i)
    {
        unsigned int score;
        std::cin >> score;
        books.push_back(score);
    }

    for (auto i = 0u; i < nb_libs; ++i)
    {
        unsigned int nb_books_lib;
        unsigned int signup;
        unsigned int efficiency;
        std::unordered_set<unsigned int> books;
        std::cin >> nb_books_lib >> signup >> efficiency;
        for (auto j = 0u; j < nb_books_lib; j++)
        {
            unsigned int id_book;
            std::cin >> id_book;
            books.insert(id_book);
        }
        libraries.emplace_back(signup, efficiency, books);
    }

    std::cerr << "DAYS: " << days << std::endl;
    std::cerr << "NB LIBS: " << nb_libs << std::endl;
}
