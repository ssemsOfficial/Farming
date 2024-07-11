/***DHT library include & config***/

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
  /*** create 1st dht sensor ***/
   //define type and pin  
   #define DHTPIN1 A0     
   #define DHTTYPE1    DHT11       //#define DHTTYPE    DHT22     // DHT 22 (AM2302) OR //#define DHTTYPE    DHT21     // DHT 21 (AM2301)  
   //create instance dht
   DHT_Unified dht1(DHTPIN1, DHTTYPE1);
   //create event
   sensors_event_t event1;
  /*** END OF : create 1st dht sensor ***/

  /*** create 1st dht sensor ***/
   //define type and pin  
   #define DHTPIN2 A1     
   #define DHTTYPE2    DHT11     // DHT 11 
   //instance dht
   DHT_Unified dht2(DHTPIN2, DHTTYPE2);
   //create event
   sensors_event_t event2;
  /*** END OF : create 1st dht sensor ***/
uint32_t delayMS;


/** END of : DHT library include & config ***/

/*** CONSTS DECLARATION ***/
  const float  tc1 = 15;  //the needed temputure to active the solenoid 1 should be  15 degrees
  const float  tc2 = 25.00 ; // the needed temputure to active the solenoid 2 should be  25 degrees
  const float  hmdc1 = 30.00  ; // the needed Humidity to active the solenoid 1 should be   30 % 
  const float  hmdc2 = 20.00  ; // the needed Humidity to active the solenoid 2 should be  20 % 
  
/*** END OF : CONSTS DECLARATION ***/

/*** VARIAVLES DECLARATION ***/
  int S_Valve_1 = 3,
      S_Valve_2 = 2;   
  //int Temp1 =  A0, Temp2 =  A1, Humid1 =  A2, Humid2 = A3;
  char mode = 'A'; // the mode A : automated  or  M : manual
  int user_typed = 1;
  int irrigation_process_done = 0;
  float tempz1 ,
        prev_tempz1,
        tempz2,
        prev_tempz2;
  float humz1,
        prev_humz1,
        humz2,
        prev_humz2; 
/*** END OF : VARIAVLES DECLARATION***/
  
void setup() {

  //setup the Serial
  Serial.begin(115200);
  
  //SETUP DHT SENSORS
    /*** SETUP dht1 ***/
    dht1.begin();
    sensor_t dht_sensor_1;
    dht1.temperature().getSensor(&dht_sensor_1);
    dht1.humidity().getSensor(&dht_sensor_1);
    /*** END OF : SETUP dht1 ***/

    /*** SETUP dht2 ***/
    dht2.begin();
    sensor_t dht_sensor_2;
    dht2.temperature().getSensor(&dht_sensor_2);
    dht2.humidity().getSensor(&dht_sensor_2);
    /*** END OF : SETUP dht1 ***/
    // delayMS = sensor.min_delay / 1000;
  //END OF : SETUP DHT SENSORS
  
  //inputs ' pins setup
  
  //outputs ' pins setup
  pinMode(S_Valve_1, OUTPUT);
  pinMode(S_Valve_2, OUTPUT);

}

void loop() {
 if(mode == 'A')  // if the mode is the automatic mode
  {  
        //reading temperature value from dht
      dht1.temperature().getEvent(&event1);
      tempz1 = event1.temperature;
      // 
      if(tempz1 != prev_tempz1 )// test if it got a different value from the previous one
        { 
          Serial.print("z1+t+"+String(tempz1));
          prev_tempz1 = tempz1;
        }//end if(temp != prev_temp )
      delay(250);  
        //reading humidity value from dht   
      dht1.humidity().getEvent(&event1);
      humz1 = event1.relative_humidity;
      //
      if(humz1 != prev_humz1)// test if it got a different value from the previous one
        { 
          Serial.print("z1+h+"+String(humz1));
          prev_humz1 = humz1;
        }//if(hum != prev_hum)
        //test the condition of ....
      if( tempz1 == tc1 & humz1 == hmdc1 )
        {
          //activ valve 1
          //notification 
                /*Serial.println(" ");
                  Serial.println(">>>> NOTIFICATION FROM AUTOMATED MODE !!");
                  Serial.println("    valve 1 is activated");
                  Serial.println(" ");*/
          //activ valve 1        
                  digitalWrite(S_Valve_1,1);
          //delay
                  /*Serial.println("****************irrigation process****************");           
                  Serial.print("wait");*/
                  int counter = 10;
                  while(counter != 0)
                    {
                      /*Serial.print(".");*/
                      delay(500);
                      counter--;       
                    }
           //stop valve 1
                /*Serial.println("");
                  Serial.println("****************irrigation process done***********");*/
                  digitalWrite(S_Valve_1,0);
        } //end   if( tempz1 == tc1 & humz1 == hmdc1 ) 

        delay(250);
        //reading temperature value from dht 2
      dht2.temperature().getEvent(&event2);
      tempz2 = event2.temperature;
      // 
      if(tempz2 != prev_tempz2 )// test if it got a different value from the previous one
        { 
          Serial.print("z2+t+"+String(tempz2));
          prev_tempz2 = tempz2;
        }//end if(tempz2 != prev_tempz2 )
      delay(250);  
        //reading humidity value from dht   
      dht2.humidity().getEvent(&event2);
      humz2 = event2.relative_humidity;
      //
      if(humz2 != prev_humz2)// test if it got a different value from the previous one
        { 
          Serial.print("z2+h+"+String(humz2));
          prev_humz2 = humz2;
        }//if(humz2 != prev_humz2)
        //test the condition of ....
      if( tempz2 == tc1 & humz2 == hmdc1 )
        {
          //activ valve 1
          //notification 
                /*Serial.println(" ");
                  Serial.println(">>>> NOTIFICATION FROM AUTOMATED MODE !!");
                  Serial.println("    valve 1 is activated");
                  Serial.println(" ");*/
          //activ valve 1        
                  digitalWrite(S_Valve_2,1);
          //delay
                  /*Serial.println("****************irrigation process****************");           
                  Serial.print("wait");*/
                  int counter = 10;
                  while(counter != 0)
                    {
                      /*Serial.print(".");*/
                      delay(500);
                      counter--;       
                    }
           //stop valve 1
                /*Serial.println("");
                  Serial.println("****************irrigation process done***********");*/
                  digitalWrite(S_Valve_2,0);
        } //end   if( tempz2 == tc1 & humz2 == hmdc1 )                
                           
     
     /*if( map( analogRead(Temp2), 0, 1023, 100, 0 ) == tc2 & map( analogRead(Humid2), 0, 1023, 100, 0) == hmdc2 )
     {
        int process_done = 0;
        if(process_done == 0){ 
          //activ valve 2
          //notification 
                  Serial.println(" ");
                  Serial.println(">>>> NOTIFICATION FROM AUTOMATED MODE !!");
                  Serial.println("    valve 2 is activated");
                  Serial.println(" ");
          //activ valve 2        
                  digitalWrite(S_Valve_2,1); 
          //delay
                  Serial.println("****************irrigation process****************");
                  Serial.print("wait.");
                  int counter = 10;
                  while(counter != 0){
                    Serial.print(".");
                    delay(100);
                    counter--;       
                  }
         
          //stop valve 2
                  
                  Serial.println("****************irrigation process done****************");
                  process_done = 1;
        }         
         
          while(process_done == 1){ 
            if( map( analogRead(Temp2), 0, 1023, 100, 0 ) != tc2 | map( analogRead(Humid2), 0, 1023, 100, 0) != hmdc2 )
              {
                digitalWrite(S_Valve_2,0);
                process_done = 0;
              }
            };        
                  
     }*/
  }

  
  //active only once each time
  /*if(user_typed == 1)
  { 
    Serial.println(" ");
    Serial.println(" "); 
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" "); 
    Serial.println(" ");
    Serial.println(">>welcome user , what you wanna do :");
    Serial.println("          Type 1 if you wanna consult your data");
    Serial.println("          Type 2 if you wanna the Mannual Mode");
    Serial.println(" ");
    Serial.println(" "); 
    Serial.println(" ");
    user_typed = 0;
  }*/

  
  //if user entred something else
  /*if(Serial.available())
    {
      char action = Serial.read();

      user_typed = 1;

      if(action == '1')
        {

          //getting data from DHT sensor
           
           
           
          
          Serial.println("==================== Data ====================");
              Serial.println("    GREEN ZONE 1 : ");
                  Serial.print("        Humidity : ");
                  dht1.humidity().getEvent(&event1);
                  Serial.println( event1.relative_humidity);

                  Serial.print("        Tempurature : ");
                  dht1.temperature().getEvent(&event1);
                  Serial.println( event1.temperature  );

              
              Serial.println("    GREEN ZONE 2 : ");
                  Serial.print("        Humidity : ");
                  dht2.humidity().getEvent(&event2);
                  Serial.println( event2.relative_humidity );

                  Serial.print("        Tempurature : ");
                  dht2.temperature().getEvent(&event2);                  
                  Serial.println( event2.temperature  );                   
          Serial.println("==============================================");
          delay(4000);
        }
      else if(action == '2')
        {   
            //notifie that the manual mode is activated
            Serial.println(" ");
            Serial.println("Mannual mode is activated");
            Serial.println(" ");
            mode = 'M';
            
            //print the menu 
             Serial.println("==================== manual mode menu ====================");
             Serial.println("    GREEN ZONE 1 : ");
                  Serial.println("        type 1 if you wanna active vanne . ");
                  Serial.println("        type 2 if you wanna stop vanne . ");

              
              Serial.println("    GREEN ZONE 2 : ");
                  Serial.println("        type 3 if you wanna active vanne . ");
                  Serial.println("        type 4 if you wanna stop vanne . ");

              Serial.println("    return to automated mode ");
                  Serial.println("        type 5 if you wanna if you wanna exit from the manual mode . ");
 
             Serial.println("==========================================================");

           while(mode == 'M')
           {

              if(Serial.available())
            {
              char manualAction = Serial.read();

                if(mode == 'M' & manualAction == '1' )
                {
                 //notifie that the valve 1 is activated
                  Serial.println(" ");
                  Serial.println("valve 1 is activated");
                  Serial.println(" ");
                  
                  digitalWrite(S_Valve_1,1);                 
                }
                else if(mode == 'M' & manualAction == '2' )
                {
                 //notifie that the valve 1 is desactivated
                  Serial.println(" ");
                  Serial.println("valve 1 is desactivated");
                  Serial.println(" ");
                  
                  digitalWrite(S_Valve_1,0);  
                }
                else if(mode == 'M' & manualAction == '3' )
                {
                  //notifie that the valve 2 is activated
                  Serial.println(" ");
                  Serial.println("valve 1 is activated");
                  Serial.println(" ");
                  
                  digitalWrite(S_Valve_2,1);
                }
                else if(mode == 'M' & manualAction == '4' )
                {
                 //notifie that the valve 2 is desactivated
                  Serial.println(" ");
                  Serial.println("valve 2 is desactivated");
                  Serial.println(" ");
                  digitalWrite(S_Valve_2,0);
                }
                else if(mode == 'M' & manualAction == '5' )
                {   
                  //notifie that the automated mode is activated
                  Serial.println(" ");
                  Serial.println("Automated mode is activated");
                  Serial.println(" ");
                  //active automated mode
                  mode = 'A';
                }
              }
              
           }

            
        }
    }*/
  
  
  
}
