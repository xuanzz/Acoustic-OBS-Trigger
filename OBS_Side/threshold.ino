int getThreshold()
{
threshold = EEPROM.read(thresholdValueAddress);
}

void setThreshold(int thresholdValue)
{
  EEPROM.write(thresholdValueAddress, thresholdValue);
  threshold = thresholdValue;
}

void updateThresholdFromSerial()
{
  while (Serial.available() > 0)
  {
    char inputChar = Serial.read();
    if (inputChar == '+')
    {
      setThreshold(threshold + 1);
    }
    if (inputChar == '-')
    {
      setThreshold(threshold - 1);
    }
    if (inputChar == '*')
    {
      setThreshold(10);
    }
    Serial.print("Set threshold to: "); Serial.println(getThreshold());
  }
}

