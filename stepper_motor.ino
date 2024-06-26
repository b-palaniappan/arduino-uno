#include <AccelStepper.h>           // Load the AccelStepper library

#define motorPin1  8                // IN1 pin on the ULN2003A driver
#define motorPin2  9                // IN2 pin on the ULN2003A driver
#define motorPin3  10               // IN3 pin on the ULN2003A driver
#define motorPin4  11               // IN4 pin on the ULN2003A driver

int stepsPerRevolution = 64;        // steps per revolution
int degreePerRevolution = 5.625;    // degree per revolution

/*
 * AccelStepper::FULL2WIRE (2) means: 2 wire stepper (2 pins needed). 
 * AccelStepper::FULL3WIRE (3) means: 3 wire stepper, like a harddisk motor (3 pins needed). 
 * AccelStepper::FULL4WIRE (4) means: 4 wire stepper (4 pins needed). 
 * AccelStepper::HALF3WIRE (6) means: 3 wire half stepper, like a harddisk motor (3 pins needed) 
 * AccelStepper::HALF4WIRE (8) means: 4 wire half stepper (4 pins needed) 
 *
 * AccelStepper uses AccelStepper::FULL4WIRE (4 pins needed) by default.
 */
AccelStepper stepper(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  Serial.begin(9600);               // initialise the serial monitor

  stepper.setMaxSpeed(1000.0);      // set the max motor speed
  stepper.setAcceleration(100.0);   // set the acceleration
  stepper.setSpeed(200);            // set the current speed

}

// Degrees of the momevement. So first to 30 degrees, then to -30 graden then to 60 degrees etc.
int steps[] = { 0 ,180, 0, -180 };

// The total entries in steps[]
int stepsCount = 5;

// Keeps track of the position in steps[] we are about to run
int stepsIndex = 0;

void loop() {
  // If the stepper isn't moving and doesn't have to go any distance
  if (!stepper.isRunning() && stepper.distanceToGo() == 0) {

    // Move the stepper to the degrees on the position of stepIndex in steps[]
    stepper.moveTo(degToSteps(steps[stepsIndex]));

    // Increase the index when the movement has been finished
    stepsIndex++;

    // If we have executed all positions of steps[]
    if (stepsIndex > stepsCount) {
      // Set the index to 0 and start all over again
      stepsIndex = 0;
    }
  }
  stepper.run();
}

/*
 * Converts degrees to steps
 * 
 * 28BYJ-48 motor has 5.625 degrees per step
 * 360 degrees / 5.625 = 64 steps per revolution
 * 
 * Example with degToSteps(45):
 * (64 / 5.625) * 45 = 512 steps
 */
float degToSteps(float deg) {
  return (stepsPerRevolution / degreePerRevolution) * deg;
}
