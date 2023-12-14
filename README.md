# 3004_Final_Project
AED Plus Simulation



File Organization
The submission folder consists of two sub-directories:
 - Design Documents: Contains all design documents for this project. File names reflect the contents.
 - 3004_Final_Project: Project Source Code.
    Images folder containing visual assets for the application.
	Source & Header Files: aed.ccp/h, CPR.cpp/h, CustomDialog.cpp, mainwindow.cpp/h/ui, main.cpp, patient.cpp/h, resources.qrc and QT .pro file.


Installation, Setup and Instructions for Use:
- Open the 3004_Final_Project folder or the .pro file in QT.
- Build and Run the app in QT.
- To use:
    - Press the power button.
    - Select Adult or Child from the Combobox.
    - Click on OK.
    - Apply the respective electrode pads to the patient depending on the patient type.
    - While performing CPR:
    	- Click on the CPR buttons to adjust the CPR quality.
- For testing:
    - You can change inital patient status in the customDialogBox class.
    - You can change the patient status after CPR in the CPR utility module.

Tests:
- App builds and Runs in QT. Passed.
- Pressing power button turns the device on and off. Passed
- User can close application by clicking close window button. Passed
- User can run the simulation with either adult/child patient type. Passed
- Analyzed patient heart rate results in all possible scenarios. Passed
- Delivers a shock to the patient if heart rate anaysis concludes it shockable. Passed
- Battery level reduces after each shock. Passed
- AED Sends a warning when Battery level will drop below the minimum required charge. Passed
- Audio(console) prompts guiding the user with instructions for use. Passed
