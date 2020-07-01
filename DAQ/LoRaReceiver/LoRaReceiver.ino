#include <SPI.h>
#include <LoRa.h>
#include <Math.h>
// #define txPower = 17

#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>
// Set pins:  CE, IO,CLK
int rands = random(1,5);
DS1302RTC RTC(5,4,3);


void setup() {
  Serial.begin(57600);
  while (!Serial);

  Serial.println("LoRa Receiver at freq");
  Serial.println(915E6);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  } 
 LoRa.setSpreadingFactor(7);           // ranges from 6-12,default 7 see API docs
  // LoRa.setTxPower(17);            //default are 17
  Serial.println("LoRa init succeeded.");
  configTime();

}

void configTime(){
  Serial.println("RTC module activated");
  Serial.println();
  delay(500);
  
  if (RTC.haltRTC()) {
    Serial.println("The DS1302 is stopped.  Please run the SetTime");
    Serial.println("example to initialize the time and begin running.");
    Serial.println();
  }
  if (!RTC.writeEN()) {
    Serial.println("The DS1302 is write protected. This normal.");
    Serial.println();
  }
  
  delay(5000);
}

String accPath2 = "2"; //node value for path choosing

/*Validating node*/
int accValueFor1 = 2;
int accValueFor3 = 2;
int accValueFor5 = 2;
/**/

int myPathValue = 2;
String nodeId = "01";

double myPosX = -6.9765749;
double myPosY = 107.6310007;

double myDistance = 30;

void sendThem(String payload, int payloadRSSI){
  
  String timeUnix = "";

  tmElements_t tm;
  
  Serial.print("UNIX Time: ");
  timeUnix = RTC.get();
  Serial.println(timeUnix);

  // if (! RTC.read(tm)) {
  //   Serial.println("  Time = ");
    
  // } else {
  
  if (RTC.read(tm)) {
    Serial.println("DS1302 read error!  Please check the circuitry.");
    Serial.println();
    delay(9000);
  }
  
  // Wait one second before repeating :)
  // delay (1000);

  LoRa.beginPacket();                   // start packet
//  LoRa.print("node1_");
//  LoRa.print("node2_");
  LoRa.print(nodeId);            // add payload
  LoRa.print(",");  
  LoRa.print(payload);              // add payload
  LoRa.print(",");  
  LoRa.print(payloadRSSI);               // add payload
  LoRa.print(",");    
  LoRa.print(myPosX);               // add payload
  LoRa.print(","); 
  LoRa.print(myPosY);               // add payload
  LoRa.print(",");           // add payload// add payload
  LoRa.print(timeUnix);// add payload
  LoRa.print(",");
  LoRa.print(myPathValue);
  // LoRa.print(",");
  LoRa.endPacket();    
};


/*
Todo
1. Set rule untuk jaringan mash berdasarkan rssi dan hop terdekat
2. masukin data rtc kedalam payload
3. Tau tempat uji coba agar dapat menentukan path value
*/

// void rules(String rssiValue, String pathValue){
//   if (rssiValue < "-90"){
//     /* code */
//     if (pathValue == )
//   }
  
  
// };

void msgCome(int packetSize){
  if(packetSize == 0) return;   
  byte msgLength = LoRa.read();
  String nodeComeId = "";
  String msgPayload = "";
  int payloadRSSI ;

  // String payloadRSSI = "";
    // received a packet
  Serial.println("Received packet!");

    // read packet
  while (LoRa.available()) {
    // nodeComeId +=  (char)LoRa.read();
    msgPayload += (char)LoRa.read();
    payloadRSSI = LoRa.packetRssi();   
  };

  int distRssi = LoRa.packetRssi();
  Serial.println(distRssi);
  if(distRssi > -25 && distRssi < -110){
    Serial.println("4 Meter");
  }

  if (msgLength < 11) {   // check length for error
    Serial.println("Gotcha");
    // Serial.println("ID: "+nodeComeId);
    Serial.print("Message RSSI: ");
    Serial.println(payloadRSSI);
    Serial.println("Message: " + msgPayload);
    sendThem(msgPayload, payloadRSSI);
//    Serial.print("Sending to everyone with payload: node1_");
//    Serial.print("Sending to everyone with payload: node4_");
    Serial.print("Sending to everyone with payload: "+ nodeId);
    Serial.print("," + msgPayload);
    Serial.print(",");
    Serial.println(payloadRSSI);
    // return;                             // skip rest of function
  }else{
    Serial.println("not match data");
    LoRa.print("Not match data");
    return;
  }

  
}

// int distRssi = LoRa.packetRssi();

// //standard mengambil jarak dalam meter dari RSSI
//  double getDistance(int rssi, int txPower) {
//     /*
//      * RSSI = TxPower - 10 * n * lg(d)
//      * n = 2 (in free space)
//      * 
//      * d = 10 ^ ((TxPower - RSSI) / (10 * n))
//      */
//     int d = 10 ^((txPower - payRSSI) / (10*2));
 
//     return d;
// };

// void dapatJarak(int payRSSI, int txPower){
//   int d = 10 ^((txPower - payRSSI) / (10*2));

//   int paRSSI = txPower - (10 * 2 *log(d));

//   if(payRSSI < -110 && payRSSI > -40){
//     Serial.println("5 Meter");
//   }
// }

void loop() {
  // try to parse packet
  
    // byte sender = LoRa.read();
    // print RSSI of packet
    // Serial.print("RSSI ");
    // Serial.println(LoRa.packetRssi());
    // Serial.println("Received from: 0x" + String(sender, HEX));
  // Serial.println(distRssi);  
  msgCome(LoRa.parsePacket());
}

void print2digits(int number) {
  if (number >= 0 && number < 10)
    Serial.write('0');
  Serial.print(number);
}
