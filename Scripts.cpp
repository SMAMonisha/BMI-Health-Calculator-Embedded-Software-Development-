#include<LiquidCrystal.h>
#define FORCE_SENSOR_PIN A0 // the FSR and 10K pulldown are connected to A0
const int trigPin = 12;
const int echoPin = 11;
double distanceCm;
long duration;
double height;
double bmi;
double analogReadingWeight;
double w1;

const int rs = 2;
const int en = 3;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode (FORCE_SENSOR_PIN, INPUT);
  lcd.begin(16, 2);
  pinMode(A1, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.print("BMI Measure");
  delay(2000);
  lcd.clear();
}

void loop() {
 lcd.setCursor(0, 0);
   /*double analogReading = analogRead(FORCE_SENSOR_PIN);
  double newton = exp((analogReading-555.53)/156.34);
  double analogReadingWeight = 446-(100*(newton*.224));
  analogReadingWeight = analogReadingWeight / 2.205;

  Serial.print("Weight := ");
  Serial.print(analogReadingWeight);
  Serial.println(" kg");*/
   double analogReading = analogRead(FORCE_SENSOR_PIN);
  double newton = exp((analogReading-555.53)/156.34);
  double analogReadingWeight = 446-(100*(newton*.224));
  analogReadingWeight = analogReadingWeight / 2.205;

  Serial.print("Weight := ");
  Serial.print(analogReadingWeight);
  Serial.println(" kg");
  

  //Distance Formulas
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.0340 / 2;
  //height = ( distanceCm);
  delay(1000);
  double HeightCm=334.00 - distanceCm;
  Serial.print("Height := ");
  Serial.print(HeightCm);
  Serial.println(" cm");

  bmi = analogReadingWeight / ((HeightCm/100)*(HeightCm/100));
  Serial.print("BMI = ");
  Serial.println(bmi);	

  delay(1000);  
  
  lcd.print(HeightCm);
  lcd.print("cm ");
  lcd.print(analogReadingWeight);
  lcd.print("kg");
  lcd.setCursor(0, 1);
  lcd.print("BMI = ");
  lcd.print(bmi);
	
  /*
  delay(3000);
  for (int positionCounter = 0; positionCounter < 1; positionCounter++) {
    lcd.scrollDisplayLeft(); // scroll one position left:
    delay(500);              // wait a bit
  }
  */
  
  delay(3000);
  lcd.clear();

  //Categorizing BMI and turning on corresponding LEDs
  if (bmi<18.5){
    Serial.println ("UNDERWEIGHT");
    
    lcd.print("YOU ARE            ");
    lcd.setCursor(0, 1);
    lcd.print("UNDERWEIGHT                 ");
    digitalWrite (A1,HIGH);
    delay(3000);
    
    
    lcd.clear();
    lcd.print("GAIN WEIGHT                 ");
    lcd.setCursor(0, 1);
    lcd.print("2450 CAL/DAY");
    delay(3000);
    lcd.clear();
    digitalWrite (A1,LOW);
  }
  else if (bmi>18.5&&bmi<25){
    Serial.println ("NORMAL             ");
    
    lcd.print("YOU ARE            ");
    lcd.setCursor(0, 1);
    lcd.print("NORMAL                  ");
    digitalWrite (10,HIGH);
    delay(3000);
    lcd.clear();
    lcd.print("MAINTAIN WEIGHT                 ");
    lcd.setCursor(0, 1);
    lcd.print("2382 CAL/DAY");
    delay(3000);
    lcd.clear();
    digitalWrite (10,LOW);
  }
  else if (bmi>=25&&bmi<30){
    
    lcd.print("YOU ARE            ");
    lcd.setCursor(0, 1);
    Serial.println ("OVERWEIGHT");
    lcd.print("OVERWEIGHT             ");
    digitalWrite (9,HIGH);
    delay(3000);
    lcd.clear();
    lcd.print("LOSE WEIGHT                 ");
    lcd.setCursor(0, 1);
    lcd.print("2465 CAL/DAY");
    delay(3000);
    lcd.clear();
    digitalWrite (9,LOW);
  }
  else if (bmi>=30&&bmi<35){
    Serial.println ("OBESE");
    
    lcd.print("YOU ARE            ");
    lcd.setCursor(0, 1);
    lcd.print("OBESE                     ");
    digitalWrite (A2,HIGH);
    delay(3000);
    lcd.clear();
    lcd.print("LOSE WEIGHT                 ");
    lcd.setCursor(0, 1);
    lcd.print("2414 CAL/DAY");
    delay(3000);
    lcd.clear();
    digitalWrite (A2,LOW);
  }
  else if (bmi>=35){
    Serial.println ("SEVERELY OBESE");
    
    lcd.print("YOU ARE            ");
    lcd.setCursor(0, 1);
    lcd.print("SEVERELY OBESE                ");
    digitalWrite (A3,HIGH);
    delay(3000);
    lcd.clear();
    lcd.print("LOSE WEIGHT                 ");
    lcd.setCursor(0, 1);
    lcd.print("1914 CAL/DAY");
    delay(3000);
    lcd.clear();
    digitalWrite (A3,LOW);
  } 
}