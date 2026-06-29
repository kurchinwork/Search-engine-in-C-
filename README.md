# I'm Ilya K 
This repository was created for working with the final project files for 
the **"C++ Developer from Scratch"** course on the *SkillBox* platform. 

### The project topic is "Implementing a search system for a company's corporate portal."

The plan is to:
- develop a search engine for the company's corporate portal
  – similar to the Yandex or Google search bar;
- build search indexes;
- work with configuration files;
- write a set of tests to validate the solution;
- write a relevance formula for returning search results.

### Language and tools:
- C
- C++
- CMake
- JSON File

# Launching and preparing the project:
1. It is necessary to properly organize the file structure if the original project structure has been modified.
   The project structure is as follows:
    ```bash 
        SearchEngine 
        |_ config
          |_ config.json
          |_ answers.json
          |_ requests.json
        |_ include
          |_ ConverterJSON.h
          |_ InvertedIndex.h
          |_ SearchServer.h
        |_ resoursces
        |_ src
          |_ main.cpp
          |_ ConverterJSON.cpp
          |_ InvertedIndex.cpp
          |_ SearchServer.cpp
          |_ tests.cpp
    
    ```
2. Before running, ensure the required configuration fields in "config/config.json" are fully populated.

    In the field "files" : [
    
    ]
    
    , list the files to be searched, separated by commas. It is recommended to store these files in the resources folder.

3. To run the project, the following components are required:
   - Cmake 3.20 or later;
   - C++ 20 or later;
   - Build the project. You can build it from the console:
      ```bash
        mkdir build
        cd build
        cmake ..
        cmake --build .
      ```
    If the build fails, I recommend checking the project structure (see above).

5. If problems arise while running the program, you can be confused about its correct operation. To do this, you need to
   run the tests and run their test.cpp.

6. Where are the questions (search queries) entered?
   All search queries are entered into the requests.json file.
   It contains an array of strings, where each string is a separate query that the program should process.

7. Where are the results (results) obtained?
   The program writes the search results to the answers.json file.
   This file is created in the same folder after the search engine completes. For each request from requests.json, a response will be generated: whether a match was found (result: true/false),
   as well as the document IDs and their relevance (rank).


My contact information is in my profile.

Course module repository: 
[Full modules SkillBox Course](https://github.com/kurchinwork/Practical-courses-from-Skillbox)



# Меня зовут Илья К.
Этот репозиторий создан для работы с файлами финального 
проекта курса «Разработчик C++ с нуля» на платформе SkillBox.

Тема проекта: «Реализация системы поиска для корпоративного портала компании».

Планируется состоит в следующем:
- разработать поисковую систему для корпоративного портала компании
 — аналогичную поисковой строке Яндекса или Google;
- создать поисковые индексы;
- работать с конфигурационными файлами;
- написать набор тестов для проверки решения;
- написать формулу релевантности для возврата результатов поиска.
  
Язык и инструменты:
- C
- C++
- CMake
- JSON-файл

# Запуск и подготовка к работе проекта:
1. Необходимо правильно организовать структуру файлов, если изначальная структура проекта была изменена.
Структура проекта следующая:
```bash 
    SearchEngine 
    |_ config
      |_ config.json
      |_ answers.json
      |_ requests.json
    |_ include
      |_ ConverterJSON.h
      |_ InvertedIndex.h
      |_ SearchServer.h
    |_ resoursces
    |_ src
      |_ main.cpp
      |_ ConverterJSON.cpp
      |_ InvertedIndex.cpp
      |_ SearchServer.cpp
      |_ tests.cpp

```

2. Перед запуском, необходимо убедиться что обязательные поля конфигурации полностью заполненные "config/config.json".
   
    В поле "files": [

     ]   
    
    , через запятую перечисляются файлы по которым необходимо запустить поиск, эти файлы рекомендуется хранить в папке resources.

3. Для того чтобы запустить проект необходимы следующие компоненты:
   - Cmake не ниже версии 3.20;
   - С++ не ниже версии 20;
   - Выполнить сборку проекта, выполнить сборку можно через консоль:
   ```bash
     mkdir build
     cd build
     cmake ..
     cmake --build .
   ```
   Если сборка не выполнилась, рекомендую проверить структуру проекта (см. выше).
     
5. При возникновении проблем во время работы программы, можно убиться в правильности её работы, для этого необходимо
   запустить тесты и запустить их test.cpp.

6. Куда вносятся вопросы (запросы для поиска):
   Все поисковые запросы вносятся в файл requests.json.
   Внутри него находится массив строк, где каждая строка — это отдельный запрос, который программа должна обработать.

7. Где получается найденное (результат работы):
   Результаты поиска программа записывает в файл answers.json.
   Этот файл создается в той же папке после завершения работы поисковика. Внутри него для 
   каждого запроса из requests.json будет сгенерирован ответ: нашлись ли совпадения (result: true/false), 
   а также id документов и их релевантность (rank).
  
Моя контактная информация указана в моем профиле.

Репозиторий модуля всего курса: 
[Все модули пройденного курса](https://github.com/kurchinwork/Practical-courses-from-Skillbox).
