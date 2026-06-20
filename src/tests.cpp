//
// Created by kurchin_iu on 17.06.2026.
//
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "ConverterJSON.h"

using namespace std;

//тест для метода GetTextDocuments
vector<string> GetTextDocuments();
int GetResponsesLimit();

ConverterJSON converter;

TEST(ConverterJSON_Tests, GetTextDocuments_ValidFile) {


    //создаю тестовый JSON файл config,json
    //правльный тест
    ofstream testConfig("config.json");
    testConfig << R"({
        "config": {
            "name": "SearchEngine",
            "version": "1.0",
            "max_responses": 5
        },
        "files": [
            "../resources/file1.txt",
            "../resources/file2.txt"
        ]
    })";
    testConfig.close();

    vector<string> expected = {
        "milk sugar coffee\n",
        "coffee water coffee\n",
        "aaaaaaaa\n"
    };
    vector<string> result;

    ASSERT_NO_THROW({
        result = converter.GetTextDocuments();
    });

    EXPECT_EQ(result, expected);

    remove("config.json");
}

//тест для GetResponsesLimit
TEST(ConverterJSON_Tests, GetResponsesLimit_ValidValue) {
    ofstream testConfig("config.json");
    testConfig << R"({
        "config": {
            "name": "SearchEngine",
            "version": "1.0",
            "max_responses": 5
        },
        "files": [
            "../resources/file001.txt",
            "../resources/file002.txt"
        ]
    })";
    testConfig.close();

    int limit = converter.GetResponsesLimit();

    EXPECT_EQ(limit, 5);

    remove("config.json");
}