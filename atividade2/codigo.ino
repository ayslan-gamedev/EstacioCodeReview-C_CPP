#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0); // Initialize the LCD

const int tringPin = 6;
const int echoPin = 7;

void setup()
{
  lcd.begin(16, 2); // Initialize LCD with 16 columns and 2 rows
  pinMode(tringPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

static int lastDistance = 0;

void loop()
{
  // Check if distance has changed
  if(lastDistance != (int)Distance()){
	lcd.clear();
    lcd.print(Distance());
    lcd.print(" cm");
    lastDistance = (int)Distance();
  }
}

float Distance(){
  digitalWrite(tringPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(tringPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tringPin, LOW);

  return pulseIn(echoPin, HIGH) / 58.2; // Calculate and return distance in cm
}