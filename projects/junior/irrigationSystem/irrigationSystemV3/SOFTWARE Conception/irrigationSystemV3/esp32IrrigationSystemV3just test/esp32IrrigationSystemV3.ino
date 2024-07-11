
#include <WiFi.h>
#include <FirebaseESP32.h>

// authentification info
#define FIREBASE_HOST "  "
#define FIREBASE_AUTH " "

#define WIFI_SSID " "
#define WIFI_PASSWORD "  "


//Define FirebaseESP32data object for data sending and receiving
FirebaseData firebaseData;
String path = "/couter";
//variables declaration
int countr = 0;

int increaBtn = 12 ;

void setup()
{

  //setup counter increament button
  pinMode(increaBtn, INPUT_PULLUP);

  // setup serial
  Serial.begin(115200);
  
  //setup & connect wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //Setup Firebase info & try to connect to project

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  Firebase.beginStream(firebaseData,path);

 
}  


  


void loop()
{

  if( digitalRead(increaBtn) == LOW){
    countr += 1 ;
    if(Firebase.setInt(firebaseData, path, countr))
    {
       //Success
        Serial.println("counter :");
        Serial.print(countr);

     }else{
      //Failed?, get the error reason from firebaseData

      Serial.print("Error in setInt, ");
      Serial.println(firebaseData.errorReason());
  }
  delay(300);
 } 
 
}
