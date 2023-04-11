#include <Arduino.h>

#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  890 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  960 // this is the 'maximum' pulse length count (out of 4096)

#define SERVO_FREQ 200 // Analog servos run at ~50 Hz updates

int reservoir = -1;
float flowRate = 0.0;

void setup()
{
    Serial.begin(115200);
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
    delay(100);
    for (uint16_t i = 0; i<4; ++i) {
        pwm.setPWM(i, 0, SERVOMAX);
    }
}

void loop()
{
    if (Serial.available()) {
        reservoir = Serial.parseInt();
        flowRate = Serial.parseFloat();
    }
    else {
        Serial.print("[");
        Serial.print(reservoir);
        Serial.print(",");
        Serial.print(flowRate);
        Serial.print("]");

        for (uint16_t i = 0; i<4; ++i) {
            if (i!=reservoir) {
                pwm.setPWM(i, 0, SERVOMIN);
            }
            else {
                pwm.setPWM(i, 0, SERVOMAX);
            }
        }

    }

    delay(500);
}


// void setup() {
//     Serial.begin(115200);
//     Serial.println("16 channel PWM test!");

//     pwm.begin();
//     pwm.setPWMFreq(200);  //

//     // yield();
// }

// void loop() {

//     // //servo A
//     // Serial.println("A");
//     // pwm.setPWM(0, 0, 890);
//     // delay(2000);
//     // Serial.println("A2");
//     // pwm.setPWM(0, 0, 930);
//     // delay(2000);
//     // //servo B
//     // Serial.println("B");
//     // pwm.setPWM(1, 0, 890);
//     // delay(2000);
//     // Serial.println("B2");
//     // pwm.setPWM(1, 0, 930);
//     // delay(2000);
//     // //Servo C
//     // Serial.println("C");
//     // pwm.setPWM(2, 0, 905);
//     // delay(2000);
//     // Serial.println("C2");
//     // pwm.setPWM(2, 0, 965);
//     // delay(2000);
//     // //Servo D
//     // Serial.println("D");
//     // pwm.setPWM(3, 0, 900);
//     // delay(2000);
//     // Serial.println("D2");
//     // pwm.setPWM(3, 0, 960);
//     // delay(2000);

//     Serial.println("1");
//     for (uint16_t pulselen = SERVOMIN; pulselen<SERVOMAX; ++pulselen) {
//         pwm.setPWM(2, 0, pulselen);
//     }
//     delay(500);
//     Serial.println("2");
//     for (uint16_t pulselen = SERVOMAX; pulselen>=SERVOMAX; --pulselen) {
//         pwm.setPWM(2, 0, pulselen);
//     }
//     delay(500);
// }
