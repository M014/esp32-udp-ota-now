#include <WiFi.h>
#include <esp_now.h>


int gpioCount;

uint8_t gpiodata[15];

uint8_t gpios[] = {23, 22, 21, 19, 18, 17, 4, 15, 26, 27, 14, 13, 25, 33, 32};

uint8_t broadcastAddress[] = {0xa4, 0xe5, 0x7c, 0x7f, 0x1a, 0x38};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//Serial.print("Status: ");
//Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");


for(int i=0; i<15; i++){

   gpiodata[i] = digitalRead(gpios[i]);
   Serial.print(gpiodata[i]);

  }



}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  //初始化now
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    ESP.restart();
    delay(10);
  }
  // 设置发送数据回调函数
 esp_now_register_send_cb(OnDataSent);


  // 绑定数据接收端
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // 检查设备是否配对成功
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    ESP.restart();
    delay(10000);
    return;
  }






gpioCount = sizeof(gpios)/sizeof(uint8_t);

  pinMode(23, INPUT_PULLUP );
  pinMode(22, INPUT_PULLUP );
  pinMode(21, INPUT_PULLUP );
  pinMode(19, INPUT_PULLUP );
  pinMode(18, INPUT_PULLUP );
  pinMode(17, INPUT_PULLUP );
  pinMode(4, INPUT_PULLUP );
  pinMode(15, INPUT_PULLUP );
  pinMode(26, INPUT_PULLUP );
  pinMode(27, INPUT_PULLUP );
  pinMode(14, INPUT_PULLUP );
  pinMode(13, INPUT_PULLUP );  
  pinMode(25, INPUT_PULLUP );
  pinMode(33, INPUT_PULLUP );
  pinMode(32, INPUT_PULLUP );
  pinMode(35, INPUT_PULLUP );




}


void loop() {

 esp_now_send(broadcastAddress, (uint8_t *) &gpiodata, sizeof(gpiodata));

 delay(100);
}






