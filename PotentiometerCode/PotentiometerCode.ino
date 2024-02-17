
#include <CSV_Parser.h>
char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
String letters2[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
//A: D2
//B: D3
int a=7; 
int b=6; 
int c=5; 
int d=11; 
int e=10; 
int f=8; 
int g=9; 
int dp=4; 

int red = 3;
int blue = 2;


  //The setup routine runs once when you press reset
  //Define a tolerance +- a percent
  int tolerance = 5;
  
  char * csv_str = "PotOne,PotTwo\n"
  "Pot1,Pot2\n"
  "683,1023\n"
  "406,697\n"
  "333,410\n"
  "935,897\n"
  "648,360\n"
  "674,544\n"
  "846,552\n"
  "562,352\n"
  "37,800\n"
  "740,202\n"
  "956,743\n"
  "77,958\n"
  "609,973\n"
  "537,427\n"
  "353,38\n"
  "549,253\n"
  "123,55\n"
  "92,646\n"
  "365,303\n"
  "20,11\n"
  "771,628\n"
  "575,656\n"
  "706,66\n"
  "288,55\n"
  "877,509\n"
  "82,728\n";
  CSV_Parser cp(csv_str, /*format*/ "LL");

  //retrieving parsed values (and casting them to correct types,
  //corresponding to format string provided in constructor above)
  int32_t   *potone =           (int32_t*)cp["PotOne"];
  int32_t   *pottwo =           (int32_t*)cp["PotTwo"];
  //for csv: A = 1, B = 2,....Z = 26

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
void setup() {
  Serial.begin(9600);
  int i;
  for(i=4;i<=11;i++) {
    pinMode(i,OUTPUT);
  }

  //led code:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);


  //for csv: A = 1, B = 2,....Z = 26
  for (int i = 1; i < 27; i++) {
      Serial.print(letters[i - 1]);
      Serial.print(" - ");
      Serial.print(potone[i]);              
      Serial.print(" - ");
      Serial.print(pottwo[i]);              
      // Serial.print(longs_from_hex[i], HEX); Serial.println();
      Serial.println(" ");
  }
}

void loop() {
  //Serial.println("check");
  

  if(Serial.available() > 0)  {

    
    char incomingData= (char)Serial.read(); // can be -1 if read error
    // Serial.println(incomingLetter);
    int letter_index = 0;
    for (int i=0; i<26; i++) {  
      // Serial.println(incomingData.c_str()[0]);
      // Serial.println(letters2[i].c_str())[0];

      if (incomingData == letters[i]) {
        //Serial.println(incomingLetter);
        Serial.println(letters[i]);
        Serial.println("Letter index: ");
        Serial.println(i);
        letter_index = i;
        break;
      }
    }
    
    //Min and Max readings for potentiometer
    // const int min = 0;
    // const int max = 1023;
    //go from percentage to what letter you are doing
    //Read from analog pin 0
    //Value should range from 0-1023
    int32_t pot1 = 1000;
    int32_t pot2 = analogRead(A2);
    int32_t pot1_ground_truth = potone[letter_index + 1];
    int32_t pot2_ground_truth = pottwo[letter_index + 1];
    Serial.println(pot1_ground_truth);
    Serial.println(pot2_ground_truth);
    //make a double for integer division error reasons
    // (Exp - Tru) / Tru
    // PD: (abs(Exp - Tru)) / ((Exp + Tru)/ 2) * 100
    //closeness formula - they want a higher number
    int d1 = max( abs(1023-pot1_ground_truth), abs(pot1_ground_truth - 0));
    double pot1_percent_error = (abs(d1-abs(pot1_ground_truth - pot1)) / (double)d1) * 10;
    int pot1_close_int = round(pot1_percent_error);
    Serial.println(pot1_close_int);

    int d2 = max( abs(1023-pot2_ground_truth), abs(pot2_ground_truth - 0));
    double pot2_percent_error = (abs(d2-abs(pot2_ground_truth - pot2)) / (double)d2) * 10;
    int pot2_close_int = round(pot2_percent_error);
    Serial.println(pot2_close_int);
    // int pot2_num_int = (int) pot1_num;

    // Serial.println(pot2_num);


    // Print Potentiometer Vvalue
    Serial.print("Pot1: ");
    Serial.print(pot1);
    Serial.println(" ");
    Serial.print("Percent1: ");
    Serial.print(pot1_close_int);
    Serial.println(" ");

    Serial.print("Pot2: ");
    Serial.print(pot2);
    Serial.println(" ");
    Serial.print("Percent2: ");
    Serial.print(pot2_close_int);
    Serial.println(" ");

    switch (pot2_close_int) {
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
    //LED code:
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

  
