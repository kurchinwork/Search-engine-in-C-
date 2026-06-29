//
// Created by kurchin_iu on 24.06.2026.
//

#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

#include "../include/SearchServer.h"


using namespace std;

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input) {
    vector<vector<RelativeIndex>> result;

    for (int i = 0; queries_input.size() > i; i++) {

        set<string> unique_wrods;
        string word;
        stringstream ss(queries_input[i]);

        while (ss >> word) {
            unique_wrods.insert(word);
        }

        if (unique_wrods.empty()) {
            result.push_back({});
            continue;
        }

        map<size_t, size_t> AbsoluteRelevance;
        map<size_t, size_t> words_count_in_doc;

        for (const auto& w:unique_wrods) {
            auto entries = _index.GetWordCount(w);
            for (const auto& entry : entries) {
                AbsoluteRelevance[entry.doc_id]  += entry.count;
                words_count_in_doc[entry.doc_id]++;
            }
        }

        vector<RelativeIndex> current_query_result;
        size_t max_ra = 0;

        for (const auto& [doc_id, total_count] : AbsoluteRelevance) {
            if (words_count_in_doc[doc_id] == unique_wrods.size()) {
                RelativeIndex rel_idx;
                rel_idx.doc_id = doc_id;

                rel_idx.rank = static_cast<float>(total_count);
                current_query_result.push_back(rel_idx);

                if (total_count > max_ra) {
                    max_ra = total_count;
                }
            }
        }

        if (current_query_result.empty()) {
            result.push_back({});
            continue;
        }

        //расчет относительной релевантности
        for (auto& item : current_query_result) {
            item.rank = item.rank / max_ra;
        }

        //сортировка по убыванию rank, при равенстве то по возрастанию doc_id
        sort(current_query_result.begin(), current_query_result.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            if (abs(a.rank - b.rank) > 1e-5f) {
                return a.rank > b.rank;
            }
            return a.doc_id < b.doc_id;
        });

        if (current_query_result.size() > static_cast<size_t>(_responses_limit)) {
            current_query_result.resize(_responses_limit);
        }

        result.push_back(current_query_result);
    }

    return result;

}