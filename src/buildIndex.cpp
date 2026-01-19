#include<iostream>
#include <strings.h>
#include "../include/document.hpp"
#include "../include/class_inverted_index.hpp"

int main(){
    auto& index_class = InvertedIndexClass::getInstance(); 
    //parse json
    auto documents = parse_json();
    index_class.buildInvertedIndex(documents); 
    auto inverted_index = index_class.getInvertedIndex(); 
    std::cout<<"The inverted index is built successfully";
    
    return 0 ; 
}