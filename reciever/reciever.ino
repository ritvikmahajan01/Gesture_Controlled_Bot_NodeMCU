#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "ritvik";
const char *password = "Ritvikm01@";

int pwm1 = 14;
int dir1 = 12;
int pwm2 = 13;
int dir2 = 9;
double roll = 0.0;
double pitch = 0.0;
double temproll = 0.0;
double temppitch = 0.0;
double in_roll = 0.0;
double in_pitch = 0.0;
int counter = 0;


ESP8266WebServer server(80);

void handleSentVar() {
//  Serial.println("handleSentVar function called...");


  if (server.hasArg("roll")){
    temproll = server.arg("roll").toFloat();
    server.send(200, "text/html", "Data received");
  }

  if (server.hasArg("pitch")){
    temppitch = server.arg("pitch").toFloat();
    server.send(200, "text/html", "Data received");
  }

  roll = temproll-in_roll;
  pitch = temppitch-in_pitch;
  Serial.print("Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.println(roll);
  if (counter < 20){
    in_pitch = temppitch;
    in_roll = temproll;
    counter++;
    Serial.println("Calibrating");
  }
  
  if ((pitch > 5.00) && (abs(roll) < 5.0)){
  analogWrite(pwm1, 255); //left
  digitalWrite(dir1, HIGH);
  analogWrite(pwm2, 110); //right
  digitalWrite(dir2, LOW);
  }
  else if ((pitch < -5.00) && (abs(roll) < 5.0)){
  analogWrite(pwm1, 255); //left
  digitalWrite(dir1, LOW);
  analogWrite(pwm2, 110); //right
  digitalWrite(dir2, HIGH);
  }
  else if ((roll < -5.00) && (abs(pitch) < 5.0)){
  analogWrite(pwm1, 255); //left
  digitalWrite(dir1, LOW);
  analogWrite(pwm2, 110); //right
  digitalWrite(dir2, LOW);
  }

   else if ((roll > 5.00) && (abs(pitch) < 5.0)){
  analogWrite(pwm1, 255); //left
  digitalWrite(dir1, HIGH);
  analogWrite(pwm2, 110); //right
  digitalWrite(dir2, HIGH);
  }
  else{
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
  }
  
}

void setup() {
  delay(1);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  pinMode(14, OUTPUT); //d5,PWM1
  pinMode(12, OUTPUT); //d6, dir1
  pinMode(13,OUTPUT); //d7,PWM2
  pinMode(9,OUTPUT);//sd2, dir2
  digitalWrite(pwm1, LOW);
  digitalWrite(pwm2, LOW);
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/data/", HTTP_GET, handleSentVar); // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();
}
