// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <photonlib/PhotonCamera.h>
#include <units/angle.h>
#include <units/length.h>

#include <Constants.h>

class Vision : public frc2::SubsystemBase {
 public:
  Vision();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

  /**
   * Get shooter camera data.
   * 
   * @return PhotonPipelineResult object containing the frame information.
   */
  photonlib::PhotonPipelineResult GetShooterCamData();

  /**
   * Get intake camera data.
   * 
   * @return PhotonPipelineResult object containing the frame information.
   */
  photonlib::PhotonPipelineResult GetIntakeCamData();

  /**
   * Get the distance from the target hub to the camera.
   * 
   * @return distance to the target from the shooter camera in inches.
   * @param result PhotonPipelineResult object containing the frame information.
   */
  double GetHubTargetDistance(photonlib::PhotonPipelineResult* result);

  /**
   * Get the angle offset from the target hub to the camera.
   * 
   * @return angle offset to the target from the shooter camera in degrees.
   * @param result PhotonPipelineResult object containing the frame information.
   */
  double GetHubTargetAngle(photonlib::PhotonPipelineResult* result);

 private:
  photonlib::PhotonCamera m_shooterCamera{"Shooter Cam"};
  photonlib::PhotonCamera m_intakeCamera{"Intake Cam"};
};
