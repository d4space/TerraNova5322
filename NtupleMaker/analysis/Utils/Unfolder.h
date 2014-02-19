#ifndef __Unfolder_h_
#define __Unfolder_h_
#include <iostream>
#include <vector>
#include <cmath>

#include "TH1.h"
#include "TH2.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"
#include "TDecompLU.h"


class Unfolder{
 
  private:
	TString _sname;


	TMatrixD* _mMigrationMatrix;
	TMatrixD* _mMigrationMatrixInverse;
	TH2D* _hMigrationMatrixInverse;

	TH2D* _hMigrationMatrix;

	TH1D* _htrue;
	TH1D* _hmeas;


	TH1D* _hunfold;
	TH1D* _hforefold;

	

  public:
	Unfolder() {}
	Unfolder(TString const sname);
	~Unfolder() {};

	void setMigrationMatrix(TH2D* hmigmat) { 
		_hMigrationMatrix = hmigmat;
		_hMigrationMatrixInverse =(TH2D*) _hMigrationMatrix->Clone("_hMigrationMatrixInverse");
		_hMigrationMatrixInverse->Clear();
		if (_mMigrationMatrix !=0 ) _mMigrationMatrix->Delete(); 
		_mMigrationMatrix= histToMatrix(hmigmat);
//		_mMigrationMatrix->Transpose(*_mMigrationMatrix);
		_mMigrationMatrixInverse = (TMatrixD*)_mMigrationMatrix->Clone(TString::Format("%s_migMatInverse",_sname.Data()));
		cout<<"Migration Matrix======================="<<endl;
		int DIM = hmigmat->GetNbinsX();
		for( int i(0);i<DIM;i++)
		{
		  for(int j(0);j<DIM;j++)
		  {
		  cout<<(*_mMigrationMatrixInverse)(i,j)<<" ";
		  }
		  cout<<endl;
		}
		for( int j(0);j<DIM;j++)
		{
		  double colSum(0);
		  for( int i(0);i<DIM;i++)
		  {
		    colSum+=(*_mMigrationMatrixInverse)(i,j);
		  }
		  cout<<j<<"th colmun Sum is "<<colSum<<endl;
		}

		double det;
		_mMigrationMatrixInverse->Invert(&det);
		//TDecompLU lu(*_mMigrationMatrix);
		//TDecompSVD svd(*_mMigrationMatrix);
		//cout<<"condition number of lu is "<<lu.Condition()<<endl;
		//cout<<"condition number of svd is "<<svd.Condition()<<endl;
		//lu.InvertLU(*_mMigrationMatrixInverse,det);
		//*_mMigrationMatrixInverse= lu.Invert();
		//svd.Decompose();
		//*_mMigrationMatrixInverse= svd.GetMatrix();

		cout<<"Inverted Migration Matrix======================="<<endl;
		for( int i(0);i<DIM;i++)
		{
		  for(int j(0);j<DIM;j++)
		  {
		  cout<<(*_mMigrationMatrixInverse)(i,j)<<" ";
		  }
		  cout<<endl;
		}
		cout<<"Inverse matrix determinant is "<<det<<endl;
		setMigHistInverse(_mMigrationMatrixInverse);
	}

	void setTrue(TH1D* hist){ _htrue = hist;}		
	void setMeas(TH1D* hist){ _hmeas = hist;}		
	
//	void unfold();//{};

	TH1D* getTrue() {return _htrue;}
	TH1D* getMeas() {return _hmeas;}
	TH2D* getMigMatHist() { return _hMigrationMatrix;}
	TMatrixD* getMigMat() { return _mMigrationMatrix;}
	TMatrixD* getMigMatInverse() { return _mMigrationMatrixInverse;}
	TH2D* getMigHistInverse() { return _hMigrationMatrixInverse;}

	TMatrixD* histToMatrix(TH2 const* hist);	
	void setMigHistInverse(TMatrixD const* matrix);	

	void CRMultiply(TH1D* hout, TH1D const* hist, TMatrixD const* mat);

	void unfold();
	void forefold();

	void doUnfolding();
	TH1D* getUnfolded() {return _hunfold;}
	TH1D* getForefold() {return _hforefold;}

	void printUnfoldStats();

	void colNormalize(TH2D* histo);
	void rowNormalize(TH2D* histo);



};


//
// constructors
// 
Unfolder::Unfolder(TString const sname){
		_sname=sname;
		_htrue = 0;
		_hmeas = 0;
		_hMigrationMatrix = 0;
		_mMigrationMatrix = 0;
		_mMigrationMatrixInverse = 0;
	        _hMigrationMatrixInverse = 0;
		_hunfold = 0;
		_hforefold = 0;
}	

//
// convert 2-d histogram to matrix
//
TMatrixD* Unfolder::histToMatrix(TH2 const* hist) {

  // Convention histogram (x,y) to Matrix (x,y)
	int n = hist -> GetNbinsX();

  	TMatrixD *retVal = new TMatrixD(n,n);

  	int theBin;

	for (int i = 0; i < n; i++) 
    	for (int j = 0; j < n; j++) {
			theBin = hist -> GetBin ( i+1, j+1 );
			double val = hist->GetBinContent(theBin);
      		(*retVal)(i,j) = val; 
	}
	return retVal;
}
void Unfolder::setMigHistInverse(TMatrixD const* matrix)
{
  int n= _hMigrationMatrixInverse->GetNbinsX();
  //int nMat = matrix->GetNcols();
  int theBin;
  double tmpVal;
  for(int i(0);i<n;i++)
  for(int j(0);j<n;j++)
  {
    theBin = _hMigrationMatrixInverse->GetBin(i+1,j+1);
    tmpVal = (*matrix)(i,j);
    _hMigrationMatrixInverse->SetBinContent(theBin, tmpVal );
    //_hMigrationMatrixInverse->SetBinContent(i+1,j+1, (*matrix)(i,j) );
  }
}


//
//
//
void Unfolder::CRMultiply(TH1D* hout, TH1D const* hist, TMatrixD const* mat){
  // Convention: newVector(x) =  mat(x,y) * vector(y)

	int ncols= mat->GetNcols(); 
	int nrows = mat->GetNrows();

	for (int row = 0; row < nrows; ++row) {
		double sumVal =0.0;
		double sumErr =0.0;
		for (int col = 0; col < ncols; ++col){
			double matval = (*mat)(row,col);
			double matval1 = (*mat)(row,col);
			double vecval = hist->GetBinContent(col+1);
			double vecerr = hist->GetBinError(col+1);
			sumVal+=matval*vecval;
			sumErr+=matval1*matval1*vecerr*vecerr;
		}

		hout->SetBinContent(row+1,sumVal);
		hout->SetBinError(row+1,sqrt(sumErr));
	}
}
//
//
//
void Unfolder::doUnfolding() {

	this->unfold();
	this->forefold();

}

void Unfolder::unfold(){
	if(_hunfold ==0) _hunfold = (TH1D*)_htrue->Clone(TString::Format("%s_unfold",_sname.Data()));
	_hunfold->Clear();
	CRMultiply(_hunfold,_hmeas,_mMigrationMatrixInverse);

}
void Unfolder::forefold(){
	if (_hforefold==0)	_hforefold = (TH1D*)_htrue->Clone(TString::Format("%s_forefold",_sname.Data()));
	_hforefold->Clear();

	CRMultiply(_hforefold,_htrue,_mMigrationMatrix);
}

void Unfolder::printUnfoldStats() {


	printf ("\n----------------------------------------------\n");
	printf ("printing the unfolding statistics\n");
	printf ("----------------------------------------------\n");

	printf ("%-11s"
		,"bin width"
	);

	printf("%10s", "true");
	printf("\t%-20s", "unfolded");
	printf("\t%-20s", "measured");
	printf("\t%-20s", "forefolded");


	printf("\n");

	int nbinsx =_hmeas->GetNbinsX();

	for (int ibin = 1; ibin <= nbinsx; ++ibin){

		double masslow = _hmeas->GetBinLowEdge(ibin);
		double binwidth = _hmeas->GetBinWidth(ibin);


		printf (
			"[%04.0f,%04.0f]"
			,masslow,masslow+binwidth
		);
			
		printf("%10.0f",this->_htrue->GetBinContent(ibin));

		
		printf("\t%9.1f +/- %-7.1f"
		""
			,this->_hunfold->GetBinContent(ibin),
			this->_hunfold->GetBinError(ibin)
		);

		printf("\t%9.1f +/- %-7.1f"
		""
			,this->_hmeas->GetBinContent(ibin),
			this->_hmeas->GetBinError(ibin)
		);


		printf("\t%9.1f +/- %-7.1f"
		""
			,this->	_hforefold->GetBinContent(ibin),
			this->	_hforefold->GetBinError(ibin)
		);

		printf("\n");
	}
}
void Unfolder::colNormalize(TH2D* hist)
{
  // index (x,y) as (row, column)
  int nbinsx = hist->GetNbinsX();
  int nbinsy = hist->GetNbinsY();
  for( int icol(1);icol<=nbinsy; icol++)
  {
    double sum(0);
    for(int irow(1);irow<=nbinsx;irow++)
    {
      sum += hist->GetBinContent(irow,icol);
    }
    for(int irow(1);irow<=nbinsx;irow++)
    {
      double val = hist->GetBinContent(irow,icol);
      val /= sum;
      hist->SetBinContent(irow,icol,val);
    }
  }
}
void Unfolder::rowNormalize(TH2D* hist)
{
  // index (x,y) as (row, column)
  int nbinsx = hist->GetNbinsX();
  int nbinsy = hist->GetNbinsY();
  for( int irow(1);irow<=nbinsx; irow++)
  {
    double sum(0);
    for(int icol(1);icol<=nbinsy;icol++)
    {
      sum += hist->GetBinContent(irow,icol);
    }
    for(int icol(1);icol<=nbinsy;icol++)
    {
      double val = hist->GetBinContent(irow,icol);
      val /= sum;
      hist->SetBinContent(irow,icol,val);
    }
  }
}
#endif

