#include "DocumentLoader.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <system_error>
#include <utility>
using namespace std;

vector<Document> DocumentLoader::loadDocuments(const string& folderPath) {
    namespace fs = filesystem;

    vector<Document> documents;
    error_code error;
    fs::directory_iterator entry(folderPath, error);
    const fs::directory_iterator end;
    if (error) {
        return documents;
    }

    vector<fs::path> textFiles;
    for (; entry != end; entry.increment(error)) {
        if (error) {
            error.clear();
            continue;
        }

        error_code statusError;
        if (entry->is_regular_file(statusError) && !statusError &&
            entry->path().extension() == ".txt") {
            textFiles.push_back(entry->path());
        }
    }

    sort(textFiles.begin(), textFiles.end(), [](const fs::path& left, const fs::path& right) {
        return left.filename().string() < right.filename().string();
    });

    int nextId = 1;
    for (const fs::path& filePath : textFiles) {
        ifstream input(filePath, ios::binary);
        if (!input) {
            continue;
        }

        string content((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
        if (input.bad()) {
            continue;
        }

        documents.push_back({nextId++, filePath.filename().string(), move(content)});
    }

    return documents;
}
