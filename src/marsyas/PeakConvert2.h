/*
** Copyright (C) 1998-2005 George Tzanetakis <gtzan@cs.uvic.ca>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef MARSYAS_PECONVERT2_H
#define MARSYAS_PECONVERT2_H

#include "MarSystem.h"	

namespace Marsyas
{
/** 
\class PeakConvert2
\ingroup MarSystem
\brief PeakConvert2

PeakConvert2 N real and imaginary spectrum values to 
to a fixed number of peaks.
*/


	class Peaker;
	class MaxArgMax;
	class SimulMaskingFft;

class PeakConvert2: public MarSystem
{
private:
  realvec lastphase_;
  realvec phase_;
  realvec mag_;
	realvec magCorr_;
	realvec frequency_;
  realvec lastmag_;
	realvec lastfrequency_;
  realvec deltamag_;
	realvec deltafrequency_;
	realvec masked_,
			lpPeakerRes_,
			tmpBuff_,
			peakProb_,
			peakProbWeight_;

	mrs_real lpCoeff_;
	mrs_natural N_;
  mrs_real fundamental_;
  mrs_real factor_;
  mrs_natural	hopSize_,
				instFreqHopSize_;
  mrs_natural downFrequency_;
  mrs_natural upFrequency_;
  mrs_natural nbParameters_;
  mrs_natural nbPeaks_;
  mrs_natural frameMaxNumPeaks_;
	mrs_natural size_;
	mrs_natural psize_;
	mrs_natural skip_;
  bool pick_;
	bool prec_;

	mrs_natural frame_;

	bool useStereoSpectrum_;

	Peaker* peaker_;
	MaxArgMax* max_;
	SimulMaskingFft *masking_;

	MarControlPtr ctrl_totalNumPeaks_;
	MarControlPtr ctrl_frameMaxNumPeaks_;
  
  void addControls();
	void myUpdate(MarControlPtr sender);

	mrs_real lobe_value_compute(mrs_real f, mrs_natural type, mrs_natural size);
	//void getBinInterval(realvec& interval, realvec& index, realvec& mag);
	void getShortBinInterval(realvec& interval, realvec& index, realvec& mag);
	void getLargeBinInterval(realvec& interval, realvec& index, realvec& mag);
 
	void ComputeMasking (realvec& in);
	void ComputeMagnitudeAndPhase (realvec in);
	void ComputePeaker (realvec in, realvec& out);


	static mrs_real GaussianPdf (mrs_real x, mrs_real std = 1);

public:
  PeakConvert2(std::string name);
	PeakConvert2(const PeakConvert2& a);
  ~PeakConvert2();
  MarSystem* clone() const;    

  void myProcess(realvec& in, realvec& out); 
};

}//namespace Marsyas

#endif

	

	

	
