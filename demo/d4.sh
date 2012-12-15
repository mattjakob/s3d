#!/bin/sh

#TXT="xedit -bg white -geometry 800x550 "
TXT="echo "

BIN=../bin
MOD=../model
SCN=../scn

echo "************************************************"
echo "Animation of Articulated Object"
echo "1) Scene Description File"
echo "  (click button to quit)"
$TXT $SCN/arm.scn

echo "Animation of Articulated Object"
echo "2) Running 60 Frames"
$BIN/xanim 60 < $SCN/arm.scn



