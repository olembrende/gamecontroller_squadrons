#include <Arduino.h>
#include <Keypad.h>
#include <Joystick.h>

//DEFINITIONS
#define ENABLE_PULLUPS
#define NUMBUTTONS 9 //replace "?"with number of buttong you are using
#define NUMROWS 3 //replace "?" with number of rows you have
#define NUMCOLS 3 //replace "?" with number of columns you have


void CheckAllButtons(void);

//BUTTON MATRIX
//first change number of rows and columns to match your button matrix, 
//then replace all "?" with numbers (starting from 0)
byte buttons[NUMROWS][NUMCOLS] = {
  {1,2,3},
  {4,9,5},
  {6,7,8}
};

//BUTTON MATRIX PART 2
byte rowPins[NUMROWS] = {6,7,8}; //change "?" to the pins the rows of your button matrix are connected to
byte colPins[NUMCOLS] = {3,4,5}; //change "?" to the pins the rows of your button matrix are connected to

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

// Create the Joystick
//Joystick_ Joystick;
//JOYSTICK SETTINGS
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  9, //number of buttons
  0, //number of hat switches
  //Set as many axis to "true" as you have potentiometers for
  true, // y axis
  true, // x axis
  false, // z axis
  false, // rx axis
  false, // ry axis
  false, // rz axis
  false, // rudder
  false, // throttle
  false, // accelerator
  false, // brake
  false); // steering wheel

// Constant that maps the physical pin to the joystick button.
const int pinToButtonMap = 2;
const int XPin = A5;
const int YPin = A4;
int range = 1023;
int center = 0;

void setup() {
	// Initialize Button Pins
	pinMode(pinToButtonMap, INPUT_PULLUP);
  pinMode(XPin, INPUT);
  pinMode(YPin, INPUT);

	// Initialize Joystick Library
	Joystick.begin();
}

// Last state of the button
int lastButtonState = 0;

void loop() {

	// Read pin values
	int currentButtonState = !digitalRead(pinToButtonMap);
	if (currentButtonState != lastButtonState){
	  Joystick.setButton(0, currentButtonState);
	  lastButtonState = currentButtonState;
	}

	CheckAllButtons();

  double xpin_value = analogRead(XPin);
  xpin_value = map(xpin_value, 0, 1023, 0, range);
  Joystick.setXAxis(xpin_value);

  double ypin_value = analogRead(YPin);
  ypin_value = map(ypin_value, 0, 1023, 0, range);
  Joystick.setYAxis(ypin_value);

	delay(50);
}

void CheckAllButtons(void){
	if (buttbx.getKeys()){
		for (int i=0; i<LIST_MAX; i++){
			if ( buttbx.key[i].stateChanged ){
				switch (buttbx.key[i].kstate){ 
					case PRESSED:
					case HOLD:
						Joystick.setButton(buttbx.key[i].kchar, 1);
						break;
					case RELEASED:
					case IDLE:
						Joystick.setButton(buttbx.key[i].kchar, 0);
						break;
				}
			}   
		}
	}
}
