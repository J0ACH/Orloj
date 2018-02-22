
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
	//qDebug() << clock.now().secs();
	//qDebug() << clock.now().second();

	Timestamp a(3.0950);
	Timestamp b(1);
	Timestamp c = a + b;
	//qDebug() << "sec:" << a.second() << " nsec: " << a.nsecs();
	qDebug() << a.toString();
	qDebug() << b.toString();
	qDebug() << c.toString();

	//connect(&clock, SIGNAL(timeout()), this, SLOT(onTick()));
	//clock.start(1000);
	clock.schedAbs(a, this, SLOT(onSchedAbs()));
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


