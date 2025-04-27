#convert -size "$W"x"$H" xc:none -draw "roundrectangle 0,0,$W,$H,$R,$R" $MASK
#convert $SRC -matte $MASK -compose DstIn -composite $DST
# brew install imagemagick
magick  -size 1680x1050 xc:none -draw "roundrectangle 0,0,1680,1050,35,35" ./png/mask.png
magick  ./png/fr_0003.png -alpha Set ./png/mask.png  -compose DstIn -composite ./png/picture_with_rounded_corners.png 
