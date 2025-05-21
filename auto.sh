#!/usr/bin/bash
read  -p "Enter The filename: " filename
if [ -e "$filename" ]; then 
echo "File exist"
else 
echo "Such file does not exist .so creating.."
touch "$filename"
chmod +x "$filename"
fi
nano "$filename"
