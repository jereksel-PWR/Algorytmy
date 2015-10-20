#!/usr/bin/env bash

wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/mon1.zip
wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/mon2.zip
wget https://gist.githubusercontent.com/jereksel/e44795ce3dc44d1b00ab/raw/sprawdzarka.py

unzip mon1.zip
unzip mon2.zip

python3 sprawdzarka.py -p build/mon1 -i mon1/in -o mon1/out
test1=$?

python3 sprawdzarka.py -p build/mon2easy -i mon2/in -o mon2/out
test2=$?

rm -rf mon2/in/mon216.in
rm -rf mon2/in/mon217.in
rm -rf mon2/in/mon218.in
rm -rf mon2/in/mon219.in
rm -rf mon2/in/mon220.in
rm -rf mon2/in/mon221.in
rm -rf mon2/in/mon222.in
rm -rf mon2/in/mon223.in
rm -rf mon2/in/mon224.in
rm -rf mon2/in/mon229.in

python3 sprawdzarka.py -p build/mon2 -i mon2/in -o mon2/out
test3=$?

exit $(($test1+$test2+$test3))