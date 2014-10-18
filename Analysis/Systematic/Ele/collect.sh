#! /bin/sh 

for num in {1..900}
do
  #cp -r ../BatchJobs/EventSelection$num/ElectronFitResultsRayleighGausSimultNominal/RstElectron/SigYields_Nominal.root ./FitResult/SigYields_$num.root
  cp -r ../EventSelection$num/ElectronFitResultsRayleighGausSimultNominal/RstElectron/SigYields_Nominal.root ./FitResult/SigYields_$num.root
  #ls -l MetFit$num/EleFitResults/RstElectron/SigYields_Nominal.root
done
