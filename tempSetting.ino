#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <Servo.h> 


LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10); //create the lcd variable
int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
OneWire ds(DS18S20_Pin);  // on digital pin 2
Servo myservo;  // create servo object to control a servo 


int potIn = A0;
int potRead;
int targetTemp=100;
int motorPos = 0;
 
void setup() {
  lcd.clear();                    //clear the LCD during setup
  lcd.begin(16,2);                //define the columns (16) and rows (2)
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);

}
 
void loop() {
  displayTemp();
  adjustTemp();
}




void setTemp(){
  potRead = analogRead(potIn);
  targetTemp = map(potRead, 3, 1020, 50, 130);
}


void displayTemp(){
  lcd.print("SetTempTo: ");
  setTemp();
  lcd.print(targetTemp);
  if (targetTemp>=100) {
    lcd.setCursor(14,0);
    lcd.print("F");
  } else {
    lcd.setCursor(13,0);
    lcd.print("F ");
  }
  lcd.setCursor(0,1);
  lcd.print("CurTemp: ");
  float tempRead = getTemp()*9/5+32;
  Serial.println(tempRead);
  //lcd.print(getFloorInt(tempRead));
  lcd.print(tempRead);
  lcd.print("F ");
  delay(250);
  lcd.home();

}

int getFloorInt(float number){
  return int(floor(number));
}

void adjustTemp() {
  motorPos = map(targetTemp, 50, 130, 179, 0);
  //delay(1000);
  myservo.write(motorPos);
  delay(100);
}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}
