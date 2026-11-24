#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class ResultFormatter {
public:
    void display(const std::vector<std::pair<int, int>>& rankedResults,
                 const std::unordered_map<int, std::string>& documentNames,
                 const std::unordered_map<int, std::string>& documentSnippets) const;
};
