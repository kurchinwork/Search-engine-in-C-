//
// Created by Ellies on 20.06.2026.
//

#include "../include/InvertedIndex.h"
#include <sstream>

using namespace std;

void InvertedIndex::UpdateDocumentBase(vector<string> input_dosc) {
    docs.clear();
    freq_dict.clear();

    docs = input_dosc;

    vector<thread> threads;

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {
        threads.push_back(thread([this, doc_id] () {
            string text = docs[doc_id];
            stringstream ss(text);
            string word;

            map<string, size_t> local_bag_of_words;
            while (ss >> word) {
                local_bag_of_words[word]++;
            }

            lock_guard<mutex> lock(dict_mutex);
            for (const auto& [local_word, count] : local_bag_of_words) {
                Entry entry;

                entry.doc_id = doc_id;
                entry.count = count;

                freq_dict[local_word].push_back(entry);
            }
        }));
    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

vector<Entry> InvertedIndex::GetWordCount(const string &word) {

    auto it = freq_dict.find(word);

    if (it == freq_dict.end()) {
        return {};
    } else {
        return it->second;
    }
}

