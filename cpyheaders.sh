#!/bin/bash

destdir="build/include/"
mkdir -p $destdir

cd src

for file in $(find -name '*.h' -print) ; do 
	cp --parents $file "../"$destdir
done
