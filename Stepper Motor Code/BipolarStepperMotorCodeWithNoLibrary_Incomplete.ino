#include <string>

#define enablePin 10
#define dirPin 9
#define pulsePin 8

int NumOfSteps = 4000;
float DELay = 1;
int DIR = 0;
float NewRPM = 0;
float CurrentRPM = 1;
int MinDelay = 3100;
float MaxRPM = 80;
float Increment = 0.1;
String demmand;


void setup() {
  Serial.begin(9600);

  pinMode(enablePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);

  digitalWrite(enablePin, LOW); 
  digitalWrite(dirPin, LOW);
  digitalWrite(pulsePin, LOW);

  if (MaxRPM > 0)
  {
    Serial.println("MaxRPM is...");
    Serial.println(MaxRPM);
  }
  else
  {
    MaxRPM = 60000 / (MinDelay * NumOfSteps);
    Serial.println("MaxRPM is...");
    Serial.println(MaxRPM);
  }
  delay(1000);
  Serial.println("Enter a new RPM at any time: ");
}

void loop() {
  
  if (Serial.available())
  {
    demmand = Serial.readStringUntil('\n');
    demmand.trim();
    NewRPM = demmand.toFloat();
    Serial.print("Adjusting to ");
    Serial.println(NewRPM);
  }

  if (NewRPM > MaxRPM)
  {
    NewRPM = CurrentRPM;
    Serial.print("Your NewRPM is too high. Try to enter something equal to or smaller than...");
    Serial.println(MaxRPM);
  }

  DELay = 60000000 / (CurrentRPM * NumOfSteps);

  if (NewRPM > CurrentRPM)
  {
    CurrentRPM = CurrentRPM + Increment;
    if (NewRPM < CurrentRPM)
    {
      CurrentRPM = NewRPM;
    }
  }
  else if (NewRPM < CurrentRPM)
  {
    CurrentRPM = CurrentRPM - Increment;
    if (NewRPM > CurrentRPM)
    {
      CurrentRPM = NewRPM;
    }
  }
  else
  {
    NewRPM = CurrentRPM;
  }

  if (NewRPM <= 0)
  {
    NewRPM = CurrentRPM;
  }
//

  if (DIR = 0)
  {
    digitalWrite(dirPin, LOW);
    for (int i = 0; i < NumOfSteps/40; i++) 
    { 
      digitalWrite(pulsePin, HIGH);
      delayMicroseconds(DELay);  
      digitalWrite(pulsePin, LOW);
      delayMicroseconds(DELay);
    }
  }
  else if(DIR = 1)
  {
    digitalWrite(dirPin, HIGH);
    for (int i = 0; i < NumOfSteps/64; i++)
    { 
      digitalWrite(pulsePin, LOW);
      delayMicroseconds(DELay);  
      digitalWrite(pulsePin, HIGH);
      delayMicroseconds(DELay);
    }
  }
  else
  {
    digitalWrite(enablePin, LOW);  
    digitalWrite(dirPin, LOW);  
    digitalWrite(pulsePin, LOW);
  }
}
