#!/bin/bash
# Compilation script for Restaurant Bot

echo "==================================="
echo "  Restaurant Bot - Compilation"
echo "==================================="

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Compile command
echo "Compiling modular restaurant bot..."
g++ -std=c++17 -o restaurant_bot main.cpp common.cpp manual_mode.cpp ai_mode.cpp girdi.cpp -I.

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Compilation successful!${NC}"
    echo ""
    echo "Executable created: restaurant_bot"
    echo "File size: $(ls -lh restaurant_bot | awk '{print $5}')"
    echo ""
    echo "To run the program:"
    echo "  ./restaurant_bot"
    echo ""
    echo "==================================="
else
    echo -e "${RED}✗ Compilation failed!${NC}"
    echo "Please check the error messages above."
    exit 1
fi
