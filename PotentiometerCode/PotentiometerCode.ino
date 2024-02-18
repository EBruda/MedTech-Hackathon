
#include <CSV_Parser.h>
char letters[26] = {'A', 'E', 'I',  'K', 'L', 'O','U'};

//pins for the display
int a=7; 
int b=6; 
int c=5; 
int d=11; 
int e=10; 
int f=8; 
int g=9; 
int dp=4; 

//pins for the LED light
int red = 3;
int blue = 2;

//CSV string with the baseline potentiometer values (generated from an Excel File)
char * csv_str = "PotOne,PotTwo\n"
"Pot1,Pot2\n"
"0,731\n" //A
"0,754\n" //E
"0,755\n" //I
"568,1023\n" //K
"1023,1023\n" //L
"575,833\n" //O
"38,1023\n"; //U

CSV_Parser cp(csv_str, /*format*/ "LL");

//retrieving parsed values (and casting them to correct types,
//corresponding to format string provided in constructor above)
int32_t   *potone =           (int32_t*)cp["PotOne"];
int32_t   *pottwo =           (int32_t*)cp["PotTwo"];
//for csv: A = 1, B = 2,....Z = 26

//Functions for displaying different numbers on the display
void display1(void) {
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
} 

void display2(void) {
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);

  digitalWrite(g,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(d,HIGH);
}
  
void display3(void) { 
  digitalWrite(a,HIGH);

  digitalWrite(b,HIGH);
    
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);

  digitalWrite(g,HIGH);
} 

void display4(void) {
  
  digitalWrite(f,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
} 

void display5(void) { 
  digitalWrite(a,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
} 

void display6(void) { 
  digitalWrite(a,HIGH);
  digitalWrite(f,HIGH);

  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);

  digitalWrite(e,HIGH);  
} 

void display7(void) {   
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}
  

void display8(void) { 
  digitalWrite(a,HIGH);

  digitalWrite(b,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(c,HIGH);

  digitalWrite(d,HIGH);  
  digitalWrite(e,HIGH);  
  digitalWrite(f,HIGH);
  
} 

void display9(void) { 
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g,HIGH);

  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);  
  digitalWrite(f,HIGH);
  
} 

void display0(void) { 
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);

  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);  
  digitalWrite(e,HIGH);
  
  digitalWrite(f,HIGH);  
} 

void clearDisplay(void) { 
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);

  digitalWrite(g,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);  

  digitalWrite(e,LOW);  
  digitalWrite(f,LOW);  
} 

//Setup function
void setup() {
  Serial.begin(9600);
  //sets the pins to output
  int i;
  for(i=4;i<=11;i++) {
    pinMode(i,OUTPUT);
  }

  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);

  //prints out the baseline potentiometer values
  for (int i = 1; i < 8; i++) {
      Serial.print(letters[i - 1]);
      Serial.print(" - ");
      Serial.print(potone[i]);              
      Serial.print(" - ");
      Serial.print(pottwo[i]);              
      Serial.println(" ");
  }
}

void loop() {
  
  //waits for an input from the user
  if(Serial.available() > 0)  {
  
    char incomingData= (char)Serial.read(); // can be -1 if read error
    
    //gets the index of the letter in the array (ex: A = 0, B = 1, etc)
    int letter_index = 0;
    for (int i=0; i<8; i++) {  
      if (incomingData == letters[i]) {
        // Serial.println(letters[i]);
        // Serial.println("Letter index: ");
        // Serial.println(i);
        letter_index = i;
        break;
      }
    }
    
  
    //Read from analog pin 0
    //Value should range from 0-1023
    int32_t pot1 = analogRead(A1); //actual potentiometer reading for sensor 1
    int32_t pot2 = analogRead(A2); //actual potentiometer reading for sensor 2
    int32_t pot1_ground_truth = potone[letter_index + 1];
    int32_t pot2_ground_truth = pottwo[letter_index + 1];


    // PD: (abs(Exp - Tru)) / ((Exp + Tru)/ 2) * 100
    //closeness formula 
    //calculates how close you are from 0 to 9
    int d1 = max( abs(1023-pot1_ground_truth), abs(pot1_ground_truth - 0));
    double pot1_percent_error = (abs(d1-abs(pot1_ground_truth - pot1)) / (double)d1) * 10;
    int pot1_close_int = (int) (pot1_percent_error);
    // Serial.println(pot1_close_int);

    int d2 = max( abs(1023-pot2_ground_truth), abs(pot2_ground_truth - 0));
    double pot2_percent_error = (abs(d2-abs(pot2_ground_truth - pot2)) / (double)d2) * 10;
    int pot2_close_int = (int)(pot2_percent_error);


    // Print Potentiometer Vvalue
    Serial.print("Pot1: ");
    Serial.print(pot1);
    Serial.println(" ");
    Serial.print("Percent1: ");
    Serial.print(pot1_percent_error * 10);
    Serial.println(" ");

    Serial.print("Pot2: ");
    Serial.print(pot2);
    Serial.println(" ");
    Serial.print("Percent2: ");
    Serial.print(pot2_percent_error * 10);
    Serial.println(" ");
    //displays the closeness number on the display
    switch (pot1_close_int) {
      case 0:
        display0();
        break;
      case 1:
        display1();
        break;
      case 2:
        display2();
        break;
      case 3:
        display3();
        break;
      case 4:
        display4();
        break;
      case 5:
        display5();
        break;
      case 6:
        display6();
        break;
      case 7:
        display7();
        break;
      case 8:
        display8();
        break;
      case 9:
        display9();
        break;
    }
    //LED code for knowing which display is for which sensor:
    digitalWrite(red, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(red, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second

    digitalWrite(blue, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(blue, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
  }
    // delay(500);  //Delay in between reads for stability
  
}

  
