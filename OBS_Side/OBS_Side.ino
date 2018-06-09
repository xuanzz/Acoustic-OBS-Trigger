//Average sampling settings
#define updateInterval  50 //how long between each sampling, in 1/1000 seconds(1000 = 1 sec)
#define samplingPeriod  10000 //how long would you like to calculate the average value
#define  windowPeriod 5000 //how long would you like to let the user to input the pulse
short currentSampleCount = 0; //current count of sample
int maxSampleCount = (samplingPeriod + windowPeriod) / updateInterval;
long averageValue = 0;
int averageCount = samplingPeriod / updateInterval; //how many of values in the sampling period
int capturedValue[(samplingPeriod + windowPeriod) / updateInterval]; //the amount of samples in the sampling period
unsigned long previousMillis = 0;

//Magnet Settings
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

// Pin definitions
const int knockSensor = 1;         // Piezo sensor on pin 0.
const int programSwitch = 2;       // If this is high we program a new code.
const int lockMotor = 21;           // Gear motor used to turn the lock.
const int redLED = 3;              // Status LED
const int greenLED = 2;
// Status LED

// Tuning constants.  Could be made vars and hoooked to potentiometers for soft configuration, etc.
const int threshold = 10;           // Minimum signal from the piezo to register as a knock
const int rejectValue = 25;        // If an individual knock is off by this percentage of a knock we don't unlock..
const int averageRejectValue = 15; // If the average timing of the knocks is off by this percent we don't unlock.
const int knockFadeTime = 150;     // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int lockTurnTime = 650;      // milliseconds that we run the motor to get it to go a half turn.
const int maximumKnocks = 20;       // Maximum number of knocks to listen for.
const int knockComplete = 1200;     // Longest time to wait for a knock before we assume that it's finished.


// Variables.
int secretCode[maximumKnocks] = {50, 25, 25, 50, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Initial setup: "Shave and a Hair Cut, two bits."
int knockReadings[maximumKnocks];   // When someone knocks this array fills with delays between knocks.
int knockSensorValue = 0;           // Last reading of the knock sensor.
int programButtonPressed = false;   // Flag so we remember the programming button setting at the end of the cycle.

void setup() {
  averageSamplingSetup();
  pinMode(lockMotor, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(programSwitch, INPUT);
  Serial.begin(9600);                     // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");       // but feel free to comment them out after it's working right.
  digitalWrite(greenLED, HIGH);      // Green LED on, everything is go.
  MagnetSetup();
}

void loop() {
  if ((millis() - previousMillis) > updateInterval)
  {
    updateValue();
    previousMillis = millis();
  }
  // Listen for any knock at all.
  knockSensorValue = averageValue - abs(analogRead(knockSensor));
  //  if (digitalRead(programSwitch)==HIGH){  // is the program button pressed?
  //    programButtonPressed = true;          // Yes, so lets save that state
  //    digitalWrite(redLED, HIGH);           // and turn on the red light too so we know we're programming.
  //  } else {
  //    programButtonPressed = false;
  //    digitalWrite(redLED, LOW);
  //  }

  if (knockSensorValue >= threshold) {
    listenToSecretKnock();
  }
}
