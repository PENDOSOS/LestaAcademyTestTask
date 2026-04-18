#!/bin/bash

BUILD_DIR="build/tests"

./${BUILD_DIR}/Player/player_tests
echo ""
./${BUILD_DIR}/Controller/controller_tests

echo ""
./generate-coverage-info.sh