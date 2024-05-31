//Arduino for Musicians
//Listing 4.9: Metronome 3 (Complete Metronome)

//Constants for output of tone to speaker
const int speakerPin = 9;
const int frequency = 880;
const int duration = 50;

//Potentiometer pin:
const int potPin = 0;

//Variable to track the value of the pot
int potValue;

//Switch pin:
const int pushButtonPin = 2 ;

//Variable to track pushbutton status
int pushButtonStatus = HIGH;

//A boolean variable to track if metronome is on or off:
boolean on = false;

//Variables to track tempo and time delay
unsigned int beats_per_minute = 60;
unsigned int MS_per_beat = 0;

//Variable to track time
long last_time = 0;

void setup()
{
    //Set the digital pin for input and pullup resistor:
    pinMode(pushButtonPin, INPUT_PULLUP);
    
    //Calculate MS_per_beat based on tempo in BPM
    unsigned int milliseconds_per_minute = 1000 * 60;
    MS_per_beat = milliseconds_per_minute/beats_per_minute;
}

void loop()
{
    checkPushButton();
    checkPot();
    
    //Play a tone if the metronome is on.
    long current_time = millis();
    if((current_time - last_time >= MS_per_beat) && on == true)
    {
        //Output the tone
        tone(speakerPin, frequency, duration);
        last_time = current_time;
    }
    
}

void checkPot()
{
    //Check the status of the potentiometer:
    int value = analogRead(potPin);
    
    //Re-calculate the tempo if the value has changed.
    if(value != potValue)
    {
        //Map the value to a reasonable metronome range of 30 BPM to 350 BPM
        beats_per_minute = map(value, 0, 1023, 30, 350);
        
        //Recalculate the delay time
     	 unsigned int milliseconds_per_minute = 1000 * 60;
	   MS_per_beat = milliseconds_per_minute/beats_per_minute;
        
        //Update potValue
        potValue = value;
        
    }
}

void checkPushButton()
{
    //Check digital pin 2 for a button press
    int button_state = digitalRead(pushButtonPin);
    
    //Check for button press
    if(button_state == LOW && button_state != pushButtonStatus)
    {
        //Swap on/off states
        on =! on;
        
        //update buttonStatus;
        pushButtonStatus = button_state;
        //Use delay for a kludgy form of debouncing
        delay(20);
    }
    //Check for button release
    if(button_state == HIGH && button_state != pushButtonStatus)
    {
        //Updtate the pushbutton status to off
        pushButtonStatus = button_state;
        delay(20);
    }
}

