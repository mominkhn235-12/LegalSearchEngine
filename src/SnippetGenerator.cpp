
#include "SnippetGenerator.h"

#include <algorithm>
#include <cctype>

using namespace std;

string SnippetGenerator::generate(
    const string& documentContent,
    const vector<string>& queryTerms) const {

    string lowercaseContent = documentContent;

    transform(lowercaseContent.begin(), lowercaseContent.end(),
              lowercaseContent.begin(),
              [](unsigned char character) {
                  return static_cast<char>(tolower(character));
              });

    size_t earliestPosition = string::npos;
    string earliestTerm;

    // Find the query term that appears earliest in the document.
    for (const string& queryTerm : queryTerms) {

        if (queryTerm.empty()) {
            continue;
        }

        string lowercaseTerm = queryTerm;

        transform(lowercaseTerm.begin(), lowercaseTerm.end(),
                  lowercaseTerm.begin(),
                  [](unsigned char character) {
                      return static_cast<char>(tolower(character));
                  });

        const size_t matchPosition = lowercaseContent.find(lowercaseTerm);

        if (matchPosition != string::npos &&
            matchPosition < earliestPosition) {

            earliestPosition = matchPosition;
            earliestTerm = lowercaseTerm;
        }
    }

    // No query term was found.
    if (earliestPosition == string::npos) {
        return string();
    }

    // Extract 50 characters before and after the match.
    const size_t snippetStart = earliestPosition > 50
        ? earliestPosition - 50
        : 0;

    const size_t matchEnd = earliestPosition + earliestTerm.length();

    const size_t charactersAfter =
        min(size_t{50}, documentContent.length() - matchEnd);

    const size_t snippetEnd = matchEnd + charactersAfter;

    string snippet = documentContent.substr(
        snippetStart, snippetEnd - snippetStart);

    if (snippetStart > 0) {
        snippet.insert(0, "...");
    }

    if (snippetEnd < documentContent.length()) {
        snippet.append("...");
    }

    return snippet;
}
