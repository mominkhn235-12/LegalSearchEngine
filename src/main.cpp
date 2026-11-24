#include "DocumentLoader.h"
#include "IndexBuilder.h"
#include "QueryProcessor.h"
#include "RankingModule.h"
#include "ResultFormatter.h"
#include "SearchModule.h"
#include "SnippetGenerator.h"
#include "TextProcessor.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    DocumentLoader loader;
    TextProcessor textProcessor;
    QueryProcessor queryProcessor(textProcessor);
    IndexBuilder indexBuilder;
    const vector<Document> documents = loader.loadDocuments("data");
    unordered_map<int, string> documentNames;
    unordered_map<int, const Document*> documentsById;
    for (const Document& document : documents) {
        documentNames.emplace(document.id, document.filename);
        documentsById.emplace(document.id, &document);
    }

    for (const Document& document : documents) {
        const vector<string> words = textProcessor.process(document.content);
        indexBuilder.addDocument(document.id, words);
    }

    SearchModule searchModule(indexBuilder.getIndex());
    RankingModule rankingModule;
    ResultFormatter resultFormatter;
    SnippetGenerator snippetGenerator;

    vector<string> terms;
    for (const auto& entry : indexBuilder.getIndex()) {
        terms.push_back(entry.first);
    }
    sort(terms.begin(), terms.end());

    cout << "Inverted index:\n";
    const auto& invertedIndex = indexBuilder.getIndex();
    for (const string& term : terms) {
        cout << term << ":";
        vector<int> documentIds;
        for (const auto& documentEntry : invertedIndex.at(term)) {
            documentIds.push_back(documentEntry.first);
        }
        sort(documentIds.begin(), documentIds.end());

        for (int documentId : documentIds) {
            cout << ' ' << documentId << "(frequency: "
                 << invertedIndex.at(term).at(documentId) << ')';
        }
        cout << '\n';
    }

    cout << "Total loaded documents: " << documents.size() << '\n';

    cout << "Enter a search query: ";
    string query;
    if (!getline(cin, query)) {
        cout << "No search query was provided.\n";
        return 0;
    }

    const vector<string> queryWords = queryProcessor.process(query);
    if (queryWords.empty()) {
        cout << "No searchable tokens were found.\n";
        return 0;
    }

    cout << "Processed tokens:";
    for (const string& token : queryWords) {
        cout << ' ' << token;
    }
    cout << '\n';

    unordered_map<string, vector<pair<int, int>>> searchResults;
    for (const string& token : queryWords) {
        searchResults.emplace(token, searchModule.search(token));
    }

    const vector<pair<int, int>> rankedResults = rankingModule.rank(searchResults);
    unordered_map<int, string> documentSnippets;
    for (const auto& result : rankedResults) {
        const auto document = documentsById.find(result.first);
        if (document != documentsById.end()) {
            documentSnippets.emplace(
                result.first,
                snippetGenerator.generate(document->second->content, queryWords));
        }
    }

    resultFormatter.display(rankedResults, documentNames, documentSnippets);
    return 0;
}
