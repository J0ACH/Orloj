
#include "Clocks.h"

namespace Orloj {

	// Clocks /////////////////////////////////////////////////////

	Clock::Clock(QObject *parent) {
		//time.start();
		initTime = now();
		setTimerType(Qt::PreciseTimer);
		//connect(this, SIGNAL(timeout()), this, SLOT(tick()));

		//qDebug() << "START" << initTime.toString();
		//qint64 syncNsecs = 1000000000 - initTime.nsecs();


		//int cnt = std::to_string(sync.nsecs()).size();

		/*
		qDebug() << "cnt:" << syncFullSec.remainingTimeNSecs();
		*/
	}

	/*
	void SystemClock::restartTime() {
	//QThread::usleep(1000000000 - initTime.nsecs());
	//std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 - initTime.nsecs()));

	qint64 restTime = 1000000000 - initTime.nsecs();
	QElapsedTimer restClock;
	restClock.start();

	while (restClock.nsecsElapsed() <= restTime)
	{
	QString txt, nulls;
	qint64 rest = restTime - restClock.nsecsElapsed();
	int cnt = std::to_string(rest).size();
	for (int i = 0; i < (9 - cnt); i++) { nulls += "0"; }
	txt = QString("nsec: %1%2").arg(
	nulls,
	QString::number(rest)
	);
	qDebug() << "FIN at:" << txt;
	}
	time.start();

	TimeStamp sync = now();
	qDebug() << "DONE" << sync.toString();
	qDebug() << "time" << time.nsecsElapsed();
	}
	*/

	void Clock::tick() {
		qDebug() << "TICK" << now().toString();
	}

	Timestamp Clock::now() {
		using namespace std::chrono;
		system_clock::time_point timePoint = system_clock::now();
		system_clock::duration sinceEpoch = timePoint.time_since_epoch();
		seconds secs = duration_cast<seconds>(sinceEpoch);
		nanoseconds nsecs = sinceEpoch - secs;
		return Timestamp(secs.count(), nsecs.count());
	}

	void Clock::schedAbs(Timestamp t, const QObject *receiver, const char *method) {
		qDebug() << "Clock::schedAbs t:" << t.toString();
		connect(this, SIGNAL(timeout()), receiver, method);
		start(3000);
	}

	// SystemClock /////////////////////////////////////////////////////

	SystemClock::SystemClock() {
		using namespace std::chrono;
		system_clock::time_point timePoint = system_clock::now();
		system_clock::duration sinceEpoch = timePoint.time_since_epoch();
		seconds secs = duration_cast<seconds>(sinceEpoch);
		nanoseconds nsecs = sinceEpoch - secs;
		initStamp = Timestamp(secs.count(), nsecs.count());
		qint64 restTime = 10e8 - initStamp.nsecs();
		//qDebug() << "initStam:" << initStamp.nsecs();
		//qDebug() << "restTime:" << restTime;
		int msec = qRound(restTime * 10e-7);
		//qDebug() << "msec:" << msec;

		time.setTimerType(Qt::PreciseTimer);
		time.setInterval(1000);
		QTimer::singleShot(msec, &time, SLOT(start()));
	}

	Timestamp SystemClock::now() {
		//return initStamp + Timestamp(0, time.nsecsElapsed());
		using namespace std::chrono;
		system_clock::time_point timePoint = system_clock::now();
		system_clock::duration sinceEpoch = timePoint.time_since_epoch();
		seconds secs = duration_cast<seconds>(sinceEpoch);
		nanoseconds nsecs = sinceEpoch - secs;
		return Timestamp(secs.count(), nsecs.count());
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
		initStamp = Timestamp(secs.count(), nsecs.count());

		time.start();
	}

	Timestamp NanoClock::now() {
		return initStamp + Timestamp(0, time.nsecsElapsed());
	}

	void NanoClock::cycleTest(int cnt) {
		QList<qint64> a;
		for (int i = 0; i < cnt; i++) {
			a.append(time.nsecsElapsed());
			//if (a[i] > 5) { qDebug(); }
		}
		for (int i = 0; i < cnt; i++) {
			qDebug() << Timestamp(0, a[i]).toString();
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