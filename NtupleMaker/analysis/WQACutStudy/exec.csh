#!/bin/tcsh
#W_Lept1_X
#pt, et, eta, phi,etaSC,phiSC,dEtaIn,dPhiIn,sigmaIEtaIEta,HoverE
#

set DIR = /d1/DATA/WQAsy/IV/batch

echo ""
echo "++++++++++++++++++++++++++++"
echo $DIR
echo ""

date 

foreach EMC (EB EE EBEE) #EB EE EBEE ALL(<2.5)
    echo ""
    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
    echo $EMC
    foreach VARs (pt et eta phi etaSC phiSC dEtaIn dPhiIn sigmaIEtaIEta HoverE dxy AEff03 dz InvEminusInvP)
	echo ""
	set VAR = `echo "W_Lept1_"$VARs `
	echo $EMC " === " $VAR 
	root -l -b -q sgnfc.C+'("'${DIR}'","'${VAR}'","'${EMC}'",-1)' >& log_${VARs}_${EMC}.txt 
	date
##	sleep 1m
   end

    foreach VARs (pt)
	echo ""
	set VAR = `echo "W_Neut_"$VARs `
	echo $EMC " === " $VAR 
	root -l -b -q sgnfc.C+'("'${DIR}'","'${VAR}'","'${EMC}'",-1)' >& log_${VARs}_${EMC}.txt 
	date
#	sleep 1m
    end

end

date

# root -l sgnfc.C+'("DATA/ALL/batch","W_Lept1_HoverE","EB",-1)'


