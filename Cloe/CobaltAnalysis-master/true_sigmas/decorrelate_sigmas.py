#!/usr/bin/python3.6
# -*-coding:Utf-8 -*

import os
import sys
import pandas as pd
import numpy as np
from math import *

pd.set_option('display.max_rows', None)

def triple_coincidence(sigmas,energies):
    sig01 = sigmas.iloc[0]
    sig02 = sigmas.iloc[1]
    sig12 = sigmas.iloc[2]

    c0 = 1./energies.iloc[0]
    c1 = 1./energies.iloc[1]
    c2 = 1./energies.iloc[2]


    if (c0*sig01**2+c0*sig02**2 > c0*sig12**2):
        sig_indiv0 = sqrt((1/2)*(c0*sig01**2+c0*sig02**2-c0*sig12**2))
        return sig_indiv0


def variances_pair(sigmas,numbers):
    sig0 = sigmas.iloc[0]
    sig1 = sigmas.iloc[1]
    sig2 = sigmas.iloc[2]

    n0 = numbers.iloc[0]
    n1 = numbers.iloc[1]
    n2 = numbers.iloc[2]

    var = [2*((sig0**4)/(n0-1)),2*((sig1**4)/(n1-1)),2*((sig2**4)/(n2-1))]

    return var

def variances_indiv(variances,energies):
    var01 = variances[0]
    var02 = variances[1]
    var12 = variances[2]

    c0 = 1./energies.iloc[0]
    c1 = 1./energies.iloc[1]
    c2 = 1./energies.iloc[2]

    var0 = c0/4*(var01+var02+var12)

    return var0



try:
    SigmaFile = np.loadtxt(fname="sigma_files/%s/sigma_%s_%s.txt" % tuple(sys.argv[1:4]))
    EnergyFile = np.loadtxt(fname="energy_files/%s/energy_%s_%s.txt" % tuple(sys.argv[1:4]))

    if SigmaFile.size: #garantit que le fichier ait une taille non nulle
        if SigmaFile.ndim>1: #garantit qu'il y ait plus d'une ligne dans le fichier (sinon ça fait planter EnergyFile[:,3])

            df = pd.DataFrame({
                'col': SigmaFile[:,0],
                'row': SigmaFile[:,1],
                'counts': SigmaFile[:,2],
                'sigma': SigmaFile[:,3],
                'energy': EnergyFile[:,3],
            })

            df['col'] = df['col'].astype(int)
            df['row'] = df['row'].astype(int)
            df['counts'] = df['counts'].astype(int)

            sorted_data = df.sort_values(by=['counts'], ascending=False)


            ## on forme des groupes de (1+2) PMs : celui du fichier qu'on vient d'ouvrir (0), et les deux PMs
            ## qui ont le plus de stat en coincidence avec le premier (1 et 2)
            for i in range(0,df['col'].size,2):
                ## on garanti que le dans le fichier qu'on vient d'ouvrir, il y ait bien de quoi
                ## faire des paires de PMs jusqu'au bout du fichier
                if (i+1)<df['col'].size:


                    ## on prend le PM 1, on ouvre son fichier de coincidences correspondant, et on
                    ## va chercher la ligne qui correspond au PM 2, pour avoir sigma12

                    second_counts = (sys.argv[1],sorted_data['col'].iloc[i],sorted_data['row'].iloc[i]) ## tuple

                    SigmaFile2 = np.loadtxt(fname="sigma_files/%s/sigma_%i_%i.txt" % second_counts)
                    EnergyFile2 = np.loadtxt(fname="energy_files/%s/energy_%i_%i.txt" % second_counts)

                    df2 = pd.DataFrame({
                        'col': SigmaFile2[:,0],
                        'row': SigmaFile2[:,1],
                        'counts': SigmaFile2[:,2],
                        'sigma': SigmaFile2[:,3],
                        'energy': EnergyFile2[:,3],
                    })


                    first_counts = df2[(df2.col == int(sys.argv[2])) & (df2.row == int(sys.argv[3]))]
                    third_counts = df2[(df2.col == sorted_data['col'].iloc[i+1]) & (df2.row == sorted_data['row'].iloc[i+1])]

                    if (third_counts.empty==False) & (first_counts.empty==False):

                        ## sigma01 et sigma02 sont trouvés avec le fichier SigmaFile (avec sorted_data)
                        ## sigma12 est trouvé avec SigmaFile2


                        counts01 = sorted_data['counts'].iloc[i]
                        counts02 = sorted_data['counts'].iloc[i+1]
                        counts12 = third_counts['counts'].iloc[0]## a changer

                        sigma01 = sorted_data['sigma'].iloc[i]
                        sigma02 = sorted_data['sigma'].iloc[i+1]
                        sigma12 = third_counts['sigma'].iloc[0]## a changer


                        energy0 = first_counts['energy'].iloc[0]## a changer
                        energy1 = sorted_data['energy'].iloc[i]
                        energy2 = sorted_data['energy'].iloc[i+1]

                        first = pd.DataFrame({
                            'counts': [counts01,counts02,counts12],
                            'sigma': [sigma01,sigma02,sigma12],
                            'energy': [energy0,energy1,energy2]
                        })


                        true_sigmas = triple_coincidence(first['sigma'],first['energy'])
                        var_pair = variances_pair(first['sigma'],first['counts'])
                        var_indiv = variances_indiv(var_pair,first['energy'])


                        if true_sigmas is not None:
                            x0 = np.array([
                                (int(sys.argv[2]),int(sys.argv[3]),true_sigmas,var_indiv)
                            ])


                        with open('true_sigmas.txt', mode='a') as file_object:
                            print(x0, file=file_object)

    else:
        print("File is Empty!!!")

except IOError:
    print("File does not exist!!!")
