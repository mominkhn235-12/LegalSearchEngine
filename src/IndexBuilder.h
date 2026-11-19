
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class IndexBuilder {
public:
    void addDocument(int documentId, const std::vector<std::string>& words);

    const std::unordered_map<std::string, std::unordered_map<int, int>>& getIndex() const;

private:
    // Word -> Document ID -> Frequency
    std::unordered_map<std::string, std::unordered_map<int, int>> invertedIndex;
};
