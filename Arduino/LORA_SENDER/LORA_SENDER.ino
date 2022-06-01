#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//LORA
#define CS_LORA 5
#define RESET 14
#define DIO0 2
#define spreadingFactor 10
#define codingRateDenominator 5
#define signalBandwidth 500E3

int counter = 0;


void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  //setup LoRa transceiver module
  LoRa.setPins(CS_LORA, RESET, DIO0);
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  //replace the LoRa.begin(---E-) argument with your location's frequency

  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  LoRa.setSpreadingFactor(spreadingFactor);
  LoRa.setCodingRate4(codingRateDenominator);
  LoRa.setSignalBandwidth(signalBandwidth);
  LoRa.onTxDone(onTxDone);
  Serial.println("LoRa Initializing OK!");


  // INITIALIZE OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  } else {

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.println(F("Starting..."));
    display.display();
    delay(2000);
  }


  display.clearDisplay(); //for Clearing the display
  // LoRa.sleep();
}

void loop() {
  if (runEvery(5000)) { // repeat every 5000 millis

    Serial.print("Sending packet non-blocking: ");
    Serial.println(counter);

    // send in async / non-blocking mode
    LoRa.beginPacket();
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket(true); // true = async / non-blocking mode
    counter++;
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(1);
    display.println("Enviado: ");
    display.print(counter);
    display.display();
  }
}

void onTxDone() {
  Serial.println("TxDone");
}

boolean runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}
