#!/bin/bash

BUILD_DIR="build/tests"

echo "---------Player tests---------"
./${BUILD_DIR}/Player/player_tests
echo ""
echo "-------Controller tests-------"
./${BUILD_DIR}/Controller/controller_tests

echo ""
./generate-coverage-info.sh