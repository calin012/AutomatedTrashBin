#include <Servo.h>

#define TRIG 10
#define ECHO 9
#define SERVO A1
#define BUTTON 7

long duration;
float distance;

Servo myServo;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUTTON, INPUT_PULLUP); 

  myServo.attach(SERVO);
  myServo.write(90);
}

void loop() {
  bool buttonPressed = digitalRead(BUTTON) == LOW;

 
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distance = (duration * 0.0343) / 2.0;

  Serial.print("Distance (cm): ");
  Serial.println(distance);

  if (distance <= 70 || buttonPressed) {
    myServo.write(0);   
    delay(180);         

    // Stop
    myServo.write(90);
    delay(5000);         

    // Rotate backward
    myServo.write(180);  
    delay(180);         

    // Stop again
    myServo.write(90);
  } else {
    myServo.write(90);   
  }

  delay(100); 
}
