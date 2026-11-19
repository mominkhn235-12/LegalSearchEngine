#include "DocumentLoader.h"
#include "IndexBuilder.h"
#include "TextProcessor.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    DocumentLoader loader;
    TextProcessor textProcessor;
    IndexBuilder indexBuilder;
    const vector<Document> documents = loader.loadDocuments("data");

    for (const Document& document : documents) {
        const vector<string> words = textProcessor.process(document.content);
        indexBuilder.addDocument(document.id, words);
    }

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
    return 0;
}
