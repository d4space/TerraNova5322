#! /bin/tcsh -f
echo "===================================== Running MET Fit ====================================="
python runFits.py MuonRayleighGausNominal
rm -f *.d *.so
python runFits.py ElectronRayleighGausNominal
rm -f *.d *.so
#echo "===================================== MET Fit finished ====================================="
#echo "===================================== Running Systematic uncertainties ====================================="
#root -l -q 'Systematics.C+("Mu")'
#root -l -q 'Systematics.C+("Ele")'
#echo "===================================== Systematic uncertainties Finished ====================================="
