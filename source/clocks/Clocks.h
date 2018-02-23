#ifndef CLOCKs_H
#define CLOCKs_H

#include <chrono>
#include <thread>

#include "Timestamp.h"

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

		Timestamp now();
		Timestamp toQuant(int n);

		void connectOnSec(const QObject *receiver, const char *method);

	private:
		Timestamp initStamp;
		QTimer time;
	};

	// NanoClock /////////////////////////////////////////////////////

	class NanoClock {
	public:
		NanoClock();

		Timestamp now();

		void cycleTest(int cnt);

	private:
		Timestamp initStamp;
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