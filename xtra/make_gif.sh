#convert -size "$W"x"$H" xc:none -draw "roundrectangle 0,0,$W,$H,$R,$R" $MASK
#convert $SRC -matte $MASK -compose DstIn -composite $DST
# brew install imagemagick
magick -delay 12 -loop 1 ../png/*.png ../kapla.gif
