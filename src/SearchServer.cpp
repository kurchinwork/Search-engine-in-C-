//
// Created by kurchin_iu on 24.06.2026.
//

#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "../include/SearchServer.h"
#include "../include/ConverterJSON.h"


using namespace std;

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input) {

    vector<vector<RelativeIndex>> result;

    for (int i = 0; queries_input.size() > i; i++) {

        set<string> unique_wrods;

        string word;
        string query = queries_input[i];
        stringstream ss(query);

        while (ss >> word) {
            unique_wrods.insert(word);
        }

        vector<string> words_vector (unique_wrods.begin(), unique_wrods.end());
        sort(words_vector.begin(), words_vector.end(), [this] (const string& a, const string& b) {
            return _index.GetWordCount(a).size() < _index.GetWordCount(b).size();
        });

        map<size_t, size_t> absoluteRelevance;

        for (const auto& w : words_vector) {
            auto entries = _index.GetWordCount(w);
            for (const auto& entry : entries) {
                absoluteRelevance[entry.doc_id] += entry.count;
            }
        }

        if (absoluteRelevance.empty()) {
            result.push_back({});
            continue;
        }

        size_t max_ra = 0;
        for (const auto& pair : absoluteRelevance) {
            if (pair.second > max_ra) {
                max_ra = pair.second;
            }
        }

        vector<RelativeIndex> current_query_result;
        //рассчет относительной релевантности
        for (const auto& pair : absoluteRelevance) {
            RelativeIndex rel_idx;
            rel_idx.doc_id = pair.first;

            rel_idx.rank = (float)pair.second / max_ra;

            current_query_result.push_back(rel_idx);
        }

        sort(current_query_result.begin(), current_query_result.end(), [](const RelativeIndex &a, const RelativeIndex &b) {
            if (a.rank != b.rank) {
                return a.rank > b.rank;
            }

            return a.doc_id < b.doc_id;
        });

        ConverterJSON converter;
        int max_responses = converter.GetResponsesLimit();

        if (current_query_result.size() > max_responses) {
            current_query_result.resize(max_responses);
        }

        result.push_back(current_query_result);
    }



    return result;
}