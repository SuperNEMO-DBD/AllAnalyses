#!/usr/bin/python3.6
# -*-coding:Utf-8 -*

# Python script to reshape calorimeter.map HV text files in something understandable by root

import os
import sys
import pandas as pd
import numpy as np
from math import *

HighVoltages = np.loadtxt(fname="calorimeter_fr.txt",comments='#',delimiter='  ',dtype=str)

if sys.argv[1] == 'fr':
    wall = 0
elif sys.argv[1] == 'it':
    wall = 1
else: print("Unknown calorimeter wall type!")



with open('HV.txt', mode='w') as file_object:
    counter=0
    for col in range(0,20):
        for row in range(0,13):
            HV = ', '.join(HighVoltages[[counter],[4]])
            print(wall,col,row,HV, file=file_object)
            counter+=1
