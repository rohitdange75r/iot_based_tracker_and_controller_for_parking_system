/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "template id here"
#define BLYNK_TEMPLATE_NAME "IOT  TRACKER AND CONTROLLING FOR PARKING SYSTEM"
#define BLYNK_AUTH_TOKEN "auth token here"

#include <Wire.h>
#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid here";
char pass[] = "password here";

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo servo1, servo2;
// Servo servo2;

const int mainsensorPin1 = 16;
const int mainsensorPin2 = 17;
const int slotsensorPin1 = 5;
const int slotsensorPin2 = 18;
const int slotsensorPin3 = 19;
const int slotsensorPin4 = 23;

const int servopin1 = 13;
const int servopin2 = 12;

int Slot1 = 0;
int Slot2 = 0;
int Slot3 = 0;
int Slot4 = 0;

bool carInSensor1 = false;
bool carOutSensor1 = false;
bool carOutSensor2 = false;
bool carOutSensor3 = false;
bool carOutSensor4 = false;

void setup()
{
    Serial.begin(115200);
    servo1.attach(servopin1);
    servo2.attach(servopin2);
    pinMode(mainsensorPin1, INPUT);
    pinMode(mainsensorPin2, INPUT);
    pinMode(slotsensorPin1, INPUT);
    pinMode(slotsensorPin2, INPUT);
    pinMode(slotsensorPin3, INPUT);
    pinMode(slotsensorPin4, INPUT);
    lcd.init();
    lcd.clear();
    lcd.backlight(); // Make sure backlight is on

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{

    // Entry Detection
    if (digitalRead(mainsensorPin1) == LOW) // Entry gate sensor
    {
        servo1.write(90);
        delay(3000);
        if (!carInSensor1) // Car entering for the first time
        {
            carInSensor1 = true;
            // Check which slot sensor detects the car
            if (digitalRead(slotsensorPin1) == LOW)
            {
                Slot1++;
                Serial.println("Car Entered Slot 1");
            }
            // Check which slot sensor detects the car
            if (digitalRead(slotsensorPin2) == LOW)
            {
                Slot2++;
                Serial.println("Car Entered Slot 2");
            }
            // Check which slot sensor detects the car
            if (digitalRead(slotsensorPin3) == LOW)
            {
                Slot3++;
                Serial.println("Car Entered Slot 3");
            }
            // Check which slot sensor detects the car
            if (digitalRead(slotsensorPin4) == LOW)
            {
                Slot4++;
                Serial.println("Car Entered Slot 4");
            }
        }
    }
    else
    {
        carInSensor1 = false;
        servo1.write(0);
    }

    if (digitalRead(slotsensorPin1) == LOW)
    {
        delay(3000);
        if (!carOutSensor1 && Slot1 > 0)
        {
            carOutSensor1 = true;

            if (digitalRead(mainsensorPin2) == LOW)
            {
                Slot1--;
                Serial.println("Car Exited Slot 1");
                delay(1000);
                servo2.write(90);
            }
        }
    }

    else if (digitalRead(slotsensorPin2) == LOW)
    {
        delay(3000);
        if (!carOutSensor2 && Slot2 > 0)
        {
            carOutSensor2 = true;

            if (digitalRead(mainsensorPin2) == LOW)
            {
                Slot2--;
                Serial.println("Car Exited Slot 2");
                delay(1000);
                servo2.write(90);
            }
        }
    }

    else if (digitalRead(slotsensorPin3) == LOW)
    {
        delay(3000);
        if (!carOutSensor3 && Slot3 > 0)
        {
            carOutSensor3 = true;

            if (digitalRead(mainsensorPin2) == LOW)
            {
                Slot3--;
                Serial.println("Car Exited Slot 3");
                delay(1000);
                servo2.write(90);
            }
        }
    }

    else if (digitalRead(slotsensorPin4) == LOW)
    {
        delay(3000);
        if (!carOutSensor4 && Slot4 > 0)
        {
            carOutSensor4 = true;

            if (digitalRead(mainsensorPin2) == LOW)
            {
                Slot4--;
                Serial.println("Car Exited Slot 4");
                delay(1000);
                servo2.write(90);
            }
        }
    }
    else
    {
        carOutSensor1 = false;
        carOutSensor2 = false;
        carOutSensor3 = false;
        carOutSensor4 = false;
        servo2.write(0);
    }

    Serial.println("Slot1 = " + String(Slot1));
    Serial.println("Slot2 = " + String(Slot2));
    Serial.println("Slot3 = " + String(Slot3));
    Serial.println("Slot4 = " + String(Slot4));

    lcd.setCursor(3, 0);
    lcd.print("Parking System");

    lcd.setCursor(0, 1);
    lcd.print("Slot1:");
    lcd.print(Slot1);

    lcd.setCursor(9, 1);
    lcd.print("Slot2:");
    lcd.print(Slot2);

    lcd.setCursor(0, 2);
    lcd.print("Slot3:");
    lcd.print(Slot3);

    lcd.setCursor(9, 2);
    lcd.print("Slot4:");
    lcd.print(Slot4);

    Blynk.virtualWrite(V0, Slot1);
    Blynk.virtualWrite(V1, Slot2);
    Blynk.virtualWrite(V2, Slot3);
    Blynk.virtualWrite(V3, Slot4);

    Blynk.run();
}
