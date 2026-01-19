#include "../include/class_inverted_index.hpp"
#include "../include/process_field.hpp"

void InvertedIndexClass::buildInvertedIndex(
    const std::vector<Document>& documents
) {
    int totalWords = 0;
    int totalDocs  = 0;

    for (const auto& doc : documents) {
        ::processField(doc.title, doc.id, true,
                     StemEnglish, docLengths, *this);

        ::processField(doc.description, doc.id, false,
                     StemEnglish, docLengths, *this);

        totalWords += docLengths[doc.id];
        totalDocs++;
    }

    avg_doc_length =
        static_cast<double>(totalWords) / totalDocs;

    total_docs = totalDocs;
}

const InvertedIndex&
InvertedIndexClass::getInvertedIndex() const {
    return index;
}

int InvertedIndexClass::get_doc_length(int docId) const {
    auto it = docLengths.find(docId);
    if (it == docLengths.end()) {
        return 0;  
    }
    return it->second;
}

double InvertedIndexClass::get_avg_doc_length() const {
    return avg_doc_length;
}

int InvertedIndexClass::getTotalDocs() const {
    return total_docs;
}
