#!/bin/bash

#set -x

OUT="hex_colors.txt"

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <input_file> [<output_file>]"
    echo "    Input file should be of the form: "
    echo "    Position (r, theta): (#, #), Color: #XXXXXX"
    exit 1
fi

FILENAME=$1
OUTPUT_FILE=${2:-${OUT}}

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
