
/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt/Firebase-ESP32
 * 
 * Copyright (c) 2022 mobizt
 *
*/

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "TOPNET637"
#define WIFI_PASSWORD "A9C43546C2"

//For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyDfQ_wChK8KQ0yiVkhmmd0lP8jMYJwxeWs"

/* 3. Define the RTDB URL */
#define DATABASE_URL "smart-farming-d6687-default-rtdb.europe-west1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "sssems@account.com"
#define USER_PASSWORD "123456789"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
int pos1,
    pos2;
void setup()
{

  Serial.begin(115200);

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

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  //Or use legacy authenticate method
  //config.database_url = DATABASE_URL;
  //config.signer.tokens.legacy_token = "<database secret>";

  //To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino


  //////////////////////////////////////////////////////////////////////////////////////////////
  //Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  //otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////

  Firebase.begin(&config, &auth);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  /** Timeout options.

  //WiFi reconnect timeout (interval) in ms (10 sec - 5 min) when WiFi disconnected.
  config.timeout.wifiReconnect = 10 * 1000;

  //Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
  config.timeout.socketConnection = 10 * 1000;

  //Server response read timeout in ms (1 sec - 1 min).
  config.timeout.serverResponse = 10 * 1000;

  //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
  config.timeout.rtdbKeepAlive = 45 * 1000;

  //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
  config.timeout.rtdbStreamReconnect = 1 * 1000;

  //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
  //will return false (error) when it called repeatedly in loop.
  config.timeout.rtdbStreamError = 3 * 1000;

  Note:
  The function that starting the new TCP session i.e. first time server connection or previous session was closed, the function won't exit until the 
  time of config.timeout.socketConnection.

  You can also set the TCP data sending retry with
  config.tcp_data_sending_retry = 1;

  */
}

void loop()
{
 if( Serial.available()  ){
  String x = Serial.readString() ;
  pos1 =  x.indexOf('+');
  Serial.println("1 : " + x.substring( 0, pos1) );
  
  if(x.substring( 0, pos1) == "z1"){
    pos2 =  x.indexOf('+', pos1+1);
    Serial.println("1 : " + x.substring( pos1+1, pos2) );  
  
      if(x.substring( pos1+1, pos2) == "t"){
       
        x = x.substring( pos2+1);
        Serial.println(x);    
        if (Firebase.ready() )
        {
    
        Serial.printf("Set string... %s\n", Firebase.setString(fbdo, F("/farmX/GreenZone1/irrigationSystem/temperature"), String(x) ) ? "ok" : fbdo.errorReason().c_str());

        Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("/farmX/GreenZone1/irrigationSystem/temperature") ) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
        }

     }
     else if(x.substring( pos1+1, pos2) == "h"){
       
        x = x.substring( pos2+1);
        Serial.println(x);    
        if (Firebase.ready() )
        {
    
        Serial.printf("Set string... %s\n", Firebase.setString(fbdo, F("/farmX/GreenZone1/irrigationSystem/humidity"), String(x) ) ? "ok" : fbdo.errorReason().c_str());

        Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("/farmX/GreenZone1/irrigationSystem/humidity") ) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
        }

       }
  }
  else if(x.substring( 0, pos1) == "z2")
  {
    pos2 =  x.indexOf('+', pos1+1);
    Serial.println("1 : " + x.substring( pos1+1, pos2) );  
  
      if(x.substring( pos1+1, pos2) == "t"){
       
        x = x.substring( pos2+1);
        Serial.println(x);    
        if (Firebase.ready() )
        {
    
        Serial.printf("Set string... %s\n", Firebase.setString(fbdo, F("/farmX/GreenZone2/irrigationSystem/temperature"), String(x) ) ? "ok" : fbdo.errorReason().c_str());

        Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("/farmX/GreenZone2/irrigationSystem/temperature") ) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
        }

     }
     else if(x.substring( pos1+1, pos2) == "h"){
       
        x = x.substring( pos2+1);
        Serial.println(x);    
        if (Firebase.ready() )
        {
    
        Serial.printf("Set string... %s\n", Firebase.setString(fbdo, F("/farmX/GreenZone2/irrigationSystem/humidity"), String(x) ) ? "ok" : fbdo.errorReason().c_str());

        Serial.printf("Get string... %s\n", Firebase.getString(fbdo, F("/farmX/GreenZone2/irrigationSystem/humidity") ) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());
        }

       }
  }
  
  
 }
}
  
