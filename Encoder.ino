//From bildr article: http://bildr.org/2012/08/rotary-encoder-arduino/
//modified by Justeen Lee on 03072015
//update:
//1. delete unused code
//2. modify code so that turning right increases value and vice versa.
//3. modify code for Arduino Mega2560 and use pin 21 and 20 as interrupt pins

int encoderPin1 = 21;
int encoderPin2 = 20;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;


void setup() {
  Serial.begin (9600);
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  //call updateEncoder() when any high/low changed seen
  //on interrupt 2 (pin 21), or interrupt 3 (pin 20)
  attachInterrupt(2, updateEncoder, CHANGE);
  attachInterrupt(3, updateEncoder, CHANGE);
}

void loop(){
  //Do stuff here
  Serial.println(encoderValue);
  delay(100); //just here to slow down the output, and show it will work  even during a delay
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
  if(sum == 0b1101) encoderValue --;
  if(sum == 0b1110) encoderValue ++;
  lastEncoded = encoded; //store this value for next time
}
