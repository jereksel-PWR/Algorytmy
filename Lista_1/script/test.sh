#!/usr/bin/env bash

wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/mst.zip
wget https://gist.githubusercontent.com/jereksel/e44795ce3dc44d1b00ab/raw/sprawdzarka.py

unzip mst.zip

python3 sprawdzarka.py -p build/kruskal -i mst/in -o mst/out
test1=$?

python3 sprawdzarka.py -p build/prim -i mst/in -o mst/out
test2=$?

exit $(($test1+$test2))