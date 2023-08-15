const int pinLedOutput = 8;
const int pinButtonInput = 13;

// Initialize Arduino board 
void setup()
{
  // sets the pins modes
  pinMode(pinButtonInput, INPUT);
  pinMode(pinLedOutput, OUTPUT);
}

// Update constatly
void loop()
{
  int currentButtonValue = digitalRead(pinButtonInput); // get the button (ON/OFF)
  
  if(currentButtonValue == 1){
    int ledStatus = digitalRead(pinLedOutput); // get the current led value (1/0)
    digitalWrite(pinLedOutput, !ledStatus); // set the new led value (reverse)
    delay(200);
  } 
}