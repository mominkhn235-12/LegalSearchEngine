#include "TextProcessor.h"

#include <cctype>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

vector<string> TextProcessor::process(const string& text) {
    static const unordered_set<string> stopWords = {
        "the", "is", "to", "and", "of", "a", "an", "in", "for", "was"
    };

    vector<string> words;
    string currentWord;

    const auto addWord = [&]() {
        if (!currentWord.empty() && stopWords.find(currentWord) == stopWords.end()) {
            words.push_back(move(currentWord));
        }
        currentWord.clear();
    };

    for (unsigned char character : text) {
        if (isalnum(character)) {
            currentWord += static_cast<char>(tolower(character));
        } else {
            addWord();
        }
    }
    addWord();

    return words;
}
