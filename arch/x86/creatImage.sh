#!/bin/bash

if [ ! -d "/mnt/myOSfs" ] ; then
sudo mkdir /mnt/myOSfs
fi
sudo mount -o loop $1/a.img /mnt/myOSfs
sudo cp $2/loader.bin /mnt/myOSfs
sudo cp $2/kernel.bin /mnt/myOSfs
sudo umount /mnt/myOSfs


