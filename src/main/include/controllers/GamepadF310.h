// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

/**
 * ?: Written by FRC team 4669 for the 2021-2022 season. 
 * 
 * !: Please make sure that the controller is set to XInput and not DirectInput. 
 * To check, look on the back of the controller at the X/D switch, make sure its towards X.
 * 
 * !: Please make sure that the controller mode is not on. 
 * To check, look at the controller, near the Logitech logo there is a LED, if on, press the MODE button.
 * 
 * !: The F310 controller does not have rumble. 
 * Do not use the rumble feature. It will not work.
 */

#pragma once

#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/POVButton.h>

#include <Constants.h>

class GamepadF310 {
 public:
  GamepadF310();
  double getLeftJoyY();
  double getLeftJoyX();

  double getRightJoyY();
  double getRightJoyX();

  double getLeftTrigger();
  double getRightTrigger();

  /**
   * Actual controller object. Takes the USB order ID as a parameter.
   * 
   * !: Make sure the USB order ID is correct. 
   * To check, open FRC driver station and check the "USB Devices" tab and look at the order ID.
   * 
   * For example, this ID is 0. https://i.imgur.com/8G8JkBM.png 
   * For example, this ID is 3. https://i.imgur.com/daCHBMz.png
   */
  frc::Joystick f310Controller{ OperatorConstants::kF310ControllerID };

  // Colour buttons
  frc2::JoystickButton greenButton{ &f310joystick, 1 };
  frc2::JoystickButton redButton{ &f310joystick, 2 };
  frc2::JoystickButton blueButton{ &f310joystick, 3 };
  frc2::JoystickButton orangeButton{ &f310joystick, 4 };

  // Shoulder buttons
  frc2::JoystickButton leftShoulderButton{ &f310joystick, 5 };
  frc2::JoystickButton rightShoulderButton{ &f310joystick, 6 };

  // Misc buttons
  frc2::JoystickButton backButton{ &f310joystick, 7 };
  frc2::JoystickButton startButton{ &f310joystick, 8 };

  // Joystick buttons (joysticks can be pressed down)
  frc2::JoystickButton leftJoyButton{ &f310joystick, 9 };
  frc2::JoystickButton rightJoyButton{ &f310joystick, 10 };

  // POV Buttons (the D-Pad buttons that are on the left side of the controller, opposite of the colour buttons)
  frc2::POVButton dpadUpButton{ &f310joystick, 0 };
  frc2::POVButton dpadUpperRightButton{ &f310joystick, 45 };
  frc2::POVButton dpadRightButton{ &f310joystick, 90 };
  frc2::POVButton dpadLowerRightButton{ &f310joystick, 135 };
  frc2::POVButton dpadDownButton{ &f310joystick, 180 };
  frc2::POVButton dpadLowerLeftButton{ &f310joystick, 225 };
  frc2::POVButton dpadLeftButton{ &f310joystick, 270 };
  frc2::POVButton dpadUpperLeftButton{ &f310joystick, 315 };
  frc2::POVButton dpadCenteredButton{ &f310joystick, -1 };

 private:
   /**
    * Get value of a given axis after applying a deadzone.
    * 
    * @param joyID 
    * @return value of the axis after applying the deadzone 
    */
   double deadzone(int joyID);
};
