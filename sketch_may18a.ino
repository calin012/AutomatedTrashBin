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
  pinMode(BUTTON, INPUT_PULLUP); // Button wired to ground

  myServo.attach(SERVO);
  myServo.write(90); // Start with servo stopped
}

void loop() {
  bool buttonPressed = digitalRead(BUTTON) == LOW;

  // Trigger ultrasonic sensor
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Read echo duration
  duration = pulseIn(ECHO, HIGH);
  distance = (duration * 0.0343) / 2.0;

  Serial.print("Distance (cm): ");
  Serial.println(distance);

  // Check distance or button press
  if (distance <= 70 || buttonPressed) {
    // Rotate forward
    myServo.write(0);    // full speed forward
    delay(180);         // rotate for 1 second

    // Stop
    myServo.write(90);
    delay(5000);         // wait while stopped

    // Rotate backward
    myServo.write(180);  // full speed backward
    delay(180);         // rotate for 1 second

    // Stop again
    myServo.write(90);
  } else {
    myServo.write(90);   // Stay stopped
  }

  delay(100); // Small delay for stability
}
