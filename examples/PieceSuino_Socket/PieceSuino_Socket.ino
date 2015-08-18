#include "esp8266.h"
#define SSID        "Your SSID"
#define PASSWORD    "Your Password"
esp8266 wifi(Serial1);
uint32_t len;

void setup(){

  Serial.begin(9600);
  Serial1.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  wifi.begin();//初始化
  wifi.getVersion();//取得WiFi韌體版本
  wifi.reset();//重啟WiFi
  wifi.setWifiMode(1);//將WiFi模組設定為Station模式
  wifi.connToWifi(SSID,PASSWORD);//連接網路
  wifi.getIP();//取得IP
  wifi.enableMUX();//開啟多人連線模式
  wifi.createTCPServer(8090);//開啟TCP Server

  pinMode(13, OUTPUT);
}

void loop(){

  //取得socket client訊息並回傳
  //------------------------------------------
  len = wifi.recv();
  if(len){
    char recvData[len-1];
    for (uint32_t i = 0; i < len; i++) {
      Serial.print("Recive ");
      Serial.print(i);
      Serial.print(" Byte: ");
      Serial.print(wifi.MessageBuffer[i]); 
      Serial.print("  From: ");
      Serial.println(wifi.client_id);
      recvData[i] = wifi.MessageBuffer[i];
    }
    wifi.Send(wifi.client_id , recvData , len);
  }
  //------------------------------------------

}

