// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "frc/Joystick.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/POVButton.h>

#include "Constants.h"

class F310 {
 public:
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

 // Objects/Defined Variables
  frc::Joystick f310joystick{OperatorConstants::kF310};

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

  frc2::JoystickButton greenButtonObject{&f310joystick, green_button};
  frc2::JoystickButton redButtonObject{&f310joystick, red_button};
  frc2::JoystickButton blueButtonObject{&f310joystick, blue_button};
  frc2::JoystickButton orangeButtonObject{&f310joystick, orange_button};
  frc2::JoystickButton leftShoulderButtonObject{&f310joystick, left_shoulder_button};
  frc2::JoystickButton rightShoulderButtonObject{&f310joystick, right_shoulder_button};
  frc2::JoystickButton backButtonObject{&f310joystick, back_button};
  frc2::JoystickButton startButtonObject{&f310joystick, start_button};
  frc2::JoystickButton leftJoyButtonObject{&f310joystick, left_joy_button};
  frc2::JoystickButton rightJoyButtonObject{&f310joystick, right_joy_button};

  frc2::POVButton dpadUpButtonObject{&f310joystick, 0};
  frc2::POVButton dpadUpperRightButtonObject{&f310joystick, 45};
  frc2::POVButton dpadRightButtonObject{&f310joystick, 90};
  frc2::POVButton dpadLowerRightButtonObject{&f310joystick, 135};
  frc2::POVButton dpadDownButtonObject{&f310joystick, 180};
  frc2::POVButton dpadLowerLeftButtonObject{&f310joystick, 225};
  frc2::POVButton dpadLeftButtonObject{&f310joystick, 270};
  frc2::POVButton dpadUpperLeftButtonObject{&f310joystick, 315};
  frc2::POVButton dpadCenteredButtonObject{&f310joystick, -1};
};
