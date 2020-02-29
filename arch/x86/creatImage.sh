#!/bin/bash

if [ ! -d "/mnt/myOSfs" ] ; then
sudo mkdir /mnt/myOSfs
fi
sudo mount -o loop image/a.img /mnt/myOSfs
sudo cp output/loader.bin /mnt/myOSfs
sudo cp output/kernel.bin /mnt/myOSfs
sudo umount /mnt/myOSfs


