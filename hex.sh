#!/bin/bash

FILENAME="polar_image_data.txt"
OUTPUT_FILE="hex_colors.txt"

echo "Starting script..."
if [ -f "$FILENAME" ]; then
    echo "Input file found."
else
    echo "Input file not found."
    exit 1
fi

awk -F"Color: #" '{print $2}' $FILENAME > $OUTPUT_FILE

if [ $? -eq 0 ]; then
    echo "awk command executed successfully."
else
    echo "awk command failed."
fi

echo "Script completed."$OUTPUT_FILE
