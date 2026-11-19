
#include "IndexBuilder.h"

using namespace std;

void IndexBuilder::addDocument(int documentId, const vector<string>& words) {
    for (const string& word : words) {
        invertedIndex[word][documentId]++;
    }
}

const unordered_map<string, unordered_map<int, int>>& IndexBuilder::getIndex() const {
    return invertedIndex;
}
