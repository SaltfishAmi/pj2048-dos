#include "MAIN.H"


long slot1[8][8],  slot2[8][8], slot3[8][8], lastOverwritten[8][8];
int slotData[4][2], lastOverwrittenNumber=EOF, slotEmpty[4]={1,1,1,1};
//slotData[0=lastOverwritten,1=1,2=2,3=3][0=roundNumber, 1=score]
//int promptOnOverwrite=0;
int fileSlotStatus[3];
/*
void playerSave()
{
    flushMessage();
    cout<<"Press 1, 2 or 3 to select slot,\nB to cancel,"<<endl;
    cout<<"F to save to a file.";
    int slotInput;
    while(slotInput!=1&&slotInput!=2&&slotInput!=3&&slotInput!='Z'-48&&slotInput!='z'-48&&slotInput+48!='F'&&slotInput+48!='f')
    {
        slotInput=getch()-48;
        if(slotInput+48=='F'||slotInput+48=='f')
        {
            playerSaveFile();
            flushMessage();
            return;
        }
    }
    flushMessage();
    if(slotInput=='Z'-48||slotInput=='z'-48)
    {
        flushMessage();
        return;
    }
    while(slotEmpty[slotInput]==0&&promptOnOverwrite==1)
    {
        flushMessage();
        cout<<"Overwrite existing slot?(A/B)"<<endl;
        char input=getch();
        if(input=='z'||input=='Z')return;
        else if(input==13)break;
    }
    cout<<"Saving to slot "<<slotInput<<"...";
//    waitSec(1, "Saving ");
    saveProgress(slotInput);
    refreshStatus();
    flushMessage();
    cout<<"Saved! Continue after 1 second...";
//    waitSec(1, "       ");
    flushMessage();
} */
//------------------------------------------------------------------------------
#define YAXIS_A 9
#define POS_A 13,YAXIS_A
#define POS_B POS_A+2
#define POS_C POS_A+4
#define ARR_A 11,YAXIS_A
#define ARR_B ARR_A+2
#define ARR_C ARR_A+4
#define TOPBAR 8,7

int moveCursor(int position)
{
    if(position>2||position<0)return 0;
    for(int i=0;i<=2;i++)
    {
        gotoxy(ARR_A+2*i);
        cout<<((position==i)?'>':' ');
    }
    return 1;
}
void backToGame()
{
    clrscr();
    paintGrid(grdX, grdY);
    refreshAll();
}
void cleanPanel()
{
    for(int i=1;i<=9;i++)
    {
        gotoxy(7,6+i);
        for(int j=1;j<=29;j++)cout<<' ';
    }
}
#define UNSCRED 0     //why?
#define SCRED 1
void dialogSL(int cmd)  //0=selsav 1=selload 12=save 3=load 4=savefile 6=loadfile
{
    cout<<endl;
    textcolor(LIGHTGRAY);
    if(cmd==NULL)
    {
        backToGame();
        return;
    }
    char input;
    if(cmd==C_SAVE)
    {
        cleanPanel();
	gotoxy(TOPBAR);
	cout<<"Clear all RAM & file saves?";
        gotoxy(POS_B);
        cout<<"[A]Cancel";
        gotoxy(POS_C);
        cout<<"[X]Confirm";
        input=getch();
        while(input!=13&&input!='8')input=getch();
        if(input==13)return;
        else if(input=='8')
        {
            cleanData();
            cleanFile();
            return;
        }
    }
    int i, j;
    //int scroll=0, scrollPos=0;
    //int nothingToShow=1;
    gotoxy(6,6);
    for(i=1;i<=31;i++)cout<<'=';
    for(i=1;i<=10;i++)
    {
        gotoxy(6,6+i);
        cout<<'|';
        gotoxy(36,6+i);
        cout<<'|';
    }
    gotoxy(6,16);
    for(i=1;i<=31;i++)cout<<'=';
    cleanPanel();
    gotoxy(16,15);
    cout<<"[A]Confirm [B]Cancel"<<endl;
    //int lastChecked=1;
    int lineNumber=0;
    int totalChoices=0;
    switch(cmd)
    {
        case STF_S:
            gotoxy(TOPBAR);
            cout<<"Select save type";
            gotoxy(POS_A);
            cout<<"Save in RAM"<<endl;
            gotoxy(POS_B);
            cout<<"Save in file"<<endl;
            gotoxy(POS_C);
            cout<<"Clear all data"<<endl;
            totalChoices=3;
            break;
        case STF_L:
            gotoxy(TOPBAR);
            cout<<"Select load type";
            gotoxy(POS_A);
            cout<<"Load from RAM"<<endl;
            gotoxy(POS_B);
            cout<<"Load from file"<<endl;
            totalChoices=2;
            break;
        case T_SAVE:
            gotoxy(TOPBAR);
            cout<<"Select save slot";
            gotoxy(POS_A);
            cout<<"Slot 1"<<endl;
            gotoxy(POS_B);
            cout<<"Slot 2"<<endl;
            gotoxy(POS_C);
            cout<<"Slot 3"<<endl;
            totalChoices=3;
            for(i=1;i<=3;i++)
            {
                if(slotEmpty[i]==0)
                {
                    gotoxy(20,9+(i-1)*2);
                    cout<<"(Overwrite)";
                }
            }
            break;
        case T_LOAD:
            gotoxy(TOPBAR);
            cout<<"Select load slot";
            //lastChecked=1;
            lineNumber=0;
            //while(lastChecked!=0&&lineNumber<=2)
            //{
            for(i=1;i<=3;i++)
            {
                gotoxy(POS_A+lineNumber*2);
                if(slotEmpty[i])cout<<"Empty";
                else cout<<"Slot "<<i;
                //lastChecked=0;
                lineNumber++;
            }                         //
            if(slotEmpty[0]==0)
            {
                gotoxy(12,YAXIS_A+5);
                cout<<"[X]Load last overwritten";
            }
            //}
            //if(lineNumber==3)
            //{
            //    gotoxy(21,14);
            //    cout<<'v';
            //    scroll=1;
            //}
            //if(nothingToShow)
            //{
            //    gotoxy(POS_B);
            //    cout<<"Nothing to load!"<<endl;
            //}
            totalChoices=3;
            break;
        case F_SAVE:
            gotoxy(TOPBAR);
            cout<<"Select save file";
            gotoxy(POS_A);
            cout<<"File 1"<<endl;
            gotoxy(POS_B);
            cout<<"File 2"<<endl;
            gotoxy(POS_C);
            cout<<"File 3"<<endl;
            refreshFileslotStatus();
	    for(i=0;i<=2;i++)
            {
                if(fileSlotStatus[i]==1)
                {
		    gotoxy(20,9+i*2);
                    cout<<"(Overwrite)";
                }
            }
            totalChoices=3;
            break;
        case F_LOAD:
            gotoxy(TOPBAR);
            cout<<"Select load file";
            //lastChecked=0;
            lineNumber=0;
            //while(lastChecked<2)
            //{
            for(i=0;i<=2;i++)
            {
                gotoxy(POS_A+lineNumber*2);
                if(fileSlotStatus[i]==1)cout<<"File "<<i+1;
                else cout<<"Empty";
                        //lastChecked=i;
                        //nothingToShow=1;
                        //break;
                    //lastChecked=4;
                lineNumber++;
            }

            //}
            //if(nothingToShow)
            //{
            //    gotoxy(POS_B);
            //    cout<<"Nothing to load!"<<endl;
            //}
            totalChoices=3;
            break;
    }
    //
    //int result=0;
    int selection=0;
    moveCursor(selection);
    input=0;
    while(1)
    {
        gotoxy(17,15);
        input=getch();
        while(input!='W'&&input!='w'&&input!='S'&&input!='s'&&input!='Z'&&input!='z'&&input!=13&&input!='8')
            input=getch();
        switch(input)
        {
            case 'W': case 'w':
                if(selection>0)
                {
                    selection--;
                    moveCursor(selection);
                }
                break;
            case 'S': case 's':
                if(selection<totalChoices-1)
                {
                    selection++;
                    moveCursor(selection);
                }
                break;
            case 'Z': case 'z':
                dialogSL(cmd/10);
                return;
            case '8':
                if(cmd==T_LOAD&&slotEmpty[0]==0)
                {
                    loadProgress(0);
                    return;
                }
                break;
            case 13:
                if(cmd<10)
                {
                    dialogSL(cmd*10+selection);
                    backToGame();
                    return;
                }
                else if(cmd%10==0)
                {
                    switch(cmd)
                    {
                        case T_SAVE:
                            saveProgress(selection+1);
                            return;
                        case T_LOAD:
                            if(slotEmpty[selection+1])continue;
                            loadProgress(selection+1);
                            return;
                        default: continue;
                    }
                }
                else if(cmd%10==1)
                {
                    switch(cmd)
                    {
                        case F_SAVE:
                            switch(selection)
                            {
                                case 0: saveToFile("1.424"); break;
                                case 1: saveToFile("2.424"); break;
                                case 2: saveToFile("3.424"); break;
                            }
                            return;
                        case F_LOAD:
                            if(fileSlotStatus[selection]==0)continue;
                            switch(selection)
                            {
                                case 0: loadFromFile("1.424"); break;
                                case 1: loadFromFile("2.424"); break;
                                case 2: loadFromFile("3.424"); break;
                            }
                            return;
                        default: continue;
                    }
                }
                break;
        }
    }
    //getch();
}
//------------------------------------------------------------------------------
void refreshFileslotStatus()
{
    fileSlotStatus[0]=checkFile("1.424");
    fileSlotStatus[1]=checkFile("2.424");
    fileSlotStatus[2]=checkFile("3.424");
}
//------------------------------------------------------------------------------
/*
void playerLoad()
{
    flushMessage();
    cout<<"Press 1, 2 or 3 load from a slot,\nF to load from file."<<endl;
    cout<<"5 to load the data that \noverwritten most recently."<<endl;
    cout<<"To cancel, press B.";
    char slotInput;
    int slotNum;
    while(1)
    {
        slotInput=getch();
        switch(slotInput)
        {
            case '5': slotNum=0; break;
            case 'Z': case 'z':
                flushMessage();
                return;
            case '1': slotNum=1; break;
            case '2': slotNum=2; break;
            case '3': slotNum=3; break;
            case 'f': case 'F':
                playerLoadFile();
                flushMessage();
                return;
        }
        if(slotNum>=0&&slotNum<=3)break;
    }
    flushMessage();
    if(slotNum!=0) cout<<"Loading slot "<<slotNum<<"...";
    else cout<<"Loading last overwritten data...";
    if(slotEmpty[slotNum]==1) cout<<endl<<"Slot empty!! Continue after 1 second...";
    else
    {
//        waitSec(1);
        loadProgress(slotNum);
        refreshStatus();
        flushMessage();
        cout<<"Loaded! Continue after 1 second...";
    }
//    waitSec(1, "       ");
    flushMessage();
}
//------------------------------------------------------------------------------
void playerSaveFile()
{
    int fileSlot=0;
    flushMessage();
    cout<<"Press 1, 2 or 3 to select file, \nB to cancel."<<endl;
    //cout<<"This will save to a file that can be perserved permanently."<<endl;
    while(fileSlot!=1&&fileSlot!=2&&fileSlot!=3&&fileSlot!='Z'-48&&fileSlot!='z'-48)
        fileSlot=getch()-48;
    switch(fileSlot)
    {
        case ('Z'-48): case ('z'-48):  return;
        case 1: fileSlotStatus[1]=checkFile("1.424");break;
        case 2: fileSlotStatus[2]=checkFile("2.424");break;
        case 3: fileSlotStatus[3]=checkFile("3.424");break;
    }
    while(fileSlotStatus[fileSlot]==1&&promptOnOverwrite==1)
    {
        flushMessage();
        cout<<"Overwrite existing save file?(A/B)"<<endl;
        char input=getch();
        if(input=='z'||input=='Z')return;
        else if(input==13)break;
    }
    //system("title Console 2048 - saving to file");
//    waitSec(1, "Saving ");
    switch(fileSlot)
    {
        case 1: saveToFile("1.424"); break;
        case 2: saveToFile("2.424"); break;
        case 3: saveToFile("3.424"); break;
    }
    refreshStatus();
    flushMessage();
    //system("title Console 2048 - game in progress");
    cout<<"Saved to file! Continue after 1 second...";
    //waitSec(1, "       ");
    flushMessage();
}
//------------------------------------------------------------------------------
void playerLoadFile()
{
    int fileSlot=0, result=0;
    flushMessage();
    cout<<"Press 1, 2 or 3 to select file, \nB to cancel."<<endl;
    //cout<<"This will load from a save file created by 2048 earlier."<<endl;
    while(fileSlot!=1&&fileSlot!=2&&fileSlot!=3&&fileSlot!=4)
        fileSlot=getch()-48;
    if(fileSlot=='z'-48||fileSlot=='Z'-48)return;
   // system("title Console 2048 - loading file");
    //waitSec(1);
    switch(fileSlot)
    {
        case 1: result=loadFromFile("1.424"); break;
        case 2: result=loadFromFile("2.424"); break;
        case 3: result=loadFromFile("3.424"); break;
    }
    needRepaint*=fileSlot;
    if(result==0)
    {
    flushMessage();
    cout<<"Failed to open file! Continue after 1 second...";
    //waitSec(1, "       ");
    return;
    }
    else if(result==2) return;
    else if(result==3) return;
    refreshStatus();
    flushMessage();
    system("title Console 2048 - game in progress");
    cout<<"Loaded from file! Continue after 1 second...";
    //waitSec(1, "       ");
    flushMessage();
} */
/*------------------------------------------------------------------------------
void enterDevMode()
{
    system("title Console 2048 - development mode");
    clrscr();
    gotoxy(1,1);
    cout<<"Specifying outputs? or press 0 to back.";
    if(getch()=='0')return;
    cout<<endl<<"Enter less than 6 Ascii or 3 Asian characters for each number."<<endl;
    for(int i=2;i<=524288;i*=2)cout<<i<<endl;

}
*/
//------------------------------------------------------------------------------
int confirmYN(int options)
//options
//1=flush
{
    char input;
    while(1)
    {
        if(options==1)flushMessage();
        cout<<"[A]Confirm [B]Cancel";
        input=getch();
        cout<<input<<endl;
        if(input==13) return 1;
        else if(input=='z'||input=='Z') return 0;
    }
}
