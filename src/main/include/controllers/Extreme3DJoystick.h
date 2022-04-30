// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

/**
 * ?: Written by FRC team 4669 for the 2021-2022 season.
 */

#pragma once

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/POVButton.h>

#include <Constants.h>

class Extreme3DJoystick {
 public:
  /**
   * Actual controller object.
   *
   * !: Make sure the USB order ID is correct.
   * To check, open FRC driver station and check the "USB Devices" tab and look at the order ID.
   *
   * For example, this ID is 0. https://i.imgur.com/f5Y4lWg.png
   * For example, this ID is 3. https://i.imgur.com/CZ21uRp.png
   *
   * @param controllerID USB order ID of the controller.
   * @param joyYDeadzone The deadzone for the joystick Y axis. Default is 0.0.
   * @param joyXDeadzone The deadzone for the joystick X axis. Default is 0.0.
   * @param joyZDeadzone The deadzone for the joystick Z axis. Default is 0.0.
   * @param sliderDeadzone The deadzone for the slider. Default is 0.0.
   */
  Extreme3DJoystick(int controllerID, double joyYDeadzone=0.0, double joyXDeadzone=0.0, double joyZDeadzone=0.0, double sliderDeadzone=0.0);

  // Side to side
  double getJoyX();

  // Forward/backward
  double getJoyY();

  // Yaw (twist)
  double getJoyZ();

  // Little slider on the joystick
  double getSlider();


  //*: Objects
  frc::Joystick extremeJoystick;

  // Buttons on joystick handle
  frc2::JoystickButton triggerButton{ &extremeJoystick, 1 };
  frc2::JoystickButton sideTriggerButton{ &extremeJoystick, 2 };

  frc2::JoystickButton topLeftJoyButton{ &extremeJoystick, 5 };
  frc2::JoystickButton bottomLeftJoyButton{ &extremeJoystick, 3 };

  frc2::JoystickButton topRightJoyButton{ &extremeJoystick, 6 };
  frc2::JoystickButton bottomRightJoyButton{ &extremeJoystick, 4 };

  // Hat buttons on joystick handle
  frc2::POVButton hatUpButton{ &extremeJoystick, 0 };
  frc2::POVButton hatUpperRightButton{ &extremeJoystick, 45 };
  frc2::POVButton hatRightButton{ &extremeJoystick, 90 };
  frc2::POVButton hatLowerRightButton{ &extremeJoystick, 135 };
  frc2::POVButton hatDownButton{ &extremeJoystick, 180 };
  frc2::POVButton hatLowerLeftButton{ &extremeJoystick, 225 };
  frc2::POVButton hatLeftButton{ &extremeJoystick, 270 };
  frc2::POVButton hatUpperLeftButton{ &extremeJoystick, 315 };
  frc2::POVButton hatCenteredButton{ &extremeJoystick, -1 };

  // Side buttons on the joystick base
  frc2::JoystickButton topLeftButton{ &extremeJoystick, 7 };
  frc2::JoystickButton middleLeftButton{ &extremeJoystick, 9 };
  frc2::JoystickButton bottomLeftButton{ &extremeJoystick, 11 };

  frc2::JoystickButton topRightButton{ &extremeJoystick, 8 };
  frc2::JoystickButton middleRightButton{ &extremeJoystick, 10 };
  frc2::JoystickButton bottomRightButton{ &extremeJoystick, 12 };

 private:
  // Deadzone thresholds
  double joyYDeadzone;
  double joyXDeadzone;
  double joyZDeadzone;
  double sliderDeadzone;

  /**
   * Get value of a given axis after applying a deadzone.
   *
   * @param axisID ID of the axis to get the value of.
   * @param threshold The deadzone threshold.
   * @return value of axis, if it's above the threshold (deadzone), 0.0 otherwise
   */
  double deadzone(int axisID, double threshold);
};
