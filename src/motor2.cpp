// #include "motorControll.h"
// #include "encoder.h"

// Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29, &Wire);
// sensors_event_t event;

// double distance = 0;
// #define TIME_DELAY 500
// double Kp = 3.45, Ki = 0.09, Kd = 1;
// double targetAngleX = 0, integral = 0, prevT = 0;
// double lastErrorAngle = 0, lastErrorEncoder = 0, lastError = 0;
// double errorAngle, errorEncoder = 0;
// double currentAngle;

// double Kp1 = 5.5, Kd1 = 0.5;
// double Kp2 = 4, Kd2 = 1;
// double targetEncoder = 1000; // distance oneCell

// double leftMotorSpeed, rightMotorSpeed;
// double normalization(double x)
// {
//     if (x > 180)
//     {
//         x = x - 360;
//     }
//     else if (x < -180)
//     {
//         x = x + 360;
//     }
//     return x;
// }

// void rightForward(int speed)
// {
//     speed = constrain(speed, MIN_SPEED, MAX_SPEED);
//     ledcWrite(1, speed);
//     digitalWrite(in3, LOW);
// }
// void leftForward(int speed)
// {
//     speed = constrain(speed, MIN_SPEED, MAX_SPEED);
//     ledcWrite(0, speed);
//     digitalWrite(in2, LOW);
// }

// void leftBackwards(int speed)
// {
//     speed = constrain(speed, MIN_SPEED, MAX_SPEED);
//     ledcWrite(2, speed);
//     digitalWrite(in1, LOW);
// }

// void rightBackwards(int speed)
// {
//     speed = constrain(speed, MIN_SPEED, MAX_SPEED);
//     ledcWrite(3, speed);
//     digitalWrite(in4, LOW);
// }

// void motor_stop()
// {
//     ledcWrite(0, 0);
//     ledcWrite(1, 0);
//     ledcWrite(2, 0);
//     ledcWrite(3, 0);

//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
//     digitalWrite(in3, LOW);
//     digitalWrite(in4, LOW);
// }

// void motorForward(int speed1, int speed2)
// {
//     leftForward(speed1);
//     rightForward(speed2);
// }

// void motorBackwards(int speed1, int speed2)
// {
//     leftBackwards(speed1);
//     rightBackwards(speed2);
// }
// void moveFoward(double s)
// {
//     EnRight = 0, EnLeft = 0;
//     distance = 0;
//     leftMotorSpeed = 60, rightMotorSpeed = 60;
//     while (distance < s && leftMotorSpeed > 30 && rightMotorSpeed > 30)
//     {
//         distance = (double)(EnRight + EnLeft) / 2 * (WHEEL_DIAMETER * M_PI / PULSES_PER_REV);
//         // PID di oneCell
//         errorEncoder = s - distance;
//         double derivative1 = errorEncoder - lastError;

//         double output1 = Kp1 * errorEncoder + Kd1 * derivative1;
//         double speed = constrain(output1, MIN_SPEED, MAX_SPEED);

//         // PID di thang
//         bno.getEvent(&event);
//         currentAngle = event.orientation.x;
//         currentAngle = normalization(currentAngle);

//         errorAngle = targetAngleX - currentAngle;
//         if (errorAngle > 180) errorAngle -= 360;
//         else if (errorAngle < -180) errorAngle += 360;
//         double derivative2 = errorAngle - lastErrorAngle;

//         double output2 = Kp2 * errorAngle + Kd2 * derivative2;
//         double offsetSpeed = constrain(output2, 0, 50);

//         leftMotorSpeed = constrain(speed + offsetSpeed, MIN_SPEED, MAX_SPEED);
//         rightMotorSpeed = constrain(speed - offsetSpeed, MIN_SPEED, MAX_SPEED);

//         motorForward(leftMotorSpeed, rightMotorSpeed);
//         lastErrorAngle = errorAngle;
//         lastErrorEncoder = errorEncoder;
//     }
//     motor_stop();
//     delay(100);
// }
// void goStraight(double s)
// {
//     EnRight = 0;
//     EnLeft = 0;
//     distance = 0;
//     double speed = 100;
//     while (distance < s && speed > 10)
//     {
//         distance = (float)(EnRight + EnLeft) / 2 * (WHEEL_DIAMETER * M_PI / PULSES_PER_REV);
//         if (abs(distance - s) < 0.35 * s)
//             speed = speed - 1.3;
//         bno.getEvent(&event);
//         currentAngle = event.orientation.x;
//         currentAngle = normalization(currentAngle);

//         double currT = micros();
//         double deltaT = ((double)currT - prevT) / (1.0e6);
//         prevT = currT;

//         errorAngle = targetAngleX - currentAngle;
//         if (errorAngle > 180)
//             errorAngle -= 360;
//         else if (errorAngle < -180)
//             errorAngle += 360;

//         double derivative = (errorAngle - lastError) / deltaT;
//         integral += errorAngle * deltaT;

//         double output = Kp * errorAngle + Kd * derivative + Ki * integral;
//         lastError = errorAngle;

//         int leftMotorSpeed = constrain(speed + output, MIN_SPEED, MAX_SPEED);
//         int rightMotorSpeed = constrain(speed - output, MIN_SPEED, MAX_SPEED);

//         motorForward(leftMotorSpeed, rightMotorSpeed);
//     }
//     motor_stop();
//     delay(TIME_DELAY);
// }
// void turnRight(double angleSet)
// {
//     EnRight = 0, EnLeft = 0;
//     double steps = angleSet * 1.2;
//     double speed = 75;
//     while (EnRight <= steps && speed > 10)
//     {
//         if (steps - EnRight < 35)
//         {
//             speed = speed - 2.5;
//         }

//         errorEncoder = EnRight - EnLeft;
//         double offsetSpeed = 2 * errorEncoder;

//         leftMotorSpeed = constrain(speed + offsetSpeed, MIN_SPEED, MAX_SPEED);
//         rightMotorSpeed = constrain(speed - offsetSpeed, MIN_SPEED, MAX_SPEED);

//         rightBackwards(rightMotorSpeed);
//         leftForward(leftMotorSpeed);
//     }
//     motor_stop();
//     targetAngleX = normalization(targetAngleX + angleSet);
//     delay(TIME_DELAY);
// }
// void turnLeft(double angleSet)
// {
//     EnRight = 0, EnLeft = 0;
//     double steps = angleSet * 1.2 + 20;
//     double speed = 75;
//     while (EnRight <= steps && speed > 10)
//     {
//         if (steps - EnRight < 50)
//         {
//             speed = speed - 7;
//         }
//         errorEncoder = EnRight - EnLeft;
//         double offsetSpeed = 2 * errorEncoder;

//         leftMotorSpeed = constrain(speed + offsetSpeed, MIN_SPEED, MAX_SPEED);
//         rightMotorSpeed = constrain(speed - offsetSpeed, MIN_SPEED, MAX_SPEED);

//         leftBackwards(leftMotorSpeed);
//         rightForward(rightMotorSpeed);
//     }
//     motor_stop();
//     targetAngleX = normalization(targetAngleX - angleSet);
//     delay(TIME_DELAY);
// }