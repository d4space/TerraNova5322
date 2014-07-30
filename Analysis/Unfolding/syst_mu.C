{
  //*
  double mutracksigp[14]={0};
  mutracksigp[1]= 0.19;
  mutracksigp[2]= 0.17;
  mutracksigp[3]= 0.14;
  mutracksigp[4]= 0.11;
  mutracksigp[5]= 0.11;
  mutracksigp[6]= 0.13;
  mutracksigp[7]= 0.16;
  mutracksigp[8]= 0.20;
  mutracksigp[9]= 0.23;
  mutracksigp[10]= 0.25;
  mutracksigp[11]= 0.27;
  mutracksigp[12]= 0.29;
  mutracksigp[13]= 0.30;

  double mutracksigm[14] ={0};
  mutracksigm[1]= 0.10; 
  mutracksigm[2]= 0.16;
  mutracksigm[3]= 0.17;
  mutracksigm[4]= 0.14;
  mutracksigm[5]= 0.13;
  mutracksigm[6]= 0.11;
  mutracksigm[7]= 0.08;
  mutracksigm[8]= 0.13;
  mutracksigm[9]= 0.09;
  mutracksigm[10]= 0.14;
  mutracksigm[11]= 0.19;
  mutracksigm[12]= 0.22;
  mutracksigm[13]= 0.24;
 
  double mutrackbckp[14] = {0};
  mutrackbckp[1 ]= 0.22;
  mutrackbckp[2 ]= 0.21;
  mutrackbckp[3 ]= 0.18;
  mutrackbckp[4 ]= 0.16;
  mutrackbckp[5 ]= 0.15;
  mutrackbckp[6 ]= 0.15;
  mutrackbckp[7 ]= 0.16;
  mutrackbckp[8 ]= 0.18;
  mutrackbckp[9 ]= 0.20;
  mutrackbckp[10]= 0.21;
  mutrackbckp[11]= 0.22;
  mutrackbckp[12]= 0.23;
  mutrackbckp[13]= 0.24;
 
  double mutrackbckm[14] ={0};
  mutrackbckm[1 ]= 0.17;
  mutrackbckm[2 ]= 0.24;
  mutrackbckm[3 ]= 0.31;
  mutrackbckm[4 ]= 0.29;
  mutrackbckm[5 ]= 0.22;
  mutrackbckm[6 ]= 0.17;
  mutrackbckm[7 ]= 0.15;
  mutrackbckm[8 ]= 0.16;
  mutrackbckm[9 ]= 0.21; 
  mutrackbckm[10]= 0.27;
  mutrackbckm[11]= 0.32;
  mutrackbckm[12]= 0.35;
  mutrackbckm[13]= 0.37;
  
  double muidisosigp[14] = {0};
  muidisosigp[1 ] = 0.12;
  muidisosigp[2 ] = 0.11;
  muidisosigp[3 ] = 0.10;
  muidisosigp[4 ] = 0.09;
  muidisosigp[5 ] = 0.09;
  muidisosigp[6 ] = 0.10;
  muidisosigp[7 ] = 0.10;
  muidisosigp[8 ] = 0.12;
  muidisosigp[9 ] = 0.13;
  muidisosigp[10] = 0.13;
  muidisosigp[11] = 0.14;
  muidisosigp[12] = 0.14;
  muidisosigp[13] = 0.15;

  double muidisosigm[14] = {0};
  muidisosigm[1 ] = 0.13;
  muidisosigm[2 ] = 0.13; 
  muidisosigm[3 ] = 0.15;
  muidisosigm[4 ] = 0.16;
  muidisosigm[5 ] = 0.10;
  muidisosigm[6 ] = 0.12;
  muidisosigm[7 ] = 0.13;
  muidisosigm[8 ] = 0.10;
  muidisosigm[9 ] = 0.09;
  muidisosigm[10] = 0.11;
  muidisosigm[11] = 0.13;
  muidisosigm[12] = 0.14;
  muidisosigm[13] = 0.15;

  double muidisobckp[14]={0};
  muidisobckp[1 ] = 0.10;
  muidisobckp[2 ] = 0.10;
  muidisobckp[3 ] = 0.10;
  muidisobckp[4 ] = 0.11;
  muidisobckp[5 ] = 0.13;
  muidisobckp[6 ] = 0.16;
  muidisobckp[7 ] = 0.18;
  muidisobckp[8 ] = 0.20;
  muidisobckp[9 ] = 0.22;
  muidisobckp[10] = 0.24;
  muidisobckp[11] = 0.25;
  muidisobckp[12] = 0.25;
  muidisobckp[13] = 0.26;

  double muidisobckm[14] = {0};
  muidisobckm[1 ] = 0.20;
  muidisobckm[2 ] = 0.16;
  muidisobckm[3 ] = 0.18;
  muidisobckm[4 ] = 0.15;
  muidisobckm[5 ] = 0.13;
  muidisobckm[6 ] = 0.17;
  muidisobckm[7 ] = 0.23;
  muidisobckm[8 ] = 0.24;
  muidisobckm[9 ] = 0.25;
  muidisobckm[10] = 0.27;
  muidisobckm[11] = 0.28;
  muidisobckm[12] = 0.29;
  muidisobckm[13] = 0.29;

  double mutrackp[14]={0};
  double mutrackm[14]={0};
  double muidisop[14]={0};
  double muidisom[14]={0};
  for(int i(1);i<14;i++)
  {
    mutrackp[i]  = TMath::Sqrt(mutracksigp[i] *mutracksigp[i]  + mutrackbckp[i]*mutrackbckp[i]);
    mutrackm[i]  = TMath::Sqrt(mutracksigm[i] *mutracksigm[i]  + mutrackbckm[i]*mutrackbckm[i]);

    muidisop[i]  = TMath::Sqrt(muidisosigp[i] *muidisosigp[i]  + muidisobckp[i] *muidisobckp[i]);
    muidisom[i]  = TMath::Sqrt(muidisosigm[i] *muidisosigm[i]  + muidisobckm[i] *muidisobckm[i]);
  }
 
  double mutoyp[14] = {0};
  mutoyp[1 ] = 0.4323;
  mutoyp[2 ] = 0.2473;
  mutoyp[3 ] = 0.2742;
  mutoyp[4 ] = 0.4182;
  mutoyp[5 ] = 0.4885;
  mutoyp[6 ] = 0.5158;
  mutoyp[7 ] = 0.5746;
  mutoyp[8 ] = 0.7582;
  mutoyp[9 ] = 0.3349;
  mutoyp[10] = 0.3527;
  mutoyp[11] = 0.4707;
  mutoyp[12] = 0.5730;
  mutoyp[13] = 0.5338;

  double mutoym[14] = {0};
  mutoym[1 ] = 0.2001;
  mutoym[2 ] = 0.1545;
  mutoym[3 ] = 0.1734;
  mutoym[4 ] = 0.3098;
  mutoym[5 ] = 0.4001;
  mutoym[6 ] = 0.4068;
  mutoym[7 ] = 0.7785;
  mutoym[8 ] = 0.4950;
  mutoym[9 ] = 0.3063;
  mutoym[10] = 0.3146;
  mutoym[11] = 0.3719;
  mutoym[12] = 0.4312;
  mutoym[13] = 0.4685;

  double muPOGp[14] = {0};
  muPOGp[1 ] = 0.87;
  muPOGp[2 ] = 1.12;
  muPOGp[3 ] = 0.73;
  muPOGp[4 ] = 0.91;
  muPOGp[5 ] = 1.00;
  muPOGp[6 ] = 0.76;
  muPOGp[7 ] = 0.81;
  muPOGp[8 ] = 1.11;
  muPOGp[9 ] = 1.11;
  muPOGp[10] = 1.01;
  muPOGp[11] = 2.04;
  muPOGp[12] = 2.22;
  muPOGp[13] = 2.20;

  double muPOGm[14] = {0};
  muPOGm[1 ] = 0.83;
  muPOGm[2 ] = 0.77;
  muPOGm[3 ] = 0.82;
  muPOGm[4 ] = 0.69;
  muPOGm[5 ] = 1.02;
  muPOGm[6 ] = 1.19;
  muPOGm[7 ] = 0.95;
  muPOGm[8 ] = 0.72;
  muPOGm[9 ] = 0.79;
  muPOGm[10] = 1.34;
  muPOGm[11] = 1.72;
  muPOGm[12] = 2.87;
  muPOGm[13] = 2.62;

  double mutotaleffp[14]={0};
  double mutotaleffm[14]={0};
  for(int i(1);i<14;i++)
  {
    mutotaleffp[i]  = sqrt(mutrackp[i] *mutrackp[i] +mutoyp[i] *mutoyp[i] +muidisop[i] *muidisop[i] +muPOGp[i] *muPOGp[i]);
    mutotaleffm[i]  = sqrt(mutrackm[i] *mutrackm[i] +mutoym[i] *mutoym[i] +muidisom[i] *muidisom[i] +muPOGm[i] *muPOGm[i]);
  } 
  
  double mustatp[14] = {0};
  mustatp[1 ]= 0.9202 ; 
  mustatp[2 ]= 0.9267 ;
  mustatp[3 ]= 1.0331 ;
  mustatp[4 ]= 1.1262 ;
  mustatp[5 ]= 1.5045 ;
  mustatp[6 ]= 1.4961 ;
  mustatp[7 ]= 2.1085 ;
  mustatp[8 ]= 2.0564 ;
  mustatp[9 ]= 2.7194 ;
  mustatp[10]= 5.4584 ;
  mustatp[11]= 10.5096;
  mustatp[12]= 18.2816;
  mustatp[13]= 24.2144;

  double mustatm[14] = {0};
  mustatm[1 ] = 1.1495 ;
  mustatm[2 ] = 1.1196 ;
  mustatm[3 ] = 1.2729 ;
  mustatm[4 ] = 1.3512 ;
  mustatm[5 ] = 1.7651 ;
  mustatm[6 ] = 1.8067 ;
  mustatm[7 ] = 2.4696 ;
  mustatm[8 ] = 2.4629 ;
  mustatm[9 ] = 3.1121 ;
  mustatm[10] = 6.2686 ;
  mustatm[11] = 12.1287;
  mustatm[12] = 16.3956;
  mustatm[13] = 33.3982;

  double mumetp[14] = {0};
  mumetp[1 ] = 0.0617; 
  mumetp[2 ] = 0.0451452;
  mumetp[3 ] = 0.0881;
  mumetp[4 ] = 0.1288;
  mumetp[5 ] = 0.1290;
  mumetp[6 ] = 0.1371;
  mumetp[7 ] = 0.2503;
  mumetp[8 ] = 0.303893;
  mumetp[9 ] = 0.1248;
  mumetp[10] = 0.2070;
  mumetp[11] = 0.360465;
  mumetp[12] = 0.551997;
  mumetp[13] = 0.664495;

  double mumetm[14] ={0};
  mumetm[1 ] = 0.0402;
  mumetm[2 ] = 0.0286243;
  mumetm[3 ] = 0.0591;
  mumetm[4 ] = 0.0755;
  mumetm[5 ] = 0.0734;
  mumetm[6 ] = 0.0853;
  mumetm[7 ] = 0.166606;
  mumetm[8 ] = 0.236722;
  mumetm[9 ] = 0.1549;
  mumetm[10] = 0.3018;
  mumetm[11] = 0.4771;
  mumetm[12] = 0.6494;
  mumetm[13] = 0.7726;

  double muscalep[14] = {0};
  muscalep[1 ] = 0.0243; 
  muscalep[2 ] = 0.0280;
  muscalep[3 ] = 0.0315;
  muscalep[4 ] = 0.0391;
  muscalep[5 ] = 0.0447;
  muscalep[6 ] = 0.0611;
  muscalep[7 ] = 0.0915;
  muscalep[8 ] = 0.1054;
  muscalep[9 ] = 0.0662;
  muscalep[10] = 0.1203;
  muscalep[11] = 0.0534;
  muscalep[12] = 0.0558;
  muscalep[13] = 0.0570;

  double muscalem[14] ={0};
  muscalem[1 ] = 0.0238; 
  muscalem[2 ] = 0.0309;
  muscalem[3 ] = 0.0390;
  muscalem[4 ] = 0.0403;
  muscalem[5 ] = 0.0431;
  muscalem[6 ] = 0.0585;
  muscalem[7 ] = 0.0872;
  muscalem[8 ] = 0.1253;
  muscalem[9 ] = 0.0544;
  muscalem[10] = 0.1214;
  muscalem[11] = 0.0563;
  muscalem[12] = 0.0578;
  muscalem[13] = 0.0586;

  double musmearp[14] ={0};
  musmearp[1 ] = 0.3902; 
  musmearp[2 ] = 0.2034;
  musmearp[3 ] = 0.2562;
  musmearp[4 ] = 0.3877;
  musmearp[5 ] = 0.4036;
  musmearp[6 ] = 0.3791;
  musmearp[7 ] = 0.6556;
  musmearp[8 ] = 0.5697;
  musmearp[9 ] = 0.3184;
  musmearp[10] = 0.3328;
  musmearp[11] = 0.4681;
  musmearp[12] = 0.5542;
  musmearp[13] = 0.4548;

  double musmearm[14] = {0};
  musmearm[1 ] = 0.1460; 
  musmearm[2 ] = 0.0965;
  musmearm[3 ] = 0.1786;
  musmearm[4 ] = 0.2578;
  musmearm[5 ] = 0.2341;
  musmearm[6 ] = 0.2278;
  musmearm[7 ] = 0.3668;
  musmearm[8 ] = 0.5848;
  musmearm[9 ] = 0.2307;
  musmearm[10] = 0.3182;
  musmearm[11] = 0.4379;
  musmearm[12] = 0.5160;
  musmearm[13] = 0.5613;

  double muMomResp[14]={0};
  double muMomResm[14]={0};
  for(int i(1);i<14;i++)
  {
    muMomResp[i]  = sqrt(musmearp[i] *musmearp[i] +muscalep[i] *muscalep[i] ); 
    muMomResm[i]  = sqrt(musmearm[i] *musmearm[i] +muscalem[i] *muscalem[i] ); 
  }
  
  double muqcdbckgrp[14]={0};
  muqcdbckgrp[1 ] = 1.1888;
  muqcdbckgrp[2 ] = 1.5950;
  muqcdbckgrp[3 ] = 1.1278;
  muqcdbckgrp[4 ] = 1.3924;
  muqcdbckgrp[5 ] = 1.2443;
  muqcdbckgrp[6 ] = 2.2605;
  muqcdbckgrp[7 ] = 1.1487;
  muqcdbckgrp[8 ] = 1.8617;
  muqcdbckgrp[9 ] = 0.6912; 
  muqcdbckgrp[10] = 0.6790;
  muqcdbckgrp[11] = 0.6995;
  muqcdbckgrp[12] = 0.7260;
  muqcdbckgrp[13] = 0.7427;
 
  double muqcdbckgrm[14]={0};
  muqcdbckgrm[1 ] = 1.2431;
  muqcdbckgrm[2 ] = 1.4121;
  muqcdbckgrm[3 ] = 1.3396;
  muqcdbckgrm[4 ] = 1.0235;
  muqcdbckgrm[5 ] = 1.1964;
  muqcdbckgrm[6 ] = 1.9669;
  muqcdbckgrm[7 ] = 1.0839;
  muqcdbckgrm[8 ] = 2.3055;
  muqcdbckgrm[9 ] = 0.8416; 
  muqcdbckgrm[10] = 0.8401;
  muqcdbckgrm[11] = 0.8623;
  muqcdbckgrm[12] = 0.8890;
  muqcdbckgrm[13] = 0.9061;

  double muqcdshapep[14] = {0};
  muqcdshapep[1 ] = 0.3729;
  muqcdshapep[2 ] = 0.4557;
  muqcdshapep[3 ] = 0.2102;
  muqcdshapep[4 ] = 0.3853;
  muqcdshapep[5 ] = 0.4290;
  muqcdshapep[6 ] = 0.3940;
  muqcdshapep[7 ] = 0.1659;
  muqcdshapep[8 ] = 0.2923;
  muqcdshapep[9 ] = 0.3466; 
  muqcdshapep[10] = 0.1299;
  muqcdshapep[11] = 0.8764;
  muqcdshapep[12] = 0.9405;
  muqcdshapep[13] = 0.9226;
 
  double muqcdshapem[14] ={0};
  muqcdshapem[1 ] = 0.1329;
  muqcdshapem[2 ] = 0.3125;
  muqcdshapem[3 ] = 0.4215;
  muqcdshapem[4 ] = 0.3460;
  muqcdshapem[5 ] = 0.2472;
  muqcdshapem[6 ] = 0.2124;
  muqcdshapem[7 ] = 0.1092;
  muqcdshapem[8 ] = 0.5836;
  muqcdshapem[9 ] = 0.2582; 
  muqcdshapem[10] = 0.1055;
  muqcdshapem[11] = 0.8416;
  muqcdshapem[12] = 0.8987;
  muqcdshapem[13] = 0.8923;

  double muewkp[14] ={0};
  muewkp[1 ] = 0.1660;
  muewkp[2 ] = 0.1523;
  muewkp[3 ] = 0.1530;
  muewkp[4 ] = 0.1462;
  muewkp[5 ] = 0.1527;
  muewkp[6 ] = 0.1857;
  muewkp[7 ] = 0.2406;
  muewkp[8 ] = 0.2713;
  muewkp[9 ] = 0.3387; 
  muewkp[10] = 0.3608;
  muewkp[11] = 0.3753;
  muewkp[12] = 0.3940;
  muewkp[13] = 0.4029;
 
  double muewkm[14] ={0};
  muewkm[1 ] = 0.2042;
  muewkm[2 ] = 0.1913;
  muewkm[3 ] = 0.1806;
  muewkm[4 ] = 0.1696;
  muewkm[5 ] = 0.1847;
  muewkm[6 ] = 0.2389;
  muewkm[7 ] = 0.2957;
  muewkm[8 ] = 0.3627;
  muewkm[9 ] = 0.3358; 
  muewkm[10] = 0.3494;
  muewkm[11] = 0.3632;
  muewkm[12] = 0.3638;
  muewkm[13] = 0.3680;

  double mufsrp[14] ={0};
  mufsrp[1 ] = 0.0148003;
  mufsrp[2 ] = 0.0256613;
  mufsrp[3 ] = 0.0265483;
  mufsrp[4 ] = 0.0198106;
  mufsrp[5 ] = 0.0241401;
  mufsrp[6 ] = 0.0268263;
  mufsrp[7 ] = 0.0318734;
  mufsrp[8 ] = 0.0312375;
  mufsrp[9 ] = 0.0377605;
  mufsrp[10] = 0.0228441;
  mufsrp[11] = 0.0295351;
  mufsrp[12] = 0.0393;
  mufsrp[13] = 0.0518017;
 
  double mufsrm[14] ={0};
  mufsrm[1 ] = 0.0216572;
  mufsrm[2 ] = 0.0290663;
  mufsrm[3 ] = 0.0304291;
  mufsrm[4 ] = 0.0180261;
  mufsrm[5 ] = 0.0173884;
  mufsrm[6 ] = 0.0233484;
  mufsrm[7 ] = 0.0205926;
  mufsrm[8 ] = 0.0297664;
  mufsrm[9 ] = 0.0338547;
  mufsrm[10] = 0.0371577;
  mufsrm[11] = 0.0485584;
  mufsrm[12] = 0.042456;
  mufsrm[13] = 0.0246013;

  double musvdunfp[14] ={0};
  musvdunfp[1 ] = 0.2036;
  musvdunfp[2 ] = 0.1786;
  musvdunfp[3 ] = 0.2121;
  musvdunfp[4 ] = 0.2623;
  musvdunfp[5 ] = 0.2858;
  musvdunfp[6 ] = 0.2961;
  musvdunfp[7 ] = 0.3214;
  musvdunfp[8 ] = 0.3971;
  musvdunfp[9 ] = 0.5205;
  musvdunfp[10] = 0.6648;
  musvdunfp[11] = 0.8008;
  musvdunfp[12] = 0.9051;
  musvdunfp[13] = 0.9609;
  
  double musvdunfm[14] ={0};
  musvdunfm[1 ] = 0.1421;
  musvdunfm[2 ] = 0.1275;
  musvdunfm[3 ] = 0.1514;
  musvdunfm[4 ] = 0.1769;
  musvdunfm[5 ] = 0.1907;
  musvdunfm[6 ] = 0.2037;
  musvdunfm[7 ] = 0.2255;
  musvdunfm[8 ] = 0.2802;
  musvdunfm[9 ] = 0.3717;
  musvdunfm[10] = 0.4873;
  musvdunfm[11] = 0.6025;
  musvdunfm[12] = 0.6930;
  musvdunfm[13] = 0.7420;

  double muBiasp[14] = {0};
  muBiasp[1 ] = 0.9022;
  muBiasp[2 ] = 0.6571;
  muBiasp[3 ] = 1.1301;
  muBiasp[4 ] = 3.3043;
  muBiasp[5 ] = 2.7469;
  muBiasp[6 ] = 3.0764;
  muBiasp[7 ] = 3.2467;
  muBiasp[8 ] = 5.5057;
  muBiasp[9 ] = 5.3121;
  muBiasp[10] = 1.8476;
  muBiasp[11] = 1.6692;
  muBiasp[12] = 4.4869;
  muBiasp[13] = 5.9061;
 
  double muBiasm[14]={0};
  muBiasm[1 ] = 0.4327;
  muBiasm[2 ] = 0.7800;
  muBiasm[3 ] = 0.3212;
  muBiasm[4 ] = 2.2542;
  muBiasm[5 ] = 2.3913;
  muBiasm[6 ] = 3.4663;
  muBiasm[7 ] = 3.1813;
  muBiasm[8 ] = 4.2104;
  muBiasm[9 ] = 3.7714;
  muBiasm[10] = 1.8951;
  muBiasm[11] = 2.5063;
  muBiasm[12] = 4.7858;
  muBiasm[13] = 6.1218;
/*
  double muWptCorrp[14] = {0};
  muWptCorrp[1 ] = 0.434398;
  muWptCorrp[2 ] = 0.102483;
  muWptCorrp[3 ] = 0.636979;
  muWptCorrp[4 ] = 0.806102;
  muWptCorrp[5 ] = 0.576642;
  muWptCorrp[6 ] = 0.156077;
  muWptCorrp[7 ] = 0.223734;
  muWptCorrp[8 ] = 0.446839;
  muWptCorrp[9 ] = 0.504610;
  muWptCorrp[10] = 0.471174;
  muWptCorrp[11] = 0.408033;
  muWptCorrp[12] = 0.350842;
  muWptCorrp[13] = 0.318765;

  double muWptCorrm[14] ={0};
  muWptCorrm[1 ] = 0.499474;
  muWptCorrm[2 ] = 0.00656399;
  muWptCorrm[3 ] = 0.493798;
  muWptCorrm[4 ] = 0.671649;
  muWptCorrm[5 ] = 0.486533;
  muWptCorrm[6 ] = 0.101952;
  muWptCorrm[7 ] = 0.287443;
  muWptCorrm[8 ] = 0.561686;
  muWptCorrm[9 ] = 0.683695;
  muWptCorrm[10] = 0.702180;
  muWptCorrm[11] = 0.676472;
  muWptCorrm[12] = 0.643882;
  muWptCorrm[13] = 0.624098; 

  for(int i(1);i<14;i++)
  {
    muBiasp[i] = sqrt(muBiasp[i] * muBiasp[i] + muWptCorrp[i] * muWptCorrp[i]) ; 
    muBiasm[i] = sqrt(muBiasm[i] * muBiasm[i] + muWptCorrm[i] * muWptCorrm[i]) ; 
  }
 */ 
  
  double systtotalp[14] = {0};
  double systtotalm[14] = {0};
  for(int i(1);i<14;i++)
  {
    systtotalp[i] =sqrt(mutotaleffp[i] *mutotaleffp[i] +mumetp[i] *mumetp[i] +muMomResp[i] *muMomResp[i] +muqcdshapep[i] *muqcdshapep[i] +muqcdbckgrp[i] *muqcdbckgrp[i] + muewkp[i] *muewkp[i]  +muBiasp[i] *muBiasp[i] +musvdunfp[i] *musvdunfp[i]  +mufsrp[i] *mufsrp[i] + 2.6*2.6);
    systtotalm[i] =sqrt(mutotaleffm[i] *mutotaleffm[i] +mumetm[i] *mumetm[i] +muMomResm[i] *muMomResm[i] +muqcdshapem[i] *muqcdshapem[i] +muqcdbckgrm[i] *muqcdbckgrm[i] + muewkm[i] *muewkm[i]  +muBiasm[i] *muBiasm[i] +musvdunfm[i] *musvdunfm[i]  +mufsrm[i] *mufsrm[i] + 2.6*2.6);
  }

  double totaluncerp[14]={0};
  double totaluncerm[14]={0};
  for(int i(1);i<14;i++)
  {
    totaluncerp[i] = sqrt(mustatp[i] *mustatp[i] +systtotalp[i] *systtotalp[i]);
    totaluncerm[i] = sqrt(mustatm[i] *mustatm[i] +systtotalm[i] *systtotalm[i]);
  }
  
//  Print out result
  cout<<fixed<<setprecision(2);
  
  // Recon. 
  cout<<"Recon. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<< mutotaleffp[i] << "\t" << mutotaleffm[i] <<endl;
  }
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mutotaleffp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mutotaleffm[i] ;
  }
    cout << " \\"<<"\\"<<endl;
    cout << endl;
  
  //Momentum Resolution
  cout<<"MomRes.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<muMomResp[i] <<"\t"<< muMomResm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muMomResp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muMomResm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //MET Resolution
  cout<<"METRes.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<mumetp[i] <<"\t"<< mumetm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mumetp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mumetm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //QCD Background
  cout<<"QCD Bckgr.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<muqcdbckgrp[i] <<"\t"<< muqcdbckgrm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muqcdbckgrp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muqcdbckgrm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //QCD Shape
  cout<<"QCD Shape. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<muqcdshapep[i] <<"\t"<< muqcdshapem[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muqcdshapep[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muqcdshapem[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //EWK
  cout<<"EWK. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<muewkp[i] <<"\t"<< muewkm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muewkp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muewkm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //SVD.Unf
  cout<<"SVD.Unf. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<musvdunfp[i] <<"\t"<< musvdunfm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << musvdunfp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << musvdunfm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //FSR
  cout<<"FSR. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<mufsrp[i] <<"\t"<< mufsrm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mufsrp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mufsrm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //Unf.Bias
  cout<<"Unf.Bias. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<muBiasp[i] <<"\t"<< muBiasm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muBiasp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << muBiasm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //Total syst
  cout<<"Total. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<systtotalp[i] <<"\t"<< systtotalm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << systtotalp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << systtotalm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //Statistical error
  cout<<"Statistical Error"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<mustatp[i] <<"\t"<< mustatm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mustatp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << mustatm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //Total Uncertainty
  cout<<"Total Uncertainty"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<totaluncerp[i] <<"\t"<< totaluncerm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << totaluncerp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << totaluncerm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  // Make Incl
  //*
  TFile *fp = new TFile("ResultWpToMuNu/Result_WpToMuNu.root");
  TFile *fm = new TFile("ResultWmToMuNu/Result_WmToMuNu.root");
  TH1D *h_data_p;
  TH1D *h_data_m;
  TH1D *h_MC_p;
  TH1D *h_MC_m;
  TH1D *h_dataRec_p;
  TH1D *h_dataRec_m;
  h_data_p = (TH1D*)fp->Get("BornEffCorr")->Clone("h_data_p");
  h_data_m = (TH1D*)fm->Get("BornEffCorr")->Clone("h_data_m");
  h_MC_p = (TH1D*)fp->Get("SVD_Born.Gen")->Clone("h_MC_p");
  h_MC_m = (TH1D*)fm->Get("SVD_Born.Gen")->Clone("h_MC_m");
  h_dataRec_p = (TH1D*)fp->Get("data_Rec")->Clone("h_dataRec_p");
  h_dataRec_m = (TH1D*)fm->Get("data_Rec")->Clone("h_dataRec_m");
  cout << "Inclusive Cross-section" << endl;
  cout << "bin\tW+\t\tW-\t\t Wincl"<<endl;
  for( int ipt(1);ipt<14;ipt++)
  {
    cout<<ipt<<"\t"<<h_data_p->GetBinContent(ipt)<<"\t\t"<<h_data_m->GetBinContent(ipt)<< "\t\t" << h_data_p->GetBinContent(ipt)+h_data_m->GetBinContent(ipt) << endl;
  }
  
  double muEffErrp[14]={0};
  double muEffErrm[14]={0};
  double muEffErri[14]={0};
  cout <<"W+ EffErr \t W- EffErr \t W EffErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muEffErrp[i] = h_data_p->GetBinContent(i)*0.01*mutotaleffp[i];
    muEffErrm[i] = h_data_m->GetBinContent(i)*0.01*mutotaleffm[i];
    muEffErri[i] = sqrt(muEffErrp[i]*muEffErrp[i] + muEffErrm[i]*muEffErrm[i]);
    cout << muEffErrp[i] << "\t" << muEffErrm[i] << "\t" << muEffErri[i] << endl;
  }

  double muMomResErrp[14]={0};
  double muMomResErrm[14]={0};
  double muMomResErri[14]={0};
  cout <<"W+ MomResErr \t W- MomResErr \t W EffErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muMomResErrp[i] = h_data_p->GetBinContent(i)*0.01*muMomResp[i];
    muMomResErrm[i] = h_data_m->GetBinContent(i)*0.01*muMomResm[i];
    muMomResErri[i] = sqrt(muMomResErrp[i]*muMomResErrp[i] + muMomResErrm[i]*muMomResErrm[i]);
    cout << muMomResErrp[i] << "\t" << muMomResErrm[i] << "\t" << muMomResErri[i]<<endl;
  }

  double muMetErrp[14]={0};
  double muMetErrm[14]={0};
  double muMetErri[14]={0};
  cout <<"W+ MetErr \t W- MetErr \t W MetErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muMetErrp[i] = h_data_p->GetBinContent(i)*0.01*mumetp[i];
    muMetErrm[i] = h_data_m->GetBinContent(i)*0.01*mumetm[i];
    muMetErri[i] = sqrt(muMetErrp[i]*muMetErrp[i] + muMetErrm[i]*muMetErrm[i]);
    cout << muMetErrp[i] << "\t" << muMetErrm[i] <<"\t" << muMetErri[i]<<endl;
  }
  
  double muQCDBckErrp[14]={0};
  double muQCDBckErrm[14]={0};
  double muQCDBckErri[14]={0};
  cout <<"W+ QCDBckErr \t W- QCDBckErr \t W QCDBckErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muQCDBckErrp[i] = h_data_p->GetBinContent(i)*0.01*muqcdbckgrp[i];
    muQCDBckErrm[i] = h_data_m->GetBinContent(i)*0.01*muqcdbckgrm[i];
    muQCDBckErri[i] = sqrt(muQCDBckErrp[i]*muQCDBckErrp[i] + muQCDBckErrm[i]*muQCDBckErrm[i]);
    cout << muQCDBckErrp[i] << "\t" << muQCDBckErrm[i] <<"\t" << muQCDBckErri[i] <<endl;
  }
  
  double muQCDShapeErrp[14]={0};
  double muQCDShapeErrm[14]={0};
  double muQCDShapeErri[14]={0};
  cout <<"W+ QCDShapeErr \t W- QCDShapeErr \t W QCDShapeErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muQCDShapeErrp[i] = h_data_p->GetBinContent(i)*0.01*muqcdshapep[i];
    muQCDShapeErrm[i] = h_data_m->GetBinContent(i)*0.01*muqcdshapem[i];
    muQCDShapeErri[i] = sqrt(muQCDShapeErrp[i]*muQCDShapeErrp[i] + muQCDShapeErrm[i]*muQCDShapeErrm[i]);
    cout << muQCDShapeErrp[i] << "\t" << muQCDShapeErrm[i] <<"\t" << muQCDShapeErri[i] <<endl;
  }
  
  double muEWKErrp[14]={0};
  double muEWKErrm[14]={0};
  double muEWKErri[14]={0};
  cout <<"W+ EWKErr \t W- EWKErr \t W EWKKErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muEWKErrp[i] = h_data_p->GetBinContent(i)*0.01*muewkp[i];
    muEWKErrm[i] = h_data_m->GetBinContent(i)*0.01*muewkm[i];
    muEWKErri[i] = sqrt(muEWKErrp[i]*muEWKErrp[i] + muEWKErrm[i]*muEWKErrm[i]);
    cout << muEWKErrp[i] << "\t" << muEWKErrm[i] <<"\t" << muEWKErri[i] <<endl;
  }
  
  double muSVDUnfErrp[14]={0};
  double muSVDUnfErrm[14]={0};
  double muSVDUnfErri[14]={0};
  cout <<"W+ SVDUnfErr \t W- SVDUnfErr \t W SVDUnfErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muSVDUnfErrp[i] = h_data_p->GetBinContent(i)*0.01*musvdunfp[i];
    muSVDUnfErrm[i] = h_data_m->GetBinContent(i)*0.01*musvdunfm[i];
    muSVDUnfErri[i] = sqrt(muSVDUnfErrp[i]*muSVDUnfErrp[i] + muSVDUnfErrm[i]*muSVDUnfErrm[i]);
    cout << muSVDUnfErrp[i] << "\t" << muSVDUnfErrm[i] <<"\t" << muSVDUnfErri[i] <<endl;
  }
  
  double muFSRErrp[14]={0};
  double muFSRErrm[14]={0};
  double muFSRErri[14]={0};
  cout <<"W+ FSRErr \t W- FSRErr \t W FSRErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muFSRErrp[i] = h_data_p->GetBinContent(i)*0.01*mufsrp[i];
    muFSRErrm[i] = h_data_m->GetBinContent(i)*0.01*mufsrm[i];
    muFSRErri[i] = sqrt(muFSRErrp[i]*muFSRErrp[i] + muFSRErrm[i]*muFSRErrm[i]);
    cout << muFSRErrp[i] << "\t" << muFSRErrm[i] <<"\t" << muFSRErri[i] <<endl;
  }
  
  double muLumiErrp[14]={0};
  double muLumiErrm[14]={0};
  double muLumiErri[14]={0};
  cout <<"W+ LumiErr \t W- LumiErr \t W LumiErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muLumiErrp[i] = h_data_p->GetBinContent(i)*0.01*2.6;
    muLumiErrm[i] = h_data_m->GetBinContent(i)*0.01*2.6;
    //muLumiErri[i] = sqrt(muLumiErrp[i]*muLumiErrp[i] + muLumiErrm[i]*muLumiErrm[i]);
    muLumiErri[i] = muLumiErrp[i]+muLumiErrm[i];
    cout << muLumiErrp[i] << "\t" << muLumiErrm[i] <<"\t" << muLumiErri[i] <<endl;
  }
  
  double muUnfBiasErrp[14]={0};
  double muUnfBiasErrm[14]={0};
  double muUnfBiasErri[14]={0};
  cout <<"W+ UnfBiasErr \t W- UnfBiasErr \t W UnfBiasErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muUnfBiasErrp[i] = h_data_p->GetBinContent(i)*0.01*muBiasp[i];
    muUnfBiasErrm[i] = h_data_m->GetBinContent(i)*0.01*muBiasm[i];
    muUnfBiasErri[i] = sqrt(muUnfBiasErrp[i]*muUnfBiasErrp[i] + muUnfBiasErrm[i]*muUnfBiasErrm[i]);
    cout << muUnfBiasErrp[i] << "\t" << muUnfBiasErrm[i] <<"\t" << muUnfBiasErri[i] <<endl;
  }
  
  double muStatErrp[14]={0};
  double muStatErrm[14]={0};
  double muStatErri[14]={0};
  cout <<"W+ StatErr \t W- StatErr \t W StatErr" <<endl;
  for(int i(1);i<14;i++)
  {
    muStatErrp[i] = h_data_p->GetBinContent(i)*0.01*mustatp[i];
    muStatErrm[i] = h_data_m->GetBinContent(i)*0.01*mustatm[i];
    muStatErri[i] = sqrt(muStatErrp[i]*muStatErrp[i] + muStatErrm[i]*muStatErrm[i]);
    cout << muStatErrp[i] << "\t" << muStatErrm[i] <<"\t" << muStatErri[i] <<endl;
  }
  
  double muTotalUnceri[14]={0};
  cout <<" Wincl TotalUncertainty" <<endl;
  for(int i(1);i<14;i++)
  {
    muTotalUnceri[i] = sqrt(muEffErri[i]*muEffErri[i] + muMomResErri[i]*muMomResErri[i]+muMetErri[i]*muMetErri[i]+ muQCDBckErri[i]*muQCDBckErri[i] + muQCDShapeErri[i]*muQCDShapeErri[i]+ muEWKErri[i]*muEWKErri[i] + muSVDUnfErri[i]*muSVDUnfErri[i] + muFSRErri[i]*muFSRErri[i]+ muLumiErri[i]*muLumiErri[i] + muUnfBiasErri[i]*muUnfBiasErri[i]+ muStatErri[i]*muStatErri[i]);
   // muTotalUnceri[i] = muEffErri[i] + muMomResErri[i] + muMetErri[i] + muQCDBckErri[i] + muQCDShapeErri[i] + muEWKErri[i] + muSVDUnfErri[i] + muFSRErri[i] + muLumiErri[i] + muUnfBiasErri[i] + muStatErri[i];
    cout << muTotalUnceri[i] <<endl;
  }

  TString resultDir = "ResultWinclToMuNu";
  gSystem->mkdir(resultDir,kTRUE);

  TFile f_out(resultDir+"/Result_WinclMu.root","recreate");
  TH1D* BornEffCorr = new TH1D("BornEffCorr","BornEffCorr",13,0,13);
  TH1D* PowhegErr = new TH1D("PowhegErr","PowhegErr",13,0,13);
  TH1D* SVD_BornGen = new TH1D("SVD_BornGen","SVD_BornGen",13,0,13);SVD_BornGen->Sumw2();
  TH1D* data_Rec = new TH1D("data_Rec","data_Rec",13,0,13);data_Rec->Sumw2();
    
    for(int i(1);i<14;i++)
    {
      BornEffCorr->SetBinContent(i,h_data_p->GetBinContent(i) + h_data_m->GetBinContent(i));
      BornEffCorr->SetBinError(i,muTotalUnceri[i]);
      SVD_BornGen->SetBinContent(i,h_MC_p->GetBinContent(i) + h_MC_m->GetBinContent(i));
      SVD_BornGen->SetBinError(i,sqrt(h_MC_p->GetBinContent(i)+h_MC_p->GetBinError(i)*h_MC_p->GetBinError(i) +h_MC_m->GetBinContent(i)+ h_MC_m->GetBinError(i)*h_MC_m->GetBinError(i)));
      data_Rec->SetBinContent(i,h_dataRec_p->GetBinContent(i) + h_dataRec_m->GetBinContent(i));
      data_Rec->SetBinError(i,sqrt(h_dataRec_p->GetBinError(i)*h_dataRec_p->GetBinError(i) + h_dataRec_m->GetBinError(i)*h_dataRec_m->GetBinError(i)));
      PowhegErr->SetBinContent(i,sqrt(h_MC_p->GetBinError(i)*h_MC_p->GetBinError(i) + h_MC_m->GetBinError(i)*h_MC_m->GetBinError(i)));
    }
    BornEffCorr->Write();
    PowhegErr->Write();
    SVD_BornGen->Write();
    data_Rec->Write();

  // */
}
