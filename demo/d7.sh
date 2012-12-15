#!/bin/sh

BIN=../bin
MOD=../model
SCN=../scn
DEM=../demo
PIC=../pic

cd $PIC

echo "************************************************"
echo "Mapping Examples"

echo "1) Rendering Texture Mapping "
echo "(type q to quit)"
$BIN/xmap < $SCN/tmaps.scn > $DEM/t.ppm
$BIN/vw $DEM/t.ppm 2

echo "2) Rendering Bump Mapping "
echo "(type q to quit)"
$BIN/xmap < $SCN/bump.scn > $DEM/t.ppm
$BIN/vw $DEM/t.ppm 2

echo "3) Rendering Environment Mapping "
echo "(type q to quit)"
$BIN/xmap < $SCN/env.scn > $DEM/t.ppm
$BIN/vw $DEM/t.ppm 2

echo "4) Rendering Light Mapping "
echo "(type q to quit)"
$BIN/xmap < $SCN/slide.scn > $DEM/t.ppm
$BIN/vw $DEM/t.ppm 2


cd $DEM
/bin/rm -f t.ppm


