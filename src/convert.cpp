/*
 * convert.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/convert.h"
#include "TDirectory.h"


float ptRel(const TVector3 &dir, const TVector3 &track)
{
  float magnitute = track.Perp(dir.Unit());
  return magnitute;
}

float pPar(const TVector3 &dir, const TVector3 &track)
{
  float magnitude = (dir.Unit()).Dot(track);
  return magnitude;
}


float deltaR(float eta1, float eta2, float phi1, float phi2){
  float dEta = std::abs(eta1 - eta2);
  float dPhi = (std::abs(phi1 - phi2) > TMath::Pi()) ? (std::abs(phi1 - phi2) - TMath::Pi()) : std::abs(phi1 - phi2);

  return sqrt(dEta*dEta + dPhi*dPhi);
}


/*
bool comparePairs(const std::pair<float, float>& i, const std::pair<float, float>& j){
  return i.second > j.second;
}
*/

std::vector<size_t> sorted_indices(const std::vector<float> &v) {
  // initialize original index locations
  std::vector<size_t> idx(v.size());
  for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indices based on comparing values in v
  std::sort(idx.begin(), idx.end(),
            [&v](size_t i1, size_t i2) {return v[i1] > v[i2];} );
  
  return idx;
}


float catchNan(const float& in){

if(in!=in) return 0;
return in;
}


void convert::analyze(size_t childid /* this info can be used for printouts */){


    d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");

    d_ana::dBranchHandler<Jet>         jets(tree(),"Jet");
    //referenced by the jets
    //do not read gen if not needed - takes a lot of time for nothing
    d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle",false);
    //read the tracks - needed
    d_ana::dBranchHandler<Track>       tracks(tree(),"EFlowTrack",true);


    const TString& samplename=getLegendName();
    isTtbar_=0;
    isMC_=0;
    if(samplename.Contains("ttbar"))
      isTtbar_=1;
    if(samplename.Contains("MC"))
      isMC_=1;
    


    TTree* myskim=addTree("tree");
    /*
     * Add a simple branch to the tree
     */
    initJetBranches(myskim);
    initTrackBranches(myskim);


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
            bool fill=true;

            fill &= fillTrackBranches(tracks,jet);
            fill &= fillJetBranches(jet);

            if(fill)
                myskim->Fill();
        }

    }


    /*
     * Must be called in the end, takes care of thread-safe writeout and
     * call-back to the parent process
     */
    processEndFunction();
}

void convert::initBranches(TTree* t){
	initTrackBranches(t);
	initJetBranches(t);
}


void convert::initJetBranches(TTree* myskim){

   addBranch(myskim,"jet_pt", &jet_pt_);
   addBranch(myskim,"jet_eta", &jet_eta_);
   addBranch(myskim,"isB", &isB_);
   addBranch(myskim,"isC", &isC_);
   addBranch(myskim,"isUDSG", &isUDSG_);
   addBranch(myskim,"isMC", &isMC_);
   addBranch(myskim,"isTtbar", &isTtbar_);
   addBranch(myskim,"sigmad0times", &sigmad0times_);
}

bool convert::fillJetBranches(const Jet* jet){

    jet_pt_=jet->PT;
    jet_eta_=jet->Eta;

    sigmad0times_ = 1.5;

    if(std::abs(jet_eta_) > 2.) return false;

    isB_=0;
    isC_=0;
    isUDSG_=0;

    if(jet->Flavor == 5)
        isB_=1;
    else if(jet->Flavor == 4)
        isC_=1;
    else if(jet->Flavor == 1 || jet->Flavor == 2 || jet->Flavor == 3 || jet->Flavor == 21)
        isUDSG_=1;
    else
        return false; //undefined flavour


    return true;
}


///////tracks

void convert::initTrackBranches(TTree* myskim){

    addBranch(myskim,"track_pt", &track_pt_);
    addBranch(myskim,"track_eta", &track_eta_);
    addBranch(myskim,"track_releta", &track_releta_);
    addBranch(myskim,"track_sip3D", &track_sip3D_);
    addBranch(myskim,"track_sip2D", &track_sip2D_);
    addBranch(myskim,"track_pPar", &track_pPar_);
    addBranch(myskim,"track_ptRel", &track_ptRel_);
}


bool convert::fillTrackBranches(const std::vector<Track*>& tracks,const Jet* jet){

    track_pt_.clear();
    track_eta_.clear();
    track_releta_.clear();
    track_sip3D_.clear();
    track_sip2D_.clear();
    track_pPar_.clear();
    track_ptRel_.clear();

    float jpx=jet->P4().Px();
    float jpy=jet->P4().Py();
    float jpz=jet->P4().Pz();

    const TVector3 jetDir = jet->P4().Vect();

    std::vector<float> S2;
    std::vector<float> ptS2;
    std::vector<float> etaS2;
    std::vector<float> reletaS2;
    std::vector<float> pParS2;
    std::vector<float> ptRelS2;
    std::vector<float> sip3DS2;
    S2.clear();
    ptS2.clear();
    etaS2.clear();
    reletaS2.clear();
    pParS2.clear();
    ptRelS2.clear();
    sip3DS2.clear();

    if(tracks.size() == 0.) return false;
   
    for(const auto& track:tracks){
      
      if(track->PT<1)continue;
      if(track->Eta>2.5)continue;
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

      const TVector3 trackDir = track->P4().Vect();
      float trkPttRel = ptRel(jetDir, trackDir);
      float trkPPar = pPar(jetDir, trackDir);

      /*
      track_pt_.push_back(track->PT);
      track_releta_.push_back(track->Eta-jet->Eta);
      track_sip3D_.push_back(sip3D);
      track_sip2D_.push_back(sip2D);
      
      const TVector3 trackDir = track->P4().Vect();
      track_ptRel_.push_back( ptRel(jetDir, trackDir) ); 
      track_pPar_.push_back( pPar(jetDir, trackDir) );              
      */
      

      S2.push_back(catchNan(sip2D));
      ptS2.push_back(track->PT);
      etaS2.push_back(track->Eta);
      reletaS2.push_back(track->Eta-jet->Eta);
      ptRelS2.push_back(trkPttRel);
      pParS2.push_back(trkPPar);    
      sip3DS2.push_back(catchNan(sip3D));
    }


    std::vector<size_t> sortedIndex = sorted_indices(S2);


    for(unsigned int ij=0; ij<15; ++ij){
      if(ij < S2.size()){
	int ijS = sortedIndex.at(ij);

	track_pt_.push_back(ptS2.at(ijS));
	track_eta_.push_back(etaS2.at(ijS));
	track_releta_.push_back(reletaS2.at(ijS));
	track_sip3D_.push_back(sip3DS2.at(ijS));
	track_sip2D_.push_back(S2.at(ijS));
	track_ptRel_.push_back(ptRelS2.at(ijS));
	track_pPar_.push_back(pParS2.at(ijS));
      }
      else{
	track_pt_.push_back(0.);
	track_eta_.push_back(0.);
	track_releta_.push_back(0.);
	track_sip3D_.push_back(0.);
	track_sip2D_.push_back(0.);
	track_ptRel_.push_back(0.);
	track_pPar_.push_back(0.);
      }
    }

    return true;
}




