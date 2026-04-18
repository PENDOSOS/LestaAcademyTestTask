#!/bin/bash

PROJECT_ROOT="LestaAcademyTestTask"

declare -a MODULE_NAMES=("Player" "Controller")

echo "--------------------------------"
echo "        Coverage reports        "
echo "--------------------------------"

for MODULE_NAME in "${MODULE_NAMES[@]}"; do  

    BUILD_DIRECTORY="./build/tests/${MODULE_NAME}"
    INFO_FILE="./${BUILD_DIRECTORY}/coverage.info"

    lcov --capture \
        --directory "$BUILD_DIRECTORY" \
        --output-file "$INFO_FILE" \
        --quiet \
        --rc lcov_branch_coverage=1 \
        2>/dev/null
    lcov --extract "$INFO_FILE" "*/${PROJECT_ROOT}/${PROJECT_ROOT}/${MODULE_NAME}.*" -o "${INFO_FILE}-tmp" \
        --quiet
    mv "$INFO_FILE-tmp" "$INFO_FILE"

    echo "Coverage report: $MODULE_NAME"
    echo "--------------------------------"
    lcov --summary "$INFO_FILE" 2>/dev/null | grep -E "lines|functions"
    echo "--------------------------------"
done