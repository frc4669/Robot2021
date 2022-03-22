// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

//?: Written by FRC team 4669 for the 2021-2022 season.

#include <controllers/Attack3Joystick.h>

Attack3Joystick::Attack3Joystick() {}

double Attack3Joystick::getJoyX() {
  return attack3Controller.GetRawAxis(0);
}

double Attack3Joystick::getJoyY() {
  return attack3Controller.GetRawAxis(1);
}

double Attack3Joystick::getSlider(){
  return attack3Controller.GetRawAxis(2);
}


double Attack3Joystick::deadzone(int joyID) {
  double joystickValue = attack3Controller.GetRawAxis(joyID);
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
