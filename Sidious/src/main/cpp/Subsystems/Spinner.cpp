// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Spinner.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/SpinnerStop.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS


Spinner::Spinner() : frc::Subsystem("Spinner") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
spinnerMotor.reset(new WPI_TalonSRX(8));



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
}

void Spinner::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new SpinnerStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Spinner::Periodic() {
    // Put code here to be run every loop

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Spinner::RotationControl(double Rotations)
{

  int counter = 0; //create a counter to count how many rotations of the spinner we have made
  bool same = true; //used for checking if the first color we see is the same as we see now
  const frc::Color initialColor = m_colorMatcher.MatchClosestColor(m_colorSensor.GetColor(), confidence);
  char initialColorChar;

  if (initialColor == kBlueTarget){ initialColorChar = 'B';}
  else if (initialColor == kRedTarget) {initialColorChar = 'R';} 
  else if (initialColor == kGreenTarget) {initialColorChar = 'G';}
  else if (initialColor == kYellowTarget) {initialColorChar = 'Y';} 
  else {initialColorChar = 'U';}

  while(counter < rotations)
  {

    spinnerMotor->Set(motorSpeed);

    if(getCurrentColor() == initialColorChar)
    {
      if(!same) {counter += increment;  same = true;} //saying the color we are reading now is the same as the one we just read previously. 
      else{same = true;} // we are still on the initial color and have not seen anything different
    }

    if(!(getCurrentColor() == initialColorChar))  {same = false;}

  }

spinnerMotor->Set(0.00);

}
void Spinner::RotationControlEnocder(double Rotations)
{

  while(spinnerMotor->GetSelectedSensorPosition() < Rotations)
  {
    spinnerMotor->Set(ControlMode::PercentOutput, 0.2);
  }

  spinnerMotor->Set(ControlMode::PercentOutput, 0.0);

  //138240 encoder rotations (360 TPR R4T encoder, 9:1 torque gearbox, 3 inch comp wheel)


}

void Spinner::PushDataToSD(double m_counter, std::string m_colorString)
{

  frc::SmartDashboard::PutNumber("Counter", m_counter);
  frc::SmartDashboard::PutString("Detected Color", m_colorString);

}

void Spinner::PositionControl()
{

  std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  
  if (gameData.length() > 0)
  {
    switch(gameData[0])
    {
      case 'B': GameDataBlue(getCurrentColor());  break;
      case 'R': GameDataRed(getCurrentColor());  break;
      case 'Y': GameDataYellow(getCurrentColor());  break;
      case 'G': GameDataGreen(getCurrentColor()); break;
      default:  break;
    }
  }
}

char Spinner::getCurrentColor() {

  char colorChar;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(m_colorSensor.GetColor(), confidence);

  if (matchedColor == kBlueTarget){ colorChar = 'B';}
  else if (matchedColor == kRedTarget) {colorChar = 'R';} 
  else if (matchedColor == kGreenTarget) {colorChar = 'G';}
  else if (matchedColor == kYellowTarget) {colorChar = 'Y';} 
  else {colorChar = 'U';}

  return colorChar;

}

void Spinner::GameDataBlue(char currentColor) {
  if(currentColor == 'R') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'G') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'Y') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'U') {spinnerMotor->Set(ControlMode::PercentOutput, 0.0); }

}

void Spinner::GameDataRed(char currentColor) {
  if(currentColor == 'B') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'G') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'Y') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'U') {spinnerMotor->Set(ControlMode::PercentOutput, 0.0); }
}

void Spinner::GameDataGreen(char currentColor) {
  if(currentColor == 'R') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'B') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'Y') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'U') {spinnerMotor->Set(ControlMode::PercentOutput, 0.0); }
}

void Spinner::GameDataYellow(char currentColor) {
  if(currentColor == 'R') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'G') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'B') {spinnerMotor->Set(ControlMode::Position, 0); }
  if(currentColor == 'U') {spinnerMotor->Set(ControlMode::PercentOutput, 0.0); }
}