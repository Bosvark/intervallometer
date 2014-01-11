#include <LiquidCrystal.h>
 
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  
  
 return btnNONE;  // when all others fail, return this...
}

int state = 0;

int interval = 0;
int intervalcounter = 0;
int shot_count = 0;
int shotcounter = 0;

void take_picture()
{
  lcd.setCursor(0,1);
  lcd.print("  TAKING SHOT!  ");
        
  pinMode(2, OUTPUT);
  
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  
  pinMode(2, INPUT);
}

void state_machine()
{
  char butt_press=0;
  
  lcd_key = read_LCD_buttons();  // read the buttons
    
  switch(state)
  {
    case 0:
      if (lcd_key == btnRIGHT){
        state = 1;
      }else if (lcd_key == btnSELECT){
        state = 3;
        intervalcounter = interval;
        shotcounter = shot_count;
        break;
      }
      
      lcd.setCursor(0,0);
      lcd.print("Intervallometer ");
      lcd.setCursor(0,1);
      lcd.print("<Idle>          ");
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

      lcd.setCursor(0,0);
      lcd.print("Set Interval    ");
      
      String interval_str(interval);
      char interval_char[10];
      interval_str.toCharArray(interval_char, sizeof(interval_char));
      lcd.setCursor(0,1);
      lcd.print(interval_char);
      lcd.print("                ");
      
      break;
    }  
    case 2:
    {
      if (lcd_key == btnRIGHT){
        state = 0;
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

      lcd.setCursor(0,0);
      lcd.print("Set Shot count  ");
      
      String shot_count_str(shot_count);
      char shot_count_char[10];
      shot_count_str.toCharArray(shot_count_char, sizeof(shot_count_char));
      lcd.setCursor(0,1);
      lcd.print(shot_count_char);
      lcd.print("                ");
      
      break;
    }
    case 3:
      take_picture();
      
      if ((interval == 0) || (shot_count == 0)){
        state = 0;
        return;
      }
      
      state = 4;
      
      // Break statement ommitted intentionally
    case 4:
      if (lcd_key == btnSELECT){
        state = 0;
        break;
      }
      
      if(intervalcounter > 1)
        delay(1000);
      else
        delay(500);  // The other 500 msec will be spent taking the shot
        
      intervalcounter--;
      
      if(intervalcounter == 0){
        intervalcounter = interval;
        shotcounter--;

        // Take the shot
        take_picture();
        break;
      }
      
      if(shotcounter == 1){
        state = 0;
        interval = 0;
        shot_count = 0;
      }
      
      String interval_str(intervalcounter);
      char interval_char[10];
      interval_str.toCharArray(interval_char, sizeof(interval_char));
      lcd.setCursor(0,1);
      lcd.print("I:");
      lcd.print(interval_char);
      lcd.print(" S:");
      
      String shot_count_str(shotcounter);
      char shot_count_char[10];
      shot_count_str.toCharArray(shot_count_char, sizeof(shot_count_char));
      lcd.print(shot_count_char);
      lcd.print("                ");
      
      break;

  }

  if(butt_press){
    // Allow button to be kept pressed
    delay(250);
      
  }else{
    // Make sure the key is released before we continue
    while(lcd_key != btnNONE){
      lcd_key = read_LCD_buttons();
    }
  }
}

void setup()
{
 lcd.begin(16, 2);              // start the library
}
  
void loop()
{
  state_machine();
}
