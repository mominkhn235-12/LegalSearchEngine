#include "QueryProcessor.h"

using namespace std;

QueryProcessor::QueryProcessor(TextProcessor& processor)
    : textProcessor(processor) {}

vector<string> QueryProcessor::process(const string& query) const {
    return textProcessor.process(query);
}
