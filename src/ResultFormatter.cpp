#include "ResultFormatter.h"

#include <iostream>

using namespace std;

void ResultFormatter::display(
    const vector<pair<int, int>>& rankedResults,
    const unordered_map<int, string>& documentNames,
    const unordered_map<int, string>& documentSnippets) const {
    if (rankedResults.empty()) {
        cout << "No results found.\n";
        return;
    }

    static const string unknownDocument = "Unknown document";
    cout << "Ranked search results:\n";
    for (size_t index = 0; index < rankedResults.size(); ++index) {
        const int documentId = rankedResults[index].first;
        const int score = rankedResults[index].second;
        const auto documentName = documentNames.find(documentId);
        const string& filename = documentName == documentNames.end()
            ? unknownDocument
            : documentName->second;
        const auto snippet = documentSnippets.find(documentId);

        cout << index + 1 << ". " << filename
             << " (Document ID: " << documentId
             << ", Relevance score: " << score << ")\n";
        cout << "   " << (snippet == documentSnippets.end() || snippet->second.empty()
            ? "Snippet unavailable."
            : snippet->second) << '\n';
    }
}
