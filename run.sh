#!/bin/bash

# Set the build directory (you can change this to whatever you prefer)
BUILD_DIR="build"

# Check if the build directory exists, if not, create it
if [ ! -d "$BUILD_DIR" ]; then
  echo "Build directory doesn't exist, creating it..."
  mkdir "$BUILD_DIR"
fi

# Change to the build directory
cd "$BUILD_DIR"

# Function to display usage
usage() {
  echo "Usage: $0 --day <day_number> [--benchmark]"
  echo "  --day <day_number>    Specify the day (1-25)"
  echo "  --benchmark           Run benchmarks after execution"
  exit 1
}

# Default values
BENCHMARK=false
DAY=0

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
  case "$1" in
    --day)
      DAY=$2
      shift 2
      ;;
    --benchmark)
      BENCHMARK=true
      shift
      ;;
    *)
      usage
      ;;
  esac
done

# Check if --day is provided and valid
if [ "$DAY" -eq 0 ]; then
  echo "Error: You must specify a day using --day <day_number>"
  usage
fi

if [ "$DAY" -lt 1 ] || [ "$DAY" -gt 25 ]; then
  echo "Error: Invalid day number. It must be between 1 and 25."
  usage
fi

# Go back to the root directory to check for changes
cd ..

# List all source files
SOURCE_FILES=$(find AoC25 -type f \( -name "*.cpp" -o -name "*.hpp" \))

# Check if any source files have changed since the last build
if [ -f "$BUILD_DIR/runAoC" ]; then
  echo "Checking for changes in source files..."

  # Get the timestamp of the last build and compare it with the source files' timestamps
  LAST_BUILD_TIMESTAMP=$(stat -c %Y "$BUILD_DIR/runAoC")
  NEEDS_REBUILD=false

  for file in $SOURCE_FILES; do
    FILE_TIMESTAMP=$(stat -c %Y "$file")
    if [ "$FILE_TIMESTAMP" -gt "$LAST_BUILD_TIMESTAMP" ]; then
      NEEDS_REBUILD=true
      break
    fi
  done

  if [ "$NEEDS_REBUILD" = true ]; then
    echo "Source files have changed, rebuilding..."
    cd "$BUILD_DIR"
    make
  else
    echo "No changes detected, skipping rebuild."
  fi
else
  # If binary doesn't exist, build it
  echo "Binary doesn't exist, building the project..."
  cd "$BUILD_DIR"
  cmake ..
  make
fi

# Run the code for the specified day
echo "Running solution for Day $DAY..."
echo
RES=$(AoC25/runAoC --day "$DAY")

FILTER=0
# Run the benchmark if the --benchmark flag is set
if [ "$BENCHMARK" = true ]; then
  echo "Running benchmarks..."
  echo
  BENCHMARK_FILTER="day$DAY"
  AoC25/benchmarks --benchmark_filter="$BENCHMARK_FILTER"
  echo
  echo
fi

# Print the result
echo $RES
