
#include "pico/stdlib.h"      // Will be used to lower CPU speed and save energy
#include <Wire.h>             // Required for I2C communication with OLED and BMP280
#include <Adafruit_AHTX0.h>   // library for AHT20 higrometer
#include <Adafruit_SSD1306.h> // Library for OLED 0.96 inch display
#include <Adafruit_BMP280.h>  // library for BMP280 sensor 

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SEALEVELPRESSURE_HPA (1013.25)

// inititialize OLED display class
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

// initialize BMP280 sensor class
Adafruit_BMP280 bmp;      // I2C

// initialize AHT20
Adafruit_AHTX0 aht;

// to check if AHT20 sensor present
uint8_t  isaht20;

void setup() {

  set_sys_clock_khz(20000, true); // Lowering CPU System clock to 20000 kHz to save energy
  // set_sys_clock_48mhz(); // Set System clock back to 48 MHz 
 
// launch I2C for BMP280 sensor
  Wire.setSDA(4); // Set SDA pin for I2C0 on RP2040
  Wire.setSCL(5); // Set SCL pin for I2C0 on RP2040
  Wire.begin();   // Initialize I2C communication - bus #1

Serial.println(F("Testing pressure sensor..."));
  if (!bmp.begin()) Serial.println(F("Pressure sensor NOT detected!"));

// launching AHT20 sensor
  isaht20 = 1;
  if (!aht.begin()) 
    { Serial.println("Could not find AHT20 sensor!");
      isaht20 = 0; }; 

// launch I2C for OLED display 
  Wire1.setSDA(10); // Set SDA pin for I2C1 on RP2040
  Wire1.setSCL(11); // Set SCL pin for I2C1 on RP2040
  Wire1.begin();    // Initialize I2C communication - bus #2

  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address may be different
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setRotation(2); //rotates text on OLED 1=90 degrees, 2=180 degrees

  // set contrast for OLED - lower value = less power drain if you want to conserve battery
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(255);
}

void loop() {

  sensors_event_t humidity, temp;
 
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);

  // read temperature & humidity from AHT20 sensor
  if (isaht20) aht.getEvent(&humidity, &temp);

  // display temperature from BMP280 or AHT20
  display.print("TMP=");
  if (!isaht20) 
      {  display.print(bmp.readTemperature()); }  // display temp from BMP280
  else 
      { display.print(temp.temperature); };       // display temp from AHT20
  display.println("C");
                                                                                                                                                                                                                
  display.println("CISNIENIE=");
  display.print(bmp.readPressure() / 100.0F);
  display.println("hPa");
  
//  display.print("NPM=");
//  display.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
//  display.print("m");

  display.print("WILG=");
  display.print(humidity.relative_humidity);
  display.println("%");

  display.display();  
  delay(1000);
}
