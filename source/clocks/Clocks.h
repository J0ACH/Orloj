#ifndef CLOCKs_H
#define CLOCKs_H

#include <chrono>
#include <thread>

#include "Timestamp.h"

//#include <QTime>
#include <QDebug>
#include <QString>
#include <QTimer>
//#include <QElapsedTimer>
//#include <QDeadlineTimer>
//#include <QThread>

//#include "Core.h"

namespace Orloj
{

	// Clocks /////////////////////////////////////////////////////

	class Clock : public QTimer
	{
		Q_OBJECT

	public:
		Clock(QObject *parent = Q_NULLPTR);

		Timestamp now();
		
		void schedAbs(Timestamp t, const QObject *receiver, const char *method);
		

	private:

		Timestamp initTime;

		private slots:
		void tick();

		//void restartTime();
	};
}

#endif // CLOCKs_H