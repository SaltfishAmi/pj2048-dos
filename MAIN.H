#include <iostream.h>
//#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream.h>
#define VERSION "2.5DS"
#define EMP 0
//#define EOF -1
#include <string.h>
//using namespace std;

extern int grdX, grdY, posX, posY;
extern int codX[8], codY[8];
//prevXY?
extern long data[8][8];
extern long slot1[8][8], slot2[8][8], slot3[8][8], lastOverwritten[8][8];
extern int slotData[4][2], lastOverwrittenNumber, slotEmpty[4];
extern int fileSlotStatus[3];

extern long lastData[8][8];
extern int lastScore;

extern int round;
extern int score;

//extern int promptOnOverwrite;

extern int needRepaint;

extern const int base;

void paintGrid(int sizeX, int sizeY);
#define NOFILE 1
void refreshStatus(int isNoFile=0);
void refreshDisplay();
void flushMessage();
void refreshAll(int isNoFile=0);

//void waitSec(int sec, char message[7]="Loading");

void genNew2();

#define FLUSH 1
int confirmYN(int options=0);

int moveAll(int direction);
void moveLine(int direction, int lineNumber);
int addAll(int direction);

void saveProgress(int slotNumber);
int loadProgress(int slotNumber);
void cleanData();

//void playerSave();
//void playerLoad();
#define STF_S 1
#define STF_L 2
#define T_SAVE 10
#define T_LOAD 20
#define F_SAVE 11
#define F_LOAD 21
#define C_SAVE 12
void dialogSL(int cmd);

void saveToFile(char* fileName);
int loadFromFile(char* fileName);
int checkFile(char* fileName);
void cleanFile();
void refreshFileslotStatus();

//void playerSaveFile();
//void playerLoadFile();

