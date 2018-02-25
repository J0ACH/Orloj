
#include <QApplication>
#include "OrlojTest.h"

using namespace Orloj;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	OrlojTestApplication test;
	return app.exec();
}


OrlojTestApplication::OrlojTestApplication(QObject *parent) {

	/*
	Timetag zero;
	printTag(zero);
	Timetag current = clock.now();
	printTag(current);
	Timetag a(1.0075);
	printTag(a);
	qDebug() << a.toDouble();
	//qDebug() << a.toTime();
	Timetag b(1, 500);
	printTag(b);
	*/

	//clock.connectOnSec(this, SLOT(onTick()));

	/*
	*/
	Timetag a;// = Timetag(1.5);
	Timetag b = Timetag(0,10000);
	Timetag c = a + b;
	Timetag d = a - b;
	printTag(a);
	printTag(b);
	printTag(c);
	printTag(d);

}

void OrlojTestApplication::printTag(Timetag tag) {

	qDebug() << "\ntoString EPOCH   :" << tag.toString(Timetag::EPOCH);
	qDebug() << "toString BUNDLE  :" << tag.toString(Timetag::BUNDLE);
	qDebug() << "toString FULL    :" << tag.toString(Timetag::FULL);
	qDebug() << "toString DATE    :" << tag.toString(Timetag::DATE);
	qDebug() << "toString TIME    :" << tag.toString(Timetag::TIME);
	qDebug() << "toString DOUBLE  :" << tag.toString(Timetag::DOUBLE);


}

void OrlojTestApplication::onTick() {
	Timetag current = clock.now();
	printTag(current);

	//qDebug() << clock.now().toString();
	//Timetag ts = clock.now();
//	qDebug() << clock.now().toString();
	//qDebug() << "bundle" << ts.toBundle();
}

void OrlojTestApplication::onSchedAbs() {
	qDebug() << "OrlojTestApplication::onSchedAbs()";
}


