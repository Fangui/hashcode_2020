#include <vector>
#include "struct.hh"
#include "parse.hh"

int compute_intersection(const std::unordered_set<unsigned int>& books_library, const std::unordered_set<unsigned int>& available) {
    int score = 0;

    for (auto b: books_library) {
        if (available.find(b) != available.end())
            score += books[b];
    }

    return score;
}

unsigned int select_library(std::unordered_set<unsigned int> &available_library,
                            std::unordered_set<unsigned int> &available_books) {
    int result = 0;

    float max_score = 0;
    for (auto it = available_library.cbegin(); it != available_library.cend(); it++) {
        
        auto &li = libraries[*it];

        if (days < li.signup)
            continue;

        float score = compute_intersection(li.books, available_books) / li.signup;
        if (score > max_score) {
            max_score = score ;
            result = *it;
        }
    }

    available_library.erase(result);
    for (unsigned int book : libraries[result].books) {
        available_books.erase(book);
    }

    if (days > libraries[result].signup)
        days -= libraries[result].signup;
    else
    {
        std::cerr << "warning bad behaviour \n";
        return -1;
    }

    return result;
}

std::vector<unsigned int> sort_libraries() {
    // initialize
    std::unordered_set<unsigned int> available_books;
    std::unordered_set<unsigned int> available_libraries;
    for (auto i = 0u; i < books.size(); i++) {
        available_books.insert(i);
    }
    for (auto i = 0u; i < libraries.size(); i++) {
        available_libraries.insert(i);
    }

    // Iterate
    std::vector<unsigned int> id_libraries{};
    for (auto i = 0u; i < libraries.size(); i++) {
        auto res = select_library(available_libraries, available_books);
        id_libraries.push_back(res);
    }

    return id_libraries;
}
