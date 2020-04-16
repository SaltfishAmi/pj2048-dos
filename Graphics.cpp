#include "MAIN.H"
#include <dos.h>
char* D_2      ="2     ";
char* D_4      ="4     ";
char* D_8      ="8     ";
char* D_16     ="16    ";
char* D_32     ="32    ";
char* D_64     ="64    ";
char* D_128    ="128   ";
char* D_256    ="256   ";
char* D_512    ="512   ";
char* D_1024   ="1024  ";
char* D_2048   ="2048  ";
char* D_4096   ="4096  ";
char* D_8192   ="8192  ";
char* D_16384  ="16384 ";
char* D_32768  ="32768 ";
char* D_65536  ="65536 ";
char* D_131072 ="131072";
char* D_262144 ="262144";
char* D_524288 ="524288";

char slotIndicator[3];
char fileSlotIndicator[3];

void genNew2()
{
    while(1)
    {
        //generate a 2 before or after every moving||adding
        posX=rand()%grdX;
        posY=rand()%grdY;
		if(data[posX][posY]==EMP)     //if a block is empty, fill it; otherwise regenerate
		{
            gotoxy(codX[posX],codY[posY]);
            //base*=2;
            data[posX][posY]=base;
//			sleep(200);
            textcolor(YELLOW);
//            textbackground(YELLOW);
			cprintf(D_2);
//			sleep(100);
			textcolor(LIGHTGRAY);
            flushMessage();
            return;
        }
    }
}
//------------------------------------------------------------------------------
void refreshStatus(int isNoFile)
{
#define InfoPos (codY[grdY-1]+2)
    textcolor(YELLOW);
//    textbackground(BLUE);
    gotoxy(1,InfoPos);
    cprintf("Round");
    //if(grdX>=7) gotoxy(InfoPos,5);
    gotoxy(1,InfoPos+2);
    cprintf("Score");
    //if(grdX>=7) gotoxy(InfoPos,7);
    gotoxy(9,InfoPos);
    cprintf("Saveslots");
    //if(grdX>=7) gotoxy(InfoPos,9);
    gotoxy(9,InfoPos+2);
    cprintf("Filesaves");
    textcolor(WHITE);
    gotoxy(1,InfoPos+1);
    cprintf("%d",round);
    //if(grdX>=7) gotoxy(InfoPos,6);
    gotoxy(1,InfoPos+3);
    cprintf("%d",score);
    //if(grdX>=7) gotoxy(InfoPos,8);
    gotoxy(9,InfoPos+1);
    for(int i=1;i<=3;i++)
    {
        if(slotEmpty[i]==0)slotIndicator[i]='X';
        else slotIndicator[i]=' ';
    }
    cprintf("[%c][%c][%c]",slotIndicator[1],slotIndicator[2],slotIndicator[3]);
    if(isNoFile==1)
    {
        //if(grdX>=7) gotoxy(InfoPos,10);
        gotoxy(9,InfoPos+3);
        refreshFileslotStatus();
        for(int i=0;i<=2;i++)
        {
            if(fileSlotStatus[i]==1)fileSlotIndicator[i]='X';
            else fileSlotIndicator[i]=' ';
        }
        cprintf("[%c][%c][%c]",fileSlotIndicator[0],fileSlotIndicator[1],fileSlotIndicator[2]);
    }
/*    if(grdX>=7)
    {
        textcolor(YELLOW);
        gotoxy(InfoPos,11);
        cprintf("[P]toggle");
        gotoxy(InfoPos,12);
        cprintf("Overwrite");
        gotoxy(InfoPos,13);
        cprintf("Prompt");
        textcolor(WHITE);
        if(promptOnOverwrite==1) cprintf("[X]");
        else if (promptOnOverwrite==0) cprintf("[ ]");
    }
    else
    {     *//*
        textcolor(YELLOW);
        gotoxy(1,InfoPos+4);
        cprintf("Prompt on Overwrite");
        textcolor(WHITE);
        gotoxy(1,InfoPos+5);
        cprintf("[P] to toggle:  ");
        if(promptOnOverwrite==1) cprintf(" On");
        else if (promptOnOverwrite==0) cprintf("Off");   */
	//}
	textcolor(LIGHTGRAY);
	//else if
    #undef InfoPos
}
//------------------------------------------------------------------------------
void refreshDisplay()
{
    refreshStatus(NOFILE);
    textcolor(YELLOW);
    for(int i=0;i<grdX;i++){
        for(int j=0;j<grdY;j++){
            if(data[i][j]>=0)
            {
                gotoxy(codX[i],codY[j]);
                //data[i][j]=524289;
                switch(data[i][j])
                {
                    //customize outputs of every number (max 6 asciis or 3 unicodes)
                    //function of reading these customizations from file is to be developed.

                    case 0:      cprintf("      "); break;
                    case 2:      cprintf(D_2     ); break;
                    case 4:      cprintf(D_4     ); break;
                    case 8:      cprintf(D_8     ); break;
                    case 16:     cprintf(D_16    ); break;
                    case 32:     cprintf(D_32    ); break;
                    case 64:     cprintf(D_64    ); break;
                    case 128:    cprintf(D_128   ); break;
                    case 256:    cprintf(D_256   ); break;
                    case 512:    cprintf(D_512   ); break;
                    case 1024:   cprintf(D_1024  ); break;
                    case 2048:   cprintf(D_2048  ); break;
                    case 4096:   cprintf(D_4096  ); break;
					case 8192:   cprintf(D_8192  ); break;
                    case 16384:  cprintf(D_16384 ); break;
                    case 32768:  cprintf(D_32768 ); break;
					case (long)65536:  cprintf(D_65536 ); break;
					case (long)131072: cprintf(D_131072); break;
					case (long)262144: cprintf(D_262144); break;
					case (long)524288: cprintf(D_524288); break;
					//max 6 digits. if exceed, print something to indicate
                    //that the player is incredible.
					default:
				   // if (data[i][j]==65536
                        flushMessage();
                        system("title Console 2048 - you're incredible!");
                        cout<<"Exceeded number limit. You've reached 1048576."<<endl;
                        cout<<"You are an expert in playing 2048."<<endl;
                        cout<<"This game is too low-IQ for you!"<<endl;
                        cout<<"Press any key to exit...";
                        getch();
                        exit(1);
                }
            }
        }
	}
	textcolor(LIGHTGRAY);
    flushMessage();
}
//------------------------------------------------------------------------------
void flushMessage()
{
    gotoxy(1,codY[grdY-1]+6);
    for(int i=1;i<=5;i++)
    cout<<"                                                                              "<<endl;    gotoxy(1,codY[grdY-1]+8);
    gotoxy(1,codY[grdY-1]+6);
}
//------------------------------------------------------------------------------
void paintGrid(int sizeX, int sizeY)
{
        int i,j;
        grdX=sizeX;
        grdY=sizeY;
        clrscr();
		//system("color 1f");
        gotoxy(1,1);
//        system("title Console 2048 - game in progress");
        cout << "[+]Play [X][Y]SL [A]Undo [B]Reset/Quit" <<endl;
        //paint the grid
        for(i=1;i<=grdX;i++)
        {
            //output column number
            gotoxy(8*i,2);
            cout<<i;
        }
        cout<<endl;
		for(i=0;i<=grdY;i++)
        {
            for(j=1;j<=grdX;j++)
            {
                if (j==1) cout<<"   ";    //leave place for line number
                if (i==0||i==grdY) cout<<"========";    //topline
                else cout <<"--------";    //normal lines
                if (j==grdX&&(i==0||i==grdY)) cout<<'='<<endl<<endl;   //last char in topline
                else if (j==grdX&&i!=0) cout<<'-'<<endl<<endl;   //last char in normal line

            }
        }
		for(i=0;i<=grdX;i++)
        {
            for(int j=0;j<grdY;j++)
            {
                for(int k=4,n=0;n<=grdX;k=k+8,n++)
                {
                    if(k==4){gotoxy(2,2*j+4);cout<<j+1;}   //output line number
                    gotoxy(k,2*j+4);    //vertical lines
                    cout<<'.';
                }   codY[j]=2*j+4;     //coordinates of each posY
            }
            if(i!=grdX)codX[i]=6+8*i;    //coordinates of each posX
        }
        //grid painting complete

}
//------------------------------------------------------------------------------
void refreshAll(int isNoFile)
{
    flushMessage();
    refreshStatus(isNoFile);
    refreshDisplay();
}
/*------------------------------------------------------------------------------
void waitSec(int sec, char message[7])
{
    //waiting with graphics
    int nowTime=time(0);
    gotoxy(71,1);
    textcolor(YELLOW);
    textbackground(BLUE);
    cprintf("- %s", message);
    int waitSec_A=0;
    while(time(0)-nowTime<=sec)
	{
        gotoxy(71,1);
		sleep(200);
        switch(waitSec_A)
        {
            case 0: cprintf("\\"); waitSec_A=1; break;
            case 1: cprintf("|");  waitSec_A=2; break;
            case 2: cprintf("/");  waitSec_A=3; break;
            case 3: cprintf("-");  waitSec_A=0; break;
        }
    }
	gotoxy(71,1);
    cout<<"         ";
}
*///------------------------------------------------------------------------------
