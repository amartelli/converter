/*
 * convert.h
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#ifndef convert_H_
#define convert_H_

#include "interface/basicAnalyzer.h"
#include "interface/sampleCollection.h"
#include "classes/DelphesClasses.h"
#include "TTree.h"

class convert: public d_ana::basicAnalyzer{
public:
	convert():d_ana::basicAnalyzer(),read_(false){}
	~convert(){}

	///////


	std::vector<TString> getListOfBranches(){
		if(allbranches_.size())
			return allbranches_;
		else{
			TTree *t=new TTree();
			initBranches(t);
			return allbranches_;
		}
	}



    void setIsRead(bool isread){read_=isread;}
	void initBranches(TTree* );
	///////

private:
	void analyze(size_t id);
	void postProcess(){}

	/////USER FUNCTIONS
    void initJetBranches(TTree* );
	void initTrackBranches(TTree* );

    bool fillJetBranches(const Jet*);
    bool fillTrackBranches(const std::vector<Track*>& ,const Jet* );


    template <class T>
    void addBranch(TTree* t, const char* name,  T*, const char* leaflist=0);


    /////data///////

    ///jet branches
    float jet_pt_;
    float jet_eta_;

    int isB_;
    int isC_;
    int isUDSG_;
    int isMC_;
    int isTtbar_;
    float sigmad0times_;

    ///track branches
    std::vector<float> track_pt_;
    std::vector<float> track_eta_;
    std::vector<float> track_releta_;
    std::vector<float> track_sip3D_;
    std::vector<float> track_sip2D_;
    std::vector<float> track_ptRel_;
    std::vector<float> track_pPar_;

    std::vector<TString> allbranches_;

    bool read_;

};

template <class T>
void convert::addBranch(TTree* t, const char* name,  T* address, const char* leaflist){

  if(read_ ){
    t->SetBranchAddress(name,address);
  }
  else{
    if(leaflist)
      t->Branch(name  ,address  ,leaflist );
    else
      t->Branch(name  ,address);
  }
  allbranches_.push_back((TString)name);

}

#endif /* convert_H_ */
