#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12346);
unsigned long previousTime = 0;

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Accelerometer Test");
    Serial.println("");

    if (!accel.begin())
    {
        Serial.println("ADXL345 was not detected ... please check wiring");
        while (1);
    }
    Serial.println("");
}

void loop()
{
    unsigned long currentTime = millis();
    if (currentTime - previousTime == 100)
    {
        previousTime = currentTime;

        sensors_event_t event;
        accel.getEvent(&event);

        float X = event.acceleration.x / 9.80665;
        float Y = event.acceleration.y / 9.80665;
        float Z = event.acceleration.z / 9.80665;
        
        Serial.print("{\"time\": ");
        Serial.print(currentTime);
        Serial.print(", \"x\": ");
        Serial.print(X);
        Serial.print(", \"y\": ");
        Serial.print(Y);
        Serial.print(", \"z\": ");
        Serial.print(Z);
        Serial.println("}");
    }
}
