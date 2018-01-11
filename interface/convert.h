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

	void postProcess();
};





#endif /* convert_H_ */
