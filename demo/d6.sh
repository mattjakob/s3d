#!/bin/sh

#set TXT = "xedit -bg white -geometry 800x500 "
TXT="echo "

BIN=../bin
MOD=../model
SCN=../scn

echo "************************************************"
echo "Radiosity with Polygonal Model"
echo "1) Scene Description File"
echo "  (click button to quit)"
$TXT $SCN/whitted.scn

echo "2) Rendering using Ray Tracing "
echo "  (type q to quit)"
$BIN/xray < $SCN/whitted.scn > w.ppm
$BIN/vw w.ppm 2

/bin/rm -f w.ppm


