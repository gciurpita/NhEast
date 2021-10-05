// New Haven East 3
// Bill's panel program by Geoff Smith w/ correctio
// enhanced with serial monitor debugging by gregc

const char version [] = "New Haven East 3 211005a";

#include "Wire.h"  //For I2R operations with MRC cards

byte Input[4];
byte Output = 0;

//Chip addresses

int chip20 = 0x020;
int chip21 = 0x021;
int chip22 = 0x022;
int chip23 = 0x023;
int chip24 = 0x024;
int chip25 = 0x025;

int portA = 0x012;
int portB = 0x013;

//Inputs from buttons

bool bA1, bA2, bA3, bA4, bA5, bA6;
bool bB1, bB2, bB3, bB4, bB5, bB6, bB7, bB8, bB9, bB10, bB11, bB12, bB13;
bool bC1, bC2, bC3, bC4, bC5, bC6;
bool bD1, bD2, bD3, bD4, bD5, bD6, bX1, bX2;

//Output addresses for switch relays

int s1N = 0;
int s1R = 1;
int s2N = 2;
int s2R = 3;
int s3N = 4;
int s3R = 5;
int s4N = 6;
int s4R = 7;
int s5N = 8;
int s5R = 9;
int s6N = 10;
int s6R = 11;
int s7N = 12;
int s7R = 13;
int s8N = 14;
int s8R = 15;
int s9N = 16;
int s9R = 17;
int s10N = 18;
int s10R = 19;
int s11N = 20;
int s11R = 21;
int s12N = 22;
int s12R = 23;
int s13N = 24;
int s13R = 25;
int s14N = 26;
int s14R = 27;
int s15N = 28;
int s15R = 29;
int s16N = 30;
int s16R = 31;
int s17N = 32;
int s17R = 33;
int s18N = 34;
int s18R = 35;
int s19N = 36;
int s19R = 37;
int s20N = 38;
int s20R = 39;
int s21N = 40;
int s21R = 41;
int s22N = 42;
int s22R = 43;
int s23N = 44;
int s23R = 45;
int s24N = 46;
int s24R = 47;
int s25N = 48;
int s25R = 49;
int s26N = 50;
int s26R = 51;
int s27N = 52;
int s27R = 53;
int s28N = 54;
int s28R = 55;
int s29N = 56;
int s29R = 57;

int LED = 13;

bool routeSet = false;

// -----------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  Wire.begin();    //start I2C bus

//set output ports  
  Wire.beginTransmission(chip22);
  Wire.write(0x00);  //IODIRA register
  Wire.write(0x00);  //set port A to outputs
  Wire.endTransmission();
  Wire.beginTransmission(chip22);
  Wire.write(0x01);  //IODIRB register
  Wire.write(0x00);  //set port B to outputs
  Wire.endTransmission();

  Wire.beginTransmission(chip23);
  Wire.write(0x00);  
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.beginTransmission(chip23);
  Wire.write(0x01); 
  Wire.write(0x00); 
  Wire.endTransmission();

  Wire.beginTransmission(chip24);
  Wire.write(0x00); 
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.beginTransmission(chip24);
  Wire.write(0x01); 
  Wire.write(0x00); 
  Wire.endTransmission();

  Wire.beginTransmission(chip25);
  Wire.write(0x00); 
  Wire.write(0x00); 
  Wire.endTransmission();
  Wire.beginTransmission(chip25);
  Wire.write(0x01); 
  Wire.write(0x00); 
  Wire.endTransmission();

  //Set pullup resistors on inputs

  Wire.beginTransmission(chip20);
  Wire.write(0x0C); // GPPUA register
  Wire.write(0xFF); // turn on pullups
  Wire.endTransmission();  

  Wire.beginTransmission(chip20);
  Wire.write(0x0D); // GPPUB register
  Wire.write(0xFF); // turn on pullups
  Wire.endTransmission();  

  Wire.beginTransmission(chip21);
  Wire.write(0x0C); // GPPUA register
  Wire.write(0xFF); // turn on pullups
  Wire.endTransmission();  

  Wire.beginTransmission(chip21);
  Wire.write(0x0D); // GPPUB register
  Wire.write(0xFF); // turn on pullups
  Wire.endTransmission();  

  pinMode(A0, INPUT_PULLUP);        //Arduino pins A0 and A1 are additional digital inputs
  pinMode(A1, INPUT_PULLUP);

  pinMode(LED, OUTPUT);              //LED pin

    Serial.println (version);
}

// -----------------------------------------------------------------------------
byte ReadPort(int chip, int port)
{
  Wire.beginTransmission(chip);
  Wire.write(port);    
  Wire.endTransmission();
  Wire.requestFrom(chip, 1); //get 1 byte
  return Wire.read();
}

// -----------------------------------------------------------------------------
void readButtons()
{
  Input[0] = ReadPort(chip20, portB);   //Inputs from MRC boards
  Input[1] = ReadPort(chip20, portA);
  Input[2] = ReadPort(chip21, portB);
  Input[3] = ReadPort(chip21, portA);

  bA1 = !bitRead(Input[0], 7);     //break out individual buttons from port bytes
  bA2 = !bitRead(Input[0], 6);
  bA3 = !bitRead(Input[0], 5);
  bA4 = !bitRead(Input[0], 4); 
  bA5 = !bitRead(Input[0], 3);
  bA6 = !bitRead(Input[0], 2);
  bB2 = !bitRead(Input[0], 1);
  bB3 = !bitRead(Input[0], 0); 

  bB4 = !bitRead(Input[1], 7);
  bB5 = !bitRead(Input[1], 6);
  bB6 = !bitRead(Input[1], 5);
  bB7 = !bitRead(Input[1], 4); 
  bB8 = !bitRead(Input[1], 3);
  bB9 = !bitRead(Input[1], 2);
  bB10 = !bitRead(Input[1], 1);
  bB11 = !bitRead(Input[1], 0); 

  bB12 = !bitRead(Input[2], 7);
  bB13 = !bitRead(Input[2], 6);
  bB1 = !bitRead(Input[2], 5);
  bC1 = !bitRead(Input[2], 4); 
  bC2 = !bitRead(Input[2], 3);
  bC3 = !bitRead(Input[2], 2);
  bC4 = !bitRead(Input[2], 1);
  bC5 = !bitRead(Input[2], 0); 

  bC6 = !bitRead(Input[3], 7);
  bX1 = !bitRead(Input[3], 6);
  bD6 = !bitRead(Input[3], 5);
  bD5 = !bitRead(Input[3], 4); 
  bD1 = !bitRead(Input[3], 3);
  bD2 = !bitRead(Input[3], 2);
  bD3 = !bitRead(Input[3], 1);
  bD4 = !bitRead(Input[3], 0);

  bX2 = !digitalRead(A0);      //Input from Arduino pin          
}

// -----------------------------------------------------------------------------
void debounce()               //second read of buttons
{
  delay(100);
  readButtons();
}

// -----------------------------------------------------------------------------
//relay pulse functions
void
sendPulse(
    int     chip,
    int     port,
    byte    output )
{  
    Serial.print   ("sendPulse: ");
    Serial.print   (chip, HEX);
    Serial.print   (" ");
    Serial.print   (port, HEX);
    Serial.print   (" ");
    Serial.println (output, HEX);
    
    Wire.beginTransmission(chip);  
    Wire.write(port);              
    Wire.write(output);           //set pulse bit
    Wire.endTransmission();

    delay(20);                    //pulse length                      

    Wire.beginTransmission(chip);
    Wire.write(port);
    Wire.write(0);                //clear pulse bit
    Wire.endTransmission();

    delay(20);                    //interpulse delay
}

// -----------------------------------------------------------------------------
void
pulse(
    int relay )
{
    Serial.print   ("pulse: ");
    Serial.println (relay, DEC);

    Output = 0;
    bitWrite(Output, relay%8, 1);       //set the relevant bit in the byte to be sent        

    if(relay < 8)                       //then find the right port to send it to
        sendPulse(chip22, portB, Output);
    else if(relay > 7 && relay < 16)
        sendPulse(chip22, portA, Output);
    else if(relay > 15 && relay < 24)
        sendPulse(chip23, portB, Output);
    else if(relay > 23 && relay < 32)
        sendPulse(chip23, portA, Output);
    else if(relay > 31 && relay < 40)
        sendPulse(chip24, portB, Output);
    else if(relay > 39 && relay < 48)
        sendPulse(chip24, portA, Output);
    else if(relay > 47 && relay < 56)
        sendPulse(chip25, portB, Output);
    else
        sendPulse(chip25, portA, Output);
}

// -----------------------------------------------------------------------------
// process commands from serial monitor
void
pcRead (void)
{
    static int  val = 0;

    if (Serial.available()) {
        int c = Serial.read ();

        switch (c)  {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            val = c - '0' + (10 * val);
            Serial.println (val);
            break;

        case ' ':
            val = 0;
            break;

        case 'p':
            pulse (val);
            val = 0;
            break;

        case 'v':
            Serial.print ("\nversion: ");
            Serial.println (version);
            break;

        default:
            Serial.print ("unknown: ");
            Serial.println (c);
            break;
        }
    }
}

// -----------------------------------------------------------------------------
void loop()
{
  pcRead ();

  readButtons();

//Routes from A to B--------------------------------
  if(bA1 && bB2)        //A1 to B2
  {
    if(!routeSet)
    {
      debounce();
      if(bA1 && bB2)      //confirm that buttons still pushed
      {
        pulse(s1N);       //set selected route
        routeSet = true;
      }
    }
  }
  else if(bA1 && bB3)   //A1 to B3
  {
    if(!routeSet)
    {
      debounce();
      if(bA1 && bB3)    
      {
        pulse(s1R);
        pulse(s2N);
        routeSet = true;
      }
    }
  }
  else if(bA2 && bB3)   //A2 to B3
  {
    if(!routeSet)
    {
      debounce();
      if(bA2 && bB3)
      {
        pulse(s2R);
        pulse(s1N);
        routeSet = true;
      }
    }
  }
  else if(bA2 && bB4)   //A2 to B4
  {
    if(!routeSet)
    {
      debounce();
      if(bA2 && bB4)
      {      
        pulse(s2N);
        pulse(s3N);
        routeSet = true;
      }
    }
  }
  else if(bA3 && bB4)   //A3 to B4
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bB4)
      {
        pulse(s4N);
        pulse(s3R);
        routeSet = true;
      }
    }
  }
  else if(bA3 && bB5)   //A3 to B5
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bB5)
      {
        pulse(s4N);
        pulse(s3N);
        routeSet = true;
      }
    }
  }
  else if(bA3 && bB6)   //A3 to B6
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bB6)
      {
        pulse(s4R);
        pulse(s5N);
        routeSet = true;          
      }
    }
  }  
  else if(bA4 && bB6)   //A4 to B6
  {
    if(!routeSet)
    {
      debounce();
      if(bA4 && bB6)
      {
        pulse(s5R);
        pulse(s4N);
        routeSet = true;
      }
    }
  }
  else if(bA4 && bB7)   //A4 to B7
  {
    if(!routeSet)
    {
      debounce();
      if(bA4 && bB7)
      {
        pulse(s5N);
        routeSet = true;      
      }
    }
  }
  else if(bA5 && bB10)  //A5 to B10
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bB10)
      {
        pulse(s6N);
        routeSet = true;      
      }
    } 
  }  
  else if(bA5 && bB11)  //A5 to B11
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bB11)
      {  
        pulse(s6R);
        pulse(s7N);
        routeSet = true;
      }
    }
  }
  else if(bA6 && bB11)   //A6 to B11
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bB11)
      {
        pulse(s7R);
        pulse(s6N);
        routeSet = true;
      }
    }
  }
  else if(bA6 && bB12)    //A6 to B12
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bB12)
      {
        pulse(s7N);
        routeSet = true;
      }
    }
  }

//Routes from B to C-----------------------------------------

  else if(bB1 && bC1)       //B1 to C1
  {
    if(!routeSet)
    { 
      debounce();
      if(bB1 && bC1)
      {
        pulse(s15R);
        routeSet = true;
      }
    }
  }
  else if(bB2 && bC1)       //B2 to C1
  {
    if(!routeSet)
    {
      debounce();
      if(bB2 && bC1)
      {
        pulse(s10N);
        pulse(s15N);
        routeSet = true;
      }
    }
  }
  else if(bB3 && bC1)       //B3 to C1
  {
    if(!routeSet)
    {
      debounce();
      if(bB3 && bC1)
      {
        pulse(s10R);
        pulse(s15N);
        routeSet = true;
      }
    }
  }
  else if(bB3 && bC2)       //B3 to C2
  {
    if(!routeSet)
    {
      debounce();
      if(bB3 && bC2)
      {
        pulse(s10N);
        pulse(s11R);
        pulse(s16N);
        routeSet = true;
      }
    }
  }
  else if(bB4 && bC2)       //B4 to C2
  {
    if(!routeSet)
    {
      debounce();
      if(bB4 && bC2)
      {
        pulse(s11N);
        pulse(s16N);
        routeSet = true;      
      }
    }
  }
  else if(bB5 && bC2)        //B5 to C2
  {
    if(!routeSet)
    {
      debounce();
      if(bB5 && bC2)
      {
        pulse(s12N);
        pulse(s16R);
        routeSet = true;
      }
    }
  }
  else if(bB5 && bC3)       //B5 to C3
  {
    if(!routeSet)
    {
      debounce();
      if(bB5 && bC3)
      {
        pulse(s12N);
        pulse(s16N);
        pulse(s17N);
        routeSet = true;        
      }
    }
  }
  else if(bB6 && bC2)       //B6 to C2
  {
    if(!routeSet)
    {
      debounce();
      if(bB6 && bC2)
      {
        pulse(s8R);
        pulse(s12R);
        pulse(s16R);
        routeSet = true;      
      }
    }
  }
  else if(bB6 && bC3)       //B6 to C3
  {
    if(!routeSet)
    {
      debounce();
      if(bB6 && bC3)
      {
        pulse(s8R);
        pulse(s12R);
        pulse(s16N);
        routeSet = true;       
      }
    }
  }
  else if(bB7 && bC2)       //B7 to C2
  {
    if(!routeSet)
    {
      debounce();
      if(bB7 && bC2)          //B7 to C2
      {
        pulse(s8N);
        pulse(s12R);
        pulse(s16R);
        routeSet = true;      
      }
    }
  }
  else if(bB7 && bC3)       //B7 to C3
  {
    if(!routeSet)
    {
      debounce();
      if(bB7 && bC3)
      {
        pulse(s8N);
        pulse(s12R);
        pulse(s16N);
        pulse(s17N);
        routeSet = true;        
      }
    }
  }
  else if(bB8 && bC3)       //B8 to C3
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bC3)
      {
        pulse(s17R);
        routeSet = true;
      }
    }
  }
  else if(bB8 && bC4)       //B8 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bC4)
      {
        pulse(s17N);
        pulse(s18N);
        pulse(s20N);
        routeSet = true;
      }
    }
  }
  else if(bB9 && bC4)            //B9 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB9 && bC4)
      {
        pulse(s14N);
        pulse(s18R);
        pulse(s20N);
        routeSet = true;          
      }
    }
  }
  else if(bB10 && bC4)           //B10 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB10 && bC4)
      {
        pulse(s14R);
        pulse(s18R);
        pulse(s20N);
        routeSet = true;
      }
    }
  }
  else if(bB11 && bC4)           //B11 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB11 && bC4)
      {
        pulse(s9R);
        pulse(s13N);
        pulse(s20R);
        routeSet = true;
      }
    }
  }
  else if(bB11 && bC5)           //B11 to C5
  {
    if(!routeSet)
    {
      debounce();
      if(bB11 && bC5)
      {
        pulse(s9R);
        pulse(s13N);
        pulse(s20N);
        routeSet = true;
      }
    }
  }
  else if(bB12 && bC4)           //B12 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB12 && bC4)
      {
        pulse(s9N);
        pulse(s13N);
        pulse(s20R);
        routeSet = true;
      }
    }
  }
  else if(bB12 && bC5)           //B12 to C5
  {
    if(!routeSet)
    {
      debounce();
      if(bB12 && bC5)
      {
        pulse(s9N);
        pulse(s13N);
        pulse(s20N);
        routeSet = true;
      }
    }
  }
  else if(bB13 && bC4)           //B13 to C4
  {
    if(!routeSet)
    {
      debounce();
      if(bB13 && bC4)
      {
        pulse(s13R);
        pulse(s20R);
        routeSet = true;        
      }
    }
  }
  else if(bB13 && bC5)           //B13 to C5
  {
    if(!routeSet)
    {
      debounce();
      if(bB13 && bC5)
      {
        pulse(s13R);
        pulse(s20N);
        routeSet = true;       
      }
    }
  }

// Routes from C to D----------------------------------------------------------

  else if(bC1 && bD1)   //C1 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC1 && bD1)
      {
        pulse(s19N);
        pulse(s26N);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC1 && bD2)    //C1 to D2    
  {
    if(!routeSet)
    {
      debounce();
      if(bC1 && bD2)
      {
        pulse(s19N);
        pulse(s26N);
        pulse(s27N);
        routeSet = true;
      }
    }
  }
  else if(bC1 && bD3)    //C1 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC1 && bD3)
      {
        pulse(s19R);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;
      }
    }
  }      
  else if(bC1 && bD4)    //C1 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bC1 && bD4)
      {    
        pulse(s19R);
        pulse(s23R);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bC2 && bD1)    //C2 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC2 && bD1)
      {
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26R);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC2 && bD2)    //C2 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bC2 && bD2)
      {
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }
    }
  }
  else if(bC2 && bD3)    //C2 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC2 && bD3)
      {
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;      
      }
    }
  }     
  else if(bC2 && bD4)    //C2 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bC2 && bD4)
      {
        pulse(s19N);
        pulse(s23R);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bC3 && bD1)    //C3 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC3 && bD1)
      {
        pulse(s23N);
        pulse(s24N);
        pulse(s25R);
        pulse(s26R);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC3 && bD2)    //C3 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bC3 && bD2)
      {
        pulse(s23N);
        pulse(s24N);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }
    }
  }    
  else if(bC3 && bD3)    //C3 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC3 && bD3)
      {     
        pulse(s23N);
        pulse(s24N);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;
      }
    }
  }  
  else if(bC3 && bD4)    //C3 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bC3 && bD4)
      {
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bC4 && bD1)    //C4 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC4 && bD1)
      {
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC4 && bD2)    //C4 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bC4 && bD2)
      {
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }
    } 
  } 
  else if(bC4 && bD3)    //C4 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC4 && bD3)
      {
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;
      }
    }
  } 
  else if(bC4 && bD4)    //C4 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bC4 && bD4)
      {
        pulse(s22N);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;
      }
    }
  } 
  else if(bC4 && bD5)    //C4 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bC4 && bD5)
      {
        pulse(s22N);
        pulse(s24N);
     // pulse(s28N);
     // pulse(s29N);
        routeSet = true;
      }
    }
  }
  else if(bC5 && bD1)    //C5 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD1)
      {
        pulse(s21N);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC5 && bD2)    //C5 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD2)
      {
        pulse(s21N);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }
    }
  }
  else if(bC5 && bD3)    //C5 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD3)
      {
        pulse(s21N);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;
      }
    } 
  }  
  else if(bC5 && bD4)    //C5 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD4)
      {
        pulse(s21N);
        pulse(s22R);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bC5 && bD5)   //C5 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD5)
      {
        pulse(s21N);
        pulse(s22R);
        pulse(s24N);
     // pulse(s28N);
     // pulse(s29N);    
        routeSet =true;
      }
    }
  }
  else if(bC5 && bD6)   //C5 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bC5 && bD6)
      {
        pulse(s21N);
        pulse(s22N);
     // pulse(s28R);
     // pulse(s29N);
        routeSet = true;
      }
    }
  }
  else if(bC6 && bD1)    //C6 to D1
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bD1)
      {
        pulse(s21R);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27R);
        routeSet = true;
      }
    }
  }
  else if(bC6 && bD2)    //C6 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bD2)
      {
        pulse(s21R);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }
    }
  }
  else if(bC6 && bD3)    //C6 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bD3)
      {
        pulse(s21R);
        pulse(s22R);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;
      }
    }
  }   
  else if(bC6 && bD4)    //C6 to D4
  {
    if(!routeSet)
    { 
      debounce();
      if(bC6 && bD4)
      {
        pulse(s21R);
        pulse(s22R);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bC6 && bD5)   //C6 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bD5)
      {
        pulse(s21R);
        pulse(s22R);
        pulse(s24N);
     // pulse(s28N);
     // pulse(s29N);
        routeSet = true;
      }
    }
  }
  else if(bD5)   //D5
  {
    if(!routeSet)
    {
      debounce();
      if(bD5)
      {
        pulse(s28N);
        pulse(s29N);
        routeSet = true;
      }
    }
  }

  else if(bC6 && bD6)   //C6 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bD6)
      {
        pulse(s21R);
        pulse(s22N);
     // pulse(s28R);
     // pulse(s29N);
        routeSet = true;
      }
    }
  }
  else if(bC6 && bX1)   //C6 to X1
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bX1)
      {
        pulse(s21N);
        routeSet = true;        
      }
    }
  }

//Super routes----------------------------------------------------------

  else if(bA1 && bD2)   //A1 to D2
  {
    if(!routeSet)
    {      
      debounce();
      if(bA1 && bD2)
      {
      pulse(s1N);
      pulse(s10N);
      pulse(s15N);
      pulse(s19N);
      pulse(s26N);
      pulse(s27N);
      routeSet = true;
      }  
    }
  }
  else if(bA1 && bD3)   //A1 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bA1 && bD3)
      {
        pulse(s1N);
        pulse(s10N);
        pulse(s15N);
        pulse(s19R);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;        
      }      
    }
  }
  else if(bA1 && bD4)   //A1 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA1 && bD4)
      {
        pulse(s1N);
        pulse(s10N);
        pulse(s15N);
        pulse(s19R);
        pulse(s23R);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bA2 && bD2)   //A2 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bA2 && bD2)
      {
        pulse(s2N);
        pulse(s3N);
        pulse(s11N);
        pulse(s16N);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }      
    }
  }    
  else if(bA2 && bD3)   //A2 to D3
  {
    {
      debounce();
      if(bA2 && bD3)
      {
        pulse(s2N);
        pulse(s3N);
        pulse(s11N);
        pulse(s16N);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;
      }
    }
  }
  else if(bA2 && bD4)   //A2 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA2 && bD4)
      {
        pulse(s2N);
        pulse(s3N);
        pulse(s11N);
        pulse(s16N);
        pulse(s19N);
        pulse(s23R);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }      
    }
  }
  else if(bA3 && bD2)   //A3 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bD2)
      {
        pulse(s4N);
        pulse(s3R);
        pulse(s11N);
        pulse(s16N);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }      
    }
  }
  else if(bA3 && bD3)   //A3 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bD3)
      {
        pulse(s4N);
        pulse(s3R);
        pulse(s11N);
        pulse(s16N);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;
      }      
    }
  }
  else if(bA3 && bD4)   //A3 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA3 && bD4)
      {
        pulse(s4N);
        pulse(s3N);
        pulse(s12N);
        pulse(s16N);
        pulse(s17N);
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }
    }
  }
  else if(bA4 && bD2)   //A4 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bA4 && bD2)
      {
        pulse(s5N);
        pulse(s8N);
        pulse(s12R);
        pulse(s16R);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;
      }      
    }
  }    
  else if(bA4 && bD3)   //A4 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bA4 && bD3)
      {
        pulse(s5N);
        pulse(s8N);
        pulse(s12R);
        pulse(s16R);
        pulse(s19N);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;
      }       
    }
  }
  else if(bA4 && bD4)   //A4 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA4 && bD4)
      {
        pulse(s5N);
        pulse(s8N);
        pulse(s12R);
        pulse(s16N);
        pulse(s17N);
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;
      }      
    }
  }
  else if(bA5 && bD2)   //A5 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bD2)
      {
        pulse(s6N);
        pulse(s14R);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;        
      }      
    }
  }
  else if(bA5 && bD3)   //A5 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bD3)
      {
        pulse(s6N);
        pulse(s14R);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;                
      }
    }
  }
  else if(bA5 && bD4)   //A5 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bD4)
      {
        pulse(s6N);
        pulse(s14R);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;        
      }      
    }
  }
  else if(bA5 && bD5)   //A5 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bA5 && bD5)
      {
        pulse(s6N);
        pulse(s14R);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24N);
        pulse(s28N);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }      
  else if(bA6 && bD2)   //A6 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bD2)
      {
        pulse(s7N);
        pulse(s9N);
        pulse(s13N);
        pulse(s20R);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;        
      }      
    }
  }
  else if(bA6 && bD3)   //A6 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bD3)
      {
        pulse(s7N);
        pulse(s9N);
        pulse(s13N);
        pulse(s20R);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;        
      }      
    }
  }
  else if(bA6 && bD4)   //A6 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bD4)
      {
        pulse(s7N);
        pulse(s9N);
        pulse(s13N);
        pulse(s20R);
        pulse(s22N);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;        
      }      
    }
  }
  else if(bA6 && bD5)   //A6 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bD5)
      {
        pulse(s7N);
        pulse(s9N);
        pulse(s13N);
        pulse(s20R);
        pulse(s22N);
        pulse(s24N);
        pulse(s28N);
        pulse(s29N);
        routeSet = true;          
      }      
    }
  }
  else if(bA6 && bD6)   //A6 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bA6 && bD6)
      {
        pulse(s7N);
        pulse(s9N);
        pulse(s13N);
        pulse(s20N);
        pulse(s22N);
        pulse(s28R);
        pulse(s29N);
        routeSet = true;          
      }      
    }
  }

  else if(bB1 && bD2)   //B1 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bB1 && bD2)
      {
        pulse(s15R);
        pulse(s19N);
        pulse(s26N);
        pulse(s27N);
        routeSet = true;        
      }      
    }
  }
  else if(bB1 && bD3)   //B1 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bB1 && bD3)
      {
        pulse(s15R);
        pulse(s19R);
        pulse(s23N);
        pulse(s25N);
        pulse(s26N);
        routeSet = true;        
      }      
    }
  }
  else if(bB1 && bD4)   //B1 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bB1 && bD4)
      {
        pulse(s15R);
        pulse(s19R);
        pulse(s23R);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;        
      }      
    }
  }

  else if(bB8 && bD2)
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bD2)
      {
        pulse(s17R);
        pulse(s23N);
        pulse(s24N);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;        
      }      
    }
  }

  else if(bB8 && bD3)   //B8 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bD3)
      {
        pulse(s17R);
        pulse(s23N);
        pulse(s24N);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;        
      }      
    }
  }
  else if(bB8 && bD4)   //B8 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bD4)
      {
        pulse(s17R);
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        routeSet = true;        
      }      
    }
  }
  else if(bB8 && bD5)   //B8 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bB8 && bD5)
      {
        pulse(s17N);
        pulse(s18N);
        pulse(s20N);
        pulse(s22N);
        pulse(s24N);
        pulse(s28N);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }

  else if(bB9 && bD2)   //B9 to D2
  {
    if(!routeSet)
    {
      debounce();
      if(bB9 && bD2)
      {
        pulse(s14N);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26R);
        pulse(s27N);
        routeSet = true;        
      }      
    }
  }

  else if(bB9 && bD3)   //B9 to D3
  {
    if(!routeSet)
    {
      debounce();
      if(bB9 && bD3)
      {
        pulse(s14N);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25R);
        pulse(s26N);
        routeSet = true;        
      }      
    }
  }
  else if(bB9 && bD4)   //B9 to D4
  {
    if(!routeSet)
    {
      debounce();
      if(bB9 && bD4)
      {
        pulse(s14N);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24R);
        pulse(s25N);
        routeSet = true;        
      }      
    }
  }
  else if(bB9 && bD5)   //B9 to D5
  {
    if(!routeSet)
    {
      debounce();
      if(bB9 && bD5)
      {
        pulse(s14N);
        pulse(s18R);
        pulse(s20N);
        pulse(s22N);
        pulse(s24N);
        pulse(s28N);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }

  else if(bB11 && bD6)  //B11 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bB11 && bD6)
      {
        pulse(s9R);
        pulse(s13N);
        pulse(s20N);
        pulse(s20N);
        pulse(s22N);
        pulse(s28R);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }
  else if(bB12 && bD6)  //B12 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bB12 && bD6)
      {
        pulse(s9N);
        pulse(s13N);
        pulse(s20N);
        pulse(s20N);
        pulse(s22N);
        pulse(s28R);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }

  else if(bB13 && bD6)  //B13 to D6
  {
    if(!routeSet)
    {
      debounce();
      if(bB13 && bD6)
      {
        pulse(s13R);
        pulse(s20N);
        pulse(s21N);
        pulse(s22N);
     // pulse(s28R);
     // pulse(s29N);
        routeSet = true;        
      }      
    }
  }

  else if(bD6)  //D6
  {
    if(!routeSet)
    {
      debounce();
      if(bD6)
      {
        pulse(s28R);
        pulse(s29N);
        routeSet = true;        
      }      
    }
  }

  else if(bC6 && bX2)    //C6 to X2
  {
    if(!routeSet)
    {
      debounce();
      if(bC6 && bX2)
      {
        pulse(s21N);
        pulse(s29R);
        routeSet = true;
      }
    }
  }

  // single buttons
#if 0
  else if(bX1 && bX2)   //X1 to X2
  {
    if(!routeSet)
    {
      debounce();
      if(bX1 && bX2)
      {
        pulse(s29R);
        routeSet = true;
      }
    }
  }
#else

  // test case
  else if(bX2)   // X2
  {
    if(!routeSet)
    {
      debounce();
      if(bX2)
      {
        pulse(s29R);
        routeSet = true;
      }
    }
  }
#endif
  else if (bA1 && bA3 && bA5)  //all switches normal
  {
    if(!routeSet)
    {
      debounce();
      if(bA1 && bA3 && bA5)
      {
        pulse(s1N);
        pulse(s2N);
        pulse(s3N);
        pulse(s4N);
        pulse(s5N);
        pulse(s6N);
        pulse(s7N);
        pulse(s8N);
        pulse(s9N);
        pulse(s10N);
        pulse(s11N);
        pulse(s12N);
        pulse(s13N);
        pulse(s14N);
        pulse(s15N);
        pulse(s16N);
        pulse(s17N);
        pulse(s18N);
        pulse(s19N);
        pulse(s20N);
        pulse(s21N);
        pulse(s22N);
        pulse(s23N);
        pulse(s24N);
        pulse(s25N);
        pulse(s26N);
        pulse(s27N);
        pulse(s28N);
        pulse(s29N);
        routeSet = true;  
      }
    }
  }
  else                  //all possible routes checked
  {
    routeSet = false;    //all button combinations released
  }
  if(routeSet)
  {
    digitalWrite(LED, HIGH);  //keep LED on while buttons pressed
  }
  else
  {
    digitalWrite(LED, HIGH);  //flash LED otherwise to confirm program running
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
}
