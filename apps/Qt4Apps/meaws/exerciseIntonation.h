#ifndef MEAWS_EXERCISE_INTONATION_H
#define MEAWS_EXERCISE_INTONATION_H

#include "defs.h"
#include "exerciseAbstract.h"

class ExerciseIntonation : public Exercise {
public:
	ExerciseIntonation();
	void setupDisplay();
	QString exercisesDir();

private:
	QLabel *resultLabel;

};
#endif

