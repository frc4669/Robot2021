// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Vision.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <photonlib/PhotonUtils.h>

Vision::Vision() {

}

// This method will be called once per scheduler run
void Vision::Periodic() {
/* frc::SmartDashboard::PutBoolean("Intake Cam Has Targets", m_intakeCamera.GetLatestResult().HasTargets());
  frc::SmartDashboard::PutBoolean("Shooter Cam Has Targets", m_shooterCamera.GetLatestResult().HasTargets());

  frc::SmartDashboard::PutNumber("Shooter Target Estimated Distance", 0.00);
  frc::SmartDashboard::PutNumber("Estimated Exit Angle Needed", 0.00);
  frc::SmartDashboard::PutNumber("Estimated Exit Velocity Needed", 0.00); */
}

photonlib::PhotonPipelineResult Vision::GetShooterCamData() {
  return m_shooterCamera.GetLatestResult();
}

photonlib::PhotonPipelineResult Vision::GetIntakeCamData() {
  return m_intakeCamera.GetLatestResult();
}

double Vision::GetHubTargetDistance(photonlib::PhotonTrackedTarget* result) {
  units::meter_t dist =  photonlib::PhotonUtils::CalculateDistanceToTarget( VisionContants::kCameraHeight,
                                                                            VisionContants::kHubHeight,
                                                                            VisionContants::kCameraAngle,
                                                                            units::degree_t{ result->GetPitch() } );
  return dist.value();
}

bool Vision::ShooterHasTarget() {
  return GetShooterCamData().HasTargets();
}
