//
//  SFoilSide.cpp
//
//  Created by James Mott on 29/01/13.
//
//  This module calculates the side of the foil (inner/outer) that the SFoil MC has been generated on.
//
//  NOTE:
//  There have been some problems trying to implement an algorithm for sectors 1-5 inclusive, so at the 
//  moment it is implemented only for sectors 6 and above.
//  Sector 5 may have different widths and not necessarily correspond to strips like the other sectors.
//  Sectors 1-4 (MoMet) seem to have three stripes in the MC. One on inner, one on outer and what looks
//  like one in the middle of the foil.  This needs to be investigated before using this module.
//
//  24/4/2013 - Stefano Torre 
//  adding the position of hte strips as defined in the NEMO3 geometry files  

#include "NemoUtils/SFoilSide.h"

#include "CLHEP/Vector/TwoVector.h"

#include <iomanip>

void   SFoilSide::createStripsDictionary() {
  std::vector<FoilStrip> strips;
  //                         id  mat vertex                                      radius       angle        min vtx num  max vtx num  min z    max z   inn radius   out radius 
  strips.push_back(FoilStrip(111, 64, CLHEP::Hep3Vector(154.864, 6.491 , -0.15), 0.041887902, 154.9999728, 0.068659091,	0.198018873, -124.25, 123.95, 154.996818 , 155.0031276));
  strips.push_back(FoilStrip(121, 64, CLHEP::Hep3Vector(154.46 , 12.928, -0.3 ), 0.083496551, 155.0000799, 0.199067049,	0.332532215, -125.15, 124.55, 154.9969374, 155.0032225));
  strips.push_back(FoilStrip(131, 64, CLHEP::Hep3Vector(153.776, 19.442, -0.15), 0.125768426, 155.0001598, 0.333584749,	0.467049845, -125   , 124.7 , 154.9970276, 155.003292 ));
  strips.push_back(FoilStrip(141, 64, CLHEP::Hep3Vector(152.817, 25.921, -0.15), 0.168022847, 154.9997862, 0.468097786,	0.601563204, -125   , 124.7 , 154.9966643, 155.0029081));
  strips.push_back(FoilStrip(151, 64, CLHEP::Hep3Vector(151.586, 32.353, -0.15), 0.210277268, 155.0001032, 0.60259368 ,	0.736058825, -125   , 124.7 , 154.9969607, 155.0032458));
  strips.push_back(FoilStrip(161, 64, CLHEP::Hep3Vector(150.084, 38.728, -0.15), 0.252531689, 155.0002098, 0.737105991,	0.870571045, -125   , 124.7 , 154.9970535, 155.0033661));
  strips.push_back(FoilStrip(171, 64, CLHEP::Hep3Vector(148.343, 44.938, -0.15), 0.294140339, 155.0002242, 0.871614436,	1.000974008, -124.25, 123.95, 154.9970622, 155.0033861));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(0, strips));
  strips.clear();

  //                         id  mat vertex                                                   angle        min vtx num  max vtx num  min z    max z   inn radius   out radius
  strips.push_back(FoilStrip(211, 41, CLHEP::Hep3Vector(145.2766627, 54.02813077, 99.55    ), 0.356047167, 154.9978956 ,1.068656891 ,1.198018407, 75.8	   , 123.3   , 154.9954019, 155.0003893));
  strips.push_back(FoilStrip(212, 41, CLHEP::Hep3Vector(145.2812602, 54.02984054, 28.4375  ), 0.356047167, 155.0028007 ,1.068658937 ,1.19801636	, -19.8625 , 76.7375 , 155.0003893, 155.0052121));
  strips.push_back(FoilStrip(213, 41, CLHEP::Hep3Vector(145.2767103, 54.02814847, -52.925  ), 0.356047167, 154.9979464 ,1.068656912 ,1.198018386, -86.925  , -18.925 , 154.9955035, 155.0003893));
  strips.push_back(FoilStrip(214, 41, CLHEP::Hep3Vector(145.2812561, 54.02983903, -96.4875 ), 0.356047167, 155.0027964 ,1.068658936 ,1.198016362, -106.9875, -85.9875, 155.0003893, 155.0052034));
  strips.push_back(FoilStrip(215, 41, CLHEP::Hep3Vector(145.2765995, 54.02810725, -114.625 ), 0.356047167, 154.9978281 ,1.068656863 ,1.198018435, -123.2   , -106.05 , 154.995267 , 155.0003893));
  strips.push_back(FoilStrip(221, 41, CLHEP::Hep3Vector(142.9027438, 60.02505234, 101	   ), 0.397655817, 154.9974229 ,1.199067192 ,1.332534644, 78.45	   , 123.55  , 154.9949758, 154.99987  ));
  strips.push_back(FoilStrip(222, 41, CLHEP::Hep3Vector(142.9073144, 60.02697213, 31.9625  ), 0.397655817, 155.0023803 ,1.199069325 ,1.33253251	, -15.5125 , 79.4375 , 154.99987  , 155.0048906));
  strips.push_back(FoilStrip(223, 41, CLHEP::Hep3Vector(142.9026942, 60.02503151, -46.525  ), 0.397655817, 154.9973691 ,1.199067169 ,1.332534667, -78.525  , -14.525 , 154.9948682, 154.99987  ));
  strips.push_back(FoilStrip(224, 41, CLHEP::Hep3Vector(142.9073533, 60.02698848, -93.7375 ), 0.397655817, 155.0024225 ,1.199069343 ,1.332532492, -109.9375, -77.5375, 154.99987  , 155.004975 ));
  strips.push_back(FoilStrip(225, 41, CLHEP::Hep3Vector(142.9027554, 60.0250572 , -116.1   ), 0.397655817, 154.9974355 ,1.199067197 ,1.332534639, -123.25  , -108.95 , 154.9950009, 154.99987  ));
  strips.push_back(FoilStrip(231, 41, CLHEP::Hep3Vector(140.2397452, 66.0079387 , 112.95   ), 0.439927691, 154.9975294 ,1.333565931 ,1.467033292, 102.4	   , 123.5   , 154.9950373, 155.0000214));
  strips.push_back(FoilStrip(232, 41, CLHEP::Hep3Vector(140.2442107, 66.01004055, 71.7375  ), 0.439927691, 155.0024648 ,1.333568056 ,1.467031168, 40.0625  , 103.4125, 155.0000214, 155.0049081));
  strips.push_back(FoilStrip(233, 41, CLHEP::Hep3Vector(140.2396773, 66.00790672, -21.175  ), 0.439927691, 154.9974543 ,1.333565898 ,1.467033324, -83.425  , 41.075  , 154.9948871, 155.0000214));
  strips.push_back(FoilStrip(234, 41, CLHEP::Hep3Vector(140.2440242, 66.00995277, -97.8125 ), 0.439927691, 155.0022586 ,1.333567967 ,1.467031257, -113.2125, -82.4125, 155.0000214, 155.0044958));
  strips.push_back(FoilStrip(235, 41, CLHEP::Hep3Vector(140.2397687, 66.00794972, -117.75  ), 0.439927691, 154.9975553 ,1.333565942 ,1.46703328	, -123.3   , -112.2  , 154.9950891, 155.0000214));
  strips.push_back(FoilStrip(241, 41, CLHEP::Hep3Vector(137.325773 , 71.87383444, 106.7	   ), 0.482182112, 154.997471  ,1.468085711 ,1.601553122, 89.2	   , 124.2   , 154.9949575, 154.9999845));
  strips.push_back(FoilStrip(242, 41, CLHEP::Hep3Vector(137.3301796, 71.87614076, 31.475   ), 0.482182112, 155.0024446 ,1.468087852 ,1.601550982, -27.275  , 90.225  , 154.9999845, 155.0049047));
  strips.push_back(FoilStrip(243, 41, CLHEP::Hep3Vector(137.3257151, 71.87380409, -61.3	   ), 0.482182112, 154.9974056 ,1.468085683 ,1.60155315	, -96.35   , -26.25  , 154.9948266, 154.9999845));
  strips.push_back(FoilStrip(244, 41, CLHEP::Hep3Vector(137.3301497, 71.87612514, -106.875 ), 0.482182112, 155.0024109 ,1.468087837 ,1.601550996, -118.425 , -95.325 , 154.9999845, 155.0048373));
  strips.push_back(FoilStrip(245, 41, CLHEP::Hep3Vector(137.3257502, 71.87382251, -120.6   ), 0.482182112, 154.9974453 ,1.4680857   ,1.601553133, -123.8   , -117.4  , 154.994906 , 154.9999845));
  strips.push_back(FoilStrip(251, 41, CLHEP::Hep3Vector(134.1669519, 77.61081523, 109.45   ), 0.524436534, 154.9974504 ,1.602591637 ,1.736059065, 94.95	   , 123.95  , 154.9950843, 154.9998165));
  strips.push_back(FoilStrip(252, 41, CLHEP::Hep3Vector(134.1712725, 77.61331454, 57.8875  ), 0.524436534, 155.0024417 ,1.602593785 ,1.736056917, 19.8375  , 95.9375 , 154.9998165, 155.005067 ));
  strips.push_back(FoilStrip(253, 41, CLHEP::Hep3Vector(134.1668364, 77.61074841, -15.05   ), 0.524436534, 154.9973169 ,1.602591579 ,1.736059123, -50.925  , 20.825  , 154.9948174, 154.9998165));
  strips.push_back(FoilStrip(254, 41, CLHEP::Hep3Vector(134.1712512, 77.61330223, -80.7375 ), 0.524436534, 155.0024172 ,1.602593775 ,1.736056928, -111.5375, -49.9375, 154.9998165, 155.0050178));
  strips.push_back(FoilStrip(255, 41, CLHEP::Hep3Vector(134.1669239, 77.61079905, -117.1   ), 0.524436534, 154.997418  ,1.602591623 ,1.736059079, -123.65  , -110.55 , 154.9950196, 154.9998165));
  strips.push_back(FoilStrip(261, 47, CLHEP::Hep3Vector(130.77     , 83.211     , 0.55     ), 0.566690955, 154.9995594 ,1.738140007 ,1.869552891, -121.2   , 122.3   , 154.9899225, 155.0091964));
  strips.push_back(FoilStrip(271, 47, CLHEP::Hep3Vector(127.196    , 88.579     , -0.1     ), 0.608299604, 155.0001989 ,1.871612641 ,2.000972235, -121.6   , 121.4   , 154.9923034, 155.0080944));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(1, strips));
  strips.clear();

  strips.push_back(FoilStrip(311, 42, CLHEP::Hep3Vector(121.4699906, 96.2764074 , 119.2  ), 0.670206433, 154.9971137, 2.068659961, 2.198022129, 114.45 , 123.95, 154.9945497, 154.9996776));
  strips.push_back(FoilStrip(312, 42, CLHEP::Hep3Vector(121.4741057, 96.27966896, 97.4   ), 0.670206433, 155.0023645, 2.068662151, 2.198019938, 79.35  , 115.45, 154.9996776, 155.0050514));
  strips.push_back(FoilStrip(313, 42, CLHEP::Hep3Vector(121.4701274, 96.27651576, 52.9   ), 0.670206433, 154.9972881, 2.068660034, 2.198022056, 25.45  , 80.35 , 154.9948986, 154.9996776));
  strips.push_back(FoilStrip(314, 42, CLHEP::Hep3Vector(121.4741019, 96.27966597, -28.7  ), 0.670206433, 155.0023597, 2.068662149, 2.19801994 , -83.85 , 26.45 , 154.9996776, 155.0050418));
  strips.push_back(FoilStrip(315, 42, CLHEP::Hep3Vector(121.4697701, 96.27623259, -103.4 ), 0.670206433, 154.9968322, 2.068659844, 2.198022247, -123.95, -82.85, 154.9939869, 154.9996776));
  strips.push_back(FoilStrip(321, 42, CLHEP::Hep3Vector(117.3598441, 101.2461401, 121.4  ), 0.711815082, 154.9971416, 2.199059756, 2.332527451, 117.95 , 124.85, 154.9942943, 154.9999889));
  strips.push_back(FoilStrip(322, 42, CLHEP::Hep3Vector(117.3642636, 101.2499528, 71.45  ), 0.711815082, 155.0029784, 2.199062268, 2.332524938, 23.95  , 118.95, 154.9999889, 155.0059678));
  strips.push_back(FoilStrip(323, 42, CLHEP::Hep3Vector(117.3598685, 101.2461612, -25.75 ), 0.711815082, 154.9971738, 2.19905977 , 2.332527437, -76.45 , 24.95 , 154.9943588, 154.9999889));
  strips.push_back(FoilStrip(324, 42, CLHEP::Hep3Vector(117.3641101, 101.2498204, -100.15), 0.711815082, 155.0027756, 2.199062181, 2.332525026, -124.85, -75.45, 154.9999889, 155.0055624));
  strips.push_back(FoilStrip(331, 43, CLHEP::Hep3Vector(112.9782217, 106.1143297, 111.8  ), 0.754086957, 154.9978372, 2.333576605, 2.467043701, 98.7   , 124.9 , 154.9953974, 155.000277 ));
  strips.push_back(FoilStrip(332, 43, CLHEP::Hep3Vector(112.9819414, 106.1178235, 39.85  ), 0.754086957, 155.0029404, 2.333578802, 2.467041505, -20    , 99.7  , 155.000277 , 155.0056039));
  strips.push_back(FoilStrip(333, 43, CLHEP::Hep3Vector(112.9781564, 106.1142683, -72    ), 0.754086957, 154.9977476, 2.333576566, 2.467043739, -125   , -19   , 154.9952183, 155.000277 ));
  strips.push_back(FoilStrip(341, 43, CLHEP::Hep3Vector(108.3943565, 110.7923201, 114.25 ), 0.796341378, 154.9976604, 2.46808898 , 2.601556228, 104.2  , 124.3 , 154.9953103, 155.0000105));
  strips.push_back(FoilStrip(342, 43, CLHEP::Hep3Vector(108.3978437, 110.7958845, 46.2   ), 0.796341378, 155.0026468, 2.468091126, 2.601554082, -12.8  , 105.2 , 155.0000105, 155.0052832));
  strips.push_back(FoilStrip(343, 43, CLHEP::Hep3Vector(108.394198 , 110.7921581, -68    ), 0.796341378, 154.9974337, 2.468088882, 2.601556325, -124.2 , -11.8 , 154.9948568, 155.0000105));
  strips.push_back(FoilStrip(351, 43, CLHEP::Hep3Vector(103.6173579, 115.2721732, 100.65 ), 0.838595799, 154.9975186, 2.602591134, 2.736058504, 76.95  , 124.35, 154.9950622, 154.999975 ));
  strips.push_back(FoilStrip(352, 43, CLHEP::Hep3Vector(103.6207399, 115.2759356, 26.9   ), 0.838595799, 155.0025776, 2.602593311, 2.736056327, -24.15 , 77.95 , 154.999975 , 155.0051802));
  strips.push_back(FoilStrip(353, 43, CLHEP::Hep3Vector(103.6172751, 115.2720811, -73.65 ), 0.838595799, 154.9973948, 2.60259108 , 2.736058557, -124.15, -23.15, 154.9948146, 154.999975 ));
  strips.push_back(FoilStrip(361, 43, CLHEP::Hep3Vector(98.65444272, 119.5471129, 101.45 ), 0.88085022 , 154.9974557, 2.737119814, 2.870587238, 79.25  , 123.65, 154.9950091, 154.9999024));
  strips.push_back(FoilStrip(362, 43, CLHEP::Hep3Vector(98.65760077, 119.5509398, 26.1   ), 0.88085022 , 155.0024174, 2.737121949, 2.870585102, -28.05 , 80.25 , 154.9999024, 155.0049323));
  strips.push_back(FoilStrip(363, 43, CLHEP::Hep3Vector(98.65428892, 119.5469266, -75.6  ), 0.88085022 , 154.9972141, 2.73711971 , 2.870587342, -124.15, -27.05, 154.9945258, 154.9999024));
  strips.push_back(FoilStrip(371, 43, CLHEP::Hep3Vector(93.59653368, 123.5480645, 94.5   ), 0.92245887 , 154.9981786, 2.871622481, 3.00098376 , 66     , 123   , 154.9957503, 155.0006068));
  strips.push_back(FoilStrip(372, 43, CLHEP::Hep3Vector(93.59953444, 123.5520254, 12.8   ), 0.92245887 , 155.0031478, 2.871624553, 3.000981686, -41.4  , 67    , 155.0006068, 155.0056889));
  strips.push_back(FoilStrip(373, 43, CLHEP::Hep3Vector(93.59643586, 123.5479354, -81.95 ), 0.92245887 , 154.9980166, 2.871622413, 3.000983828, -123.5 , -40.4 , 154.9954263, 155.0006068));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(2, strips));
  strips.clear();

  strips.push_back(FoilStrip(411, 44, CLHEP::Hep3Vector(85.77332323, 129.1004763, 56.9	  ), 0.984365698, 154.9967611, 3.068666268, 3.19802873 , -9.85	 , 123.65 , 154.9937311 ,154.9997911));
  strips.push_back(FoilStrip(412, 44, CLHEP::Hep3Vector(85.77656405, 129.1053541, -41.8	  ), 0.984365698, 155.0026174, 3.06866871 , 3.198026286, -74.65	 , -8.95  , 154.9997911 ,155.0054437));
  strips.push_back(FoilStrip(413, 44, CLHEP::Hep3Vector(85.77328716, 129.100422 , -98.7	  ), 0.984365698, 154.9966959, 3.06866624 , 3.198028757, -123.65 , -73.75 , 154.9936007 ,154.9997911));
  strips.push_back(FoilStrip(421, 44, CLHEP::Hep3Vector(80.32855285, 132.557612 , 55.1	  ), 1.025974347, 154.9974093, 3.19907554 , 3.332543004, -13.9	 , 124.1  , 154.994617  ,155.0002016));
  strips.push_back(FoilStrip(422, 42, CLHEP::Hep3Vector(80.33154907, 132.5625562, -61	  ), 1.025974347, 155.0031906, 3.199078027, 3.332540514, -109.125, -12.875, 155.0002016 ,155.0061795));
  strips.push_back(FoilStrip(423, 44, CLHEP::Hep3Vector(80.32875748, 132.5579496, -116.4  ), 1.025974347, 154.9978042, 3.19907571 , 3.332542834, -124.7	 , -108.1 , 154.9954067 ,155.0002016));
  strips.push_back(FoilStrip(431, 44, CLHEP::Hep3Vector(74.65757141, 135.8324008, 64.1	  ), 1.068246222, 154.9974002, 3.333570811, 3.467038283, 5.35	 , 122.85 , 154.9944342 ,155.0003661));
  strips.push_back(FoilStrip(432, 44, CLHEP::Hep3Vector(74.66043853, 135.8376173, -47.775 ), 1.068246222, 155.0033527, 3.333573374, 3.467035722, -101.875, 6.325  , 155.0003661 ,155.0063393));
  strips.push_back(FoilStrip(433, 44, CLHEP::Hep3Vector(74.65769368, 135.8326232, -112.325), 1.068246222, 154.997654 , 3.333570921, 3.467038174, -123.75 , -100.9 , 154.9949419 ,155.0003661));
  strips.push_back(FoilStrip(441, 42, CLHEP::Hep3Vector(68.85265105, 138.8652793, 64.9	  ), 1.110500643, 154.9975915, 3.468083624, 3.601550932, 4.7	 , 125.1  , 154.9945548 ,155.0006282));
  strips.push_back(FoilStrip(442, 44, CLHEP::Hep3Vector(68.85523237, 138.8704855, -46.475 ), 1.110500643, 155.0034025, 3.468086126, 3.601548431, -98.675 , 5.725  , 155.0006282 ,155.0061768));
  strips.push_back(FoilStrip(443, 42, CLHEP::Hep3Vector(68.85283586, 138.8656521, -111.775), 1.110500643, 154.9980075, 3.468083803, 3.601550753, -125.9	 , -97.65 , 154.9953869 ,155.0006282));
  strips.push_back(FoilStrip(451, 44, CLHEP::Hep3Vector(62.9247601 , 141.6492088, 50.05	  ), 1.152755064, 154.9968509, 3.602587965, 3.73605591 , -22.6	 , 122.7  , 154.9937968 ,154.9999051));
  strips.push_back(FoilStrip(452, 44, CLHEP::Hep3Vector(62.92715562, 141.6546014, -48.8	  ), 1.152755064, 155.0027517, 3.602590505, 3.736053371, -75.95	 , -21.65 , 154.9999051 ,155.0055982));
  strips.push_back(FoilStrip(453, 44, CLHEP::Hep3Vector(62.92480671, 141.6493138, -99.45  ), 1.152755064, 154.9969657, 3.602588014, 3.736055861, -123.9	 , -75	  , 154.9940264 ,154.9999051));
  strips.push_back(FoilStrip(461, 44, CLHEP::Hep3Vector(56.88384849, 144.1810814, 117	  ), 1.195009486, 154.9966336, 3.737113077, 3.870581209, 110.75	 , 123.25 , 154.993496  ,154.9997712));
  strips.push_back(FoilStrip(462, 44, CLHEP::Hep3Vector(56.88607591, 144.186727 , 41.083  ), 1.195009486, 155.0027028, 3.737115689, 3.870578597, -29.517 , 111.683, 154.9997712 ,155.0056344));
  strips.push_back(FoilStrip(463, 44, CLHEP::Hep3Vector(56.88385153, 144.1810891, -69.483 ), 1.195009486, 154.9966419, 3.737113081, 3.870581206, -110.383, -28.583, 154.9935126 ,154.9997712));
  strips.push_back(FoilStrip(464, 44, CLHEP::Hep3Vector(56.88618829, 144.1870119, -116.7  ), 1.195009486, 155.003009 , 3.737115821, 3.870578465, -123.95 , -109.45, 154.9997712 ,155.0062469));
  strips.push_back(FoilStrip(471, 44, CLHEP::Hep3Vector(50.83699123, 146.4230946, 60.575  ), 1.236618135, 154.9971687, 3.87161813 , 4.000980252, -3	 , 124.15 , 154.9940931 ,155.0002443));
  strips.push_back(FoilStrip(472, 44, CLHEP::Hep3Vector(50.83890118, 146.4285956, -25.067 ), 1.236618135, 155.0029918, 3.871620559, 4.000977822, -48.067 , -2.067 , 155.0002443 ,155.0057394));
  strips.push_back(FoilStrip(473, 44, CLHEP::Hep3Vector(50.83700095, 146.4231226, -66.808 ), 1.236618135, 154.9971983, 3.871618143, 4.00098024 , -86.483 , -47.133, 154.9941524 ,155.0002443));
  strips.push_back(FoilStrip(474, 44, CLHEP::Hep3Vector(50.8389562 , 146.428754 , -104.8  ), 1.236618135, 155.0031596, 3.871620629, 4.000977752, -124.05 , -85.55 , 155.0002443 ,155.0060749));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(3, strips));
  strips.clear();

  strips.push_back(FoilStrip(511, 45, CLHEP::Hep3Vector(41.68136852, 149.2877383, 100.55 ), 1.298524963, 154.9973074, 4.068662555, 4.198024562, 77.05  , 124.05 , 154.9949591, 154.9996556));
  strips.push_back(FoilStrip(512, 45, CLHEP::Hep3Vector(41.68273696, 149.2926395, 8.15   ), 1.298524963, 155.002396 , 4.068664678, 4.198022439, -61.75 , 78.05  , 154.9996556, 155.0051364));
  strips.push_back(FoilStrip(513, 45, CLHEP::Hep3Vector(41.68132459, 149.287581 , -92.35 ), 1.298524963, 154.997144 , 4.068662487, 4.19802463 , -123.95, -60.75 , 154.9946325, 154.9996556));
  strips.push_back(FoilStrip(521, 45, CLHEP::Hep3Vector(35.43539051, 150.8924047, 72.1   ), 1.340133613, 154.9973699, 4.199055256, 4.332522755, 19.35  , 124.85 , 154.994704 , 155.0000359));
  strips.push_back(FoilStrip(522, 45, CLHEP::Hep3Vector(35.43659561, 150.8975362, -51.9  ), 1.340133613, 155.0026411, 4.199057525, 4.332520485, -124.15, 20.35  , 155.0000359, 155.0052463));
  strips.push_back(FoilStrip(531, 45, CLHEP::Hep3Vector(29.0284892 , 152.2543207, 58.1   ), 1.382405487, 154.9968754, 4.333580246, 4.467048169, -6.7   , 122.9  , 154.9941479, 154.9996029));
  strips.push_back(FoilStrip(532, 45, CLHEP::Hep3Vector(29.02948317, 152.2595343, -62    ), 1.382405487, 155.0021828, 4.333582531, 4.467045886, -118.3 , -5.7   , 154.9996029, 155.0047628));
  strips.push_back(FoilStrip(533, 45, CLHEP::Hep3Vector(29.02849624, 152.2543577, -120.2 ), 1.382405487, 154.996913 , 4.333580262, 4.467048153, -123.1 , -117.3 , 154.9942231, 154.9996029));
  strips.push_back(FoilStrip(541, 45, CLHEP::Hep3Vector(22.57057111, 153.3450861, 79.75  ), 1.424659909, 154.9972455, 4.46809198 , 4.601559585, 36.05  , 123.45 , 154.9943001, 155.0001908));
  strips.push_back(FoilStrip(542, 45, CLHEP::Hep3Vector(22.57136925, 153.3505087, -32.75 ), 1.424659909, 155.0027265, 4.468094339, 4.601557226, -102.55, 37.05  , 155.0001908, 155.0052623));
  strips.push_back(FoilStrip(543, 45, CLHEP::Hep3Vector(22.57063517, 153.3455213, -112.75), 1.424659909, 154.9976854, 4.468092169, 4.601559396, -123.95, -101.55, 154.99518  , 155.0001908));
  strips.push_back(FoilStrip(551, 45, CLHEP::Hep3Vector(16.07272915, 154.1614021, 60.55  ), 1.46691433 , 154.9970016 , 4.602593746, 4.736061561, -2     , 123.1  , 154.9943896, 154.9996136));
  strips.push_back(FoilStrip(552, 45, CLHEP::Hep3Vector(16.07328682, 154.1667511, -62    ), 1.46691433 , 155.0023796 , 4.602596061, 4.736059247, -123   , -1     , 154.9996136, 155.0051456));
  strips.push_back(FoilStrip(561, 45, CLHEP::Hep3Vector(9.545843251, 154.7034597, 41.75  ), 1.509168751, 154.9976889, 4.737104728, 4.870571951, -40.55 , 124.05 , 154.9951438, 155.000234 ));
  strips.push_back(FoilStrip(562, 45, CLHEP::Hep3Vector(9.546157856, 154.7085582, -81.75 ), 1.509168751, 155.0027971, 4.737106926, 4.870569752, -123.95, -39.55 , 155.000234 , 155.0053602));
  strips.push_back(FoilStrip(571, 45, CLHEP::Hep3Vector(3.100948893, 154.9664474, 55.05  ), 1.5507774  , 154.99747  , 4.871632312, 5.000994183, -13.85 , 123.95 , 154.9949169, 155.0000231));
  strips.push_back(FoilStrip(572, 45, CLHEP::Hep3Vector(3.10104879 , 154.9714369, -68.45 ), 1.5507774  , 155.0024605, 4.871634393, 5.0009921  , -124.05, -12.85 , 155.0000231, 155.0048978));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(4, strips));
  strips.clear();

  strips.push_back(FoilStrip(611, 46, CLHEP::Hep3Vector(-6.490878953, 154.8611119, 104.7   ), 1.612684229, 154.9970822, 5.068657885, 5.198020079, 85.7	      , 123.7	    , 154.9941915, 154.9999728));
  strips.push_back(FoilStrip(612, 46, CLHEP::Hep3Vector(-6.491124531, 154.8669712, 65.45   ), 1.612684229, 155.0029467, 5.068660331, 5.198017632, 44.2	      , 86.7	    , 154.9999728, 155.0059205));
  strips.push_back(FoilStrip(613, 46, CLHEP::Hep3Vector(-6.490882002, 154.8611846, 19.6	   ), 1.612684229, 154.997155 , 5.068657915, 5.198020049, -6	      , 45.2	    , 154.9943372, 154.9999728));
  strips.push_back(FoilStrip(614, 46, CLHEP::Hep3Vector(-6.491115219, 154.866749 , -33.1   ), 1.612684229, 155.0027243, 5.068660238, 5.198017725, -61.2	      , -5	    , 154.9999728, 155.0054757));
  strips.push_back(FoilStrip(615, 46, CLHEP::Hep3Vector(-6.490890244, 154.8613813, -73.35  ), 1.612684229, 154.9973518, 5.068657997, 5.198019967, -86.5	      , -60.2	    , 154.9947308, 154.9999728));
  strips.push_back(FoilStrip(616, 46, CLHEP::Hep3Vector(-6.491102754, 154.8664516, -104.8  ), 1.612684229, 155.0024266, 5.068660114, 5.198017849, -124.1      , -85.5	    , 154.9999728, 155.0048804));
  strips.push_back(FoilStrip(621, 46, CLHEP::Hep3Vector(-12.89832187, 154.4652155, 103.5   ), 1.654292878, 155.0028048, 5.19845195 , 5.33191477 , 83.2	      , 123.8	    , 155.0001149, 155.0054947));
  strips.push_back(FoilStrip(622, 46, CLHEP::Hep3Vector(-12.89877991, 154.4706885, 68.36   ), 1.654292878, 155.008297 , 5.198454335, 5.331912427, 52.56	      , 84.16	    , 155.0054947, 155.0110992));
  strips.push_back(FoilStrip(623, 46, CLHEP::Hep3Vector(-12.89831716, 154.4651593, 31.02   ), 1.654292878, 155.0027484, 5.198451925, 5.331914794, 8.52	      , 53.52	    , 155.0000021, 155.0054947));
  strips.push_back(FoilStrip(624, 46, CLHEP::Hep3Vector(-12.8987806 , 154.4706968, -18.57  ), 1.654292878, 155.0083053, 5.198454338, 5.331912423, -46.62      , 9.48	    , 155.0054947, 155.0111159));
  strips.push_back(FoilStrip(625, 46, CLHEP::Hep3Vector(-12.89829909, 154.4649434, -64.26  ), 1.654292878, 155.0025318, 5.198451831, 5.331914886, -82.86      , -45.66	    , 154.9995689, 155.0054947));
  strips.push_back(FoilStrip(626, 46, CLHEP::Hep3Vector(-12.89877932, 154.4706815, -103.05 ), 1.654292878, 155.0082899, 5.198454332, 5.33191243 , -124.2      , -81.9	    , 155.0054947, 155.0110851));
  strips.push_back(FoilStrip(631, 49, CLHEP::Hep3Vector(-19.3831348 , 153.788803 , -0.05   ), 1.696564753, 155.0054897, 5.332354792, 5.4658153  , -120.65     , 120.55	    , 154.9949034, 155.016076 ));
  strips.push_back(FoilStrip(641, 54, CLHEP::Hep3Vector(-25.9091301 , 152.824799 , -0.3	   ), 1.738819174, 155.0054909, 5.467833137, 5.601293645, -121.35     , 120.75	    , 154.9949971, 155.0159847));
  strips.push_back(FoilStrip(651, 55, CLHEP::Hep3Vector(-32.2074165 , 151.622498 , -0.15   ), 1.781073595, 155.0054824, 5.60464755 , 5.727844541, -121.6      , 121.3	    , 154.9965559, 155.0144089));
  strips.push_back(FoilStrip(661, 61, CLHEP::Hep3Vector(-38.4503937 , 150.160812 , -0.05   ), 1.823328016, 155.005491 , 5.731194203, 5.86465471 , -117.05     , 116.95	    , 154.9999363, 155.0110456));
  strips.push_back(FoilStrip(671, 62, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , 91.5	   ), 1.864936666, 155.0054983, 5.890831604, 5.972968619, 69.75	      , 113.25	    , 154.9955879, 155.0154086));
  strips.push_back(FoilStrip(672, 62, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , 34.75   ), 1.864936666, 155.0054983, 5.890831604, 5.972968619, 2.75	      , 66.75	    , 154.9967655, 155.0142311));
  strips.push_back(FoilStrip(673, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -9.62611), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -9.64549706 , -9.60672294 , 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(674, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -15.2767), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -15.29660431, -15.25679569, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(675, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -21.2786), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -21.29800696, -21.25919304, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(676, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -27.0986), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -27.11800696, -27.07919304, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(677, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -33.1485), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -33.16789701, -33.12910299, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(678, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -38.9819), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -39.00130696, -38.96249304, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(679, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -44.8495), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -44.8684096 , -44.8305904 , 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(680, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -50.7064), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -50.72531954, -50.68748046, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(681, 63, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -56.3118), 1.864936666, 155.0054983, 5.890831604, 5.972968619, -56.33119701, -56.29240299, 155.0054983, 155.0054983));
  strips.push_back(FoilStrip(682, 65, CLHEP::Hep3Vector(-44.7346992 , 148.409943 , -90	   ), 1.864936666, 155.0054983, 5.867222526, 5.996577698, -121.75     , -58.25	    , 155.0011068, 155.0098897));
  strips_dictionary.insert(std::pair<int, std::vector<FoilStrip> >(5, strips));
  strips.clear();
}

SFoilSide::SFoilSide() {
  createStripsDictionary();
}

SFoilSide::~SFoilSide() {
}

int SFoilSide::getSFoilSide(CLHEP::Hep3Vector trueVertex) const{

  int side = -1;

  if (getSFoilPerpDist(trueVertex) > 0){
    side = 1;
  } else {
    side = 0;
  }
 
  return side;
}

double SFoilSide::getSFoilPerpDist(CLHEP::Hep3Vector trueVertex) const {
  double sector = sectorfinder_.sectorNumber(trueVertex);

  if(sector > 6){
    return getSFoilPerpDistFromApproximation(trueVertex);
  } else {
    return getSFoilPerpDistFromGeom(trueVertex);
  }
}

double SFoilSide::getSFoilPerpDistFromGeom(CLHEP::Hep3Vector trueVertex) const{
  // first identify the sector
  double sector = sectorfinder_.sectorNumber(trueVertex);

  double dist_from_begin_of_sector = sector - (int)sector;
  
  int sector_id;

  double distance = 1;

  if (dist_from_begin_of_sector < 0.05 and (int)sector != 0) {
    // check if this may actually belong to previous sector
    dist_from_begin_of_sector = sector - ((int)sector-1);
    if (dist_from_begin_of_sector < 1.002) {
      sector_id = ((int)sector-1);
    } else {
      sector_id = (int)sector;
    }
  } else {
    sector_id = (int)sector;
  }

  // find the strip facing the vertex
  
  std::map<int, std::vector<FoilStrip> >::const_iterator dictEntry = strips_dictionary.find(sector_id);
  if (dictEntry == strips_dictionary.end()) {
    std::cout << "-- WARNING : SFoilSide::getSFoilPerpDistFromGeom\n"
	      << "-- could not find entry in the strips dictionary for : \n"
	      << "-- sector number = " << sector << " - sector_id = " << sector_id
	      << std::endl;
    return distance;
  }

  std::vector<FoilStrip>::const_iterator stripIt = dictEntry->second.begin();
  bool found = false;
  while (!found && stripIt != dictEntry->second.end()) {
    if (trueVertex.z() >= stripIt->low_z  and 
	trueVertex.z() <= stripIt->high_z and
	sector >= stripIt->low_vtx_num and
	sector <= stripIt->high_vtx_num) {
      found = true;

      // the vertex was generated on the volume of this strip. 
      // Now we calculate the distance from the center.
      // 1) vector joining the center of the strip and the generated vertex
      CLHEP::Hep2Vector trueVertex_xy(trueVertex);
      CLHEP::Hep2Vector center_xy(stripIt->center);
      CLHEP::Hep2Vector delta_xy = trueVertex_xy - center_xy;
      double center_radius = center_xy.mag();
      double vertex_rasius = trueVertex_xy.mag();

      // ST: debugging printout
      // if (sector_id == 4) {
      // 	std::cout << "-- sector : " << sector_id 
      // 		  << std::setprecision(7) << " - strip center : " << std::setw(10) << center_xy.mag()
      // 		  << std::setprecision(7) << " - z strip : [ " << std::setw(8) << stripIt->low_z << " , " << std::setw(8) << stripIt->high_z << " ] "
      // 		  << std::setprecision(7) << " - z center : " << trueVertex.z()
      // 		  << std::setprecision(7) << " - vertex radius : " << std::setw(10) << trueVertex_xy.mag()
      // 		  << std::setprecision(7) << " - vertex proj : " << std::setw(12) << trueVertex_xy.dot( center_xy.unit() )
      // 		  << std::setprecision(7) << " - radius : " << std::setw(10) << stripIt->radius
      // 		  << std::setprecision(7) << " - distance : " << std::setw(12) << trueVertex_xy.dot( center_xy.unit() ) - stripIt->radius
      // 		  << std::endl;
      // }

      // 2) get the (x,y) projection of the vectors
      distance = trueVertex_xy.dot( center_xy.unit() ) - stripIt->radius;
    }
    ++stripIt;
  }
  
  return distance;
}

double SFoilSide::getSFoilPerpDistFromApproximation(CLHEP::Hep3Vector trueVertex) const{

  // First get sector number and x and y coordinates of trueVertex
  double sector = sectorfinder_.sectorNumber(trueVertex);
  double x = trueVertex.x();
  double y = trueVertex.y();

  // Start by finding the centre of the strip which the true vertex is located in.
  double sectorCentre = 0;

  // Strips at edge are 63 mm and five in centre are 65 mm.  Separated by 0.5 mm.
  // SFoil contribution starts at sector number + 0.06866.  Seems to also overrun to ~0.001
  // Calculate centre of each strip accordingly...
  if ((sector - (int)sector) >= 0.068 && (sector - (int)sector) < 0.19905){
    sectorCentre = (int)sector + 0.133853;
  } else if((sector - (int)sector) >= 0.19905 && (sector - (int)sector) < 0.33354){
    sectorCentre = (int)sector + 0.266292;
  } else if((sector - (int)sector) >= 0.33354 && (sector - (int)sector) < 0.46803){
    sectorCentre = (int)sector + 0.400783;
  } else if((sector - (int)sector) >= 0.46803 && (sector - (int)sector) < 0.60252){
    sectorCentre = (int)sector + 0.535275;
  } else if((sector - (int)sector) >= 0.60252 && (sector - (int)sector) < 0.73701){
    sectorCentre = (int)sector + 0.669767;
  } else if((sector - (int)sector) >= 0.73701 && (sector - (int)sector) < 0.87150){
    sectorCentre = (int)sector + 0.804258;
  } else if((sector - (int)sector) >= 0.87150 && (sector - (int)sector) < 1.0){
    sectorCentre = (int)sector + 0.936697;
  } else if((sector-(int)sector) < 0.001){
    sectorCentre = (int)sector - 0.063303;
  }

  // Calculate coordinates of the point (x_P, y_P) at the centre of the strip
  double R_Foil = 155.0;
  double x_P = R_Foil*cos(sectorCentre*TMath::TwoPi()/20.0);
  double y_P = R_Foil*sin(sectorCentre*TMath::TwoPi()/20.0);

  // Calculate a line perpendicualr to vector (x_P, y_P).  This line should 
  // be parallel to the strip direction and therefore run right down the middle
  // of the strip. Line is of for y = m1*x + c1
  double m1 = -x_P/y_P;
  double c1 = y_P - m1*x_P;

  // Calculate a line that runs perpendicular to the strip (in direction (x_P, y_P)) 
  // and goes through the trueVertex. Form is y = m2*x + c2.
  double m2 = y_P/x_P;
  double c2 = y - m2*x;

  // Calculate intersection of perpendicular line through point and line parallel
  // to strip.
  double x0 = (c2-c1)/(m1-m2);
  double y0 = m1*x0+c1;

  // Calculate perpendicular distance.  If intersection is closer to origin than vertex,
  // we know it's on the outside of the foil - then use convention of positive distance.
  // Set distance to be negative is it's on the inside of foil.
  double PerpDist = 0;
  if(x0*x0+y0*y0 < x*x + y*y){
    PerpDist = sqrt(pow(x-x0,2)+pow(y-y0,2));
  } else {
    PerpDist = -sqrt(pow(x-x0,2)+pow(y-y0,2));
  }

  return PerpDist;
}
