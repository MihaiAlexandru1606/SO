#!/bin/bash

OUT_DIR=indent
files=$(find ./ | grep "..\.c\|..\.h" | sed 's|^./||')
[ -d $OUT_DIR ] || mkdir $OUT_DIR

for file in $files
do
	indent -nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1 $file -o "$OUT_DIR/$file"
done
