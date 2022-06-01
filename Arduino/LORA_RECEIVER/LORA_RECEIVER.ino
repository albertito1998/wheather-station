

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

//define the pins used by the transceiver module
//LORA
#define CS_LORA 5
#define RESET 14
#define DIO0 2
#define spreadingFactor 10
#define codingRateDenominator 5
#define signalBandwidth 500E3

String LoRaData = "";

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
  // register the receive callback
 // LoRa.onReceive(onReceive);

  // put the radio into receive mode
 // LoRa.receive();
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
}

void loop() {
   // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      LoRaData=(char)LoRa.read();
      Serial.print(LoRaData);
    }

  // print Information of quality
  Serial.print("RSSI (dBm) -->");
  Serial.println(LoRa.packetRssi());
  Serial.print(" SNR dB.-->");
  Serial.println(LoRa.packetSnr());
  Serial.print("F error :");
  Serial.println(LoRa.packetFrequencyError());
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("message: ");
  display.setTextSize(2);
  display.print(LoRaData);
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("FE:");
  display.setTextSize(2);
  display.print(LoRa.packetFrequencyError());
  display.println(" Hz");
  display.setTextSize(1);
  display.display();

/*
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("RSSI: ");
  display.setTextSize(2);
  display.print(LoRa.packetRssi());
  display.println(" dBm");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("SNR:");
  display.setTextSize(2);
  display.print(LoRa.packetSnr());
  display.println(" dB");
  display.setTextSize(1);
  display.display();
  delay(1000); */
  }
}



///////////////////////////////////// INTERRUPT /////////////////////////////////
void onReceive(int packetSize) {
    // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
      LoRaData = (char)LoRa.read();
      Serial.println(LoRaData);
  }

  // print Information of quality
  Serial.print("RSSI (dBm) -->");
  Serial.println(LoRa.packetRssi());
  Serial.print(" SNR dB.-->");
  Serial.println(LoRa.packetSnr());
  Serial.print("F error :");
  Serial.println(LoRa.packetFrequencyError());
  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("message: ");
  display.setTextSize(2);
  display.print(LoRaData);
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("FE:");
  display.setTextSize(2);
  display.print(LoRa.packetFrequencyError());
  display.println(" Hz");
  display.setTextSize(1);
  display.display();
  delay(1000);


  display.clearDisplay();
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println("RSSI: ");
  display.setTextSize(2);
  display.print(LoRa.packetRssi());
  display.println(" dBm");
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.println("SNR:");
  display.setTextSize(2);
  display.print(LoRa.packetSnr());
  display.println(" dB");
  display.setTextSize(1);
  display.display();
  delay(1000);

}
