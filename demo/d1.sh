#!/bin/sh

bin=../bin
mod=../model

echo "************************************************"
echo "Rotation Surface and Rendering with Flat Shading"

echo "1) Profile Curve"
echo "  (type q to quit)"
$bin/ple $mod/curve.pts

# generating rotation surface
$bin/rsurf 18 < $mod/curve.pts > cyl.tl

# creating scene file
echo "scene {" > hdr.scn
echo " camera = view { from = {0, 0, -2.5}, up = {0, 1, 0}, imgw = 640, imgh = 480}," >> hdr.scn
echo " light = dist_light {direction = {0, 0, -1} }," >> hdr.scn
echo " object = polyobj { shape =" >> hdr.scn
cat hdr.scn cyl.tl > cyl.scn
echo "}};" >> cyl.scn

echo  "2) Plot of Rotation Surface"
echo "  (type q to quit)"
$bin/splot < cyl.scn

echo  "3) Rendering Flat Shaded Image"
echo "  (type q to quit)"
$bin/zflat < cyl.scn > cyl.ppm
$bin/vw cyl.ppm

/bin/rm -f cyl.ppm cyl.scn hdr.scn cyl.tl 



