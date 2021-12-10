/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "frc/Joystick.h"
#include <frc2/command/button/JoystickButton.h>
#include "frc2/command/button/POVButton.h"

#include "Constants.h"

class F310
{

public:

    frc::Joystick f310joystick{IOConstants::kF310};

    const int green_button = 1;
    const int red_button = 2;
    const int blue_button = 3;
    const int orange_button = 4;
    const int left_shoulder_button = 5;
    const int right_shoulder_button = 6;
    const int back_button = 7;
    const int start_button = 8;
    const int left_joy_button = 9;
    const int right_joy_button = 10;

    frc2::Button greenButtonObject = frc2::Button([this] { return this->getButton(this->green_button); });
    frc2::Button redButtonObject = frc2::Button([this] { return this->getButton(this->red_button); });
    frc2::Button blueButtonObject = frc2::Button([this] { return this->getButton(this->blue_button); });
    frc2::Button orangeButtonObject = frc2::Button([this] { return this->getButton(this->orange_button);} );
    frc2::Button leftShoulderButtonObject = frc2::Button([this] { return this->getButton(this->left_shoulder_button);} );
    frc2::Button rightShoulderButtonObject = frc2::Button([this] { return this->getButton(this->right_shoulder_button);} );
    frc2::Button backButtonObject = frc2::Button([this] { return this->getButton(this->back_button);} );
    frc2::Button startButtonObject = frc2::Button([this] { return this->getButton(this->start_button);} );
    frc2::Button leftJoyButtonObject = frc2::Button([this] { return this->getButton(this->left_joy_button);} );
    frc2::Button rightJoyButtonObject = frc2::Button([this] { return this->getButton(this->right_joy_button);} );

    // The above syntax for buttons were changed to adjust for a bug in frc library
    // This is a example of it properly used: 
    // frc2::Button rightJoyButtonObject{&f310joystick, right_joy_button};

    F310();
    double getLeftX();
    double getLeftXCubed();
    double getLeftY();
    double getLeftYCubed();
    double getRightX();
    double getRightXCubed();
    double getRightY();
    double getRightYCubed();
    double getLeftTrigger();
    double getRightTrigger();
    bool getButton(int buttonPort);
    bool getButtonPressed(int buttonPort);
    bool getButtonReleased(int buttonPort);
    int getDPadPOV();
    double deadzone(int port);

};