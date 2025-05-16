#convert -size "$W"x"$H" xc:none -draw "roundrectangle 0,0,$W,$H,$R,$R" $MASK
#convert $SRC -matte $MASK -compose DstIn -composite $DST
# brew install imagemagick
#
# compose DstIn multiplies alpha channels, suitable when both source and mask have alpha.
# compose copy-opacity is best when your mask is grayscale and you want to use it as an alpha mask.
# alpha on ensures the presence of an alpha channel but does not modify existing transparency.
#
magick  -size 1050x1050 xc:none -draw "roundrectangle 0,0,1050,1050,35,35" ../png/mask.png
for img in ../png/*.png; do
  magick "$img" ../png/mask.png -alpha on -compose copy-opacity -composite "../png/$(basename "$img")"
done
rm ../png/mask.png
