// Adafruit IO Subscription Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/
#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

int blueTx=7;   //Tx (보내는핀 설정)at
int blueRx=8;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed(""); //피드 적기

void setup() {
  
  pinMode(D1, OUTPUT);  //출력핀 설정 | Output Pin Settings
  pinMode(D2, OUTPUT);  //출력핀 설정 | Output Pin Settings
  pinMode(D3, OUTPUT);  //출력핀 설정 | Output Pin Settings
  
  // start the serial connection
  Serial.begin(115200); //시리얼 모니터 통신속도 | Serial monitor baud rate
  mySerial.begin(9600); //블루투스 시리얼 통신속도 | Bluetooth serial communication speed
  
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // start MQTT connection to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  counter->onMessage(handleMessage);

  // wait for an MQTT connection
  // NOTE: when blending the HTTP and MQTT API, always use the mqttStatus
  // method to check on MQTT connection status specifically

  /*************서버 접속 중 | Connecting to server************/
  while(io.mqttStatus() < AIO_CONNECTED) {
    
    digitalWrite(D1, LOW);  //RED_LED_ON
    digitalWrite(D2, HIGH); //YELLOW_LED_OFF
    digitalWrite(D3, HIGH); //BLUE_LED_OFF
    Serial.print(".");
    delay(500);             //500ms
    digitalWrite(D2, LOW);  //YELLOW_LED_ON
    Serial.print(".");
    delay(500);             //500ms
  }

  // Because Adafruit IO doesn't support the MQTT retain flag, we can use the
  // get() function to ask IO to resend the last value for this feed to just
  // this MQTT client after the io client is connected.
  counter->get();

  // we are connected

  /**********서버 접속완료 | Server connection complete***********/
  digitalWrite(D1, HIGH); //RED_LED_OFF
  digitalWrite(D2, HIGH); //YELLOW_LED_OFF
  digitalWrite(D3, LOW);  //BLUE_LED_ON
  
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // Because this sketch isn't publishing, we don't need
  // a delay() in the main program loop.

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

  int state = data->toInt();
  int flag1, flag2, flag3;

  
  if(state == 1 && flag1 == 0){
    //1번 로봇에 블루투스 연결하기
    flag1 = 1;
    /**********AT 통신 적기**********/
    
  }
  else {
    flag1 = 0;
  }
  if(state == 2 && flag2){
    //2번 로봇에 블루투스 연결하기
   flag2 = 1;
    /**********AT 통신 적기**********/
  }
  else {
    flag2 = 0;
  }

  if(state == 3 && flag3 == 0){
    //블루투스 연결해제
    flag3 = 1;
    /**********AT 통신 적기**********/
  }
  else {
    flag3 = 0;
  }
}
