#include "SearchModule.h"
#include <algorithm>

using namespace std;

SearchModule::SearchModule(
    const unordered_map<string, unordered_map<int, int>>& index)
    : invertedIndex(index) {}

vector<pair<int, int>> SearchModule::search(const string& query) const {
    vector<pair<int, int>> results;
    const auto term = invertedIndex.find(query);
    if (term == invertedIndex.end()) {
        return results;
    }

    results.reserve(term->second.size());
    for (const auto& documentEntry : term->second) {
        results.emplace_back(documentEntry.first, documentEntry.second);
    }
    std::sort(results.begin(),results.end(),[](const pair<int,int>& a, const pair<int,int>&b)
    {
        return a.first < b.first;
    });
    return results;
}
