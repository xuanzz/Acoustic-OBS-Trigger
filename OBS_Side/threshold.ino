int getThreshold()
{
  threshold = EEPROM.read(thresholdValueAddress);
  return threshold;
}

void setThreshold(int thresholdValue)
{
  EEPROM.write(thresholdValueAddress, thresholdValue);
  threshold = thresholdValue;
}

void updateThresholdFromSerial()
{
  while (Serial1.available() > 0)
  {
    char inputChar = Serial1.read();
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
    Serial1.print("Set threshold to: "); Serial1.println(getThreshold());
  }
}

