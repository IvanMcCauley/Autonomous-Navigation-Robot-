

////Primary MSP432 Code///

#ifndef __CC3200R1M1RGC__
//#define BUFSIZE 1024
#include <SPI.h>
#endif
#include <WiFi.h>
#define NOTE_B0  31

// group password is: kngr5328
String position = ("0");
char ssid[] = "NETGEAR63";
char password[] = "littlecello367";
//IPAddress server = (3,250,38,184);
char server[] = "3.250.38.184";
int port = 8000;
int destination;
int CurrentPosition;
int motor1PWM = 39; // P2.6
int motor1Phase = 40; // P2.7
int motor2PWM = 38; //2.4
int motor2Phase = 34; // 5.6
int motor3PWM = 32; 
int motor3Phase = 11; 

int beep[] = {
  NOTE_B0, NOTE_B0,NOTE_B0, NOTE_B0, NOTE_B0, NOTE_B0, NOTE_B0, NOTE_B0};

int SloMoSound[] = {
  3,3,3,3,3,3,3,3 };

  int SnailSound[] = {
  5,5,5,5,5,5,5,5
  };

//int destination=0;

String target;
WiFiClient client;

void setup() {
Serial.begin(9600);
delay(1000);
Serial.print("Connecting to network: ");
Serial.print(ssid);
Serial.flush();
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
Serial.flush();
delay(300);
}
Serial.println("Connected");
Serial.print("Obtaining IP address");
Serial.flush();
while (WiFi.localIP() == INADDR_NONE) {
Serial.print(".");
Serial.flush();
delay(300);
}
Serial.println();
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());

}

void SendMessage(){
// post body
String postBody("position=");
postBody += position;
// send post request and headers

client.println("POST /api/arrived/kngr5328 HTTP/1.1");
client.println("Content-Type: application/x-www-form-urlencoded");

client.print("Content-Length: ");
client.println(postBody.length());
client.println();

// send post body
client.println(postBody);
Serial.println("SendMessage Success");

}


#define BUFSIZE 512
  String readResponse() {
  char buffer[BUFSIZE];
  memset(buffer, 0, BUFSIZE);
  client.readBytes(buffer, BUFSIZE);
  String response(buffer);
  Serial.println("readResponse Success");
  Serial.println(response);
  return response;
}
int getStatusCode(String& response) {
String code = response.substring(9, 12);
Serial.print("GetStatusCode Success -->> ");
Serial.println(code);
return code.toInt();
}
String getResponseBody(String& response) {
int split = response.indexOf("\r\n\r\n");
String body = response.substring(split+4,response.length());
body.trim();
Serial.println("Going to the next position -->>  " + body);
return body;
}

 String RecResponse() {
  int destination; 
  // read response
  String response = readResponse();
  String body;

  // get status code
  int statusCode =  200 ;//getStatusCode(response);
  Serial.println(statusCode);
  if (statusCode == 200) {
    // success, read body
    Serial.println("Checking Status Code");
    String body = getResponseBody(response);
Serial.println("RecResponse Success -> ");

    // check if at final destination
    if (!body.equals("Finished")) {
      destination = body.toInt();
    }
  }
  return body;
}

bool connect(){
  if (!client.connect(server,port)){
    Serial.println("Error Connecting to Server");
    return false;
  } else{
    Serial.println("Connected");
  }
  return true;
}

//Start of zero to destination
void Zero_to_One(){
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //at A turn left
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);;
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
  
  }


//zero to two function
void Zero_to_Two(){
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  }
  DriveForward();
  delay(200);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
  }
}

//zero to three function
void Zero_to_Three(){
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
  position = destination;
  //might need to do a custom Stop function after Uturn
  }
}

//zero to four function
void Zero_to_Four(){
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  }
  Uturn();
  delay(1300);
  Stop();
  delay(200);
  Steer();
  Stop();
  position = destination;
  delay(1000);
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
  }


//zero to five function
void Zero_to_Five(){
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);;
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
   Stop();
   delay(500);
   JunctionFive();
  }
  position = destination;
}

 
 //Start of one to destination
void One_to_Zero(){
  DriveForward();
  delay(200);
  Steer();
  //at B turn left
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);;
  }
  Steer();
  //drive through 4
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //Stop at 0
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}

//one to two function
void One_to_Two(){
  DriveForward();
  delay(200);
  Steer();
  //at B turn right
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);;
  }
  Steer();
  //drive through 3
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //Stop at 2
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}
//one to three function
void One_to_Three(){
  DriveForward();
  delay(200);
  Steer();
  //at B turn right
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);;
  }
  Steer();
  //Stop at 3
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}
//one to four function
void One_to_Four(){
  DriveForward();
  delay(200);
  Steer();
  //at B turn left
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);;
  }
  Steer();
  //Stop at 4
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}

void One_to_Five(){
  DriveForward();
  delay(200);
  Steer();
  //drive through b
 if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  JunctionFive();
 }
  position = destination;
 }



//Start of two to destination functions
//two to zero function
void Two_to_Zero() {
  DriveForward();
  delay(200);
  Steer();
  //at A go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(1000);
  position = destination;
  }
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
}

//two to one function
void Two_to_One() {
  DriveForward();
  delay(200);
  Steer();
  //at A go right
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
 
}

//two to three function
void Two_to_Three() {
  Uturn();
  delay(1300);
  Steer();
  //until it reaches 3
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(500);
  position = destination;
  }
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
}

//two to four function
void Two_to_Four() {
  DriveForward();
  delay(200);
  Steer();
  //at A go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  //at 0 go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(500);
  }
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
}

//two to five function
void Two_to_Five() {
  DriveForward();
  delay(200);
  Steer();
  //at A go right
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);
  }
  Steer();
  //at 1 go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  //at b go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  JunctionFive();
  }
  position = destination;
}


//start of Three to destination functions
void Three_to_Zero(){
  DriveForward();
  delay(200);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //go straight through junction A
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(500);
  position = destination;
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
  }
  
}

//3 - > 1
void Three_to_One(){
  DriveForward();
  delay(200);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}
  

//3 - > 2
void Three_to_Two(){
  DriveForward();
  delay(200);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}

//3 - > 4
void Three_to_Four(){
  Uturn();
  delay(1300);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  }
  delay(3000);
}
//3 - > 5
void Three_to_Five(){
  DriveForward();
  delay(200);
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveRight();
  delay(1000);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  JunctionFive();
  }
  position = destination;
  }


//four to destination functions
//four to zero function
void Four_to_Zero() {
  DriveForward();
  delay(200);
  Steer();
  //at 0 stop
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
}
}

//four to one function
void Four_to_One() {
  DriveForward();
  delay(200);
  Steer();
  //at 0 go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //at a go left
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);;
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  position = destination;
  delay(3000);
  }
}

//four to two function
void Four_to_Two() {
  DriveForward();
  delay(200);
  Steer();
  //at 0 go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //at a go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(500);
  position = destination;
  }
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
}

//four to three function
void Four_to_Three() {
  DriveForward();
  delay(200);
  Steer();
  //at 0 go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  //at a go straight
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(500);
  position = destination;
  }
  Uturn();
  delay(1300);
  Stop();
  delay(3000);
}

//four to five function
void Four_to_Five() {
  DriveForward();
  delay(200);
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  //at 5 stop
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  DriveLeft();
  delay(1000);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  DriveForward();
  delay(200);
  }
  Steer();
  if( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550){
  Stop();
  delay(200);
  JunctionFive();
  }
  position = destination;
}

void DriveLeft() {
    digitalWrite(motor1Phase, HIGH); //forward
    analogWrite(motor1PWM, 150); // set speed of motor

    digitalWrite(motor2Phase, HIGH); //forward
    analogWrite(motor2PWM, 25); // set speed of motor to slightly higher
 }

void DriveRight() {
    digitalWrite(motor1Phase, HIGH); //forward
    analogWrite(motor1PWM, 25); // set speed of motor to slightly higher

    digitalWrite(motor2Phase, HIGH); //forward
    analogWrite(motor2PWM, 150); // set speed of motor
 }

void DriveForward(){

    digitalWrite(motor1Phase, HIGH); //forward
    analogWrite(motor1PWM, 150); // set speed of motor

    digitalWrite(motor2Phase, HIGH); //forward
    analogWrite(motor2PWM, 140); // set speed of motor
 }

 void SloMo(){

    digitalWrite(motor1Phase, HIGH); //forward
    analogWrite(motor1PWM, 75); // set speed of motor

    digitalWrite(motor2Phase, HIGH); //forward
    analogWrite(motor2PWM, 70); // set speed of motor
 }

 void Snail(){

    SnailBeep();

    digitalWrite(motor1Phase, HIGH); //forward
    analogWrite(motor1PWM, 37.5); // set speed of motor

    digitalWrite(motor2Phase, HIGH); //forward
    analogWrite(motor2PWM, 35); // set speed of motor
 }

 void Reverse(){
    digitalWrite(motor1Phase, LOW); //Backward
    analogWrite(motor1PWM, 150); // set speed of motor

    digitalWrite(motor2Phase, LOW); //Backward
    analogWrite(motor2PWM, 145); // set speed of motor
 }

 void Stop(){
    digitalWrite(motor1Phase, LOW); //Backward
    analogWrite(motor1PWM, 0); // set speed of motor to zero

    digitalWrite(motor2Phase, LOW); //Backward
    analogWrite(motor2PWM, 0); // set speed of motor to zero
    Sweep();
  }

   void Sweep(){

    digitalWrite(motor3Phase, HIGH); //forward
    analogWrite(motor3PWM, 90); // set speed of motor
    delay (1000);  
    
    digitalWrite(motor3Phase, LOW); //forward
    analogWrite(motor3PWM, 90); // set speed of motor
    delay (1000);

    digitalWrite(motor3Phase, HIGH); //forward
    analogWrite(motor3PWM, 0); // set speed of motor

 }


 void Uturn() {
  //make sure to have a stop afetr the Uturn
    digitalWrite(motor1Phase, LOW); //backward
    analogWrite(motor1PWM, 90); // set speed of motor

    digitalWrite(motor2Phase, LOW); //forward
    analogWrite(motor2PWM, 90); // set speed of motor
  //the delay after calling Uturn function is what makes it turn the right distance
 }

  void SloMoBeep(){
   for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/SloMoSound[thisNote];

    tone(A8, beep[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(A8);
  }
}

  void SnailBeep(){
     for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration2 = 1000/SnailSound[thisNote];

    tone(A8, beep[thisNote],noteDuration2);
   
    int pauseBetweenNotes = noteDuration2 * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(A8);
  }
    
  }


 


//Steering function called in between each juntion
 void Steer() {
    int shouldContinue = 1;
    
    while (shouldContinue == 1) {
      //for loop to try an dix this becasue the sesnors are staying on the same value
        for (i=0;i<5;i++){
        AnalogValue[i]=analogRead(AnalogPin[i]);
        }
      //end of for loop
        
        if (AnalogValue[1] > 350 && AnalogValue[2] < 300 && AnalogValue[3] > 350 || AnalogValue[1] < 300 && AnalogValue[2] < 300 && AnalogValue[3] < 300) {
            DriveForward();
        }

        if (AnalogValue[4] < 300 || AnalogValue[3] < 300 || AnalogValue[3] < 300 && AnalogValue[4] < 300 || AnalogValue[2] < 300 && AnalogValue[3] < 300 || AnalogValue[2] < 300 && AnalogValue[3] < 300 && AnalogValue[4] < 300) {
            DriveLeft();
        }

        if (AnalogValue[1] < 300 || AnalogValue[1] < 300 && AnalogValue[2] < 300 || AnalogValue[0] < 300 || AnalogValue[0] < 300 && AnalogValue[1] < 300 || AnalogValue[0] < 300 && AnalogValue[1] < 300 && AnalogValue[2] < 300) {
            DriveRight();
        }
        

        if ( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550) {
            //shouldContinue = false;
            shouldContinue = 0;
        }
        
    }
 }

//Function to get as close as possible to wall using the Sharp distance sensor
 void JunctionFive(){
    int Continue = 1;
      
    while(Continue == 1){
      ParkingSensor = analogRead(ParkingPin)- 874;
      DriveForward();
      delay(3000);
      SloMo();
      delay(5000);
      Snail();
      delay(1000);
      if(ParkingSensor > 3){
        Stop();
        delay(3000);
        Continue = 0;

          
      }
    }
}



/////////////////////////////////////////////////////////////////////
/////////////////LOOP////////////////////////////////////////////////

void loop(){
  if (connect()){
    SendMessage();      
    String response = readResponse();
    getStatusCode(response);

    // We are assigning the cut string response from the server to the variable, target
    target = getResponseBody(response); 

    //We are converting our current position to an Integer
    CurrentPosition = position.toInt();
    destination = target.toInt();        

    Serial.println("Position as Int");
    Serial.println(CurrentPosition);
    Serial.println("Destination as Int");
    Serial.println(destination);

  if(CurrentPosition == 0 && destination == 1){
    Zero_to_One();
  CurrentPosition == 1;
 }

  if(CurrentPosition == 0 && destination == 2){
    Zero_to_Two();
    CurrentPosition == 2;
  }

    if(CurrentPosition == 0 && destination == 3){
    Zero_to_Three();
    
    CurrentPosition == 3;
  }

  if(CurrentPosition == 0 && destination == 4){
    Zero_to_Four();

    //CurrentPosition == 4;
  }

  if(CurrentPosition == 0 && destination == 5){
    Zero_to_Five();

   // CurrentPosition == 5;
  }

  
  if(CurrentPosition == 1 && destination == 0){
  One_to_Zero();
  CurrentPosition == 0;
 }

  if(CurrentPosition == 1 && destination == 2){
    One_to_Two();
    CurrentPosition == 2;
  }

   if(CurrentPosition == 1 && destination == 3){
    One_to_Three();
    CurrentPosition == 3;
  }

   if(CurrentPosition == 1 && destination == 4){
    One_to_Four();
    CurrentPosition == 4;
  }
   if(CurrentPosition == 1 && destination == 5){
    One_to_Five();
    CurrentPosition == 5;
  }

  if(CurrentPosition == 2 && destination == 0){
    Two_to_Zero();
    CurrentPosition == 0;
  }

  if(CurrentPosition == 2 && destination == 1){
    Two_to_One();
    CurrentPosition == 1;
  }

  if(CurrentPosition == 2 && destination == 3){
    Two_to_Three();
    CurrentPosition == 3;
  }

  if(CurrentPosition == 2 && destination == 4){
    Two_to_Four();
    CurrentPosition == 4;
  }

  if(CurrentPosition == 2 && destination == 5){
    Two_to_Five();
    CurrentPosition == 5;
  }

    if(CurrentPosition == 3 && destination == 0){
    Three_to_Zero();
    CurrentPosition == 0;
  }
  
  if(CurrentPosition == 3 && destination == 1){
    Three_to_One();
    CurrentPosition == 1;
  }

  if(CurrentPosition == 3 && destination == 2){
    Three_to_Two();
    CurrentPosition == 2;
  }

  if(CurrentPosition == 3 && destination == 4){
    Three_to_Four();
    CurrentPosition == 4;
  }

  if(CurrentPosition == 3 && destination == 5){
    Three_to_Five();
    CurrentPosition == 5;
  }

  if(CurrentPosition == 4 && destination == 0){
    Four_to_Zero();
    CurrentPosition == 0;
  }

  if(CurrentPosition == 4 && destination == 1){
    Four_to_One();
    CurrentPosition == 1;
  }

  if(CurrentPosition == 4 && destination == 2){
    Four_to_Two();
    CurrentPosition == 2;
  }

  if(CurrentPosition == 4 && destination == 3){
    Four_to_Three();
    CurrentPosition == 3;
  }

  if(CurrentPosition == 4 && destination == 5){
    Four_to_Five();
    CurrentPosition == 5;
  }


    client.stop();
}

}

////Secondary MSP432 Code(For added flag and brush Feature)

int motor3PWM = 39; // P2.6
int motor3Phase = 40; // P2.7
int motor4PWM = 38; //2.4
int motor4Phase = 34; // 2.3

// void Stop(){
//    digitalWrite(motor1Phase, LOW); //Backward
//    analogWrite(motor1PWM, 0); // set speed of motor to zero
//
//    digitalWrite(motor2Phase, LOW); //Backward
//    analogWrite(motor2PWM, 0); // set speed of motor to zero
//  }
     void Sweep(){

    digitalWrite(motor3Phase, HIGH); //forward
    analogWrite(motor3PWM, 80); // set speed of motor
    delay (1500);  

    digitalWrite(motor3Phase, HIGH); //forward
    analogWrite(motor3PWM, 0); // set speed of motor

 }

    void Flag(){

    digitalWrite(motor4Phase, HIGH); //forward
    analogWrite(motor4PWM, 130); // set speed of motor
    delay (2500);  

    digitalWrite(motor4Phase, HIGH); //forward
    analogWrite(motor4PWM, 0); // set speed of motor

 }



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


}                                                                                          

void loop() {
   if ( AnalogValue[0] > 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] < 550 || AnalogValue[0] < 550 && AnalogValue[1] < 550 && AnalogValue[2] < 550 && AnalogValue[3] < 550 && AnalogValue[4] > 550) {
            Flag();
            Sweep();
        }
  
}




