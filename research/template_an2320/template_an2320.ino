#include <Wire.h>
void setup() {
  Wire.begin();       
  Serial.begin(115200);
  delay(100); 
}
void loop() {
  float humidity = 0.00;
  float temperature = 0.00;

  Wire.beginTransmission(0x5c);
  Wire.write(0x03);
  Wire.write(0x00);
  Wire.write(0x04);
  Wire.endTransmission();
  delay(1000);  

  int ans = Wire.requestFrom(0x5c,6);
  while(Wire.available() !=0){   
    int H1,H2,T1,T2 = 0;
    for(int i = 1; i <  ans+1; i++){     
      int c = Wire.read();        
      switch (i){    
          case 5:
          T1 = c;
          break;
          case 6:
          T2 = c; 
          break;
          case 3:
          H1 = c; 
          break;
          case 4: 
          H2 = c;  
          break;
          default:
          break;
        }       
    }       
    humidity = (H1*256 + H2)/10.0; 
    temperature = (T1*256 + T2)/10.0; 
    Serial.print("  Temperature=");
    Serial.print(temperature);
    Serial.print("’C  Humidity=");
    Serial.print(humidity);
    Serial.println("%   ");
    } 
}
