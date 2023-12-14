#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>
#include <QString>

using namespace std;

class Patient : public QObject {
    Q_OBJECT

public:
    // Public static variable
    static int p_count;

    // Constructor
    Patient(bool isAdult, int status, QObject *parent = nullptr);

    // destructor
    ~Patient();

    // Getters
    bool getIsAdult();
    int getStatus();

    // Setters
    void setStatus(int newStatus);

private:
    int num;
    bool isAdult;
    int status;
};

#endif // PATIENT_H
