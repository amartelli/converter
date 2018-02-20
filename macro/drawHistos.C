#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TFile.h>
#include <TCanvas.h>
#include "TRandom3.h"
#include "TLegend.h"
#include "TLatex.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <fstream>
#include <string>
#include "TROOT.h"
#include "TSystem.h"





void drawHistos(){

  gROOT->Macro("/afs/cern.ch/user/a/amartell/public/setStyle.C");

  std::vector<std::string> names;
  names.push_back("TTB");
  names.push_back("TTB_v3");
  //  names.push_back("QCD");
  //names.push_back("QCD_v3");


  std::vector<std::string> nameH;
  nameH.push_back("jet_pt");  
  nameH.push_back("jet_eta");
  nameH.push_back("jet_flavor");

  nameH.push_back("track_n");
  nameH.push_back("track_pt");
  nameH.push_back("track_eta");
  nameH.push_back("track_releta");
  nameH.push_back("track_sip3D");
  nameH.push_back("track_sip2D");
  nameH.push_back("track_ptRel");
  nameH.push_back("track_pPar");

  int iColors[2] = {kRed, kBlue};
  int iColorsJ[3] = {kBlue, kRed, kGreen+1};

  TH1D* histo[2][11];
  TH1D* histo_b[2][11];
  TH1D* histo_c[2][11];
  TH1D* histo_l[2][11];

  TH1D* dummyS[2];
  int type = 0;
  TFile *inF[2];
  for(int ij=0; ij<2; ++ij){
    inF[ij] = TFile::Open(("../plots"+names.at(ij)+"/plots"+names.at(ij)+".root").c_str());  
    for(int io=0; io<11; ++io){
      histo[ij][io] = (TH1D*)inF[ij]->Get(("d_sample/"+nameH.at(io)).c_str());
      histo[ij][io]->SetLineColor(iColors[ij]);
      histo[ij][io]->SetLineWidth(2);
      if(io == 0 || io == 4)      histo[ij][io]->Rebin(2);
      if(io == 1 || io == 5)      histo[ij][io]->Rebin(6);
      if(io > 6)      histo[ij][io]->Rebin(4);
      histo[ij][io]->Scale(1./histo[ij][io]->GetEntries());


      histo_b[ij][io] = (TH1D*)inF[ij]->Get(("d_sample/"+nameH.at(io)+"_b").c_str());
      histo_b[ij][io]->SetLineColor(iColorsJ[0]);
      histo_b[ij][io]->SetLineWidth(2);
      histo_b[ij][io]->SetLineStyle(ij+1);
      if(io == 0 || io == 4)      histo_b[ij][io]->Rebin(2);
      //      if(io != 6) histo_b[ij][io]->Rebin(4);
      if(io == 1 || io == 5)      histo_b[ij][io]->Rebin(6);
      if(io > 6)      histo_b[ij][io]->Rebin(4);
      histo_b[ij][io]->Scale(1./histo_b[ij][io]->GetEntries());


      histo_c[ij][io] = (TH1D*)inF[ij]->Get(("d_sample/"+nameH.at(io)+"_c").c_str());
      histo_c[ij][io]->SetLineColor(iColorsJ[1]);
      histo_c[ij][io]->SetLineWidth(2);
      histo_c[ij][io]->SetLineStyle(ij+1);
      //      if(io != 6)histo_c[ij][io]->Rebin(4);
      if(io == 0 || io == 4)      histo_c[ij][io]->Rebin(2);
      if(io == 1 || io == 5)      histo_c[ij][io]->Rebin(6);
      if(io > 6)      histo_c[ij][io]->Rebin(4);
      histo_c[ij][io]->Scale(1./histo_c[ij][io]->GetEntries());


      histo_l[ij][io] = (TH1D*)inF[ij]->Get(("d_sample/"+nameH.at(io)+"_l").c_str());
      histo_l[ij][io]->SetLineColor(iColorsJ[2]);
      histo_l[ij][io]->SetLineWidth(2);
      histo_l[ij][io]->SetLineStyle(ij+1);
      //      if(io != 6)histo_l[ij][io]->Rebin(4);
      if(io == 0 || io == 4)      histo_l[ij][io]->Rebin(2);
      if(io == 1 || io == 5)      histo_l[ij][io]->Rebin(6);
      if(io > 6)      histo_l[ij][io]->Rebin(4);
      histo_l[ij][io]->Scale(1./histo_l[ij][io]->GetEntries());
    }
    dummyS[ij] = new TH1D(Form("dummyS_%d", ij), "", 1, 0, 1);
    dummyS[ij]->SetLineStyle(ij+1);
    dummyS[ij]->SetLineWidth(2);
    dummyS[ij]->SetLineColor(kBlack);
  }
      

  TLegend *legTGM = new TLegend(0.85,0.8,0.95,0.95,NULL,"brNDC");
  legTGM->SetTextFont(42);
  legTGM->SetTextSize(0.04);
  legTGM->SetFillStyle(0);
  legTGM->SetFillColor(kWhite);
  legTGM->SetLineColor(kWhite);
  legTGM->SetShadowColor(kWhite);
  for(int ij=0; ij<2; ++ij)
    legTGM->AddEntry(histo[ij][0], names.at(ij).c_str(), "l");


  TLegend *legTGS = new TLegend(0.85,0.8,0.95,0.95,NULL,"brNDC");
  legTGS->SetTextFont(42);
  legTGS->SetTextSize(0.04);
  legTGS->SetFillStyle(0);
  legTGS->SetFillColor(kWhite);
  legTGS->SetLineColor(kWhite);
  legTGS->SetShadowColor(kWhite);
  for(int ij=0; ij<2; ++ij)
    legTGS->AddEntry(dummyS[ij], names.at(ij).c_str(), "l");


  TLegend *legTGJ= new TLegend(0.85,0.65,0.95,0.8,NULL,"brNDC");
  legTGJ->SetTextFont(42);
  legTGJ->SetTextSize(0.04);
  legTGJ->SetFillStyle(0);
  legTGJ->SetFillColor(kWhite);
  legTGJ->SetLineColor(kWhite);
  legTGJ->SetShadowColor(kWhite);
  legTGJ->AddEntry(histo_b[0][0], "b ", "l");
  legTGJ->AddEntry(histo_c[0][0], "c ", "l");
  legTGJ->AddEntry(histo_l[0][0], "usdg ", "l");




  gStyle->SetOptStat(0);


  TCanvas* cn[11];
  for(int ij=0; ij<nameH.size(); ++ij){
    cn[ij] = new TCanvas();
    cn[ij]->cd();
    //histo[ij]->GetXaxis()->SetTitle(nameH.at(ij).c_str());
    //hN[1]->GetYaxis()->SetTitle("events");
    histo[0][ij]->Draw("h");
    histo[1][ij]->Draw("h, same");
    legTGM->Draw("h, same");
    cn[ij]->Print(("plots_"+names.at(0)+"_vs_"+names.at(1)+"/histo_"+nameH.at(ij)+".png").c_str(), "png");
  }


  TCanvas* cnJ[11];
  for(int ij=0; ij<nameH.size(); ++ij){
    cnJ[ij] = new TCanvas();
    cnJ[ij]->cd();
    if(ij >= 7) gPad->SetLogy();
    //histo[ij]->GetXaxis()->SetTitle(nameH.at(ij).c_str());
    //hN[1]->GetYaxis()->SetTitle("events");
    histo_b[0][ij]->Draw("h");
    histo_b[1][ij]->Draw("h, same");
    histo_c[0][ij]->Draw("h, same");
    histo_c[1][ij]->Draw("h, same");
    histo_l[0][ij]->Draw("h, same");
    histo_l[1][ij]->Draw("h, same");
    legTGS->Draw("same");
    legTGJ->Draw("same");
    cnJ[ij]->Print(("plots_"+names.at(0)+"_vs_"+names.at(1)+"/histo_Flavour_"+nameH.at(ij)+".png").c_str(), "png");
  }



}
