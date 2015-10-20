#!/usr/bin/env bash

wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/cyk.zip
wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/sub.zip
wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/inw2.zip
wget https://dl.dropboxusercontent.com/u/908983/sio2pwr/testy/gog.zip

wget https://gist.githubusercontent.com/jereksel/e44795ce3dc44d1b00ab/raw/sprawdzarka.py

unzip cyk.zip
unzip sub.zip
unzip inw2.zip
unzip gog.zip

python3 sprawdzarka.py -p build/bin/cykl -i cyk/in -o cyk/out
test1=$?

python3 sprawdzarka.py -p build/bin/ElGoog -i gog/in -o gog/out
test2=$?

python3 sprawdzarka.py -p build/bin/inwersje -i inw2/in -o inw2/out
test3=$?

python3 sprawdzarka.py -p build/bin/podciag -i sub/in -o sub/out
test4=$?


exit $(($test1+$test2+$test3+$test4))