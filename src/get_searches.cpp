#include <iostream>
#include <string>
#include "../include/bm25.hpp"
#include "../include/process_input.hpp"

int main() {
    std::string input;

    std::cout << "Welcome to the search engine fam\n";
    std::cout << "Enter your query bro: ";

    std::getline(std::cin, input); 

    auto parsed_input = parse_input(input);
    auto scored_docs  = score_all_documents(parsed_input);

    // -------- print results --------
    std::cout << "\nSearch results:\n";

    for (const auto& [docId, score] : scored_docs) {
        std::cout << "DocID: " << docId
                  << " | Score: " << score << "\n";
    }

    return 0;
}
