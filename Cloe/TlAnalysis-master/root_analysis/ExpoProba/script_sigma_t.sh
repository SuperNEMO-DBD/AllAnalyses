#!/bin/bash


for ((j=0;j<500;j+=100))
do
root -l -b -q draw_expo_proba.cc\($j\)
done
