//
//  RadonWeight.cpp
//
//  Created by James Mott on 09/10/12.
//
//  This module is intended to provide the appropriate weighting to take into account the fact that 
//  the distribtuion of radon in the detector is not uniform in reality, but is modelled this way in 
//  the MC.  We calculate this weighting using activities for each phase, side, sector and layer 
//  provided by Vera.

//  This module has updated values for sectors 6, 7 & 8 (selenium foils) using the SWire and SFoil measurements
//  made by James Mott.  All other values are those provided by Vera.

//  We know that the number of expected events from a given wire (defined by side, sector and 
//  layer), spread over phases 1 & 2 is given by:

//  N_exp = (efficiency_P1 * activity_P1 * time_P1) + (efficiency_P2 * activity_P2 * time_P2)

//  Now efficiency_P1 = N_P1 / (Geom_1 * N_Gen_P1) where Geom_1 is a geometric factor
//  corresponding to the number of generated events assigned to that wire and N_Gen_P1 is the proportion
//  of generated events assigned to phase 1.

//  We know that events are distributed according to run time, so N_Gen_P1 = (time_P1/total_time) * N_Gen_Total

//  Vera's definitions of activity are such that if you scaled up the wire activity, then you would get
//  her activity as the total MC activity.  Therefore activity_P1 = activity_P1_Vera * Geom_1.

//  Substituting these values we get:

//  N_exp = (N_P1 * activity_P1_Vera)*(total_time/N_Gen_Total) + (N_P2 * activity_P2_Vera)*(total_time/N_Gen_Total)

//  However, the our measured radon activity may significantly differ from Vera's and we want it to be easy
//  to quantify our SWire activity.  Therefore we divide by the total activity of Vera's map and then scale 
//  to the total activity that we have meaured:

//  N_exp = (N_P1 * activity_P1_Vera/total_activity_P1_Vera)*(activity_SWire_P1*total_time/N_Gen_Total) + 
//          (N_P2 * activity_P2_Vera/total_activity_P2_Vera)*(activity_SWire_P2*total_time/N_Gen_Total)

//  Therefore for phase 1 all wire are weighted by activity_P1_Vera/total_activity_P1_Vera and the histogram
//  must be scaled by (activity_SWire_P1*total_time/N_Gen_Total)

//  Finally, note that if not all runs in the MC are accepted, then N_Gen_Total must be scaled accordingly

//  15/05/2013 - Stefano Torre
//  I have modified the activities of the wires in L0 measured in the sectors containing the Mo100
//  In Sector 10 and 14 the activity in sector 11 and 15 respectively is used as the measurement was 
//  affected by a bug in the description of the foil geometry in these sectors

#include <iostream>
#include "NemoUtils/RadonWeight.h"
#include "Hereward/DataProcPipeline/AbsEnv.h"

RadonWeight::RadonWeight() {

  WirePosition wire;
  Activity rn_act_P1, rn_act_P2, bi210_act_P1, bi210_act_P2;    

  // ACTIVITIES ARE HARD-CODED HERE, BUT SHOULD PROBABLY BE ADDED TO A DATABASE AT AN OPPORTUNE MOMENT!

  // SET RADON ACTIVITIES FOR PHASE 1
  wire = WirePosition(0,0,0);  rn_act_P1 = Activity(797.273254,9.14092731);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,0);  rn_act_P1 = Activity(438.18,34.95);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,0);  rn_act_P1 = Activity(400.94,38.64);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,0);  rn_act_P1 = Activity(516.17,44.33);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,0);  rn_act_P1 = Activity(444.25,42.27);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,0);  rn_act_P1 = Activity(623.71,36.01);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,0);  rn_act_P1 = Activity(512.70,59.6);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,0);  rn_act_P1 = Activity(551.04,57.2);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,0);  rn_act_P1 = Activity(532.24,85.2);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,0);  rn_act_P1 = Activity(742.698059,8.36201);     add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,0); rn_act_P1 = Activity(491.10,36.01);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,0); rn_act_P1 = Activity(551.07,38.56);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,0); rn_act_P1 = Activity(591.73,33.24);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,0); rn_act_P1 = Activity(579.72,32.46);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,0); rn_act_P1 = Activity(471.27,29.16);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,0); rn_act_P1 = Activity(514.76,31.95);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,0); rn_act_P1 = Activity(310.71,37.21);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,0); rn_act_P1 = Activity(794.949829,8.65698147);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,0); rn_act_P1 = Activity(776.045898,8.5668869);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,0); rn_act_P1 = Activity(751.687805,8.74046612);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,1);  rn_act_P1 = Activity(840.80957,8.63152313);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,1);  rn_act_P1 = Activity(810.11322,8.25786781);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,1);  rn_act_P1 = Activity(818.884583,8.33732128);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,1);  rn_act_P1 = Activity(827.080078,8.41291714);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,1);  rn_act_P1 = Activity(786.067017,8.18287182);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,1);  rn_act_P1 = Activity(824.660278,8.32947731);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,1);  rn_act_P1 = Activity(798.88501,8.04904079);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,1);  rn_act_P1 = Activity(779.796387,8.07180405);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,1);  rn_act_P1 = Activity(810.454529,8.26349354);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,1);  rn_act_P1 = Activity(808.541382,8.22307014);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,1); rn_act_P1 = Activity(777.664124,8.12140369);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,1); rn_act_P1 = Activity(791.039307,8.23151207);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,1); rn_act_P1 = Activity(847.640686,8.70348454);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,1); rn_act_P1 = Activity(774.930481,8.17666626);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,1); rn_act_P1 = Activity(792.373291,8.16359329);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,1); rn_act_P1 = Activity(835.090698,8.41467953);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,1); rn_act_P1 = Activity(834.789673,8.39207172);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,1); rn_act_P1 = Activity(847.572876,8.53309345);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,1); rn_act_P1 = Activity(798.820312,8.16015339);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,1); rn_act_P1 = Activity(829.14032,8.52747059);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,2);  rn_act_P1 = Activity(808.750183,7.88808823);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,2);  rn_act_P1 = Activity(822.401978,7.8006258);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,2);  rn_act_P1 = Activity(793.446899,7.6626668);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,2);  rn_act_P1 = Activity(788.049377,7.676332);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,2);  rn_act_P1 = Activity(778.647827,7.68456507);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,2);  rn_act_P1 = Activity(802.838684,7.64435005);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,2);  rn_act_P1 = Activity(753.799011,7.26352882);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,2);  rn_act_P1 = Activity(777.202515,7.49147797);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,2);  rn_act_P1 = Activity(775.772827,7.46522188);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,2);  rn_act_P1 = Activity(774.67041,7.47436714);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,2); rn_act_P1 = Activity(755.189087,7.46870518);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,2); rn_act_P1 = Activity(806.663574,7.78232622);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,2); rn_act_P1 = Activity(817.305176,7.95753622);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,2); rn_act_P1 = Activity(759.07312,7.62704611);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,2); rn_act_P1 = Activity(806.137512,7.77652693);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,2); rn_act_P1 = Activity(841.318726,7.91831493);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,2); rn_act_P1 = Activity(895.258423,8.19683838);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,2); rn_act_P1 = Activity(864.611389,7.94795084);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,2); rn_act_P1 = Activity(798.245117,7.63390398);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,2); rn_act_P1 = Activity(781.359192,7.62637377);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,3);  rn_act_P1 = Activity(1172.51257,10.3167105);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,3);  rn_act_P1 = Activity(1182.94238,10.1336803);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,3);  rn_act_P1 = Activity(1180.38452,10.2056503);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,3);  rn_act_P1 = Activity(1158.01013,10.0932102);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,3);  rn_act_P1 = Activity(1060.27686,9.66635323);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,3);  rn_act_P1 = Activity(1114.18323,9.77618504);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,3);  rn_act_P1 = Activity(1108.99866,9.56950474);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,3);  rn_act_P1 = Activity(1093.71216,9.73733044);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,3);  rn_act_P1 = Activity(1082.03381,9.69500256);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,3);  rn_act_P1 = Activity(1132.65784,9.84417534);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,3); rn_act_P1 = Activity(1118.76611,9.99786854);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,3); rn_act_P1 = Activity(1111.75293,10.0439796);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,3); rn_act_P1 = Activity(1129.81738,10.5874004);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,3); rn_act_P1 = Activity(1041.03552,10.0384102);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,3); rn_act_P1 = Activity(1115.32373,9.93543053);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,3); rn_act_P1 = Activity(1185.79871,10.25947);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,3); rn_act_P1 = Activity(1320.11536,10.8981199);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,3); rn_act_P1 = Activity(1240.63953,10.7382097);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,3); rn_act_P1 = Activity(1111.02173,9.84307861);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,3); rn_act_P1 = Activity(1178.13391,10.3269701);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,4);  rn_act_P1 = Activity(1997.66699,16.1676292);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,4);  rn_act_P1 = Activity(2028.80896,15.6731396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,4);  rn_act_P1 = Activity(1931.80396,15.3700705);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,4);  rn_act_P1 = Activity(1912.69104,15.3974104);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,4);  rn_act_P1 = Activity(1797.88,14.9274998);     add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,4);  rn_act_P1 = Activity(1710.54895,14.4495497);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,4);  rn_act_P1 = Activity(1943.47302,15.0458002);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,4);  rn_act_P1 = Activity(2024.745,15.5740404);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,4);  rn_act_P1 = Activity(1805.53894,14.7000904);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,4);  rn_act_P1 = Activity(1998.672,15.5117702);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,4); rn_act_P1 = Activity(1950.11096,15.5526896);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,4); rn_act_P1 = Activity(1987.36597,15.7593498);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,4); rn_act_P1 = Activity(1929.51001,15.9127102);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,4); rn_act_P1 = Activity(1953.49805,16.09412);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,4); rn_act_P1 = Activity(1927.19104,15.4905701);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,4); rn_act_P1 = Activity(2063.12793,15.76653);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,4); rn_act_P1 = Activity(2163.5459,16.2672596);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,4); rn_act_P1 = Activity(2176.45093,16.1435795);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,4); rn_act_P1 = Activity(2079.68506,15.7615204);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,4); rn_act_P1 = Activity(2080.64697,16.1708908);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,5);  rn_act_P1 = Activity(1338.02466,11.8400497);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,5);  rn_act_P1 = Activity(1424.23291,11.9296398);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,5);  rn_act_P1 = Activity(1383.01172,11.7541103);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,5);  rn_act_P1 = Activity(1404.38342,11.9421196);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,5);  rn_act_P1 = Activity(1328.08606,11.5693102);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,5);  rn_act_P1 = Activity(1403.96765,11.7749596);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,5);  rn_act_P1 = Activity(1391.38147,11.5977097);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,5);  rn_act_P1 = Activity(1443.12756,11.8768301);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,5);  rn_act_P1 = Activity(1389.6427,11.7019196);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,5);  rn_act_P1 = Activity(1380.97437,11.7267904);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,5); rn_act_P1 = Activity(1386.70349,11.9502602);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,5); rn_act_P1 = Activity(1397.03503,12.1790504);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,5); rn_act_P1 = Activity(1409.06262,12.1247797);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,5); rn_act_P1 = Activity(1432.15698,12.5035);     add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,5); rn_act_P1 = Activity(1270.22668,11.2920399);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,5); rn_act_P1 = Activity(1476.30066,12.1360903);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,5); rn_act_P1 = Activity(1573.16113,12.6504898);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,5); rn_act_P1 = Activity(1609.21301,12.9573298);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,5); rn_act_P1 = Activity(1556.271,12.6454096);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,5); rn_act_P1 = Activity(1441.95569,12.1212997);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,6);  rn_act_P1 = Activity(925.264404,11.9470196);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,6);  rn_act_P1 = Activity(985.859619,12.27211);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,6);  rn_act_P1 = Activity(948.567383,12.0352497);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,6);  rn_act_P1 = Activity(957.420349,12.0343704);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,6);  rn_act_P1 = Activity(798.932617,11.0985899);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,6);  rn_act_P1 = Activity(946.774597,11.9230604);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,6);  rn_act_P1 = Activity(954.531311,11.7337904);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,6);  rn_act_P1 = Activity(969.598633,11.9936399);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,6);  rn_act_P1 = Activity(940.257507,11.8293505);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,6);  rn_act_P1 = Activity(971.305969,12.2245903);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,6); rn_act_P1 = Activity(942.06366,11.9989204);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,6); rn_act_P1 = Activity(957.263672,13.5539503);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,6); rn_act_P1 = Activity(946.971619,12.06985);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,6); rn_act_P1 = Activity(1017.70892,14.15343);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,6); rn_act_P1 = Activity(926.349792,11.8143396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,6); rn_act_P1 = Activity(652.551636,9.88489056);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,6); rn_act_P1 = Activity(1004.00763,12.3313198);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,6); rn_act_P1 = Activity(964.717834,12.1499395);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,6); rn_act_P1 = Activity(938.723206,11.8011303);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,6); rn_act_P1 = Activity(896.993225,11.7544298);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,7);  rn_act_P1 = Activity(795.132446,16.0472908);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,7);  rn_act_P1 = Activity(811.883606,16.2678604);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,7);  rn_act_P1 = Activity(774.750183,15.4493999);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,7);  rn_act_P1 = Activity(819.708252,16.0271893);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,7);  rn_act_P1 = Activity(762.023926,15.4397202);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,7);  rn_act_P1 = Activity(817.876404,15.9972601);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,7);  rn_act_P1 = Activity(781.400391,15.2725697);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,7);  rn_act_P1 = Activity(779.456543,15.2317801);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,7);  rn_act_P1 = Activity(816.519104,15.9209805);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,7);  rn_act_P1 = Activity(780.804871,15.4349203);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,7); rn_act_P1 = Activity(753.426208,15.1936798);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,7); rn_act_P1 = Activity(756.729431,15.5111303);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,7); rn_act_P1 = Activity(832.497498,16.3891392);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,7); rn_act_P1 = Activity(776.05188,16.3353901);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,7); rn_act_P1 = Activity(737.23114,15.2602196);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,7); rn_act_P1 = Activity(738.322205,15.37498);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,7); rn_act_P1 = Activity(781.843079,15.4178104);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,7); rn_act_P1 = Activity(767.612793,15.3926897);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,7); rn_act_P1 = Activity(790.194275,15.2989502);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,7); rn_act_P1 = Activity(732.831116,15.10392);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,0,8);  rn_act_P1 = Activity(864.743042,18.6470699);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,1,8);  rn_act_P1 = Activity(744.494019,16.9963093);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,2,8);  rn_act_P1 = Activity(765.148193,17.4090595);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,3,8);  rn_act_P1 = Activity(829.446167,18.2339897);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,4,8);  rn_act_P1 = Activity(705.632751,16.8137302);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,5,8);  rn_act_P1 = Activity(787.919067,17.9836197);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,6,8);  rn_act_P1 = Activity(702.461853,17.0076199);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,7,8);  rn_act_P1 = Activity(762.714539,17.7267609);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,8,8);  rn_act_P1 = Activity(770.222168,17.40411);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,9,8);  rn_act_P1 = Activity(747.831665,18.0194893);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,10,8); rn_act_P1 = Activity(707.457703,17.2559204);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,11,8); rn_act_P1 = Activity(765.213135,17.3407898);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,12,8); rn_act_P1 = Activity(766.565613,17.2681808);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,13,8); rn_act_P1 = Activity(953.054016,19.6222591);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,14,8); rn_act_P1 = Activity(825.022522,17.9281006);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,15,8); rn_act_P1 = Activity(698.215942,16.3854198);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,16,8); rn_act_P1 = Activity(792.919189,17.6994209);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,17,8); rn_act_P1 = Activity(821.312683,18.9214191);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,18,8); rn_act_P1 = Activity(743.82196,17.9635105);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(0,19,8); rn_act_P1 = Activity(722.422119,17.2222404);  add_Rn_P1(wire, rn_act_P1);

  wire = WirePosition(1,0,0);  rn_act_P1 = Activity(644.567627,6.8980422);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,0);  rn_act_P1 = Activity(448.79,31.19);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,0);  rn_act_P1 = Activity(385.64,35.25);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,0);  rn_act_P1 = Activity(410.69,36.40);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,0);  rn_act_P1 = Activity(321.03,31.85);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,0);  rn_act_P1 = Activity(672.39,33.62);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,0);  rn_act_P1 = Activity(321.54,49.9);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,0);  rn_act_P1 = Activity(416.52,50.9);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,0);  rn_act_P1 = Activity(273.97,70.2);            add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,0);  rn_act_P1 = Activity(649.635498,6.62800217);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,0); rn_act_P1 = Activity(495.88,27.64);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,0); rn_act_P1 = Activity(364.94,28.85);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,0); rn_act_P1 = Activity(566.66,29.17);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,0); rn_act_P1 = Activity(524.33,31.03);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,0); rn_act_P1 = Activity(326.86,28.23);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,0); rn_act_P1 = Activity(479.45,30.21);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,0); rn_act_P1 = Activity(511.70,34.73);           add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,0); rn_act_P1 = Activity(659.197937,6.58662701);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,0); rn_act_P1 = Activity(701.259033,6.85517216);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,0); rn_act_P1 = Activity(676.302124,6.92700195);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,1);  rn_act_P1 = Activity(809.044495,7.35100222);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,1);  rn_act_P1 = Activity(775.981018,6.96458387);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,1);  rn_act_P1 = Activity(735.843384,6.62116385);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,1);  rn_act_P1 = Activity(765.297913,6.85628605);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,1);  rn_act_P1 = Activity(761.114319,6.88403702);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,1);  rn_act_P1 = Activity(725.123108,6.61750793);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,1);  rn_act_P1 = Activity(731.419983,6.56649303);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,1);  rn_act_P1 = Activity(720.550171,7.01849413);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,1);  rn_act_P1 = Activity(715.907227,6.80060577);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,1);  rn_act_P1 = Activity(720.599915,6.85384798);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,1); rn_act_P1 = Activity(690.06012,6.46754503);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,1); rn_act_P1 = Activity(710.707092,6.61616898);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,1); rn_act_P1 = Activity(740.781189,6.85145283);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,1); rn_act_P1 = Activity(734.765503,6.81860018);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,1); rn_act_P1 = Activity(720.480225,6.51411676);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,1); rn_act_P1 = Activity(756.388672,6.63677597);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,1); rn_act_P1 = Activity(745.943787,6.65014791);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,1); rn_act_P1 = Activity(746.09668,6.61559105);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,1); rn_act_P1 = Activity(762.792114,6.77081823);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,1); rn_act_P1 = Activity(746.279114,6.87151194);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,2);  rn_act_P1 = Activity(1020.742,8.86062431);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,2);  rn_act_P1 = Activity(1065.82397,8.65180874);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,2);  rn_act_P1 = Activity(945.244629,7.95926619);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,2);  rn_act_P1 = Activity(971.942688,8.21060371);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,2);  rn_act_P1 = Activity(1044.46997,8.59595394);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,2);  rn_act_P1 = Activity(984.945374,8.20417595);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,2);  rn_act_P1 = Activity(961.958618,7.86432695);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,2);  rn_act_P1 = Activity(904.06488,7.61495113);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,2);  rn_act_P1 = Activity(926.079407,7.89017582);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,2);  rn_act_P1 = Activity(938.284424,7.83728981);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,2); rn_act_P1 = Activity(936.422485,7.97049093);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,2); rn_act_P1 = Activity(919.506409,7.91355801);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,2); rn_act_P1 = Activity(922.910278,8.0353384);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,2); rn_act_P1 = Activity(978.398071,8.33260345);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,2); rn_act_P1 = Activity(935.613281,7.89610386);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,2); rn_act_P1 = Activity(976.594421,7.97838211);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,2); rn_act_P1 = Activity(992.392517,8.10150146);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,2); rn_act_P1 = Activity(991.981812,8.00662518);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,2); rn_act_P1 = Activity(984.788513,8.09737396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,2); rn_act_P1 = Activity(944.643677,8.16779613);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,3);  rn_act_P1 = Activity(1369.14978,10.3694496);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,3);  rn_act_P1 = Activity(1338.79175,9.65514946);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,3);  rn_act_P1 = Activity(1228.49512,9.02788067);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,3);  rn_act_P1 = Activity(1289.35205,9.38137722);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,3);  rn_act_P1 = Activity(1347.12598,9.79190636);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,3);  rn_act_P1 = Activity(1269.29272,9.16274929);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,3);  rn_act_P1 = Activity(1291.66882,9.12864494);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,3);  rn_act_P1 = Activity(1238.20166,9.14791489);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,3);  rn_act_P1 = Activity(1227.61401,9.14112663);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,3);  rn_act_P1 = Activity(1232.48804,9.04605579);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,3); rn_act_P1 = Activity(1227.0802,9.09552383);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,3); rn_act_P1 = Activity(1223.47302,9.15213203);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,3); rn_act_P1 = Activity(1191.72498,9.15676117);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,3); rn_act_P1 = Activity(1239.0946,9.61852169);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,3); rn_act_P1 = Activity(1179.68298,8.76790905);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,3); rn_act_P1 = Activity(1317.45166,9.22073746);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,3); rn_act_P1 = Activity(1334.72681,9.31856823);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,3); rn_act_P1 = Activity(1304.51184,9.13562107);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,3); rn_act_P1 = Activity(1317.28687,9.3806572);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,3); rn_act_P1 = Activity(1231.11572,9.89028454);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,4);  rn_act_P1 = Activity(1587.94934,11.6362801);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,4);  rn_act_P1 = Activity(1541.84937,11.0111704);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,4);  rn_act_P1 = Activity(1539.37891,10.4657402);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,4);  rn_act_P1 = Activity(1610.25891,11.1049995);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,4);  rn_act_P1 = Activity(1546.36438,11.05581);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,4);  rn_act_P1 = Activity(1549.44519,10.5053196);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,4);  rn_act_P1 = Activity(1568.83606,10.3968496);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,4);  rn_act_P1 = Activity(1583.57251,10.7996197);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,4);  rn_act_P1 = Activity(1642.0116,10.99401);     add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,4);  rn_act_P1 = Activity(1670.41089,11.0383501);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,4); rn_act_P1 = Activity(1679.87463,11.1429796);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,4); rn_act_P1 = Activity(1599.95166,10.9145403);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,4); rn_act_P1 = Activity(1563.81909,10.9177704);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,4); rn_act_P1 = Activity(1587.62036,11.1649399);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,4); rn_act_P1 = Activity(1629.47693,10.80404);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,4); rn_act_P1 = Activity(1747.75977,11.1395998);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,4); rn_act_P1 = Activity(1614.2771,10.6451998);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,4); rn_act_P1 = Activity(1717.99243,10.9219904);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,4); rn_act_P1 = Activity(1516.08142,10.4233999);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,4); rn_act_P1 = Activity(1641.4248,11.0144396);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,5);  rn_act_P1 = Activity(1873.55481,12.8828402);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,5);  rn_act_P1 = Activity(1823.13892,12.1632404);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,5);  rn_act_P1 = Activity(1771.75073,11.68888);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,5);  rn_act_P1 = Activity(1748.94531,11.7811499);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,5);  rn_act_P1 = Activity(1779.52454,12.6257296);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,5);  rn_act_P1 = Activity(1775.65503,11.7126503);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,5);  rn_act_P1 = Activity(1848.6532,11.9038601);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,5);  rn_act_P1 = Activity(1749.52869,11.93855);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,5);  rn_act_P1 = Activity(1753.02429,11.9310598);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,5);  rn_act_P1 = Activity(1825.57654,12.1781797);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,5); rn_act_P1 = Activity(1834.10632,12.06985);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,5); rn_act_P1 = Activity(1826.63831,12.2682304);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,5); rn_act_P1 = Activity(1743.17102,12.04776);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,5); rn_act_P1 = Activity(1820.30249,12.8838196);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,5); rn_act_P1 = Activity(1814.51428,11.8184299);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,5); rn_act_P1 = Activity(1938.08264,12.16751);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,5); rn_act_P1 = Activity(1858.29431,12.0953398);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,5); rn_act_P1 = Activity(1907.55957,11.9335804);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,5); rn_act_P1 = Activity(1770.61194,11.9753599);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,5); rn_act_P1 = Activity(1902.87976,12.6784801);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,6);  rn_act_P1 = Activity(959.599365,9.05765438);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,6);  rn_act_P1 = Activity(966.98468,8.6788578);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,6);  rn_act_P1 = Activity(981.392029,8.41618156);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,6);  rn_act_P1 = Activity(967.804749,8.55024815);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,6);  rn_act_P1 = Activity(1005.05237,9.39043999);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,6);  rn_act_P1 = Activity(1078.38416,8.85563564);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,6);  rn_act_P1 = Activity(1110.32349,9.01281738);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,6);  rn_act_P1 = Activity(1093.94019,9.27420044);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,6);  rn_act_P1 = Activity(1011.6676,8.85915375);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,6);  rn_act_P1 = Activity(1093.53174,9.36658764);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,6); rn_act_P1 = Activity(1016.11145,8.85953045);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,6); rn_act_P1 = Activity(1055.24133,9.18322563);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,6); rn_act_P1 = Activity(1079.03699,9.22548962);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,6); rn_act_P1 = Activity(1038.3866,9.2823143);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,6); rn_act_P1 = Activity(1023.71222,8.74878407);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,6); rn_act_P1 = Activity(1028.07361,8.66345406);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,6); rn_act_P1 = Activity(969.767761,8.36494732);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,6); rn_act_P1 = Activity(483.674225,5.92484379);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,6); rn_act_P1 = Activity(954.411804,8.61903095);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,6); rn_act_P1 = Activity(964.450623,8.69024563);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,7);  rn_act_P1 = Activity(750.651489,12.2290201);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,7);  rn_act_P1 = Activity(775.009705,12.3010798);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,7);  rn_act_P1 = Activity(820.547424,12.4196396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,7);  rn_act_P1 = Activity(789.475342,12.0644503);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,7);  rn_act_P1 = Activity(810.669067,13.0383701);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,7);  rn_act_P1 = Activity(810.052429,12.1114302);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,7);  rn_act_P1 = Activity(799.466492,12.07584);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,7);  rn_act_P1 = Activity(798.041199,12.2999601);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,7);  rn_act_P1 = Activity(798.697449,12.3655396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,7);  rn_act_P1 = Activity(840.298889,12.8087502);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,7); rn_act_P1 = Activity(826.60083,12.5903101);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,7); rn_act_P1 = Activity(801.518066,12.5764303);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,7); rn_act_P1 = Activity(797.760986,12.25457);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,7); rn_act_P1 = Activity(791.495117,12.6516199);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,7); rn_act_P1 = Activity(760.502563,11.7200699);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,7); rn_act_P1 = Activity(791.505066,11.9800596);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,7); rn_act_P1 = Activity(799.297363,12.3790197);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,7); rn_act_P1 = Activity(627.041626,10.5362501);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,7); rn_act_P1 = Activity(810.639404,12.80898);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,7); rn_act_P1 = Activity(772.167114,11.9628897);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,0,8);  rn_act_P1 = Activity(894.72522,14.9088202);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,1,8);  rn_act_P1 = Activity(767.2229,13.2149);       add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,2,8);  rn_act_P1 = Activity(780.764099,12.7877703);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,3,8);  rn_act_P1 = Activity(755.385803,12.5573902);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,4,8);  rn_act_P1 = Activity(722.510315,13.2823601);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,5,8);  rn_act_P1 = Activity(758.952087,12.4604797);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,6,8);  rn_act_P1 = Activity(757.383301,12.98522);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,7,8);  rn_act_P1 = Activity(769.460938,13.1975002);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,8,8);  rn_act_P1 = Activity(782.235657,13.7672501);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,9,8);  rn_act_P1 = Activity(740.815552,13.2626104);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,10,8); rn_act_P1 = Activity(759.606201,12.89007);    add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,11,8); rn_act_P1 = Activity(777.672241,13.4180603);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,12,8); rn_act_P1 = Activity(783.21167,13.6027298);   add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,13,8); rn_act_P1 = Activity(990.379089,15.3599997);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,14,8); rn_act_P1 = Activity(796.015747,13.4012699);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,15,8); rn_act_P1 = Activity(919.309326,13.8818102);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,16,8); rn_act_P1 = Activity(771.528503,12.9025698);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,17,8); rn_act_P1 = Activity(615.625549,11.5123396);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,18,8); rn_act_P1 = Activity(715.030029,12.6993799);  add_Rn_P1(wire, rn_act_P1);
  wire = WirePosition(1,19,8); rn_act_P1 = Activity(791.026672,13.7533302);  add_Rn_P1(wire, rn_act_P1);

  // SET RADON ACTIVITIES FOR PHASE 2
  wire = WirePosition(0,0,0);  rn_act_P2 = Activity(153.95,2.38);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,0);  rn_act_P2 = Activity(74.51, 6.93);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,0);  rn_act_P2 = Activity(25.36, 7.31);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,0);  rn_act_P2 = Activity(43.73, 9.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,0);  rn_act_P2 = Activity(19.71, 8.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,0);  rn_act_P2 = Activity(50.29, 7.29);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,0);  rn_act_P2 = Activity(44.58, 9.3);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,0);  rn_act_P2 = Activity(52.13, 9.8);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,0);  rn_act_P2 = Activity(43.70,14.0);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,0);  rn_act_P2 = Activity(145.43,2.29);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,0); rn_act_P2 = Activity(19.37, 5.26);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,0); rn_act_P2 = Activity(25.09, 5.58);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,0); rn_act_P2 = Activity(44.90, 5.75);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,0); rn_act_P2 = Activity(74.64, 7.04);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,0); rn_act_P2 = Activity(40.68, 5.25);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,0); rn_act_P2 = Activity(52.56, 6.44);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,0); rn_act_P2 = Activity(28.04, 6.26);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,0); rn_act_P2 = Activity(171.06,2.49);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,0); rn_act_P2 = Activity(161.42,2.44);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,0); rn_act_P2 = Activity(146.72,2.33);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,1);  rn_act_P2 = Activity(120.45,1.89);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,1);  rn_act_P2 = Activity(111.72,1.80);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,1);  rn_act_P2 = Activity(113.53,1.81);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,1);  rn_act_P2 = Activity(119.75,1.88);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,1);  rn_act_P2 = Activity(113.64,1.85);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,1);  rn_act_P2 = Activity(117.57,1.84);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,1);  rn_act_P2 = Activity(118.06,1.80);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,1);  rn_act_P2 = Activity(113.07,1.79);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,1);  rn_act_P2 = Activity(123.92,1.87);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,1);  rn_act_P2 = Activity(116.75,1.78);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,1); rn_act_P2 = Activity(115.79,1.81);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,1); rn_act_P2 = Activity(118.69,1.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,1); rn_act_P2 = Activity(121.65,1.91);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,1); rn_act_P2 = Activity(113.93,1.95);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,1); rn_act_P2 = Activity(120.96,1.90);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,1); rn_act_P2 = Activity(120.19,1.89);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,1); rn_act_P2 = Activity(119.07,1.85);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,1); rn_act_P2 = Activity(117.29,1.81);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,1); rn_act_P2 = Activity(113.76,1.78);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,1); rn_act_P2 = Activity(118.47,1.88);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,2);  rn_act_P2 = Activity(115.75,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,2);  rn_act_P2 = Activity(118.57,1.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,2);  rn_act_P2 = Activity(116.53,1.65);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,2);  rn_act_P2 = Activity(119.71,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,2);  rn_act_P2 = Activity(117.43,1.70);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,2);  rn_act_P2 = Activity(122.79,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,2);  rn_act_P2 = Activity(119.21,1.62);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,2);  rn_act_P2 = Activity(119.09,1.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,2);  rn_act_P2 = Activity(118.05,1.63);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,2);  rn_act_P2 = Activity(114.18,1.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,2); rn_act_P2 = Activity(113.60,1.61);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,2); rn_act_P2 = Activity(124.54,1.70);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,2); rn_act_P2 = Activity(121.40,1.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,2); rn_act_P2 = Activity(134.66,1.96);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,2); rn_act_P2 = Activity(115.43,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,2); rn_act_P2 = Activity(120.06,1.70);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,2); rn_act_P2 = Activity(132.82,1.76);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,2); rn_act_P2 = Activity(127.37,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,2); rn_act_P2 = Activity(109.93,1.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,2); rn_act_P2 = Activity(112.95,1.65);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,3);  rn_act_P2 = Activity(196.33,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,3);  rn_act_P2 = Activity(196.27,2.23);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,3);  rn_act_P2 = Activity(200.84,2.26);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,3);  rn_act_P2 = Activity(206.89,2.33);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,3);  rn_act_P2 = Activity(194.87,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,3);  rn_act_P2 = Activity(209.03,2.31);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,3);  rn_act_P2 = Activity(199.06,2.20);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,3);  rn_act_P2 = Activity(189.26,2.18);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,3);  rn_act_P2 = Activity(188.17,2.16);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,3);  rn_act_P2 = Activity(192.36,2.17);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,3); rn_act_P2 = Activity(183.09,2.14);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,3); rn_act_P2 = Activity(190.79,2.21);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,3); rn_act_P2 = Activity(186.20,2.35);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,3); rn_act_P2 = Activity(245.61,3.05);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,3); rn_act_P2 = Activity(179.34,2.21);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,3); rn_act_P2 = Activity(196.35,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,3); rn_act_P2 = Activity(213.50,2.35);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,3); rn_act_P2 = Activity(200.54,2.32);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,3); rn_act_P2 = Activity(180.01,2.14);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,3); rn_act_P2 = Activity(198.21,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,4);  rn_act_P2 = Activity(284.68,3.24);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,4);  rn_act_P2 = Activity(297.31,3.25);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,4);  rn_act_P2 = Activity(289.72,3.19);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,4);  rn_act_P2 = Activity(291.11,3.25);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,4);  rn_act_P2 = Activity(278.84,3.21);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,4);  rn_act_P2 = Activity(288.97,3.20);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,4);  rn_act_P2 = Activity(326.28,3.31);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,4);  rn_act_P2 = Activity(356.47,3.53);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,4);  rn_act_P2 = Activity(323.78,3.35);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,4);  rn_act_P2 = Activity(344.44,3.44);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,4); rn_act_P2 = Activity(352.37,3.50);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,4); rn_act_P2 = Activity(359.84,3.55);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,4); rn_act_P2 = Activity(349.75,3.72);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,4); rn_act_P2 = Activity(395.34,5.79);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,4); rn_act_P2 = Activity(335.08,3.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,4); rn_act_P2 = Activity(325.96,3.43);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,4); rn_act_P2 = Activity(334.86,3.45);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,4); rn_act_P2 = Activity(328.81,3.38);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,4); rn_act_P2 = Activity(299.50,3.24);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,4); rn_act_P2 = Activity(299.73,3.30);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,5);  rn_act_P2 = Activity(209.39,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,5);  rn_act_P2 = Activity(212.85,2.55);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,5);  rn_act_P2 = Activity(217.02,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,5);  rn_act_P2 = Activity(216.83,2.60);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,5);  rn_act_P2 = Activity(201.68,2.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,5);  rn_act_P2 = Activity(223.59,2.60);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,5);  rn_act_P2 = Activity(224.80,2.60);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,5);  rn_act_P2 = Activity(238.70,2.77);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,5);  rn_act_P2 = Activity(207.70,2.50);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,5);  rn_act_P2 = Activity(228.00,2.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,5); rn_act_P2 = Activity(220.54,2.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,5); rn_act_P2 = Activity(229.79,2.63);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,5); rn_act_P2 = Activity(219.45,2.72);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,5); rn_act_P2 = Activity(287.77,3.65);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,5); rn_act_P2 = Activity(207.51,2.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,5); rn_act_P2 = Activity(204.79,2.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,5); rn_act_P2 = Activity(223.17,2.62);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,5); rn_act_P2 = Activity(236.61,2.72);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,5); rn_act_P2 = Activity(223.74,2.63);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,5); rn_act_P2 = Activity(208.34,2.53);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,6);  rn_act_P2 = Activity(149.23,2.64);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,6);  rn_act_P2 = Activity(151.45,2.63);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,6);  rn_act_P2 = Activity(145.86,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,6);  rn_act_P2 = Activity(159.45,2.71);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,6);  rn_act_P2 = Activity(117.01,2.35);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,6);  rn_act_P2 = Activity(141.40,2.51);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,6);  rn_act_P2 = Activity(152.33,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,6);  rn_act_P2 = Activity(143.97,2.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,6);  rn_act_P2 = Activity(134.28,2.42);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,6);  rn_act_P2 = Activity(148.82,2.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,6); rn_act_P2 = Activity(133.09,2.40);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,6); rn_act_P2 = Activity(140.07,2.47);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,6); rn_act_P2 = Activity(145.47,2.67);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,6); rn_act_P2 = Activity(159.16,3.01);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,6); rn_act_P2 = Activity(146.78,2.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,6); rn_act_P2 = Activity(96.57,2.11);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,6); rn_act_P2 = Activity(143.80,2.55);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,6); rn_act_P2 = Activity(153.56,2.67);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,6); rn_act_P2 = Activity(150.15,2.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,6); rn_act_P2 = Activity(144.05,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,7);  rn_act_P2 = Activity(88.13,3.18);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,7);  rn_act_P2 = Activity(87.40,3.14);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,7);  rn_act_P2 = Activity(91.46,3.18);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,7);  rn_act_P2 = Activity(93.27,3.24);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,7);  rn_act_P2 = Activity(70.18,2.86);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,7);  rn_act_P2 = Activity(95.05,3.24);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,7);  rn_act_P2 = Activity(93.56,3.09);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,7);  rn_act_P2 = Activity(94.47,3.10);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,7);  rn_act_P2 = Activity(83.69,2.96);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,7);  rn_act_P2 = Activity(98.78,3.17);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,7); rn_act_P2 = Activity(82.82,2.95);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,7); rn_act_P2 = Activity(81.60,2.97);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,7); rn_act_P2 = Activity(91.42,3.52);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,7); rn_act_P2 = Activity(81.71,3.50);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,7); rn_act_P2 = Activity(74.11,3.02);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,7); rn_act_P2 = Activity(82.48,3.11);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,7); rn_act_P2 = Activity(88.54,3.09);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,7); rn_act_P2 = Activity(97.17,3.17);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,7); rn_act_P2 = Activity(89.38,3.04);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,7); rn_act_P2 = Activity(82.37,3.00);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,0,8);  rn_act_P2 = Activity(188.55,5.52);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,1,8);  rn_act_P2 = Activity(163.76,5.01);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,2,8);  rn_act_P2 = Activity(245.87,6.17);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,3,8);  rn_act_P2 = Activity(277.88,6.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,4,8);  rn_act_P2 = Activity(161.21,5.30);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,5,8);  rn_act_P2 = Activity(169.84,5.20);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,6,8);  rn_act_P2 = Activity(153.58,4.91);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,7,8);  rn_act_P2 = Activity(181.50,5.99);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,8,8);  rn_act_P2 = Activity(123.62,4.49);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,9,8);  rn_act_P2 = Activity(166.52,5.60);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,10,8); rn_act_P2 = Activity(126.87,4.58);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,11,8); rn_act_P2 = Activity(132.23,4.47);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,12,8); rn_act_P2 = Activity(167.96,5.25);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,13,8); rn_act_P2 = Activity(351.49,7.76);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,14,8); rn_act_P2 = Activity(167.29,5.17);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,15,8); rn_act_P2 = Activity(225.41,5.96);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,16,8); rn_act_P2 = Activity(150.40,4.82);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,17,8); rn_act_P2 = Activity(263.93,6.96);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,18,8); rn_act_P2 = Activity(190.83,5.72);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(0,19,8); rn_act_P2 = Activity(176.39,5.41);  add_Rn_P2(wire, rn_act_P2);

  wire = WirePosition(1,0,0);  rn_act_P2 = Activity(141.57,2.05);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,0);  rn_act_P2 = Activity(34.79, 5.90);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,0);  rn_act_P2 = Activity(38.32, 6.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,0);  rn_act_P2 = Activity(72.21,12.97);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,0);  rn_act_P2 = Activity(31.83, 7.24);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,0);  rn_act_P2 = Activity(46.69, 6.76);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,0);  rn_act_P2 = Activity( 26.65, 7.9);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,0);  rn_act_P2 = Activity( 45.90, 8.4);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,0);  rn_act_P2 = Activity( 24.79,12.6);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,0);  rn_act_P2 = Activity(139.67,1.88);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,0); rn_act_P2 = Activity(56.28, 6.73);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,0); rn_act_P2 = Activity(23.50, 5.12);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,0); rn_act_P2 = Activity(50.47, 5.33);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,0); rn_act_P2 = Activity(31.04, 6.94);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,0); rn_act_P2 = Activity(39.93, 5.87);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,0); rn_act_P2 = Activity(67.90, 5.61);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,0); rn_act_P2 = Activity(73.25, 7.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,0); rn_act_P2 = Activity(148.50,1.93);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,0); rn_act_P2 = Activity(153.92,2.03);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,0); rn_act_P2 = Activity(165.14,2.14);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,1);  rn_act_P2 = Activity(113.09,1.63);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,1);  rn_act_P2 = Activity(113.48,1.57);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,1);  rn_act_P2 = Activity(102.20,1.46);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,1);  rn_act_P2 = Activity(109.52,1.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,1);  rn_act_P2 = Activity(106.82,1.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,1);  rn_act_P2 = Activity(104.81,1.53);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,1);  rn_act_P2 = Activity(102.41,1.42);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,1);  rn_act_P2 = Activity(99.74,1.51);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,1);  rn_act_P2 = Activity(102.94,1.49);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,1);  rn_act_P2 = Activity(104.68,1.45);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,1); rn_act_P2 = Activity(101.75,1.42);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,1); rn_act_P2 = Activity(104.28,1.45);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,1); rn_act_P2 = Activity(103.24,1.49);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,1); rn_act_P2 = Activity(112.88,8.39);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,1); rn_act_P2 = Activity(102.83,1.50);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,1); rn_act_P2 = Activity(106.76,1.51);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,1); rn_act_P2 = Activity(107.42,1.48);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,1); rn_act_P2 = Activity(105.18,1.44);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,1); rn_act_P2 = Activity(109.23,1.51);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,1); rn_act_P2 = Activity(106.21,1.54);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,2);  rn_act_P2 = Activity(158.83,2.00);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,2);  rn_act_P2 = Activity(161.28,1.89);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,2);  rn_act_P2 = Activity(136.99,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,2);  rn_act_P2 = Activity(149.77,1.82);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,2);  rn_act_P2 = Activity(156.70,1.90);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,2);  rn_act_P2 = Activity(140.10,1.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,2);  rn_act_P2 = Activity(140.43,1.68);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,2);  rn_act_P2 = Activity(133.67,1.64);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,2);  rn_act_P2 = Activity(134.40,1.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,2);  rn_act_P2 = Activity(138.40,1.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,2); rn_act_P2 = Activity(142.19,1.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,2); rn_act_P2 = Activity(136.21,1.66);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,2); rn_act_P2 = Activity(134.38,1.72);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,2); rn_act_P2 = Activity(144.19,9.43);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,2); rn_act_P2 = Activity(132.05,1.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,2); rn_act_P2 = Activity(143.83,1.76);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,2); rn_act_P2 = Activity(143.95,1.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,2); rn_act_P2 = Activity(143.21,1.68);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,2); rn_act_P2 = Activity(148.57,1.77);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,2); rn_act_P2 = Activity(137.46,1.76);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,3);  rn_act_P2 = Activity(249.58,2.56);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,3);  rn_act_P2 = Activity(261.95,2.37);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,3);  rn_act_P2 = Activity(232.85,2.15);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,3);  rn_act_P2 = Activity(246.30,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,3);  rn_act_P2 = Activity(263.09,2.46);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,3);  rn_act_P2 = Activity(226.91,2.16);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,3);  rn_act_P2 = Activity(228.27,2.09);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,3);  rn_act_P2 = Activity(221.37,2.12);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,3);  rn_act_P2 = Activity(218.62,2.10);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,3);  rn_act_P2 = Activity(218.57,2.05);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,3); rn_act_P2 = Activity(227.07,2.09);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,3); rn_act_P2 = Activity(222.57,2.10);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,3); rn_act_P2 = Activity(211.64,2.13);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,3); rn_act_P2 = Activity(261.42,13.22); add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,3); rn_act_P2 = Activity(207.68,2.13);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,3); rn_act_P2 = Activity(235.78,2.22);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,3); rn_act_P2 = Activity(235.33,2.16);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,3); rn_act_P2 = Activity(238.65,2.14);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,3); rn_act_P2 = Activity(241.95,2.23);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,3); rn_act_P2 = Activity(225.96,2.23);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,4);  rn_act_P2 = Activity(253.19,2.55);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,4);  rn_act_P2 = Activity(248.29,2.35);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,4);  rn_act_P2 = Activity(232.86,2.19);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,4);  rn_act_P2 = Activity(233.70,2.30);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,4);  rn_act_P2 = Activity(240.61,2.43);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,4);  rn_act_P2 = Activity(249.58,2.30);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,4);  rn_act_P2 = Activity(274.94,2.34);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,4);  rn_act_P2 = Activity(270.34,2.39);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,4);  rn_act_P2 = Activity(261.48,2.33);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,4);  rn_act_P2 = Activity(263.55,2.30);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,4); rn_act_P2 = Activity(258.89,2.28);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,4); rn_act_P2 = Activity(270.07,2.36);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,4); rn_act_P2 = Activity(278.33,2.49);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,4); rn_act_P2 = Activity(307.01,16.24); add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,4); rn_act_P2 = Activity(271.61,2.48);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,4); rn_act_P2 = Activity(268.02,2.42);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,4); rn_act_P2 = Activity(246.53,2.24);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,4); rn_act_P2 = Activity(264.04,2.29);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,4); rn_act_P2 = Activity(235.60,2.22);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,4); rn_act_P2 = Activity(265.60,2.47);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,5);  rn_act_P2 = Activity(361.99,3.26);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,5);  rn_act_P2 = Activity(358.64,3.03);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,5);  rn_act_P2 = Activity(325.50,2.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,5);  rn_act_P2 = Activity(316.16,2.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,5);  rn_act_P2 = Activity(324.44,3.12);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,5);  rn_act_P2 = Activity(344.54,2.87);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,5);  rn_act_P2 = Activity(369.48,2.92);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,5);  rn_act_P2 = Activity(362.00,3.02);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,5);  rn_act_P2 = Activity(346.42,2.93);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,5);  rn_act_P2 = Activity(363.45,2.95);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,5); rn_act_P2 = Activity(343.48,2.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,5); rn_act_P2 = Activity(350.93,2.91);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,5); rn_act_P2 = Activity(334.28,2.95);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,5); rn_act_P2 = Activity(386.37,16.63); add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,5); rn_act_P2 = Activity(342.23,3.00);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,5); rn_act_P2 = Activity(352.00,3.01);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,5); rn_act_P2 = Activity(342.49,2.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,5); rn_act_P2 = Activity(329.20,2.78);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,5); rn_act_P2 = Activity(340.06,2.90);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,5); rn_act_P2 = Activity(371.62,3.21);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,6);  rn_act_P2 = Activity(166.96,2.12);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,6);  rn_act_P2 = Activity(154.93,1.93);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,6);  rn_act_P2 = Activity(159.59,1.87);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,6);  rn_act_P2 = Activity(148.06,1.86);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,6);  rn_act_P2 = Activity(139.42,2.01);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,6);  rn_act_P2 = Activity(147.68,1.81);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,6);  rn_act_P2 = Activity(152.12,1.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,6);  rn_act_P2 = Activity(158.22,1.93);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,6);  rn_act_P2 = Activity(138.54,1.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,6);  rn_act_P2 = Activity(155.99,1.96);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,6); rn_act_P2 = Activity(134.42,1.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,6); rn_act_P2 = Activity(143.23,1.81);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,6); rn_act_P2 = Activity(146.16,1.89);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,6); rn_act_P2 = Activity(166.69,11.33); add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,6); rn_act_P2 = Activity(146.73,1.89);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,6); rn_act_P2 = Activity(155.24,1.95);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,6); rn_act_P2 = Activity(152.06,1.83);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,6); rn_act_P2 = Activity(84.37,1.37);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,6); rn_act_P2 = Activity(162.28,1.94);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,6); rn_act_P2 = Activity(165.97,2.06);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,7);  rn_act_P2 = Activity(99.62,2.73);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,7);  rn_act_P2 = Activity(93.07,2.57);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,7);  rn_act_P2 = Activity(90.64,2.53);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,7);  rn_act_P2 = Activity(88.78,2.53);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,7);  rn_act_P2 = Activity(90.99,2.64);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,7);  rn_act_P2 = Activity(89.56,2.46);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,7);  rn_act_P2 = Activity(95.43,2.56);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,7);  rn_act_P2 = Activity(90.04,2.48);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,7);  rn_act_P2 = Activity(105.75,2.64);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,7);  rn_act_P2 = Activity(91.01,2.49);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,7); rn_act_P2 = Activity(88.82,2.51);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,7); rn_act_P2 = Activity(95.12,2.57);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,7); rn_act_P2 = Activity(93.46,2.62);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,7); rn_act_P2 = Activity(83.74,15.55);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,7); rn_act_P2 = Activity(85.61,2.58);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,7); rn_act_P2 = Activity(87.43,2.58);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,7); rn_act_P2 = Activity(90.20,2.52);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,7); rn_act_P2 = Activity(86.33,2.41);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,7); rn_act_P2 = Activity(94.87,2.57);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,7); rn_act_P2 = Activity(94.49,2.59);   add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,0,8);  rn_act_P2 = Activity(424.13,7.16);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,1,8);  rn_act_P2 = Activity(219.94,4.74);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,2,8);  rn_act_P2 = Activity(241.49,4.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,3,8);  rn_act_P2 = Activity(256.47,4.86);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,4,8);  rn_act_P2 = Activity(196.17,4.84);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,5,8);  rn_act_P2 = Activity(267.95,4.97);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,6,8);  rn_act_P2 = Activity(260.23,5.04);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,7,8);  rn_act_P2 = Activity(246.68,4.85);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,8,8);  rn_act_P2 = Activity(212.38,4.99);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,9,8);  rn_act_P2 = Activity(198.28,4.69);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,10,8); rn_act_P2 = Activity(223.60,4.59);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,11,8); rn_act_P2 = Activity(225.80,4.86);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,12,8); rn_act_P2 = Activity(245.18,4.98);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,13,8); rn_act_P2 = Activity(565.97,54.71); add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,14,8); rn_act_P2 = Activity(228.00,4.99);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,15,8); rn_act_P2 = Activity(484.74,7.02);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,16,8); rn_act_P2 = Activity(235.71,4.68);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,17,8); rn_act_P2 = Activity(252.67,4.90);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,18,8); rn_act_P2 = Activity(213.35,4.64);  add_Rn_P2(wire, rn_act_P2);
  wire = WirePosition(1,19,8); rn_act_P2 = Activity(308.63,5.86);  add_Rn_P2(wire, rn_act_P2);

  // SET BI-210 ACTIVITIES FOR PHASE 1
  wire = WirePosition(0,0,1);  bi210_act_P1 = Activity(6016.76,83.2933);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,0,2);  bi210_act_P1 = Activity(5844.33,82.5958);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,0,3);  bi210_act_P1 = Activity(8776,100.874);     add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,0,4);  bi210_act_P1 = Activity(7659.31,103.409);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,0,5);  bi210_act_P1 = Activity(10368.5,184.322);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,1,1);  bi210_act_P1 = Activity(2164.18,54.6218);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,1,2);  bi210_act_P1 = Activity(2030.21,54.0963);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,1,3);  bi210_act_P1 = Activity(3003.1,64.8994);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,1,4);  bi210_act_P1 = Activity(2792.04,75.1971);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,1,5);  bi210_act_P1 = Activity(3728.49,123.147);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,2,1);  bi210_act_P1 = Activity(2711.995,62.1863); add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,2,2);  bi210_act_P1 = Activity(2711.89,59.9134);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,2,3);  bi210_act_P1 = Activity(4201.53,73.7254);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,2,4);  bi210_act_P1 = Activity(3900.51,81.0685);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,2,5);  bi210_act_P1 = Activity(5294.31,140.921);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,3,1);  bi210_act_P1 = Activity(3407.59,65.0049);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,3,2);  bi210_act_P1 = Activity(3333.09,64.3302);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,3,3);  bi210_act_P1 = Activity(5631.89,83.1098);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,3,4);  bi210_act_P1 = Activity(4887.35,87.0692);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,3,5);  bi210_act_P1 = Activity(6477.62,149.923);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,4,1);  bi210_act_P1 = Activity(2487.73,57.299);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,4,2);  bi210_act_P1 = Activity(2295.5,55.9572);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,4,3);  bi210_act_P1 = Activity(3669.13,69.2271);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,4,4);  bi210_act_P1 = Activity(3263.86,76.5604);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,4,5);  bi210_act_P1 = Activity(4469.84,129.762);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,5,1);  bi210_act_P1 = Activity(12249.6,109.961);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,5,2);  bi210_act_P1 = Activity(12527.6,111.599);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,5,3);  bi210_act_P1 = Activity(23783.4,155.235);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,5,4);  bi210_act_P1 = Activity(21500.5,150.492);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,5,5);  bi210_act_P1 = Activity(29954.6,283.392);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,6,1);  bi210_act_P1 = Activity(3205.62,63.1832);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,6,2);  bi210_act_P1 = Activity(3004.32,61.3302);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,6,3);  bi210_act_P1 = Activity(4675.21,76.4437);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,6,4);  bi210_act_P1 = Activity(4615.06,85.1605);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,6,5);  bi210_act_P1 = Activity(5721.95,143.132);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,7,1);  bi210_act_P1 = Activity(4641.39,72.2358);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,7,2);  bi210_act_P1 = Activity(4389.16,71.6151);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,7,3);  bi210_act_P1 = Activity(6626.36,87.4972);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,7,4);  bi210_act_P1 = Activity(5778.83,92.8832);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,7,5);  bi210_act_P1 = Activity(7848.52,159.554);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,8,1);  bi210_act_P1 = Activity(3105.68,61.6942);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,8,2);  bi210_act_P1 = Activity(2912.71,61.5726);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,8,3);  bi210_act_P1 = Activity(4582.81,76.702);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,8,4);  bi210_act_P1 = Activity(4690.73,84.416);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,8,5);  bi210_act_P1 = Activity(6294.65,146.981);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,9,1);  bi210_act_P1 = Activity(1667.49,50.7807);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,9,2);  bi210_act_P1 = Activity(1736.42,51.807);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,9,3);  bi210_act_P1 = Activity(2817.35,64.6067);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,9,4);  bi210_act_P1 = Activity(2629.68,74.9125);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,9,5);  bi210_act_P1 = Activity(3551.02,125.211);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,10,1); bi210_act_P1 = Activity(2678.76,59.8202);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,10,2); bi210_act_P1 = Activity(2634.45,59.4854);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,10,3); bi210_act_P1 = Activity(4729,77.9421);     add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,10,4); bi210_act_P1 = Activity(4231.3,84.7171);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,10,5); bi210_act_P1 = Activity(5601.79,147.408);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,11,1); bi210_act_P1 = Activity(1879.92,52.3807);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,11,2); bi210_act_P1 = Activity(1855.4,51.9604);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,11,3); bi210_act_P1 = Activity(3550.09,68.7359);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,11,4); bi210_act_P1 = Activity(3470.85,81.1673);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,11,5); bi210_act_P1 = Activity(4419.6,142.323);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,12,1); bi210_act_P1 = Activity(4069.65,70.2182);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,12,2); bi210_act_P1 = Activity(4159.74,71.8131);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,12,3); bi210_act_P1 = Activity(5904.8,86.6704);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,12,4); bi210_act_P1 = Activity(5516.87,91.3943);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,12,5); bi210_act_P1 = Activity(7093.95,155.856);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,13,1); bi210_act_P1 = Activity(16308.1,128.468);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,13,2); bi210_act_P1 = Activity(17245.8,133.649);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,13,3); bi210_act_P1 = Activity(31789.2,185.347);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,13,4); bi210_act_P1 = Activity(25178.1,169.935);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,13,5); bi210_act_P1 = Activity(35979.6,342.341);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,14,1); bi210_act_P1 = Activity(2121.99,54.3541);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,14,2); bi210_act_P1 = Activity(2162.56,54.7879);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,14,3); bi210_act_P1 = Activity(3590.18,69.2934);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,14,4); bi210_act_P1 = Activity(2897.41,74.4141);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,14,5); bi210_act_P1 = Activity(2913.5,112.537);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,15,1); bi210_act_P1 = Activity(13189.1,114.51);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,15,2); bi210_act_P1 = Activity(12884.4,114.842);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,15,3); bi210_act_P1 = Activity(25972.1,162.357);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,15,4); bi210_act_P1 = Activity(22164.5,156.306);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,15,5); bi210_act_P1 = Activity(23758.1,260.527);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,16,1); bi210_act_P1 = Activity(18737.7,136.121);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,16,2); bi210_act_P1 = Activity(18786.6,138.136);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,16,3); bi210_act_P1 = Activity(29330.7,173.787);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,16,4); bi210_act_P1 = Activity(29813.9,178.956);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,16,5); bi210_act_P1 = Activity(37967.9,329.064);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,17,1); bi210_act_P1 = Activity(14416.8,124.049);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,17,2); bi210_act_P1 = Activity(15087.9,127.619);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,17,3); bi210_act_P1 = Activity(25207.3,168.596);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,17,4); bi210_act_P1 = Activity(26995.7,173.974);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,17,5); bi210_act_P1 = Activity(31704.8,314.453);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,18,1); bi210_act_P1 = Activity(2465.46,59.6495);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,18,2); bi210_act_P1 = Activity(2369.33,58.6209);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,18,3); bi210_act_P1 = Activity(4145.38,75.1018);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,18,4); bi210_act_P1 = Activity(5021.98,91.4325);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,18,5); bi210_act_P1 = Activity(5231.96,143.555);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,19,1); bi210_act_P1 = Activity(3468.17,67.4544);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,19,2); bi210_act_P1 = Activity(3707.43,68.9879);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,19,3); bi210_act_P1 = Activity(5698.63,85.562);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,19,4); bi210_act_P1 = Activity(5171.26,92.4329);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(0,19,5); bi210_act_P1 = Activity(6326.86,151.745);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,0,1);  bi210_act_P1 = Activity(6406.72,72.9889);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,0,2);  bi210_act_P1 = Activity(5919.19,73.0704);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,0,3);  bi210_act_P1 = Activity(11135.5,98.9106);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,0,4);  bi210_act_P1 = Activity(8318.15,90.5406);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,0,5);  bi210_act_P1 = Activity(11610.4,144.792);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,1,1);  bi210_act_P1 = Activity(2227.41,46.1975);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,1,2);  bi210_act_P1 = Activity(2166.07,48.1498);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,1,3);  bi210_act_P1 = Activity(4727.36,66.1557);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,1,4);  bi210_act_P1 = Activity(3954.64,69.6941);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,1,5);  bi210_act_P1 = Activity(4951.42,98.1604);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,2,1);  bi210_act_P1 = Activity(3181.2,49.7386);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,2,2);  bi210_act_P1 = Activity(3065.02,50.9507);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,2,3);  bi210_act_P1 = Activity(6259.19,69.4724);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,2,4);  bi210_act_P1 = Activity(4860.55,69.1989);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,2,5);  bi210_act_P1 = Activity(6664.9,106.917);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,3,1);  bi210_act_P1 = Activity(3626.13,56.2159);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,3,2);  bi210_act_P1 = Activity(3626.13,55.5521);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,3,3);  bi210_act_P1 = Activity(6887.24,74.505);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,3,4);  bi210_act_P1 = Activity(5186.23,76.8932);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,3,5);  bi210_act_P1 = Activity(6838.32,112.896);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,4,1);  bi210_act_P1 = Activity(2703.62,52.8645);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,4,2);  bi210_act_P1 = Activity(2589.2,52.308);    add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,4,3);  bi210_act_P1 = Activity(5022.46,69.4524);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,4,4);  bi210_act_P1 = Activity(3847.9,72.914);    add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,4,5);  bi210_act_P1 = Activity(5147.94,106.675);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,5,1);  bi210_act_P1 = Activity(12983.9,92.3119);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,5,2);  bi210_act_P1 = Activity(13698.4,95.8623);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,5,3);  bi210_act_P1 = Activity(28442.8,137.178);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,5,4);  bi210_act_P1 = Activity(23170.4,128.297);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,5,5);  bi210_act_P1 = Activity(30878.3,205.837);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,6,1);  bi210_act_P1 = Activity(3320.07,51.096);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,6,2);  bi210_act_P1 = Activity(3182.82,51.8492);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,6,3);  bi210_act_P1 = Activity(6387.58,70.3071);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,6,4);  bi210_act_P1 = Activity(5876.85,75.6774);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,6,5);  bi210_act_P1 = Activity(7327.49,112.827);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,7,1);  bi210_act_P1 = Activity(5539.59,67.5545);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,7,2);  bi210_act_P1 = Activity(4727.74,59.5514);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,7,3);  bi210_act_P1 = Activity(8943.17,84.2042);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,7,4);  bi210_act_P1 = Activity(7268.85,85.8719);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,7,5);  bi210_act_P1 = Activity(9641.71,131.665);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,8,1);  bi210_act_P1 = Activity(3475.09,54.9395);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,8,2);  bi210_act_P1 = Activity(3048.57,51.5938);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,8,3);  bi210_act_P1 = Activity(6360.04,72.3494);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,8,4);  bi210_act_P1 = Activity(5035.35,74.6826);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,8,5);  bi210_act_P1 = Activity(6607.94,111.813);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,9,1);  bi210_act_P1 = Activity(2104.66,44.2998);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,9,2);  bi210_act_P1 = Activity(1718.55,42.1772);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,9,3);  bi210_act_P1 = Activity(3534.23,57.6146);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,9,4);  bi210_act_P1 = Activity(2827.76,63.4795);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,9,5);  bi210_act_P1 = Activity(3881.82,94.3114);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,10,1); bi210_act_P1 = Activity(3032.84,49.4306);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,10,2); bi210_act_P1 = Activity(3075.41,51.8547);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,10,3); bi210_act_P1 = Activity(6005.07,69.7629);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,10,4); bi210_act_P1 = Activity(4744.7,71.8768);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,10,5); bi210_act_P1 = Activity(5801.23,104.629);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,11,1); bi210_act_P1 = Activity(2314.75,45.1461);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,11,2); bi210_act_P1 = Activity(2305.8,46.9163);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,11,3); bi210_act_P1 = Activity(5104.19,66.056);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,11,4); bi210_act_P1 = Activity(3857.27,68.7245);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,11,5); bi210_act_P1 = Activity(5169.48,102.583);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,12,1); bi210_act_P1 = Activity(4942.48,62.1327);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,12,2); bi210_act_P1 = Activity(4661.96,61.6461);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,12,3); bi210_act_P1 = Activity(7935.49,79.3556);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,12,4); bi210_act_P1 = Activity(5828.89,78.5754);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,12,5); bi210_act_P1 = Activity(8066.94,122.633);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,13,1); bi210_act_P1 = Activity(15420,105.19);     add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,13,2); bi210_act_P1 = Activity(17130.2,110.544);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,13,3); bi210_act_P1 = Activity(34217,161.227);    add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,13,4); bi210_act_P1 = Activity(31357.7,156.556);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,13,5); bi210_act_P1 = Activity(38143.6,242.354);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,14,1); bi210_act_P1 = Activity(2306.89,44.2377);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,14,2); bi210_act_P1 = Activity(1986.34,43.6866);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,14,3); bi210_act_P1 = Activity(4007.84,57.6961);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,14,4); bi210_act_P1 = Activity(4141.13,66.7624);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,14,5); bi210_act_P1 = Activity(4513.13,94.2192);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,15,1); bi210_act_P1 = Activity(12637,90.2518);    add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,15,2); bi210_act_P1 = Activity(13290.6,93.5303);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,15,3); bi210_act_P1 = Activity(28202.6,135.748);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,15,4); bi210_act_P1 = Activity(24211.7,132.621);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,15,5); bi210_act_P1 = Activity(34741.5,221.773);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,16,1); bi210_act_P1 = Activity(17093.2,106.099);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,16,2); bi210_act_P1 = Activity(17992.8,107.928);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,16,3); bi210_act_P1 = Activity(40486.6,161.246);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,16,4); bi210_act_P1 = Activity(26350.3,137.435);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,16,5); bi210_act_P1 = Activity(35575.6,222.529);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,17,1); bi210_act_P1 = Activity(14548.2,96.8652);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,17,2); bi210_act_P1 = Activity(15456.3,100.524);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,17,3); bi210_act_P1 = Activity(32119.8,146.016);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,17,4); bi210_act_P1 = Activity(25919.6,136.449);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,17,5); bi210_act_P1 = Activity(23814.5,186.556);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,18,1); bi210_act_P1 = Activity(2492.4,47.1789);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,18,2); bi210_act_P1 = Activity(2249.51,47.2342);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,18,3); bi210_act_P1 = Activity(5308.42,67.7786);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,18,4); bi210_act_P1 = Activity(4688.42,71.7772);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,18,5); bi210_act_P1 = Activity(5768.91,106.028);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,19,1); bi210_act_P1 = Activity(4265.15,58.6267);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,19,2); bi210_act_P1 = Activity(4382.3,60.8973);   add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,19,3); bi210_act_P1 = Activity(7911.99,85.9338);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,19,4); bi210_act_P1 = Activity(6700.33,80.8181);  add_Bi210_P1(wire, bi210_act_P1);
  wire = WirePosition(1,19,5); bi210_act_P1 = Activity(8239.48,127.154);  add_Bi210_P1(wire, bi210_act_P1);

  // Vera did not measure layers 0 & 6-8, so set layer 0 to be the same as 1, and 6, 7 & 8 to be the same as layer 5.
  for(int sector = 0; sector < 20; sector++){
      wire = WirePosition(0,sector,0);  bi210_act_P1 = (activities_Bi210_P1.find(WirePosition(0,sector,1)))->second; add_Bi210_P1(wire,bi210_act_P1);
      wire = WirePosition(1,sector,0);  bi210_act_P1 = (activities_Bi210_P1.find(WirePosition(1,sector,1)))->second; add_Bi210_P1(wire,bi210_act_P1);
    for(int layer = 6; layer < 9; layer++){
      wire = WirePosition(0,sector,layer);  bi210_act_P1 = (activities_Bi210_P1.find(WirePosition(0,sector,5)))->second; add_Bi210_P1(wire,bi210_act_P1);
      wire = WirePosition(1,sector,layer);  bi210_act_P1 = (activities_Bi210_P1.find(WirePosition(1,sector,5)))->second; add_Bi210_P1(wire,bi210_act_P1);
    }
  }

  // SET BI-210 ACTIVITIES FOR PHASE 2
  wire = WirePosition(0,0,1);  bi210_act_P2 = Activity(5645.19,63.9858);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,0,2);  bi210_act_P2 = Activity(5503.75,64.0114);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,0,3);  bi210_act_P2 = Activity(8152.66,78.098);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,0,4);  bi210_act_P2 = Activity(6805.72,75.4183);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,0,5);  bi210_act_P2 = Activity(8451.27,134.732);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,1,1);  bi210_act_P2 = Activity(2157.7,41.4166);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,1,2);  bi210_act_P2 = Activity(1849.07,39.0786);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,1,3);  bi210_act_P2 = Activity(2441.79,44.664);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,1,4);  bi210_act_P2 = Activity(2323.02,50.0689);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,1,5);  bi210_act_P2 = Activity(2807.89,83.6337);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,2,1);  bi210_act_P2 = Activity(2553.13,47.2471);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,2,2);  bi210_act_P2 = Activity(2553.13,45.2023);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,2,3);  bi210_act_P2 = Activity(3597.57,53.5845);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,2,4);  bi210_act_P2 = Activity(3371.37,57.3782);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,2,5);  bi210_act_P2 = Activity(4202.37,100.322);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,3,1);  bi210_act_P2 = Activity(3208.06,49.7964);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,3,2);  bi210_act_P2 = Activity(3187.55,49.9136);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,3,3);  bi210_act_P2 = Activity(4934.7,62.4524);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,3,4);  bi210_act_P2 = Activity(4333.37,63.7667);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,3,5);  bi210_act_P2 = Activity(5185.16,108.525);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,4,1);  bi210_act_P2 = Activity(2353.69,43.1542);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,4,2);  bi210_act_P2 = Activity(2180.31,42.0806);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,4,3);  bi210_act_P2 = Activity(3231.56,51.0055);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,4,4);  bi210_act_P2 = Activity(2902.84,54.6614);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,4,5);  bi210_act_P2 = Activity(3339.65,90.0464);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,5,1);  bi210_act_P2 = Activity(11617,89.9148);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,5,2);  bi210_act_P2 = Activity(11700.2,90.7807);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,5,3);  bi210_act_P2 = Activity(22140.2,127.169);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,5,4);  bi210_act_P2 = Activity(19980.7,121.144);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,5,5);  bi210_act_P2 = Activity(27079.6,228.951);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,6,1);  bi210_act_P2 = Activity(3193.71,49.3658);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,6,2);  bi210_act_P2 = Activity(2789.2,46.788);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,6,3);  bi210_act_P2 = Activity(4190.17,57.647);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,6,4);  bi210_act_P2 = Activity(4003.27,61.535);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,6,5);  bi210_act_P2 = Activity(4885.36,106.774);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,7,1);  bi210_act_P2 = Activity(4362.76,56.9666);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,7,2);  bi210_act_P2 = Activity(4294.4,57.289);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,7,3);  bi210_act_P2 = Activity(6146.73,68.7086);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,7,4);  bi210_act_P2 = Activity(5386.64,71.0341);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,7,5);  bi210_act_P2 = Activity(7246.95,130.268);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,8,1);  bi210_act_P2 = Activity(3035.5,47.8295);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,8,2);  bi210_act_P2 = Activity(2742.46,46.6823);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,8,3);  bi210_act_P2 = Activity(4201.74,57.9409);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,8,4);  bi210_act_P2 = Activity(4062.05,61.1004);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,8,5);  bi210_act_P2 = Activity(5083.54,106.929);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,9,1);  bi210_act_P2 = Activity(1752.09,37.896);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,9,2);  bi210_act_P2 = Activity(1654.98,37.6596);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,9,3);  bi210_act_P2 = Activity(2247.85,43.785);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,9,4);  bi210_act_P2 = Activity(2184.03,50.1916);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,9,5);  bi210_act_P2 = Activity(2841.65,89.1308);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,10,1); bi210_act_P2 = Activity(2601.12,45.3956);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,10,2); bi210_act_P2 = Activity(2409.46,44.3403);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,10,3); bi210_act_P2 = Activity(4022.25,57.0324);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,10,4); bi210_act_P2 = Activity(3790.9,61.1821);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,10,5); bi210_act_P2 = Activity(4689.89,106.733);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,11,1); bi210_act_P2 = Activity(1904.98,39.6464);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,11,2); bi210_act_P2 = Activity(1807.44,38.7524);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,11,3); bi210_act_P2 = Activity(2963.52,49.2519);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,11,4); bi210_act_P2 = Activity(3005.39,55.0001);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,11,5); bi210_act_P2 = Activity(3650.59,94.8883);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,12,1); bi210_act_P2 = Activity(3984.94,56.3753);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,12,2); bi210_act_P2 = Activity(3913.8,56.8269);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,12,3); bi210_act_P2 = Activity(5412.73,68.326);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,12,4); bi210_act_P2 = Activity(4753.85,66.0855);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,12,5); bi210_act_P2 = Activity(6073.82,122.749);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,13,1); bi210_act_P2 = Activity(16220,115.132);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,13,2); bi210_act_P2 = Activity(16773,120.193);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,13,3); bi210_act_P2 = Activity(31562.2,167.606);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,13,4); bi210_act_P2 = Activity(24944.2,178.979);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,13,5); bi210_act_P2 = Activity(29215.1,234.112);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,14,1); bi210_act_P2 = Activity(2012.94,40.4018);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,14,2); bi210_act_P2 = Activity(2110.61,41.2748);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,14,3); bi210_act_P2 = Activity(3073.43,50.2681);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,14,4); bi210_act_P2 = Activity(2597.41,52.4624);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,14,5); bi210_act_P2 = Activity(2595.78,80.7664);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,15,1); bi210_act_P2 = Activity(12336.8,93.2811);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,15,2); bi210_act_P2 = Activity(12269.8,94.304);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,15,3); bi210_act_P2 = Activity(24137.8,132.779);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,15,4); bi210_act_P2 = Activity(20835.2,126.3);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,15,5); bi210_act_P2 = Activity(21432.1,210.084);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,16,1); bi210_act_P2 = Activity(17754.1,111.863);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,16,2); bi210_act_P2 = Activity(17481.8,112.507);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,16,3); bi210_act_P2 = Activity(27541.3,142.248);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,16,4); bi210_act_P2 = Activity(27880.4,145);      add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,16,5); bi210_act_P2 = Activity(33931.2,265.648);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,17,1); bi210_act_P2 = Activity(13920.9,101.29);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,17,2); bi210_act_P2 = Activity(13992.1,102.404);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,17,3); bi210_act_P2 = Activity(24266.5,140.905);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,17,4); bi210_act_P2 = Activity(25651.4,142.134);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,17,5); bi210_act_P2 = Activity(29951.5,263.419);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,18,1); bi210_act_P2 = Activity(2365.45,44.229);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,18,2); bi210_act_P2 = Activity(2208.8,43.0625);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,18,3); bi210_act_P2 = Activity(3671.91,54.91);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,18,4); bi210_act_P2 = Activity(4539.57,65.7774);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,18,5); bi210_act_P2 = Activity(4297.69,101.65);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,19,1); bi210_act_P2 = Activity(3480.18,52.1396);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,19,2); bi210_act_P2 = Activity(3539.63,52.7141);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,19,3); bi210_act_P2 = Activity(5047.6,63.1088);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,19,4); bi210_act_P2 = Activity(4670.8,65.7341);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(0,19,5); bi210_act_P2 = Activity(4869.6,105.52);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,0,1);  bi210_act_P2 = Activity(6023.37,60.4504);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,0,2);  bi210_act_P2 = Activity(5832.4,60.2718);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,0,3);  bi210_act_P2 = Activity(10064.6,80.9746);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,0,4);  bi210_act_P2 = Activity(7555.77,74.2529);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,0,5);  bi210_act_P2 = Activity(10037.7,115.085);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,1,1);  bi210_act_P2 = Activity(2043.64,34.3486);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,1,2);  bi210_act_P2 = Activity(2121.16,35.5873);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,1,3);  bi210_act_P2 = Activity(3938.41,48.2715);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,1,4);  bi210_act_P2 = Activity(3213.6,49.8813);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,1,5);  bi210_act_P2 = Activity(3996.61,71.8912);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,2,1);  bi210_act_P2 = Activity(2963.7,38.179);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,2,2);  bi210_act_P2 = Activity(3193.27,40.0395);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,2,3);  bi210_act_P2 = Activity(5396.9,52.0612);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,2,4);  bi210_act_P2 = Activity(4054.18,50.214);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,2,5);  bi210_act_P2 = Activity(5415.01,76.9026);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,3,1);  bi210_act_P2 = Activity(3414.52,44.2221);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,3,2);  bi210_act_P2 = Activity(3414.92,42.4406);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,3,3);  bi210_act_P2 = Activity(5995.46,56.359);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,3,4);  bi210_act_P2 = Activity(4407.2,56.4541);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,3,5);  bi210_act_P2 = Activity(5729.2,83.1609);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,4,1);  bi210_act_P2 = Activity(2465.46,40.9512);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,4,2);  bi210_act_P2 = Activity(2590.94,40.1211);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,4,3);  bi210_act_P2 = Activity(4366.89,52.5919);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,4,4);  bi210_act_P2 = Activity(3119.19,53.8451);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,4,5);  bi210_act_P2 = Activity(4245.9,78.8);      add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,5,1);  bi210_act_P2 = Activity(12063.5,77.0229);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,5,2);  bi210_act_P2 = Activity(12857.5,78.5632);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,5,3);  bi210_act_P2 = Activity(26079.7,113.325);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,5,4);  bi210_act_P2 = Activity(20987.9,104.217);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,5,5);  bi210_act_P2 = Activity(27931.2,167.978);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,6,1);  bi210_act_P2 = Activity(3150.73,39.7226);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,6,2);  bi210_act_P2 = Activity(3244,40.5607);     add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,6,3);  bi210_act_P2 = Activity(5522.56,52.9031);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,6,4);  bi210_act_P2 = Activity(5187.67,56.9926);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,6,5);  bi210_act_P2 = Activity(6330.72,84.8462);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,7,1);  bi210_act_P2 = Activity(5053.7,54.0645);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,7,2);  bi210_act_P2 = Activity(4515.73,47.763);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,7,3);  bi210_act_P2 = Activity(7967.68,66.6736);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,7,4);  bi210_act_P2 = Activity(6199.05,67.0119);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,7,5);  bi210_act_P2 = Activity(8170.63,103.251);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,8,1);  bi210_act_P2 = Activity(3232.65,42.6858);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,8,2);  bi210_act_P2 = Activity(2923.04,39.2933);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,8,3);  bi210_act_P2 = Activity(5594.35,54.8345);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,8,4);  bi210_act_P2 = Activity(4342.81,54.2937);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,8,5);  bi210_act_P2 = Activity(5575.89,81.9054);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,9,1);  bi210_act_P2 = Activity(1952.35,31.69);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,9,2);  bi210_act_P2 = Activity(1771.97,30.9672);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,9,3);  bi210_act_P2 = Activity(2863.83,39.4166);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,9,4);  bi210_act_P2 = Activity(2167.22,42.7188);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,9,5);  bi210_act_P2 = Activity(3144.57,65.4069);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,10,1); bi210_act_P2 = Activity(2823.5,37.1788);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,10,2); bi210_act_P2 = Activity(2983.65,38.9472);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,10,3); bi210_act_P2 = Activity(5255.85,51.7026);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,10,4); bi210_act_P2 = Activity(3684.53,49.8137);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,10,5); bi210_act_P2 = Activity(4722.45,74.5578);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,11,1); bi210_act_P2 = Activity(2086.37,33.4732);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,11,2); bi210_act_P2 = Activity(2183.29,34.6378);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,11,3); bi210_act_P2 = Activity(4309.57,48.3868);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,11,4); bi210_act_P2 = Activity(3108.52,49.1407);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,11,5); bi210_act_P2 = Activity(4291.09,75.3008);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,12,1); bi210_act_P2 = Activity(4585.04,50.2371);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,12,2); bi210_act_P2 = Activity(4500.51,49.994);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,12,3); bi210_act_P2 = Activity(6977.15,62.7315);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,12,4); bi210_act_P2 = Activity(5260.71,61.2944);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,12,5); bi210_act_P2 = Activity(6612.95,93.0939);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,13,1); bi210_act_P2 = Activity(14305.8,99.7792);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,13,2); bi210_act_P2 = Activity(17786,110.766);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,13,3); bi210_act_P2 = Activity(33067.3,166.632);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,13,4); bi210_act_P2 = Activity(28881.3,146.473);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,13,5); bi210_act_P2 = Activity(29937.1,174.61);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,14,1); bi210_act_P2 = Activity(2199.49,34.9307);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,14,2); bi210_act_P2 = Activity(2069.32,34.2053);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,14,3); bi210_act_P2 = Activity(3349.39,43.322);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,14,4); bi210_act_P2 = Activity(3499.9,50.3927);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,14,5); bi210_act_P2 = Activity(3796.24,69.4442);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,15,1); bi210_act_P2 = Activity(11993.6,75.7022);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,15,2); bi210_act_P2 = Activity(12753.1,78.0053);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,15,3); bi210_act_P2 = Activity(26444.8,113.19);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,15,4); bi210_act_P2 = Activity(22566.5,108.689);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,15,5); bi210_act_P2 = Activity(30839.9,178.922);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,16,1); bi210_act_P2 = Activity(16596.9,89.7481);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,16,2); bi210_act_P2 = Activity(17105,89.4563);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,16,3); bi210_act_P2 = Activity(37791.4,134.07);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,16,4); bi210_act_P2 = Activity(24800.8,113.327);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,16,5); bi210_act_P2 = Activity(32484.9,182.392);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,17,1); bi210_act_P2 = Activity(13688.4,81.3217);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,17,2); bi210_act_P2 = Activity(15010.7,85.287);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,17,3); bi210_act_P2 = Activity(30565.3,124.046);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,17,4); bi210_act_P2 = Activity(24672.6,115.262);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,17,5); bi210_act_P2 = Activity(22382.4,155.949);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,18,1); bi210_act_P2 = Activity(2433.76,37.1511);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,18,2); bi210_act_P2 = Activity(2341.7,36.9505);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,18,3); bi210_act_P2 = Activity(4490.12,50.4773);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,18,4); bi210_act_P2 = Activity(3823.04,52.6349);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,18,5); bi210_act_P2 = Activity(4707.21,77.3807);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,19,1); bi210_act_P2 = Activity(4205.4,49.538);    add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,19,2); bi210_act_P2 = Activity(4234.44,50.0649);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,19,3); bi210_act_P2 = Activity(7487.24,67.2033);  add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,19,4); bi210_act_P2 = Activity(5913.06,68.354);   add_Bi210_P2(wire, bi210_act_P2);
  wire = WirePosition(1,19,5); bi210_act_P2 = Activity(7413.17,104.348);  add_Bi210_P2(wire, bi210_act_P2);

  // Vera did not measure layers 0 & 6-8, so set layer 0 to be the same as 1, and 6, 7 & 8 to be the same as layer 5.
  for(int sector = 0; sector < 20; sector++){
      wire = WirePosition(0,sector,0);  bi210_act_P2 = (activities_Bi210_P2.find(WirePosition(0,sector,1)))->second; add_Bi210_P2(wire,bi210_act_P2);
      wire = WirePosition(1,sector,0);  bi210_act_P2 = (activities_Bi210_P2.find(WirePosition(1,sector,1)))->second; add_Bi210_P2(wire,bi210_act_P2);
    for(int layer = 6; layer < 9; layer++){
      wire = WirePosition(0,sector,layer);  bi210_act_P2 = (activities_Bi210_P2.find(WirePosition(0,sector,5)))->second; add_Bi210_P2(wire,bi210_act_P2);
      wire = WirePosition(1,sector,layer);  bi210_act_P2 = (activities_Bi210_P2.find(WirePosition(1,sector,5)))->second; add_Bi210_P2(wire,bi210_act_P2);
    }
  }

  // Get total activity for 214 and 210 for both phases to divide weights by.  Calculate this using different numbers of 
  // wires in each layer.
  total_Rn_Act_P1 = 0; 
  total_Rn_Act_P2 = 0; 
  total_Bi210_Act_P1 = 0; 
  total_Bi210_Act_P2 = 0; 

  // Inner side first:
  for(int sector = 0; sector < 20; sector++){
    for(int layer = 0; layer < 4; layer++){
      total_Rn_Act_P1    += 16.0*(activities_Rn_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 16.0*(activities_Rn_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 16.0*(activities_Bi210_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 16.0*(activities_Bi210_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
    }
    for(int layer = 4; layer < 6; layer++){
      total_Rn_Act_P1    += 14.0*(activities_Rn_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 14.0*(activities_Rn_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 14.0*(activities_Bi210_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 14.0*(activities_Bi210_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
    }
    for(int layer = 6; layer < 9; layer++){
      total_Rn_Act_P1    += 12.0*(activities_Rn_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 12.0*(activities_Rn_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 12.0*(activities_Bi210_P1.find(WirePosition(0,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 12.0*(activities_Bi210_P2.find(WirePosition(0,sector,layer))->second.act)/6180.0;
    }
  }

  // Then outer side:
  for(int sector = 0; sector < 20; sector++){
    for(int layer = 0; layer < 4; layer++){
      total_Rn_Act_P1    += 18.0*(activities_Rn_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 18.0*(activities_Rn_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 18.0*(activities_Bi210_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 18.0*(activities_Bi210_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
    }
    for(int layer = 4; layer < 6; layer++){
      total_Rn_Act_P1    += 20.0*(activities_Rn_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 20.0*(activities_Rn_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 20.0*(activities_Bi210_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 20.0*(activities_Bi210_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
    }
    for(int layer = 6; layer < 9; layer++){
      total_Rn_Act_P1    += 23.0*(activities_Rn_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Rn_Act_P2    += 23.0*(activities_Rn_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P1 += 23.0*(activities_Bi210_P1.find(WirePosition(1,sector,layer))->second.act)/6180.0;
      total_Bi210_Act_P2 += 23.0*(activities_Bi210_P2.find(WirePosition(1,sector,layer))->second.act)/6180.0;
    }
  }

  std::cout << "-------- RadonWeigth - Initializing radon map ----------------------------------------------\n"
	    << "- total Rn activity in phase 1: " << total_Rn_Act_P1 << "\n"
	    << "- total RN activity in phase 2: " << total_Rn_Act_P2 << "\n"
	    << "- total Bi210 activity in phase 1: " << total_Bi210_Act_P1 << "\n" 
	    << "- total Bi210 activity in phase 2: " << total_Bi210_Act_P2 << "\n" 
	    << "--------------------------------------------------------------------------------------------\n"
	    << std::endl;
  RandomNumGen = new TRandom3(12345);  
}

RadonWeight::~RadonWeight() {
  activities_Rn_P1.clear();
  activities_Rn_P2.clear();
  activities_Bi210_P1.clear();
  activities_Bi210_P2.clear();
}

void RadonWeight::add_Rn_P1(WirePosition &aWirePosition, Activity &anActivity) {
  if (activities_Rn_P1.find(aWirePosition) == activities_Rn_P1.end()) {
    activities_Rn_P1.insert(std::pair<WirePosition, Activity>(aWirePosition, anActivity));
  }
}

void RadonWeight::add_Rn_P2(WirePosition &aWirePosition, Activity &anActivity) {
  if (activities_Rn_P2.find(aWirePosition) == activities_Rn_P2.end()) {
    activities_Rn_P2.insert(std::pair<WirePosition, Activity>(aWirePosition, anActivity));
  }
}

void RadonWeight::add_Bi210_P1(WirePosition &aWirePosition, Activity &anActivity) {
  if (activities_Bi210_P1.find(aWirePosition) == activities_Bi210_P1.end()) {
    activities_Bi210_P1.insert(std::pair<WirePosition, Activity>(aWirePosition, anActivity));
  }
}

void RadonWeight::add_Bi210_P2(WirePosition &aWirePosition, Activity &anActivity) {
  if (activities_Bi210_P2.find(aWirePosition) == activities_Bi210_P2.end()) {
    activities_Bi210_P2.insert(std::pair<WirePosition, Activity>(aWirePosition, anActivity));
  }
}

WirePosition RadonWeight::getWirePosition(CLHEP::Hep3Vector trueVertex) const {

  // Set positions to 100 so that you can see test whether it's not found
  int layer = 100;
  int side  = 100;
  int sector = 100;

  // Layer and side definition ported straight from vtx2wire.C in rootana
  double R = sqrt(trueVertex.x()*trueVertex.x() + trueVertex.y()*trueVertex.y());
  if(R > 150.9 && R < 155.0){layer=0; side=0;}
  if(R > 148.1 && R < 150.9){layer=1; side=0;}
  if(R > 145.3 && R < 148.1){layer=2; side=0;}
  if(R > 142.1 && R < 145.3){layer=3; side=0;}
  if(R > 125.9 && R < 128.6){layer=4; side=0;}
  if(R > 122.7 && R < 125.9){layer=5; side=0;}
  if(R > 106.5 && R < 109.3){layer=6; side=0;}
  if(R > 103.7 && R < 106.5){layer=7; side=0;}
  if(R > 100.5 && R < 103.7){layer=8; side=0;}

  if(R >= 155.0 && R < 159.0){layer=0; side=1;}
  if(R >= 159.0 && R < 161.8){layer=1; side=1;}
  if(R >= 161.8 && R < 164.6){layer=2; side=1;}
  if(R >= 164.6 && R < 168.0){layer=3; side=1;}
  if(R >= 181.2 && R < 184.1){layer=4; side=1;}
  if(R >= 184.1 && R < 187.3){layer=5; side=1;}
  if(R >= 200.7 && R < 203.5){layer=6; side=1;}
  if(R >= 203.5 && R < 206.3){layer=7; side=1;}
  if(R >= 206.3 && R < 209.1){layer=8; side=1;}

  SectorData sectorfinder;
  sector = (int)(sectorfinder.sectorNumber(trueVertex));

  WirePosition wire(side,sector,layer);
  return wire;
}

WirePosition RadonWeight::getWirePosition(double x, double y, double z) const {
  return getWirePosition(CLHEP::Hep3Vector(x,y,z));
}

double RadonWeight::getRadonWeight(CLHEP::Hep3Vector trueVertex) const{

  WirePosition wire = getWirePosition(trueVertex);

  if(wire.side == 100 or wire.sector == 100 or wire.layer == 100) return 0.0;

  double activity, activity_err;

  // Get weights by dividing by total SWire activity.
  if (AbsEnv::instance()->runNumber() < 3396){
    activity     = ((activities_Rn_P1.find(wire))->second.act)/total_Rn_Act_P1;
    activity_err = ((activities_Rn_P1.find(wire))->second.act_error)/total_Rn_Act_P1;
  } else {
    activity     = ((activities_Rn_P2.find(wire))->second.act)/total_Rn_Act_P2;
    activity_err = ((activities_Rn_P2.find(wire))->second.act_error)/total_Rn_Act_P2;
  }

  double weight = RandomNumGen->Gaus(activity,activity_err);
  while (weight < 0){weight = RandomNumGen->Gaus(activity,activity_err);}

  return weight;
}

double RadonWeight::getBi210Weight(CLHEP::Hep3Vector trueVertex) const{

  WirePosition wire = getWirePosition(trueVertex);

  if(wire.side == 100 or wire.sector == 100 or wire.layer == 100) return 0.0;

  double activity, activity_err;

  // Get weights by dividing by total SWire activity.
  if (AbsEnv::instance()->runNumber() < 3396){
    activity     = ((activities_Bi210_P1.find(wire))->second.act)/total_Bi210_Act_P1;
    activity_err = ((activities_Bi210_P1.find(wire))->second.act_error)/total_Bi210_Act_P1;
  } else {
    activity     = ((activities_Bi210_P2.find(wire))->second.act)/total_Bi210_Act_P2;
    activity_err = ((activities_Bi210_P2.find(wire))->second.act_error)/total_Bi210_Act_P2;
  }

  double weight = RandomNumGen->Gaus(activity,activity_err);
  while (weight < 0){weight = RandomNumGen->Gaus(activity,activity_err);}

  return weight;
}
