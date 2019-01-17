//#include <SoftwareSerial.h>
//#include <Servo.h> 
//SoftwareSerial mySerial(0, 1); // RX, TX


int led = 8; //for led
//int led2 = 11;
//int led3 = 12;

int buzzer = 9;  //for buzzer
int gas = A5;  // MQ-02 gas detect
int airQuality = A0; // MQ-135 Air Quality
int fire = A2; //Fire Detect


int irSensor = 10;  // obstacle detect light on
int irSensor2 = 6;  // obstacle detect and alarm
int motionSensor = HIGH;  // HIGH MEANS NO OBSTACLE
int motionSensor2 = HIGH;  // HIGH MEANS NO OBSTACLE
int gasLimit = 400;       
//int fireValue = 0;             
String quality ="";
//int servoPin = 4;
//Servo Servo1;

  int gasSensor;
  int airQualitySensor;
  int fireSensor;
  

void setup() {
                     
  pinMode(gas,INPUT);                 
  pinMode(airQuality, INPUT);  
  pinMode(fire, INPUT); 
                    
  pinMode(led, OUTPUT);
 // pinMode(led2, OUTPUT);
  //pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(irSensor, INPUT);
  pinMode(irSensor2, INPUT);

  //Servo1.attach(servoPin);
  
  Serial.begin(9600);


}

void loop() {
  gasSensor = analogRead(gas);
  airQualitySensor = analogRead(airQuality);
  fireSensor = analogRead(fire);
  motionSensor = digitalRead(irSensor);
  motionSensor2 = digitalRead(irSensor2);

 
  //Methods
  gasWork();
   delay(100); 
  airWork();
   delay(100);
  fireWork();
   delay(100);
  motionWork();
   delay(100);
   motionWork2();
   delay(100);

//  if(Serial.available() > 0)  // Send data only when you receive data:
//  {
//    Serial.print("found"); 
//    int data = Serial.read();      
//    //Serial.print(data);        
//    Serial.println("");
//    bluetooth(data);
//    
//  }     

  
  
  delay(100);

}

// Gas Detect Method

int gasWork() {

  Serial.print("Gas Value: ");
  
  Serial.print(gasSensor);
  
  if (gasSensor > gasLimit)
  {
    //digitalWrite(led, HIGH);
    tone(buzzer, 1000, 200);
  }
  else
  {
    //digitalWrite(led, LOW);
    noTone(buzzer);
  }
  Serial.println("");
}

// Air Quality Method

int airWork(){

Serial.print("Air Quality: ");

  if(airQualitySensor<175){
    quality = "GOOD! ";
    Serial.print(quality);
  }
  else if (airQualitySensor >175 && airQualitySensor<225){
    quality = "Medium ";
    Serial.print(quality);
  }
  else if (airQualitySensor >225 && airQualitySensor<300){
    quality = "Bad ";
    Serial.print(quality);
  }
  else if (airQualitySensor >300){
    quality = "Very Bad ";
    Serial.print(quality);
  }
  Serial.println("");
  
  }

 // Fire Detect

  int fireWork(){
    
    if (fireSensor < 100)

   {

     Serial.println("Fire Detected");
     //digitalWrite(led, HIGH);
     tone(buzzer, 1000, 200);

    }else {
      //digitalWrite(led, LOW);
      noTone(buzzer);
    }
    Serial.println("");
  }


// Motion Detect

 int  motionWork() {

  
  if (motionSensor == LOW)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    digitalWrite(led, HIGH);
    
  }
  else
  {
    digitalWrite(led, LOW);
    
  }

  Serial.println("");
  }

// Bluetooth Work

//  int bluetooth(int d){
//
//  
//    
//    if(d == 255){             
//     
//      digitalWrite(led2, HIGH);
//      
//    }
//    else if(d == 241) {      
//      digitalWrite(led2, LOW); 
//    }
//
//    else if(d == 225) {      
//      digitalWrite(led3, HIGH); 
//    }
//
//    else if(d == 33) {      
//      digitalWrite(led3, LOW); 
//    }
//
//    else if(d == 97) {      
//      digitalWrite(led3, LOW); 
//    }
//
//    else if(d == 141) {      
//      Servo1.write(180);
//    }
//
//    else if(d == 13) {      
//      Servo1.write(0);
//    }
//
//    
// 
//    
//    
//    }


    int motionWork2(){

      if (motionSensor2 == LOW)
  {
    Serial.println("Thief!! Thief!!");
    
    tone(buzzer, 1000, 200);
  }
  else
  {
    
    noTone(buzzer);
  }

  Serial.println("");
  }
      
      
