#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "document.hpp"
#include "stemming/english_stem.h"

struct FieldPosting {
    int titleFrequency = 0;
    int descriptionFrequency = 0;
};

// term -> docId -> FieldPosting
using InvertedIndex = std::unordered_map<
    std::string,
    std::unordered_map<int, FieldPosting>
>;


class InvertedIndexClass {
private:
    InvertedIndex index;                       
    std::unordered_map<int, int> docLengths;  
    double avg_doc_length = 0.0;
    int total_docs = 0;

    stemming::english_stem<> StemEnglish;
    
    friend void processField(
           const std::string&,
           int,
           bool,
           stemming::english_stem<>&,
           std::unordered_map<int, int>&,
           InvertedIndexClass&
       );

public:
    void processField(
        const std::string& text,
        int docId , 
        bool isTitle ,
        stemming::english_stem<>& StemEnglish
    );
    
    static InvertedIndexClass& getInstance() {
           static InvertedIndexClass instance; 
           return instance;
    }
    
    void buildInvertedIndex(const std::vector<Document>& documents);
      
    const InvertedIndex& getInvertedIndex() const;

    int get_doc_length(int docId) const;
    int getTotalDocs() const;
    double get_avg_doc_length() const;
};
