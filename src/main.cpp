#include <iostream>
#include <nlohmann/json.hpp>

#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

using json = nlohmann::json;
using namespace std;

int main() {
    try {
        ConverterJSON converter;

        cout << "--------Start read config--------" << endl;
        auto documents = converter.GetTextDocuments();

        converter.GetInfoConfig();

        cout << "\n---Indexing documents---" << endl;
        InvertedIndex index;
        index.UpdateDocumentBase(documents);
        cout << "-Indexing is a complete-" << endl;



        cout << "\n---Reading requests---" << endl;
        auto requests = converter.GetRequests();
        if (requests.empty()) {
            cout << "Error: request.json is empty or not found" << endl;
            return 1;
        }
        cout << "Be loaded " << requests.size() << " requests;" << endl;
        cout << "-Reading is a complete-";


        cout << "\n---Searching in process---" << endl;
        SearchServer search_server(index);
        auto searchResult = search_server.search(requests);

        vector<vector<pair<int, float>>> finalAnswers;
        for (const auto& query_res : searchResult) {
            vector<pair<int, float>> convertedResult;
            for (const auto& item : query_res) {
                convertedResult.push_back(make_pair(static_cast<int>(item.doc_id), item.rank));
            }
            finalAnswers.push_back(convertedResult);
        }
        converter.putAnswers(finalAnswers);

        cout << "-Searching be endned successfully-" << endl;

    } catch (const exception& e) {
        cerr << "Error caught in main.cpp" << e.what() << endl;
        cerr << "The app has been terminated automatically";

        return 1;
    }

    return 0;
}
