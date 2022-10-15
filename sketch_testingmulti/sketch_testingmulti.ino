// Uses a PIR sensor to detect movement, buzzes a buzzer
// more info here: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/
//
// based upon:
// PIR sensor tester by Limor Fried of Adafruit
// tone code by michael@thegrebs.com
// Digital 4 – controls RELAY4’s COM4 pin (located in J4)
// Digital 5 – controls RELAY3’s COM3 pin (located in J3)
// Digital 6 – controls RELAY2’s COM2 pin (located in J2)
// Digital 7 – controls RELAY1’s COM1 pin (located in J1)
//Only four Arduino Digital I/O pins, pins 4-7, are required to control the four different relays. 
//Additionally the 5V and two GND Arduino pins are also required to power up the Relay Shield


int relay1pin = 7;
int relay2pin = 6; 
int relay3pin = 5;
int relay4pin = 4;

int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int input2Pin = 3;              // choose the input pin (for PIR sensor 2)
int pirState = LOW;             // we start, assuming no motion detected
int pir2State = LOW;
int val = 0;                    // variable for reading the pin status
int lights = 0;

int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     
  pinMode(input2Pin, INPUT);                              // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);
  pinMode(relay1pin, OUTPUT);
  pinMode(relay2pin, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  val = digitalRead(inputPin);  // read input value
  lights = digitalRead(input2Pin);
  
  if (val == HIGH) {// check if the input is HIGH
    digitalWrite(relay2pin, HIGH); //turn Skelecat ON
    digitalWrite(ledPin, HIGH);  // turn LED ON
    playTone(300, 860);
    delay(150);

    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
    }
  else {
      digitalWrite(relay2pin, LOW); //turn Skelecat OFF
      digitalWrite(ledPin, LOW); // turn LED OFF
      playTone(0, 0);
      delay(300);    
      if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
    //CONTROL LIGHT PUSHBUTTON
    if (lights == HIGH) {            // check if the input is HIGH
    digitalWrite(relay1pin, HIGH);  // turn LIGHTS ON
        
    if (pir2State == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pir2State = HIGH;
      }
    } 
   else {
      digitalWrite(relay1pin, LOW); // turn LED OFF
         
      if (pir2State == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pir2State = LOW;
    }
    
   }    
  }  
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}


