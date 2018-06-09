void stripSetup()
{
  // this resets all the neopixels to an off state
  strip.Begin();
  strip.SetPixelColor(7, red);
  strip.Show();
}

void setStrip(int count)
{
  for (int i = 0; i < constrain(count, 0, PixelCount - 1); i++)
  {
    strip.SetPixelColor(i, green);
  }
  for (int i = count; i < PixelCount - 1; i++)
  {
    strip.SetPixelColor(i, black);
  }
  strip.Show();
}

void stripBlink(bool msgCode)
{
  if (msgCode) //blink green color while code is true
  {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < PixelCount; i++)
      {
        strip.SetPixelColor(i, green);
      }
      strip.Show();
      delay(100);
      for (int i = 0; i < PixelCount; i++)
      {
        strip.SetPixelColor(i, black);
      }
      strip.Show();
      delay(100);
    }
  }
  else //blink red color while code is false
  {
    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < PixelCount; i++)
      {
        strip.SetPixelColor(i, red);
      }
      strip.Show();
      delay(100);
      for (int i = 0; i < PixelCount; i++)
      {
        strip.SetPixelColor(i, black);
      }
      strip.Show();
      delay(100);
    }
  }
  stripSetup();
}

