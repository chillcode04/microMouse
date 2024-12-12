#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

extern Adafruit_BNO055 bno;
extern sensors_event_t event;
#define in1 4
#define in2 16
#define in3 18
#define in4 19
#define ena1 25
#define ena2 32

#define MAX_SPEED 255
#define MIN_SPEED 0

#define PULSES_PER_REV 205
#define WHEEL_DIAMETER 3.8
#define oneCell 13.5

extern double distance;

extern double Kp, Ki, Kd;
extern double targetAngleX , integral, prevT , lastError ;
extern double errorAngle;
extern double currentAngle;

void rightForward(int speed);

void leftForward(int speed);

void leftBackwards(int speed);

void rightBackwards(int speed);

void motor_stop();

void motorForward(int speed1, int speed2);

void motorBackwards(int speed1, int speed2);

double normalization(double x);

void goStraight(double s);

void turnRight(double angleset);

void turnLeft(double angleset);
#endif
