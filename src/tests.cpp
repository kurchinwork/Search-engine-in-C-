//
// Created by kurchin_iu on 17.06.2026.
//
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "ConverterJSON.h"
#include "InvertedIndex.h"

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

void TestInvertedIndexFunctionality(
    const std::vector<std::string>& docs,
    const std::vector<std::string>& requests,
    const std::vector<std::vector<Entry>>& expected)
{
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    for (size_t i = 0; i < requests.size(); ++i) {
        auto word = requests[i];
        std::vector<Entry> result = idx.GetWordCount(word);

        ASSERT_EQ(result.size(), expected[i].size());
        for (size_t j = 0; j < result.size(); ++j) {
            EXPECT_EQ(result[j], expected[i][j]);
        }
    }
}

// тест из задания
TEST(TestCaseInvertedIndex, TestBasic) {
    const std::vector<std::string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the great bell of the striking clock"
    };
    const std::vector<std::string> requests = {"london", "the"};
    const std::vector<std::vector<Entry>> expected = {
        {
            {0, 1}
        },
        {
                {0, 1}, {1, 3}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestBasic2) {
    const std::vector<std::string> docs = {
        "milk milk milk milk water water world",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino mocha"
    };
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
    const std::vector<std::vector<Entry>> expected = {
        {
            {0, 4}, {1, 1}, {2, 5}
        },
        {
                {0, 2}, {1, 2}, {2, 5}
        },
        {
                {3, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "InvertedIndex.h"
#include "SearchServer.h"

TEST(TestCaseSearchServer, TestSimple) {
    const std::vector<std::string> docs = {
        "milk milk milk milk water water world",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino mocha"
    };
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};

    // Ожидаемый результат для 3 запросов:
    // Запрос "milk": найдется в доках 0, 1, 2. Максимум совпадений (5) в доке 2.
    // Запрос "water": найдется в доках 0, 1, 2. Максимум совпадений (5) в доке 2.
    // Запрос "cappuccino": найдется только в доке 3.
    const std::vector<std::vector<RelativeIndex>> expected = {
        {
            {2, 1.0f}, {0, 0.8f}, {1, 0.2f}
        },
        {
                {2, 1.0f}, {0, 0.4f}, {1, 0.4f}
        },
        {
                {3, 1.0f}
        }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx, 5);
    std::vector<std::vector<RelativeIndex>> result = srv.search(requests);

    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i].size(), expected[i].size());
        for (size_t j = 0; j < result[i].size(); ++j) {
            EXPECT_EQ(result[i][j].doc_id, expected[i][j].doc_id);
            // Так как float может иметь погрешность, проверяем через проверку близости значений
            EXPECT_NEAR(result[i][j].rank, expected[i][j].rank, 0.001f);
        }
    }
}

TEST(TestCaseSearchServer, TestAdvanced) {
    const std::vector<std::string> docs = {
        "milk milk milk milk water water world",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino mocha"
    };

    // Запрос из нескольких слов
    // Запрос с несуществующим словом
    const std::vector<std::string> requests = {"milk water", "sugar"};

    const std::vector<std::vector<RelativeIndex>> expected = {
        {
            {2, 1.0f}, {0, 0.6f} // Документ 1 отсечен лимитом
        },
        {
            // Для "sugar" ожидается пустой результат
        }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx, 2);
    std::vector<std::vector<RelativeIndex>> result = srv.search(requests);

    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        ASSERT_EQ(result[i].size(), expected[i].size());
        for (size_t j = 0; j < result[i].size(); ++j) {
            EXPECT_EQ(result[i][j].doc_id, expected[i][j].doc_id);
            EXPECT_NEAR(result[i][j].rank, expected[i][j].rank, 0.001f);
        }
    }
}