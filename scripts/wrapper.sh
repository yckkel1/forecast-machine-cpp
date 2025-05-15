#!/bin/bash
set -e

EXECUTABLE="./build/Debug/forecast_engine"

if [ ! -x "$EXECUTABLE" ]; then
  echo "[ERROR] Executable not found or not built: $EXECUTABLE"
  echo "[HINT] Run ./scripts/rebuild.sh first."
  exit 1
fi

"$EXECUTABLE" "$@"

