/*
 * convert.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/convert.h"
#include "TDirectory.h"


void convert::analyze(size_t childid /* this info can be used for printouts */){


	d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");
	d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle");
	d_ana::dBranchHandler<Jet>         jets(tree(),"Jet");


	TTree* myskim=addTree("tree");
	/*
	 * Add a simple branch to the tree
	 */

	float jet_pt=0;
	myskim->Branch("jet_pt", &jet_pt);
	float jet_eta=0;
	myskim->Branch("jet_eta", &jet_eta);







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

		for(size_t i=0;i<jets.size();i++){
			const Jet* jet=jets.at(i);

			jet_pt =jet->PT;
			jet_eta=jet->Eta;


			myskim->Fill();
		}




	}


	/*
	 * Must be called in the end, takes care of thread-safe writeout and
	 * call-back to the parent process
	 */
	processEndFunction();
}



void convert::postProcess(){



}



