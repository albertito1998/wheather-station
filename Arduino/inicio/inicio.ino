#include <WiFi.h>
#include "time.h"
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_BMP085.h>
#include <TinyGPS++.h>                                  // Tiny GPS Plus Library
#include <SoftwareSerial.h>                             // Software Serial Library so we can use other Pins for communication with the GPS 
#include <MechaQMC5883.h>
#include <Adafruit_CCS811.h>
#include <BH1750.h>
#include <SPI.h>
#include <LoRa.h>
#include "FS.h"
#include "SD.h"
#include "Adafruit_VL53L0X.h"
#include "INA226.h"
#include "Adafruit_VEML6070.h"
// Provide the token generation process info.
#include <addons/TokenHelper.h>
// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>




// 'definitivo', 128x64px
const unsigned char myBitmap [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xe0, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x40, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0x80, 0x01, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xe0, 0x07, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xf9, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xf1, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 0xe1, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xc0, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xc0, 0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0x9f, 0x80, 0xf3, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0x0f, 0x80, 0xe3, 0xe0, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0x0f, 0x80, 0xc3, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x0f, 0xc1, 0x81, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x8c, 0x0f, 0xa3, 0x81, 0xec, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0x07, 0x1f, 0x01, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7c, 0x06, 0x1f, 0x01, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7c, 0x0c, 0x1f, 0x01, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x7e, 0x18, 0x1f, 0x83, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x79, 0xf8, 0x1e, 0x7e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x71, 0xf8, 0x1c, 0x7e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x61, 0xf8, 0x1c, 0x3e, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x41, 0xf8, 0x18, 0x3e, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0xc0, 0xfc, 0x30, 0x3f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x80, 0xf3, 0xf0, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x80, 0xe3, 0xe0, 0x38, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x80, 0xc3, 0xf0, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x0f, 0xc1, 0x81, 0xf0, 0x60, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xf3, 0x81, 0xfc, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0x01, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 0x01, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0xff, 0x01, 0xff, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0x83, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


// 'baseline_wifi_white_18dp', 10x10px
const unsigned char wifi [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x61, 0x80, 0x0c, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x0c, 0x00,
  0x00, 0x00, 0x00, 0x00
};


// 'baseline_battery_full_white_18dp', 10x10px
const unsigned char battery_full [] PROGMEM = {
  0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00,
  0x1e, 0x00, 0x00, 0x00
};


// 'baseline_battery_alert_white_18dp', 10x10px
const unsigned char battery_alert [] PROGMEM = {
  0x00, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x12, 0x00, 0x1e, 0x00, 0x12, 0x00, 0x1e, 0x00,
  0x1e, 0x00, 0x00, 0x00
};

// 'baseline_bluetooth_white_18dp', 10x10px
const unsigned char bluetooth [] PROGMEM = {
  0x00, 0x00, 0x04, 0x00, 0x26, 0x00, 0x1e, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x26, 0x00,
  0x04, 0x00, 0x00, 0x00
};

// 'LORA', 18x18px
const unsigned char LORA [] PROGMEM = {
  0xf7, 0xfb, 0xc0, 0xe7, 0xf9, 0xc0, 0xcf, 0xfc, 0xc0, 0x93, 0xf2, 0x40, 0xb3, 0x33, 0x40, 0x24,
  0x09, 0x00, 0x24, 0x0d, 0x00, 0x2c, 0x0d, 0x80, 0x2c, 0x0d, 0x80, 0x24, 0x09, 0x00, 0x26, 0x19,
  0x00, 0xb3, 0xf3, 0x40, 0x9b, 0xf6, 0x40, 0xcf, 0xfc, 0xc0, 0xe7, 0xf9, 0xc0, 0xf7, 0xfb, 0xc0,
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xc0
};


#define WIFI_SSID "EUSKALTEL_ham5Sx9"
#define WIFI_PASSWORD "ELfJJQt9Rwat3mDfuM"
#define FIREBASE_HOST "https://wheather-station-18cb0-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "C9VYnLQUa3PYcvaa6uL8kPVpfXF45q3tkBS4ybqp"
#define API_KEY "AIzaSyAb45HOgsruLp1SaxqTvrKu04qviqPFi_Y"

/* 3. Define the project ID */
#define FIREBASE_PROJECT_ID "wheather-station-18cb0"

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "tfmwhetaherstation@gmail.com" // 100365677@alumnos.uc3m.es
#define USER_PASSWORD "yJ1K1S0C4p" //Omega_98 333atl1998
//#define UID0 "RDQjNDZRm9NVXSigf75GO7poBv92" //tfmwhetaherstation@gmail.com
//#define UID1 "ElHYi2zcIFTSFk6N0nUsxWE4j352" //100365677@alumnos.uc3m.es
//#define UID2 "ViF2hDkYzkTO5SySGrFzyB3Mk4A2" //albegoco@gmail.com
//#define WS "SYSTEM1"

/* 4. If work with RTDB, define the RTDB URL */
#define DATABASE_URL "https://wheather-station-18cb0-default-rtdb.europe-west1.firebasedatabase.app/"

/* 6. Define the Firebase Data object */
FirebaseData fbdo;

/* 7. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 8. Define the FirebaseConfig data for config data */
FirebaseConfig config;

String USERS[3] = { "ElHYi2zcIFTSFk6N0nUsxWE4j352", "ViF2hDkYzkTO5SySGrFzyB3Mk4A2", "RDQjNDZRm9NVXSigf75GO7poBv92" };
String WHEATHER[3] = { "WHEATHER_1", "WHEATHER_2", "WHEATHER_3" };


#define BUTTON_PIN_BITMASK 0x200000000 //
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10800       /* Time ESP32 will go to sleep (in seconds) 3h 10800*/

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";



char epochTimeFormat [32];

const long gmtOffset_sec = 0;
const int daylightOffset_sec = 7200; //3600


///////////////////////////////////////////////////////////////////////
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT22     // DHT22 (AM2302)
#define CS_LORA 5
#define pluv_PIN GPIO_NUM_32
#define RESET 14
#define OLED_RESET -1
#define DIO0 2
#define SD_CHIP_SELECT_PIN 15
#define spreadingFactor 10
#define codingRateDenominator 5
#define signalBandwidth 500E3
#define SCREEN_ADDRESS 0x3c //128x64
#define TimeMeasure 4 // NUMBER OF MEASURINGS. ONE PER SECOND
#define TimeDisplay 3000 // number of miliseconds refresing display
#define BATTERYPIN 12

// CSS811
Adafruit_CCS811 ccs;

// DISPLAY
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// LIGHT METER
BH1750 lightMeter;


// BMP180
Adafruit_BMP085 bmp;

// INA226
INA226 INA;


//VL53L0X
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//VEML6070
Adafruit_VEML6070 uv = Adafruit_VEML6070();

//GPS
static const int RXPin = 16, TXPin = 17;                // Ublox 6m GPS module on pins 4(rx) and 3(tx).
static const uint32_t GPSBaud = 9600;                   // Ublox GPS default Baud Rate is 9600
TinyGPSPlus gps;                                        // Create an Instance of the TinyGPS++ object called gps
SoftwareSerial ss(RXPin, TXPin);                        // The serial connection to the GPS device



// QMC5883

MechaQMC5883 qmc;

String daysOfTheWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
String monthsNames[12] = { "January", "february", "March", "April", "May",  "June", "July", "August", "September", "October", "November", "December" };

// DEFINE GLOBAL VARIABLES
float PRESSUREBMP180 = 0, TEMPERATUREBMP180 = 0, TEMPERATUREDHT22 = 0, HUMIDITYDHT22 = 0, CO2 = 0, TVOC = 0, LIGHT = 0, UVLEVEL = 0, WATT = 0, SOLARVOLTAGE = 0, SHUNT = 0, CURRENT = 0, LATITUDE = 43.270591946730036, direccion = 0, wind = 0, LONGITUDE =-2.9422544972776223, headingDegrees,  waterLevel = 0, voltage = 0, ALTITUDE = 0;
float PRESSUREBMP180M = 0, TEMPERATUREBMP180M = 0, TEMPERATUREDHT22M = 0, HUMIDITYDHT22M = 0, CO2M = 0, TVOCM = 0, LIGHTM = 0, direccionM = 0, windM = 0, batteryLevelM = 0, voltageM = 0, WATTM = 0, SOLARVOLTAGEM = 0, SHUNTM = 0, CURRENTM = 0, waterLevelM = 0, ALTITUDEM = 0;
int16_t RELAY1 = 0, RELAY2 = 0, RELAY3 = 0, RELAY4 = 0, batteryLevel = 0;
unsigned long epochTime;
String Timestamp = "", forecast = "No data", statusRain = "No data"; unsigned long time_miliseconds;

int  contador  = 0, communication = 0 , UVLEVELM = 0;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 4096;  // sensor maximum
uint32_t delayMS;
String outgoing;              // outgoing message
byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xF3;      // destination to send to
//Pluviometro
RTC_DATA_ATTR int pluv_count = 0;
RTC_DATA_ATTR unsigned long epochTimePrevious = 0;
volatile long last_interrupt_time = 0;

struct Message {
  byte TemperatureAirLORA[5];
  byte HumidityAirLORA[5];
  byte PressureLORA[8];
  byte eCO2LORA[6];
  byte TVOCLORA[6];
  byte luxLORA[6];
  byte windLORA[4];
  byte direccionLORA[5];
  char waterLevelLORA[3];
  char batteryLevelLORA[3];
  byte UVLORA[2];
  byte WATTLORA [4];
  byte CURRENTLORA [4];
  byte VOLTAGESOLARLORA [4];
  byte SHUNTLORA [4];
  byte ALTITUDELORA [4];
  byte LONGITUDELORA [4];
  byte LATITUDELORA [4];
  char TimestampLORA[25];
  char RELAY1LORA[1];
  char RELAY2LORA[1];
  char RELAY3LORA[1];
  char RELAY4LORA[1];
} message;


unsigned long dataMillis = 0;
int count = 0;

void printLocalTime(), Firestore(), onReceive(int packetSize), RTDB(), checkConfig(),  sendLoraMessage(), sensorsInitialize(), measureAll(), MeanCalculation(), displayAll(), connectivity(), initLora(), initSD(), appendFile(fs::FS &fs, const char * path), writeFile(fs::FS &fs, const char * path, const char * message), RTDB(), drawProgressbar(int x, int y, int width, int height, int progress), displaySensorDetails();
bool wifiConnect();
void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Wire.begin();
  delay(100);
  esp_sleep_enable_ext0_wakeup(pluv_PIN, 1);
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 :
      Serial.println("Wakeup caused by external pluviometer");
      pluv_count++;
      wifiConnect();
      esp_sleep_enable_timer_wakeup((TIME_TO_SLEEP - (epochTime - epochTimePrevious) / 1000)* uS_TO_S_FACTOR);
      epochTimePrevious = epochTime;
      esp_deep_sleep_start();
      break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    case ESP_SLEEP_WAKEUP_TIMER :
      Serial.println("Wakeup caused by timer");
      sensorsInitialize();
      measureAll();
      MeanCalculation();
      displayAll();
      connectivity();
      ccs.disableInterrupt ();

      display.clearDisplay();
      display.display();
      epochTimePrevious = epochTime;
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                     " Seconds");
      //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
      Serial.println("Configured all RTC Peripherals to be powered down in sleep");
      Serial.println("Going to sleep now");
      Serial.flush();
      esp_deep_sleep_start();
      break;
    default :
      Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
      sensorsInitialize();
      measureAll();
      MeanCalculation();
      displayAll();
      connectivity();
      epochTimePrevious = epochTime;
      INA.configure(INA226_AVERAGES_1024, INA226_BUS_CONV_TIME_8244US,  INA226_SHUNT_CONV_TIME_8244US, INA226_MODE_POWER_DOWN);
       pluv_count=0;
      ccs.disableInterrupt ();
      qmc.setMode(Mode_Standby ,ODR_200Hz,RNG_2G,OSR_256);
      display.clearDisplay();
      display.display();
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                     " Seconds");
      //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
      Serial.println("Configured all RTC Peripherals to be powered down in sleep");
      Serial.println("Going to sleep now");
      Serial.flush();
      esp_deep_sleep_start();
      break;

  }
}
void loop()
{
}


//////////////////////////////////////////////////////////////////////////

void sensorsInitialize() {

  // ANALOGS 
  analogReadResolution(12);
  //analogSetSamples(samples);
  // INITIALIZE OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  } else {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);

    Serial.println("Initializing sensors...");
    display.println(F("Initializing sensors..."));
    display.display();
    delay(3000);
  }
  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(3000);

  // VL53L0X
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    // while (1);
  }


  // GPS
  ss.begin(GPSBaud);

  // INITIALIZE BMP180
  if (!bmp.begin(BMP085_ULTRALOWPOWER))
  {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
    //display.println(F("Couldn't find BMP180"));
    // display.display();
    delay(1000);
    // while (1) {}
  }


  // INA226
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  // Configure INA226
  INA.configure(INA226_AVERAGES_1024, INA226_BUS_CONV_TIME_8244US,  INA226_SHUNT_CONV_TIME_8244US, INA226_MODE_SHUNT_BUS_CONT);

  // Calibrate INA226. Rshunt = 0.01 ohm, Max excepted current = 4A
  INA.calibrate(0.01, 4);
  // Enable Power Over-Limit Alert
  INA.enableOverPowerLimitAlert();
  INA.setPowerLimit(1000);
  // Display configuration
  // checkConfig();


  // CO2 SENSOR
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);
  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    // while (1);
  }
 // ccs.enableInterrupt (); // FOR DATA READY
  //ccs.disableInterrupt ();
 // ccs.setThresholds(2000,   2500,  50 );
  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC);

  // VEML6070
  uv.begin(VEML6070_1_T);  // pass in the integration time constant
  bool activado = uv.clearAck();
  uv.setInterrupt ( true, 0); //level 1 for threshold value of 145, 0 for 102 (default)

  // DHT22
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;


  // LIGHT SENSOR
  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::ONE_TIME_LOW_RES_MODE)) {
    Serial.println(F("One mode low resolution"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }


  //HMC8553
  qmc.init();
  qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256); 
  /* Display some basic information on this sensor */
  displaySensorDetails();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readINA() {

  float currentINA = 0, wattsINA = 0, voltageINA = 0, shuntINA = 0;
  currentINA = INA.readShuntCurrent();
  wattsINA = INA.readBusPower();
  voltageINA = INA.readBusVoltage();
  shuntINA = INA.readShuntVoltage();
  if (currentINA < 0) {
    currentINA = 0;
  }
  if (wattsINA < 0) {
    wattsINA = 0;
  }
  if (voltageINA < 0) {
    voltageINA = 0;
  }
  if (shuntINA < 0) {
    shuntINA = 0;
  }
  WATT = wattsINA + WATT;
  SOLARVOLTAGE = voltageINA + SOLARVOLTAGE;
  SHUNT = shuntINA + SHUNT;
  CURRENT = currentINA + CURRENT;

}
void readCO2 () {
  if (ccs.available()) {
    ccs.setEnvironmentalData(TEMPERATUREDHT22, HUMIDITYDHT22);
    if (!ccs.readData()) {
      CO2 = ccs.geteCO2() + CO2;
      TVOC = ccs.getTVOC() + TVOC;
      float currentSelected = ccs.getCurrentSelected(); //returns the "Current Selected" in uA.
      Serial.print("eCO2: ");
      Serial.print(CO2);
      Serial.print("Current CSS811: ");
      Serial.print(currentSelected);
      Serial.print("TVOC: ");
      Serial.print(TVOC );
      Serial.print(" ppb");

    }
    else {
      Serial.println("ERROR!");
      while (1);
    }
  }
}


void readLight () {
  // we use here the maxWait option due fail save
  if (lightMeter.measurementReady(true)) {
    LIGHT = lightMeter.readLightLevel() + LIGHT;
    float lux = lightMeter.readLightLevel();
    Serial.print(F("Light: "));
    Serial.print(lux);
    Serial.println(F(" lx"));

    if (lux < 0) {
      Serial.println(F("Error condition detected"));
    } else {
      if (lux > 40000.0) {
        // reduce measurement time - needed in direct sun light
        if (lightMeter.setMTreg(32)) {
          Serial.println(
            F("Setting MTReg to low value for high light environment"));
        } else {
          Serial.println(
            F("Error setting MTReg to low value for high light environment"));
        }
      } else {
        if (lux > 10.0) {
          // typical light environment
          if (lightMeter.setMTreg(69)) {
            Serial.println(F(
                             "Setting MTReg to default value for normal light environment"));
          } else {
            Serial.println(F("Error setting MTReg to default value for normal "
                             "light environment"));
          }
        } else {
          if (lux <= 10.0) {
            // very low light environment
            if (lightMeter.setMTreg(138)) {
              Serial.println(
                F("Setting MTReg to high value for low light environment"));
            } else {
              Serial.println(F("Error setting MTReg to high value for low "
                               "light environment"));
            }
          }
        }
      }
    }
    Serial.println(F("--------------------------------------"));
  }
  lightMeter.configure(BH1750::ONE_TIME_LOW_RES_MODE);

  UVLEVEL = uv.readUV() + UVLEVEL;
  Serial.println("UV LEVEL: ");
  Serial.print(UVLEVEL);

}

void readHumidityAndTemperature() {
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    TEMPERATUREDHT22 = event.temperature + TEMPERATUREDHT22;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    HUMIDITYDHT22 = event.relative_humidity + HUMIDITYDHT22;
  }
}

void readPressure() {
  PRESSUREBMP180 = bmp.readPressure() + PRESSUREBMP180;
  TEMPERATUREBMP180 = bmp.readTemperature() + TEMPERATUREBMP180;
  ALTITUDE = bmp.readAltitude() + ALTITUDE+58;

}

void readQMC5883()
{
  /* Get a new sensor event */
 int x, y, z;
  int azimuth;
  //float azimuth; //is supporting float too
  qmc.read(&x, &y, &z,&azimuth);
  //azimuth = qmc.azimuth(&y,&x);//you can get custom azimuth
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.print(" a: ");
  Serial.print(azimuth);
  Serial.println();
  delay(100);
  float heading = atan2(x, y);

  // Correct for when signs are reversed.
  if (heading < 0)
    heading += 2 * PI;

  // Check for wrap due to addition of declination.
  if (heading > 2 * PI)
    heading -= 2 * PI;

  // Convert radians to degrees for readability.
  direccion = heading * 180 / M_PI + direccion;
  Serial.print("Angulo de la veleta: ");
  Serial.print(heading * 180 / M_PI);
}

void readBatteryLevel() {
  // read the analog in value
  voltage = analogRead(BATTERYPIN)*3.3/4095*2+voltage;
  Serial.println("Analog");
  Serial.println(analogRead(BATTERYPIN));
  Serial.println("voltage");
  Serial.println(voltage);
}



void readGPS() {
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude="); Serial.print(gps.location.lat(), 6);
      Serial.print("Longitude="); Serial.println(gps.location.lng(), 6);
      LATITUDE  = gps.location.lat();
      LONGITUDE = gps.location.lng();
      Timestamp = gps.date.value() + "" + gps.time.value();
      // PRINT TIME

      display.clearDisplay();
      int hora = gps.time.hour();
      int minutos = gps.time.minute();
      int load = 0;
      uint8_t par;

      display.fillRoundRect(0, 0, 128, 12, 3, SSD1306_WHITE);
      display.setCursor(8, 2);
      // Tamaño del texto
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK);
      display.print(gps.date.day());
      display.print("  ");
      display.print(gps.date.day());
      display.print("/");
      display.print(gps.date.month());
      display.print("/");
      display.println(gps.date.year());
      display.setTextColor(SSD1306_WHITE);
      // Tamaño del texto
      display.setTextSize(3);
      display.setCursor(15, 20);


      //display.print(hora);
      par = gps.time.second() & 0b1;
      if (par)
      {
        //numero impar
        display.print(" ");
      }
      else
      {
        //numero par
        display.print(":");
      }
      if (minutos < 10)
      {
        display.print("0");
      }
      else
      {
        // Posición del texto
        display.print("");
      }
      display.print(minutos);

      display.drawCircle(117, 48, 10, SSD1306_WHITE);
      display.setCursor(112, 45);
      display.setTextSize(1);
      if (gps.time.second() < 10)
      {
        display.print("0");
        display.print(gps.time.second());
      }
      else
      {
        display.println(gps.time.second());
      }

      time_miliseconds = ((gps.date.year() * 31556926 + (gps.date.month() - 1) * 2629743 + gps.date.day() * 86400 + gps.time.hour() * 3600 + gps.time.minute() * 60 + gps.time.second()) * 1000) - (1970 * 31556926) * 1000;
      load = map(gps.time.second(), 0, 59, 15, 106);
      display.drawLine(15, 50, load, 50, SSD1306_WHITE);

      // Enviar a pantalla
      display.display();

      delay(3000);
      // Limpir buffer
      display.clearDisplay();

    }
  }
}

void readLevelWater () {
  /*VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout! */

  
  int range = map(analogRead(26), sensorMin, sensorMax, 0, 3);
  // range value:
  switch (range) {
    case 0:    // Sensor getting wet
      statusRain = "Flood";
      break;
    case 1:    // Sensor getting wet
      statusRain = "Rain Start";
      break;
    case 2:    // Sensor dry
      statusRain = "No Rain";
      break;
  }

  // CALCULATE M2 RAIN
 waterLevel=pluv_count*10*2.76/201.061; // de ML y area de captador 201,061 a L/m2

  /*if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(measure.RangeMilliMeter);
    waterLevel = measure.RangeMilliMeter + waterLevel;
    display.print("mm");
    display.display();
    Serial.println();
    delay(2000);
  } else {
    display.display();
    display.clearDisplay();
    return;
  } */
}


void measureAll() {
  readLevelWater ();
  //readGPS();
  for (contador = 1; contador <= TimeMeasure; contador++) {
    display.clearDisplay();
    display.setTextSize(2); // set font size to 2 you can set it up to 3
    display.setCursor(0, 25);
    display.setTextColor(WHITE);
    display.print("MEASURING:");
    display.print(contador * 100 / TimeMeasure);
    display.print(" % ");
    drawProgressbar(0, 10, 120, 10, int(contador * 100 / TimeMeasure)); // declare the graphics fillrect(int x, int y, int width, int height)
    display.display();
    readPressure();
    readLight ();
    readHumidityAndTemperature();
    readCO2();
    //readINA();
    readBatteryLevel();
    delay(1000);
  }
}

void MeanCalculation() {
  contador=TimeMeasure;
  PRESSUREBMP180M = PRESSUREBMP180 / contador;
  TEMPERATUREBMP180M = TEMPERATUREBMP180 / contador;
  ALTITUDEM = ALTITUDE / contador;
  TEMPERATUREDHT22M = TEMPERATUREDHT22 / contador;
  HUMIDITYDHT22M = HUMIDITYDHT22 / contador;
  CO2M = CO2 / contador;
  TVOCM = TVOC / contador;
  LIGHTM = LIGHT / contador;
  UVLEVELM = UVLEVEL / contador;
  direccionM =  direccion / contador;
  windM = wind / contador;
  waterLevelM = waterLevel;
  voltageM = voltage / contador;
  batteryLevelM = voltageM*100-320;
  WATTM = WATT / contador;
  SOLARVOLTAGEM = SOLARVOLTAGE / contador;
  SHUNTM = SHUNT / contador;
  CURRENTM = CURRENT / contador;
 
}


void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

///////////////////////////////////////////////////////// COMUNICATIONNN ////////////////////////////////////////////
// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void connectivity()
{
  initSD();
  appendFile(SD, "/wheatherstation.txt");

  if (wifiConnect()) {
    /* Assign the api key (required) */
    //config.host = FIREBASE_HOST;
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the RTDB URL */
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);


    // Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    // Assign the maximum retry of token generation
    config.max_token_generation_retry = 5;
    Firebase.reconnectWiFi(true);
    /* Initialize the library with the Firebase authen and config */
    Firebase.begin(&config, &auth);

    // Getting the user UID might take a few seconds
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "") {
      Serial.print('.');
      delay(1000);
    }
    // Print user UID
    String uid = "";
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);
    Firestore();
    RTDB();
   
    WiFi.disconnect();
    delay(500);

  }
  else {
    Serial.println("No WIFI. Lora messaging");
    initLora();
  }

}



void RTDB() {

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {

        String path = "/" + USERS[i] + "/" + WHEATHER[j];

        String jsonStr = "";

        FirebaseJson json1;

        FirebaseJsonData jsonObj;

        json1.set("CurrentValues/Pressure", String(PRESSUREBMP180M));
        json1.set("CurrentValues/TemperatureBMP180", String(TEMPERATUREBMP180M));
        json1.set("CurrentValues/TemperatureAir", String(TEMPERATUREDHT22M));
        json1.set("CurrentValues/HumidityAir", String(HUMIDITYDHT22M));
        json1.set("CurrentValues/eCO2", String(CO2M));
        json1.set("CurrentValues/TVOC", String( TVOCM));
        json1.set("CurrentValues/lux", String( LIGHTM));
        json1.set("CurrentValues/wind", String( windM));
        json1.set("CurrentValues/direction", String( direccionM));
        json1.set("CurrentValues/waterLevel", String(waterLevelM));
        json1.set("CurrentValues/battery", String(batteryLevelM));
        json1.set("CurrentValues/voltage", String(voltageM));
        json1.set("CurrentValues/currentSolar", String(CURRENTM));
        json1.set("CurrentValues/solarVoltage", String(SOLARVOLTAGEM));
        json1.set("CurrentValues/watts", String(WATTM));
        json1.set("CurrentValues/lat", String(LATITUDE));
        json1.set("CurrentValues/Altitude", String(ALTITUDEM));
        json1.set("CurrentValues/long", String(LONGITUDE));
        json1.set("CurrentValues/UV", String(UVLEVELM));
        json1.set("CurrentValues/forecast", String(forecast));
        json1.set("CurrentValues/statusRain", String(statusRain));
        json1.set("CurrentValues/TimeMeassure", (String(epochTimeFormat)));
        json1.set("statusActuators/RELAY1", String(RELAY1));
        json1.set("statusActuators/RELAY2", String(RELAY2));
        json1.set("statusActuators/RELAY3", String(RELAY3));
        json1.set("statusActuators/RELAY4", String(RELAY4));


        Serial.println("------------------------------------");
        Serial.println("JSON Data");
        json1.toString(jsonStr, true);
        Serial.println(jsonStr);
        Serial.println("------------------------------------");

        Serial.println("------------------------------------");
        Serial.println("Set JSON test...");

        if (Firebase.RTDB.set(&fbdo, path.c_str(), &json1))
        {
          Serial.println("PASSED");
          Serial.println("PATH: " + fbdo.dataPath());
          Serial.println("TYPE: " + fbdo.dataType());
        }
        else {
          Serial.println("FAILED");
          Serial.println("REASON: " + fbdo.errorReason());
        }
      }
    } // FORS
  
}


void Firestore() {

  if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
  {
    dataMillis = millis();

    FirebaseJson js;


    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        String content = "";

        //We will create the nested document in the parent path "a0/b0/c0
        //a0 is the collection id, b0 is the document id in collection a0 and c0 is the collection id in the document b0.
        //and d? is the document id in the document collection id c0 which we will create.
        String documentPath = "SENSORS/" + USERS[i] + "/" + WHEATHER[j] + "/" + String(epochTime); //+String(String(now.unixtime()))

        js.set("fields/TemperatureDHT22/doubleValue", String(TEMPERATUREDHT22M).c_str());
        js.set("fields/HumidityDHT22/doubleValue", String(HUMIDITYDHT22M).c_str());
        js.set("fields/CO2/doubleValue", String(CO2M).c_str());
        js.set("fields/TVOC/doubleValue", String(TVOCM ).c_str());
        js.set("fields/PressureBMP180/doubleValue", String(PRESSUREBMP180M).c_str());
        js.set("fields/TemperatureBMP180/doubleValue", String(TEMPERATUREBMP180M).c_str());
        js.set("fields/LIGHT/doubleValue", String(LIGHTM).c_str());
        js.set("fields/battery/doubleValue", String(voltageM).c_str());
        js.set("fields/currentSolar/doubleValue", String(CURRENTM).c_str());
        js.set("fields/batteryLevel/doubleValue", String(batteryLevelM).c_str());
        js.set("fields/watts/doubleValue", String(WATTM).c_str());
        js.set("fields/DIRECTION/doubleValue", String(direccionM).c_str());
        js.set("fields/WIND/doubleValue", String(windM).c_str());
        js.set("fields/UV/doubleValue", String(UVLEVELM).c_str());
        js.set("fields/statusRain/stringValue", String(statusRain).c_str());
        js.set("fields/waterLevel/doubleValue", String(waterLevelM).c_str());
        js.set("fields/SHUNT/doubleValue", String(SHUNTM).c_str());
        js.set("fields/forecast/stringValue", String(forecast).c_str());
        js.set("fields/LAT/doubleValue", String(LATITUDE).c_str());
        js.set("fields/Altitude/doubleValue", String(ALTITUDEM).c_str());
        js.set("fields/LONGITUDE/doubleValue", String(LONGITUDE).c_str());
        js.set("fields/TIMESTAMP/stringValue", (String(epochTimeFormat)));
        js.set("fields/timestamp/doubleValue", (String(epochTime)));
        js.toString(content);

        Serial.println("------------------------------------");
        Serial.println("Create a document...");

        if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" , documentPath.c_str(), content.c_str()))
        {
          Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        }
        else
        {
          Serial.println(fbdo.errorReason());
        }
      }
    }
  }
}

// Initialize LORA
void initLora() {
  SPI.end();
  digitalWrite(SD_CHIP_SELECT_PIN, HIGH);
  digitalWrite(CS_LORA, HIGH);
  //LoRa.setSPIFrequency(8E6);
  //setup LoRa transceiver module
  LoRa.setPins(CS_LORA, RESET, DIO0);
  while (!LoRa.begin(866E6)) {
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(destination);
  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setSignalBandwidth(signalBandwidth);
  Serial.println("LoRa Initializing OK!");
  delay(1000);
  sendLoraMessage();
  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendLoraMessage() {

  String messageLORA =
    String(PRESSUREBMP180M) + "," +
    String(TEMPERATUREBMP180M) + "," +
    String(TEMPERATUREDHT22M) + "," +
    String(HUMIDITYDHT22M) + "," +
    String(CO2M) + "," +
    String(TVOCM) + "," +
    String(LIGHTM) + "," +
    String(UVLEVELM) + "," +
    String(direccionM) + "," +
    String(windM) + "," +
    String(waterLevelM) + "," +
    String(batteryLevelM) + "," +
    String(voltageM) + "," +
    String(WATTM) + "," +
    String(SOLARVOLTAGEM) + "," +
    String(SHUNTM ) + "," +
    String(CURRENTM) + "," +
    String(ALTITUDEM) + "," +
    String(statusRain) + "," +
    String(epochTime) + "," +
    String(epochTimeFormat);

  while (LoRa.beginPacket() == 0) {
    Serial.print("waiting for radio ... ");
    delay(100);
  }
  Serial.print("Sending packet non-blocking: ");
  // send in async / non-blocking mode
  LoRa.beginPacket();
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(messageLORA.length());        // add payload length
  LoRa.print(messageLORA);
  msgCount++;     // add payload  LoRa.print(messageLORA);
  LoRa.endPacket(true); // true = async / non-blocking mode
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("Message Lora sent: ");
  display.display();
  delay(TimeDisplay);
  delay(1000);
  LoRa.sleep();
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";                 // payload of packet

  while (LoRa.available()) {            // can't use readString() in callback, so
    incoming += (char)LoRa.read();      // add bytes one by one
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xF3) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}

bool wifiConnect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");
  int teller = 0;
  while ((WiFi.status() != WL_CONNECTED) && (teller <= 60))
  { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println('\n');
    Serial.println("Connection OK!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP32 to the computer

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("Connection OK!"));
    display.setCursor(0, 35);
    display.print("IP address:");
    display.setCursor(0, 45);
    display.print(WiFi.localIP());
    display.display();
    delay(TimeDisplay);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    epochTime = getTime();
    Serial.println("EPCHTIME:");
    Serial.print(epochTime);
    printLocalTime();
    return true;
  } else {
    return false;
  }
}


void initSD () {
  digitalWrite(SD_CHIP_SELECT_PIN, LOW);
  digitalWrite(CS_LORA, HIGH);
  SPI.end();
  // SD INIT
  if (!SD.begin(SD_CHIP_SELECT_PIN)) {
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/wheatherstation.txt");
  if (!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/wheatherstation.txt", "PRESSUREBMP180M,TEMPERATUREBMP180M,TEMPERATUREDHT22M,HUMIDITYDHT22M,CO2M,TVOCM,LIGHTM,UVLEVELM,direccionM,windM,waterLevelM,batteryLevelM,voltageM,WATTM,SOLARVOLTAGEM,SHUNTM,CURRENTM,ALTITUDEM,statusRain,Forecast, TimeMillis, Timestamp \r\n");
  }
  else {
    Serial.println("File already exists");
  }
  file.close();
}

// Write to the SD card
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  // creation of the message
  String messageSD = "\r\n" +
                     String(PRESSUREBMP180M) + "," +
                     String(TEMPERATUREBMP180M) + "," +
                     String(TEMPERATUREDHT22M) + "," +
                     String(HUMIDITYDHT22M) + "," +
                     String(CO2M) + "," +
                     String(TVOCM) + "," +
                     String(LIGHTM) + "," +
                     String(UVLEVELM) + "," +
                     String(direccionM) + "," +
                     String(windM) + "," +
                     String(waterLevelM) + "," +
                     String(batteryLevelM) + "," +
                     String(voltageM) + "," +
                     String(WATTM) + "," +
                     String(SOLARVOLTAGEM) + "," +
                     String(SHUNTM ) + "," +
                     String(CURRENTM) + "," +
                     String(ALTITUDEM) + "," +
                     statusRain + "," +
                     forecast + "," +
                     String(epochTime) + "," +
                     String(epochTimeFormat);

  if (file.print(messageSD)) {
    Serial.println("Message appended");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(1);
    display.println("Added message SD ");
    display.setTextSize(2);
    display.display();
    delay(TimeDisplay);
  } else {
    Serial.println("Append failed");
    display.clearDisplay();
    display.println("Append Failed");
    display.setTextSize(2);
    display.display();
    delay(TimeDisplay);
  }
  file.close();
  SD.end();
}


void checkConfig()
{
  Serial.print("Mode:                  ");
  switch (INA.getMode())
  {
    case INA226_MODE_POWER_DOWN:      Serial.println("Power-Down"); break;
    case INA226_MODE_SHUNT_TRIG:      Serial.println("Shunt Voltage, Triggered"); break;
    case INA226_MODE_BUS_TRIG:        Serial.println("Bus Voltage, Triggered"); break;
    case INA226_MODE_SHUNT_BUS_TRIG:  Serial.println("Shunt and Bus, Triggered"); break;
    case INA226_MODE_ADC_OFF:         Serial.println("ADC Off"); break;
    case INA226_MODE_SHUNT_CONT:      Serial.println("Shunt Voltage, Continuous"); break;
    case INA226_MODE_BUS_CONT:        Serial.println("Bus Voltage, Continuous"); break;
    case INA226_MODE_SHUNT_BUS_CONT:  Serial.println("Shunt and Bus, Continuous"); break;
    default: Serial.println("unknown");
  }

  Serial.print("Samples average:       ");
  switch (INA.getAverages())
  {
    case INA226_AVERAGES_1:           Serial.println("1 sample"); break;
    case INA226_AVERAGES_4:           Serial.println("4 samples"); break;
    case INA226_AVERAGES_16:          Serial.println("16 samples"); break;
    case INA226_AVERAGES_64:          Serial.println("64 samples"); break;
    case INA226_AVERAGES_128:         Serial.println("128 samples"); break;
    case INA226_AVERAGES_256:         Serial.println("256 samples"); break;
    case INA226_AVERAGES_512:         Serial.println("512 samples"); break;
    case INA226_AVERAGES_1024:        Serial.println("1024 samples"); break;
    default: Serial.println("unknown");
  }

  Serial.print("Bus conversion time:   ");
  switch (INA.getBusConversionTime())
  {
    case INA226_BUS_CONV_TIME_140US:  Serial.println("140uS"); break;
    case INA226_BUS_CONV_TIME_204US:  Serial.println("204uS"); break;
    case INA226_BUS_CONV_TIME_332US:  Serial.println("332uS"); break;
    case INA226_BUS_CONV_TIME_588US:  Serial.println("558uS"); break;
    case INA226_BUS_CONV_TIME_1100US: Serial.println("1.100ms"); break;
    case INA226_BUS_CONV_TIME_2116US: Serial.println("2.116ms"); break;
    case INA226_BUS_CONV_TIME_4156US: Serial.println("4.156ms"); break;
    case INA226_BUS_CONV_TIME_8244US: Serial.println("8.244ms"); break;
    default: Serial.println("unknown");
  }

  Serial.print("Shunt conversion time: ");
  switch (INA.getShuntConversionTime())
  {
    case INA226_SHUNT_CONV_TIME_140US:  Serial.println("140uS"); break;
    case INA226_SHUNT_CONV_TIME_204US:  Serial.println("204uS"); break;
    case INA226_SHUNT_CONV_TIME_332US:  Serial.println("332uS"); break;
    case INA226_SHUNT_CONV_TIME_588US:  Serial.println("558uS"); break;
    case INA226_SHUNT_CONV_TIME_1100US: Serial.println("1.100ms"); break;
    case INA226_SHUNT_CONV_TIME_2116US: Serial.println("2.116ms"); break;
    case INA226_SHUNT_CONV_TIME_4156US: Serial.println("4.156ms"); break;
    case INA226_SHUNT_CONV_TIME_8244US: Serial.println("8.244ms"); break;
    default: Serial.println("unknown");
  }

  Serial.print("Max possible current:  ");
  Serial.print(INA.getMaxPossibleCurrent());
  Serial.println(" A");

  Serial.print("Max current:           ");
  Serial.print(INA.getMaxCurrent());
  Serial.println(" A");

  Serial.print("Max shunt voltage:     ");
  Serial.print(INA.getMaxShuntVoltage());
  Serial.println(" V");

  Serial.print("Max power:             ");
  Serial.print(INA.getMaxPower());
  Serial.println(" W");
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  strftime(epochTimeFormat, 32, "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay, 10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}





///////////////////////////////////////////////////////////// DISPLAYSS /////////////////////////////////////////////////////


void drawProgressbar(int x, int y, int width, int height, int progress)
{
  if (progress > 100) {
    progress = 100;
  } else if (progress < 0) {
    progress = 0;
  }
  int bar = ((int)(width - 1) / 100) * progress;
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  display.fillRect(x + 2, y + 2, bar , height - 2, SSD1306_WHITE); // initailize the graphics fillRect(int x, int y, int width, int height)
}


void displayAll() {

  display.clearDisplay();
  switch (5) {
    case 1:
      // SOLO WIFI
      display.drawBitmap(112, 0, wifi , 10, 10, WHITE);
      display.drawBitmap(96, 0, battery_alert, 10, 10, WHITE);
      break;
    case 2:
      // SOLO LORA
      display.drawBitmap(112, 0, LORA, 10, 10, WHITE);
      display.drawBitmap(96, 0, battery_alert, 10, 10, WHITE);
      break;
    case 3:
      // SOLO BLUETOOTH
      display.drawBitmap(112, 0, bluetooth, 10, 10, WHITE);
      display.drawBitmap(96, 0, battery_alert, 10, 10, WHITE);
      break;
    case 4:
      // WIFI+LORA
      display.drawBitmap(112, 0, LORA, 10, 10, WHITE);
      display.drawBitmap(96, 0, wifi , 10, 10, WHITE);
      display.drawBitmap(80, 0, battery_alert, 10, 10, WHITE);
      break;
    case 5:
      // WIFI+LORA+BLUETOOTH
      display.drawBitmap(112, 0, LORA, 10, 10, WHITE);
      display.drawBitmap(96, 0, wifi , 10, 10, WHITE);
      display.drawBitmap(80, 0, bluetooth, 10, 10, WHITE);
      display.drawBitmap(64, 0, battery_alert, 10, 10, WHITE);
      break;
    default:
      display.drawBitmap(80, 0, battery_alert, 10, 10, WHITE);
  }
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("Light: ");
  display.setTextSize(2);
  display.print(LIGHTM);
  display.println(" lx");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("UVLEVEL: ");
  display.println(UVLEVELM);
  display.setTextSize(2);
  if (UVLEVELM >= 11) {
    display.print(" EXTREME");
  } else if ((UVLEVELM >= 8) && (UVLEVELM <= 10)) {
    display.print("VERY HIGH");
  } else if ((UVLEVELM >= 6) && (UVLEVELM <= 7)) {
    display.print(" HIGH");
  } else if ((UVLEVELM >= 3) && (UVLEVELM <= 5)) {
    display.print(" MODERATE");
  } else {
    display.print(" LOW");
  }
  display.display();
  delay(10000);
  ///////////////////////////////////////////////////////////////////// BMP180
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("Pressure: ");
  display.setTextSize(2);
  display.print(PRESSUREBMP180M);
  display.print(" Pa");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("Altitude: ");
  display.setTextSize(2);
  display.print(ALTITUDEM);
  display.print(" m");
  display.display();
  delay(TimeDisplay);
  ///////////////////////////////////////////////////////////////////// DHT22
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("Temperature: ");
  display.setTextSize(2);
  display.print(TEMPERATUREDHT22M);
  display.println(" C");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("Humidity air: ");
  display.setTextSize(2);
  display.print(HUMIDITYDHT22M);
  display.print(" %");
  display.display();
  delay(TimeDisplay);
  ///////////////////////////////////////////////////////////////////// CCS811
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("eCO2: ");
  display.setTextSize(2);
  display.print(CO2M);
  display.println(" ppm");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("TVOC: ");
  display.setTextSize(2);
  display.print(TVOCM );
  display.println(" ppb");
  display.setTextSize(1);
  display.display();
  delay(TimeDisplay);
  ///////////////////////////////////////////////////////////////////// INA
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("WATTS: ");
  display.setTextSize(2);
  display.print(WATTM);
  display.println(" mW");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("VOLTAGE: ");
  display.setTextSize(2);
  display.print(SOLARVOLTAGEM);
  display.println(" mV");
  display.display();
  delay(TimeDisplay);
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("CURRENT: ");
  display.setTextSize(2);
  display.print(CURRENTM);
  display.println(" mA");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("SHUNT: ");
  display.setTextSize(2);
  display.print(SHUNTM);
  display.println(" mV");
  display.display();
  delay(TimeDisplay);

  ///////////////////////////////////////////////////////////////////// BATTERY LEVEL

  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("BATTERY: ");
  display.setTextSize(2);
  display.print(voltageM);
  display.println(" V");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("PORCENTAGE:");
  display.setTextSize(2);
  display.print(batteryLevelM);
  display.print(" %");
  display.setTextSize(1);
  display.display();
  delay(TimeDisplay);

  ///////////////////////////////////////////////////////////////////// HMC5883L
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("DIRECTION: ");
  display.setTextSize(2);
  display.print(direccionM);
  display.println(" DEG");
  display.display();
  delay(TimeDisplay);

    ///////////////////////////////////////////////////////////////////// BATTERY LEVEL

  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("SURFACE: ");
  display.setTextSize(2);
  display.print(statusRain);
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("RAIN L/M2 LAST 3 HOUR:");
  display.setTextSize(2);
  display.print(waterLevelM);
  display.setTextSize(1);
  display.display();
  delay(TimeDisplay);

  
}
