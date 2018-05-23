/*
 * plotHisto.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef plotHisto_H_
#define plotHisto_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"
#include "TTree.h"
#include "TH1.h"

class plotHisto: public d_ana::basicAnalyzer{
 public:
 plotHisto():d_ana::basicAnalyzer(){}
  ~plotHisto(){}
  
  
 private:
  void analyze(size_t id);
  void postProcess(){}
  
  /////USER FUNCTIONS
  void initJetHistos();
  void initTrackHistos();
  
  bool fillJetHistos(const Jet*);
  bool fillTrackHistos(const std::vector<Track*>& ,const Jet* );



  /////data///////

  ///jet 
  TH1* jet_pt;
  TH1* jet_eta;
  
  TH1* jet_flavor;
  
  ///track 
  TH1* track_n;
  TH1* track_pt;
  TH1* track_eta;
  TH1* track_releta;
  TH1* track_sip3D;
  TH1* track_sip2D;
  TH1* track_ptRel;
  TH1* track_pPar;

  //b
  TH1* jet_pt_b;
  TH1* jet_eta_b;  
  TH1* jet_flavor_b;
  TH1* track_n_b;
  TH1* track_pt_b;
  TH1* track_eta_b;
  TH1* track_releta_b;
  TH1* track_sip3D_b;
  TH1* track_sip2D_b;
  TH1* track_ptRel_b;
  TH1* track_pPar_b;

  //c
  TH1* jet_pt_c;
  TH1* jet_eta_c;  
  TH1* jet_flavor_c;
  TH1* track_n_c;
  TH1* track_pt_c;
  TH1* track_eta_c;
  TH1* track_releta_c;
  TH1* track_sip3D_c;
  TH1* track_sip2D_c;
  TH1* track_ptRel_c;
  TH1* track_pPar_c;
  
  //l
  TH1* jet_pt_l;
  TH1* jet_eta_l;  
  TH1* jet_flavor_l;
  TH1* track_n_l;
  TH1* track_pt_l;
  TH1* track_eta_l;
  TH1* track_releta_l;
  TH1* track_sip3D_l;
  TH1* track_sip2D_l;
  TH1* track_ptRel_l;
  TH1* track_pPar_l;

};





#endif /* plotHisto_H_ */
