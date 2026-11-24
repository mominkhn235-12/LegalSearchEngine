#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SearchModule {
public:
    explicit SearchModule(
        const std::unordered_map<std::string, std::unordered_map<int, int>>& index);

    std::vector<std::pair<int, int>> search(const std::string& query) const;

private:
    const std::unordered_map<std::string, std::unordered_map<int, int>>& invertedIndex;
};
