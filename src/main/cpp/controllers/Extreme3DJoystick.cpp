// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include "controllers/Extreme3DJoystick.h"

Extreme3DJoystick::Extreme3DJoystick(int controllerID, double joyYDeadzone, double joyXDeadzone, double joyZDeadzone, double sliderDeadzone) : extremeJoystick{controllerID} {
  this->joyYDeadzone = joyYDeadzone;
  this->joyXDeadzone = joyXDeadzone;
  this->joyZDeadzone = joyZDeadzone;
  this->sliderDeadzone = sliderDeadzone;
}

double Extreme3DJoystick::getJoyX() {
  return deadzone(0, joyXDeadzone);
}

double Extreme3DJoystick::getJoyY() {
  return deadzone(1, joyYDeadzone);
}

double Extreme3DJoystick::getJoyZ() {
  return deadzone(2, joyZDeadzone);
}

double Extreme3DJoystick::getSlider() {
  return deadzone(3, sliderDeadzone);
}


double Extreme3DJoystick::deadzone(int axisID, double threshold) {
  double joystickValue = extremeJoystick.GetRawAxis(axisID);
  double joystickDeadzone = threshold;
  double absJoystickValue = std::abs(joystickValue);

  if(absJoystickValue > joystickDeadzone)
    return joystickValue;
  else
    return 0.0; // joystick value is within deadzone, return 0
}
