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
$TXT $SCN/rad.scn

echo "2) Rendering using Radiosity "
echo "  (type q to quit)"
$BIN/xrad < $SCN/rad.scn > r.ppm
$BIN/vw r.ppm 2

/bin/rm -f r.ppm


