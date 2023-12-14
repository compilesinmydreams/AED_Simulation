#include "cpr.h"

int startCPR(AED *aed, int duration) {
    // Start CPR for a duration
    qInfo("AED: Start CPR");
    QThread::sleep(1);
    RandomCPR(duration);

    // Stop CPR and disable CPR buttons
    emit aed->enableButton(false);
    QCoreApplication::processEvents();
    qInfo("AED: STOP CPR");

    // Update CPR level to 0 (none)
    updateAED(aed, 0);
    QCoreApplication::processEvents();

    QThread::sleep(1);

    // Return a random new status for the patient
   return QRandomGenerator::global()->bounded(0, 3);
}

void RandomCPR(int duration) {
    // Print *Push* to the console to simulate CPR
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() <= duration) {
        qInfo("User:*Push*");
        QCoreApplication::processEvents();
        QThread::msleep(800);
   }
}

void updateAED(AED *aed, int quality) {
    // Update CPR level
    emit aed->displayCompressionsSignal(quality);
    QCoreApplication::processEvents();
}

void pushHarder(AED *aed) {
    updateAED(aed, 1);
    qInfo("AED: PUSH HARDER");
}

void goodCompressions(AED *aed) {
    updateAED(aed, 3);
    qInfo("AED: Good Compressions");
}

void continueCPR(AED *aed) {
    updateAED(aed, 2);
    qInfo("AED: Continue CPR");
}

void Release(AED *aed) {
    updateAED(aed, 4);
    qInfo("AED: FULLY RELEASE");
}
