#include <algorithm>
#include <vector>
#include "struct.hh"
#include "parse.hh"

int compute_intersection(const Library &library,
                         const std::unordered_set<unsigned int> &available, const unsigned cur_day) {
    int score = 0;

    unsigned possible = (days - cur_day - library.signup) * library.efficiency;

    for (unsigned int i = 0; i < library.book_scores.size() && i < possible; i++) {
        if (available.find(library.book_scores[i]) != available.end()) {
            score += books[library.book_scores[i]];
        }
    }

    return score;
}

int select_library(std::unordered_set<unsigned int> &available_library,
                   std::unordered_set<unsigned int> &available_books) {

    static unsigned cur_day = 0;
    int result = 0;

    float max_score = 0;
    for (auto it = available_library.cbegin(); it != available_library.cend(); it++) {

        auto &li = libraries[*it];

        if (days < cur_day + li.signup)
            continue;

        float score = compute_intersection(li, available_books, cur_day) / li.signup;
        if (score > max_score) {
            max_score = score;
            result = *it;
        }
    }

    available_library.erase(result);
    for (unsigned int book : libraries[result].books) {
        available_books.erase(book);
    }

    if (days > cur_day + libraries[result].signup)
        cur_day += libraries[result].signup;
    else {
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
        for (const auto b : libraries[i].books) {
            libraries[i].book_scores.push_back(b);
        }
        std::sort(libraries[i].book_scores.begin(), libraries[i].book_scores.end(),
                  [](unsigned int a, unsigned int b) { return books[a] > books[b]; });
    }

    // Iterate
    std::vector<unsigned int> id_libraries{};
    for (auto i = 0u; i < libraries.size(); i++) {
        auto res = select_library(available_libraries, available_books);
        if (res == -1)
            break;
        id_libraries.push_back(res);
    }

    return id_libraries;
}
