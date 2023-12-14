#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "aed.h"
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Contructor
    MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow();

private:
    //Private variables
    Ui::MainWindow *ui;
    AED aed;
    QLabel *imageLabel;
    QLabel *CPRLevelLabel;

private slots:
    void pressPowerButton();
    void initializePatient(); // implemented in the CustomDialog.cpp file
    void applyPads();
    void updateBatteryLevel(int level);
    void updateShockCount(int count);
    void displayHR(int status);
    void displayCompressions(int quality);
    void CPRButtonsEnable(bool value);
};
#endif // MAINWINDOW_H
