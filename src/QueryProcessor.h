#pragma once

#include "TextProcessor.h"

#include <string>
#include <vector>

class QueryProcessor {
public:
    explicit QueryProcessor(TextProcessor& textProcessor);

    std::vector<std::string> process(const std::string& query) const;

private:
    TextProcessor& textProcessor;
};
