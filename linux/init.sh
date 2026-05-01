#!/bin/bash

set -e

echo "Введите тип сборки: "
read build_type

if [ "$build_type" != "Debug" ] && [ "$build_type" != "Release" ]; then
    echo "Не верный тип сборки!"
    echo "Будет использован автоматический выбор"
    build_type="Debug"
fi

echo ""
echo "Тип сборки: $build_type"

echo ""
echo "Генерация набора для сборки, требуется установленный clang/llvm"
echo ""

mkdir -p ../lib
mkdir -p tmp
cd tmp
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..

echo ""
echo "Для выхода нажмите Enter..."
read
