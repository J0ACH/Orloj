
#include "Timetag.h"

namespace Orloj {

	// Timetag /////////////////////////////////////////////////////

	Timetag::Timetag() {
		eSec = 0;
		nSec = 0;
		tz = QTimeZone::systemTimeZone();
	}
	Timetag::Timetag(double t) {
		//if (t < 0) { t = 0; } // ??? min 1-1-1970 
		eSec = qFloor(t);
		nSec = (t - eSec) * 10e8;
		tz = QTimeZone::systemTimeZone();
	}
	Timetag::Timetag(qint64 epochsec, qint64 nanosec) {
		eSec = epochsec;
		nSec = nanosec;
		tz = QTimeZone::systemTimeZone();
	}

	qint64 Timetag::epochSecs() { return eSec; }
	qint64 Timetag::nanoSecs() { return nSec; }

	int Timetag::year() { return QDateTime::fromSecsSinceEpoch(eSec, tz).date().year(); }
	int Timetag::month() { return QDateTime::fromSecsSinceEpoch(eSec, tz).date().month(); }
	int Timetag::day() { return QDateTime::fromSecsSinceEpoch(eSec, tz).date().day(); }
	int Timetag::hour() { return QDateTime::fromSecsSinceEpoch(eSec, tz).time().hour(); }
	int Timetag::minute() { return QDateTime::fromSecsSinceEpoch(eSec, tz).time().minute(); }
	int Timetag::second() { return QDateTime::fromSecsSinceEpoch(eSec, tz).time().second(); }
	int Timetag::milisecond() { return qRound(nSec * 10e-7); }

	double Timetag::toDouble() { return eSec + nSec * 10e-10; }

	QString Timetag::toString(TimeForm form) {
		QString txt, txtNanoSec;
		int lastIndex;

		switch (form)
		{
		case Orloj::Timetag::EPOCH:
		default:
			txt = QString("%1.%2")
				.arg(eSec, 10, 10, QChar('0'))
				.arg(nSec, 9, 10, QChar('0'));
			break;
		case Orloj::Timetag::BUNDLE:
			txt = QString::number(toBundle());
			break;
		case Orloj::Timetag::DOUBLE:
			txtNanoSec = QString("%1").arg(nSec, 9, 10, QChar('0'));
			lastIndex = txtNanoSec.lastIndexOf(QRegExp("[1-9]")) + 1;
			txtNanoSec.chop(txtNanoSec.size() - lastIndex);
			if (txtNanoSec.isEmpty()) { txtNanoSec = "0"; }
			txt = QString("%1.%2")
				.arg(eSec)
				.arg(txtNanoSec);
			break;
		case Orloj::Timetag::FULL:
			txtNanoSec = QString("%1").arg(nSec, 9, 10, QChar('0'));
			txtNanoSec.resize(3, QChar('0'));
			txt = QString("%1.%2.%3, %4:%5:%6.%7")
				.arg(day(), 2, 10, QChar('0'))
				.arg(month(), 2, 10, QChar('0'))
				.arg(year())
				.arg(hour(), 2, 10, QChar('0'))
				.arg(minute(), 2, 10, QChar('0'))
				.arg(second(), 2, 10, QChar('0'))
				.arg(milisecond(), 3, 10, QChar('0'));
			break;
		case Orloj::Timetag::DATE:
			txt = QString("%1/%2/%3")
				.arg(year())
				.arg(month(), 2, 10, QChar('0'))
				.arg(day(), 2, 10, QChar('0'));
			break;
		case Orloj::Timetag::TIME:
			txt = QString("%1:%2:%3")
				.arg(hour(), 2, 10, QChar('0'))
				.arg(minute(), 2, 10, QChar('0'))
				.arg(second(), 2, 10, QChar('0'));
			break;
		}

		return txt;
	}

	quint64 Timetag::toBundle() {
		quint32 second_1900_1970 = 2208988800; // pozn.: pocet sekund pri zapocteni 17 prestupnych let 
		quint32 second_1900_now = second_1900_1970 + eSec;
		quint64 sec2osc = 4294967296; // pow(2,32)/1
		double nanos2osc = 4.294967296; // pow(2,32)/1e9
		quint64 bundle = second_1900_now * sec2osc + nSec * nanos2osc;
		return bundle;
	}

	QDate Timetag::toDate() { return QDate(year(), month(), day()); }
	QTime Timetag::toTime() { return QTime(hour(), minute(), second(), milisecond()); }

	void Timetag::setDate(QDate date) { eSec = QDateTime(date, toTime()).toSecsSinceEpoch(); }
	void Timetag::setDate(int y, int m, int d) { Timetag::setDate(QDate(y, m, d)); }

	Timetag Timetag::operator+(Timetag & other) { return Timetag(toDouble() + other.toDouble()); }
	Timetag Timetag::operator-(Timetag & other) { return Timetag(toDouble() - other.toDouble()); }
	Timetag Timetag::operator+=(Timetag & other) {
		eSec += other.epochSecs();
		nSec += other.nanoSecs();
		return *this;
	}
	Timetag Timetag::operator-=(Timetag & other) {
		eSec -= other.epochSecs();
		nSec -= other.nanoSecs();
		return *this;
	}
}