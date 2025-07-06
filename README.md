# rp2040-meteo-station
Cheap and very simple meteo / weather station  with RP2040 (one/zero) , OLED 0.96 128x64 SSD 1315 / SSD 1306 module, sensors board BMP280 + AHT20 - to display : temperature, humidity, air pressure or optionally altitude 

Uses Arduino RP2040/RP2350 core from EARL PHILHOWER : https://github.com/earlephilhower/arduino-pico in board manager URL

Installation of following libraries is required to compile the source code :
- Adafruit AHTX0  for ATH20 humidity & temperature sensor :  https://github.com/adafruit/Adafruit_AHTX0
- Adafruit SSD1306 for SSD1315 based OLED 128x64 screen : https://github.com/adafruit/Adafruit_SSD1306
- Adafruit BMP280  for barometric Bosch BMxXXX air pressure, temperature and attitude sensor : https://github.com/adafruit/Adafruit_BMP280_Library

Low energy consuming portable USB based small device that can be used as altimeter when climbing or gliding. Everyone can build it :-) 
