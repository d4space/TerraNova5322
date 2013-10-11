#include <TH1D.h>
#include "RooRealVar.h"
#include "RooGenericPdf.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "TMath.h"
#include "RooGaussian.h"

class CPepeModel0
{
public:
  CPepeModel0():model(0){}
  CPepeModel0(const char *name, RooRealVar &x);
  ~CPepeModel0() {
    delete sigma;
    delete model;
  }
  RooRealVar *sigma;
  RooGenericPdf *model;
};

class CPepeModel1
{
public:
  CPepeModel1():model(0){}
  CPepeModel1(const char *name, RooRealVar &x, RooRealVar *s=0, RooRealVar *sigma1=0);
  ~CPepeModel1() {
    //delete sigma;
    //delete a1;
    delete model;
  }
  RooRealVar *sigma, *a1;
  RooGenericPdf *model;
};

class CPepeGaus
{
public:
  CPepeGaus():model(0){}
  CPepeGaus(const char *name, RooRealVar &x, RooRealVar *s=0, RooRealVar *sigma1=0, RooRealVar *t_gau_mean=0, RooRealVar *t_gau_sigma=0, RooRealVar *t_frac=0);
  ~CPepeGaus() {
    delete sigma;
    delete a1;
    delete frac;
    delete gau_mean;
    delete gau_sigma;
    delete model;
  }
  RooRealVar *sigma, *a1, *gau_mean, *gau_sigma, *frac;
  RooGenericPdf *model;
};

class CPepeModel2
{
public:
  CPepeModel2():model(0){}
  CPepeModel2(const char *name, RooRealVar &x);
  ~CPepeModel2() {
    delete a1;
    delete a2;
    delete a3;
    delete model;
  }
  RooRealVar *a1, *a2, *a3;
  RooGenericPdf *model;
};

class CHistModel
{
public:
  CHistModel():model(0){}
  CHistModel(const char *name, RooRealVar &x, TH1D* hist, int intOrder=1);
  virtual ~CHistModel() { 
    delete inHist;
    delete dataHist;
    delete model;
  }
  TH1D        *inHist;
  RooDataHist *dataHist;
  RooHistPdf  *model;
};

class CPepeModelMean
{
  public:
    CPepeModelMean():model(0){}
    CPepeModelMean(const char *name, RooRealVar &x, RooRealVar *m1=0, RooRealVar *s1=0, RooRealVar *sigma1=0);
    ~CPepeModelMean() {
      delete mean;
      delete sigma;
      delete model;
    }
    RooRealVar *sigma, *mean, *a1;
    RooGenericPdf *model;
};

class cGaussian
{
public:
  cGaussian():model(0){}
  cGaussian(const char *name, RooRealVar &x, RooRealVar *tmp_mean=0, RooRealVar *tmp_sigma=0);
  ~cGaussian() {
    delete mean;
    delete sigma;
    delete model;
  }
  RooRealVar *mean, *sigma;
  RooGenericPdf *model;
};

//--------------------------------------------------------------------------------------------------
cGaussian::cGaussian(const char *name, RooRealVar &x, RooRealVar *tmp_mean, RooRealVar *tmp_sigma)
{
  char meanName[50];
  char sigmaName[50];
  
  if(tmp_mean){
    sprintf(meanName,"%s",tmp_mean->GetName());
    mean = tmp_mean;
  }else{
    sprintf(meanName,"mean_%s",name);
    mean = new RooRealVar(meanName,meanName,15,0,50);
  }

  if(tmp_sigma){
    sprintf(sigmaName,"%s",tmp_sigma->GetName());
    sigma = tmp_sigma;
  }else{
    sprintf(sigmaName,"sigma_%s",name);
    sigma = new RooRealVar(sigmaName,sigmaName,25,0,50);
  }
  
  char vname[50];
  sprintf(vname,"cGaussPdf_%s",name);
  char formula[200];
  sprintf(formula, "1/(%s*TMath::Sqrt(2*3.141592))*exp(-1/2*(%s-%s)*(%s-%s)/%s/%s)",
      sigmaName,
      x.GetName(),
      meanName,
      x.GetName(),
      meanName,
      sigmaName,
      sigmaName);

  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*mean,*sigma));
  //model = new RooGaussian(vname,vname,x,*mean,*sigma);
}

//--------------------------------------------------------------------------------------------------
CPepeModelMean::CPepeModelMean(const char *name, RooRealVar &x, RooRealVar *m1, RooRealVar *s1, RooRealVar *sigma1)
{
  char sigmaName[50];
  char meanName[50];
  char a1Name[50];
  
  if(s1) {
    sprintf(sigmaName,"%s",s1->GetName());
    sigma = s1;
  } else {
    sprintf(sigmaName,"sigma_%s",name);
    sigma = new RooRealVar(sigmaName,sigmaName,25,5,75);
  }
  if(m1) {
    sprintf(meanName,"%s",m1->GetName());
    mean = m1;
  } else {
    sprintf(meanName,"mean_%s",name);
    mean = new RooRealVar(meanName,meanName,15,0,50);
  }
  if(sigma1) {
    sprintf(a1Name,"%s",sigma1->GetName());
    a1 = sigma1;
  } else {
    sprintf(a1Name,"a1_%s",name);
    a1 = new RooRealVar(a1Name,a1Name,0.01,-1,1);
  }
  char formula[500];
  // f(x) = (x-mean)*exp[-(x-mean)^2 / (s + a*(x-mean))^2] = (x-mean)*exp[-(x-mean)*(x-mean)/(s*s + 2*a*(x-mean) + a*a*(x-mean)*(x-mean))]
  sprintf(formula, "TMath::Max(0,(%s-%s)*exp(-(%s-%s)*(%s-%s)/(%s*%s + 2*%s*%s*(%s-%s) + %s*%s*(%s-%s)*(%s-%s))))",
      x.GetName(),meanName,
      x.GetName(),meanName,x.GetName(),meanName,
      sigmaName,sigmaName,
      sigmaName,a1Name,x.GetName(),meanName,
      a1Name,a1Name,x.GetName(),meanName,x.GetName(),meanName);
      
  char vname[50];
  sprintf(vname,"pepeMeanPdf_%s",name);
  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*mean,*sigma,*a1));
}

//--------------------------------------------------------------------------------------------------
CPepeModel0::CPepeModel0(const char *name, RooRealVar &x)
{
  char sigmaName[50]; sprintf(sigmaName,"sigma_%s",name); sigma = new RooRealVar(sigmaName,sigmaName,10,5,20);
  
  // f(x) = x*exp[-x^2 / s^2]
  char formula[200];
  sprintf(formula,
          "%s*exp(-%s*%s/%s/%s)",
	  x.GetName(),
	  x.GetName(),x.GetName(),
	  sigmaName,sigmaName);
  
  char vname[50];
  sprintf(vname,"pepe0Pdf_%s",name);  
  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*sigma));
}

//--------------------------------------------------------------------------------------------------
CPepeModel1::CPepeModel1(const char *name, RooRealVar &x, RooRealVar *s, RooRealVar *sigma1)
{
  char sigmaName[50];
  if(s) {
    sprintf(sigmaName,"%s",s->GetName());
    sigma = s;
  } else {
    sprintf(sigmaName,"sigma_%s",name);
    //sigma = new RooRealVar(sigmaName,sigmaName,25,5,75);
    sigma = new RooRealVar(sigmaName,sigmaName,25,0,75);
  }
  char a1Name[50];
  if(sigma1) {
    sprintf(a1Name,"%s",sigma1->GetName());
    a1 = sigma1;
  } else {
    sprintf(a1Name,"a1_%s",name);
    a1 = new RooRealVar(a1Name,a1Name,0.01,-1,1);
  }
  // f(x) = x*exp[-x^2 / (s + ax)^2] = x*exp[-x*x/(s*s + 2*a*x + a*a*x*x)]
  char formula[200];
  sprintf(formula, "TMath::Max(0,%s*exp(-%s*%s/(%s*%s + 2*%s*%s*%s + %s*%s*%s*%s)))",
	  x.GetName(),
	  x.GetName(),x.GetName(),
	  sigmaName,sigmaName,
	  sigmaName,a1Name,x.GetName(),
	  a1Name,a1Name,x.GetName(),x.GetName());
  
  char vname[50];
  sprintf(vname,"pepe1Pdf_%s",name);  
  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*sigma,*a1));
}
CPepeGaus::CPepeGaus(const char *name, RooRealVar &x, RooRealVar *s, RooRealVar *sigma1, RooRealVar *t_gau_mean, RooRealVar *t_gau_sigma, RooRealVar *t_frac)
{
  char sigmaName[50];
  if(s) {
    sprintf(sigmaName,"%s",s->GetName());
    sigma = s;
  } else {
    sprintf(sigmaName,"sigma_%s",name);
    sigma = new RooRealVar(sigmaName,sigmaName,25,0,75);
    //sigma = new RooRealVar(sigmaName,sigmaName,25,5,75);
  }
  char a1Name[50];
  if(sigma1) {
    sprintf(a1Name,"%s",sigma1->GetName());
    a1 = sigma1;
  } else {
    sprintf(a1Name,"a1_%s",name);
    a1 = new RooRealVar(a1Name,a1Name,0.01,-1,1);
  }
  char gau_meanName[50];
  if(t_gau_mean)
  {
    gau_mean = t_gau_mean;
  }else{
    sprintf(gau_meanName,"gau_mean_%s",name);
    gau_mean = new RooRealVar(gau_meanName,gau_meanName,15,0,50);
  }
  char gau_sigmaName[50];
  if(t_gau_sigma)
  {
    gau_sigma = t_gau_sigma;
  }else{
    sprintf(gau_sigmaName,"gau_sigma_%s",name);
    //gau_sigma = new RooRealVar(gau_sigmaName,gau_sigmaName,25,5,75);
    gau_sigma = new RooRealVar(gau_sigmaName,gau_sigmaName,25,0,75);
  }
  char fracName[50];
  if(t_frac)
  {
    frac = t_frac;
  }else{
    sprintf(fracName,"frac_%s",name);
    //frac = new RooRealVar(fracName,fracName,0.5,0.001,1);
    frac = new RooRealVar(fracName,fracName,0.5,0.001,25);
  }
  // f(x) = x*exp[-x^2 / (s + ax)^2] = x*exp[-x*x/(s*s + 2*a*x + a*a*x*x)]
  char formula[500];
  sprintf(formula,
      "TMath::Max(0, \
    %s*exp(-%s*%s/(%s*%s + 2*%s*%s*%s + %s*%s*%s*%s))+ \
      %s*1/(%s*TMath::Sqrt(2*3.141592))*exp(-1/2*(%s-%s)*(%s-%s)/(%s*%s)))",
	  x.GetName(),
	  x.GetName(),x.GetName(),
	  sigma->GetName(),sigma->GetName(),
	  sigma->GetName(),a1->GetName(),x.GetName(),
	  a1->GetName(),a1->GetName(),x.GetName(),x.GetName(),
	  frac->GetName(),
	  gau_sigma->GetName(),
	  x.GetName(),
	  gau_mean->GetName(),
	  x.GetName(),
	  gau_mean->GetName(),
	  gau_sigma->GetName(),
	  gau_sigma->GetName()
	   );
  
  char vname[50];
  sprintf(vname,"pepe1GausPdf_%s",name);
  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*sigma,*a1,*gau_mean, *gau_sigma, *frac));
}

//--------------------------------------------------------------------------------------------------
CPepeModel2::CPepeModel2(const char *name, RooRealVar &x)
{
  char a1Name[50]; sprintf(a1Name, "a1_%s", name); a1 = new RooRealVar(a1Name,a1Name,0.1,-1,1);
  char a2Name[50]; sprintf(a2Name, "a2_%s", name); a2 = new RooRealVar(a2Name,a2Name,1,0,10);
  char a3Name[50]; sprintf(a3Name, "a3_%s", name); a3 = new RooRealVar(a3Name,a3Name,100,70,400);
  
  // f(x) = x*exp[-x^2 / a*x*x + b*x + c]
  char formula[300];
  sprintf(formula,
          "%s*exp(-%s*%s/(%s*%s*%s + %s*%s + %s))",
	  x.GetName(),
	  x.GetName(),x.GetName(),
	  a1Name,x.GetName(),x.GetName(),
	  a2Name,x.GetName(),
	  a3Name);
  
  char vname[50];
  sprintf(vname,"pepe2Pdf_%s",name);  
  model = new RooGenericPdf(vname,vname,formula,RooArgSet(x,*a1,*a2,*a3));
}

//--------------------------------------------------------------------------------------------------
CHistModel::CHistModel(const char *name, RooRealVar &x, TH1D* hist, int intOrder)
{
  char vname[100];
  
  sprintf(vname,"inHist_%s",name);   inHist   = (TH1D*)hist->Clone(vname);  
  sprintf(vname,"dataHist_%s",name); dataHist = new RooDataHist(vname,vname,RooArgSet(x),inHist);
  sprintf(vname,"histPdf_%s",name);  model    = new RooHistPdf(vname,vname,x,*dataHist,intOrder); 
}
