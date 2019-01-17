/*
 * PIR sensor tester
 */
 
int buzzer = 8;
int pir = 4;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
//int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(buzzer, OUTPUT);      // declare LED as output
  pinMode(pir, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
 int value = digitalRead(pir);  // read input value
  if (value == HIGH) {            // check if the input is HIGH
    tone(buzzer,1000);
    //if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      //pirState = HIGH;
    //}
  } else {
    noTone(buzzer);
    //if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
     // pirState = LOW;
    //}
  }
}
