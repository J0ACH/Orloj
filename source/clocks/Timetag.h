#ifndef TIMETAG_H
#define TIMETAG_H

#include <QDebug>
#include <QString>

#include <QDateTime>
#include <QTimeZone>

namespace Orloj {

	// Timetag /////////////////////////////////////////////////////

	class Timetag
	{
	public:
		Timetag();
		Timetag(double t);
		Timetag(qint64 sec, qint64 nanosec);

		enum TimeForm { EPOCH, BUNDLE, DOUBLE, FULL, DATE, TIME };

		qint64 epochSecs();
		qint64 nanoSecs();

		QString toString(TimeForm form = TimeForm::EPOCH);
		quint64 toBundle();
		double toDouble();

		int year();
		int month();
		int day();
		int hour();
		int minute();
		int second();

		Timetag operator+(Timetag &other);
		Timetag operator-(Timetag &other);
		Timetag operator+=(Timetag &other);

	private:
		qint64 eSec;
		qint64 nSec;
		QTimeZone tz;
	};

}

#endif // TIMETAG_H