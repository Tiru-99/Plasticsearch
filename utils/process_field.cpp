#include <cctype>
#include<string>
#include "../include/stemming/english_stem.h"
#include <unordered_map>
#include "../include/process_field.hpp"
#include "../include/class_inverted_index.hpp"
#include "../include/string_utils.hpp"

void processField(
    const std::string& text,
    int docId,
    bool isTitle,
    stemming::english_stem<>& StemEnglish , 
    std::unordered_map<int, int>& docLength , 
    InvertedIndexClass& indexClass
) {
    std::string word; 
    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            word += std::tolower(static_cast<unsigned char>(c));
        } else {
            if (!word.empty()) {
                std::wstring wword = toWString(word);
                StemEnglish(wword);
                std::string stemmed = toString(wword);

                if (isTitle){
                    indexClass.index[stemmed][docId].titleFrequency++;
                    docLength[docId]++ ;
                } else {
                    indexClass.index[stemmed][docId].descriptionFrequency++;
                    docLength[docId]++ ; 
                }
                word.clear();
            }
        }
    }

    // last word
    if (!word.empty()) {
        std::wstring wword = toWString(word);
        StemEnglish(wword);
        std::string stemmed = toString(wword);

        if (isTitle){
            indexClass.index[stemmed][docId].titleFrequency++;
            docLength[docId]++ ; 
        } else {
            indexClass.index[stemmed][docId].descriptionFrequency++;
            docLength[docId]++ ; 
        }
    }
    
}