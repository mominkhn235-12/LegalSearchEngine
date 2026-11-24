#pragma once

#include <string>
#include <vector>

class SnippetGenerator {
public:
    std::string generate(const std::string& documentContent,
                         const std::vector<std::string>& queryTerms) const;
};
