#pragma once

#include <vector>
#include <string>
#include <unordered_map>

double calculate_tf(
    int termFreq,
    int docLength,
    double avgDocLength
);

double combined_tf(
    int titleTF,
    int descTF
);

double calculate_idf(
    int totalDocs,
    int docFreq
);


double score_query(
    const std::vector<std::string>& queryTerms,
    int docId
);

std::unordered_map<int, double>
score_all_documents(
    const std::vector<std::string>& queryTerms
);
