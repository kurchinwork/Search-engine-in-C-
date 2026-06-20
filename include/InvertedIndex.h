//
// Created by Ellies on 20.06.2026.
//

#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H

#pragma once

#include <map>
#include <string>
#include <vector>

//стркутура хранения информации вхождения слова
struct Entry {
    size_t doc_id;
    size_t count;
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> input_dosc);
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    //список содержимого документов
    std::vector<std::string> docs;

    //словарь частот слов
    std::map<std::string, std::vector<Entry>> freq_dict;

};


#endif //SEARCHENGINE_INVERTEDINDEX_H
