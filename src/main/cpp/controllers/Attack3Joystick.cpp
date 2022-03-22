// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include <controllers/Attack3Joystick.h>

Attack3Joystick::Attack3Joystick(int controllerID, double joyYDeadzone, double joyXDeadzone, double sliderDeadzone) : attack3Controller{controllerID} {
  this->joyYDeadzone = joyYDeadzone;
  this->joyXDeadzone = joyXDeadzone;
  this->sliderDeadzone = sliderDeadzone;
}

double Attack3Joystick::getJoyX() {
  return deadzone(0, joyYDeadzone);
}

double Attack3Joystick::getJoyY() {
  return deadzone(1, joyYDeadzone);
}

double Attack3Joystick::getSlider(){
  return deadzone(2, sliderDeadzone);
}


double Attack3Joystick::deadzone(int axisID, double threshold) {
  double joystickValue = attack3Controller.GetRawAxis(axisID);
  double joystickDeadzone = threshold;
  double absJoystickValue = abs(joystickValue);

  if(absJoystickValue > joystickDeadzone)
    return joystickValue;
  else
    return 0.0; // joystick value is within deadzone, return 0
}
