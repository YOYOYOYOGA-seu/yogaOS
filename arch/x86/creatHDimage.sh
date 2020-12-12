#!/bin/bash
rm -f $1m.img
rm -f image/$1m.img
echo "1 



$1
$1m.img"|bximage
mv $1m.img image/disk.img
