# EventGenerators

## All these commands need to be ran on the FNAL gpvm's

## To build / link all the event generators + Nuisance
git clone https://github.com/afropapp13/BuildEventGenerators.git;

cd BuildEventGenerators;

./build_generators.sh;

## To test that the build was successful by producing a few events
cd jobcards;

./run_all.sh;

## To setup the enviroment, source the setup script every time that you connect to the gpvm machines

source setup_generators.sh


# Once you have all of the Flat files produced under mySamples directory


## Make sure to have .flat.root files in your mySamples directory

## To make them, go over to https://github.com/maxdubnowski/BuildEventGenerators.git and follow this Repo 

## Move the .flat.root files to the mySamples directory


## Run the Flat tree analyzer which loops through the .flat files, makes all of the plots, and converts to .root file for each of the event generators,

root -l script_LoopGenerators.cxx



## Plot the 1D histograms

root -l GeneratorOverlay.cpp


## Plot the 2D histograms

root -l GeneratorOverlay2D.cpp
