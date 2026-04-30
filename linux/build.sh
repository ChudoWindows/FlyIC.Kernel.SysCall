
#!/bin/bash

set -e

echo "Сборка программы..."
echo ""

cd tmp
cmake --build .

echo ""
echo "Для выхода нажмите Enter..."
read
