
#include "Clocks.h"

namespace Orloj {

	// SystemClock /////////////////////////////////////////////////////

	SystemClock::SystemClock() {

		initStamp = now();
		Timetag rest = toQuant(1);
		int msec = rest.second() * 1000 + qRound(rest.nanoSecs() * 10e-7);
		//qDebug() << "quant" << rest.toString();
		//qDebug() << "msec" << msec;
		time.setTimerType(Qt::PreciseTimer);
		time.setInterval(1000);
		QTimer::singleShot(msec, &time, SLOT(start()));
	}

	Timetag SystemClock::now() {
		using namespace std::chrono;
		system_clock::time_point timePoint = system_clock::now();
		system_clock::duration sinceEpoch = timePoint.time_since_epoch();
		seconds secs = duration_cast<seconds>(sinceEpoch);
		nanoseconds nsecs = sinceEpoch - secs;
		return Timetag(secs.count(), nsecs.count());
	}

	Timetag SystemClock::toQuant(int n) {
		Timetag nowStamp = now();
		int restSec;
		if (n > 1) { restSec = n - nowStamp.second() % n - 1; }
		else { restSec = 0; }
		qint64 restTime = 10e8 - nowStamp.nanoSecs();

		//qDebug() << "nowStamp:" << Timetag(nowStamp.second(), nowStamp.nanoSecs()).toString();
		//qDebug() << "restSec:" << restSec;
		//int msec = qRound(restTime * 10e-7);
		//qDebug() << "msec:" << msec;
		return Timetag(restSec, restTime);
	}

	void SystemClock::connectOnSec(const QObject *receiver, const char *method) {
		QObject::connect(&time, SIGNAL(timeout()), receiver, method);
	}

	// NanoClock /////////////////////////////////////////////////////

	NanoClock::NanoClock() {

		using namespace std::chrono;
		system_clock::time_point timePoint = system_clock::now();
		system_clock::duration sinceEpoch = timePoint.time_since_epoch();
		seconds secs = duration_cast<seconds>(sinceEpoch);
		nanoseconds nsecs = sinceEpoch - secs;
		initStamp = Timetag(secs.count(), nsecs.count());

		time.start();
	}

	Timetag NanoClock::now() {
		return initStamp + Timetag(0, time.nsecsElapsed());
	}

	void NanoClock::cycleTest(int cnt) {
		QList<qint64> a;
		for (int i = 0; i < cnt; i++) {
			a.append(time.nsecsElapsed());
			//if (a[i] > 5) { qDebug(); }
		}
		for (int i = 0; i < cnt; i++) {
			qDebug() << Timetag(0, a[i]).toString();
		}
	}

	// Timeline /////////////////////////////////////////////////////

	Timeline::Timeline() {
		time.setTimerType(Qt::PreciseTimer);
	}

	void Timeline::start() { time.start(); }

	void Timeline::schedAbs(double t, const QObject *receiver, const char *method) {
		QObject::connect(&time, SIGNAL(timeout()), receiver, method);
	}


}