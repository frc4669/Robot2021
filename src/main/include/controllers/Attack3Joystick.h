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

class Attack3Joystick {
 public:
  Attack3Joystick();
  // Side to side
  double getJoyX();

  // Forward/backward
  double getJoyY();

  // Little slider on the joystick
  double getSlider();

  /**
   * Actual controller object. Takes the USB order ID as a parameter.
   * 
   * !: Make sure the USB order ID is correct. 
   * To check, open FRC driver station and check the "USB Devices" tab and look at the order ID.
   * 
   * For example, this ID is 0. https://i.imgur.com/lleN1Ot.png
   * For example, this ID is 3. https://i.imgur.com/Ex4Lodt.png
   */
  frc::Joystick attack3Controller{ OperatorConstants::kAttack3JoystickID };

  // Buttons on joystick handle
  frc2::JoystickButton triggerButton{ &attack3Controller, 1 };

  frc2::JoystickButton leftJoyButton{ &attack3Controller, 4 };
  frc2::JoystickButton rightJoyButton{ &attack3Controller, 5 };

  frc2::JoystickButton topJoyButton{ &attack3Controller, 3 };
  frc2::JoystickButton bottomJoyButton{ &attack3Controller, 2 };

  // Left base buttons
  frc2::JoystickButton topLeftButton{ &attack3Controller, 6 };
  frc2::JoystickButton bottomLeftButton{ &attack3Controller, 7 };

  // Right base buttons
  frc2::JoystickButton topRightButton{ &attack3Controller, 11 };
  frc2::JoystickButton bottomRightButton{ &attack3Controller, 10 };

  // Center base buttons
  frc2::JoystickButton centerLeftButton{ &attack3Controller, 8 };
  frc2::JoystickButton centerRightButton{ &attack3Controller, 9 };

 private:
   /**
    * Get value of a given axis after applying a deadzone.
    * 
    * @param joyID 
    * @return value of the axis after applying the deadzone 
    */
   double deadzone(int joyID);
};
