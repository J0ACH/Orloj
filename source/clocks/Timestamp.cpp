
#include "Timestamp.h"

namespace Orloj {

	// Timestamp /////////////////////////////////////////////////////

	Timestamp::Timestamp() { epochSec = 0; nanoSec = 0; }
	Timestamp::Timestamp(qint64 secs, qint64 nsecs) { epochSec = secs; nanoSec = nsecs; }

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

}