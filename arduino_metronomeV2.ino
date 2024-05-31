// Metronome with Tempto Pot (from Arduino for Musicians)

// Constants for output of tone to speaker
const int speakerPin = 9; // 100 Ohm resistor from pin 9, to speaker +
const int frequency = 880;
const int duration = 50;

// Pot Pin:
const int potPin = 0;

//var to track pot val
int potValue;

// Variable to track tempo & time delay
unsigned int beats_per_minute = 60;
unsigned int MS_per_beat = 0;

void setup() 
{
  // Calcualte the beats_per_minute based on tempo in BPM:
  unsigned int milliseconds_per_minute = 1000 * 60;
  MS_per_beat = milliseconds_per_minute/beats_per_minute;
}

void loop() 
{
  // Check the status of the pot:
  int value = analogRead(potPin);
  // Recalculate tempo if val changes
  if(value != potValue){
    //map value to reasonable metronome range of 30 / 350 bpm
    beats_per_minute = map(value, 0, 1023, 30, 350);

    // recalc the delay timr
    unsigned int milliseconds_per_minute = 1000 * 60;
    MS_per_beat = milliseconds_per_minute/beats_per_minute;

    // update pot val:
    potValue = value;
  }  


  // output the tone
  tone(speakerPin, frequency, duration);

  // Delay loop for specified amount of time
  delay(MS_per_beat);

}
