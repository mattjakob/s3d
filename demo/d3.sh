#!/bin/sh

BIN=../bin
MOD=../model
SCN=../scn

echo "************************************************"
echo "Primitves and Hierarchies"

echo "1) Orthographic View of Sphere Bounding Boxes"
echo "  (type q to quit)"
$BIN/ortho -5 5 < $SCN/spheres.scn

echo "3) Rendering Spheres using Z-Sort"
echo "  (type q to quit)"
$BIN/zsort < $SCN/spheres.scn > s.ppm
$BIN/vw s.ppm 2

/bin/rm -f s.ppm


