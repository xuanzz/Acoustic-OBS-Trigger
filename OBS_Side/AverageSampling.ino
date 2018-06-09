void averageSamplingSetup() {
  for (int i = 0; i < ((samplingPeriod + windowPeriod) / updateInterval); i++)
  {
    capturedValue[i] = analogRead(knockSensor);
    //Serial.println("Sample" + String(i) + ": " + (String)capturedValue[i]);
  }
}

void updateValue()
{
  if (currentSampleCount >= maxSampleCount - 1)  {
    currentSampleCount = 0;
  }
  else  {
    currentSampleCount ++;
  }
  capturedValue[currentSampleCount] = analogRead(knockSensor);
  if (abs((capturedValue[currentSampleCount] - averageValue)) > threshold * 2)
  {
    averageSamplingSetup();
  }
  //Serial.println("update Value " + (String)currentSampleCount + ": " + (String)capturedValue[currentSampleCount]);

  if (currentSampleCount % 1 == 0)
  {
    calculateWindowsAverage(currentSampleCount);
  }
}


int calculateWindowsAverage(int startPoint)
{
  //Serial.println("Start Point: " + (String)startPoint);
  long returnAverageValue = 0;
  for (int i = 0; i < averageCount; i++)
  {
    returnAverageValue += capturedValue[((startPoint + i) % maxSampleCount)];
    //Serial.println("Average index: " + (String)((startPoint + i) % maxSampleCount) + " Val: " + (String)returnAverageValue);
  }
  //Serial.println("End Point: " + (String)(((startPoint + averageCount-1) % maxSampleCount)));
  averageValue = returnAverageValue / averageCount;
  //Serial.println("calculate average: " + (String)averageValue);
  return returnAverageValue;
}
