#!/bin/bash

active_dir="src/structures/activeStructures"
passive_dir="src/structures/passiveStructures"
output_file="data/structuresList.json"

echo "{" > "$output_file"
echo '  "activeStructures": [' >> "$output_file"

first=true
for file in "$active_dir"/*.cpp; do
  filename=$(basename "$file" .cpp)
  if [ "$first" = true ]; then
    echo "    \"$filename\"" >> "$output_file"
    first=false
  else
    echo "    ,\"$filename\"" >> "$output_file"
  fi
done

echo '  ],' >> "$output_file"
echo '  "passiveStructures": [' >> "$output_file"

first=true
for file in "$passive_dir"/*.cpp; do
  filename=$(basename "$file" .cpp)
  if [ "$first" = true ]; then
    echo "    \"$filename\"" >> "$output_file"
    first=false
  else
    echo "    ,\"$filename\"" >> "$output_file"
  fi
done

echo '  ]' >> "$output_file"
echo "}" >> "$output_file"

echo "File created: $output_file"
