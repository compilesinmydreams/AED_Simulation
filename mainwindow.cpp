#include "mainwindow.h"
#include "ui_mainwindow.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->powerButton->setCursor(Qt::PointingHandCursor);
    ui->batteryLabel->setText("Battery Level: Initializing");

    // Initialize black box for the screen
    imageLabel = new QLabel(this);
    imageLabel->resize(200, 48);
    imageLabel->move(463, 170);
    imageLabel->raise(); // to ensure the label is at the front and not hidden
    imageLabel->setStyleSheet("background-color: black;");

    // Initialize the CPR quality bar
    CPRLevelLabel = new QLabel(this);
    CPRLevelLabel->move(470, 230);

    // Multiple connect functions
    connect(&aed, SIGNAL(batteryLevelChanged(int)), this, SLOT(updateBatteryLevel(int)));
    connect(&aed, SIGNAL(shockCountChanged(int)), this, SLOT(updateShockCount(int)));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressPowerButton()));
    connect(ui->adultPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->adultPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(&aed, SIGNAL(displayHRSignal(int)), this, SLOT(displayHR(int)));
    connect(&aed, SIGNAL(displayCompressionsSignal(int)), this, SLOT(displayCompressions(int)));
    connect(&aed, SIGNAL(enableButton(bool)), this, SLOT(CPRButtonsEnable(bool)));
    connect(ui->badCPRButton, SIGNAL(pressed()), &aed, SLOT(badCPRClicked()));
    connect(ui->okCPRButton, SIGNAL(pressed()), &aed, SLOT(okCPRClicked()));
    connect(ui->goodCPRButton, SIGNAL(pressed()), &aed, SLOT(goodCPRClicked()));
    connect(ui->fullyReleaseCPRButton, SIGNAL(pressed()), &aed, SLOT(releaseClicked()));
}

// Destructor
MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::pressPowerButton() {
    // Changes the color of the power button
    if (aed.getPower()) {
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(237, 51, 59);}");
    } else {
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(51, 209, 122);}");
        initializePatient(); // Initialize patient when the device is turned on
    }

    // Turn AED ON/OFF
    aed.togglePower();

    // Enable/disable the buttons for the pads
    if (aed.getPower()) {
        ui->adultPad1CheckBox->setEnabled(true);
        ui->adultPad2CheckBox->setEnabled(true);
        ui->childPad1CheckBox->setEnabled(true);
        ui->childPad2CheckBox->setEnabled(true);
    } else {
        ui->batteryLabel->setText("Battery Level: Initializing");
        ui->adultPad1CheckBox->setChecked(false);
        ui->adultPad2CheckBox->setChecked(false);
        ui->childPad1CheckBox->setChecked(false);
        ui->childPad2CheckBox->setChecked(false);

        ui->adultPad1CheckBox->setEnabled(false);
        ui->adultPad2CheckBox->setEnabled(false);
        ui->childPad1CheckBox->setEnabled(false);
        ui->childPad2CheckBox->setEnabled(false);
    }
}

void MainWindow::applyPads() {
    aed.setPadsStatus(ui->adultPad1CheckBox->isChecked(), ui->adultPad2CheckBox->isChecked(), ui->childPad1CheckBox->isChecked(), ui->childPad2CheckBox->isChecked());
}

void MainWindow::updateBatteryLevel(int level) {
    // Adjust the color based on the battery level
    QString textColor;
    if (level <= 20) {
        textColor = "red";
    } else if (level <= 60) {
        textColor = "orange";
    } else {
        textColor = "white";
    }

    // Update battery % level
    ui->batteryLabel->setText("Battery Level: " + QString::number(level) + "%");

    // Update the stylesheet
    ui->batteryLabel->setStyleSheet(QString("QLabel { color: %1; }").arg(textColor));

    QApplication::processEvents(); //Force UI updates
}

void MainWindow::updateShockCount(int count) {
    // Update shock count
    ui->shockLabel->setText("# of Shocks: " + QString::number(count));

    QApplication::processEvents(); //Force UI updates
}

void MainWindow::displayHR(int status) {
    // Update the image based on the status
    QPixmap originalImage;
    switch (status) {
        case 0:
            originalImage.load(":/images/asys.jpg");
            break;
        case 1:
            originalImage.load(":/images/stable.jpg");
            break;
        case 2:
            originalImage.load(":/images/vfib.jpg");
            break;
        case 3:
            originalImage.load(":/images/vtach.jpg");
            break;
        case 4:
            originalImage.load(":/images/black.jpg");
            break;
        default:
            break;
    }

    // Resize and set the image
    QPixmap resizedImage = originalImage.scaled(200, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(resizedImage);

    // Show the QLabel
    imageLabel->show();
}
void MainWindow::displayCompressions(int quality) {
    // Update the CPR Level Label to show the quality of the compressions
    CPRLevelLabel->raise(); // to ensure the label is at the front and not hidden
    if (quality==1) {
        CPRLevelLabel->resize(20, 5);
        CPRLevelLabel->setStyleSheet("background-color: red;");
    } else if (quality==2) {
        CPRLevelLabel->resize(35, 5);
        CPRLevelLabel->setStyleSheet("background-color: yellow;");
    } else if (quality==4) {
        CPRLevelLabel->resize(75, 5);
        CPRLevelLabel->setStyleSheet("background-color: blue;");
    } else if (quality==0) {
        CPRLevelLabel->setStyleSheet("background-color: transparent;");
    } else {
        CPRLevelLabel->resize(55, 5);
        CPRLevelLabel->setStyleSheet("background-color: green;");
    }
    CPRLevelLabel->show();
}

void MainWindow::CPRButtonsEnable(bool value) {
    // enable/disable CPR buttons
    ui->badCPRButton->setEnabled(value);
    ui->okCPRButton->setEnabled(value);
    ui->goodCPRButton->setEnabled(value);
    ui->fullyReleaseCPRButton->setEnabled(value);
}
