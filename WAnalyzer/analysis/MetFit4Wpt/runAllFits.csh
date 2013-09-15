#! /bin/tcsh -f
echo "===================================== Running MET Fit ====================================="
python runFits.py MuonRayleighGausNominal
python runFits.py MuonRayleighGausUp
python runFits.py MuonRayleighGausDown
python runFits.py MuonRayleighGausBeforeRC
python runFits.py ElectronRayleighGausNominal
python runFits.py ElectronRayleighGausUp
python runFits.py ElectronRayleighGausDown
python runFits.py ElectronRayleighGausBeforeRC
echo "===================================== MET Fit finished ====================================="
echo "===================================== Running Systematic uncertainties ====================================="
root -l -q 'Systematics.C+("Mu")'
root -l -q 'Systematics.C+("Ele")'
echo "===================================== Systematic uncertainties Finished ====================================="
