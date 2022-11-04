### Blender Digital Twin Arduino Code in C++ 

	// Motor A connections
	int enA = 9;
	int in1 = 8;
	int in2 = 7;
	int on_btn = 0;

	int dir_btn_mode = 4;

	int speed2_btn = 12;
	int speed3_btn = 13;

	int  on_btn_state = 0;

	bool on=false;

	void setup() {
		// Set all the motor control pins to outputs
		pinMode(enA, OUTPUT);
		pinMode(in1, OUTPUT);
		pinMode(in2, OUTPUT);

	  // Set buttons to input
	  pinMode(on_btn, INPUT_PULLUP);
	  pinMode(dir_btn_mode, INPUT);
	  pinMode(speed2_btn, INPUT);
	  pinMode(speed3_btn, INPUT);


		// Turn off motors - Initial state
		digitalWrite(in1, LOW);
		digitalWrite(in2, LOW);

	  Serial.begin(9600);
	}

	void loop() {
	  on_btn_state = digitalRead(on_btn);
	  dir_btn_mode = digitalRead(dir_btn_mode); 
	  speed2_btn = digitalRead(speed2_btn);
	  speed3_btn = digitalRead(speed3_btn);

	  Serial.println(on_btn_state);
	  if(on_btn_state==0 && on==false){
	    //Serial.println("button_pressed_on");
	    setOn();
	    on=true;
	  }else if(on_btn_state==0 && on==true){
	    //Serial.println("button_pressed_off");
	    setOff();
	    on=false;
	  } 
	  delay(200);


	/*
	//------------ Changing the direction ---------------

	  Serial.println(dir_btn_mode); //pin 11
	  if(dir_btn_mode==0 && on==false){
	    directionControl();
	    on=true;
	  }else if(dir_btn_mode==0 && on==true){
	    setOff();
	    on=false;
	  } 
	  delay(200);

	*/

	}

	void setOn(){
	  Serial.println("motor on");
	  digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
	  analogWrite(enA, 255);
	}
	void setOff(){
	  Serial.println("motor off");
		analogWrite(enA, 255);
	  digitalWrite(in1, LOW);
		digitalWrite(in2, LOW);
	}


	// This function lets you control spinning direction of motors
	void directionControl() {
		// Set motors to maximum speed
		// For PWM maximum possible values are 0 to 255
	  Serial.println("direction control: motor on");
		analogWrite(enA, 255);

		// Turn on motor A & B
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
		delay(2000);

		// Now change motor directions
	  Serial.println("direction control: change direction");
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
		delay(2000);

		// Turn off motors
	  Serial.println("direction control: motor off");
		digitalWrite(in1, LOW);
		digitalWrite(in2, LOW);
	}

	/*

	// This function lets you control speed of the motors
	void speedControl() {
		// Turn on motors
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);

		// Accelerate from zero to maximum speed
	  Serial.println("speed control: accelerating");
		for (int i = 0; i < 256; i++) {
			analogWrite(enA, i);
			delay(20);
		}

		// Decelerate from maximum speed to zero
	  Serial.println("speed control: decelerating");
		for (int i = 255; i >= 0; --i) {
			analogWrite(enA, i);
			delay(20);
		}

		// Now turn off motors
		digitalWrite(in1, LOW);
		digitalWrite(in2, LOW);
	}
	*/
