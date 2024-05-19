// Metronome (from Arduino for Musicians)

// Constants for output of tone to speaker
const int speakerPin = 9;
const int frequency = 880;
const int duration = 50;

// Variable to track time delay
unsigned int MS_per_beat = 0;

void setup() {
  // Calcualte the amount of delay:
  // milliseconds per min/beats per min
  unsigned int milliseconds_per_minute = 1000 * 60;
  unsigned int beats_per_minute = 60;
  MS_per_beat = milliseconds_per_minute/beats_per_minute;

}

void loop() {
  // output the tone
  tone(speakerPin, frequency, duration);

  // Delay loop for specified amount of time
  delay(MS_per_beat);

}
