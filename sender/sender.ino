#include <ESP8266WiFi.h>
#include "mpu9250.h"

bfs::Mpu9250 imu(&Wire, 0x68);
int status;

const char *ssid = "ritvik";
const char *password = "Ritvikm01@";

float acc_x = 0.0;
float acc_y = 0.0;
float acc_z = 0.0;
float roll = 0.0;
float pitch = 0.0;

void setup() {
  Serial.begin(115200);
  delay(10);
  Wire.begin();
  Wire.setClock(400000);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.begin(115200);

  while(!Serial) {}
  /* Start communication */
  if (!imu.Begin()) {
    Serial.println("IMU initialization unsuccessful");
    while(1) {}
  }
}

void loop() {
  if (imu.Read()){
    acc_x = float(imu.accel_x_mps2());
    acc_y = float(imu.accel_y_mps2());
    acc_z = float(imu.accel_z_mps2());

    roll = atan2(acc_y , sqrt(acc_x*acc_x + acc_z*acc_z)) * 57.3;
    pitch = atan2((- acc_x) , sqrt(acc_y * acc_y + acc_z * acc_z)) * 57.3;
//    Serial.println(roll);
//    Serial.println(pitch);
  }



  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char *host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/data/";

  String url_roll = url;
  url_roll += "?roll=";
  url_roll += roll;

  String url_pitch = url;
  url_pitch += "?pitch=";
  url_pitch += pitch;


  client.print(String("GET ") + url_roll + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  client.print(String("GET ") + url_pitch + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

//  Serial.println();
//  Serial.println("Closing connection");
//  Serial.println();
//  Serial.println();
//  Serial.println();

  delay(5);
}
