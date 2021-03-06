#ifndef TIMETAG_H
#define TIMETAG_H

#include <QDebug>
#include <QtMath>
#include <QDateTime>
#include <QTimeZone>

namespace Orloj {

	// Timetag /////////////////////////////////////////////////////

	class Timetag
	{
	public:
		Timetag();
		Timetag(double t);
		Timetag(qint64 epochsec, qint64 nanosec);

		enum TimeForm { EPOCH, BUNDLE, DOUBLE, FULL, DATE, TIME };

		qint64 epochSecs();
		qint64 nanoSecs();

		int year();
		int month();
		int day();
		int hour();
		int minute();
		int second();
		int milisecond();
				
		double toDouble();
		QString toString(TimeForm form = TimeForm::DOUBLE);
		quint64 toBundle();
		QDate toDate();
		QTime toTime();

		void setDate(QDate date);
		void setDate(int y, int m, int d);

		Timetag operator+(Timetag &other);
		Timetag operator-(Timetag &other);
		Timetag operator+=(Timetag &other);
		Timetag operator-=(Timetag &other);

	private:
		qint64 eSec;
		qint64 nSec;
		QTimeZone tz;
	};

}

#endif // TIMETAG_H