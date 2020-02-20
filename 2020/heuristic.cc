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

    int max_score = 0;
    for (auto it = available_library.cbegin(); it != available_library.cend(); it++) {
        int score = compute_intersection(libraries[*it].books, available_books);
        if (score > max_score) {
            max_score = score;
            result = *it;
        }
    }

    available_library.erase(result);
    for (unsigned int book : libraries[result].books) {
        available_books.erase(book);
    }
    return result;
}

std::vector<unsigned int> sort_libraries() {
    // initialize
    std::unordered_set<unsigned int> available_books;
    std::unordered_set<unsigned int> available_libraries;
    for (int i = 0; i < books.size(); i++) {
        available_books.insert(i);
    }
    for (int i = 0; i < libraries.size(); i++) {
        available_libraries.insert(i);
    }

    // Iterate
    std::vector<unsigned int> id_libraries{};
    for (int i = 0; i < libraries.size(); i++) {
        id_libraries.push_back(select_library(available_libraries, available_books));
        std::cerr << id_libraries[id_libraries.size() - 1] << "\n";
    }

    return id_libraries;
}