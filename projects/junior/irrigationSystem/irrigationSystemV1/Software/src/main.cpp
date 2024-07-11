
//consts 
  const int  tc1 = 15 ; //the needed temputure to active the solenoid 1 should be  15 degrees
  const int  tc2 = 25 ; // the needed temputure to active the solenoid 2 should be  25 degrees
  const int  hmdc1 = 30 ; // the needed Humidity to active the solenoid 1 should be   30 % 
  const int  hmdc2 = 20 ; // the needed Humidity to active the solenoid 2 should be  20 % 
//variables declaration
  int S_Valve_1 = 3, S_Valve_2 = 2;   
  int Temp1 =  A0, Temp2 =  A1, Humid1 =  A2, Humid2 = A3;
  
  char mode = 'A'; // the mode A : automated  or  M : manual
  int user_typed = 1; 
  
void setup() {

  //setup the Serial
  Serial.begin(9600);

  //inputs ' pins setup
  pinMode(Temp1, INPUT);
  pinMode(Temp2, INPUT);
  pinMode(Humid1, INPUT);
  pinMode(Humid2, INPUT);
  //outputs ' pins setup
  pinMode(S_Valve_1, OUTPUT);
  pinMode(S_Valve_2, OUTPUT);

 
  
}

void loop() {
  //
  
  
  if(mode == 'A')
  {
      
      
      int process_done = 0;
     //if u get the need tempurateur & humadity active the valve
     
     if(process_done == 0){
     if(map(analogRead(Temp1), 0, 1023, 100, 0) == tc1 & map(analogRead(Humid1), 0, 1023, 100, 0)== hmdc1 )
     {
          //activ valve 1
          //notification 
                  Serial.println(" ");
                  Serial.println(">>>> NOTIFICATION FROM AUTOMATED MODE !!");
                  Serial.println("    valve 1 is activated");
                  Serial.println(" ");
          //activ valve 1        
                  digitalWrite(S_Valve_1,1); 
          //delay
                  Serial.println("****************irrigation process****************");
                  Serial.print("wait.");
                  int counter = 10;
                  while(counter != 0){
                    Serial.print(".");
                    delay(100);
                    counter--;       
                  }
         
          //stop valve 1
                  
                  Serial.println("****************irrigation process done****************");
                  process_done = 1;
                  
        }        
          while(process_done == 1){ 
            if( map( analogRead(Temp2), 0, 1023, 100, 0 ) != tc2 | map( analogRead(Humid2), 0, 1023, 100, 0) != hmdc2 )
              {
                digitalWrite(S_Valve_1,0);
                process_done = 0;
              }
            };        
          //change sensor values 
                  
                      
     }
     if( map( analogRead(Temp2), 0, 1023, 100, 0 ) == tc2 & map( analogRead(Humid2), 0, 1023, 100, 0) == hmdc2 )
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
                  
     }
  }
  
  //active only once each time
  if(user_typed == 1)
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
  }
  //if user entred something else
  if(Serial.available())
    {
      char action = Serial.read();

      user_typed = 1;

      if(action == '1')
        {
          Serial.println("==================== Data ====================");
              Serial.println("    GREEN ZONE 1 : ");
                  Serial.print("        Tempurature : ");
                  Serial.println( map(analogRead(Temp1), 0, 1023, 100, 0) );

                  Serial.print("        Humidity : ");
                  Serial.println( map(analogRead(Humid1), 0, 1023, 100, 0) );
 
              
              Serial.println("    GREEN ZONE 2 : ");
                  Serial.print("        Tempurature : ");
                  Serial.println( map(analogRead(Humid1), 0, 1023, 100, 0) );

                  Serial.print("        Humidity : ");
                  Serial.println( map(analogRead(Humid2), 0, 1023, 100, 0) ); 
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
    }
  
  
  
}
