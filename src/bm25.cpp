#include "../include/class_inverted_index.hpp"
#include<math.h>

double calculate_tf(
    int termFreq,
    int docLength,
    double avgDocLength
) {
    constexpr double k1 = 1.5;
    constexpr double b  = 0.75;

    return (termFreq * (k1 + 1)) /
           (termFreq + k1 * (1 - b + b * (docLength / avgDocLength)));
}

double combined_tf(
    int titleTF,
    int descTF
) {
    constexpr double TITLE_WEIGHT = 2.0;
    constexpr double DESC_WEIGHT  = 1.0;

    return titleTF * TITLE_WEIGHT +
           descTF  * DESC_WEIGHT;
}


double calculate_idf(
    int totalDocs,
    int docFreq
) {
    return std::log(
        (totalDocs - docFreq + 0.5) /
        (docFreq + 0.5) + 1.0
    );
}

//func for per doc 
double score_query(
    const std::vector<std::string>& queryTerms,
    int docId
) {
    auto& index_class = InvertedIndexClass::getInstance();
    const auto& inverted_index = index_class.getInvertedIndex();

    double score = 0.0;

    int docLength = index_class.get_doc_length(docId);
    double avgDL  = index_class.get_avg_doc_length();
    int totalDocs = index_class.getTotalDocs();

    for (const auto& term : queryTerms) {
        auto it = inverted_index.find(term);
        if (it == inverted_index.end())
            continue;  // term not in corpus

        const auto& postings = it->second;

        auto docIt = postings.find(docId);
        if (docIt == postings.end())
            continue;  // term not in this document

        const auto& fieldPosting = docIt->second;

        //tf weighted 
        double tf = combined_tf(
            fieldPosting.titleFrequency,
            fieldPosting.descriptionFrequency
        );

        double tf_score = calculate_tf(
            tf,
            docLength,
            avgDL
        );
        
        //idf
        int docFreq = postings.size();

        double idf = calculate_idf(
            totalDocs,
            docFreq
        );

        score += tf_score * idf;
    }

    return score;
}

std::unordered_map<int, double>
score_all_documents(
    const std::vector<std::string>& queryTerms
) {
    auto& index_class = InvertedIndexClass::getInstance();

    std::unordered_map<int, double> docScores;

    int totalDocs = index_class.getTotalDocs();

    for (int docId = 0; docId < totalDocs; ++docId) {
        double score = score_query(queryTerms, docId);

        if (score > 0.0) {
            docScores[docId] = score;
        }
    }

    return docScores;
}

