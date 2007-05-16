// C++ testing
#include <iostream>
using namespace std;

#include "backend.h"
//using namespace Marsyas;

MarBackend::MarBackend(int getType) {
	method=getType;
	if (method==TYPE_INTONATION) {
		cout<<"Setting up Intonation stuff"<<endl;
		//makeRecNet();
		startIntonation();
	}
	if (method==TYPE_CONTROL) {
		cout<<"Setting up Control stuff"<<endl;
		//startControl();
// currently no difference.
		//startIntonation();
	}
}

MarBackend::~MarBackend() {
/*
	if (method==TYPE_INTONATION) {
		delete mrsWrapper;
		delete recNet;
	}
	if (method==TYPE_CONTROL) {
	}
*/
}

void MarBackend::makeRecNet() {
	MarSystemManager mng;

	recNet = mng.create("Series", "recNet");
	recNet->addMarSystem(mng.create("AudioSource", "srcRec"));
	recNet->addMarSystem(mng.create("SoundFileSink","destRec")); // temporary

	recNet->updctrl("AudioSource/srcRec/mrs_real/israte", 44100.0);
	recNet->updctrl("AudioSource/srcRec/mrs_bool/initAudio", true);

/*
	MarSystemManager mng;
	MarSystem* pnet = mng.create("Series", "pnet");

	pnet->addMarSystem(mng.create("AudioSource", "srcRec"));
//	pnet->addMarSystem(mng.create("SoundFileSource", "src"));

	pnet->addMarSystem(mng.create("ShiftInput", "sfi"));
//	pnet->updctrl("SoundFileSource/src/mrs_string/filename", audioFilename);
	pnet->addMarSystem(mng.create("PitchPraat", "pitch")); 
	pnet->addMarSystem(mng.create("RealvecSink", "rvSink")); 

	mrs_real lowPitch = 36;
	mrs_real highPitch = 79;
	mrs_real lowFreq = pitch2hertz(lowPitch);
	mrs_real highFreq = pitch2hertz(highPitch);

  mrs_natural lowSamples = 
     hertz2samples(highFreq, pnet->getctrl("SoundFileSource/src/mrs_real/osrate")->toReal());
  mrs_natural highSamples = 
     hertz2samples(lowFreq, pnet->getctrl("SoundFileSource/src/mrs_real/osrate")->toReal());
 
  pnet->updctrl("PitchPraat/pitch/mrs_natural/lowSamples", lowSamples);
  pnet->updctrl("PitchPraat/pitch/mrs_natural/highSamples", highSamples);
  
  //  The window should be just long
  //  enough to contain three periods (for pitch detection) 
  //  of MinimumPitch. E.g. if MinimumPitch is 75 Hz, the window length
  //  is 40 ms and padded with zeros to reach a power of two.
  mrs_real windowSize = 3/lowPitch*pnet->getctrl("SoundFileSource/src/mrs_real/osrate")->toReal();
  pnet->updctrl("mrs_natural/inSamples", 512);
	// pnet->updctrl("ShiftInput/sfi/mrs_natural/Decimation", 256);
	pnet->updctrl("ShiftInput/sfi/mrs_natural/WindowSize", powerOfTwo(windowSize));
	//pnet->updctrl("ShiftInput/sfi/mrs_natural/WindowSize", 1024);

	realvec mydat;
	while (pnet->getctrl("SoundFileSource/src/mrs_bool/notEmpty")->toBool()) {
   		mydat=pnet->getctrl("PitchPraat/pitch/mrs_realvec/data")->toVec();
		cout<<mydat;
		pnet->tick();
	}

    mrsWrapper = new MarSystemQtWrapper(pnet);
    mrsWrapper->start();
*/
/*
	realvec data = pnet->getctrl("RealvecSink/rvSink/mrs_realvec/data")->toVec();
   for (mrs_natural i=1; i<data.getSize();i+=2)
	   data(i) = samples2hertz(data(i), pnet->getctrl("SoundFileSource/src/mrs_real/osrate")->toReal());
   
   pnet->updctrl("RealvecSink/rvSink/mrs_bool/done", true); 



// my addition to the marsyasTest pitch stuff:
  numPitches = data.getSize()/2;
	pitchList.allocate(numPitches);
	for (int i=0; i<numPitches; i++) {
		if ( data(2*i+1)>0 )
			pitchList(i) = hertz2pitch( data(2*i+1) );
		else
			pitchList(i) = 0;
	}
	delete pnet;
	pitchList.writeText("pitchList.txt");
*/
}


void MarBackend::setFileName(string filename) {
	mrsWrapper->updctrl(filenamePtr, filename);
}

void MarBackend::startIntonation() {
	makeRecNet();

	mrsWrapper = new MarSystemQtWrapper(recNet);
	mrsWrapper->start();
	filenamePtr = mrsWrapper->getctrl("SoundFileSink/destRec/mrs_string/filename");
	mrsWrapper->pause();
	mrsWrapper->updctrl(filenamePtr, "foo.wav");
}

void MarBackend::startControl() {

}

void MarBackend::playFile() {
	cout<<"playing file now.   (not really, but it will in a few days)"<<endl;
}

void MarBackend::start() {
	cout<<"play"<<endl;
	mrsWrapper->play();
}

void MarBackend::stop() {
	cout<<"stop"<<endl;
	mrsWrapper->pause();
}

