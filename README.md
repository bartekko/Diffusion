# Diffusion
A program which simulates particles in a lattice

# Introduction
in the runone.sh file, choose appropriate values for the number of steps and number of particles to be simulated (likely much smaller than default if you're in any sort of hurry)
then run the following:  
make  
python f.py  
doall.sh  
gnuplot plot.gnu  

The end result should look similar to the included ans.png

# More information

By default, f.py creates a densities.txt file with 99 values ranging from 0.01 to 0.99. 
If you need more data points, feel free to modify the densities.txt file with any number of separate densities for which to run the simulatrion.
Keep in mind that because of a design limitation, if you choose to simulate a low number of particles, then putting in a high number of data points will cause them to alias to the same density.

This is because the simulation simulates a square lattice where the set number of particles takes up density part of the whole.
For an in-depth explanation for why this may cause problems, refer to the create_state function in diffuse23.cpp

# dependencies
g++  
boost  
gnuplot  
python 3  
gnu parallel  
bash  
if you're running the latest version of ubuntu, you may be missing boost, gnu parallel, and gnuplot.
Install them with this command:

sudo apt install libboost-all-dev parallel gnuplot

If you're running other versions of linux you probably already know what you're doing
If you're running windows, I'm sorry...
