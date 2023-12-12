/*THIS PROJECT READ DISTANCE VIA ULTRASONIC SENSOR AND PRINT IT ON LCD
  SCREEN.
  AUTOR: PAGRATIS PANAGIOTIS
  DATE: 16/11/2023

///////////////////////////////////////////////////////////////////////////////////////////  
 (free) = 1023   (1)select=639   (2)right=408    (3)down=255    (4)up=100    (5)left=0   */
 //////////////////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_H 
#define MAIN_H
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <NewPing.h>
#include <Wire.h>
//DEFINITIONS UNDER THIS LINE////////////////////////////////////////////////////
#define TRUE                1
#define FALSE               0
#define DEBUG_MODE          FALSE
#define DELAY_UPDATE_LCD    1000
#define DELAY_USS_READ      3000
#define MAX_DIST            3000
#define TRG_M_PIN           2
#define ECH_M_PIN           3
#define TRG_S_PIN           11
#define ECH_S_PIN           12
#define BTN_PIN             A0
//ABOUT LIST AND MENU DEFINITIONS UNDER THIS LINE////////////////////////////////
#define MENU_SIZE           2    //HORIZONTAL SIZE OF ARRAY (LEFT & RIGHT)
#define MAX_MENU_SIZE       (MENU_SIZE - 1)
#define MIN_MENU_SIZE       0
#define SUB_MENU_SIZE       5   //VERTICAL SIZE OF ARRAY (UP & DOWN)
#define MAX_SUB_MENU_SIZE   (SUB_MENU_SIZE - 1)
#define MIN_SUB_MENU_SIZE   0
//ABOUT TANK SIZE UNDER THIS LINE////////////////////////////////////////////////
double OFFSET_MAIN_TANK_HEIGHT  = 0.17;
double OFFSET_CCR_TANK_HEIGHT   = 0.22;
double LARGE_TANK_LENGTH        = 3.00;
double LARGE_TANK_WIDTH         = 1.30;
double LARGE_TANK_HEIGHT        = 1.40;
double SMALL_TANK_LENGTH        = 1.00;
double SMALL_TANK_WIDTH         = 1.00;
double SMALL_TANK_HEIGHT        = 1.40;
double FULL_MAIN_TANK_LT = ((LARGE_TANK_LENGTH * LARGE_TANK_WIDTH *LARGE_TANK_HEIGHT));
double FULL_CCR_TANK_LT  = ((SMALL_TANK_LENGTH * SMALL_TANK_WIDTH * SMALL_TANK_HEIGHT));
//LABELS FOR MENU SCREEN UNDER THIS LINE//////////////////////////////////////////
/////////////////////****************/////////////////////////////////////////////
#define LABEL1      "MAIN TANK"
#define LABEL2      "CCR  TANK"
/////////////////////VAL*************/////////////////////////////////////////////
#define UNIT1_1           "kL REMAIN"
#define UNIT1_2           "%  REMAIN"
#define UNIT2_1           "kL LOSS" 
#define UNIT2_2           "%  LOSS" 
#define UNIT3             "CM SPACE" 
//DECLARATION VARIABLES UNDER THIS LINE///////////////////////////////////////////
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
int btn_resistan;
int btnState;
int oldBtnState;
//ABOUT NAVIGATION IN MENU SCREENS////////////////////////////////////////////////
int screenCurrentPosition;
int screenLastPosition;
int subMenuCurrentPosition;
int subMenuLastPosition;
//MEASUREMENTS AND CONVERTIONS UNDER THIS LINE////////////////////////////////////
double distanceMainTank;
double distanceCcrTank;
double remainLTmainTank;
double remainLTccrTank;
double remainPERCmainTank;
double remainPERCccrTank;
double lossLTmainTank;
double lossLTccrTank;
double lossPERCmainTank;
double lossPERCccrTank;
//VARIABLES FOR KEEPING TIME (MILLIS) UNDER THIS LINE////////////////////////////
long unsigned cur_delay_ms;
long unsigned old_delay_ms;
//DECLARATION OF FUNCTIONS UNDER THIS LINE////////////////////////////////////////
int btn_evaluation(int val);
void changeScreen(int btn); 
void convertions();
uint8_t oneTimePressBtn(int btn);




#endif