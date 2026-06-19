#include <iostream>
#include <nlohmann/json.hpp>

#include "ConverterJSON.h"

using json = nlohmann::json;
using namespace std;

int main() {

    try {
        ConverterJSON converter;

        auto documents = converter.GetTextDocuments();

        cout << "--------Start read config--------" << endl;
        converter.getInfoConfig();



    } catch (const exception& e) {
        cerr << "Error caught in main.cpp" << e.what() << endl;
        cerr << "The app has been terminated automatically";

        return 1;
    }
    return 0;
}
