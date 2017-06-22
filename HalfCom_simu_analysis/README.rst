================================================
SuperNEMO Half Commissioning simulation analysis
================================================
:Authors: G.Oliviéro <goliviero@lpccaen.in2p3.fr>,
:Date:    05/2017

This repository is here to analyze half commissioning files from
simulation.

Goals of the analysis :
-----------------------

- Analyze Co60 source simulation
- Analyze simulated datas with Argon instead of helium in flsimulate
- Compare simulation with raw data from half commissioning (data taking : 02/2017)


Build :
-------

'Activate' falaise environment :
add to your PATH your falaise install dir:

.. code:: sh

   $ export SW_WORK_DIR="YOUR_SOFTWARE_DIR_PATH"
   $ export FALAISE_INSTALL_DIR=${SW_WORK_DIR}/Falaise/install
   $ export PATH=${FALAISE_INSTALL_DIR}/BIN:${PATH}

   $ mkdir build
   $ cd build

   $ cmake \
	  -GNinja \
	  -DFalaise_DIR=$(flquery --cmakedir) \
	  ../trunk

..
