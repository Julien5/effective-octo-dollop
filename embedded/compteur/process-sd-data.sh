#!/usr/bin/env bash

set -e
# set -x

N=$(find /media/julien/ -iname "*.bin" | wc -l);
if [[ $N -gt 0 ]]; then
    M=$(find sd-data/ -mindepth 1 -maxdepth 1 -type d | wc -l);
    DST=sd-data/$(($M+1));
    mkdir -p $DST/{bin,hex}
    find /media/julien/ -iname "*.bin" -exec mv -v "{}" $DST/bin \;
fi

D=sd-data/$(ls -t sd-data/ | head -1)
if [[ ! -z "$1" ]]; then
    D=$1
fi

if [[ ! -d $D ]]; then
    echo could not find $D
    exit 1;
fi

if [[ ! -f $D/hex/data.csv ]]; then
    mkdir -p $D/hex
    echo convert hex
    find $D/ -iname "*.bin" | sort | while read a; do xxd $a | cut -f2 -d: | cut -b1-40 | tr -d " " | tr -d "\n"; echo; done | tr "[:lower:]" "[:upper:]" > $D/hex/data
    echo copy
    cp $D/hex/data /tmp/irdata
    echo convert csv
    python3 readirdata.py 
    head data.csv
    mv -v data.csv $D/hex/data.csv
fi

cp -v $D/hex/data.csv data.csv
gnuplot readirdata.gnuplot
# xdg-open ir.png 