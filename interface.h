#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

extern float temperature;
extern int light[2];
extern int servoPos;
extern int disco;
extern int fastMode;
extern int tempflag;

extern int alarmUpper;
extern int alarmLower;

extern int database[7][1440];
extern int min[7];
extern int max[7];
extern long clock;
extern int day;
extern int minute;

//Delay
void delay(int val);

//Keypad
void initKeypadPins(void);
int readKey(void);
int keyDebouncer(void);

//Display
unsigned char read_status_display(void);
void write_command_2_display(unsigned char Command);
void write_data_2_display(unsigned char Data);
void init_display(void);
void clearDisplay(void);
void writeCharToDisplay(char ch);
void writeStringToDisplay(char* str);
void blinkCursor(void);

//Tempsensor
void initTempSensor(void);
void measureTemp(void);
void TC0_Handler(void);

//Lightsensor
void initLightSensor(void);
void measureLight(void);

//Database
void resetDatabase(void);
void manageData(void);
void initDatabase(void);
void SysTick_Handler(void);


//Servo
void printTrackSun(void);
void servoInit(void);
void turnServo(int degree);
void trackSun(void);
void servoSweep(void);

//Settings
void systemSettings(void);
void printAlarmMenu(void);
void setAlarm(void);
void checkAlarm(void);

//Tests
void testMode(void);
void startFastMode(void);
void checkFastMode(void);

//Display data
void printDisplayDataMenu(void);
void displayData(void);
void calculateAverage(void);
void calculateMax(void);
void calculateMin(void);

//Menus
void printMainMenu(void);
void printSettingsMenu(void);


#endif  /* INTERFACE_H_ */