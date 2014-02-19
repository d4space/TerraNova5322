#include "TROOT.h"
#include "TH1D.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooVoigtian.h"
#include "RooVoigtianShape.h"
#include "RooKeysPdf.h"

class CSignalModel
{
public:
  CSignalModel():model(0){}
  virtual ~CSignalModel(){ delete model; }
  RooAbsPdf *model;
};
class CVoigtian : public CSignalModel
{
public:
  CVoigtian(const char *name,RooRealVar &m);
  ~CVoigtian();
  RooRealVar *mass,*width;
  RooRealVar *sigma;
};
class CBreitWignerMC : public CSignalModel
{
  public:
    CBreitWignerMC(const char *name, RooRealVar &m, RooFormulaVar *scale);
    ~CBreitWignerMC();
    RooRealVar     *width;
    RooBreitWigner *bw;
    RooFormulaVar  *mass;
};
class CBreitWignerRD : public CSignalModel
{
  public:
    CBreitWignerRD(const char *name, RooRealVar &m, RooFormulaVar *scale);
    ~CBreitWignerRD();
    RooRealVar     *width;
    RooBreitWigner *bw;
    RooFormulaVar  *mass;
};




class CBreitWignerConvCrystalBall : public CSignalModel
{
public:
  CBreitWignerConvCrystalBall(const char *name, RooRealVar &m);
  ~CBreitWignerConvCrystalBall();
  RooRealVar     *mass, *width;
  RooBreitWigner *bw;
  RooRealVar     *mean, *sigma, *alpha, *n;
  RooCBShape     *cb;
};
class CBreitWignerConvCrystalBallScale : public CSignalModel
{
public:
  CBreitWignerConvCrystalBallScale
    (const char *name, RooRealVar &m,RooFormulaVar *scale_,
     double meanNormCB_, double sigmaCB_, double alphaCB_, double nCB_);
  ~CBreitWignerConvCrystalBallScale();

  RooBreitWigner 	*bw;
  RooFormulaVar		*mass;
  RooRealVar    	*width;

  RooCBShape     *cb;
  RooRealVar     *meanNormCB, *sigmaCB, *alphaCB, *nCB;
  RooFormulaVar     *meanCB;
};

class CMCTemplateConvGaussian : public CSignalModel
{
public:
  CMCTemplateConvGaussian(const char *name, RooRealVar &m, TH1D* hist, int intOrder=1);
  ~CMCTemplateConvGaussian();
  RooRealVar  *mean, *sigma;
  RooGaussian *gaus;
  TH1D        *inHist;
  RooDataHist *dataHist;
  RooHistPdf  *histPdf;
};

class CVoigtianCBShape : public CSignalModel
{
public:
  CVoigtianCBShape(const char *name, RooRealVar &m);
  ~CVoigtianCBShape();
  RooRealVar *mass, *width;
  RooRealVar *sigma, *alpha, *n;
};

class CMCDatasetConvGaussian : public CSignalModel
{
public:
  CMCDatasetConvGaussian(const char *name, RooRealVar &m, TTree* tree);
  ~CMCDatasetConvGaussian();
  RooRealVar  *mean, *sigma;
  RooGaussian *gaus;
  TTree       *inTree;
  RooDataSet  *dataSet;
  RooKeysPdf  *keysPdf;
};

//---------------------------------------------------------------------
CBreitWignerConvCrystalBall::CBreitWignerConvCrystalBall(const char *name, RooRealVar &m)
{
  char vname[50];
  
  sprintf(vname,"mass_%s",name);
  mass = new RooRealVar(vname,vname,91,80,100);    
  mass->setVal(91.1876);
  mass->setConstant(kTRUE);
  
  sprintf(vname,"width_%s",name);
  width = new RooRealVar(vname,vname,2.5,0.1,10);    
  width->setVal(2.4952);
  width->setConstant(kTRUE);
  
  sprintf(vname,"bw_%s",name);
  bw = new RooBreitWigner(vname,vname,m,*mass,*width);

  sprintf(vname,"mean_%s",name);  mean  = new RooRealVar(vname,vname,0,-10,10);
  sprintf(vname,"sigma_%s",name); sigma = new RooRealVar(vname,vname,1,0.1,5);
  sprintf(vname,"alpha_%s",name); alpha = new RooRealVar(vname,vname,5,0,20);
  sprintf(vname,"n_%s",name);	  n     = new RooRealVar(vname,vname,1,0,10);
 
//  n->setVal(1.0);
//  n->setConstant(kTRUE);
  
  sprintf(vname,"cb_%s",name);
  cb = new RooCBShape(vname,vname,m,*mean,*sigma,*alpha,*n);
        
  model = new RooFFTConvPdf(name,name,m,*bw,*cb);
}

CBreitWignerConvCrystalBall::~CBreitWignerConvCrystalBall()
{
  delete mass;
  delete width;
  delete bw;
  delete mean;
  delete sigma;
  delete alpha;
  delete n;
  delete cb;
}
//---------------------------------------------------------------
CBreitWignerConvCrystalBallScale::CBreitWignerConvCrystalBallScale
(const char *name, RooRealVar &m,RooFormulaVar *scale,
 double meanNormCB_, double sigmaCB_, double alphaCB_,double nCB_)
{
  char vname[50];
  //Initialization
  sprintf(vname,"meanNormCB_%s",name);
  meanNormCB = new RooRealVar(vname, vname,meanNormCB_);
  sprintf(vname,"sigmaCB_%s",name);
  sigmaCB = new RooRealVar(vname, vname,sigmaCB_);
  sprintf(vname,"alphaCB_%s",name);
  alphaCB = new RooRealVar(vname,vname,alphaCB_,0,20);
  sprintf(vname,"nCB_%s",name);
  nCB     = new RooRealVar(vname,vname,nCB_,0,10);
 
  //BreitWigner================================
  //Scale mass
  sprintf(vname,"mass_%s",name);
  mass = new RooFormulaVar(vname,vname,"@0*91.1876",RooArgSet(*scale));
 
  //Fix width
  sprintf(vname,"width_%s",name);
  width = new RooRealVar(vname,vname,2.5,0.1,10);    
  width->setVal(2.4952);
  width->setConstant(kTRUE);
  
  sprintf(vname,"bw_%s",name);
  bw = new RooBreitWigner(vname,vname,m,*mass,*width);

  //CBShape======================================
  //Scale mean
  meanNormCB->setConstant(kTRUE);
  sprintf(vname,"meanCB_%s",name);
  meanCB=new RooFormulaVar(vname,vname,"@0*@1",RooArgSet(*scale,*meanNormCB));
  //Fix shape
  sigmaCB->setConstant(kTRUE);
  alphaCB->setConstant(kTRUE);
  nCB->setConstant(kTRUE);
  
  sprintf(vname,"cb_%s",name);
  cb = new RooCBShape(vname,vname,m,*meanNormCB,*sigmaCB,*alphaCB,*nCB);
  //cb = new RooCBShape(vname,vname,m,*meanCB,*sigmaCB,*alphaCB,*nCB);
        
  model = new RooFFTConvPdf(name,name,m,*bw,*cb);
}

CBreitWignerConvCrystalBallScale::~CBreitWignerConvCrystalBallScale()
{
  delete bw;
  delete mass;
  delete width;
  delete cb;
  delete meanNormCB;
  delete meanCB;
  delete sigmaCB;
  delete alphaCB;
  delete nCB;
}


//---------------------------------------------------------------------
CBreitWignerMC::CBreitWignerMC(const char *name, RooRealVar &m, RooFormulaVar *scale)
{
  char vname[50];

  //BreitWigner================================
  //Scale mass
  sprintf(vname,"mass_%s",name);
  mass = new RooFormulaVar(vname,vname,"@0*91.1876",RooArgSet(*scale));

  //  sprintf(vname,"mass_%s",name);
  //  mass = new RooRealVar(vname,vname,91,80,100);
  //  mass->setVal(91.1876);
  //  mass->setConstant(kTRUE);

  sprintf(vname,"width_%s",name);
  width = new RooRealVar(vname,vname,2.5,0.1,10);
  width->setVal(2.4952);
  width->setConstant(kTRUE);
  
  sprintf(vname,"bw_%s",name);
  bw = new RooBreitWigner(vname,vname,m,*mass,*width);
  model = new RooBreitWigner(vname,vname,m,*mass,*width);

}

CBreitWignerMC::~CBreitWignerMC()
{
  delete mass;
  delete width;
  delete bw;
}


//---------------------------------------------------------------------
CBreitWignerRD::CBreitWignerRD(const char *name, RooRealVar &m, RooFormulaVar *scale)
{
    char vname[50];

      //BreitWigner================================
      //Scale mass
      sprintf(vname,"mass_%s",name);
      mass = new RooFormulaVar(vname,vname,"@0*91.1876",RooArgSet(*scale));
      //  sprintf(vname,"mass_%s",name);
      //  mass = new RooRealVar(vname,vname,91,80,100);
      //  mass->setVal(91.1876);
      //  mass->setConstant(kTRUE);

      sprintf(vname,"width_%s",name);
      width = new RooRealVar(vname,vname,2.5,0.1,10);
      width->setVal(2.4952);
      width->setConstant(kTRUE);
      
      sprintf(vname,"bw_%s",name);
      bw = new RooBreitWigner(vname,vname,m,*mass,*width);
      model = new RooBreitWigner(vname,vname,m,*mass,*width);

}

CBreitWignerRD::~CBreitWignerRD()
{
    delete mass;
    delete width;
    delete bw;
}



//--------------------------------------------------------------------------------------------------
CMCTemplateConvGaussian::CMCTemplateConvGaussian(const char *name, RooRealVar &m, TH1D* hist, int intOrder)
{  
  char vname[50];  
  
  sprintf(vname,"mean_%s",name);  mean  = new RooRealVar(vname,vname,0,-10,10);
  sprintf(vname,"sigma_%s",name); sigma = new RooRealVar(vname,vname,2,0,5);
  sprintf(vname,"gaus_%s",name);  gaus  = new RooGaussian(vname,vname,m,*mean,*sigma);

  sprintf(vname,"inHist_%s",hist->GetName());
  inHist = (TH1D*)hist->Clone(vname);
  
  sprintf(vname,"dataHist_%s",name); dataHist = new RooDataHist(vname,vname,RooArgSet(m),inHist);
  sprintf(vname,"histPdf_%s",name);  histPdf  = new RooHistPdf(vname,vname,m,*dataHist,intOrder);
  
  model = new RooFFTConvPdf(name,name,m,*histPdf,*gaus);
}

CMCTemplateConvGaussian::~CMCTemplateConvGaussian()
{
  delete mean;
  delete sigma;
  delete gaus;
  delete inHist;
  delete dataHist;
  delete histPdf;
}

//--------------------------------------------------------------------------
CVoigtian::CVoigtian(const char *name, RooRealVar &m)
{
  char vname[50];
  sprintf(vname,"mass_%s",name);
  mass = new RooRealVar(vname,vname,91,80,100);
  sprintf(vname,"width_%s",name);
  width = new RooRealVar(vname,vname,2.5,0.1,10);    
  width->setVal(2.4952);
  sprintf(vname,"sigma_%s",name);
  sigma = new RooRealVar(vname,vname,1,0.1,10);

  model= new RooVoigtian(name,name,m,*mass,*width,*sigma,0);
}
CVoigtian::~CVoigtian()
{
  delete mass;
  delete width;
  delete sigma;
}

CVoigtianCBShape::CVoigtianCBShape(const char *name, RooRealVar &m)
{
  char vname[50];
  
  sprintf(vname,"mass_%s",name);
  mass = new RooRealVar(vname,vname,91,80,100);
    
  sprintf(vname,"width_%s",name);
  width = new RooRealVar(vname,vname,2.5,0.1,10);    
  width->setVal(2.4952);
  width->setConstant(kTRUE);
  
  sprintf(vname,"sigma_%s",name); sigma = new RooRealVar(vname,vname,1,0.1,10);
  sprintf(vname,"alpha_%s",name); alpha = new RooRealVar(vname,vname,5,0,20);
  
  sprintf(vname,"n_%s",name);     
  n = new RooRealVar(vname,vname,1,0,10);
  n->setVal(1.0);
  
  model = new RooVoigtianShape(name,name,m,*mass,*sigma,*alpha,*n,*width,0);  
}

CVoigtianCBShape::~CVoigtianCBShape()
{
  delete mass;
  delete width;
  delete sigma;
  delete alpha;
  delete n;
}

//--------------------------------------------------------------------------------------------------
CMCDatasetConvGaussian::CMCDatasetConvGaussian(const char *name, RooRealVar &m, TTree* tree)
{  
  char vname[50];  

  sprintf(vname,"mean_%s",name);  mean  = new RooRealVar(vname,vname,0,-10,10);
  sprintf(vname,"sigma_%s",name); sigma = new RooRealVar(vname,vname,2,0,5);
  sprintf(vname,"gaus_%s",name);  gaus  = new RooGaussian(vname,vname,m,*mean,*sigma);
  
  sprintf(vname,"inTree_%s",tree->GetName());
  inTree = (TTree*)tree->Clone(vname);
  
  sprintf(vname,"dataSet_%s",name); dataSet = new RooDataSet(vname,vname,inTree,RooArgSet(m));
  sprintf(vname,"keysPdf_%s",name); keysPdf = new RooKeysPdf(vname,vname,m,*dataSet,RooKeysPdf::NoMirror,1);

  model = new RooFFTConvPdf(name,name,m,*keysPdf,*gaus);
}

CMCDatasetConvGaussian::~CMCDatasetConvGaussian()
{
  delete mean;
  delete sigma;
  delete gaus;
  delete inTree;
  delete dataSet;
  delete keysPdf;
}
