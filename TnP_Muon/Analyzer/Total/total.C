#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

void total()
{
  ofstream outfile;
  outfile.open("TotalEfficiency.txt");
  ifstream trig20p("Trigger/eta_pt_20_plus.txt");
  ifstream trig40p("Trigger/eta_pt_40_plus.txt");
  ifstream trig55p("Trigger/eta_pt_55_plus.txt");
  ifstream trig20m("Trigger/eta_pt_20_minus.txt");
  ifstream trig40m("Trigger/eta_pt_40_minus.txt");
  ifstream trig55m("Trigger/eta_pt_55_minus.txt");
  ifstream idiso20p("IDIso/eta_pt_20_plus.txt");
  ifstream idiso40p("IDIso/eta_pt_40_plus.txt");
  ifstream idiso55p("IDIso/eta_pt_55_plus.txt");
  ifstream idiso20m("IDIso/eta_pt_20_minus.txt");
  ifstream idiso40m("IDIso/eta_pt_40_minus.txt");
  ifstream idiso55m("IDIso/eta_pt_55_minus.txt");
  ifstream track20p("Tracking/eta_pt_20_plus.txt");
  ifstream track40p("Tracking/eta_pt_40_plus.txt");
  ifstream track55p("Tracking/eta_pt_55_plus.txt");
  ifstream track20m("Tracking/eta_pt_20_minus.txt");
  ifstream track40m("Tracking/eta_pt_40_minus.txt");
  ifstream track55m("Tracking/eta_pt_55_minus.txt");
  ifstream sta20p("STA/eta_pt_20_plus.txt");
  ifstream sta40p("STA/eta_pt_40_plus.txt");
  ifstream sta55p("STA/eta_pt_55_plus.txt");
  ifstream sta20m("STA/eta_pt_20_minus.txt");
  ifstream sta40m("STA/eta_pt_40_minus.txt");
  ifstream sta55m("STA/eta_pt_55_minus.txt");
  
  double bins[6];
  double tmp[6];
  double tmperr[6];
  double MC20ptrig[6];
  double ErrMC20ptrig[6];
  double RD20ptrig[6];
  double ErrRD20ptrig[6];
  double MC40ptrig[6];
  double ErrMC40ptrig[6];
  double RD40ptrig[6];
  double ErrRD40ptrig[6];
  double MC55ptrig[6];
  double ErrMC55ptrig[6];
  double RD55ptrig[6];
  double ErrRD55ptrig[6];
  double MC20mtrig[6];
  double ErrMC20mtrig[6];
  double RD20mtrig[6];
  double ErrRD20mtrig[6];
  double MC40mtrig[6];
  double ErrMC40mtrig[6];
  double RD40mtrig[6];
  double ErrRD40mtrig[6];
  double MC55mtrig[6];
  double ErrMC55mtrig[6];
  double RD55mtrig[6];
  double ErrRD55mtrig[6];

  double MC20pidiso[6];
  double ErrMC20pidiso[6];
  double RD20pidiso[6];
  double ErrRD20pidiso[6];
  double MC40pidiso[6];
  double ErrMC40pidiso[6];
  double RD40pidiso[6];
  double ErrRD40pidiso[6];
  double MC55pidiso[6];
  double ErrMC55pidiso[6];
  double RD55pidiso[6];
  double ErrRD55pidiso[6];
  double MC20midiso[6];
  double ErrMC20midiso[6];
  double RD20midiso[6];
  double ErrRD20midiso[6];
  double MC40midiso[6];
  double ErrMC40midiso[6];
  double RD40midiso[6];
  double ErrRD40midiso[6];
  double MC55midiso[6];
  double ErrMC55midiso[6];
  double RD55midiso[6];
  double ErrRD55midiso[6];

  double MC20ptrack[6];
  double ErrMC20ptrack[6];
  double RD20ptrack[6];
  double ErrRD20ptrack[6];
  double MC40ptrack[6];
  double ErrMC40ptrack[6];
  double RD40ptrack[6];
  double ErrRD40ptrack[6];
  double MC55ptrack[6];
  double ErrMC55ptrack[6];
  double RD55ptrack[6];
  double ErrRD55ptrack[6];
  double MC20mtrack[6];
  double ErrMC20mtrack[6];
  double RD20mtrack[6];
  double ErrRD20mtrack[6];
  double MC40mtrack[6];
  double ErrMC40mtrack[6];
  double RD40mtrack[6];
  double ErrRD40mtrack[6];
  double MC55mtrack[6];
  double ErrMC55mtrack[6];
  double RD55mtrack[6];
  double ErrRD55mtrack[6];

  double MC20psta[6];
  double ErrMC20psta[6];
  double RD20psta[6];
  double ErrRD20psta[6];
  double MC40psta[6];
  double ErrMC40psta[6];
  double RD40psta[6];
  double ErrRD40psta[6];
  double MC55psta[6];
  double ErrMC55psta[6];
  double RD55psta[6];
  double ErrRD55psta[6];
  double MC20msta[6];
  double ErrMC20msta[6];
  double RD20msta[6];
  double ErrRD20msta[6];
  double MC40msta[6];
  double ErrMC40msta[6];
  double RD40msta[6];
  double ErrRD40msta[6];
  double MC55msta[6];
  double ErrMC55msta[6];
  double RD55msta[6];
  double ErrRD55msta[6];

  double sf20p[6];
  double errsf20p[6];
  double sf40p[6];
  double errsf40p[6];
  double sf55p[6];
  double errsf55p[6];
  double sf20m[6];
  double errsf20m[6];
  double sf40m[6];
  double errsf40m[6];
  double sf55m[6];
  double errsf55m[6];
  
  double MC20ptot[6];
  double ErrMC20ptot[6];
  double RD20ptot[6];
  double ErrRD20ptot[6];
  double MC40ptot[6];
  double ErrMC40ptot[6];
  double RD40ptot[6];
  double ErrRD40ptot[6];
  double MC55ptot[6];
  double ErrMC55ptot[6];
  double RD55ptot[6];
  double ErrRD55ptot[6];
  double MC20mtot[6];
  double ErrMC20mtot[6];
  double RD20mtot[6];
  double ErrRD20mtot[6];
  double MC40mtot[6];
  double ErrMC40mtot[6];
  double RD40mtot[6];
  double ErrRD40mtot[6];
  double MC55mtot[6];
  double ErrMC55mtot[6];
  double RD55mtot[6];
  double ErrRD55mtot[6];


  int bin = 0;
  while(trig20p >> bins[bin] >> MC20ptrig[bin] >> ErrMC20ptrig[bin] >> RD20ptrig[bin] >> ErrRD20ptrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20ptrig[bin] << "\t" << ErrMC20ptrig[bin] << "\t" << RD20ptrig[bin] << "\t" << ErrRD20ptrig[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(trig40p >> bins[bin] >> MC40ptrig[bin] >> ErrMC40ptrig[bin] >> RD40ptrig[bin] >> ErrRD40ptrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40ptrig[bin] << "\t" << ErrMC40ptrig[bin] << "\t" << RD40ptrig[bin] << "\t" << ErrRD40ptrig[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(trig55p >> bins[bin] >> MC55ptrig[bin] >> ErrMC55ptrig[bin] >> RD55ptrig[bin] >> ErrRD55ptrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55ptrig[bin] << "\t" << ErrMC55ptrig[bin] << "\t" << RD55ptrig[bin] << "\t" << ErrRD55ptrig[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(trig20m >> bins[bin] >> MC20mtrig[bin] >> ErrMC20mtrig[bin] >> RD20mtrig[bin] >> ErrRD20mtrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20mtrig[bin] << "\t" << ErrMC20mtrig[bin] << "\t" << RD20mtrig[bin] << "\t" << ErrRD20mtrig[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(trig40m >> bins[bin] >> MC40mtrig[bin] >> ErrMC40mtrig[bin] >> RD40mtrig[bin] >> ErrRD40mtrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40mtrig[bin] << "\t" << ErrMC40mtrig[bin] << "\t" << RD40mtrig[bin] << "\t" << ErrRD40mtrig[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(trig55m >> bins[bin] >> MC55mtrig[bin] >> ErrMC55mtrig[bin] >> RD55mtrig[bin] >> ErrRD55mtrig[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55mtrig[bin] << "\t" << ErrMC55mtrig[bin] << "\t" << RD55mtrig[bin] << "\t" << ErrRD55mtrig[bin] << endl;
    bin++;
  }

  int bin = 0;
  while(idiso20p >> bins[bin] >> MC20pidiso[bin] >> ErrMC20pidiso[bin] >> RD20pidiso[bin] >> ErrRD20pidiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20pidiso[bin] << "\t" << ErrMC20pidiso[bin] << "\t" << RD20pidiso[bin] << "\t" << ErrRD20pidiso[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(idiso40p >> bins[bin] >> MC40pidiso[bin] >> ErrMC40pidiso[bin] >> RD40pidiso[bin] >> ErrRD40pidiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40pidiso[bin] << "\t" << ErrMC40pidiso[bin] << "\t" << RD40pidiso[bin] << "\t" << ErrRD40pidiso[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(idiso55p >> bins[bin] >> MC55pidiso[bin] >> ErrMC55pidiso[bin] >> RD55pidiso[bin] >> ErrRD55pidiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55pidiso[bin] << "\t" << ErrMC55pidiso[bin] << "\t" << RD55pidiso[bin] << "\t" << ErrRD55pidiso[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(idiso20m >> bins[bin] >> MC20midiso[bin] >> ErrMC20midiso[bin] >> RD20midiso[bin] >> ErrRD20midiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20midiso[bin] << "\t" << ErrMC20midiso[bin] << "\t" << RD20midiso[bin] << "\t" << ErrRD20midiso[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(idiso40m >> bins[bin] >> MC40midiso[bin] >> ErrMC40midiso[bin] >> RD40midiso[bin] >> ErrRD40midiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40midiso[bin] << "\t" << ErrMC40midiso[bin] << "\t" << RD40midiso[bin] << "\t" << ErrRD40midiso[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(idiso55m >> bins[bin] >> MC55midiso[bin] >> ErrMC55midiso[bin] >> RD55midiso[bin] >> ErrRD55midiso[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55midiso[bin] << "\t" << ErrMC55midiso[bin] << "\t" << RD55midiso[bin] << "\t" << ErrRD55midiso[bin] << endl;
    bin++;
  }

  int bin = 0;
  while(track20p >> bins[bin] >> MC20ptrack[bin] >> ErrMC20ptrack[bin] >> RD20ptrack[bin] >> ErrRD20ptrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20ptrack[bin] << "\t" << ErrMC20ptrack[bin] << "\t" << RD20ptrack[bin] << "\t" << ErrRD20ptrack[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(track40p >> bins[bin] >> MC40ptrack[bin] >> ErrMC40ptrack[bin] >> RD40ptrack[bin] >> ErrRD40ptrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40ptrack[bin] << "\t" << ErrMC40ptrack[bin] << "\t" << RD40ptrack[bin] << "\t" << ErrRD40ptrack[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(track55p >> bins[bin] >> MC55ptrack[bin] >> ErrMC55ptrack[bin] >> RD55ptrack[bin] >> ErrRD55ptrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55ptrack[bin] << "\t" << ErrMC55ptrack[bin] << "\t" << RD55ptrack[bin] << "\t" << ErrRD55ptrack[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(track20m >> bins[bin] >> MC20mtrack[bin] >> ErrMC20mtrack[bin] >> RD20mtrack[bin] >> ErrRD20mtrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20mtrack[bin] << "\t" << ErrMC20mtrack[bin] << "\t" << RD20mtrack[bin] << "\t" << ErrRD20mtrack[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(track40m >> bins[bin] >> MC40mtrack[bin] >> ErrMC40mtrack[bin] >> RD40mtrack[bin] >> ErrRD40mtrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40mtrack[bin] << "\t" << ErrMC40mtrack[bin] << "\t" << RD40mtrack[bin] << "\t" << ErrRD40mtrack[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(track55m >> bins[bin] >> MC55mtrack[bin] >> ErrMC55mtrack[bin] >> RD55mtrack[bin] >> ErrRD55mtrack[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55mtrack[bin] << "\t" << ErrMC55mtrack[bin] << "\t" << RD55mtrack[bin] << "\t" << ErrRD55mtrack[bin] << endl;
    bin++;
  }

  int bin = 0;
  while(sta20p >> bins[bin] >> MC20psta[bin] >> ErrMC20psta[bin] >> RD20psta[bin] >> ErrRD20psta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20psta[bin] << "\t" << ErrMC20psta[bin] << "\t" << RD20psta[bin] << "\t" << ErrRD20psta[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(sta40p >> bins[bin] >> MC40psta[bin] >> ErrMC40psta[bin] >> RD40psta[bin] >> ErrRD40psta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40psta[bin] << "\t" << ErrMC40psta[bin] << "\t" << RD40psta[bin] << "\t" << ErrRD40psta[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(sta55p >> bins[bin] >> MC55psta[bin] >> ErrMC55psta[bin] >> RD55psta[bin] >> ErrRD55psta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55psta[bin] << "\t" << ErrMC55psta[bin] << "\t" << RD55psta[bin] << "\t" << ErrRD55psta[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(sta20m >> bins[bin] >> MC20msta[bin] >> ErrMC20msta[bin] >> RD20msta[bin] >> ErrRD20msta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC20msta[bin] << "\t" << ErrMC20msta[bin] << "\t" << RD20msta[bin] << "\t" << ErrRD20msta[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(sta40m >> bins[bin] >> MC40msta[bin] >> ErrMC40msta[bin] >> RD40msta[bin] >> ErrRD40msta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC40msta[bin] << "\t" << ErrMC40msta[bin] << "\t" << RD40msta[bin] << "\t" << ErrRD40msta[bin] << endl;
    bin++;
  }
  int bin = 0;
  while(sta55m >> bins[bin] >> MC55msta[bin] >> ErrMC55msta[bin] >> RD55msta[bin] >> ErrRD55msta[bin] >> tmp[bin] >> tmperr[bin])
  {
    cout << bins[bin] << "\t" << MC55msta[bin] << "\t" << ErrMC55msta[bin] << "\t" << RD55msta[bin] << "\t" << ErrRD55msta[bin] << endl;
    bin++;
  }
  
  for(int i=0; i<6; i++)
  {
    MC20ptot[i]=MC20ptrig[i]*MC20pidiso[i]*MC20ptrack[i]*MC20psta[i];
    RD20ptot[i]=RD20ptrig[i]*RD20pidiso[i]*RD20ptrack[i]*RD20psta[i];
    ErrMC20ptot[i]=MC20ptot[i]*sqrt(ErrMC20ptrig[i]*ErrMC20ptrig[i]/(MC20ptrig[i]*MC20ptrig[i])+ErrMC20pidiso[i]*ErrMC20pidiso[i]/(MC20pidiso[i]*MC20pidiso[i])+ErrMC20ptrack[i]*ErrMC20ptrack[i]/(MC20ptrack[i]*MC20ptrack[i])+ErrMC20psta[i]*ErrMC20psta[i]/(MC20psta[i]*MC20psta[i]));
    ErrRD20ptot[i]=RD20ptot[i]*sqrt(ErrRD20ptrig[i]*ErrRD20ptrig[i]/(RD20ptrig[i]*RD20ptrig[i])+ErrRD20pidiso[i]*ErrRD20pidiso[i]/(RD20pidiso[i]*RD20pidiso[i])+ErrRD20ptrack[i]*ErrRD20ptrack[i]/(RD20ptrack[i]*RD20ptrack[i])+ErrRD20psta[i]*ErrRD20psta[i]/(RD20psta[i]*RD20psta[i]));
    sf20p[i]=RD20ptot[i]/MC20ptot[i];
    errsf20p[i]=sf20p[i]*sqrt(ErrRD20ptot[i]*ErrRD20ptot[i]/(RD20ptot[i]*RD20ptot[i])+ErrMC20ptot[i]*ErrMC20ptot[i]/(MC20ptot[i]*MC20ptot[i]));
    MC40ptot[i]=MC40ptrig[i]*MC40pidiso[i]*MC40ptrack[i]*MC40psta[i];
    RD40ptot[i]=RD40ptrig[i]*RD40pidiso[i]*RD40ptrack[i]*RD40psta[i];
    ErrMC40ptot[i]=MC40ptot[i]*sqrt(ErrMC40ptrig[i]*ErrMC40ptrig[i]/(MC40ptrig[i]*MC40ptrig[i])+ErrMC40pidiso[i]*ErrMC40pidiso[i]/(MC40pidiso[i]*MC40pidiso[i])+ErrMC40ptrack[i]*ErrMC40ptrack[i]/(MC40ptrack[i]*MC40ptrack[i])+ErrMC40psta[i]*ErrMC40psta[i]/(MC40psta[i]*MC40psta[i]));
    ErrRD40ptot[i]=RD40ptot[i]*sqrt(ErrRD40ptrig[i]*ErrRD40ptrig[i]/(RD40ptrig[i]*RD40ptrig[i])+ErrRD40pidiso[i]*ErrRD40pidiso[i]/(RD40pidiso[i]*RD40pidiso[i])+ErrRD40ptrack[i]*ErrRD40ptrack[i]/(RD40ptrack[i]*RD40ptrack[i])+ErrRD40psta[i]*ErrRD40psta[i]/(RD40psta[i]*RD40psta[i]));
    sf40p[i]=RD40ptot[i]/MC40ptot[i];
    errsf40p[i]=sf40p[i]*sqrt(ErrRD40ptot[i]*ErrRD40ptot[i]/(RD40ptot[i]*RD40ptot[i])+ErrMC40ptot[i]*ErrMC40ptot[i]/(MC40ptot[i]*MC40ptot[i]));
    MC55ptot[i]=MC55ptrig[i]*MC55pidiso[i]*MC55ptrack[i]*MC55psta[i];
    RD55ptot[i]=RD55ptrig[i]*RD55pidiso[i]*RD55ptrack[i]*RD55psta[i];
    ErrMC55ptot[i]=MC55ptot[i]*sqrt(ErrMC55ptrig[i]*ErrMC55ptrig[i]/(MC55ptrig[i]*MC55ptrig[i])+ErrMC55pidiso[i]*ErrMC55pidiso[i]/(MC55pidiso[i]*MC55pidiso[i])+ErrMC55ptrack[i]*ErrMC55ptrack[i]/(MC55ptrack[i]*MC55ptrack[i])+ErrMC55psta[i]*ErrMC55psta[i]/(MC55psta[i]*MC55psta[i]));
    ErrRD55ptot[i]=RD55ptot[i]*sqrt(ErrRD55ptrig[i]*ErrRD55ptrig[i]/(RD55ptrig[i]*RD55ptrig[i])+ErrRD55pidiso[i]*ErrRD55pidiso[i]/(RD55pidiso[i]*RD55pidiso[i])+ErrRD55ptrack[i]*ErrRD55ptrack[i]/(RD55ptrack[i]*RD55ptrack[i])+ErrRD55psta[i]*ErrRD55psta[i]/(RD55psta[i]*RD55psta[i]));
    sf55p[i]=RD55ptot[i]/MC55ptot[i];
    errsf55p[i]=sf55p[i]*sqrt(ErrRD55ptot[i]*ErrRD55ptot[i]/(RD55ptot[i]*RD55ptot[i])+ErrMC55ptot[i]*ErrMC55ptot[i]/(MC55ptot[i]*MC55ptot[i]));
    MC20mtot[i]=MC20mtrig[i]*MC20midiso[i]*MC20mtrack[i]*MC20msta[i];
    RD20mtot[i]=RD20mtrig[i]*RD20midiso[i]*RD20mtrack[i]*RD20msta[i];
    ErrMC20mtot[i]=MC20mtot[i]*sqrt(ErrMC20mtrig[i]*ErrMC20mtrig[i]/(MC20mtrig[i]*MC20mtrig[i])+ErrMC20midiso[i]*ErrMC20midiso[i]/(MC20midiso[i]*MC20midiso[i])+ErrMC20mtrack[i]*ErrMC20mtrack[i]/(MC20mtrack[i]*MC20mtrack[i])+ErrMC20msta[i]*ErrMC20msta[i]/(MC20msta[i]*MC20msta[i]));
    ErrRD20mtot[i]=RD20mtot[i]*sqrt(ErrRD20mtrig[i]*ErrRD20mtrig[i]/(RD20mtrig[i]*RD20mtrig[i])+ErrRD20midiso[i]*ErrRD20midiso[i]/(RD20midiso[i]*RD20midiso[i])+ErrRD20mtrack[i]*ErrRD20mtrack[i]/(RD20mtrack[i]*RD20mtrack[i])+ErrRD20msta[i]*ErrRD20msta[i]/(RD20msta[i]*RD20msta[i]));
    sf20m[i]=RD20mtot[i]/MC20mtot[i];
    errsf20m[i]=sf20m[i]*sqrt(ErrRD20mtot[i]*ErrRD20mtot[i]/(RD20mtot[i]*RD20mtot[i])+ErrMC20mtot[i]*ErrMC20mtot[i]/(MC20mtot[i]*MC20mtot[i]));
    MC40mtot[i]=MC40mtrig[i]*MC40midiso[i]*MC40mtrack[i]*MC40msta[i];
    RD40mtot[i]=RD40mtrig[i]*RD40midiso[i]*RD40mtrack[i]*RD40msta[i];
    ErrMC40mtot[i]=MC40mtot[i]*sqrt(ErrMC40mtrig[i]*ErrMC40mtrig[i]/(MC40mtrig[i]*MC40mtrig[i])+ErrMC40midiso[i]*ErrMC40midiso[i]/(MC40midiso[i]*MC40midiso[i])+ErrMC40mtrack[i]*ErrMC40mtrack[i]/(MC40mtrack[i]*MC40mtrack[i])+ErrMC40msta[i]*ErrMC40msta[i]/(MC40msta[i]*MC40msta[i]));
    ErrRD40mtot[i]=RD40mtot[i]*sqrt(ErrRD40mtrig[i]*ErrRD40mtrig[i]/(RD40mtrig[i]*RD40mtrig[i])+ErrRD40midiso[i]*ErrRD40midiso[i]/(RD40midiso[i]*RD40midiso[i])+ErrRD40mtrack[i]*ErrRD40mtrack[i]/(RD40mtrack[i]*RD40mtrack[i])+ErrRD40msta[i]*ErrRD40msta[i]/(RD40msta[i]*RD40msta[i]));
    sf40m[i]=RD40mtot[i]/MC40mtot[i];
    errsf40m[i]=sf40m[i]*sqrt(ErrRD40mtot[i]*ErrRD40mtot[i]/(RD40mtot[i]*RD40mtot[i])+ErrMC40mtot[i]*ErrMC40mtot[i]/(MC40mtot[i]*MC40mtot[i]));
    MC55mtot[i]=MC55mtrig[i]*MC55midiso[i]*MC55mtrack[i]*MC55msta[i];
    RD55mtot[i]=RD55mtrig[i]*RD55midiso[i]*RD55mtrack[i]*RD55msta[i];
    ErrMC55mtot[i]=MC55mtot[i]*sqrt(ErrMC55mtrig[i]*ErrMC55mtrig[i]/(MC55mtrig[i]*MC55mtrig[i])+ErrMC55midiso[i]*ErrMC55midiso[i]/(MC55midiso[i]*MC55midiso[i])+ErrMC55mtrack[i]*ErrMC55mtrack[i]/(MC55mtrack[i]*MC55mtrack[i])+ErrMC55msta[i]*ErrMC55msta[i]/(MC55msta[i]*MC55msta[i]));
    ErrRD55mtot[i]=RD55mtot[i]*sqrt(ErrRD55mtrig[i]*ErrRD55mtrig[i]/(RD55mtrig[i]*RD55mtrig[i])+ErrRD55midiso[i]*ErrRD55midiso[i]/(RD55midiso[i]*RD55midiso[i])+ErrRD55mtrack[i]*ErrRD55mtrack[i]/(RD55mtrack[i]*RD55mtrack[i])+ErrRD55msta[i]*ErrRD55msta[i]/(RD55msta[i]*RD55msta[i]));
    sf55m[i]=RD55mtot[i]/MC55mtot[i];
    errsf55m[i]=sf55m[i]*sqrt(ErrRD55mtot[i]*ErrRD55mtot[i]/(RD55mtot[i]*RD55mtot[i])+ErrMC55mtot[i]*ErrMC55mtot[i]/(MC55mtot[i]*MC55mtot[i]));
  }
  outfile << fixed << setprecision(4);
  outfile << "Total Efficiency and SF" << endl;
  outfile << "=======================================================================" << endl;
  outfile << "pT&Ch" << "\t" << "MC" << "\t" << "Err" << "\t" << "RD" << "\t" << "Err" << "\t" << "SF Nom" << "\t" << "Err" << "\t" << "SF Up" << "\t" << "SF Down" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "20p" << "\t" << MC20ptot[i] << "\t" << ErrMC20ptot[i] << "\t" << RD20ptot[i] << "\t" << ErrRD20ptot[i] << "\t" << sf20p[i] << "\t" << errsf20p[i] << "\t" << sf20p[i]+errsf20p[i] << "\t" <<  sf20p[i]-errsf20p[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "20m" << "\t" << MC20mtot[i] << "\t" << ErrMC20mtot[i] << "\t" << RD20mtot[i] << "\t" << ErrRD20mtot[i] << "\t" << sf20m[i] << "\t" << errsf20m[i] << "\t" << sf20m[i]+errsf20m[i] << "\t" <<  sf20m[i]-errsf20m[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "40p" << "\t" << MC40ptot[i] << "\t" << ErrMC40ptot[i] << "\t" << RD40ptot[i] << "\t" << ErrRD40ptot[i] << "\t" << sf40p[i] << "\t" << errsf40p[i] << "\t" << sf40p[i]+errsf40p[i] << "\t" <<  sf40p[i]-errsf40p[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "40m" << "\t" << MC40mtot[i] << "\t" << ErrMC40mtot[i] << "\t" << RD40mtot[i] << "\t" << ErrRD40mtot[i] << "\t" << sf40m[i] << "\t" << errsf40m[i] << "\t" << sf40m[i]+errsf40m[i] << "\t" <<  sf40m[i]-errsf40m[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "55p" << "\t" << MC55ptot[i] << "\t" << ErrMC55ptot[i] << "\t" << RD55ptot[i] << "\t" << ErrRD55ptot[i] << "\t" << sf55p[i] << "\t" << errsf55p[i] << "\t" << sf55p[i]+errsf55p[i] << "\t" <<  sf55p[i]-errsf55p[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  for(int i=0; i<6; i++)
  {
    outfile << "55m" << "\t" << MC55mtot[i] << "\t" << ErrMC55mtot[i] << "\t" << RD55mtot[i] << "\t" << ErrRD55mtot[i] << "\t" << sf55m[i] << "\t" << errsf55m[i] << "\t" << sf55m[i]+errsf55m[i] << "\t" <<  sf55m[i]-errsf55m[i] << endl;
  }
  outfile << "=======================================================================" << endl;
  outfile.close();
}

