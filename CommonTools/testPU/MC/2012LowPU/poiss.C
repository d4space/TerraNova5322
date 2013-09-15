TH1F *B30=new TH1F("B30","B30",100,0,100);
TH1F *P25=new TH1F("pileup","pileup",25,0,25);
/*********************
void Binom_Plot(Int_t k, double p, Int_t n)
{

  // k= number of successful trials                                                        
  //p = probability of success                                                             
  //N= number of trials                                                                    
  // Example: the number of heads = k after flipping a coin n times, p=0.5                 

  printf("PDF plotting %d event with prob %g and  %d trials\n",k,p,n);

  for(Int_t i=0;i<k;i++)
    {
            double x=ROOT::Math::binomial_pdf(i,p,n);
            B30->Fill(i,x);
      //printf("Step \t %d \n",i);                                                         
 }
   B30->Draw();

}
*********************/
void Pois_Plot(double Nmin, double Nmax, double Mean)
{

  // N = # of events in time interval t                                                    
  // mean = probability per unit interval * interval                                       

  printf("PDF plotting %d event with mean %g \n",Nmin,Mean);

  //  for(Int_t i=Nmin;i<Nmax;i++)                                                         
  for(double i=Nmin;i<=Nmax;i++)
    {
            double x=ROOT::Math::poisson_pdf(i,Mean);
      cout<<"input, value: "<<i<<"  "<<x<<endl;
            P25->Fill(i,x);
            //      printf("Step \t %d \t %g\n",i,x);                                      
 }
   P25->Draw();

TFile *myfile= new TFile("fillrandom.root", "RECREATE");
P25->Write();
myfile->Close();

}




