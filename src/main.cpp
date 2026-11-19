#include "DocumentLoader.h"
#include "TextProcessor.h"

#include <iostream>
using namespace std;

int main() {
    DocumentLoader loader;
    TextProcessor textProcessor;
    const vector<Document> documents = loader.loadDocuments("data");

    for (const Document& document : documents) {
        const vector<string> words = textProcessor.process(document.content);

        cout << "ID: " << document.id << '\n'
             << "Processed words:";
        for (const string& word : words) {
            cout << ' ' << word;
        }
        cout << '\n';
    }

    cout << "Total loaded documents: " << documents.size() << '\n';
    return 0;
}
