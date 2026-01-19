#pragma once 
#include<string>
#include<vector>

struct Document {
    int id ; 
    std::string title; 
    std::string description; 
};

std::vector<Document>parse_json(); 