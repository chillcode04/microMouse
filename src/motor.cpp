#include "motorControll.h"
#include "encoder.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29, &Wire);
sensors_event_t event;

double distance = 0;

double Kp = 3.45, Ki = 0.09, Kd = 1;
double targetAngleX = 0, integral = 0, prevT = 0, lastError = 0;
double errorAngle;
double currentAngle;

double normalization(double x)
{
    if (x > 180)
    {
        x = x - 360;
    }
    else if (x < -180)
    {
        x = x + 360;
    }
    return x;
}

void rightForward(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    ledcWrite(1, speed);
    digitalWrite(in3, LOW);
}
void leftForward(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    ledcWrite(0, speed);
    digitalWrite(in2, LOW);
}

void leftBackwards(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    ledcWrite(2, speed);
    digitalWrite(in1, LOW);
}

void rightBackwards(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    ledcWrite(3, speed);
    digitalWrite(in4, LOW);
}

void motor_stop()
{
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 0);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void motorForward(int speed1, int speed2)
{
    leftForward(speed1);
    rightForward(speed2);
}

void motorBackwards(int speed1, int speed2)
{
    leftBackwards(speed1);
    rightBackwards(speed2);
}
void goStraight(double s)
{
    xung_right = 0;
    xung_left = 0;
    distance = 0;
    double speed = 100;
    while (distance < s && speed > 10)
    {
        distance = (float)(xung_right + xung_left) / 2 * (WHEEL_DIAMETER * M_PI / PULSES_PER_REV);
        if (abs(distance - s) < 0.35 * s)
            speed = speed - 1.3;
        bno.getEvent(&event);
        currentAngle = event.orientation.x;
        currentAngle = normalization(currentAngle);

        double currT = micros();
        double deltaT = ((double)currT - prevT) / (1.0e6);
        prevT = currT;

        errorAngle = targetAngleX - currentAngle;
        if (errorAngle > 180)
            errorAngle -= 360;
        else if (errorAngle < -180)
            errorAngle += 360;

        double derivative = (errorAngle - lastError) / deltaT;
        integral += errorAngle * deltaT;

        double output = Kp * errorAngle + Kd * derivative + Ki * integral;
        lastError = errorAngle;

        int leftMotorSpeed = constrain(speed + output, MIN_SPEED, MAX_SPEED);
        int rightMotorSpeed = constrain(speed - output, MIN_SPEED, MAX_SPEED);

        motorForward(leftMotorSpeed, rightMotorSpeed);
    }
    motor_stop();
    delay(500);
}

void turnRight(double angleSet)
{
    xung_right = 0;
    double steps = angleSet * 1.2;
    double speed = 75;
    while (xung_right <= steps && speed > 10)
    {
        if (steps - xung_right < 35)
        {
            speed = speed - 1;
        }
        rightBackwards(speed);
        leftForward(speed);
    }
    motor_stop();
    targetAngleX = normalization(targetAngleX + angleSet);
    delay(500);
}

void turnLeft(double angleSet)
{
    xung_right = 0;
    double steps = angleSet * 1.2 + 20;
    double speed = 75;
    while (xung_right <= steps && speed > 10)
    {
        if (steps - xung_right < 40)
        {
            speed = speed - 1.55;
        }
        leftBackwards(speed);
        rightForward(speed);
    }
    motor_stop();
    targetAngleX = normalization(targetAngleX - angleSet);
    delay(500);
}