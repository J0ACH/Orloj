
#include "Timestamp.h"

namespace Orloj {

	// Timestamp /////////////////////////////////////////////////////

	Timestamp::Timestamp() {
		epochSec = 0;
		nanoSec = 0;
		tz = QTimeZone::systemTimeZone();
	}
	Timestamp::Timestamp(qint64 sec, qint64 nsec) {
		epochSec = sec;
		nanoSec = nsec;
		tz = QTimeZone::systemTimeZone();
	}

	qint64 Timestamp::secs() { return epochSec; }
	qint64 Timestamp::nsecs() { return nanoSec; }

	QString Timestamp::toString() {
		QString txt, nulls;
		int cnt = std::to_string(nanoSec).size();
		for (int i = 0; i < (9 - cnt); i++) { nulls += "0"; }
		txt = QString("secs: %1 || nsec: %2%3").arg(
			QString::number(epochSec),
			nulls,
			QString::number(nanoSec)
		);
		return txt;
	}

	int Timestamp::year() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).date().year(); }
	int Timestamp::month() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).date().month(); }
	int Timestamp::day() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).date().day(); }
	int Timestamp::hour() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).time().hour(); }
	int Timestamp::minute() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).time().minute(); }
	int Timestamp::second() { return QDateTime::fromSecsSinceEpoch(epochSec, tz).time().second(); }	

}