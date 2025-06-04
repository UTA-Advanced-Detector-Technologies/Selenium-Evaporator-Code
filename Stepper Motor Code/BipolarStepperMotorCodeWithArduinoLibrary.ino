#include <Stepper.h>

// Motor configuration
const int stepsPerRevolution = 4000; // Typically, a 1.8 stepper motor would have a defualt 200 steps. For some reason, this does not seems to be the case with this particular motor. With the 1000 frequency configuration, this should be 4000 steps. 

// Pin assignments
const int enablePin = 10;    // Motor enable pin
const int dirPin = 9;       // Direction control pin
const int pulsePin = 8;    // Pulse signal pin

// Motion Modifiers
float RampSpeed = 1;                // The starting speed of the motor
float RampMultOG = 0.25;           // The multiplier for how much of a revolution there is for the first speed
float RampMult = RampMultOG;      // The multiplier for how much of a revolution there is for a given speed
float RampStep = 0;              // The number of steps at a given speed (given value is arbitrary)
int TrgtSpeed = 20;             // The final speed of the motor in rpm 
float RampSub = 0;             // The amount of a revolution added to the RampMult value with each change in speed (given value is arbitrary)

// Stepper library instance
Stepper stepper(stepsPerRevolution, pulsePin, dirPin);

void setup() {
  // Initialize pins
  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);

  // Enable the motor
  digitalWrite(enablePin, LOW); // LOW enables motor on this driver
  RampSpeed = 1;
}

void loop() {
  // Rotate at increasing speed with fewer steps between until reaching its target speed
  if(RampSpeed < TrgtSpeed)                      // If the current speed setting is less than the target value
	{
    RampStep = stepsPerRevolution * RampMult;  // The number of steps the motor will take at a speed
		stepper.setSpeed(RampSpeed);              // Speed of motor
		stepper.step(RampSub);                   // Number of steps the motor will take
    RampSub = RampMultOG / TrgtSpeed;       // Adds a fraction of a revolution to the amount of steps removed from a revolution ()
		RampMult = RampMult - RampSub;         // Decreases the number of steps by a fraction of the starting steps
		RampSpeed = RampSpeed + 1;            // Increases the speed by one
	}
	else
	{
		stepper.setSpeed(TrgtSpeed);          // Speed is set to target speed
		stepper.step(stepsPerRevolution);    // One full revolution per loop
	}
}
