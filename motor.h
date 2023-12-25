#include <ESP32Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

void setupServos() {
  myservo1.attach(12);  // attaches the servo on pin 12
  myservo2.attach(13);  // attaches the servo on pin 13
  myservo3.attach(14);  // attaches the servo on pin 14
  myservo4.attach(25);  // attaches the servo on pin 25
  myservo5.attach(26);  // attaches the servo on pin 26
}

void rotateServos(int angle1, int angle2, int angle3, int angle4, int angle5) {
  myservo1.write(angle1);  // tell servo to go to position in variable 'angle1'
  myservo2.write(angle2);
  myservo3.write(angle3);
  myservo4.write(angle4);
  myservo5.write(angle5);
}
