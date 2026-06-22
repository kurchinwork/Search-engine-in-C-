//
// Created by kurchin_iu on 15.06.2026.
//

#include "ConverterJSON.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

//Метод получения содержимого файлов
vector<string> ConverterJSON::GetTextDocuments() {

    vector<string> containFile;

    ifstream JSON_file ("..\\config\\config.json");

    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
        throw runtime_error ("File \"config.json\" is not found");
    }

    json config_json;
    JSON_file >> config_json;
    JSON_file.close();

    if (config_json.contains("config")) {

        //проверка если поле name в файле config.json пустое
        if (config_json["config"].contains("name")) {
            string engineInfo = config_json["config"]["name"].get<string>();
            if (engineInfo.empty()) {
                throw runtime_error ("Field \"name:\" is empty");
            }
        } else {
            throw runtime_error ("Field \"name:\" is not find");
        }

        //проверка если поле version в файле config.json пустое
        if (config_json["config"].contains("version")) {
            string engineInfo = config_json["config"]["version"].get<string>();
            if (engineInfo.empty()) {
                throw runtime_error ("Field \"version:\" is empty");
            }
        } else {
            throw runtime_error ("Field \"version:\" is not find");
        }


    } else {
        throw runtime_error ("Field \"config:\" is empty and not contain forward parameters");
    }


    //считывание содержимого файлов указанных в конфиге
    if (config_json.contains("files")) {

        vector<string> filePaths = config_json["files"].get<vector<string>>();
        for (const string& path : filePaths) {
            ifstream textFile(path);

            if (!textFile.is_open()) {
                cerr << "Error opening file: " << path << endl;
                continue;
            }

            string fileContent, line;

            while (getline(textFile, line)) {
                fileContent += line + "\n";
            }

            textFile.close();
            containFile.push_back(fileContent);

        }
    } else {
        throw runtime_error ("Field: \"files\" is empty in \"config.json\"");
    }

    // ошибся в названии папки resoursces и не понимал почему в контейнер не идет содержимое файлов
    // создал вот это для проверки
    // for (const auto& path : containFile) {
    //     std::cout << "Найдено в JSON: " << path << std::endl;
    // }

    return containFile;
}

//Метод определения максимального количества ответов на запрос (готов)
int ConverterJSON::GetResponsesLimit() {
    ifstream JSON_file ("..\\config\\config.json");

    //валидация config.json
    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
        throw runtime_error ("File \"config.json\" is not found");
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

    return 5;
}

//Метод получения запросов из файла requests.json
vector<string>ConverterJSON::GetRequests() {
    return {};
}

//Метод, который помещает результаты поиска в answers.json
void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int,float>>>answers) {

}

void ConverterJSON::GetInfoConfig() {
    ifstream JSON_file ("..\\config\\config.json");

    if (!JSON_file.is_open()) {
        cerr << "File \"config.json\" is not found" << endl;
        throw runtime_error ("File \"config.json\" is not found");
    }

    json config_json;
    JSON_file >> config_json;
    JSON_file.close();

    cout << "--Current configuration:\n"
            "Name: " << config_json["config"]["name"] << endl;
    cout << "Version: " << config_json["config"]["version"] << endl;
    cout << "Max responses: " << GetResponsesLimit() << endl;
}
