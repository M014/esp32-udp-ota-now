#include <WiFi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>



const char* ssid = "send"; // 替换为你的WiFi名称
const char* password = "**********"; // 替换为你的WiFi密码

unsigned int localPort = 8888; // 本地端口号，任意选择

IPAddress receiverIP(192, 168, 4, 1); // 接收方的IP地址，与接收端一致
unsigned int receiverPort = 8888; // 接收方的端口号，与接收端一致

AsyncWebServer server(80);


WiFiUDP udp;
uint8_t gpios[] = {23, 22, 21, 19, 18, 17, 4, 15, 26, 27, 14, 13, 25, 33, 32};
void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(localPort);
  /*
  WiFi.softAP(ssid, password); // 将ESP32设置为AP模式
  
  IPAddress localIP = WiFi.softAPIP(); // 获取分配给ESP32的IP地址
  Serial.print("AP IP address: ");
  Serial.println(localIP);

  udp.begin(localPort);
*/
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "fashe.");
  });

  AsyncElegantOTA.begin(&server);  // Start ElegantOTA
  server.begin();



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

}

void loop() {
  static bool states[15] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}; // 存储15个开关状态的数组
  // 假设你已经连接了十五个开关，通过digitalRead来获取它们的状态，并将这些状态存储到states数组中。
for(int i=0; i<15; i++){

   states[i] = digitalRead(gpios[i]);
   //Serial.print(gpiodata[i]);

  }
  String data = ""; // 将所有开关量连接在一起以便发送

  for(int i = 0; i < 15; i++) {
    data += String(states[i]);
  }
  
  udp.beginPacket(receiverIP, receiverPort); // 设置数据包的目标IP和端口
  udp.print(data); // 发送数据
  udp.endPacket();

  delay(100); // 等待一秒钟并重新发送数据
}
