#include <Adafruit_LiquidCrystal.h>


//Naming pins and constants for the sake of code adaptability and my sanity
const byte water_Pump_Relay = 2;
const int moist_Enough = 654;
const int half_Moisture = 436;
//const byte moisture_Sensor_In = A0;
const byte moisture_Sensor_Out = A1;

int prev_Moisture = -1; //Initialize variable 
int moisture = 0; //Initialize variable 

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("NFT Hydroponics");
  pinMode(water_Pump_Relay, OUTPUT);
  //pinMode(moisture_Sensor_In, OUTPUT);
  pinMode(moisture_Sensor_Out, INPUT);
  Serial.begin(9600);

  delay(1000);
  lcd_1.clear();
}

void loop()
{
  //digitalWrite(A0, HIGH); //Turn on moisture sensor
  //delay(10); // Wait for 10 milliseconds for more accurate reading (can be changed to kept on for longer)
  moisture = analogRead(moisture_Sensor_Out);
  
  //digitalWrite(moisture_Sensor_In, LOW); // Turn off the sensor to reduce metal corrosion over time (though i don't think this will be important but still)
  Serial.println(moisture); //Display to computer 

  if (moisture >= moist_Enough || moisture >= half_Moisture) {
    digitalWrite(water_Pump_Relay, LOW);
    Serial.print("off");
    if (prev_Moisture != moisture) {lcd_1.clear();}
    lcd_1.setCursor(0, 0);
    lcd_1.print("NFT Hydroponics");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Moisture: OK"); 
  } else if (moisture <= half_Moisture)
  {
    digitalWrite(water_Pump_Relay, HIGH);
    Serial.println("on");
    if (prev_Moisture != moisture) {
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("Moisture: ");
      lcd_1.setCursor(10, 0);
      lcd_1.print(moisture); 
      lcd_1.setCursor(0, 1);
      lcd_1.print("Water pump on"); 
    }
  }
  prev_Moisture = moisture;
}