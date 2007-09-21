#include <iostream>
using namespace std;

#include "intonation-exercise.h"
#include <QFile>
#include <QTextStream>
#include "Transcriber.h"


IntonationExercise::IntonationExercise() {
}

IntonationExercise::~IntonationExercise() {
	delete tries;
}

int IntonationExercise::getType() {
	return TYPE_INTONATION;
}

void IntonationExercise::open(QString exerciseFilename) {
	Exercise::open(exerciseFilename);

	// load exercise answers
	mrs_natural one, two;
	mrs_natural frameSum=0;
	mrs_natural frame;
	int i=0;
	exerAnswer.create(16,2);
	//exerAnswer.create(100,2);
	QString answerFilename = exerciseFilename;
	int size = answerFilename.size();
	answerFilename.replace(size-4,4,".txt");
	QFile answerFile(answerFilename);
	if (answerFile.open(QFile::ReadOnly))
	{
		QTextStream answerText(&answerFile);
		while (!answerText.atEnd())
		{
			answerText>>one>>two;
//			exerAnswer(i,0) = one;
//			exerAnswer(i,1) = two;
			exerAnswer.stretchWrite(i,0,one);
			exerAnswer.stretchWrite(i,1,two);
			i++;
		}
	}
	answerFile.close();
	exerAnswer.stretch(i,2);
	for (i=0; i<exerAnswer.getRows()-1; i++)
	{
		frame = (mrs_natural) ( exerAnswer(i,1)*44100.0/512.0 /2.0);
		exerAnswer(i,1) = frameSum;
		frameSum += frame;
	}
	exerAnswer(i,1) = frameSum;
//	cout<<exerAnswer;

	// **** read lilypond input
	// FIXME: filename
    QFile in_file("/tmp/scale.ly");
    in_file.open(QIODevice::ReadOnly | QIODevice::Text);
    lily_input = (QTextStream(&in_file).readAll()).split('\n');
    in_file.close();
/*
	QString temp;
    for (int i = 0; i < lily_input.size(); ++i) {
        temp = lily_input.at(i);
        cout<<qPrintable(temp)<<endl;
    }
*/
}

void IntonationExercise::addTry() {
	IntonationTry *newTry = new IntonationTry();
	connect(newTry, SIGNAL(tryNumber(mrs_natural)),
		this, SLOT(button(mrs_natural)));
	newTry->setAnswer(exerAnswer);
	newTry->setLily(lily_input);
	Exercise::addTryAbstract(newTry);
}

void IntonationExercise::delTry() {
//	cout<<"del"<<endl;
	Exercise::delTryAbstract();
}

void IntonationExercise::button(mrs_natural selected)
{
	current_ = selected;
	emit analysisDone();
}

QString IntonationExercise::exercisesDir() {
	QString toReturn(MEAWS_DIR);
	toReturn.append("data/intonation/");
	return toReturn;
}

QString IntonationExercise::getMessage() {
	QString toReturn( "Selected attempt " + QString::number(current_) );
	return toReturn;
}

bool IntonationExercise::displayAnalysis(MarBackend *results) {
	tries->at(current_)->displayAnalysis(results);
	return true;
}

