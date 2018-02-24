#ifndef ORLOJTESTER_H
#define ORLOJTESTER_H

#include <QDebug>
#include "Clocks.h"

using namespace Orloj;

class OrlojTestApplication : public QObject
{
	Q_OBJECT

public:
	OrlojTestApplication(QObject *parent = Q_NULLPTR);

	public slots :
	void onTick();
	void onSchedAbs();

	void printTag(Timetag tag);

private:
	SystemClock clock;
};

#endif //  ORLOJTESTER_H