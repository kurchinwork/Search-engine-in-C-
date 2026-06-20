//
// Created by kurchin_iu on 15.06.2026.
//

#ifndef SEARCHENGINE_CONVERTERJSON_H
#define SEARCHENGINE_CONVERTERJSON_H

#include <vector>
#include <string>
#pragma once

//Основной класс, его методы в ConverterJSON.cpp
class ConverterJSON {
public:
    ConverterJSON() = default;

    //Метод получения содержимого файлов
    std::vector<std::string>GetTextDocuments();

    //Метод определения максимального количества ответов на запрос
    int GetResponsesLimit();

    //Метод получения запросов из файла requests.json
    std::vector<std::string>GetRequests();

    //Метод вкладки найденного в файл
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

    //метод вывода инфы уже проверенного конфига
    void GetInfoConfig();


};



#endif //SEARCHENGINE_CONVERTERJSON_H