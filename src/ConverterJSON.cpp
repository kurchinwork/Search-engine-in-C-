//
// Created by kurchin_iu on 15.06.2026.
//

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;

//Метод получения содержимого файлов
vector<string>GetTextDocuments() {

    vector<string> containFile;

    ifstream JSON_file ("config.json");

    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
        return containFile;
    }

    try {
        json config_json;
        JSON_file >> config_json;
        JSON_file.close();

        if (config_json.contains("files")) {
            containFile = config_json["files"].get<vector<string>>();
        } else {
            cerr << "Field: \"files\" is empty in \"config.json\"" << endl;
        }
    } catch (const json::exception &e) {
        cerr << "JSON parsing error: " << e.what() << endl;
    }
    return containFile;
}

/** 1 Написать методы
 *  vector<string>GetTextDocuments() {}
 *  int GetResponsesLimit(){}
 *  void putAnswers(std::vector<std::vector<std::pair<int,float>>>answers) {}
 *
 *  Подключить Unit тестирование через Gtest
 *
 */

//Метод определения максимального количества ответов на запрос (готов)
int GetResponsesLimit()
{
    ifstream JSON_file ("config.json");

    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
        return 1;
    }

    try {
        json config_json;
        JSON_file >> config_json;
        JSON_file.close();

        if (config_json.contains("config") && config_json["config"].contains("max_responses")) {
            return config_json["config"]["max_responses"].get<int>();
        } else {
            cerr << "Feild: \"max_responses\" is not found" << endl;
        }
    } catch (const json::exception &e) {
        cerr <<  "JSON parsing error: " << e.what() << endl;
    }

    return 1;
}

//Метод получения запросов из файла requests.json
std::vector<std::string>GetRequests() {

}

//Метод, который помещает результаты поиска в answers.json
void putAnswers(std::vector<std::vector<std::pair<int,float>>>answers) {

}


