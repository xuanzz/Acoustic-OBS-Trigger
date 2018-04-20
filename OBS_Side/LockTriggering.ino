// Runs the motor (or whatever) to unlock the door.
void triggerDoorUnlock() {
  Serial.println("Door unlocked!");
  int i = 0;

  // turn the motor on for a bit.
  digitalWrite(lockMotor, HIGH);
  MagnetState(0);
  digitalWrite(greenLED, HIGH);            // And the green LED too.
  delay (lockTurnTime);                    // Wait a bit.
  digitalWrite(lockMotor, LOW);            // Turn the motor off.
  MagnetState(1);
  // Blink the green LED a few times for more visual feedback.
  for (i = 0; i < 5; i++) {
    digitalWrite(greenLED, LOW);
    delay(100);
    digitalWrite(greenLED, HIGH);
    delay(100);
  }

}

