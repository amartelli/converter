/*
 * plotHisto.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/plotHisto.h"
#include "TDirectory.h"


float HptRel(const TVector3 &dir, const TVector3 &track)
{
  float magnitute = track.Perp(dir.Unit());
  return magnitute;
}

float HpPar(const TVector3 &dir, const TVector3 &track)
{
  float magnitude = (dir.Unit()).Dot(track);
  return magnitude;
}

float HdeltaR(float eta1, float eta2, float phi1, float phi2){
  float dEta = std::abs(eta1 - eta2);
  float dPhi = (std::abs(phi1 - phi2) > TMath::Pi()) ? (std::abs(phi1 - phi2) - TMath::Pi()) : std::abs(phi1 - phi2);

  return sqrt(dEta*dEta + dPhi*dPhi);
}



bool HcomparePairs(const std::pair<float, float>& i, const std::pair<float, float>& j){
  return i.second < j.second;
}


void plotHisto::analyze(size_t childid /* this info can be used for printouts */){


    d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");

    d_ana::dBranchHandler<Jet>         jets(tree(),"Jet");
    //referenced by the jets
    //do not read gen if not needed - takes a lot of time for nothing
    d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle");
    //read the tracks - needed
    d_ana::dBranchHandler<Track>       tracks(tree(),"EFlowTrack", true);

    /*
     * Add a simple branch to the tree
     */
    initJetHistos();
    initTrackHistos();


    size_t nevents=tree()->entries();
    if(isTestMode())
        nevents/=100;
    for(size_t eventno=0;eventno<nevents;eventno++){
        /*
         * The following two lines report the status and set the event link
         * Do not remove!
         */
        reportStatus(eventno,nevents);
        tree()->setEntry(eventno);

        //force-read particle branch

        for(size_t i=0;i<jets.size();i++){
            const Jet* jet=jets.at(i);

            std::vector<Track*> tracks;
            std::vector<GenParticle*> genparts;

            for(int j = 0; j < jet->Constituents.GetEntriesFast(); ++j){
                auto object = jet->Constituents.At(j);
                if(object == 0)continue;
                else if(object->IsA() == GenParticle::Class())
                    genparts.push_back( (GenParticle*) object );
                else if(object->IsA() == Track::Class())
                    tracks.push_back((Track*) object);
            }

	    bool okFill = fillTrackHistos(tracks,jet);
            if(okFill) fillJetHistos(jet);
        }
    }


    /*
     * Must be called in the end, takes care of thread-safe writeout and
     * call-back to the parent process
     */
    processEndFunction();
}



void plotHisto::initJetHistos(){

  jet_pt = addPlot(new TH1D("jet_pt","jet_pt",200,0,200), "p_{T} (GeV)", "N_{jet}");
  jet_eta = addPlot(new TH1D("jet_eta","",300,-3.,3.), "#eta", "N_{jet}");
  jet_flavor = addPlot(new TH1D("jet_flavor","",30,0,30), "pdgID", "N_{jet}");
  track_n = addPlot(new TH1D("track_n","",100,0,100), "n tracks", "N_{jet}");

  jet_pt_b = addPlot(new TH1D("jet_pt_b","",200,0,200), "p_{T} (GeV)", "N_{jet}");
  jet_eta_b = addPlot(new TH1D("jet_eta_b","",300,-3.,3.), "#eta", "N_{jet}");
  jet_flavor_b = addPlot(new TH1D("jet_flavor_b","",30,0,30), "pdgID", "N_{jet}");
  track_n_b = addPlot(new TH1D("track_n_b","",100,0,100), "n tracks", "N_{jet}");

  jet_pt_c = addPlot(new TH1D("jet_pt_c","",200,0,200), "p_{T} (GeV)", "N_{jet}");
  jet_eta_c = addPlot(new TH1D("jet_eta_c","",300,-3.,3.), "#eta", "N_{jet}");
  jet_flavor_c = addPlot(new TH1D("jet_flavor_c","",30,0,30), "pdgID", "N_{jet}");
  track_n_c = addPlot(new TH1D("track_n_c","",100,0,100), "n tracks", "N_{jet}");

  jet_pt_l = addPlot(new TH1D("jet_pt_l","",200,0,200), "p_{T} (GeV)", "N_{jet}");
  jet_eta_l = addPlot(new TH1D("jet_eta_l","",300,-3.,3.), "#eta", "N_{jet}");
  jet_flavor_l = addPlot(new TH1D("jet_flavor_l","",30,0,30), "pdgID", "N_{jet}");
  track_n_l = addPlot(new TH1D("track_n_l","",100,0,100), "n tracks", "N_{jet}");


}

bool plotHisto::fillJetHistos(const Jet* jet){

  jet_pt->Fill(jet->PT);
  jet_eta->Fill(jet->Eta);

  jet_flavor->Fill(jet->Flavor);

  if(jet->Flavor == 5){
    jet_pt_b->Fill(jet->PT);
    jet_eta_b->Fill(jet->Eta);
    
    jet_flavor_b->Fill(jet->Flavor);    
  }  
  else if(jet->Flavor == 4){
    jet_pt_c->Fill(jet->PT);
    jet_eta_c->Fill(jet->Eta);
    
    jet_flavor_c->Fill(jet->Flavor);    
  }
  else if(jet->Flavor == 1 || jet->Flavor == 2 || jet->Flavor == 3 || jet->Flavor == 21){
    jet_pt_l->Fill(jet->PT);
    jet_eta_l->Fill(jet->Eta);
    
    jet_flavor_l->Fill(jet->Flavor);    
  }
  return true;
}

///////tracks

void plotHisto::initTrackHistos(){
  
  track_pt = addPlot(new TH1D("track_pt","",100,0,100), "p_{T}", "N_{track}");
  track_eta = addPlot(new TH1D("track_eta","",300,-3.,3.), "#eta", "N_{track}");
  track_releta = addPlot(new TH1D("track_releta","",100,-5,5), "relEta", "N_{track}");
  track_sip3D = addPlot(new TH1D("track_sip3D","",200,-10, 10), "Sip3D", "N_{track}");
  track_sip2D = addPlot(new TH1D("track_sip2D","",200,-10, 10), "Sip2D", "N_{track}");
  track_ptRel = addPlot(new TH1D("track_ptRel","",200,0, 10), "ptRel", "N_{track}");
  track_pPar = addPlot(new TH1D("track_pPar","",400,-40, 40), "pPar", "N_{track}");

  track_pt_b = addPlot(new TH1D("track_pt_b","",100,0,100), "p_{T}", "N_{track}");
  track_eta_b = addPlot(new TH1D("track_eta_b","",300,-3.,3.), "#eta", "N_{track}");
  track_releta_b = addPlot(new TH1D("track_releta_b","",100,-5,5), "relEta", "N_{track}");
  track_sip3D_b = addPlot(new TH1D("track_sip3D_b","",200,-10, 10), "Sip3D", "N_{track}");
  track_sip2D_b = addPlot(new TH1D("track_sip2D_b","",200,-10, 10), "Sip2D", "N_{track}");
  track_ptRel_b = addPlot(new TH1D("track_ptRel_b","",200,0, 10), "ptRel", "N_{track}");
  track_pPar_b = addPlot(new TH1D("track_pPar_b","",400,-40, 40), "pPar", "N_{track}");

  track_pt_c = addPlot(new TH1D("track_pt_c","",100,0,100), "p_{T}", "N_{track}");
  track_eta_c = addPlot(new TH1D("track_eta_c","",300,-3.,3.), "#eta", "N_{track}");
  track_releta_c = addPlot(new TH1D("track_releta_c","",100,-5,5), "relEta", "N_{track}");
  track_sip3D_c = addPlot(new TH1D("track_sip3D_c","",200,-10, 10), "Sip3D", "N_{track}");
  track_sip2D_c = addPlot(new TH1D("track_sip2D_c","",200,-10, 10), "Sip2D", "N_{track}");
  track_ptRel_c = addPlot(new TH1D("track_ptRel_c","",200,0, 10), "ptRel", "N_{track}");
  track_pPar_c = addPlot(new TH1D("track_pPar_c","",400,-40, 40), "pPar", "N_{track}");

  track_pt_l = addPlot(new TH1D("track_pt_l","",100,0,100), "p_{T}", "N_{track}");
  track_eta_l = addPlot(new TH1D("track_eta_l","",300,-3.,3.), "#eta", "N_{track}");
  track_releta_l = addPlot(new TH1D("track_releta_l","",100,-5,5), "relEta", "N_{track}");
  track_sip3D_l = addPlot(new TH1D("track_sip3D_l","",200,-10, 10), "Sip3D", "N_{track}");
  track_sip2D_l = addPlot(new TH1D("track_sip2D_l","",200,-10, 10), "Sip2D", "N_{track}");
  track_ptRel_l = addPlot(new TH1D("track_ptRel_l","",200,0, 10), "ptRel", "N_{track}");
  track_pPar_l = addPlot(new TH1D("track_pPar_l","",400,-40, 40), "pPar", "N_{track}");
}


bool plotHisto::fillTrackHistos(const std::vector<Track*>& tracks,const Jet* jet){
  
  float jpx=jet->P4().Px();
  float jpy=jet->P4().Py();
  float jpz=jet->P4().Pz();
  
  const TVector3 jetDir = jet->P4().Vect();
  int jF = jet->Flavor;
  int nTracks = 0;
  int nTracks_b = 0;
  int nTracks_c = 0;
  int nTracks_l = 0;


  if(tracks.size() == 0) return false;

  //  std::cout << " number of Tracks " << tracks.size() << std::endl;
  for(const auto& track:tracks){
    
    if(track->PT<1)continue;
    if(std::abs(track->Eta>2.5))continue;
    float md0 = TMath::Abs(track->D0);
    float d0  = track->D0;
    float xd  = track->Xd;
    float yd  = track->Yd;
    float zd  = track->Zd;
    float dd0 = TMath::Abs(track->ErrorD0);
    float dz  = TMath::Abs(track->DZ);
    float ddz = TMath::Abs(track->ErrorDZ);
    
    float sign3D = (jpx*xd + jpy*yd + jpz*zd > 0.0) ? 1 : -1;
    //add transverse and longitudinal significances in quadrature
    float sip3D = sign3D * TMath::Sqrt( TMath::Power(d0 / dd0, 2) + TMath::Power(dz / ddz, 2) );
    
    float sign2D = (jpx*xd + jpy*yd > 0.0) ? 1 : -1;
    float sip2D = sign2D * d0 / TMath::Abs(dd0);
    
    if(dd0 == 0.) continue;
    if(ddz == 0.) continue;
    
    track_pt->Fill(track->PT);
    track_eta->Fill(track->Eta);
    track_releta->Fill(track->Eta-jet->Eta);
    track_sip3D->Fill(sip3D);
    track_sip2D->Fill(sip2D);
    
    const TVector3 trackDir = track->P4().Vect();
    float trkPttRel = HptRel(jetDir, trackDir);
    float trkPPar = HpPar(jetDir, trackDir);
    track_ptRel->Fill( trkPttRel);
    track_pPar->Fill(trkPPar);
    
    if(jF == 5){
      track_pt_b->Fill(track->PT);
      track_eta_b->Fill(track->Eta);
      track_releta_b->Fill(track->Eta-jet->Eta);
      track_sip3D_b->Fill(sip3D);
      track_sip2D_b->Fill(sip2D);
      track_ptRel_b->Fill( trkPttRel);
      track_pPar_b->Fill(trkPPar);
      ++nTracks_b;
    }
    else if(jF == 4){
      track_pt_c->Fill(track->PT);
      track_eta_c->Fill(track->Eta);
      track_releta_c->Fill(track->Eta-jet->Eta);
      track_sip3D_c->Fill(sip3D);
      track_sip2D_c->Fill(sip2D);
      track_ptRel_c->Fill( trkPttRel);
      track_pPar_c->Fill(trkPPar);
      ++nTracks_c;
    }
    else if(jF == 1 || jF == 2 || jF == 3 || jF == 21){
      track_pt_l->Fill(track->PT);
      track_eta_l->Fill(track->Eta);
      track_releta_l->Fill(track->Eta-jet->Eta);
      track_sip3D_l->Fill(sip3D);
      track_sip2D_l->Fill(sip2D);
      track_ptRel_l->Fill( trkPttRel);
      track_pPar_l->Fill(trkPPar);
        
      ++nTracks_l;
    }

    ++nTracks;
  }    
  //std::cout << " >>> track size = << " << track_pt_.size() << std::endl;
  
  track_n->Fill(nTracks);
  track_n_b->Fill(nTracks_b);
  track_n_c->Fill(nTracks_c);
  track_n_l->Fill(nTracks_l);
  
  return true;
}




