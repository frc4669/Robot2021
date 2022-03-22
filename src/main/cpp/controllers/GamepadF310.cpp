// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include <controllers/GamepadF310.h>

GamepadF310::GamepadF310() {}

double GamepadF310::getLeftJoyY() {
  return deadzone(1, leftJoyXDeadzone);
}

double GamepadF310::getLeftJoyX() {
  return deadzone(0, leftJoyYDeadzone);
}


double GamepadF310::getRightJoyY() {
  return deadzone(5, rightJoyYDeadzone);
}

double GamepadF310::getRightJoyX(){
  return deadzone(4, rightJoyXDeadzone);
}


double GamepadF310::getLeftTrigger() { 
  return deadzone(2, leftTriggerDeadzone); 
}

double GamepadF310::getRightTrigger() { 
  return deadzone(3, rightTriggerDeadzone); 
}


double GamepadF310::deadzone(int axisID, double threshold) {
  double joystickValue = f310Controller.GetRawAxis(axisID);
  double joystickDeadzone = threshold;
  double absJoystickValue = abs(joystickValue);

  if(absJoystickValue > joystickDeadzone)
    return joystickValue;
  else
    return 0.0; // joystick value is within deadzone, return 0
}
