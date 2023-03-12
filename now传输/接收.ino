#include <esp_now.h>
#include <WiFi.h>

int gpioCount;

uint8_t gpiodata[15];

uint8_t gpios[] = {23, 22, 21, 19, 18, 17, 4, 15, 26, 27, 14, 13, 25, 33, 32};

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&gpiodata, incomingData, sizeof(gpiodata));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.println();

    for(int i=0; i<gpioCount; i++){
        if( gpiodata[i] == 1){

         digitalWrite (gpios[i], LOW);

        }else if(gpiodata[i] == 0){
          digitalWrite (gpios[i], HIGH); 
        }    

    
  }


}



 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

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

}