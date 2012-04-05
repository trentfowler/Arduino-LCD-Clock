#include <LiquidCrystal.h>
#include <Time.h>

//=============================================================================
//Date class
class Date {
private: 
  int _month;
  int _day;
  int _year;
public:
  Date();
  Date(int month, int day, int year);
  void setMonth(int month);
  void setDay(int day);
  void setYear(int year);
  int getMonth();
  int getDay();
  int getYear();
};

Date::Date() {
  _month = 1;
  _day = 1;
  _year = 2012;
}

Date::Date(int month, int day, int year) {
  _month = month;
  _day = day;
  _year = year;
}

int Date::getMonth() {
  return _month;
}

int Date::getDay() {
  return _day;
}

int Date::getYear() {
  return _year;
}

void Date::setMonth(int month) {
  _month = month;
}

void Date::setDay(int day) {
  _day = day;
}

void Date::setYear(int year) {
  _year = year;
}

//=============================================================================

//default time
int _hr = 0;
int _min = 0;
int _sec = 0;
int _month = 1;
int _day = 1;
int _year = 2012;

//the last time values that appeared on the lcd, to be compared with the 
//current time values to determine if it is time to refresh the lcd
int prevHour = _hr;
int prevMin = _min;
int prevDay = _day;
int prevSec = _sec;

//toggle for when to show/hide seconds
bool hideSeconds = false;

//...
const int DAYLIGHT_SAVINGS_ENABLE_OPTION = 0;
const int DAYLIGHT_SAVINGS_CANCEL_OPTION = 1;

int daylightSavingsOption = DAYLIGHT_SAVINGS_ENABLE_OPTION;

bool adjustForDaylightSavings = true;

Date* daylightSavings[] = {
  new Date(3, 11, 2012), new Date(11, 4, 2012),
  new Date(3, 10, 2013), new Date(11, 3, 2013),
  new Date(3, 9, 2014), new Date(11, 2, 2014),
  new Date(3, 8, 2015), new Date(11, 1, 2015),
  new Date(3, 13, 2016), new Date(11, 6, 2016),
  new Date(3, 12, 2017), new Date(11, 5, 2017),
  new Date(3, 11, 2018), new Date(11, 4, 2018),
  new Date(3, 10, 2019), new Date(11, 3, 2019),
  new Date(3, 8, 2020), new Date(11, 1, 2020),
  new Date(3, 14, 2021), new Date(11, 7, 2021),
  new Date(3, 13, 2022), new Date(11, 6, 2022),
  new Date(3, 12, 2023), new Date(11, 5, 2023),
  new Date(3, 10, 2024), new Date(11, 3, 2024),
  new Date(3, 9, 2025), new Date(11, 2, 2025)
  };

const int numberOfSavingsYears = 14;
const int savingsDataMaxYear = 2025;

bool isDaylightSavingsDay = false;

//...
const int EXIT_INDEX = -1;

int topIndex = 0;
int selectedIndex = 0;
int previousSelectionIndex = EXIT_INDEX;

//month and week constants
const char JANUARY[4] = "JAN";
const char FEBRUARY[4] = "FEB";
const char MARCH[4] = "MAR";
const char APRIL[6] = "APRIL";
const char MAY[4] = "MAY";
const char JUNE[5] = "JUNE";
const char JULY[5] = "JULY";
const char AUGUST[4] = "AUG";
const char SEPTEMBER[4] = "SEP";
const char OCTOBER[4] = "OCT";
const char NOVEMBER[4] = "NOV";
const char DECEMBER[4] = "DEC";

const char SUNDAY[4] = "SUN";
const char MONDAY[4] = "MON";
const char TUESDAY[5] = "TUES";
const char WEDNESDAY[4] = "WED";
const char THURSDAY[6] = "THURS";
const char FRIDAY[4] = "FRI";
const char SATURDAY[4] = "SAT";

//stopwatch variables
const int STOPWATCH_CANCEL_INDEX = 1;
const int STOPWATCH_START_INDEX = 0;

int stopwatchSelectedIndex = STOPWATCH_START_INDEX;

long timeElapsed = 0;

char* stopwatchOptions[] = {
  "Pause", "Reset", "Cancel"};

int numberOfStopwatchOptions = 3;

const int STOPWATCH_PAUSE_OPTION = 0;
const int STOPWATCH_RESET_OPTION = 1;
const int STOPWATCH_CANCEL_OPTION = 2;

int stopwatchOption = STOPWATCH_PAUSE_OPTION;

//a single space character
const char BLANK = ' ';

//initialize the numbers of the interface pins and create a LiquidCrystal object named lcd
int RS = 7;
int EN = 8;
int DB4 = 9;
int DB5 = 10;
int DB6 = 11;
int DB7 = 12;
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

//custom characters
byte down_tick[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B10001,
  B01010,
  B00100,
};

byte right_tick[8] = {
  B00000,
  B01000,
  B00100,
  B00010,
  B00100,
  B01000,
  B00000,
};

byte top_2[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte bottom_2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte top_2_and_bottom_2[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};

byte all[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte bottom_3_and_center_3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B01110,
  B01110
};

byte colon_bottom[8] = { //use a period for top colon
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

//...
bool showBigClock = false;

//Time Zone variables
char timeZoneOverflowIndicator = (char)0;

const int NO_TIME_ZONE_INDEX = -1;
const int PACIFIC_INDEX = 0;
const int MOUNTAIN_INDEX = 1;
const int CENTRAL_INDEX = 2;
const int EASTERN_INDEX = 3;

const int NUMBER_OF_ZONES = 4;

int timeZone = NO_TIME_ZONE_INDEX;

int selectedZone = 0;

char* timeZones[] = {"Pacific", "Mountain", "Central", "Eastern"};

//button variables
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
const int BUTTON_3_PIN = 4;

//menu item variables
const char* HIDE_SECONDS_STRING = "Hide seconds";
const char* SHOW_SECONDS_STRING = "Show seconds";
const char* BIG_CLOCK_STRING = "Hide date";
const char* SMALL_CLOCK_STRING = "Show date";

char* menuItems[] = {
  "Set time", 
  "Set date", 
  "Stopwatch", 
  (char*)BIG_CLOCK_STRING, 
  (char*)HIDE_SECONDS_STRING, 
  "DST", 
  "Time zone", 
  "Cancel"
};

//char* main[] = {"Toggle view", "Alarm", "Stopwatch", "Timer", "Settings", "Cancel"};
//char* settings[] = {"Date/Time", "Clock options", "DST", "Time zone", "Brightness", "Cancel"};
//char* date_time[] = {"Set date", "Set time", "Cancel"};
//char* clock_options[] = {"Hide date", "Hide seconds", "Cancel"};
//char* yes_no_cancel[] = {"Yes", "No", "Cancel"};

int numberOfMenuItems = 8;

const int SET_TIME_INDEX = 0;
const int SET_DATE_INDEX = 1;
const int STOPWATCH_INDEX = 2;
const int BIG_CLOCK_INDEX = 3;
const int HIDE_SECONDS_INDEX = 4;
const int DAYLIGHT_SAVINGS_INDEX = 5;
const int TIME_ZONE_INDEX = 6;
const int CANCEL_INDEX = 7;
//const int ALARMS_INDEX =
//const int REMINDERS_INDEX = 
//const int TIMER_INDEX = 

void setup() {

  //button 1 -- menu/enter/cancel button
  pinMode(BUTTON_1_PIN, INPUT);
  digitalWrite(BUTTON_1_PIN, HIGH);

  //button 2 -- "up" button
  pinMode(BUTTON_2_PIN, INPUT);
  digitalWrite(BUTTON_2_PIN, HIGH);

  //button 3 -- "down" button
  pinMode(BUTTON_3_PIN, INPUT);
  digitalWrite(BUTTON_3_PIN, HIGH);

  setTime(_hr, _min, _sec, _day, _month, _year);

  lcd.begin(16, 2); //initialize lcd rows and cols
  
  lcd.createChar(0, down_tick);
  lcd.createChar(1, right_tick);
  lcd.createChar(2, top_2);
  lcd.createChar(3, bottom_2);
  lcd.createChar(4, top_2_and_bottom_2);
  lcd.createChar(5, all);
  lcd.createChar(6, bottom_3_and_center_3);
  lcd.createChar(7, colon_bottom);
  
  displayDateAndTime();
}

void loop() {

  if (adjustForDaylightSavings == true && isDaylightSavingsDay == true && hour() == 2) {

    isDaylightSavingsDay = false;
    if (month() < 6) 
      setTime(hour() + 1, minute(), second(), day(), month(), year());
    else setTime(hour() - 1, minute(), second(), day(), month(), year());

    (showBigClock == false) ? displayTime() : bigClock();

  }

  if (prevMin != minute()) {
    (showBigClock == false) ? displayTime() : bigClock();
  } 
  else if (hideSeconds != true) {
    if (prevSec != second()) {
      if (showBigClock == false) displayTime();
    }
  }

  //refreshes the lcd when the date changes
  if (prevDay != day()) {

    if (showBigClock == false) displayDate();

    //checks if new date is daylight savings time
    for (int i = 0; i < numberOfSavingsYears * 2; i++) {
      if (daylightSavings[i]->getYear() == year() &&
        daylightSavings[i]->getMonth() == month() &&
        daylightSavings[i]->getDay() == day()) {
        isDaylightSavingsDay = true;
      }
    }

  }

  //user pressed button 1, bring up menu
  if (digitalRead(BUTTON_1_PIN) == LOW) {
    while (digitalRead(BUTTON_1_PIN) == LOW) { } //wait
    delay(200);

    showMenu();

    while (true) {

      //user pressed button 1 ("enter" button) while a menu item was selected
      if (digitalRead(BUTTON_1_PIN) == LOW) {

        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);

        previousSelectionIndex = EXIT_INDEX;

        if (selectedIndex == SET_TIME_INDEX) {
          setTime();
        }

        else if (selectedIndex == SET_DATE_INDEX) {
          setDate();
        }

        else if (selectedIndex == STOPWATCH_INDEX) {
          stopwatch();
        }

        //else if (selectedIndex == ALARMS_INDEX) { }
        //else if (selectedIndex == REMINDERS_INDEX) { }
        //else if (selectedIndex == TIMER_INDEX) { }

        else if (selectedIndex == BIG_CLOCK_INDEX) {
          showBigClock = !showBigClock;
          (showBigClock == false) ? menuItems[BIG_CLOCK_INDEX] = (char*)BIG_CLOCK_STRING : 
                                    menuItems[BIG_CLOCK_INDEX] = (char*)SMALL_CLOCK_STRING;
                                    
          hideSeconds = !hideSeconds;
          (hideSeconds == false) ? menuItems[HIDE_SECONDS_INDEX] = (char*)HIDE_SECONDS_STRING : 
                                   menuItems[HIDE_SECONDS_INDEX] = (char*)SHOW_SECONDS_STRING;
        }

        else if (selectedIndex == DAYLIGHT_SAVINGS_INDEX) {
          daylightSavingsDialog();
        }

        else if (selectedIndex == HIDE_SECONDS_INDEX) {
          hideSeconds = !hideSeconds;
          (hideSeconds == false) ? menuItems[HIDE_SECONDS_INDEX] = (char*)HIDE_SECONDS_STRING : 
                                   menuItems[HIDE_SECONDS_INDEX] = (char*)SHOW_SECONDS_STRING;
          
          if (hideSeconds == false && showBigClock == true) {
            showBigClock = false;
            menuItems[BIG_CLOCK_INDEX] = (char*)BIG_CLOCK_STRING;
          }
        }
        
        else if (selectedIndex == TIME_ZONE_INDEX && timeZone != NO_TIME_ZONE_INDEX) {
          
          const int SET_TIME_ZONE_INDEX = 0;
          const int CHANGE_TIME_ZONE_INDEX = 1;
          const int CANCEL_INDEX = 2;
          
          char* options[] = {"Set time zone", "Change zones", "Cancel"};
          int numberOfOptions = 3;
          
          int topOption = 0;
          int selectedOption = 0;
          
          int lastTopOption = topOption;
          int lastSelectedOption = selectedOption;
          
          int option = -1;
          
          lcd.clear();
          lcd.print((char)1);
          lcd.print(options[topOption]);
          lcd.setCursor(0, 1);
          lcd.print(BLANK);
          lcd.print(options[topOption + 1]);
          lcd.setCursor(15, 1);
          timeZoneOverflowIndicator = (char)0;
          lcd.print(timeZoneOverflowIndicator);
          
          while (digitalRead(BUTTON_1_PIN) != LOW) {
            
            if (digitalRead(BUTTON_2_PIN) == LOW) {
              
              while (digitalRead(BUTTON_2_PIN) == LOW) { }
              delay(200);
              
              if (selectedOption == topOption) {
                selectedOption--;
                topOption--;
              } else selectedOption--;
              
              if (topOption > numberOfOptions - 2) topOption = numberOfOptions - 2;
              if (topOption < 0) topOption = 0;
              if (selectedOption < topOption) selectedOption = topOption;
              if (selectedOption > topOption + 1) selectedOption = topOption + 1;
            }
            
            if (digitalRead(BUTTON_3_PIN) == LOW) {
              
              while (digitalRead(BUTTON_3_PIN) == LOW) { }
              delay(200);
              
              if (selectedOption != topOption) {
                selectedOption++;
                topOption++;
              } else selectedOption++;
              
              if (topOption > numberOfOptions - 2) topOption = numberOfOptions - 2;
              if (topOption < 0) topOption = 0;
              if (selectedOption < topOption) selectedOption = topOption;
              if (selectedOption > topOption + 1) selectedOption = topOption + 1;
            }
            
            if (topOption != lastTopOption) {
                lastTopOption = topOption;
                lcd.clear();
                (selectedOption == topOption) ? lcd.print((char)1) : lcd.print(BLANK);
                lcd.print(options[topOption]);
                lcd.setCursor(0, 1);
                (selectedOption == topOption + 1) ? lcd.print((char)1) : lcd.print(BLANK);
                lcd.print(options[topOption + 1]);
                if (topOption > 0) {
                  timeZoneOverflowIndicator = '^';
                  lcd.setCursor(15, 0);
                  lcd.print(timeZoneOverflowIndicator);
                }
                if (topOption < numberOfOptions - 2) {
                  timeZoneOverflowIndicator = (char)0;
                  lcd.setCursor(15, 1);
                  lcd.print(timeZoneOverflowIndicator);
                }
              } 
              else if (selectedOption != lastSelectedOption) {
                lcd.setCursor(0, 0);
                (selectedOption == topOption) ? lcd.print((char)1) : lcd.print(BLANK);
                lcd.setCursor(0, 1);
                (selectedOption == topOption + 1) ? lcd.print((char)1) : lcd.print(BLANK);
              }
              
              (selectedOption == topOption) ? option = topOption : option = topOption + 1;
          }
          
          while (digitalRead(BUTTON_1_PIN) == LOW) { }
          delay(200);
          
          if (option == SET_TIME_ZONE_INDEX) {
            setTimeZone();
          }
          
          else if (option == CHANGE_TIME_ZONE_INDEX) {
            changeTimeZone();
          }
          
          else if (option == CANCEL_INDEX) {
            
          }
        }
        
        else if (selectedIndex == TIME_ZONE_INDEX) {
          const int SET_TIME_ZONE_INDEX = 0;
          const int CANCEL_INDEX = 1;
          
          char* options[] = {"Set time zone", "Cancel"};
          int numberOfOptions = 2;
          
          int selectedOption = SET_TIME_ZONE_INDEX;
          int lastSelectedOption = selectedOption;
          
          lcd.clear();
          lcd.print((char)1);
          lcd.print(options[SET_TIME_ZONE_INDEX]);
          lcd.setCursor(0, 1);
          lcd.print(BLANK);
          lcd.print(options[CANCEL_INDEX]);
          
          while (digitalRead(BUTTON_1_PIN) != LOW) {
            
            if (digitalRead(BUTTON_2_PIN) == LOW) {
              while (digitalRead(BUTTON_2_PIN) == LOW) { }
              delay(200);
              selectedOption = SET_TIME_ZONE_INDEX;
              lcd.setCursor(0, 0);
              lcd.print((char)1);
              lcd.setCursor(0, 1);
              lcd.print(BLANK);
            }
            
            if (digitalRead(BUTTON_3_PIN) == LOW) {
              while (digitalRead(BUTTON_3_PIN) == LOW) { }
              delay(200);
              selectedOption = CANCEL_INDEX;
              lcd.setCursor(0, 0);
              lcd.print(BLANK);
              lcd.setCursor(0, 1);
              lcd.print((char)1);              
            }
          }
          
          while (digitalRead(BUTTON_1_PIN) == LOW) { }
          delay(200);
          
          if (selectedOption == SET_TIME_ZONE_INDEX) {
            setTimeZone();
          }
        }
        
        else if (selectedIndex == CANCEL_INDEX) {
          //move the cursor back to the top of the menu
          selectedIndex = 0;
          topIndex = 0;
        }

        break;
      }

      //user pushed button 2 ("up" button) while inside the menu so 
      //adjust menu position and selection
      if (digitalRead(BUTTON_2_PIN) == LOW) {
        if (selectedIndex == topIndex) {
          topIndex--;
          selectedIndex--;
        } 
        else selectedIndex--;
        showMenu();
        delay(200); //don't wait
      }

      //user pushed button 3 ("down" button) while inside the menu so 
      //adjust menu position and selection
      if (digitalRead(BUTTON_3_PIN) == LOW) {
        if (selectedIndex == topIndex) {
          selectedIndex++;
        } 
        else {
          topIndex++;
          selectedIndex++;
        }
        showMenu();
        delay(200); //don't wait
      }
    } //end while (true)

    lcd.clear();
    //displayDateAndTime();
    (showBigClock == false) ? displayDateAndTime() : bigClock();
    while (digitalRead(BUTTON_1_PIN) == LOW) { 
    } //wait
    delay(200);
  }

  //user pressed button 2
  if (digitalRead(BUTTON_2_PIN) == LOW) {
    //...
  }

  //user pressed button 3
  if (digitalRead(BUTTON_3_PIN) == LOW) {
    //...
  }
}

void showMenu() {
  
  //error-proof topIndex and SelectedIndex
  if (topIndex < 0) {
    topIndex = 0;
  }
  if (selectedIndex < 0) {
    selectedIndex = 0;
  }
  if (topIndex > numberOfMenuItems - 2) {
    topIndex = numberOfMenuItems - 2;
  }
  if (selectedIndex > numberOfMenuItems - 1) {
    selectedIndex = numberOfMenuItems - 1;
  }

  //output (if not redundant)
  if (selectedIndex != previousSelectionIndex) {
    lcd.clear();
    if (selectedIndex == topIndex) lcd.print((char)1);
    else lcd.print(BLANK);
    lcd.print(menuItems[topIndex]);
    lcd.setCursor(0, 1);
    if (selectedIndex != topIndex) lcd.print((char)1);
    else lcd.print(BLANK);
    lcd.print(menuItems[topIndex + 1]);
    if (topIndex != 0) {
      lcd.setCursor(15, 0); 
      lcd.print("^");
    }
    if (topIndex + 1 < numberOfMenuItems - 1) {
      lcd.setCursor(15, 1);
      lcd.print((char)0);
    }
  }

  previousSelectionIndex = selectedIndex;
}

void displayDateAndTime() {
  displayDate();
  displayTime();
}

void displayDate() {
  //set cursor to beginning of line
  lcd.setCursor(0, 0);

  //output date
  time_t t = now();

  switch(weekday(t)) {
  case 1: { lcd.print(SUNDAY); break; }
  case 2: { lcd.print(MONDAY); break; }
  case 3: { lcd.print(TUESDAY); break; }
  case 4: { lcd.print(WEDNESDAY); break; }
  case 5: { lcd.print(THURSDAY); break; }
  case 6: { lcd.print(FRIDAY); break; }
  case 7: { lcd.print(SATURDAY); break; }
  };
  lcd.print(BLANK);
  switch(month(t)) {
  case 1: { lcd.print(JANUARY); break; }
  case 2: { lcd.print(FEBRUARY); break; }
  case 3: { lcd.print(MARCH); break; }
  case 4: { lcd.print(APRIL); break; }
  case 5: { lcd.print(MAY); break; }
  case 6: { lcd.print(JUNE); break; }
  case 7: { lcd.print(JULY); break; }
  case 8: { lcd.print(AUGUST); break; }
  case 9: { lcd.print(SEPTEMBER); break; }
  case 10: { lcd.print(OCTOBER); break; }
  case 11: { lcd.print(NOVEMBER); break; }
  case 12: { lcd.print(DECEMBER); break; }
  };
  lcd.print(BLANK);
  lcd.print(day(t));
  lcd.print("     "); //padding

  prevDay = day(t);

}

void displayTime() {
  //set cursor to beginning of line
  lcd.setCursor(0, 1);

  //output current time
  time_t t = now();
  lcd.print(hourFormat12(t));
  lcd.print(":");
  if (minute(t) < 10) lcd.print("0");
  lcd.print(minute(t));
  if (hideSeconds == false) {
    lcd.print(":");
    if (second(t) < 10) lcd.print("0");
    lcd.print(second(t));
  }
  if (isAM(t)) lcd.print(" AM ");
  else lcd.print(" PM ");

  if (hideSeconds == true) lcd.print("     "); //padding

  //update with values last outputted to lcd
  prevHour = hour(t);
  prevMin = minute(t);
  prevSec = second(t);
}

void displayDate(int m, int d, int y) {
  switch(m) {
  case 1: { lcd.print(JANUARY); break; }
  case 2: { lcd.print(FEBRUARY); break; }
  case 3: { lcd.print(MARCH); break; }
  case 4: { lcd.print(APRIL); break; }
  case 5: { lcd.print(MAY); break; }
  case 6: { lcd.print(JUNE); break; }
  case 7: { lcd.print(JULY); break; }
  case 8: { lcd.print(AUGUST); break; }
  case 9: { lcd.print(SEPTEMBER); break; }
  case 10: { lcd.print(OCTOBER); break; }
  case 11: { lcd.print(NOVEMBER); break; }
  case 12: { lcd.print(DECEMBER); break; }
  };
  lcd.print(" ");
  lcd.print(d);
  lcd.print(", ");
  lcd.print(y);
  lcd.print("     "); //padding, gets rid of letters that remain when a string is shorter than the last string
}

void displayTime(int hr, int min, int sec) {
  if (hr % 12 == 0) lcd.print("12");
  else lcd.print(hr % 12);
  lcd.print(":");
  if (min < 10) lcd.print("0");
  lcd.print(min);
  lcd.print(":");
  if (sec < 10) lcd.print("0");
  lcd.print(sec);
  if (hr < 12) lcd.print(" AM ");
  else lcd.print(" PM ");
}

void setTime() {

  time_t t = now();
  int hr = hour(t);
  int min = minute(t);
  int sec = 0;

  int mode = 0;
  while (mode < 3) {

    //mode = 0
    if (mode == 0) {
      lcd.clear();
      lcd.print("Set time: hours");
      lcd.setCursor(0, 1);
      displayTime(hr, min, sec);
    }

    while (mode == 0) {
      if (digitalRead(BUTTON_1_PIN) == LOW) {
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++;
      }
      else if (digitalRead(BUTTON_2_PIN) == LOW) { //add hour
        if (hr == 23) {
          hr = 0;
        } 
        else hr++;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }
      else if (digitalRead(BUTTON_3_PIN) == LOW) { //subtract hour
        if (hr == 0) {
          hr = 23;
        } 
        else hr--;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }
    } //end while (mode = 0)
    //end mode = 0

      //mode = 1
    if (mode == 1) {
      lcd.clear();
      lcd.print("Set time: minutes");
      lcd.setCursor(0, 1);
      displayTime(hr, min, sec);
    }

    while (mode == 1) {
      if (digitalRead(BUTTON_1_PIN) == LOW) {
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++;
      }

      else if (digitalRead(BUTTON_2_PIN) == LOW) { //add minute
        if (min == 59) {
          min = 0;
        } 
        else min++;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }

      else if (digitalRead(BUTTON_3_PIN) == LOW) { //subtract minute
        if (min == 0) {
          min = 59;
        } 
        else min--;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }
    } //end while (mode == 1)
    //end mode = 1

    //mode = 2
    if (mode == 2) {
      lcd.clear();
      lcd.print("Set time: seconds");
      lcd.setCursor(0, 1);
      displayTime(hr, min, sec);
    }

    while (mode == 2) {
      if (digitalRead(BUTTON_1_PIN) == LOW) {
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++;
      }

      else if (digitalRead(BUTTON_2_PIN) == LOW) { //add second
        if (sec == 59) {
          sec = 0;
        } 
        else sec++;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }

      else if (digitalRead(BUTTON_3_PIN) == LOW) { //subtract second
        if (sec == 0) {
          sec = 59;
        } 
        else sec--;
        lcd.setCursor(0, 1);
        displayTime(hr, min, sec);
        delay(200);
      }
    } //end while (mode == 2)
    //end mode = 2

  } //end while (mode < 3)

  setTime(hr, min, sec, day(), month(), year());

  isDaylightSavingsDay = false;
  for (int i = 0; i < numberOfSavingsYears * 2; i++) {
    if (daylightSavings[i]->getYear() == year() &&
      daylightSavings[i]->getMonth() == month() &&
      daylightSavings[i]->getDay() == day()) {
      isDaylightSavingsDay = true;
    }
  }

}

void setDate() {
  time_t u = now();
  int m = month(u);
  int d = day(u);
  int y = year(u);

  lcd.clear();
  lcd.print("Set date");
  lcd.setCursor(0, 1);
  displayDate(m, d, y);

  int mode = 0;
  while (mode < 3) {

    if (mode == 0) {
      lcd.clear();
      lcd.print("Set date: year");
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
    }

    while (mode == 0) { //loop to set year, loop until user presses button 1
      if (digitalRead(BUTTON_1_PIN) == LOW) { //user pressed button 1, go to next: year --> month
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++; 
      }
      if (digitalRead(BUTTON_2_PIN) == LOW) { //user pressed button to increase year
        y++;
      }
      if (digitalRead(BUTTON_3_PIN) == LOW) { //user pressed button to decrease year
        y--;
      }
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
      delay(200);
    } //end while (mode == 0)

    if (mode == 1) {
      lcd.clear();
      lcd.print("Set date: month");
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
    }

    while (mode == 1) { //loop to set month, loop until user presses button 1
      if (digitalRead(BUTTON_1_PIN) == LOW) { //user pressed button 1, go to next: month --> day
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++; 
      }
      if (digitalRead(BUTTON_2_PIN) == LOW) { //user pressed button to increase month
        if (m == 12) m = 1;
        else m++;
      }
      if (digitalRead(BUTTON_3_PIN) == LOW) { //user pressed button to decrease month
        if (m == 1) m = 12;
        else m--;
      }
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
      delay(200);
    } //end while (mode == 1)

    if (mode == 2) {
      lcd.clear();
      lcd.print("Set date: day");
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
    }

    while (mode == 2) {
      if (digitalRead(BUTTON_1_PIN) == LOW) { //user pressed button 1, go to next: day --> DONE
        while (digitalRead(BUTTON_1_PIN) == LOW) { 
        } //wait
        delay(200);
        mode++;
      }
      else if (digitalRead(BUTTON_2_PIN) == LOW) { //user pressed button to increase day
        if (m == 2) {
          if (d == 29) d = 1;
          else if (d == 28) {
            if ((y % 4) == 0) d++;
            else d = 1;
          } 
          else d++;
        }
        else if (m == 9 || m == 4 || m == 6 || m == 11) {
          if (d == 30) d = 1;
          else d++;
        }
        else {
          if (d == 31) d = 1;
          else d++;
        }              
      }
      else if (digitalRead(BUTTON_3_PIN) == LOW) { //user pressed button to decrease day
        if (m == 2) {
          if (d == 1) {
            if (y % 4 == 0) d = 29;
            else d = 28;
          } 
          else d--;
        }
        else if (m == 9 || m == 4 || m == 6 || m == 11) {
          if (d == 1) d = 30;
          else d--;
        }
        else {
          if (d == 1) d = 31;
          else d--;
        }
      }
      lcd.setCursor(0, 1);
      displayDate(m, d, y);
      delay(200);
    } //end while (mode == 2)
  } //end while (mode < 3)

  setTime(hour(), minute(), second(), d, m, y);

  if ( (year() > savingsDataMaxYear) || 
    (year() < (savingsDataMaxYear - (numberOfSavingsYears - 1))) ) {
    adjustForDaylightSavings = false;
  }

  isDaylightSavingsDay = false;
  for (int i = 0; i < numberOfSavingsYears * 2; i++) {
    if (daylightSavings[i]->getYear() == year() &&
      daylightSavings[i]->getMonth() == month() &&
      daylightSavings[i]->getDay() == day()) {
      isDaylightSavingsDay = true;
    }
  }
}

void stopwatch() {

  stopwatchSelectedIndex = STOPWATCH_START_INDEX;

  lcd.clear();
  lcd.print((char)1);
  lcd.print("Start");
  lcd.setCursor(0, 1);
  lcd.print(" Cancel");

  while (digitalRead(BUTTON_1_PIN) != LOW) {
    if (digitalRead(BUTTON_2_PIN) == LOW) { //up
      while (digitalRead(BUTTON_2_PIN) == LOW) { 
      } //wait
      lcd.setCursor(0, 0);
      lcd.print((char)1);
      lcd.setCursor(0, 1);
      lcd.print(BLANK);
      stopwatchSelectedIndex = STOPWATCH_START_INDEX;
    }

    if (digitalRead(BUTTON_3_PIN) == LOW) { //down
      while (digitalRead(BUTTON_3_PIN) == LOW) { 
      } //wait
      lcd.setCursor(0, 0);
      lcd.print(BLANK);
      lcd.setCursor(0, 1);
      lcd.print((char)1);
      stopwatchSelectedIndex = STOPWATCH_CANCEL_INDEX;
    }
  }

  if (digitalRead(BUTTON_1_PIN) == LOW) { //select

    while (digitalRead(BUTTON_1_PIN) == LOW) { 
    } //wait
    delay(200);

    if (stopwatchSelectedIndex == STOPWATCH_START_INDEX) {
      lcd.clear();
      showStopwatchOptions();
      long initialMillis = millis();
      bool paused = false;
      while (true) {

        if (!paused) {
          lcd.setCursor(0, 0);
          timeElapsed = millis() - initialMillis;
          lcd.print(timeElapsed / 1000.0);
        }

        if (digitalRead(BUTTON_1_PIN) == LOW) { 
          while (digitalRead(BUTTON_1_PIN) == LOW) { 
          } //wait
          delay(200);

          if (stopwatchOption == STOPWATCH_PAUSE_OPTION) {
            if (paused) {
              stopwatchOptions[STOPWATCH_PAUSE_OPTION] = "Pause";
            }

            if (!paused) {
              stopwatchOptions[STOPWATCH_PAUSE_OPTION] = "Restart";
            }
            showStopwatchOptions();
            paused = !paused;
          }

          if (stopwatchOption == STOPWATCH_CANCEL_OPTION) {
            stopwatchOptions[STOPWATCH_PAUSE_OPTION] = "Pause";
            stopwatchOption = STOPWATCH_PAUSE_OPTION;
            lcd.clear();
            break;
          }

          if (stopwatchOption == STOPWATCH_RESET_OPTION) {
            stopwatchOptions[STOPWATCH_PAUSE_OPTION] = "Pause";
            stopwatchOption = STOPWATCH_PAUSE_OPTION;
            lcd.clear();
            stopwatch();
          }
        }

        if (digitalRead(BUTTON_2_PIN) == LOW) {
          while (digitalRead(BUTTON_2_PIN) == LOW) { 
          } //wait
          stopwatchOption--;
          showStopwatchOptions();
        }

        if (digitalRead(BUTTON_3_PIN) == LOW) {
          while (digitalRead(BUTTON_3_PIN) == LOW) { 
          } //wait
          stopwatchOption++;
          showStopwatchOptions();
        }

      }
    } 
    else if (stopwatchSelectedIndex == 1) {
      //...
    }
  }

  while (digitalRead(BUTTON_1_PIN) == LOW) { 
  } //wait
  delay(200);
}

void showStopwatchOptions() {
  if (stopwatchOption < 0) 
    stopwatchOption = 0;
  else if (stopwatchOption > numberOfStopwatchOptions - 1) 
    stopwatchOption = numberOfStopwatchOptions - 1;
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) lcd.print(BLANK);
  lcd.setCursor(0, 1);
  lcd.print(stopwatchOptions[stopwatchOption]);
  if (stopwatchOption < numberOfStopwatchOptions - 1) {
    lcd.setCursor(15, 1);
    lcd.print((char)0);
  }
}

void daylightSavingsDialog() {

  daylightSavingsOption = DAYLIGHT_SAVINGS_ENABLE_OPTION;

  lcd.clear();
  lcd.print((char)1);
  if (adjustForDaylightSavings == true) lcd.print("Disable");
  else lcd.print("Enable");
  lcd.setCursor(0, 1);
  lcd.print(" Cancel");

  while (digitalRead(BUTTON_1_PIN) != LOW) {

    if (digitalRead(BUTTON_2_PIN) == LOW) {
      while (digitalRead(BUTTON_2_PIN) == LOW) { 
      } //wait
      delay(200);
      daylightSavingsOption = DAYLIGHT_SAVINGS_ENABLE_OPTION;
      lcd.setCursor(0, 0);
      lcd.print((char)1);
      lcd.setCursor(0, 1);
      lcd.print(" ");
    }

    if (digitalRead(BUTTON_3_PIN) == LOW) {
      while (digitalRead(BUTTON_3_PIN) == LOW) { 
      } //wait
      delay(200);
      daylightSavingsOption = DAYLIGHT_SAVINGS_CANCEL_OPTION;
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print((char)1);
    }

  }

  while (digitalRead(BUTTON_1_PIN) == LOW) { } //wait
  delay(200);

  if (daylightSavingsOption == DAYLIGHT_SAVINGS_ENABLE_OPTION) {
    adjustForDaylightSavings = !adjustForDaylightSavings;
    lcd.clear();
    lcd.print("Daylight savings");
    lcd.setCursor(0, 1);
    if (adjustForDaylightSavings == true) lcd.print("enabled");
    else lcd.print("disabled");
    delay(2000);
    daylightSavingsDialog();
  } //else daylightSavingsOption == DAYLIGHT_SAVINGS_CANCEL_OPTION

}

void bigClock() {
  time_t t = now();
  int h = hour(t);
  int m = minute(t);
  
  lcd.clear();
  int cursor_column_value = 0;
  if (h < 10) cursor_column_value = bigNumber(0, cursor_column_value);
  cursor_column_value = bigNumber(h, cursor_column_value);
  
  //output a colon
  lcd.setCursor(7, 0);
  lcd.print('.');
  lcd.setCursor(7, 1);
  lcd.print((char)7);
  
  if (m < 10) cursor_column_value = bigNumber(0, cursor_column_value);
  cursor_column_value = bigNumber(m, cursor_column_value);
  
  prevHour = hour(t);
  prevMin = minute(t);
  prevSec = second(t);
}

int bigNumber(int num, int cursor_col) {
  if (num >= 10) {
    bigNumber(num / 10, cursor_col);
    bigNumber(num % 10, cursor_col + 4);
  } 
  else {
    switch(num) {
    case 0: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)2);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)5);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    case 1: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)2);
        lcd.print((char)5);
        lcd.print(BLANK);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)3);
        lcd.print((char)5);
        lcd.print((char)3);
        break;
    }
    case 2: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)4);
        lcd.print((char)4);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)5);
        lcd.print((char)3);
        lcd.print((char)3);
        break;
    }
    case 3: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)2);
        lcd.print((char)4);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)3);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    case 4: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)3);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print(BLANK);
        lcd.print(BLANK);
        lcd.print((char)5);
        break;
    }
    case 5: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)4);
        lcd.print((char)4);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)3);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    case 6: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)4);
        lcd.print((char)4);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)5);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    case 7: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)2);
        lcd.print((char)2);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print(BLANK);
        lcd.print(BLANK);
        lcd.print((char)5);
        break;
    }
    case 8: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)4);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)5);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    case 9: {
        lcd.setCursor(cursor_col, 0);
        lcd.print((char)5);
        lcd.print((char)4);
        lcd.print((char)5);
        lcd.setCursor(cursor_col, 1);
        lcd.print((char)3);
        lcd.print((char)3);
        lcd.print((char)5);
        break;
    }
    };
  }
  
  if (num >= 10)
    return cursor_col + 8;
  else return cursor_col + 4;
  
}

void setTimeZone() {
  lcd.clear();
  lcd.print("Set time zone");
  lcd.setCursor(0, 1);
  lcd.print(timeZones[selectedZone]);
  lcd.setCursor(15, 1);
  lcd.print(timeZoneOverflowIndicator);
  
  while (digitalRead(BUTTON_1_PIN) != LOW) {
    
    if (digitalRead(BUTTON_2_PIN) == LOW) {
      while (digitalRead(BUTTON_2_PIN) == LOW) { }
      delay(200);
      selectedZone--;
      if (selectedZone < 0) {
        selectedZone = 0;
      }
      if (selectedZone == 0) {
        timeZoneOverflowIndicator = (char)0;
      }
      lcd.setCursor(0, 1);
      lcd.print(timeZones[selectedZone]);
      lcd.print(BLANK);
      lcd.setCursor(15, 1);
      lcd.print(timeZoneOverflowIndicator);
    }
    
    if (digitalRead(BUTTON_3_PIN) == LOW) {
      while (digitalRead(BUTTON_3_PIN) == LOW) { }
      delay(200);
      selectedZone++;
      if (selectedZone > NUMBER_OF_ZONES - 1) {
        selectedZone = NUMBER_OF_ZONES - 1;
      }
      if (selectedZone == NUMBER_OF_ZONES - 1) {
        timeZoneOverflowIndicator = '^';
      }
      lcd.setCursor(0, 1);
      lcd.print(timeZones[selectedZone]);
      lcd.print(BLANK);
      lcd.setCursor(15, 1);
      lcd.print(timeZoneOverflowIndicator);
    }
    
  }
  
  while (digitalRead(BUTTON_1_PIN) == LOW) { }
  delay(200);
  
  timeZone = selectedZone;
  
  lcd.clear();
  lcd.print("Time zone set");
  lcd.setCursor(0, 1);
  lcd.print("to ");
  lcd.print(timeZones[selectedZone]);
  delay(3000);
}

void changeTimeZone() {
  
  int previousTimeZone = timeZone;
  
  lcd.clear();
  lcd.print("Change time zone");
  lcd.setCursor(0, 1);
  lcd.print(timeZones[selectedZone]);
  lcd.setCursor(15, 1);
  lcd.print(timeZoneOverflowIndicator);
  
  while (digitalRead(BUTTON_1_PIN) != LOW) {
    
    if (digitalRead(BUTTON_2_PIN) == LOW) {
      while (digitalRead(BUTTON_2_PIN) == LOW) { }
      delay(200);
      selectedZone--;
      if (selectedZone < 0) {
        selectedZone = 0;
      }
      if (selectedZone == 0) {
        timeZoneOverflowIndicator = (char)0;
      }
      lcd.setCursor(0, 1);
      lcd.print(timeZones[selectedZone]);
      lcd.print(BLANK);
      lcd.setCursor(15, 1);
      lcd.print(timeZoneOverflowIndicator);
    }
    
    if (digitalRead(BUTTON_3_PIN) == LOW) {
      while (digitalRead(BUTTON_3_PIN) == LOW) { }
      delay(200);
      selectedZone++;
      if (selectedZone > NUMBER_OF_ZONES - 1) {
        selectedZone = NUMBER_OF_ZONES - 1;
      }
      if (selectedZone == NUMBER_OF_ZONES - 1) {
        timeZoneOverflowIndicator = '^';
      }
      lcd.setCursor(0, 1);
      lcd.print(timeZones[selectedZone]);
      lcd.print(BLANK);
      lcd.setCursor(15, 1);
      lcd.print(timeZoneOverflowIndicator);
    }
    
  }
  
  while (digitalRead(BUTTON_1_PIN) == LOW) { }
  delay(200);
  
  timeZone = selectedZone;
  
  int hr = hour() + (timeZone - previousTimeZone);
  
  setTime(hr, minute(), second(), day(), month(), year());
  
  lcd.clear();
  lcd.print("Time zone set");
  lcd.setCursor(0, 1);
  lcd.print("to ");
  lcd.print(timeZones[selectedZone]);
  delay(3000);
}

bool isPressed(const int BUTTON_PIN_VALUE) {
  if (digitalRead(BUTTON_PIN_VALUE) == LOW) {
    while (digitalRead(BUTTON_PIN_VALUE) == LOW) { } //wait
    delay(200);
    return true;
  }
  return false;
}

/* 
 * Displays a scrollable menu and returns the index of the item that
 * is currently selected at the time that the user presses ENTER_BUTTON.
 *
 * EXAMPLE:
 *
 * menuItems: item 1, item 2, item 3, item 4, item 5
 * numberOfMenuItems = 5
 * startRow = 0;
 * startCol = 0;
 * rows = 3
 * columns = 16
 * topOverflowIndicator = '^'
 * bottomOverflowIndicator = 'v'
 * noOverflowCharacter = ' '
 * 
 * A.) initial state (top index = 0, selected index = 0)
 * 
 *     ----------------
 *     >item 1
 *      item 2
 *      item 3        v
 *     ----------------
 * 
 * B.) state after user presses DOWN_BUTTON (top index = 0, selected index = 1)
 * 
 *     ----------------
 *      item 1
 *     >item 2
 *      item 3        v
 *     ----------------
 *
 * C.) state after user presses DOWN_BUTTON 2 more times (top index = 1, selected index = 3)
 * 
 *     ----------------
 *      item 2        ^
 *      item 3
 *     >item 4        v
 *     ----------------
 *
 * D.) state after user presses UP_BUTTON 2 times (top index = 1, selected index = 1)
 * 
 *     ----------------
 *     >item 2        ^
 *      item 3        
 *      item 4        v
 *     ----------------
 *
 * E.) state after user presses DOWN_BUTTON 3 times (top index = 2, selected index = 4)
 * 
 *     ----------------
 *      item 3        ^
 *      item 4        
 *     >item 5
 *     ----------------
 */
int scrollingMenu(LiquidCrystal lcd, char* menuItems[], int numberOfMenuItems, 
                  int startRow, int startCol, int rows, int columns, 
                  char bottomOverflowIndicator, char topOverflowIndicator,
                  char currentSelectionIndicator, char notSelectedIndicator, 
                  const int ENTER_BUTTON, const int UP_BUTTON, const int DOWN_BUTTON) {
  int topIndex;
  int previousTopIndex = 0;
  int selectedIndex = 0;
  int previousSelectedIndex = 0;
  char overflowIndicator = topOverflowIndicator;
  
  //initialize output
  for (int i = 0; i < rows - 1; i++) {
    lcd.setCursor(startCol, startRow + i);
    if (i == selectedIndex) lcd.print(currentSelectionIndicator);
    else lcd.print(notSelectedIndicator);
    lcd.print(menuItems[i]);
  }
  if (numberOfMenuItems > rows) {
    lcd.setCursor(startCol + columns - 1, startRow + rows - 1);
    lcd.print(bottomOverflowIndicator);
  }
  
  //loop for button selection and adjust output accordingly
  while (!isPressed(ENTER_BUTTON)) {
    //adjust top index and selected index
    if (isPressed(UP_BUTTON)) {
      if (selectedIndex == topIndex) {
        topIndex--;
      }
      selectedIndex--;
    }
    else if (isPressed(DOWN_BUTTON)) {
      if (selectedIndex == topIndex + rows - 1) {
        topIndex++;
      }
      selectedIndex++;
    }
    
    //check that top index and selected index are valid
    if (topIndex > numberOfMenuItems - 1 - rows - 1) {
      topIndex = numberOfMenuItems - 1 - rows - 1;
    } 
    else if (topIndex < 0) {
      topIndex = 0;
    }
    
    if (selectedIndex > numberOfMenuItems - 1) {
      selectedIndex == numberOfMenuItems - 1;
    }
    else if (selectedIndex < 0) {
      selectedIndex = 0;
    }
    
    //output menu items
    if (topIndex != previousTopIndex) {
      for (int i = 0; i < rows; i++) {
        if (topIndex + i < numberOfMenuItems - 1) {
          lcd.setCursor(startCol + 1, startRow + i);
          lcd.print(menuItems[topIndex + i]);
        }
      }
    }
    previousTopIndex = topIndex;
    
    //output selection indicators
    if (selectedIndex != previousSelectedIndex) {
      for (int i = 0; i < rows; i++) {
        lcd.setCursor(columns - 1, startRow + i);
        if (i == selectedIndex) lcd.print(currentSelectionIndicator);
        else lcd.print(notSelectedIndicator);
      }
    }
    previousSelectedIndex = selectedIndex; 
    
    //output overflow indicators
    if (rows != 1) {
      if (topIndex < numberOfMenuItems - 1 - rows + 1) {
        lcd.setCursor(startCol + columns - 1, startRow + rows - 1);
        lcd.print(bottomOverflowIndicator);
      }
      if (topIndex > 0) {
        lcd.setCursor(startCol + columns - 1, startRow);
        lcd.print(topOverflowIndicator);
      }
    } else { //rows = 1
      if (topIndex == 0) {
        overflowIndicator = bottomOverflowIndicator;
      }
      else if (topIndex = numberOfMenuItems - 1) {
        overflowIndicator = topOverflowIndicator;
      }
      lcd.setCursor(startRow, startCol + columns - 1);
      lcd.print(overflowIndicator);
    }
  } //end while
  
  return selectedIndex;
}

int scrollingMenu(char* menuItems[], int numberOfMenuItems) {
  return scrollingMenu(lcd, menuItems, numberOfMenuItems, 0, 0, 2, 16, (char)0, '^', (char)1, 
                       BLANK, BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN);
}

int scrollingMenu(char* menuName, char* menuItems[], int numberOfMenuItems) {
  lcd.clear();
  lcd.print(menuName);
  return scrollingMenu(lcd, menuItems, numberOfMenuItems, 0, 1, 1, 16, (char)0, '^', (char)1, 
                       BLANK, BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN);
}
