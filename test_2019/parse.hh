#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<int, std::unordered_set<unsigned char>> photos_h;
std::unordered_map<int, std::unordered_set<unsigned char>> photos_v;

void parse();
