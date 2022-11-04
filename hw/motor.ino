// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

int on_btn = 0;
int dir_btn = 11;
int speed2_btn = 12;
int speed3_btn = 13;

int on_btn_state = 0;
int dir_btn_state = 11;
int speed2_btn_state = 12;
int speed3_btn_state = 13;

bool on=false;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

  // Set buttons to input
  pinMode(on_btn, INPUT_PULLUP);
  pinMode(dir_btn, INPUT_PULLUP);
  pinMode(speed2_btn, INPUT_PULLUP);
  pinMode(speed3_btn, INPUT_PULLUP);

	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

  Serial.begin(9600);
}


//------------ Turn ON/OFF ------------------------
void loop() {
  on_btn_state = digitalRead(on_btn);
  dir_btn_state = digitalRead(dir_btn); 
  speed2_btn_state = digitalRead(speed2_btn);
  speed3_btn_state = digitalRead(speed3_btn);

  Serial.println(on_btn_state); //pin 0
  if(on_btn_state==0 && on==false){
    setOn();
    on=true;
  }else if(on_btn_state==0 && on==true){
    setOff();
    on=false;
  }
  delay(100);

  //------- Changing the direction ------

  Serial.println(dir_btn_state); //pin 11
  if(dir_btn_state==0 && on==false){
    directionControl();
    on=true;
  }else if(dir_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);

  //------------ Speed: slow ---------------
  Serial.println(speed3_btn_state); //pin 13
  if(speed3_btn_state==0 && on==false){
    speedSlowControl();
    on=true;
  }else if(speed3_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);

  //------------ Speed: fast ---------------
  Serial.println(speed2_btn_state); //pin 11
  if(speed2_btn_state==0 && on==false){
    speedFastControl();
    on=true;
  }else if(speed2_btn_state==0 && on==true){
    setOff();
    on=false;
  } 
  delay(100);
  //end
}


//This function lets you turn on the motor
void setOn(){
  Serial.println("motor on");
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  analogWrite(enA, 255);
}

//This function lets you stop the motor
void setOff(){
  Serial.println("motor off");
	analogWrite(enA, 255);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}


// This function lets you control spinning direction of motors
void directionControl() {
	// Now change motor directions
  Serial.println("direction control: change direction");
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	delay(2000);
}


// This function lets you control speed of the motors
void speedFastControl() {
  Serial.println("Speed Control: Accelerating");
	for (int i = 0; i < 256; i++) {
		analogWrite(in1, i);
	}
}

// This function lets you control speed of the motors
void speedSlowControl() {
  Serial.println("Speed Control: Decelerating");
	for (int i = 255; i >= 0; --i) {
		analogWrite(in1, i);
		delay(20);
	}
}