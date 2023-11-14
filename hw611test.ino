#include <Wire.h>
#include <Adafruit_BMP280.h>

#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; // I2C

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);
  unsigned status=bmp.begin(BMP280_ADDRESS);

  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.print(" Pa");
    Serial.print(" / ");
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure()/100);
    Serial.print(" hPa");
    Serial.print(" / ");
    Serial.print(bmp.readPressure()/100000);
    Serial.print(" bar");
    Serial.print(" / ");
    Serial.print(bmp.readPressure()/101300);
    Serial.println(" atm");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1005.5)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
}