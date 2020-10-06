#include <Wire.h> //allows communication to lcd
#include <LiquidCrystal_I2C.h> //general lcd stuff
//I am using an LCD to make looking at the machine nicer, and easier to test

//input
const int POT_PIN = 2;
const int BUTTON_PIN = 11;

//output
const int HOT_PIN = 10;
const int COLD_PIN = 9;
const int DRY_PIN = 8;
const int LOCK_PIN = 13;

//LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

int count = 0; //this boy's about to put in some WORK

//names of cycle types
enum WasherState{
  Idle = 0,
  Cold = 5, EconomyDry = 2,
  Hot = 7, DeluxeDry = 6,
  Medium = 3
} washer = Idle;

//potentiometer ranges from 0-1023. Values fluctuate a bit but never by more than 100 from where they are.
//set segments for 3 settings at 0-350, 351-700, 700-1023

void setup() {
  //set up pins
  pinMode(11, INPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);

  //initialize LCD
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  //set activity for an idle washer, such as being the only place where a button click matters
  if (washer == Idle) {
    //turn off anything that's on
    digitalWrite(HOT_PIN, LOW);
    digitalWrite(COLD_PIN, LOW);
    digitalWrite(DRY_PIN, LOW);
    digitalWrite(LOCK_PIN, LOW);

    int buttonBoi = digitalRead(BUTTON_PIN);
    Serial.println(buttonBoi);
    
    //read analog and choose type
    String washType = "";
    int potRead = analogRead(POT_PIN);
    if (potRead >=701) washType = "Super Deluxe";
    else if (potRead >= 351) washType = "Deluxe      ";
    else washType = "Economy     ";
    
    //write selected type to lcd
    lcd.setCursor(0,0);
    lcd.print("Selected:");
    lcd.setCursor(0,1);
    lcd.print(washType);

    //on a button press, start the selected cycle
    if (buttonBoi == HIGH){
      lcd.clear();
      //sdeluxe
      if(washType.equals("Super Deluxe")){
        digitalWrite(LOCK_PIN, HIGH);
        washer = Hot;
        count = 7;
      }

      //deluxe
      else if (washType.equals("Deluxe      ")){
        digitalWrite(LOCK_PIN, HIGH);
        washer = Hot;
        count = 7;
      }

      //econ
      else{
        digitalWrite(LOCK_PIN, HIGH);
        washer = Cold;
        count = 5;
      }
    }

    delay(250);
  }
  //activity for Cold, which is keeping an LED on as it counts down from
  else if (washer == Cold){
    //turn on LED and LCD
    digitalWrite(COLD_PIN, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Cold Water");
    lcd.setCursor(0,1);
    lcd.print(count);

    //wait a second before whifting
    delay(1000);
    count--;
    if (count == 0) {
      lcd.clear();
      digitalWrite(COLD_PIN, LOW);
      int val = analogRead(POT_PIN);
      if (val >= 351) {
        washer = DeluxeDry;
        count = 7;
      }
      else {
        washer = EconomyDry;
        count = 2;
      }
    }
  }

//activity for Hot, which is keeping an LED on as it counts down
  else if (washer == Hot){
    //turn on LED and LCD
    digitalWrite(HOT_PIN, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Hot Water");
    lcd.setCursor(0,1);
    lcd.print(count);

    //wait a second before whifting
    delay(1000);
    count-=1;
    
    if (count == 0) {
      lcd.clear();
      digitalWrite(HOT_PIN, LOW);
      int val = analogRead(POT_PIN);
      if (val >= 701) {
        washer = Medium;
        count = 7;
      }
      else if (val <= 351) {
        washer = EconomyDry;
        count = 2;
      }
      else {
        washer = DeluxeDry;
        count = 7;
      }
    }
    
  }

  //activity for Medium, which is keeping 2 LEDs on as it counts down
  else if (washer == Medium){
    //turn on LED and LCD
    digitalWrite(HOT_PIN, HIGH);
    digitalWrite(COLD_PIN, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Medium Water");
    lcd.setCursor(0,1);
    lcd.print(count);

    //wait a second before whifting
    delay(1000);
    count--;
    if (count == 0) {
      lcd.clear();
      digitalWrite(HOT_PIN, LOW);
      digitalWrite(COLD_PIN, LOW);
      int val = analogRead(POT_PIN);
      if (val <= 351) {
        washer = EconomyDry;
        count = 2;
      }
      else {
        washer = DeluxeDry;
        count = 7;
      }
    }
  }

  //activity for EconDry
  else if (washer == EconomyDry) {
    //turn on LED and LCD
    digitalWrite(DRY_PIN, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Drying");
    lcd.setCursor(0,1);
    lcd.print(count);
    //wait, then count down and check if done
    delay(1000);
    count--;
    if (count == 0) {
      lcd.clear();
      digitalWrite(LOCK_PIN, LOW);
      lcd.setCursor(11,0);
      lcd.print("Done!");
      delay(750);
      washer = Idle;
      lcd.clear();
    }
  }

  //activity for DelDry
  else if (washer == DeluxeDry) {
    //turn on LED and LCD
    digitalWrite(DRY_PIN, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Drying");
    lcd.setCursor(0,1);
    lcd.print(count);
    //wait, then count down and check if done
    delay(1000);
    count--;
    if (count == 0) {
      lcd.clear();
      digitalWrite(LOCK_PIN, LOW);
      lcd.setCursor(11,0);
      lcd.print("Done!");
      delay(750);
      washer = Idle;
      lcd.clear();
    }
  }
}
