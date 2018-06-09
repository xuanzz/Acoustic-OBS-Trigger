// Records the timing of knocks.
void listenToSecretKnock() {
  Serial1.println("knock starting");
  int i = 0;
  // First lets reset the listening array.
  for (i = 0; i < maximumKnocks; i++) {
    knockReadings[i] = 0;
  }

  int currentKnockNumber = 0;             // Incrementer for the array.
  int startTime = millis();               // Reference for when this knock started.
  int now = millis();

  digitalWrite(greenLED, LOW);            // we blink the LED for a bit as a visual indicator of the knock.
  if (programButtonPressed == true) {
    digitalWrite(redLED, LOW);                         // and the red one too if we're programming a new knock.
  }
  delay(knockFadeTime);                                 // wait for this peak to fade before we listen to the next one.
  digitalWrite(greenLED, HIGH);
  if (programButtonPressed == true) {
    digitalWrite(redLED, HIGH);
  }
  do {
    if ((millis() - previousMillis) > updateInterval)
    {
      updateValue();
      previousMillis = millis();
    }
    knockSensorValue = averageValue - abs(analogRead(knockSensor));
    setStrip((knockSensorValue * 100 / threshold) * 7 / 100);
    //listen for the next knock or wait for it to timeout.
    if (knockSensorValue >= threshold) {                 //got another knock...
      //record the delay time.
      Serial1.println("knock.");
      now = millis();
      knockReadings[currentKnockNumber] = now - startTime;
      currentKnockNumber ++;                             //increment the counter
      startTime = now;
      // and reset our timer for the next knock
      digitalWrite(greenLED, LOW);
      if (programButtonPressed == true) {
        digitalWrite(redLED, LOW);                       // and the red one too if we're programming a new knock.
      }
      delay(knockFadeTime);                              // again, a little delay to let the knock decay.
      digitalWrite(greenLED, HIGH);
      if (programButtonPressed == true) {
        digitalWrite(redLED, HIGH);
      }
    }

    now = millis();

    //did we timeout or run out of knocks?
  } while ((now - startTime < knockComplete) && (currentKnockNumber < maximumKnocks));

  //we've got our knock recorded, lets see if it's valid
  if (programButtonPressed == false) {          // only if we're not in progrmaing mode.
    if (validateKnock() == true) {
      triggerDoorUnlock();
    } else {
      Serial1.println("Secret knock failed.");
      stripBlink(0);
    }
  } else { // if we're in programming mode we still validate the lock, we just don't do anything with the lock
    validateKnock();
    // and we blink the green and red alternately to show that program is complete.
    Serial1.println("New lock stored.");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    for (i = 0; i < 3; i++) {
      delay(100);
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(100);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
}

