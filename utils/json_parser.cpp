#include <iostream>
#include "../include/json.hpp" 
#include <fstream>
#include <vector>
#include "../include/document.hpp"
using json = nlohmann::json ; 


std::vector<Document> parse_json(){
    std::ifstream file("data/documents.json"); 
    
    if(!file.is_open()){
        std::cerr<<"Error cound not open json document"<<std::endl; 
        return {};
    }
    
    json j ;
    try { 
        j = json::parse(file);
    } catch(json::parse_error &e){
        std::cerr<<"Error could not parse the file into json"<<std::endl; 
    }
    
    file.close();
    //push the document; 
    std::vector<Document> parsed ; 
    for (auto& doc : j) {
        Document document;
    
        document.id = doc.contains("id") && doc["id"].is_number()
            ? doc["id"].get<int>()
            : -1;
    
        document.title = doc.contains("title") && doc["title"].is_string()
            ? doc["title"].get<std::string>()
            : "";
    
        document.description = doc.contains("description") && doc["description"].is_string()
            ? doc["description"].get<std::string>()
            : "";
    
        parsed.push_back(document);
    }

    return parsed ; 
}

