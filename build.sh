#!/bin/bash

if [ -d "build" ]; then
    cd build
else
    mkdir "build"
    cd build
fi

# пока захардкожен флаг сборки тестов
# TODO: добавить парсинг аргументов коммандной строки
cmake -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug ..

if [[ $? -eq 0 ]]
then
	cmake --build .
fi

