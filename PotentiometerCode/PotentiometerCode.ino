
#include <CSV_Parser.h>

//The setup routine runs once when you press reset
void setup() {
  Serial.begin(9600);
  //Define a tolerance +- a percent
  int tolerance = 5;
}

void loop() {
  
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
  //Serial.println(csv_str);
  CSV_Parser cp(csv_str, /*format*/ "LL");

  //retrieving parsed values (and casting them to correct types,
  //corresponding to format string provided in constructor above)
  // char    *strings =         (char*)cp["letter"];
  //Serial.println(**strings);
  // int16_t *ints =           (int16_t*)cp["my_ints"];
  // char    *chars =             (char*)cp["my_chars"];
  int32_t   *potone =           (int32_t*)cp["PotOne"];
  // Serial.println("potone");
  int32_t   *pottwo =           (int32_t*)cp["PotTwo"];
  
  // //Serial.println((char)cp.getRowsCount());
  // Serial.print((char)strings[21]);             
  // Serial.print(" - ");
  // // Serial.print(longs[i], DEC);          Serial.print(" - ");
  // // Serial.print(ints[i], DEC);           Serial.print(" - ");
  // // Serial.print(chars[i], DEC);          Serial.print(" - ");
  // Serial.print(potone[21]);              
  // Serial.print(" - ");
  // Serial.print(pottwo[21]);              
  // Serial.print(" - ");
                      //0
  char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  for (int i = 1; i < 27; i++) {
      Serial.print(letters[i - 1]);
      Serial.print(" - ");
      Serial.print(potone[i]);              
      Serial.print(" - ");
      Serial.print(pottwo[i]);              
      // Serial.print(longs_from_hex[i], HEX); Serial.println();
      Serial.println(" ");
  }

  // if(Serial.available() > 0)  {
  //   char incomingData= Serial.read(); // can be -1 if read error


  //   int letter_index;
  //   for (int i=0; i<26; i++) {
  //     if (incomingData = letters[i]) {
  //       letter_index = i;
  //       break;
  //     }
  //   }
    
  //   //Min and Max readings for potentiometer
  //   const int min = 0;
  //   const int max = 1023;
  //   //go from percentage to what letter you are doing
  //   //Read from analog pin 0
  //   //Value should range from 0-1023
  //   int pot1 = analogRead(A1);
  //   int pot2 = analogRead(A2);



  //   //Make a percent reading off min and max values
  //   double percent1 = (double)pot1 / (max - min) * 100;
  //   double percent2 = (double)pot2 / (max - min) * 100;


    //Print Potentiometer Vvalue
    // Serial.print("Pot1: ");
    // Serial.print(pot1);
    // Serial.println(" ");
    // Serial.print("Percent1: ");
    // Serial.print(percent2);
    // Serial.println(" ");
    // Serial.println(" ");

    // Serial.print("Pot2: ");
    // Serial.print(pot2);
    // Serial.println(" ");
    // Serial.println(" ");
    // Serial.print("Percent2: ");
    // Serial.print(percent2);
    // Serial.println(" ");

    //delay(500);  //Delay in between reads for stability

  }
  delay(500);
  
}