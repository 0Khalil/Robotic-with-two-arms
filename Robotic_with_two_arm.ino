int chos;
int L1=30; 
int L2=15; 
float Q1, Q2,m; 
float x,y,q1,q2; 
int Q=50; 
#include <Servo.h> 
Servo moto1; 
Servo moto2;
#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 3;  
char hexaKeys[ROWS][COLS] = {
{'1','2','3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{' ', '0', ' '}
};
byte rowPins[ROWS] = {A2, A3, A4, A5};
 byte colPins[COLS] = {5, 6, 7}; 
Keypad customKeypad = Keypad ( makeKeymap (hexaKeys), rowPins, colPins, ROWS, COLS);
#include <LiquidCrystal.h>
 const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8; 
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

void setup() {
 moto1.attach (3); 
 moto2.attach (4); 
 lcd.begin(16, 2); 
 lcd.print(" Welcome to"); 
  lcd.setCursor(0,1);
// go to next line 
  lcd.println("control Arm"); 
  delay(3000);
}
 void forward() {
//this function to calculate 01 &Q2
      moto1.write (q1); 
      moto2.write (q2);
      lcd.clear(); 
      Q1=q1*PI/180; 
      Q2=q2*PI/180;
      x=(L1*cos(Q1)) + (L2*cos(Q1+Q2));
      y=(L1*sin(Q1)) + (L2*sin(Q1+Q2));
      lcd.print("End point of arm");
      lcd.setCursor(5,1);
      lcd.print(":"); 
      lcd.setCursor(0,1);
      lcd.print(x);
      lcd.setCursor(6,1);
      lcd.print(y); 
      Serial.print("Q1"); 
      Serial.println(q1); 
      Serial.print("Q2"); 
      Serial.println(q2); 
      delay (7000);
    }




  void invers() {
// this fuction to determine ending point of arm depending on value of x, y 
      lcd.clear();
      m= (pow(x,2)+pow(y,2)-pow(L1,2)-pow(L2,2))/(2*L1*L2);
      q2=acos (m); 
      Q2=q2*180/PI;
      Q1=Q-Q2; 
      lcd.print("Angle of Arm:");
      lcd.setCursor(0,1); 
      lcd.print("Q1="); 
      lcd.print(Q1); 
      lcd.setCursor(8,1); 
      lcd.print("&"); 
      lcd.setCursor(9,1); 
      lcd.print("Q2=");
      lcd.print(Q2); 
      Serial.print(Q1); 
      moto1.write (Q1); 
      moto2.write (Q2); 
      delay (7000);
    };


void loop() {
lcd.clear(); //clear word on lcd 
chos=FI(); 
if (chos==1) {
int g1=0,g2=0;
int h1=0,h2=0;
  lcd.clear(); 
  lcd.print("Enter anlgle Q1");
  while (g1==0) {g1=customKeypad.getKey(); } //wait user to enter first number of 01 
  lcd.setCursor(0,1); 
  g1=g1-48; // change number from ASCII 
  lcd.print (g1); // show nubmer in lcd
  while (g2==0) {g2=customKeypad.getKey(); } //wait user to enter second number of Q1 
  g2=g2-48;
  lcd.print(92); 
  delay(500); 
  q1=g1*10+g2; // sum gl & g2 
  lcd.clear();
  lcd.print("Enter anlgle Q2");
  while (h1==0) {h1=customKeypad.getKey();}
  h1=h1-48; 
  lcd.setCursor(0,1); 
                 lcd.print (h1);
                 while (h2==0) {h2=customKeypad.getKey(); }
                 h2=h2-48; 
                 lcd.print (h2); 
                 delay(500); 
                 q2=h1*10+h2; 
                 forward(); // call forward function
                 } 
  else if (chos==2) {
    int u1=0, u2=0; 
    int r1=0, r2=0; 
    lcd.clear();
    lcd.print("Enter value of x"); 
    while (u1==0) {u1=customKeypad.getKey(); } 
    u1=u1-48; 
    lcd.setCursor(0,1); 
    lcd.print (u1); 
    while (u2==0) {u2=customKeypad.getKey(); }
    u2=u2-48; 
    lcd.print (u2); 
    delay(500); 
    x=u1*10+u2; 
    lcd.clear(); 
    lcd.print("Enter value of Y"); 
    while (r1==0) {r1=customKeypad.getKey(); }
    r1=r1-48; 
    lcd.setCursor(0,1); 
    lcd.print (r1); 
    while (r2==0) {r2=customKeypad.getKey(); }
    r2=r2-48; 
    lcd.print (r2); 
    delay(500);
    y=r1*10+r2; 
    invers(); }
}
  int FI() {
// this function to let the user choose type of control the arm forward/inverse kinema 
    char kp=0; 
    moto1.write(0);
    moto2.write(0); 
    lcd.clear(); 
    lcd.print("Press 1 forward "); 
    lcd.setCursor(0,1); 
    lcd.print("or 2 for Inverse"); 
    while (kp==0) { kp = customKeypad.getKey(); } 
    kp=kp-48;
    if (kp==1) {
lcd.clear();
      lcd.print("Forward Kinematic");
      lcd.setCursor(0,1); 
      lcd.print(1); 
      delay (2000);
return 1; } 
    else if (kp==2) {
lcd.clear();
      lcd.print("Inverse Kinemitic");
      lcd.setCursor(0,1); 
      lcd.print (2); 
      delay (2000); 
      return 2; }
  }
