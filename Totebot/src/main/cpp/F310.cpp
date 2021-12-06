/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "frc/Joystick.h"
#include <frc2/command/button/JoystickButton.h>
#include "F310.h"

F310::F310() 
{
    // startButtonObject::whenPressed(new StopAll());
    // blueButtonObject::whenPressed(new ToggleCompressor());

}

double F310::getLeftX() {
    return deadzone(0);
}

double F310::getLeftXCubed() {
    return pow(getLeftX(), 3);
}

double F310::getLeftY() {
    return -deadzone(1); // Negates the Y axis of the joystick so that up is positive and down is
                            // negative
}

double F310::getLeftYCubed() {
    return pow(getLeftY(), 3);
}

double F310::getLeftTrigger() {
    return deadzone(2);
}

double F310::getRightTrigger() {
    return deadzone(3);
}

double F310::getRightX() {
    return deadzone(4);
}

double F310::getRightXCubed() {
    return pow(getRightX(), 3);
}

// ControlWinch
double F310::getRightY() {
    return -deadzone(5); // Negates the Y axis of the joystick so that up is positive and down is
                            // negative
}

bool F310::getButton(int buttonPort) {
    return f310joystick.GetRawButton(buttonPort);
}

bool F310::getButtonPressed(int buttonPort) {
    return f310joystick.GetRawButtonPressed(buttonPort);
}

bool F310::getButtonReleased(int buttonPort) {
    return f310joystick.GetRawButtonReleased(buttonPort);
}

int F310::getDPadPOV() {
    return f310joystick.GetPOV();
}

double F310::deadzone(int port) {
    double joystickValue = f310joystick.GetRawAxis(port);
    double joystickOffset = 0.075;
    double absJoystickValue = abs(joystickValue);
    if (absJoystickValue > joystickOffset) {
        double speed = absJoystickValue;
        speed = (speed * speed) + joystickOffset;
        if (joystickValue > 0)
            return speed;
        else
            return -speed;
    } else {
        return 0;
    }
}
