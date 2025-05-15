#!/bin/bash
set -e

echo "[INFO] Cleaning build directory..."
rm -rf build/
mkdir -p build
cd build

echo "[INFO] Regenerating Xcode project with CMake..."
cmake -G Xcode ..

cmake --build . --config Debug

cd ..

# Check if user passed --no-open
if [[ "$1" != "--no-open" ]]; then
  echo "[INFO] Opening Xcode project..."
  open build/ForecastEngine.xcodeproj
else
  echo "[INFO] Skipped opening Xcode."
fi
