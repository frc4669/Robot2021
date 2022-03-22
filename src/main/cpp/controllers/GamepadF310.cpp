// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include <controllers/GamepadF310.h>

GamepadF310::GamepadF310() {}

double GamepadF310::getLeftJoyY() {
  return f310Controller.GetRawAxis(1);
}

double GamepadF310::getLeftJoyX() {
  return f310Controller.GetRawAxis(0);
};


double GamepadF310::getRightJoyY() {
  return f310Controller.GetRawAxis(5);
}

double GamepadF310::getRightJoyX(){
  return f310Controller.GetRawAxis(4);
}


double GamepadF310::getLeftTrigger() { 
  return f310Controller.GetRawAxis(2); 
}

double GamepadF310::getRightTrigger() { 
  return f310Controller.GetRawAxis(3); 
}


double GamepadF310::deadzone(int joyID) {
  double joystickValue = f310Controller.GetRawAxis(joyID);
  double joystickOffset = 0.075;
  double absJoystickValue = abs(joystickValue);

  if (absJoystickValue > joystickOffset) {
    double speed = absJoystickValue;
    speed = (speed * speed) + joystickOffset;

    if (joystickValue > 0)
      return speed;
    else
      return -speed;
  } else
    return 0;
}
