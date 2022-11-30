// Motor connections
int enA = 9;
int in1 = 8;
int in2 = 7;
int on_btn = 2;
int speed1_btn = 11;
int speed2_btn = 12;
int speed3_btn = 13;

//declaring initial button states
int  on_btn_state = 0;
int  speed1_btn_state = 0;
int  speed2_btn_state = 0;
int  speed3_btn_state = 0;

//declaring if blender is on or off
bool on=false;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

  // Set buttons to input
  pinMode(on_btn, INPUT_PULLUP);
  pinMode(speed1_btn, INPUT_PULLUP);
  pinMode(speed2_btn, INPUT_PULLUP);
  pinMode(speed3_btn, INPUT_PULLUP);

	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

  Serial.begin(9600);
}

void loop() {
  //read button states
  on_btn_state = digitalRead(on_btn);
  speed1_btn_state = digitalRead(speed1_btn);
  speed2_btn_state = digitalRead(speed2_btn);
  speed3_btn_state = digitalRead(speed3_btn);
  
  //Active low; if buttons are pressed
  if(on_btn_state==0 && on==false){
    setOn();
    on=true;
  }else if(on_btn_state==0 && on==true){
    setOff();
    on=false;
  }else if(speed1_btn_state==0 && on==true){
    setSpeed1();
  }else if(speed2_btn_state==0 && on==true){
    setSpeed2();
  }else if(speed3_btn_state==0 && on==true){
    setSpeed3();
  }
  delay(300);
}
 
//turn the blender on
void setOn(){
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
  analogWrite(enA, 85);
}

//turn the blender off
void setOff(){
	analogWrite(enA, 85);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}

//set speed setting 1
void setSpeed1(){
	analogWrite(enA, 85);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

//set speed setting 2
void setSpeed2(){
	analogWrite(enA, 170);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}

//set speed setting 3
void setSpeed3(){
	analogWrite(enA, 255);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}