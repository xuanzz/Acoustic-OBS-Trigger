void MagnetSetup() {
  myservo.attach(14);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
  delay(2000);
  MagnetState(1);
}

void MagnetState(int State)
{
  if (State==1)
    myservo.write(170);
  else
  {
    myservo.write(90);
  }
}

