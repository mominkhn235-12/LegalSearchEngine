#include "RankingModule.h"

#include <algorithm>

using namespace std;

vector<pair<int, int>> RankingModule::rank(
    const unordered_map<string, vector<pair<int, int>>>& searchResults) const {
    unordered_map<int, int> scores;
    for (const auto& termResults : searchResults) {
        for (const auto& result : termResults.second) {
            scores[result.first] += result.second;
        }
    }

    vector<pair<int, int>> rankedResults;
    rankedResults.reserve(scores.size());
    for (const auto& documentScore : scores) {
        rankedResults.emplace_back(documentScore.first, documentScore.second);
    }

    sort(rankedResults.begin(), rankedResults.end(),
         [](const pair<int, int>& left, const pair<int, int>& right) {
             if (left.second != right.second) {
                 return left.second > right.second;
             }
             return left.first < right.first;
         });
    return rankedResults;
}
