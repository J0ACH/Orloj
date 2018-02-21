#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <QDebug>
#include <QString>

namespace Orloj {
	
	// Timestamp /////////////////////////////////////////////////////
	
	class Timestamp
	{
	public:
		Timestamp();
		Timestamp(qint64 secs, qint64 nsecs);

		//void sec_();
		qint64 secs();
		qint64 nsecs();

		QString toString();

	private:
		qint64 epochSec;
		qint64 nanoSec;
	};

}

#endif // TIMESTAMP_H