/*THIS PROJECT READ DISTANCE VIA ULTRASONIC SENSOR AND PRINT IT ON LCD
  SCREEN.
  AUTOR: PAGRATIS PANAGIOTIS
  DATE: 16/11/2023

  test change for check if is visible in github

///////////////////////////////////////////////////////////////////////////////////////////  
 (free) = 1023   (1)select=639   (2)right=408    (3)down=255    (4)up=100    (5)left=0   */
 //////////////////////////////////////////////////////////////////////////////////////////
#include <main.h>
//MENU LISTS UNDER THIS LINE/////////////////////////////////////////////////////
String firstLineLabel[MENU_SIZE] =                      {LABEL1, LABEL2};
String secondLineLable[MENU_SIZE] [SUB_MENU_SIZE]  =    {{UNIT1_1, UNIT1_2, UNIT2_1, UNIT2_2, UNIT3}, 
                                                        {UNIT1_1, UNIT1_2, UNIT2_1, UNIT2_2, UNIT3}};
double values[MENU_SIZE][SUB_MENU_SIZE] =                  {{remainLTmainTank, remainPERCmainTank, lossLTmainTank, lossPERCmainTank, distanceMainTank},
                                                           {remainLTccrTank, remainPERCccrTank, lossLTccrTank, lossPERCccrTank, distanceCcrTank}};
//OBJECT CREATION UNDER THIS LINE/////////////////////////////////////////////////

NewPing sonarCcrTank(TRG_S_PIN, ECH_S_PIN, MAX_DIST);
NewPing sonarMainTank(TRG_M_PIN, ECH_M_PIN, MAX_DIST);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//SETUP FUNCTION UNDER THIS LINE//////////////////////////////////////////////////
void setup() {
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    if(DEBUG_MODE) Serial.begin(9600);
}//end void setup
//MAIN LOOP UNDER THIS LINE///////////////////////////////////////////////////////
void loop() {
    btnState = btn_evaluation(analogRead(BTN_PIN));
    cur_delay_ms = millis();
    if( ((cur_delay_ms - old_delay_ms) > DELAY_USS_READ) || (btnState != oldBtnState) ) {
        //distanceMainTank = 20;
        //distanceCcrTank = 10;
        distanceMainTank =  sonarMainTank.ping_cm();
        distanceCcrTank =   sonarCcrTank.ping_cm();
        if(DEBUG_MODE) {
            Serial.print("Main Tank distance is: ");
            Serial.println(distanceMainTank);
            Serial.print("CCR tank distance is: ");
            Serial.println(distanceCcrTank);
        }//end if(debug mode true)
        convertions();
        changeScreen(btnState); 
        lcd.clear();  
        lcd.setCursor(0, 0);
        lcd.print(firstLineLabel[screenCurrentPosition]);
        lcd.setCursor(0, 1);
        lcd.print(values[screenCurrentPosition][subMenuCurrentPosition]);
        lcd.setCursor(6, 1);
        lcd.print(secondLineLable[screenCurrentPosition][subMenuCurrentPosition]);
        oldBtnState = btnState;
        old_delay_ms = cur_delay_ms;
    }//end if delay uss read
          
}//end loop
//FUNCTIONS UNDER THIS LINE////////////////////////////////////////////////////////
int btn_evaluation(int val) {
    if(val < 670 && val > 600)       return 1;
    else if( val < 450 && val > 350) return 2;
    else if(val < 300 && val > 200)  return 3;
    else if(val < 150 && val > 50)   return 4;
    else if(val < 49)                return 5;
    return 0;
}//end btn_evaluation
void changeScreen(int btn) {
    if(oneTimePressBtn(btn)) {
        if(btn == 5) {
            if(screenCurrentPosition < MAX_MENU_SIZE) 
                screenCurrentPosition += 1;
            else if(screenCurrentPosition == MAX_MENU_SIZE) 
                screenCurrentPosition = MIN_MENU_SIZE;
        }//end btn left
        if(btn == 2) {
            if(screenCurrentPosition > MIN_MENU_SIZE) 
                screenCurrentPosition -= 1;
            else if(screenCurrentPosition == MIN_MENU_SIZE) 
                screenCurrentPosition = MAX_MENU_SIZE;
        }//end btn right
        if(btn == 3) {
            if(subMenuCurrentPosition < MAX_SUB_MENU_SIZE) 
                subMenuCurrentPosition += 1;
            else if(subMenuCurrentPosition == MAX_SUB_MENU_SIZE)
                subMenuCurrentPosition = MIN_SUB_MENU_SIZE;
        }//end btn up
        if(btn == 4) {
            if(subMenuCurrentPosition > MIN_SUB_MENU_SIZE) 
                subMenuCurrentPosition -= 1;
            else if(subMenuCurrentPosition == MIN_SUB_MENU_SIZE) 
                subMenuCurrentPosition = MAX_SUB_MENU_SIZE;
        }//end btn down
    }//if oneTimePressBtn( int btn)
}//end changeScreen(int btn)
void convertions(){
    double disMAIN = (distanceMainTank - OFFSET_MAIN_TANK_HEIGHT) / 100; //convert cm to meter
    double disCCR =  (distanceCcrTank - OFFSET_CCR_TANK_HEIGHT) / 100;   //convert cm to meter
  //CONVERTIONS FOR MAIN TANK UNDER THIS LINE //////////////////////////////////////////////////////////////////////////////////////////////
    values[0][2]  = ( LARGE_TANK_LENGTH * LARGE_TANK_WIDTH * disMAIN );     //lossLTmainTank
    values[0][0]  = ( FULL_MAIN_TANK_LT - ( values[0][2] ) );               //remainLTmainTank
    values[0][1]  = ( ( 100 * values[0][0] ) / FULL_MAIN_TANK_LT);          //remainPERCmainTank
    values[0][3]  = ( ( 100 * values[0][2] ) / FULL_MAIN_TANK_LT );         //lossLTmainTank
    values[0][4]  = ( distanceMainTank );                                   //print current distance for checking
  //CONVERTIONS FOR CCR TANK UNDER THIS LINE////////////////////////////////////////////////////////////////////////////////////////////////  
    values[1][2]  = ( SMALL_TANK_LENGTH * SMALL_TANK_WIDTH * disCCR );      //lossLTmainTank
    values[1][0]  = ( FULL_CCR_TANK_LT - ( values[1][2] ) );                //remainLTmainTank
    values[1][1]  = ( ( 100 * values[1][0] ) / FULL_CCR_TANK_LT );          //remainPERCmainTank
    values[1][3]  = ( ( 100 * values[1][2] ) / FULL_CCR_TANK_LT);           //lossLTmainTank
    values[1][4]  = (distanceCcrTank);
}//end void convertions(int, int)
uint8_t oneTimePressBtn(int btn) {
    if(btn == oldBtnState) 
        return 0;
    return 1;
}//end oneTimePressBtn
































// /*THIS PROJECT READ DISTANCE VIA ULTRASONIC SENSOR AND PRINT IT ON LCD
//   SCREEN.
//   AUTOR: PAGRATIS PANAGIOTIS
//   DATE: 16/11/2023

// ///////////////////////////////////////////////////////////////////////////////////////////  
//  (free) = 1023   (1)select=639   (2)right=408    (3)down=255    (4)up=100    (5)left=0   */
//  //////////////////////////////////////////////////////////////////////////////////////////
// #include <Arduino.h>
// #include <LiquidCrystal.h>
// #include <NewPing.h>
// #include <Wire.h>
// //DEFINITIONS UNDER THIS LINE////////////////////////////////////////////////////
// #define TRUE                1
// #define FALSE               0
// #define DELAY_UPDATE_LCD    220
// #define MAX_DIST            3000
// #define trgM                2
// #define echM                3
// #define trgS                4
// #define echS                5
// #define BTN_PIN             A0
// //ABOUT LIST AND MENU DEFINITIONS UNDER THIS LINE////////////////////////////////
// #define LIST_SIZE           2    //HORIZONTAL SIZE (LEFT & RIGHT)
// #define MAX_LIST            (LIST_SIZE - 1)
// #define MIN_LIST            0
// #define SUB_MENU_SIZE       4   //VERTICAL SIZE (UP & DOWN)
// #define MAX_SUB_MENU        (SUB_MENU_SIZE - 1)
// #define MIN_SUB_MENU        0
// //ABOUT TANK SIZE UNDER THIS LINE////////////////////////////////////////////////
// #define LARGE_TANK_LENGTH   10
// #define LARGE_TANK_WIDTH    10
// #define LARGE_TANK_HEIGHT   10
// #define SMALL_TANK_LENGTH   5
// #define SMALL_TANK_WIDTH    5
// #define SMALL_TANK_HEIGHT   5
// //LABELS FOR MENU SCREEN UNDER THIS LINE//////////////////////////////////////////
// /////////////////////****************/////////////////////////////////////////////
// #define LABEL1    "MAIN TANK"
// #define LABEL2    "SECONDARY TANK"
// /////////////////////VAL*************/////////////////////////////////////////////
// #define UNIT1_1           "LT REMAIN"
// #define UNIT1_2           "%  REMAIN"
// #define UNIT2_1           "LT LOSS" 
// #define UNIT2_2           "%  LOSS"  
// //DECLARATION VARIABLES UNDER THIS LINE///////////////////////////////////////////
// const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
// int val_1, val_2, val_3, val_4;
// int btn_resistan;
// //ABOUT NAVIGATION IN MENU SCREENS//////////////////////////////////////////////
// int screenCurrentPosition;
// int subMenuCurrentPosition;
// int subMenuLastPosition;
// int screenLastPosition;
// //MEASUREMENTS AND CONVERTIONS UNDER THIS LINE/////////////////////////////////
// int distanceMainTank;
// int distanceSecondaryTank;
// int remainLTmainTank            = 11;
// int remainLTsecondaryTank       = 21;
// int remainPERCmainTank          = 12;
// int remainPERCsecondaryTank     = 22;
// int lossLTmainTank              = 13;
// int lossLTsecondaryTank         = 23;
// int lossPERCmainTank            = 14;
// int lossPERCsecondaryTank       = 24;
// //MENU LISTS UNDER THIS LINE/////////////////////////////////////////////////////
// String firstLineLabel[LIST_SIZE] =                      {LABEL1, LABEL2};
// String secondLineLable[LIST_SIZE] [SUB_MENU_SIZE]  =    {{UNIT1_1, UNIT1_2, UNIT2_1, UNIT2_2}, 
//                                                         {UNIT1_1, UNIT1_2, UNIT2_1, UNIT2_2}};
// int values[LIST_SIZE][SUB_MENU_SIZE] =                  {{remainLTmainTank, remainPERCmainTank, lossLTmainTank, lossPERCmainTank},
//                                                         {remainLTsecondaryTank, remainPERCsecondaryTank, lossLTsecondaryTank, lossPERCsecondaryTank}};
// //DECLARATION OF FUNCTIONS UNDER THIS LINE////////////////////////////////////////
// int btn_evaluation(int val);
// void changeScreen(int btn); 
// void convertions(int dis);
// //OBJECT CREATION UNDER THIS LINE/////////////////////////////////////////////////
// NewPing sonarMainTank(trgM, echM, MAX_DIST);
// //NewPing sonarSecondaryTank(trgS, echS, MAX_DIST);
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// //SETUP FUNCTION UNDER THIS LINE//////////////////////////////////////////////////
// void setup() {
//     lcd.begin(16, 2);
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     //Serial.begin(9600);
// }//end void setup
// //MAIN LOOP UNDER THIS LINE///////////////////////////////////////////////////////
// void loop() {
//     distanceMainTank = sonarMainTank.ping_cm();
//     //distanceSecondaryTank = sonarSecondaryTank.ping_cm();
//     //TODO ERASE UNDER THIS LINE IS FOR TEST;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//     values[0][0] = distanceMainTank;
//     //Serial.print(values[0][0]);
//     ///////////////////////////////////////////////////////
//     convertions(distanceMainTank);
//     changeScreen(btn_evaluation(analogRead(BTN_PIN)));    
//     lcd.clear();  
//     lcd.setCursor(0, 0);
//     lcd.print(firstLineLabel[screenCurrentPosition]);
//     lcd.setCursor(0, 1);
//     lcd.print(values[screenCurrentPosition][subMenuCurrentPosition]);
//     lcd.setCursor(6, 1);
//     lcd.print(secondLineLable[screenCurrentPosition][subMenuCurrentPosition]);
//     delay(DELAY_UPDATE_LCD);         
// }//end loop
// //FUNCTIONS UNDER THIS LINE////////////////////////////////////////////////////////
// int btn_evaluation(int val) {
//     if(val < 670 && val > 600) return 1;
//     else if( val < 450 && val > 350) return 2;
//     else if(val < 300 && val > 200) return 3;
//     else if(val < 150 && val > 50) return 4;
//     else if(val < 49) return 5;
//     return 0;
// }//end btn_evaluation
// void changeScreen(int btn) {
//     if(btn == 5) {
//         if(screenCurrentPosition < MAX_LIST) 
//             screenCurrentPosition += 1;
//     }//end btn left
//     if(btn == 2) {
//         if(screenCurrentPosition > MIN_LIST) 
//             screenCurrentPosition -= 1;
//     }//end btn right
//     if(btn == 4) {
//         if(subMenuCurrentPosition < MAX_SUB_MENU) 
//             subMenuCurrentPosition += 1;
//     }//end btn up
//     if(btn == 3) {
//         if(subMenuCurrentPosition > MIN_SUB_MENU) 
//             subMenuCurrentPosition -= 1;
//     }//end btn down
// }//end changeScreen(int btn)
// void convertions(int dis){
    
// }//end void convertions(int, int)
