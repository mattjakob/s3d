#!/bin/sh

#TXT="xedit -bg white -geometry 800x400 "
TXT="echo "

BIN=../bin
MOD=../model
SCN=../scn


echo "************************************************"
echo "CSG Object with Ray Casting Render "
echo "1) CSG Expression of Model"
echo "  (click button to quit) "
echo " (s{ 0 0 0 1} \ s{ 1 1 -1 1})" > m.csg
$TXT m.csg

cat m.csg | $BIN/xcsg > m.scn

echo "scene {" > hdr.scn
echo " camera = view { from = {0, 0, -2}, up = {0, 1, 0}}," >> hdr.scn
echo " light = dist_light {direction = {0, 1, -1} }, " >> hdr.scn
echo " object = csgobj {  shape =" >> hdr.scn
cat hdr.scn m.scn > csg.scn
echo " } }; " >> csg.scn

echo  "2) Scene Description of with Object"
echo "  (click button to quit) "
$TXT $SCN/csg.scn

echo  "3) Ray Casting Scene "
echo "  (type q to quit) "
$BIN/rt < csg.scn > csg.ppm
$BIN/vw csg.ppm 2

/bin/rm -f m.csg csg.scn hdr.scn m.scn csg.ppm



