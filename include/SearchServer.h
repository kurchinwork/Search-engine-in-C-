//
// Created by kurchin_iu on 24.06.2026.
//

#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H

#pragma once

#include <vector>
#include <string>
#include <utility>

#include "InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
private:
    InvertedIndex& _index;
public:
    SearchServer(InvertedIndex& idx) : _index(idx) { };

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

};


#endif //SEARCHENGINE_SEARCHSERVER_H