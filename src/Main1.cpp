// #include "Floodfill.h"
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>
// #include <utility/imumaths.h>
// #include "motorControll.h"
// #include "IR.h"
// #include "encoder.h"
// #include <queue>

// void setup()
// {
//     Serial.begin(9600);

//     /* Initialise the sensor */
//     if (!bno.begin())
//     {
//         while (1)
//             ;
//     }

//     delay(500);
//     bno.setExtCrystalUse(true);

//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
//     pinMode(in3, OUTPUT);
//     pinMode(in4, OUTPUT);
//     pinMode(ena1, INPUT);
//     pinMode(ena2, INPUT);

//     // Cấu hình PWM cho ESP32
//     ledcSetup(0, 500, 8);
//     ledcSetup(1, 500, 8);
//     ledcSetup(2, 500, 8);
//     ledcSetup(3, 500, 8);
//     ledcAttachPin(in1, 0);
//     ledcAttachPin(in4, 1);
//     ledcAttachPin(in2, 2);
//     ledcAttachPin(in3, 3);

//     for (int i = 0; i < 3; i++)
//     {
//         pinMode(tx[i], OUTPUT);
//     }

//     // Đặt setpoint cho PID
//     bno.getEvent(&event);
//     attachInterrupt(digitalPinToInterrupt(ena1), encoderRight, FALLING);
//     attachInterrupt(digitalPinToInterrupt(ena2), encoderLeft, FALLING);


//     floodFill(1, 4); 
//     findPath(0, 0, 1, 4); 
// }
// void loop() {
//      //nhập y trước, x sau
//     // for (int i = 0; i < width; i++) {
//     //     for (int j = 0; j < height; j++) {
//     //         cout << distanceToEnd[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }
//       //  nhập điểm xuất phát và đích đến, y trước x sau
//     if(Way.size() > 1) { 
//         int Y = Way.front().first;
//         int X = Way.front().second;
//         Way.pop(); 
//         int Y1 = Way.front().first;
//         int X1 = Way.front().second;
//         GoToNextCell(Y, X, Y1, X1, currentDirection);
//     }
// }
