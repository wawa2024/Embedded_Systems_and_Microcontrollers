#define BAUD_RATE 115200

void setup() {
  Serial.begin(BAUD_RATE,SERIAL_8N1);
}

char line[80];

void loop(void) {                                                               
  static unsigned int i = 0;
 
  if (Serial.available() > 0) {                                                 
    char c = (char)Serial.read();                                               
    if (c == '\n') {                                                            
      digitalWrite(LED_BUILTIN, HIGH);                                          
      line[i++] = 0;                                                          
      Serial.write(line);
      Serial.write("\n");                                                   
      i = 0;                                                                  
      digitalWrite(LED_BUILTIN, LOW);                                           
    } else                                                                      
      line[i++] = c;                                                          
  }                                                                             
}   
