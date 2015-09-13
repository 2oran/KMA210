//******************************************************************************************************************************************
// Setup
//******************************************************************************************************************************************
void setup()
{
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
 // Serial.begin(9600);
  delay(20);      // Enter command mode (30mS)
  start();
  command_mode();
  stop();
}
int result = 0; //OVO JE GLOBALNA VARIJABLA!!!!!!!????
//******************************************************************************************************************************************
// Main loop[
//******************************************************************************************************************************************
void loop()
{
  start();
  unsigned int  data_hex = 0x11;
  serial_8(data_hex);
  handover();
  read_kma210();

  takeover();
  stop();
  Serial.print(result,HEX);

}
//******************************************************************************************************************************************
// Komandni mod, posle power on-a
//******************************************************************************************************************************************
void command_mode()
{
      unsigned char array [3] = {0x94,0x16,0xf4};
      unsigned char data_hex;
      unsigned char i;
      unsigned char j;

      
      
  for(j=0;j<3;j++)
  {
      unsigned char result;
      data_hex = array[j]; 
      serial_8( data_hex);
          
  }
      
     
}

//*************************************************************************************************************************************
// Start condition
//*************************************************************************************************************************************
void start (void)
{
 // digitalWrite(10,HIGH);
  //digitalWrite(10,LOW);
  digitalWrite(9,LOW);    //ovo je start uslov (10uS), po dokumentaciji je 5uS
  delayMicroseconds(10);
 // digitalWrite(10,HIGH);
  //digitalWrite(10,LOW);
 
}
//*************************************************************************************************************************************
// Stop condition
//*************************************************************************************************************************************
void stop (void)
{
 
  digitalWrite(9,HIGH);   // ovo je stop uslov (10uS), po dokumentaciji je 5uS
  delayMicroseconds(10);
 
}
//*************************************************************************************************************************************
// Send command
//*************************************************************************************************************************************
unsigned char send_command(unsigned char)
{
  
}

//*************************************************************************************************************************************
// Iscitavanje senzora
//*************************************************************************************************************************************
void read_kma210()
{
  
    unsigned char i;
    // unsigned int result = 0;;
    unsigned int serial_bit;

   for(char i=15;i>=0;i--)
   {

    delayMicroseconds(39);
    digitalWrite(11,HIGH);
    digitalWrite(11,LOW);
    serial_bit  = digitalRead(9) != 0;
    //digitalWrite(10,HIGH);
    delayMicroseconds(38);
    
    result |= serial_bit << i ;
   }
      
}

//************************************************************************************************************************************
//  Serial send 8 bits
//************************************************************************************************************************************
unsigned char serial_8(unsigned char data_hex)
{
  char i;
  unsigned char result;
   for(i=0;i<8;i++)
      {
        result = data_hex & 0x80;
            
        if(result == 0x80)
        {
            digitalWrite(9,HIGH);
            delayMicroseconds(60);
            digitalWrite(9,LOW);
            delayMicroseconds(25);
            // Serial.print('1');
        }
        else
        {
            digitalWrite(9,HIGH);
            delayMicroseconds(22);
            digitalWrite(9,LOW);
            delayMicroseconds(65);
            //Serial.print('0');
        }
            data_hex <<= 1;
      }
}
  

//************************************************************************************************************************************
//  Serial send 16 bits
//************************************************************************************************************************************
unsigned char serial_16(unsigned int data_hex)
{
  char i;
  unsigned char result;
  
   for(i=0;i<16;i++)
      {
        result = data_hex & 0x8000;
            
        if(result == 0x8000)
        {
            digitalWrite(9,HIGH);
            delayMicroseconds(60);
            digitalWrite(9,LOW);
            delayMicroseconds(25);
            // Serial.print('1');
        }
        else
        {
            digitalWrite(9,HIGH);
            delayMicroseconds(22);
            digitalWrite(9,LOW);
            delayMicroseconds(65);
            //Serial.print('0');
        }
            data_hex <<= 1;
      }
}
//************************************************************************************************************************************
// Handover
//************************************************************************************************************************************
void handover (void)
{
  digitalWrite(9,HIGH);
  delayMicroseconds(23);
  digitalWrite(9,LOW);
  delayMicroseconds(30);
  pinMode(9,INPUT);
  delayMicroseconds(22);  
}
//************************************************************************************************************************************
// Takeover
//************************************************************************************************************************************
void takeover (void)
{
  delayMicroseconds(45);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  delayMicroseconds(30);
  
}

//************************************************************************************************************************************
//   Ovo je test rutina za merenje sirine impulsa kasnjenja
//************************************************************************************************************************************
void pulse()
{
 
  digitalWrite(9,HIGH);       // OVO JE SAMO TEST!!!!!!
  delayMicroseconds(65);
  digitalWrite(9,LOW);
  delayMicroseconds(23);
  
}

  
  

