#include <TM1637Display.h>
#include <Servo.h>
TM1637Display display = TM1637Display(3, 2);
Servo mixer;
unsigned long int initial=1000; //duration of first agitation
unsigned long int interval=1000; //interval agitation every 60 seconds
unsigned long int agit=1000; //substequent agitations 10 seconds
unsigned long int devt=60000; //overall development time
unsigned long int t0; // here time of start will be stored
unsigned long int secs; // here number of seconds on display will be stored
bool lop;
void times(unsigned long int a,unsigned long int b, unsigned long int c,unsigned long int d) {
  initial*=a;
  interval*=b;
  agit*=c;
  devt*=d;  
  lop=false;
}
void beep() {
  while (1) {
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
    }
}

void setup() {
pinMode(4,OUTPUT); // buzzer on pin 4
pinMode(8,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);
mixer.attach(5); // servo on pin 5
display.setBrightness(7);
display.clear();
lop=true;
while (lop) {
//                           init intvl agit devt
//if (digitalRead(8)==LOW) times(30,60,10,9); //lqn
if (digitalRead(8)==LOW) times(10,60,6,15); //caffenol
if (digitalRead(7)==LOW) times(30,30,5,6);
if (digitalRead(6)==LOW) times(5,30,5,5);
}
t0=millis();

}

void loop() {
  if ((millis()-t0)>devt) beep();
  if (((millis()-t0)%interval)<agit || (millis()-t0)<initial) {
    if (((millis()-t0)%2000)<1000) mixer.write(180);
    else mixer.write(0);
  }
  secs=(t0+devt-millis())/1000;
  display.showNumberDecEx((secs/60)*100+(secs%60), 0b01000000, false);
  
}
