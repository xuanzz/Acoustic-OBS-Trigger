// Runs the motor (or whatever) to unlock the door.
void triggerDoorUnlock() {
  Serial1.println("Door unlocked!");
  int i = 0;

  // turn the motor on for a bit.
  MagnetState(0);
  digitalWrite(greenLED, HIGH);            // And the green LED too.
  delay (lockTurnTime);                    // Wait a bit.
  MagnetState(1);
  // Blink the green LED a few times for more visual feedback.
  stripBlink(1);

}

