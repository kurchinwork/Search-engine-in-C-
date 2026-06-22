//
// Created by Ellies on 20.06.2026.
//

#include "../include/InvertedIndex.h"
#include <sstream>

using namespace std;

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_dosc) {
    docs.clear();
    freq_dict.clear();

    docs = input_dosc;

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {
        string text = docs[doc_id];
        stringstream ss(text);

        string word;

        while (ss >> word) {
            auto& entries = freq_dict[word];

            if (!entries.empty() && entries.back().doc_id == doc_id) {
                entries.back().count++;
            } else {
                Entry entry;

                entry.doc_id = doc_id;
                entry.count = 1;

                entries.push_back(entry);
            }
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

}

