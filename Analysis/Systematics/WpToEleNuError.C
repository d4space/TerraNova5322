{
#include "../Utils/const.h"
 //*
  double elestatp[14] = {0};
  elestatp[1 ]= 1.0752 ; 
  elestatp[2 ]= 1.0567 ;
  elestatp[3 ]= 1.1783 ;
  elestatp[4 ]= 1.2620 ;
  elestatp[5 ]= 1.6822 ;
  elestatp[6 ]= 1.6760 ;
  elestatp[7 ]= 2.2662 ;
  elestatp[8 ]= 2.3749 ;
  elestatp[9 ]= 2.8686 ;
  elestatp[10]= 5.9348 ;
  elestatp[11]= 10.0838;
  elestatp[12]= 14.2986;
  elestatp[13]= 24.4511;

  double elestatm[14] = {0};
  elestatm[1 ] = 1.3125 ;
  elestatm[2 ] = 1.2542 ;
  elestatm[3 ] = 1.4351 ;
  elestatm[4 ] = 1.5077 ;
  elestatm[5 ] = 2.0249 ;
  elestatm[6 ] = 2.0699 ;
  elestatm[7 ] = 2.6916 ;
  elestatm[8 ] = 2.6401 ;
  elestatm[9 ] = 3.3518 ;
  elestatm[10] = 6.8042 ;
  elestatm[11] = 12.2459;
  elestatm[12] = 17.8293;
  elestatm[13] = 25.4102;

  double elebinp[14]={0};
  elebinp[1 ]= 0.65;
  elebinp[2 ]= 0.59;
  elebinp[3 ]= 0.56;
  elebinp[4 ]= 0.53;
  elebinp[5 ]= 0.53;
  elebinp[6 ]= 0.53;
  elebinp[7 ]= 0.54;
  elebinp[8 ]= 0.62;
  elebinp[9 ]= 0.62;
  elebinp[10]= 0.73;
  elebinp[11]= 0.85;
  elebinp[12]= 0.94;
  elebinp[13]= 0.98;

  double elebinm[14] ={0};
  elebinm[1 ]= 0.59; 
  elebinm[2 ]= 0.58;
  elebinm[3 ]= 0.43;
  elebinm[4 ]= 0.43;
  elebinm[5 ]= 0.49;
  elebinm[6 ]= 0.31;
  elebinm[7 ]= 0.36;
  elebinm[8 ]= 0.57;
  elebinm[9 ]= 0.72;
  elebinm[10]= 0.73;
  elebinm[11]= 0.83;
  elebinm[12]= 1.01;
  elebinm[13]= 1.11;
 
  double elesigp[14] = {0};
  elesigp[1 ]= 1.54;
  elesigp[2 ]= 1.54;
  elesigp[3 ]= 1.37;
  elesigp[4 ]= 1.01;
  elesigp[5 ]= 0.69;
  elesigp[6 ]= 0.36;
  elesigp[7 ]= 0.81;
  elesigp[8 ]= 1.54;
  elesigp[9 ]= 1.28;
  elesigp[10]= 1.20;
  elesigp[11]= 1.39;
  elesigp[12]= 1.63;
  elesigp[13]= 1.75;
 
  double elesigm[14] ={0};
  elesigm[1 ]= 1.39;
  elesigm[2 ]= 1.42;
  elesigm[3 ]= 1.42;
  elesigm[4 ]= 1.17;
  elesigm[5 ]= 0.74;
  elesigm[6 ]= 0.28;
  elesigm[7 ]= 0.40;
  elesigm[8 ]= 0.69;
  elesigm[9 ]= 1.29; 
  elesigm[10]= 1.82;
  elesigm[11]= 2.14;
  elesigm[12]= 2.31;
  elesigm[13]= 2.39;
  
  double elebckgrp[14] = {0};
  elebckgrp[1 ] = 0.28;
  elebckgrp[2 ] = 0.25;
  elebckgrp[3 ] = 0.25;
  elebckgrp[4 ] = 0.29;
  elebckgrp[5 ] = 0.36;
  elebckgrp[6 ] = 0.42;
  elebckgrp[7 ] = 0.48;
  elebckgrp[8 ] = 0.53;
  elebckgrp[9 ] = 0.64;
  elebckgrp[10] = 0.80;
  elebckgrp[11] = 0.91;
  elebckgrp[12] = 1.00;
  elebckgrp[13] = 1.05;

  double elebckgrm[14] = {0};
  elebckgrm[1 ] = 0.68;
  elebckgrm[2 ] = 0.61; 
  elebckgrm[3 ] = 0.49;
  elebckgrm[4 ] = 0.38;
  elebckgrm[5 ] = 0.30;
  elebckgrm[6 ] = 0.26;
  elebckgrm[7 ] = 0.38;
  elebckgrm[8 ] = 0.57;
  elebckgrm[9 ] = 0.73;
  elebckgrm[10] = 0.68;
  elebckgrm[11] = 0.75;
  elebckgrm[12] = 0.78;
  elebckgrm[13] = 0.88;

  double eletoyp[14] = {0};
  eletoyp[1 ] = 0.17;
  eletoyp[2 ] = 0.11;
  eletoyp[3 ] = 0.23;
  eletoyp[4 ] = 0.34;
  eletoyp[5 ] = 0.42;
  eletoyp[6 ] = 0.41;
  eletoyp[7 ] = 0.44;
  eletoyp[8 ] = 0.70;
  eletoyp[9 ] = 0.78;
  eletoyp[10] = 1.01;
  eletoyp[11] = 1.27;
  eletoyp[12] = 1.59;
  eletoyp[13] = 1.30;

  double eletoym[14] = {0};
  eletoym[1 ] = 0.19;
  eletoym[2 ] = 0.10;
  eletoym[3 ] = 0.26;
  eletoym[4 ] = 0.36;
  eletoym[5 ] = 0.34;
  eletoym[6 ] = 0.44;
  eletoym[7 ] = 0.43;
  eletoym[8 ] = 0.60;
  eletoym[9 ] = 1.22;
  eletoym[10] = 1.10;
  eletoym[11] = 0.84;
  eletoym[12] = 2.09;
  eletoym[13] = 1.51;

  double eletotaleffp[14]={0};
  double eletotaleffm[14]={0};
  for(int i(1);i<14;i++)
  {
    eletotaleffp[i]  = sqrt(elebinp[i] *elebinp[i] + elesigp[i]*elesigp[i] + elebckgrp[i]*elebckgrp[i] + eletoyp[i] *eletoyp[i] );
    eletotaleffm[i]  = sqrt(elebinm[i] *elebinm[i] + elesigm[i]*elesigm[i] + elebckgrm[i]*elebckgrm[i] + eletoym[i] *eletoym[i] );
  } 
  
  double elemetp[14] = {0};
  elemetp[1 ] = 0.07; 
  elemetp[2 ] = 0.04;
  elemetp[3 ] = 0.07;
  elemetp[4 ] = 0.09;
  elemetp[5 ] = 0.08;
  elemetp[6 ] = 0.08;
  elemetp[7 ] = 0.17;
  elemetp[8 ] = 0.20;
  elemetp[9 ] = 0.18;
  elemetp[10] = 0.28;
  elemetp[11] = 0.53;
  elemetp[12] = 1.01;
  elemetp[13] = 3.16;

  double elemetm[14] ={0};
  elemetm[1 ] = 0.10;
  elemetm[2 ] = 0.04;
  elemetm[3 ] = 0.09;
  elemetm[4 ] = 0.12;
  elemetm[5 ] = 0.10;
  elemetm[6 ] = 0.10;
  elemetm[7 ] = 0.13;
  elemetm[8 ] = 0.23;
  elemetm[9 ] = 0.24;
  elemetm[10] = 0.43;
  elemetm[11] = 0.84;
  elemetm[12] = 1.14;
  elemetm[13] = 2.71;

  double elescalep[14] = {0};
  elescalep[1 ] = 0.35; 
  elescalep[2 ] = 0.19;
  elescalep[3 ] = 0.14;
  elescalep[4 ] = 0.21;
  elescalep[5 ] = 0.15;
  elescalep[6 ] = 0.17;
  elescalep[7 ] = 0.24;
  elescalep[8 ] = 0.43;
  elescalep[9 ] = 0.36;
  elescalep[10] = 0.18;
  elescalep[11] = 0.19;
  elescalep[12] = 0.29;
  elescalep[13] = 0.20;

  double elescalem[14] ={0};
  elescalem[1 ] = 0.06; 
  elescalem[2 ] = 0.12;
  elescalem[3 ] = 0.18;
  elescalem[4 ] = 0.28;
  elescalem[5 ] = 0.15;
  elescalem[6 ] = 0.21;
  elescalem[7 ] = 0.33;
  elescalem[8 ] = 0.57;
  elescalem[9 ] = 0.66;
  elescalem[10] = 0.71;
  elescalem[11] = 0.67;
  elescalem[12] = 1.10;
  elescalem[13] = 0.56;

  double elesmearp[14] ={0};
  elesmearp[1 ] = 0.1925; 
  elesmearp[2 ] = 0.1171;
  elesmearp[3 ] = 0.2128;
  elesmearp[4 ] = 0.2856;
  elesmearp[5 ] = 0.3235;
  elesmearp[6 ] = 0.3091;
  elesmearp[7 ] = 0.3859;
  elesmearp[8 ] = 0.5160;
  elesmearp[9 ] = 0.9845;
  elesmearp[10] = 0.9941;
  elesmearp[11] = 1.3365;
  elesmearp[12] = 1.5571;
  elesmearp[13] = 1.3165;

  double elesmearm[14] = {0};
  elesmearm[1 ] = 0.2141; 
  elesmearm[2 ] = 0.1048;
  elesmearm[3 ] = 0.2826;
  elesmearm[4 ] = 0.4092;
  elesmearm[5 ] = 0.4038;
  elesmearm[6 ] = 0.4418;
  elesmearm[7 ] = 0.4065;
  elesmearm[8 ] = 0.5679;
  elesmearm[9 ] = 1.3676;
  elesmearm[10] = 0.8140;
  elesmearm[11] = 1.2340;
  elesmearm[12] = 1.9885;
  elesmearm[13] = 1.4780;

  double eleEnResp[14]={0};
  double eleEnResm[14]={0};
  for(int i(1);i<14;i++)
  {
    eleEnResp[i]  = sqrt(elesmearp[i] *elesmearp[i] +elescalep[i] *elescalep[i] ); 
    eleEnResm[i]  = sqrt(elesmearm[i] *elesmearm[i] +elescalem[i] *elescalem[i] ); 
  }
  
  double eleqcdbckgrp[14]={0};
  eleqcdbckgrp[1 ] = 1.0729;
  eleqcdbckgrp[2 ] = 1.1023;
  eleqcdbckgrp[3 ] = 0.5858;
  eleqcdbckgrp[4 ] = 0.9564;
  eleqcdbckgrp[5 ] = 1.1488;
  eleqcdbckgrp[6 ] = 1.9617;
  eleqcdbckgrp[7 ] = 1.2419;
  eleqcdbckgrp[8 ] = 2.6948;
  eleqcdbckgrp[9 ] = 1.1687; 
  eleqcdbckgrp[10] = 1.6848;
  eleqcdbckgrp[11] = 1.8207;
  eleqcdbckgrp[12] = 1.7103;
  eleqcdbckgrp[13] = 1.9070;
 
  double eleqcdbckgrm[14]={0};
  eleqcdbckgrm[1 ] = 0.7984;
  eleqcdbckgrm[2 ] = 0.7248;
  eleqcdbckgrm[3 ] = 0.5155;
  eleqcdbckgrm[4 ] = 0.7454;
  eleqcdbckgrm[5 ] = 0.8799;
  eleqcdbckgrm[6 ] = 1.4930;
  eleqcdbckgrm[7 ] = 0.9734;
  eleqcdbckgrm[8 ] = 2.0400;
  eleqcdbckgrm[9 ] = 0.7698; 
  eleqcdbckgrm[10] = 2.1598;
  eleqcdbckgrm[11] = 1.4424;
  eleqcdbckgrm[12] = 1.3827;
  eleqcdbckgrm[13] = 3.4378;

  double eleqcdshapep[14] = {0};
  eleqcdshapep[1 ] = 0.3621;
  eleqcdshapep[2 ] = 0.4677;
  eleqcdshapep[3 ] = 0.6164;
  eleqcdshapep[4 ] = 0.4155;
  eleqcdshapep[5 ] = 0.6913;
  eleqcdshapep[6 ] = 0.6007;
  eleqcdshapep[7 ] = 0.6103;
  eleqcdshapep[8 ] = 0.8874;
  eleqcdshapep[9 ] = 0.8704; 
  eleqcdshapep[10] = 0.9543;
  eleqcdshapep[11] = 0.4220;
  eleqcdshapep[12] = 0.8768;
  eleqcdshapep[13] = 0.8999;
 
  double eleqcdshapem[14] ={0};
  eleqcdshapem[1 ] = 0.3548;
  eleqcdshapem[2 ] = 0.2352;
  eleqcdshapem[3 ] = 0.3452;
  eleqcdshapem[4 ] = 0.9577;
  eleqcdshapem[5 ] = 0.8137;
  eleqcdshapem[6 ] = 0.4763;
  eleqcdshapem[7 ] = 0.6415;
  eleqcdshapem[8 ] = 0.6790;
  eleqcdshapem[9 ] = 0.8890; 
  eleqcdshapem[10] = 0.6282;
  eleqcdshapem[11] = 0.9061;
  eleqcdshapem[12] = 0.7652;
  eleqcdshapem[13] = 0.8495;

  double eleewkp[14] ={0};
  eleewkp[1 ] = 0.10;
  eleewkp[2 ] = 0.07;
  eleewkp[3 ] = 0.08;
  eleewkp[4 ] = 0.10;
  eleewkp[5 ] = 0.13;
  eleewkp[6 ] = 0.18;
  eleewkp[7 ] = 0.24;
  eleewkp[8 ] = 0.34;
  eleewkp[9 ] = 0.42; 
  eleewkp[10] = 0.41;
  eleewkp[11] = 0.49;
  eleewkp[12] = 0.50;
  eleewkp[13] = 0.54;
 
  double eleewkm[14] ={0};
  eleewkm[1 ] = 0.09;
  eleewkm[2 ] = 0.11;
  eleewkm[3 ] = 0.21;
  eleewkm[4 ] = 0.34;
  eleewkm[5 ] = 0.21;
  eleewkm[6 ] = 0.23;
  eleewkm[7 ] = 0.26;
  eleewkm[8 ] = 0.32;
  eleewkm[9 ] = 0.48; 
  eleewkm[10] = 0.48;
  eleewkm[11] = 0.95;
  eleewkm[12] = 0.73;
  eleewkm[13] = 0.33;

  double elefsrp[14] ={0};
  elefsrp[1 ] = 0.135506;
  elefsrp[2 ] = 0.149677;
  elefsrp[3 ] = 0.114017;
  elefsrp[4 ] = 0.0665356;
  elefsrp[5 ] = 0.126617;
  elefsrp[6 ] = 0.290229;
  elefsrp[7 ] = 0.585178;
  elefsrp[8 ] = 0.729473;
  elefsrp[9 ] = 1.07369;
  elefsrp[10] = 1.91924; 
  elefsrp[11] = 1.33236; 
  elefsrp[12] = 1.3188;  
  elefsrp[13] = 1.33945; 
 
  double elefsrm[14] ={0};
  elefsrm[1 ] = 0.0903484;
  elefsrm[2 ] = 0.0934524;
  elefsrm[3 ] = 0.0748422;
  elefsrm[4 ] = 0.117356; 
  elefsrm[5 ] = 0.141232; 
  elefsrm[6 ] = 0.333736; 
  elefsrm[7 ] = 0.231212; 
  elefsrm[8 ] = 0.710899; 
  elefsrm[9 ] = 1.159;    
  elefsrm[10] = 0.819618; 
  elefsrm[11] = 0.761551; 
  elefsrm[12] = 1.81484;  
  elefsrm[13] = 0.757732; 

  double elesvdunfp[14] ={0};
  elesvdunfp[1 ] = 0.1153;
  elesvdunfp[2 ] = 0.1043;
  elesvdunfp[3 ] = 0.1063;
  elesvdunfp[4 ] = 0.1227;
  elesvdunfp[5 ] = 0.1418;
  elesvdunfp[6 ] = 0.1621;
  elesvdunfp[7 ] = 0.1875;
  elesvdunfp[8 ] = 0.2223;
  elesvdunfp[9 ] = 0.2622;
  elesvdunfp[10] = 0.3000;
  elesvdunfp[11] = 0.3312;
  elesvdunfp[12] = 0.3531;
  elesvdunfp[13] = 0.3644;
  
  double elesvdunfm[14] ={0};
  elesvdunfm[1 ] = 0.1196;
  elesvdunfm[2 ] = 0.1094;
  elesvdunfm[3 ] = 0.1138;
  elesvdunfm[4 ] = 0.1303;
  elesvdunfm[5 ] = 0.1481;
  elesvdunfm[6 ] = 0.1684;
  elesvdunfm[7 ] = 0.1979;
  elesvdunfm[8 ] = 0.2364;
  elesvdunfm[9 ] = 0.2783;
  elesvdunfm[10] = 0.3174;
  elesvdunfm[11] = 0.3489;
  elesvdunfm[12] = 0.3706;
  elesvdunfm[13] = 0.3816;

  double eleBiasp[14] = {0};
  eleBiasp[1 ] = 0.7707;
  eleBiasp[2 ] = 0.4368;
  eleBiasp[3 ] = 0.4672;
  eleBiasp[4 ] = 1.6650;
  eleBiasp[5 ] = 2.2206;
  eleBiasp[6 ] = 2.9381;
  eleBiasp[7 ] = 3.8440;
  eleBiasp[8 ] = 5.4072;
  eleBiasp[9 ] = 5.5939;
  eleBiasp[10] = 4.0037;
  eleBiasp[11] = 3.4396;
  eleBiasp[12] = 4.0359;
  eleBiasp[13] = 4.6224;
 
  double eleBiasm[14]={0};
  eleBiasm[1 ] = 0.9882;
  eleBiasm[2 ] = 0.5143;
  eleBiasm[3 ] = 0.4613;
  eleBiasm[4 ] = 1.6006;
  eleBiasm[5 ] = 2.1511;
  eleBiasm[6 ] = 2.9418;
  eleBiasm[7 ] = 3.8949;
  eleBiasm[8 ] = 5.5269;
  eleBiasm[9 ] = 5.8131;
  eleBiasm[10] = 4.1519;
  eleBiasm[11] = 3.5869;
  eleBiasm[12] = 4.8048;
  eleBiasm[13] = 5.9106;
/*
  double eleWptCorrp[14] = {0};
  eleWptCorrp[1 ] = 0.915318; 
  eleWptCorrp[2 ] = 0.0294394;
  eleWptCorrp[3 ] = 0.793438; 
  eleWptCorrp[4 ] = 1.00581;  
  eleWptCorrp[5 ] = 0.659224; 
  eleWptCorrp[6 ] = 0.121046; 
  eleWptCorrp[7 ] = 0.299264; 
  eleWptCorrp[8 ] = 0.525082; 
  eleWptCorrp[9 ] = 0.592397; 
  eleWptCorrp[10] = 0.57529;  
  eleWptCorrp[11] = 0.529585; 
  eleWptCorrp[12] = 0.486141; 
  eleWptCorrp[13] = 0.461337; 

  double eleWptCorrm[14] ={0};
  eleWptCorrm[1 ] = 1.21547; 
  eleWptCorrm[2 ] = 0.262792;
  eleWptCorrm[3 ] = 0.743959;
  eleWptCorrm[4 ] = 1.17545; 
  eleWptCorrm[5 ] = 0.937213;
  eleWptCorrm[6 ] = 0.336006;
  eleWptCorrm[7 ] = 0.252154;
  eleWptCorrm[8 ] = 0.603749;
  eleWptCorrm[9 ] = 0.671394;
  eleWptCorrm[10] = 0.576984;
  eleWptCorrm[11] = 0.437997;
  eleWptCorrm[12] = 0.319664;
  eleWptCorrm[13] = 0.255065;

  for(int i(1);i<14;i++)
  {
    eleBiasp[i] = sqrt(eleBiasp[i] * eleBiasp[i] + eleWptCorrp[i] * eleWptCorrp[i]) ; 
    eleBiasm[i] = sqrt(eleBiasm[i] * eleBiasm[i] + eleWptCorrm[i] * eleWptCorrm[i]) ; 
  }
 */ 

  double systtotalp[14] = {0};
  double systtotalm[14] = {0};
  for(int i(1);i<14;i++)
  {
    systtotalp[i] =sqrt(eletotaleffp[i] *eletotaleffp[i] +elemetp[i] *elemetp[i] +eleEnResp[i] *eleEnResp[i] +eleqcdshapep[i] *eleqcdshapep[i] +eleqcdbckgrp[i] *eleqcdbckgrp[i] + eleewkp[i] *eleewkp[i]  +eleBiasp[i] *eleBiasp[i] +elesvdunfp[i] *elesvdunfp[i]  +elefsrp[i] *elefsrp[i] + 2.6*2.6);
    systtotalm[i] =sqrt(eletotaleffm[i] *eletotaleffm[i] +elemetm[i] *elemetm[i] +eleEnResm[i] *eleEnResm[i] +eleqcdshapem[i] *eleqcdshapem[i] +eleqcdbckgrm[i] *eleqcdbckgrm[i] + eleewkm[i] *eleewkm[i]  +eleBiasm[i] *eleBiasm[i] +elesvdunfm[i] *elesvdunfm[i]  +elefsrm[i] *elefsrm[i] + 2.6*2.6);
  }

  double totaluncerp[14]={0};
  double totaluncerm[14]={0};
  for(int i(1);i<14;i++)
  {
    totaluncerp[i] = sqrt(elestatp[i] *elestatp[i] +systtotalp[i] *systtotalp[i]);
    totaluncerm[i] = sqrt(elestatm[i] *elestatm[i] +systtotalm[i] *systtotalm[i]);
  }
 
//  Print out result
  cout<<fixed<<setprecision(2);
  
  // Recon. 
  cout<<"Recon. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<< eletotaleffp[i] << "\t" << eletotaleffm[i] <<endl;
  }
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eletotaleffp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eletotaleffm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;
  
  //Energy Resolution
  cout<<"EnRes.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<eleEnResp[i] <<"\t"<< eleEnResm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleEnResp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleEnResm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //MET Resolution
  cout<<"METRes.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<elemetp[i] <<"\t"<< elemetm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elemetp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elemetm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //QCD Background
  cout<<"QCD Bckgr.Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<eleqcdbckgrp[i] <<"\t"<< eleqcdbckgrm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleqcdbckgrp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleqcdbckgrm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //QCD Shape
  cout<<"QCD Shape. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<eleqcdshapep[i] <<"\t"<< eleqcdshapem[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleqcdshapep[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleqcdshapem[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //EWK
  cout<<"EWK. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<eleewkp[i] <<"\t"<< eleewkm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleewkp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleewkm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //SVD.Unf
  cout<<"SVD.Unf. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<elesvdunfp[i] <<"\t"<< elesvdunfm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elesvdunfp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elesvdunfm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //FSR
  cout<<"FSR. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<elefsrp[i] <<"\t"<< elefsrm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elefsrp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elefsrm[i] ;
  }
    cout << " \\"<<"\\" << endl;
    cout << endl;

  //Unf.Bias
  cout<<"Unf.Bias. Syst"<<endl;
  cout<<"W+ \t W-"<<endl;
  for(int i(1);i<14;i++)
  {
    cout<<eleBiasp[i] <<"\t"<< eleBiasm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleBiasp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << eleBiasm[i] ;
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
    cout<<elestatp[i] <<"\t"<< elestatm[i]<<endl; 
  } 
  cout << "======= Put in note=======" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elestatp[i] ;
  }
    cout << " \\"<<"\\" << endl;
  for(int i(1);i<14;i++)
  {
    cout<< " & " << elestatm[i] ;
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
  TFile *fp = new TFile("../Unfolding/ResultWpToEleNu/Result_WpToEleNu.root");
  TFile *fm = new TFile("../Unfolding/ResultWmToEleNu/Result_WmToEleNu.root");
  TH1D *h_data_p;
  TH1D *h_data_m;
  TH1D *h_MC_p;
  TH1D *h_MC_m;
  TH1D *h_MC_p_UnWeighted;
  TH1D *h_MC_m_UnWeighted;
  TH1D *h_dataRec_p;
  TH1D *h_dataRec_m;
  h_data_p = (TH1D*)fp->Get("BornEffCorr")->Clone("h_data_p");
  h_data_m = (TH1D*)fm->Get("BornEffCorr")->Clone("h_data_m");
  h_MC_p = (TH1D*)fp->Get("SVD_Born.Gen")->Clone("h_MC_p");
  h_MC_m = (TH1D*)fm->Get("SVD_Born.Gen")->Clone("h_MC_m");
  h_MC_p_UnWeighted = (TH1D*)fp->Get("SVD_Born.Gen")->Clone("h_MC_p_UnWeighted");
  h_MC_m_UnWeighted = (TH1D*)fm->Get("SVD_Born.Gen")->Clone("h_MC_m_UnWeighted");
  // To make SVD_Born.Gen to h1_Born_BornFid(Not LumiWeighted)
    h_MC_p_UnWeighted->Scale(1./LumiWeight_Ele_WpToEleNu_S8);
    h_MC_m_UnWeighted->Scale(1./LumiWeight_Ele_WmToEleNu_S8);
  
  h_dataRec_p = (TH1D*)fp->Get("data_Rec")->Clone("h_dataRec_p");
  h_dataRec_m = (TH1D*)fm->Get("data_Rec")->Clone("h_dataRec_m");
  cout << "Inclusive Cross-section" << endl;
  cout << "bin\tW+\t\tW-"<<endl;
  for( int ipt(1);ipt<14;ipt++)
  {
    cout<<ipt<<"\t"<<h_data_p->GetBinContent(ipt)<<"\t\t"<<h_data_m->GetBinContent(ipt)<<endl;
  }
  
  double eleEffErrp[14]={0};
  double eleEffErrm[14]={0};
  double eleEffErri[14]={0};
  cout <<"W+ EffErr \t W- EffErr \t W EffErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleEffErrp[i] = h_data_p->GetBinContent(i)*0.01*eletotaleffp[i];
    eleEffErrm[i] = h_data_m->GetBinContent(i)*0.01*eletotaleffm[i];
    eleEffErri[i] = sqrt(eleEffErrp[i]*eleEffErrp[i] + eleEffErrm[i]*eleEffErrm[i]);
    cout << eleEffErrp[i] << "\t" << eleEffErrm[i] << "\t" << eleEffErri[i] << endl;
  }

  double eleEnResErrp[14]={0};
  double eleEnResErrm[14]={0};
  double eleEnResErri[14]={0};
  cout <<"W+ MomResErr \t W- MomResErr \t W EffErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleEnResErrp[i] = h_data_p->GetBinContent(i)*0.01*eleEnResp[i];
    eleEnResErrm[i] = h_data_m->GetBinContent(i)*0.01*eleEnResm[i];
    eleEnResErri[i] = sqrt(eleEnResErrp[i]*eleEnResErrp[i] + eleEnResErrm[i]*eleEnResErrm[i]);
    cout << eleEnResErrp[i] << "\t" << eleEnResErrm[i] << "\t" << eleEnResErri[i]<<endl;
  }

  double eleMetErrp[14]={0};
  double eleMetErrm[14]={0};
  double eleMetErri[14]={0};
  cout <<"W+ MetErr \t W- MetErr \t W MetErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleMetErrp[i] = h_data_p->GetBinContent(i)*0.01*elemetp[i];
    eleMetErrm[i] = h_data_m->GetBinContent(i)*0.01*elemetm[i];
    eleMetErri[i] = sqrt(eleMetErrp[i]*eleMetErrp[i] + eleMetErrm[i]*eleMetErrm[i]);
    cout << eleMetErrp[i] << "\t" << eleMetErrm[i] <<"\t" << eleMetErri[i]<<endl;
  }
  
  double eleQCDBckErrp[14]={0};
  double eleQCDBckErrm[14]={0};
  double eleQCDBckErri[14]={0};
  cout <<"W+ QCDBckErr \t W- QCDBckErr \t W QCDBckErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleQCDBckErrp[i] = h_data_p->GetBinContent(i)*0.01*eleqcdbckgrp[i];
    eleQCDBckErrm[i] = h_data_m->GetBinContent(i)*0.01*eleqcdbckgrm[i];
    eleQCDBckErri[i] = sqrt(eleQCDBckErrp[i]*eleQCDBckErrp[i] + eleQCDBckErrm[i]*eleQCDBckErrm[i]);
    cout << eleQCDBckErrp[i] << "\t" << eleQCDBckErrm[i] <<"\t" << eleQCDBckErri[i] <<endl;
  }
  
  double eleQCDShapeErrp[14]={0};
  double eleQCDShapeErrm[14]={0};
  double eleQCDShapeErri[14]={0};
  cout <<"W+ QCDShapeErr \t W- QCDShapeErr \t W QCDShapeErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleQCDShapeErrp[i] = h_data_p->GetBinContent(i)*0.01*eleqcdshapep[i];
    eleQCDShapeErrm[i] = h_data_m->GetBinContent(i)*0.01*eleqcdshapem[i];
    eleQCDShapeErri[i] = sqrt(eleQCDShapeErrp[i]*eleQCDShapeErrp[i] + eleQCDShapeErrm[i]*eleQCDShapeErrm[i]);
    cout << eleQCDShapeErrp[i] << "\t" << eleQCDShapeErrm[i] <<"\t" << eleQCDShapeErri[i] <<endl;
  }
  
  double eleEWKErrp[14]={0};
  double eleEWKErrm[14]={0};
  double eleEWKErri[14]={0};
  cout <<"W+ EWKErr \t W- EWKErr \t W EWKKErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleEWKErrp[i] = h_data_p->GetBinContent(i)*0.01*eleewkp[i];
    eleEWKErrm[i] = h_data_m->GetBinContent(i)*0.01*eleewkm[i];
    //eleEWKErri[i] = sqrt(eleEWKErrp[i]*eleEWKErrp[i] + eleEWKErrm[i]*eleEWKErrm[i]);
    eleEWKErri[i] = eleEWKErrp[i] + eleEWKErrm[i];
    cout << eleEWKErrp[i] << "\t" << eleEWKErrm[i] <<"\t" << eleEWKErri[i] <<endl;
  }
  
  double eleSVDUnfErrp[14]={0};
  double eleSVDUnfErrm[14]={0};
  double eleSVDUnfErri[14]={0};
  cout <<"W+ SVDUnfErr \t W- SVDUnfErr \t W SVDUnfErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleSVDUnfErrp[i] = h_data_p->GetBinContent(i)*0.01*elesvdunfp[i];
    eleSVDUnfErrm[i] = h_data_m->GetBinContent(i)*0.01*elesvdunfm[i];
    eleSVDUnfErri[i] = sqrt(eleSVDUnfErrp[i]*eleSVDUnfErrp[i] + eleSVDUnfErrm[i]*eleSVDUnfErrm[i]);
    cout << eleSVDUnfErrp[i] << "\t" << eleSVDUnfErrm[i] <<"\t" << eleSVDUnfErri[i] <<endl;
  }
  
  double eleFSRErrp[14]={0};
  double eleFSRErrm[14]={0};
  double eleFSRErri[14]={0};
  cout <<"W+ FSRErr \t W- FSRErr \t W FSRErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleFSRErrp[i] = h_data_p->GetBinContent(i)*0.01*elefsrp[i];
    eleFSRErrm[i] = h_data_m->GetBinContent(i)*0.01*elefsrm[i];
    //eleFSRErri[i] = sqrt(eleFSRErrp[i]*eleFSRErrp[i] + eleFSRErrm[i]*eleFSRErrm[i]);
    eleFSRErri[i] = eleFSRErrp[i] + eleFSRErrm[i];
    cout << eleFSRErrp[i] << "\t" << eleFSRErrm[i] <<"\t" << eleFSRErri[i] <<endl;
  }
  
  double eleLumiErrp[14]={0};
  double eleLumiErrm[14]={0};
  double eleLumiErri[14]={0};
  cout <<"W+ LumiErr \t W- LumiErr \t W LumiErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleLumiErrp[i] = h_data_p->GetBinContent(i)*0.01*2.6;
    eleLumiErrm[i] = h_data_m->GetBinContent(i)*0.01*2.6;
    //eleLumiErri[i] = sqrt(eleLumiErrp[i]*eleLumiErrp[i] + eleLumiErrm[i]*eleLumiErrm[i]);
    eleLumiErri[i] = eleLumiErrp[i]+eleLumiErrm[i];
    cout << eleLumiErrp[i] << "\t" << eleLumiErrm[i] <<"\t" << eleLumiErri[i] <<endl;
  }
  
  double eleUnfBiasErrp[14]={0};
  double eleUnfBiasErrm[14]={0};
  double eleUnfBiasErri[14]={0};
  cout <<"W+ UnfBiasErr \t W- UnfBiasErr \t W UnfBiasErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleUnfBiasErrp[i] = h_data_p->GetBinContent(i)*0.01*eleBiasp[i];
    eleUnfBiasErrm[i] = h_data_m->GetBinContent(i)*0.01*eleBiasm[i];
    eleUnfBiasErri[i] = sqrt(eleUnfBiasErrp[i]*eleUnfBiasErrp[i] + eleUnfBiasErrm[i]*eleUnfBiasErrm[i]);
    cout << eleUnfBiasErrp[i] << "\t" << eleUnfBiasErrm[i] <<"\t" << eleUnfBiasErri[i] <<endl;
  }
  
  double eleStatErrp[14]={0};
  double eleStatErrm[14]={0};
  double eleStatErri[14]={0};
  cout <<"W+ StatErr \t W- StatErr \t W StatErr" <<endl;
  for(int i(1);i<14;i++)
  {
    eleStatErrp[i] = h_data_p->GetBinContent(i)*0.01*elestatp[i];
    eleStatErrm[i] = h_data_m->GetBinContent(i)*0.01*elestatm[i];
    eleStatErri[i] = sqrt(eleStatErrp[i]*eleStatErrp[i] + eleStatErrm[i]*eleStatErrm[i]);
    cout << eleStatErrp[i] << "\t" << eleStatErrm[i] <<"\t" << eleStatErri[i] <<endl;
  }
  
  double eleTotalSystp[14]={0};
  double eleTotalSystm[14]={0};
  double eleTotalSysti[14]={0};
  cout <<"W+ TotSyst \t W- TotSyst \t W TotSyst" <<endl;
  for(int i(1);i<14;i++)
  {
    eleTotalSystp[i] = sqrt(eleEffErrp[i]*eleEffErrp[i] + eleEnResErrp[i]*eleEnResErrp[i]+eleMetErrp[i]*eleMetErrp[i]+ eleQCDBckErrp[i]*eleQCDBckErrp[i] + eleQCDShapeErrp[i]*eleQCDShapeErrp[i]+ eleEWKErrp[i]*eleEWKErrp[i] + eleSVDUnfErrp[i]*eleSVDUnfErrp[i] + eleFSRErrp[i]*eleFSRErrp[i]+ eleLumiErrp[i]*eleLumiErrp[i] + eleUnfBiasErrp[i]*eleUnfBiasErrp[i]);
    eleTotalSystm[i] = sqrt(eleEffErrm[i]*eleEffErrm[i] + eleEnResErrm[i]*eleEnResErrm[i]+eleMetErrm[i]*eleMetErrm[i]+ eleQCDBckErrm[i]*eleQCDBckErrm[i] + eleQCDShapeErrm[i]*eleQCDShapeErrm[i]+ eleEWKErrm[i]*eleEWKErrm[i] + eleSVDUnfErrm[i]*eleSVDUnfErrm[i] + eleFSRErrm[i]*eleFSRErrm[i]+ eleLumiErrm[i]*eleLumiErrm[i] + eleUnfBiasErrm[i]*eleUnfBiasErrm[i]);
    eleTotalSysti[i] = sqrt(eleEffErri[i]*eleEffErri[i] + eleEnResErri[i]*eleEnResErri[i]+eleMetErri[i]*eleMetErri[i]+ eleQCDBckErri[i]*eleQCDBckErri[i] + eleQCDShapeErri[i]*eleQCDShapeErri[i]+ eleEWKErri[i]*eleEWKErri[i] + eleSVDUnfErri[i]*eleSVDUnfErri[i] + eleFSRErri[i]*eleFSRErri[i]+ eleLumiErri[i]*eleLumiErri[i] + eleUnfBiasErri[i]*eleUnfBiasErri[i]);
    cout << eleTotalSystp[i] << "\t" << eleTotalSystm[i] << "\t" <<  eleTotalSysti[i] <<endl;
  }

  double eleTotalUnceri[14]={0};
  cout <<" Wincl TotalUncertainty" <<endl;
  for(int i(1);i<14;i++)
  {
    eleTotalUnceri[i] = sqrt(eleEffErri[i]*eleEffErri[i] + eleEnResErri[i]*eleEnResErri[i]+eleMetErri[i]*eleMetErri[i]+ eleQCDBckErri[i]*eleQCDBckErri[i] + eleQCDShapeErri[i]*eleQCDShapeErri[i]+ eleEWKErri[i]*eleEWKErri[i] + eleSVDUnfErri[i]*eleSVDUnfErri[i] + eleFSRErri[i]*eleFSRErri[i]+ eleLumiErri[i]*eleLumiErri[i] + eleUnfBiasErri[i]*eleUnfBiasErri[i]+ eleStatErri[i]*eleStatErri[i]);
   // eleTotalUnceri[i] = eleEffErri[i] + eleEnResErri[i] + eleMetErri[i] + eleQCDBckErri[i] + eleQCDShapeErri[i] + eleEWKErri[i] + eleSVDUnfErri[i] + eleFSRErri[i] + eleLumiErri[i] + eleUnfBiasErri[i] + eleStatErri[i];
    cout << eleTotalUnceri[i] <<endl;
  }

  TString resultDir = "WptXsecErrors";
  gSystem->mkdir(resultDir,kTRUE);

  TFile f_out(resultDir+"/WpToEleNuErrors.root","recreate");
    
    ///Write all errors to root
    
    TH1D* h_bin = new TH1D("h_bin","h_bin",13,0,13);
    //TH1D* h_elebinm = new TH1D("h_elebinm","h_elebinm",13,0,13);
    
    TH1D* h_idisosig = new TH1D("h_idisosig","h_idisosig",13,0,13);
    //TH1D* h_sig = new TH1D("h_sig","h_sig",13,0,13);
    //TH1D* h_elesigm = new TH1D("h_elesigm","h_elesigm",13,0,13);

    TH1D* h_idisobck = new TH1D("h_idisobck","h_idisobck",13,0,13);
    //TH1D* h_bckgr = new TH1D("h_bckgr","h_bckgr",13,0,13);
    //TH1D* h_elebckgrm = new TH1D("h_elebckgrm","h_elebckgrm",13,0,13);
  
    TH1D* h_toy = new TH1D("h_toy","h_toy",13,0,13);
    //TH1D* h_eletoym = new TH1D("h_eletoym","h_eletoym",13,0,13);
    
    TH1D* h_TotalEff = new TH1D("h_Totaleff","h_TotalEff",13,0,13);
    //TH1D* h_eleTotalEffm = new TH1D("h_eleTotaleffm","h_eleTotalEffm",13,0,13);
    
    TH1D* h_met = new TH1D("h_met","h_met",13,0,13);
    //TH1D* h_elemetm = new TH1D("h_elemetm","h_elemetm",13,0,13);
    
    TH1D* h_scale = new TH1D("h_scale","h_scale",13,0,13);
    //TH1D* h_elescalem = new TH1D("h_elescalem","h_elescalem",13,0,13);
    
    TH1D* h_smear = new TH1D("h_smear","h_smear",13,0,13);
    //TH1D* h_elesmearm = new TH1D("h_elesmearm","h_elesmearm",13,0,13);
    
    TH1D* h_EnMomRes = new TH1D("h_EnMomRes","h_EnMomRes",13,0,13);
    //TH1D* h_eleEnResm = new TH1D("h_eleEnResm","h_eleEnResm",13,0,13);
    
    TH1D* h_qcdbckgr = new TH1D("h_qcdbckgr","h_qcdbckgr",13,0,13);
    //TH1D* h_eleqcdbckgrm = new TH1D("h_eleqcdbckgrm","h_eleqcdbckgrm",13,0,13);
    
    TH1D* h_qcdshape = new TH1D("h_qcdshape","h_qcdshape",13,0,13);
    //TH1D* h_eleqcdshapem = new TH1D("h_eleqcdshapem","h_eleqcdshapem",13,0,13);
    
    TH1D* h_ewk = new TH1D("h_ewk","h_ewk",13,0,13);
    //TH1D* h_eleewkm = new TH1D("h_eleewkm","h_eleewkm",13,0,13);
    
    TH1D* h_fsr = new TH1D("h_fsr","h_fsr",13,0,13);
    //TH1D* h_elefsrm = new TH1D("h_elefsrm","h_elefsrm",13,0,13);
    
    TH1D* h_SvdUnf = new TH1D("h_SvdUnf","h_SvdUnf",13,0,13);
    //TH1D* h_eleSvdUnfm = new TH1D("h_eleSvdUnfm","h_eleSvdUnfm",13,0,13);
    
    TH1D* h_UnfoldBias = new TH1D("h_UnfoldBias","h_UnfoldBias",13,0,13);
    //TH1D* h_eleUnfoldBiasm = new TH1D("h_eleUnfoldBiasm","h_eleUnfoldBiasm",13,0,13);
    
    TH1D* h_TotalSyst = new TH1D("h_TotalSyst","h_TotalSyst",13,0,13);
    //TH1D* h_eleTotalSystm = new TH1D("h_eleTotalSystm","h_eleTotalSystm",13,0,13);
    
    TH1D* h_Stat = new TH1D("h_Stat","h_Stat",13,0,13);
    //TH1D* h_eleStatm = new TH1D("h_eleStatm","h_eleStatm",13,0,13);
    
    TH1D* h_TotalUncer = new TH1D("h_TotalUncer","h_TotalUncer",13,0,13);
    //TH1D* h_eleTotalUncerm = new TH1D("h_eleTotalUncerm","h_eleTotalUncerm",13,0,13);
    
    TH1D* h_PowhegPDF = new TH1D("h_PowhegPDF","h_PowhegPDF",13,0,13);
    //TH1D* h_elePowhegPDFm = new TH1D("h_elePowhegPDFm","h_elePowhegPDFm",13,0,13);

    TH1D* h_LumiSyst = new TH1D("h_LumiSyst","h_LumiSyst",13,0,13);
    //TH1D* h_eleLumiSystm = new TH1D("h_eleLumiSystm","h_eleLumiSystm",13,0,13);

    double PowhegPDFp[14];
    PowhegPDFp[0] = 0;
    PowhegPDFp[1] = 4.285;
    PowhegPDFp[2] = 4.156;
    PowhegPDFp[3] = 4.132 ;
    PowhegPDFp[4] = 5.839;
    PowhegPDFp[5] = 4.127;
    PowhegPDFp[6] = 5.549;
    PowhegPDFp[7] = 3.104;
    PowhegPDFp[8] = 4.887;
    PowhegPDFp[9] = 2.932;
    PowhegPDFp[10]= 2.299;
    PowhegPDFp[11]= 2.881;
    PowhegPDFp[12]= 2.793;
    PowhegPDFp[13]= 5.133;


    double PowhegPDFm[14];
    PowhegPDFm[0] = 0;
    PowhegPDFm[1] = 4.369;
    PowhegPDFm[2] = 4.373;
    PowhegPDFm[3] = 4.392;
    PowhegPDFm[4] = 4.416;
    PowhegPDFm[5] = 4.475;
    PowhegPDFm[6] = 4.811;
    PowhegPDFm[7] = 4.394;
    PowhegPDFm[8] = 4.216;
    PowhegPDFm[9] = 4.728 ;
    PowhegPDFm[10]= 4.818;
    PowhegPDFm[11]= 4.679;
    PowhegPDFm[12]= 4.765;
    PowhegPDFm[13]= 5.371;
    

    for(int i(1);i<14;i++)
    {
      h_Stat->SetBinContent(i,elestatp[i]);
      //h_eleStatm->SetBinContent(i,elestatm[i]);
      
      h_bin->SetBinContent(i,elebinp[i]);
      //h_elebinm->SetBinContent(i,elebinm[i]);
      
      h_idisosig->SetBinContent(i,elesigp[i]);
      //h_elesigm->SetBinContent(i,elesigm[i]);
      
      h_idisobck->SetBinContent(i,elebckgrp[i]);
      //h_bckgr->SetBinContent(i,elebckgrp[i]);
      //h_elebckgrm->SetBinContent(i,elebckgrm[i]);
   
      h_toy->SetBinContent(i,eletoyp[i]);
      //h_eletoym->SetBinContent(i,eletoym[i]);
   
      h_TotalEff->SetBinContent(i,eletotaleffp[i]);
      //h_eleTotalEffm->SetBinContent(i,eletotaleffm[i]);
   
      h_met->SetBinContent(i,elemetp[i]);
      //h_elemetm->SetBinContent(i,elemetm[i]);
   
      h_scale->SetBinContent(i,elescalep[i]);
      //h_elescalem->SetBinContent(i,elescalem[i]);
   
      h_smear->SetBinContent(i,elesmearp[i]);
      //h_elesmearm->SetBinContent(i,elesmearm[i]);
   
      h_EnMomRes->SetBinContent(i,eleEnResp[i]);
      //h_eleEnResm->SetBinContent(i,eleEnResm[i]);
   
      h_qcdbckgr->SetBinContent(i,eleqcdbckgrp[i]);
      //h_eleqcdbckgrm->SetBinContent(i,eleqcdbckgrm[i]);
   
      h_qcdshape->SetBinContent(i,eleqcdshapep[i]);
      //h_eleqcdshapem->SetBinContent(i,eleqcdshapem[i]);
   
      h_ewk->SetBinContent(i,eleewkp[i]);
      //h_eleewkm->SetBinContent(i,eleewkm[i]);
   
      h_fsr->SetBinContent(i,elefsrp[i]);
      //h_elefsrm->SetBinContent(i,elefsrm[i]);
   
      h_SvdUnf->SetBinContent(i,elesvdunfp[i]);
      //h_eleSvdUnfm->SetBinContent(i,elesvdunfm[i]);
   
      h_UnfoldBias->SetBinContent(i,eleBiasp[i]);
      //h_eleUnfoldBiasm->SetBinContent(i,eleBiasm[i]);
   
      h_TotalSyst->SetBinContent(i,systtotalp[i]);
      //h_eleTotalSystm->SetBinContent(i,systtotalm[i]);
   
      h_TotalUncer->SetBinContent(i,totaluncerp[i]);
      //h_eleTotalUncerm->SetBinContent(i,totaluncerm[i]);
   
      h_PowhegPDF->SetBinContent(i,PowhegPDFp[i]);
      //h_elePowhegPDFm->SetBinContent(i,PowhegPDFm[i]);
  
      h_LumiSyst->SetBinContent(i,2.6);
      //h_eleLumiSystm->SetBinContent(i,2.6);

    }
    h_Stat->Write();
    //h_eleStatm->Write();

    h_bin->Write();
    //h_elebinm->Write();

    h_idisosig->Write();
    //h_elesigm->Write();
    
    h_idisobck->Write();
    //h_bckgr->Write();
    //h_elebckgrm->Write();
                   
    h_toy->Write();
    //h_eletoym->Write();
                   
    h_TotalEff->Write();
    //h_eleTotalEffm->Write();
                   
    h_met->Write();
    //h_elemetm->Write();
                   
    h_scale->Write();
    //h_elescalem->Write();
                   
    h_smear->Write();
    //h_elesmearm->Write();
                   
    h_EnMomRes->Write();
    //h_eleEnResm->Write();
                   
    h_qcdbckgr->Write();
    //h_eleqcdbckgrm->Write();
                   
    h_qcdshape->Write();
    //h_eleqcdshapem->Write();
                   
    h_ewk->Write();
    //h_eleewkm->Write();
                   
    h_fsr->Write();
    //h_elefsrm->Write();
                   
    h_SvdUnf->Write();
    //h_eleSvdUnfm->Write();
                   
    h_UnfoldBias->Write();
    //h_eleUnfoldBiasm->Write();
                   
    h_TotalSyst->Write();
    //h_eleTotalSystm->Write();
                   
    h_TotalUncer->Write();
    //h_eleTotalUncerm->Write();

    h_PowhegPDF->Write();
    //h_elePowhegPDFm->Write();
   
    h_LumiSyst->Write();
    //h_eleLumiSystm->Write();


}
