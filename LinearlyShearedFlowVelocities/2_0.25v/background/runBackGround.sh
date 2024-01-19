#!/bin/sh

# Create background mesh
ccmToFoam backgroundMedium.ccm

# Add the cylinder mesh
mergeMeshes . ../floatingBody -overwrite

# Select cellSets for the different zones
topoSet

# Set Boundary Conditions
rm -rf 0
cp -r 0.orig 0

# Use cellSets to write zoneID
setFields -dict system/setFieldsDict_zoneID | tee log.setFields_zoneID
# setFields for alpha.water
setFields -dict system/setFieldsDict_alpha.water | tee log.setFieldsDict_alpha.water
# run solver
decomposePar
mpirun -np 64 overInterDyMFoam  -parallel | tee log.overInterDyMFoam
