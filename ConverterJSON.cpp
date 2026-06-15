//
// Created by kurchin_iu on 15.06.2026.
//

#include "ConverterJSON.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

//Метод получения содержимого файлов
std::vector<std::string>GetTextDocuments() {
    ifstream JSON_file ("config.json");

    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
    }


}

//Метод определения максимального количества ответов на запрос
int GetResponsesLimit()
{

}

//Метод получения запросов из файла requests.json
std::vector<std::string>GetRequests() {

}

//Метод который помещает результаты поиска в answers.json
void putAnswers(std::vector<std::vector<std::pair<int,float>>>answers) {

}


