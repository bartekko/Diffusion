#!/bin/bash

###
DENSITY=$1
STEPS=80000
PARTICLES=50000
###

./diffuse23 $DENSITY $STEPS $PARTICLES > intermresults/$DENSITY.txt

FILENAME="$(head -n 1 intermresults/$DENSITY.txt)"

sed -i 1,1d intermresults/$DENSITY.txt

cp intermresults/$DENSITY.txt fresults/$FILENAME.txt

echo $FILENAME >> fresults/truedensities.txt

