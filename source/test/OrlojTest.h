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

private:

	Clock clock;
};


#endif //  ORLOJTESTER_H