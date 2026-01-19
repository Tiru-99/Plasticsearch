#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "../include/class_inverted_index.hpp"
#include "../include/bm25.hpp"
#include "../include/process_input.hpp"
#include "../include/document.hpp"


std::vector<std::pair<int, double>>
top_k_results(
    const std::unordered_map<int, double>& scores,
    int k
) {
    std::vector<std::pair<int, double>> ranked(
        scores.begin(), scores.end()
    );

    std::sort(
        ranked.begin(),
        ranked.end(),
        [](const auto& a, const auto& b) {
            //descending score
            return a.second > b.second; 
        }
    );

    if (ranked.size() > static_cast<size_t>(k)) {
        ranked.resize(k);
    }

    return ranked;
}



void build_mode() {
    auto& index = InvertedIndexClass::getInstance();

    std::cout << "[BUILD] Building inverted index...\n";

    auto documents = parse_json();
    index.buildInvertedIndex(documents);

    std::cout << "[BUILD] Index built successfully\n";
    std::cout << "[BUILD] Total docs indexed: "
              << index.getTotalDocs() << "\n\n";

    std::cout << "[DEBUG] Inverted Index Snapshot:\n";
}



void search_mode() {
    auto& index = InvertedIndexClass::getInstance();

    std::cout << "[SEARCH] Building index...\n";
    auto documents = parse_json();
    index.buildInvertedIndex(documents);
    std::cout << "[SEARCH] Index ready\n\n";



    while (true) {
        std::string input;
        std::cout << "\nEnter your query (or 'exit'): ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        // parse input
        auto queryTerms = parse_input(input);

        if (queryTerms.empty()) {
            std::cout << "No valid query terms.\n";
            continue;
        }

        // score documents
        auto scores = score_all_documents(queryTerms);

        if (scores.empty()) {
            std::cout << "No results found.\n";
            continue;
        }

        // show results
        auto top5 = top_k_results(scores, 5);

        std::cout << "\nTop 5 results:\n";
        int rank = 1;
        for (const auto& [docId, score] : top5) {
            std::cout << rank++ << ") "
                      << "Doc " << docId
                      << " => " << score << "\n";
        }
    }
}
