/* 
 Name: Aryansingh Chauhan, Ackchat Omar
 Net ID: achauh9, aomar22
 Group/Team #: 85
 Abstract: Bored of checking when to take out the trash? Introducing a smart trash management system that eradicates the need to constantly keep on checking how much trash is occupied in the bin.
           With today’s technology, the smart trash will notify the user via different output methods that trash needs to be removed. By having the user notified without having them open the bin themselves to check trash levels,
           The aim is to reduce daily human effort and at the same time make sure trash is being removed from households rather than being collected.
 Project name: Smart Bin
 Project Description: Using ultrasonic sensors, I am calculating the trash stored in a bin and communicating it to the
                      user via different output devices so that they are aware of when to clear out the trash.
 References: https://docs.arduino.cc/built-in-examples/sensors/Ping
*/

#include <LiquidCrystal.h>
#include <string.h>

// Variables for the lcd:
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buzPin = 10;
const int ledRed = 8;
const int ledGreen = 2;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzPin, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {  // checking for connection between the 
    String received = (Serial.readStringUntil("\n"));  // storing data received in a string
    Serial.println(received);
    int trash = received.toInt();  // converting string to an integer value

    // now setting cursor positions for LCD
    lcd.setCursor(0, 0);
    lcd.print("Bin 1: ");
    lcd.print(trash);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("");

    // below if conditions are to give user output based on different levels in trash bin

    if (trash < 65) {  // trash level is okay
      Serial.println("Green should be on");
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Trash is fine !!");
      noTone(buzPin);
      delay (1000);
    }
    else if (trash >= 65 && trash < 90) {  // trash is piling up but does not necessarily need to be removed so only RED LED ON
      Serial.println("Red should be on");
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Prepare to empty");
      noTone(buzPin);
      delay (1000);
    } 
    else {  // trash is almost full. activating buzzer to inform the user to remove the trash
      Serial.println("Red and buzzer should be on");
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Empty Trash now!");
      tone(buzPin, 5000); // Send 5KHz sound signal...
      delay (1000);
    }
  }
}
