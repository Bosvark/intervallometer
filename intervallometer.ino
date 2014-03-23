// select the pins used on the LCD panel
#define PIN_SCE   7 //Pin 3 on LCD
#define PIN_RESET 6 //Pin 4 on LCD
#define PIN_DC    5 //Pin 5 on LCD
#define PIN_SDIN  11//4 //Pin 6 on LCD
#define PIN_SCLK  13//3 //Pin 7 on LCD
#define PIN_BKLIGHT 9

#define PIN_SHUTTER  2
#define PIN_FOCUS    3

//The DC pin tells the LCD if we are sending a command or data
#define LCD_COMMAND 0 
#define LCD_DATA  1

//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X     84
#define LCD_Y     48
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

//This table contains the hex values that represent pixels
//for a font that is 5 pixels wide and 8 pixels high
static const byte ASCII[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c \
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 0x5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
  ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
};
 
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 Serial.println(adc_key_in);
 //return adc_key_in;
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 750) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 150)  return btnUP; 
 if (adc_key_in < 350)  return btnDOWN; 
 if (adc_key_in < 500)  return btnLEFT; 
 if (adc_key_in < 750)  return btnSELECT;  // 550
  
 return btnNONE;  // when all others fail, return this...
}

int state = 0;
int refresh = 1;

int interval = 5;
int intervalcounter = 0;
int shot_count = 5;
int shotcounter = 0;

void take_picture()
{
  gotoXY(0,5);
  LCDString("TAKING SHOT!");
  
  delay(500);  // The other 500 msec will be spent taking the shot
        
  pinMode(PIN_SHUTTER, OUTPUT);
  
  digitalWrite(PIN_SHUTTER, HIGH);
  delay(500);
  digitalWrite(PIN_SHUTTER, LOW);
  
  pinMode(PIN_SHUTTER, INPUT);

  gotoXY(0,5);
  LCDString("            ");
}

void focus()
{
  gotoXY(0,5);
  LCDString("FOCUSING!");
  
  delay(500);  // The other 500 msec will be spent taking the shot
        
  pinMode(PIN_FOCUS, OUTPUT);
  
  digitalWrite(PIN_FOCUS, HIGH);
  delay(500);
  digitalWrite(PIN_FOCUS, LOW);
  
  pinMode(PIN_FOCUS, INPUT);

  gotoXY(0,5);
  LCDString("            ");
}

#define BKL_STEP_VAL  10
#define BKL_MAX      254

int backlight = BKL_MAX;

void backlight_increment()
{
  if(backlight < (BKL_MAX-BKL_STEP_VAL))
     backlight += BKL_STEP_VAL;
     
  analogWrite(PIN_BKLIGHT, backlight);
}

void backlight_decrement()
{
  if(backlight > BKL_STEP_VAL)
    backlight -= BKL_STEP_VAL;
  
  analogWrite(PIN_BKLIGHT, backlight);
}

void state_machine()
{
  char butt_press=0;
  int old_state = state;
  
  lcd_key = read_LCD_buttons();  // read the buttons
  
  if((lcd_key == btnNONE) && (refresh == 0)){
    return;
  }
  
  refresh = 0;
    
  switch(state)
  {
    case 0:
      if (lcd_key == btnRIGHT){
        state = 1;
      }else if (lcd_key == btnUP){
        take_picture();
        break;
      }else if (lcd_key == btnDOWN){
        focus();
        break;
      }else if (lcd_key == btnSELECT){
        if ((interval > 0) && (shot_count > 0)){
          state = 4;
          intervalcounter = interval;
          shotcounter = shot_count;
        }
        
        break;
      }
      
      LCDClear();
      LCDString("Intervallo");
      gotoXY(0,1);
      LCDString("<Idle>");
      break;
      
    case 1:
    {
      if (lcd_key == btnRIGHT){
        state = 2;
        break;
      }else if (lcd_key == btnLEFT){
        state = 0;
        break;
      }else if (lcd_key == btnUP){
        interval++;
        butt_press = 1;
      }else if (lcd_key == btnDOWN){
        if(interval > 0)
          interval--;
        butt_press = 1;
      }

      LCDClear();
      LCDString("Set Interval");
      
      String interval_str(interval);
      char interval_char[10];
      interval_str.toCharArray(interval_char, sizeof(interval_char));
      gotoXY(0,1);
      LCDString(interval_char);
      
      break;
    }  
    case 2:
    {
      if (lcd_key == btnRIGHT){
        state = 3;
        break;
      }else if (lcd_key == btnLEFT){
        state = 1;
        break;
      }else if (lcd_key == btnUP){
        shot_count++;
        butt_press = 1;
      }else if (lcd_key == btnDOWN){
        if(shot_count > 0)
          shot_count--;
        butt_press = 1;
      }

      LCDClear();
      LCDString("Shot count");
      
      String shot_count_str(shot_count);
      char shot_count_char[10];
      shot_count_str.toCharArray(shot_count_char, sizeof(shot_count_char));
      gotoXY(0,1);
      LCDString(shot_count_char);
      
      break;
    }
    case 3:
    {
      if (lcd_key == btnRIGHT){
        state = 0;
        break;
      }else if (lcd_key == btnLEFT){
        state = 2;
        break;
      }else if (lcd_key == btnUP){
        backlight_increment();
        butt_press = 2;
      }else if (lcd_key == btnDOWN){
        backlight_decrement();
        butt_press = 2;
      }

      LCDClear();
      LCDString("Backlight");
      
      String shot_count_str(backlight);
      char shot_count_char[10];
      shot_count_str.toCharArray(shot_count_char, sizeof(shot_count_char));
      gotoXY(0,1);
      LCDString(shot_count_char);
      
      break;
    }
    case 4:
      take_picture();
      
      if ((interval == 0) || (shot_count == 0)){
        state = 0;
        return;
      }
      
      state = 6;
      
      // Break statement ommitted intentionally
    case 6:
      if (lcd_key == btnSELECT){
        state = 0;
        break;
      }
      
      if(intervalcounter >= 1){
        delay(1000);
        intervalcounter--;
      }
              
      String interval_str(intervalcounter+1);
      char interval_char[10];
      interval_str.toCharArray(interval_char, sizeof(interval_char));

      while(1){
        LCDClear();
        LCDString("Intervallo");
        gotoXY(0,1);
        LCDString("I:");
        LCDString(interval_char);
        LCDString(" S:");

        String shot_count_str(shotcounter);
        char shot_count_char[10];
        memset(shot_count_char, 0, sizeof(shot_count_char));
        shot_count_str.toCharArray(shot_count_char, sizeof(shot_count_char));
        LCDString(shot_count_char);
              
        if(intervalcounter == 0){
          intervalcounter = interval;
          
          // Take the shot
          take_picture();
          shotcounter--;
          intervalcounter--;  // Count another interval since take_picture() also takes a second
          
          String interval_str(intervalcounter+1);
          memset(interval_char, 0, sizeof(interval_char));
          interval_str.toCharArray(interval_char, sizeof(interval_char));
        }else
          break;
      }
      
      if(shotcounter == 0){
        state = 0;
        interval = 0;
        shot_count = 0;
      }
      
      old_state = -1;  // Force display refresh
      
      break;

  }

  if(butt_press == 1){
    // Allow button to be kept pressed
    delay(100);
      
  }else if(butt_press == 2){
  }else{
    // Make sure the key is released before we continue
    while(lcd_key != btnNONE){
      lcd_key = read_LCD_buttons();
    }
  }
  
  // Check if state changed
  if(old_state != state)
    refresh = 1;
}

void setup(void) {
//  analogReference(EXTERNAL);
  Serial.begin(9600);
  LCDInit(); //Init the LCD
  
}

void loop(void) {
/*
  char key_char[10];
  lcd_key = read_LCD_buttons();

  String key_str = String(lcd_key);
  memset(key_char, 0, sizeof(key_char));
  key_str.toCharArray(key_char, sizeof(key_char));

  LCDClear();
  gotoXY(0,1);
  LCDString("Key:");
  LCDString(key_char);
  
  delay(250);
*/
  state_machine();
/*
analogWrite(PIN_BKLIGHT, 255);
delay(1000);
analogWrite(PIN_BKLIGHT, 0);
delay(1000);
*/
}

void gotoXY(int x, int y) {
  LCDWrite(0, 0x80 | (x*5));  // Column.
  LCDWrite(0, 0x40 | y);  // Row.  ?
}

//This takes a large array of bits and sends them to the LCD
void LCDBitmap(char my_array[]){
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, my_array[index]);
}

//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void LCDCharacter(char character) {
  LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding

  for (int index = 0 ; index < 5 ; index++)
    LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
    //0x20 is the ASCII character for Space (' '). The font table starts with this character

  LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
}

//Given a string of characters, one by one is passed to the LCD
void LCDString(char *characters) {
  while (*characters)
    LCDCharacter(*characters++);
}

//Clears the LCD by writing zeros to the entire screen
void LCDClear(void) {
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, 0x00);
    
  gotoXY(0, 0); //After we clear the display, return to the home position
}

//This sends the magical commands to the PCD8544
void LCDInit(void) {

  //Configure control pins
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  pinMode(PIN_BKLIGHT, OUTPUT);

  //Reset the LCD to a known state
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  
  // Switch on backlight
  analogWrite(PIN_BKLIGHT, 255);

  LCDWrite(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
  LCDWrite(LCD_COMMAND, 0xb0); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  LCDWrite(LCD_COMMAND, 0x04); //Set Temp coefficent
  LCDWrite(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14

  LCDWrite(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  LCDWrite(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse
}

//There are two memory banks in the LCD, data/RAM and commands. This 
//function sets the DC pin high or low depending, and then sends
//the data byte
void LCDWrite(byte data_or_command, byte data) {
  digitalWrite(PIN_DC, data_or_command); //Tell the LCD that we are writing either to data or a command

  //Send the data
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

