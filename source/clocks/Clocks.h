#ifndef CLOCKs_H
#define CLOCKs_H

#include <chrono>
#include <thread>

#include "Timetag.h"

//#include <QTime>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QElapsedTimer>
//#include <QDeadlineTimer>
//#include <QThread>

//#include "Core.h"

namespace Orloj
{

	// SystemClock /////////////////////////////////////////////////////

	class SystemClock {
	public:
		SystemClock();

		Timetag now();
		Timetag toQuant(int n);

		void connectOnSec(const QObject *receiver, const char *method);

	private:
		Timetag initStamp;
		QTimer time;
	};

	// NanoClock /////////////////////////////////////////////////////

	class NanoClock {
	public:
		NanoClock();

		Timetag now();

		void cycleTest(int cnt);

	private:
		Timetag initStamp;
		QElapsedTimer time;
	};

	// Timeline /////////////////////////////////////////////////////

	class Timeline
	{

	public:
		Timeline();

		void start();

		void schedAbs(double t, const QObject *receiver, const char *method);


	private:
		QTimer time;
	};
}

#endif // CLOCKs_H