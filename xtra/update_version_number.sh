#!/bin/bash

VERSION="015"

for infile in ../*.c; do

    # outfile="${infile%.in}.bak"
    # cp $infile $outfile
    sed -i '' "s/VERSION_.../VERSION_$VERSION/" $infile  


done


for infile in ../*.h; do

    # outfile="${infile%.in}.bak"
    # cp $infile $outfile
    sed -i '' "s/VERSION_.../VERSION_$VERSION/" $infile  


done
