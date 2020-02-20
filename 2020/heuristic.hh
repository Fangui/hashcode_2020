#pragma once

#include <unordered_set>

int select_library(std::unordered_set<unsigned int> &available_library,
                            std::unordered_set<unsigned int> &available_books);

std::vector<unsigned int> sort_libraries();
