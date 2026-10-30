#include <LiquidCrystal_I2C_Hangul.h>



LiquidCrystal_I2C_Hangul lcd(0x27, 16, 2);

int ledpin_red1 = 8;        // נערך את פין 2 כפלט עבור האורות האדומים
int ledpin_red2 = 11;
int ledpin_blue1 = 9;       // נערך את פין 3 כפלט עבור האורות הכחולים
int ledpin_blue2 = 12;
int slideswitch = 13;       // מתג ההחלפה המחובר לפין 13
int buzzer = 10;            // הזמר המחובר לפין 10
int val_switch = 0;         // משתנה לאחסון מצב המתג המחובר
int sensorpin = 7;          // פין החיישן
int tilt = 6;

void setup() {
  pinMode(ledpin_red1, OUTPUT);
  pinMode(ledpin_red2, OUTPUT);
  pinMode(ledpin_blue1, OUTPUT);
  pinMode(ledpin_blue2, OUTPUT);
  pinMode(slideswitch, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorpin, INPUT);
  pinMode(tilt, INPUT);
  
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  val_switch = digitalRead(slideswitch); //read on off
  
  if (val_switch == HIGH) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM ARM");
    delay(1000);
    
    int val_sensor = digitalRead(sensorpin);
    int val_tilt = digitalRead(tilt);

    if (val_sensor == HIGH || val_tilt == LOW) {  //if tilt in upside down print alarm on
      lcd.setCursor(0, 1);
      lcd.print("!!! ALARM ON !!!");
      if (val_sensor == HIGH) {
        lcd.setCursor(0, 0);
        lcd.print(" PIR SENSOR ON");
      }
      if (val_tilt == LOW) {  //if tilt in its normal position print its on
        lcd.setCursor(0, 0);
        lcd.print(" TILT SENSOR ON");
      }
      digitalWrite(ledpin_red1, HIGH);
      digitalWrite(ledpin_red2, HIGH);
      digitalWrite(ledpin_blue1, LOW);
      digitalWrite(ledpin_blue2, LOW);
      tone(buzzer, 1000);
      delay(500);
      digitalWrite(ledpin_red1, LOW);
      digitalWrite(ledpin_red2, LOW);
      digitalWrite(ledpin_blue1, HIGH);
      digitalWrite(ledpin_blue2, HIGH);
      delay(500);
      noTone(buzzer);
    } else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("                "); // Clear second line
      lcd.setCursor(0, 0);
      lcd.print("                "); // Clear first line
      digitalWrite(ledpin_red1, LOW);
      digitalWrite(ledpin_red2, LOW);
      digitalWrite(ledpin_blue1, LOW);
      digitalWrite(ledpin_blue2, LOW);
      noTone(buzzer);
    }
  } else {
    digitalWrite(ledpin_red1, LOW);
    digitalWrite(ledpin_red2, LOW);
    digitalWrite(ledpin_blue1, LOW);
    digitalWrite(ledpin_blue2, LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.print("SYSTEM OFF");
    delay(1000);
  }
}
