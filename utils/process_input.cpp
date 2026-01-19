#include <cctype>
#include "../include/process_input.hpp"
#include<string>
#include "../include/stemming/english_stem.h"
#include <vector>
#include "../include/string_utils.hpp"


std::vector<std::string> parse_input(std::string input){
    stemming::english_stem<> StemEnglish ; 
    std::string word ; 
    std::vector<std::string> parsed_input ; 
    for (char c : input) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            word += std::tolower(static_cast<unsigned char>(c));
        } else {
            if (!word.empty()) {
                std::wstring wword = toWString(word);
                StemEnglish(wword);
                std::string stemmed = toString(wword);
                //add it to the final parsed input
                parsed_input.push_back(stemmed); 
                word.clear();
            }
        }
    }

    // last word
    if (!word.empty()) {
        std::wstring wword = toWString(word);
        StemEnglish(wword);
        std::string stemmed = toString(wword);
        parsed_input.push_back(stemmed); 
        word.clear(); 
    }
    
    return parsed_input ; 
}