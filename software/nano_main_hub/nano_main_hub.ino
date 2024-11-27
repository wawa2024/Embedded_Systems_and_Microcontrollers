#define BAUD_RATE 115200

#define BUFFER_SIZE 80

char buf[BUFFER_SIZE];
constexpr int BUFFER_LIMIT = ( BUFFER_SIZE - 2 );

bool pushBuf(unsigned int i, char c) {

  if ( i > BUFFER_LIMIT ) 
    return true;
  
  buf[i] = c;
  return false;

}

void mirrorSerial(void) {

  static unsigned int i = 0;
 
  if (Serial.available() > 0) {                                                 

    char c = (char)Serial.read();                                               

    if (c == '\n') {                                                            

      digitalWrite(LED_BUILTIN, HIGH);                                          

      pushBuf([i++],0);                                                          

      Serial.write(buf);
      Serial.write("\n");                                                   

      i = 0;                                                                  

      digitalWrite(LED_BUILTIN, LOW);                                           
    } 

    else                                                                      
      pushBuf(i++,c);                                                          
  }                                                                             
}

void setup() {

  Serial.begin(BAUD_RATE,SERIAL_8N1);

}

void loop(void) {                                                               

  mirrorSerial();

}   
