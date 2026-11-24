#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class RankingModule {
public:
    std::vector<std::pair<int, int>> rank(
        const std::unordered_map<std::string, std::vector<std::pair<int, int>>>& searchResults) const;
};
