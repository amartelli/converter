/*
 * convert.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/convert.h"
#include "TDirectory.h"


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

}

bool convert::fillJetBranches(const Jet* jet){

    jet_pt_=jet->PT;
    jet_eta_=jet->Eta;

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
    addBranch(myskim,"track_releta", &track_releta_);
    addBranch(myskim,"track_sip3D", &track_sip3D_);
    addBranch(myskim,"track_sip2D", &track_sip2D_);

}


bool convert::fillTrackBranches(const std::vector<Track*>& tracks,const Jet* jet){

    track_pt_.clear();
    track_releta_.clear();
    track_sip3D_.clear();
    track_sip2D_.clear();

    float jpx=jet->P4().Px();
    float jpy=jet->P4().Py();
    float jpz=jet->P4().Pz();

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



        track_pt_.push_back(track->PT);
        track_releta_.push_back(track->Eta-jet->Eta);
        track_sip3D_.push_back(catchNan(sip3D));
        track_sip2D_.push_back(catchNan(sip2D));
    }

    return true;
}


