#!/bin/bash


for infile in ./*.c; do

    # outfile="${infile%.in}.bak"
    # cp $infile $outfile
    sed -i '' "s/VERSION_008/VERSION_009/" $infile  


done


for infile in ./*.h; do

    # outfile="${infile%.in}.bak"
    # cp $infile $outfile
    sed -i '' "s/VERSION_008/VERSION_009/" $infile  


done
