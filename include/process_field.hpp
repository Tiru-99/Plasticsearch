#pragma once 
#include "stemming/english_stem.h"
#include<string>
#include <unordered_map>


class InvertedIndexClass ; 

void processField(
    const std::string& text ,
    int docId , 
    bool isTitle , 
    stemming::english_stem<>& StemEnglish,
    std::unordered_map<int, int>& docLengths,
    InvertedIndexClass& indexClass
);