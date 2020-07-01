/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

byte address = 0xBB;

void setup() {
  //initialize Serial Monitor
  Serial.begin(57600);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
//  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
//    Serial.println(".");
    Serial.println("Starting LoRa failed!");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
//  LoRa.setTxPower(15);
  LoRa.setSpreadingFactor(7);
  Serial.println("LoRa Initializing OK!");
}

String payload = "node0";

void sendMsg(String outMsg, int counter){
   //Send LoRa packet to receiver
  LoRa.beginPacket();
//  LoRa.write(address);
  LoRa.write(outMsg.length());
  LoRa.print(outMsg);
  LoRa.print(",");
  LoRa.print(counter);
  LoRa.endPacket();
};

int counter = 0;
void loop() {
  Serial.print("Sending packet: ");
//  Serial.println(counter);
  counter++;
  sendMsg(payload,counter);
  
  Serial.println(payload);
  Serial.println(counter);
  delay(1000);
}
