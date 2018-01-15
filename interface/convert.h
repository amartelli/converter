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


class convert: public d_ana::basicAnalyzer{
public:
	convert():d_ana::basicAnalyzer(){}
	~convert(){}


private:
	void analyze(size_t id);
	void postProcess(){}

	/////USER FUNCTIONS
    void initJetBranches(TTree* );
	void initTrackBranches(TTree* );

    bool fillJetBranches(const Jet*);
    bool fillTrackBranches(const std::vector<Track*>& ,const Jet* );



    /////data///////

    ///jet branches
    float jet_pt_;
    float jet_eta_;

    int isB_;
    int isC_;
    int isUDSG_;

    ///track branches
    std::vector<float> track_pt_;
    std::vector<float> track_releta_;
    std::vector<float> track_sip3D_;
    std::vector<float> track_sip2D_;


};





#endif /* convert_H_ */
