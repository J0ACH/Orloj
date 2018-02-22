
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

	connect(&clock, SIGNAL(timeout()), this, SLOT(onTick()));
	clock.start(1000);
}

void OrlojTestApplication::onTick() {
	//qDebug() << clock.now().toString();
	Timestamp ts = clock.now();
	qDebug() << "sec:" << ts.second() << " nsec: " << ts.nsecs();
	qDebug() << "bundle" << ts.toBundle();
}


