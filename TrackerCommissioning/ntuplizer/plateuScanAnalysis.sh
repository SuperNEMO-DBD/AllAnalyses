#!/bin/bash
# plateau scan analysis

./plotraw MSSLTest49.dat
cd ../analysis/
mv nothings.root nothings55.root
cp ../ntuplizer/nothings.root .
root -q makeplots.C
mv test.png occupancyPercent49.png
cd ../ntuplizer/

./plotraw MSSLTest50.dat
cd ../analysis/
mv nothings.root nothings49.root
cp ../ntuplizer/nothings.root .
root -q makeplots.C
mv test.png occupancyPercent50.png
cd ../ntuplizer/

./plotraw MSSLTest51.dat
cd ../analysis/
mv nothings.root nothings50.root
cp ../ntuplizer/nothings.root .
root -q makeplots.C
mv test.png occupancyPercent51.png
cd ../ntuplizer/

./plotraw MSSLTest52.dat
cd ../analysis/
mv nothings.root nothings51.root
cp ../ntuplizer/nothings.root .
root -q makeplots.C
mv test.png occupancyPercent52.png
cd ../ntuplizer/

./plotraw MSSLTest53.dat
cd ../analysis/
mv nothings.root nothings52.root
cp ../ntuplizer/nothings.root .
root -q makeplots.C
mv test.png occupancyPercent53.png

mv nothings.root nothings53.root
mv nothings55.root nothings.root
