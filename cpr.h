#ifndef CPR_H
#define CPR_H

#include <QString>
#include <QtGlobal>
#include <QThread>
#include <QApplication>
#include <QTimer>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include "aed.h"

int startCPR(AED *aed, int duration);
void RandomCPR( int duration);
void updateAED(AED *aed, int quality);
void pushHarder(AED *aed);
void goodCompressions(AED *aed);
void continueCPR(AED *aed);
void Release(AED *aed);

#endif // CPR_H
