
#include <QApplication>
#include "OrlojTest.h"

using namespace Orloj;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	//qDebug() << "Orloj test";
	OrlojTestApplication test;
	return app.exec();
}


OrlojTestApplication::OrlojTestApplication(QObject *parent) {
	//connect(&clock, SIGNAL(timeout()), this, SLOT(onTick()));
	//clock.start(1000);
	//clock.schedAbs(a, this, SLOT(onSchedAbs()));

	SystemClock sc;
	//sc.cycleTest(10);
	
	/*
	qDebug() << sc.now().toString(); 
	Timestamp a = sc.now();
	Timestamp b = sc.now();
	qDebug() << a.toString();
	qDebug() << b.toString();
	*/
	
}

void OrlojTestApplication::onTick() {
	//qDebug() << clock.now().toString();
	Timestamp ts = clock.now();
	qDebug() << "sec:" << ts.second() << " nsec: " << ts.nsecs();
	qDebug() << "bundle" << ts.toBundle();
}

void OrlojTestApplication::onSchedAbs() {
	qDebug() << "OrlojTestApplication::onSchedAbs()";
}


