//The setup routine runs once when you press reset
void setup() {
  //Initialize serial moniter to read output
  Serial.begin(9600);

  

  //Define a tolerance +- a percent
  int tolerance = 5;
}

void loop() {
  //Min and Max readings for potentiometer
  const int min = 0;
  const int max = 1023;

  //Read from analog pin 0
  //Value should range from 0-1023
  int pot = analogRead(A0);

  //Make a percent reading off min and max values
  double percent = (double)pot / (max - min) * 100;



  

  //Print Potentiometer Vvalue
  Serial.print("Pot: ");
  Serial.print(pot);
  Serial.println(" ");
  Serial.print("Percent: ");
  Serial.print(percent);
  Serial.println(" ");

  delay(30);  //Delay in between reads for stability
}