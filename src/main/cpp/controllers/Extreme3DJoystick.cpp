// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include <controllers/Extreme3DJoystick.h>

Extreme3DJoystick::Extreme3DJoystick() {}

double Extreme3DJoystick::getJoyX() {
  return extremeJoystick.GetRawAxis(0);
}

double Extreme3DJoystick::getJoyY() {
  return extremeJoystick.GetRawAxis(1);
}

double Extreme3DJoystick::getJoyZ() {
  return extremeJoystick.GetRawAxis(2);
}

double Extreme3DJoystick::getSlider() {
  return extremeJoystick.GetRawAxis(3);
}


double Extreme3DJoystick::deadzone(int axisID, double threshold) {
  double joystickValue = extremeJoystick.GetRawAxis(axisID);
  double joystickDeadzone = threshold;
  double absJoystickValue = abs(joystickValue);

  if(absJoystickValue > joystickDeadzone)
    return joystickValue;
  else
    return 0.0; // joystick value is within deadzone, return 0
}
