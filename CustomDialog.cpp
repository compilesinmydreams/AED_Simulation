#include "mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QApplication>

class CustomDialog : public QDialog {
public:
    CustomDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

        QVBoxLayout *layout = new QVBoxLayout(this);

        // To add the combobox to the custom dialog
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItems(QStringList() << "Adult" << "Child");
        layout->addWidget(comboBox);

        // To add the OK button to the custom dialog and connect it to the accept slot
        QPushButton *okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);
        connect(okButton, &QPushButton::clicked, this, &CustomDialog::accept);

        // Set a fixed size
        setFixedSize(150, 100);
    }
};

void MainWindow::initializePatient() {
    CustomDialog dialog(this);

    dialog.move(25,100); // to move the custom dialog somewhere in the top left corner

    if (dialog.exec() == QDialog::Accepted) { // if user clicked ok
        QString choice = "Adult"; // Default choice

        // Retrieve the selected patient type from the custom dialog
        QList<QComboBox *> comboBoxes = dialog.findChildren<QComboBox *>();
        if (!comboBoxes.isEmpty()) {
            choice = comboBoxes.first()->currentText();
        }

        // Create the patient with the chosen type
        bool isAdult = (choice == "Adult");
        int randomScenario = QRandomGenerator::global()->bounded(2, 4); // random choice between V-FIB and V-Tach
        aed.createPatient(isAdult, randomScenario);

        qInfo("Patient created with type: %s", qPrintable(choice));
    } else {
        qInfo("User closed the dialog");
        qInfo("No Patient Type Selected. Please Restart the Device.");
        QApplication::quit();
    }
}
