
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>


const char* ssid = "send"; // 替换为你的WiFi名称
const char* password = "**********"; // 替换为你的WiFi密码

unsigned int localPort = 8888; // 本地端口号，与发送方保持一致


AsyncWebServer server(80);




WiFiUDP udp;
char incomingPacket[16]; // 存储接收到的数据


int gpioCount;

uint8_t gpiodata[15];

uint8_t gpios[] = {23, 22, 21, 19, 18, 17, 4, 15, 26, 27, 14, 13, 25, 33, 32};


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password); // 将ESP32设置为AP模式
  
  IPAddress localIP = WiFi.softAPIP(); // 获取分配给ESP32的IP地址
  Serial.print("AP IP address: ");
  Serial.println(localIP);
/*

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
*/
  udp.begin(localPort);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "jieshou.");
  });

  AsyncElegantOTA.begin(&server);  // Start ElegantOTA
  server.begin();



gpioCount = sizeof(gpios)/sizeof(uint8_t);

  pinMode(23, OUTPUT );
  pinMode(22, OUTPUT );
  pinMode(21, OUTPUT );
  pinMode(19, OUTPUT );
  pinMode(18, OUTPUT );
  pinMode(17, OUTPUT );
  pinMode(4, OUTPUT );
  pinMode(15, OUTPUT );
  pinMode(26, OUTPUT );
  pinMode(27, OUTPUT );
  pinMode(14, OUTPUT );  
  pinMode(13, OUTPUT );
  pinMode(25, OUTPUT );
  pinMode(33, OUTPUT );
  pinMode(32, OUTPUT );
  pinMode(35, OUTPUT );






}

void loop() {
  int packetSize = udp.parsePacket(); // 检查是否有数据包到达
  if (packetSize) {
    // 读取数据并将其存储在incomingPacket数组中
    int len = udp.read(incomingPacket, 15);
    if (len > 0) {
      incomingPacket[len] = 0;
    }

    // 将接收到的数据解析成15个开关量，并打印它们的值
    bool states[15];
    for(int i = 0; i < 15; i++) {
      states[i] = incomingPacket[i] == '1';

        if( states[i] == 1){

              digitalWrite (gpios[i], LOW);

        }else if(states[i] == 0){
                  digitalWrite (gpios[i], HIGH); 
              }    

      Serial.print(states[i]);
      Serial.print(" ");
    }
    Serial.println();
  }

  delay(10);
}
