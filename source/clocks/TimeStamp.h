#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QDebug>
#include <QString>

#include <QDateTime>
#include <QTimeZone>

namespace Orloj {
	
	// Timestamp /////////////////////////////////////////////////////
	
	class Timestamp
	{
	public:
		Timestamp();
		Timestamp(qint64 sec, qint64 nsec);

		qint64 secs();
		qint64 nsecs();
		
		QString toString();
		int year();
		int month();
		int day();
		int hour();
		int minute();
		int second();
				
	private:
		qint64 epochSec;
		qint64 nanoSec;

		QTimeZone tz;
		
	};

}

#endif // TIMESTAMP_H