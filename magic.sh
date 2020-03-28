#!/bin/sh
mkdir build
cd build
cmake ../
make
mkdir temp
cp covid19-data.vpk temp/
cd temp/
unzip covid19-data.vpk
cp eboot.bin ../eboot.bin
cd ../
rm -r temp/

for i in $@
do
    echo destroy | nc $i 1338
    curl --ftp-method nocwd -T eboot.bin ftp://$i:1337/ux0:/app/COVIDDATA/
    echo launch COVIDDATA | nc $i 1338
done