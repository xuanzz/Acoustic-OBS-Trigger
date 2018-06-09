int getThreshold()
{
threshold = EEPROM.read(thresholdValueAddress);
}

void setThreshold(int thresholdValue)
{
  EEPROM.write(thresholdValueAddress, thresholdValue);
}

