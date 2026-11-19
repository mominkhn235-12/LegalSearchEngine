#pragma once

#include <string>
#include <vector>

struct Document {
    int id;
    std::string filename;
    std::string content;
};

class DocumentLoader {
public:
    std::vector<Document> loadDocuments(const std::string& folderPath);
};
