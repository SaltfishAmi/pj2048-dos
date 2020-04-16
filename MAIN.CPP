//
// COPYRIGHT (C) 2014 "Hinpbock Technologies Incorporated".
// ALL RIGHTS RESERVED.
// "HINPBOCK is not programmed based on classroom knowledge!"
// Version 2.5DS
//
//------------------------------------------------------------------------------
#include "MAIN.H"
//void enterDevMode();


const int base=2;
int grdX, grdY, posX, posY;
long data[8][8];
int codX[8], codY[8];
int round;
int score;
int needRepaint=0;
//will be moved into Functions.cpp
long lastData[8][8];
int lastScore=0;


// A=enter
// B=Z
// X=8
// Y=9




void main()
{

//preparation
    int noSL;
	char input;
    int i,j;
    randomize();
//initialization
	textcolor(LIGHTGRAY);
    clrscr();
    gotoxy(1,1);
//    system("color 1F");
    cout<<"2048 for DSx86&DS2x86, version "<< VERSION << endl;
    cout<<"Copyright (C) 2014 Hinpbock Technologies."<<endl;
//    system("title Console 2048");
    //cout<<"Press D to enter Development Mode."<<endl;
    //cout<<"Note that Development Mode will require a mathematical password."<<endl;
    cout<<"Press any key to continue...";
    getch();
    //if(input=='D'||input=='d')enterDevMode();
//stem circulation
    for(;;)
    {
        restart:
        cleanData();
        clrscr();
//        system("color 1F");
        gotoxy(1,1);
        grdX=4;
        grdY=4;
//        system("title Console 2048 - selecting grid size");
        /*cout<<"Please select the size of the grid,\nor press B to quit:"<<endl;
        while(1)
        {
            cout<<"[A]4x4 [X]3x3 -> ";
            input=getch();
			if(input=='Z'||input=='z')return;
            if(input==13)
            {
                cout<<'4'<<endl;
                grdY=4;grdX=grdY;
            }
            else if(input=='8')
            {
                cout<<'3'<<endl;
                grdY=3;grdX=grdY;
            }
            if (grdX==3||grdX==4)break;
        }  */
        /*while(1)
        {
            cout<<"Then press a number key in [2,8] to determine lines.";
            input=getch();
            if(input=='0')return 0;
            cout<<input<<endl;
            grdY=input-48;
            if (grdY>=2&&grdY<=8)break;
        } */   /*
        cout<<"Ok. Now your grid will be "<<grdX<<'x'<<grdY<<"."<<endl;
        while(1)
        {
            cout<<"[A]Confirm [B]Cancel";
            input=getch();
			//if(input=='0')return;
            //cout<<input<<endl;
            if(input==13||input=='Z'||input=='z') break;
        }
        if (input=='Z'||input=='z') continue;   */
        restartSame:
        //waitSec(1);
        paintGrid(grdX, grdY);
        noSL=1;
        round=0;
        score=0;
//game start
//initializing data = 0
        for(int i=0;i<=7;i++)
            for(int j=0;j<=7;j++)
            {
                if(i<=grdX-1&&j<=grdY-1)
                        data[i][j]=0;
                else data[i][j]=EOF;
            }
//generate a 2 at the beginning
        posX=rand()%grdX;
        posY=rand()%grdY;
        data[posX][posY]=base;
//        gotoxy(codX[posX],codY[posY]);
//        cout<<data[posX][posY];
        int firstRound=1, fr2=1;  // fr2==1 <==> Un-undo-able
                                  // including 1)firstRound
                                  //           2)already undo-ed this round
        int doMoved=0, doAdded=0;
        //int gridFull=1;
        //int needGen=0;
        genNew2();
        while(1)
        {
//main game function
            int gridFull=1;
            for(int i=0;i<grdX;i++)
            {
                for(int j=0;j<grdY;j++)
                {
                    if(data[i][j]==0)gridFull=0;
                }
            }
            int roundPassed=0;
            if(firstRound==1||doMoved==1||doAdded==1)
            {
                roundPassed=1;
            //    needGen=1;
            }
            if(gridFull==1&&!roundPassed)
//determine gameover
            {
                refreshDisplay();
                flushMessage();
//                system("color 4f");
                cout<<"You lose the game!!"<<endl;
                cout<<"Your score is: ";
                if(noSL==1)cout<<score<<endl;
                else cout<<score/2<<endl;
                cout<<"[B]Quit [Y]Load"<<endl;
                //cout<<"or Q to quickly restart using previous settings."<<endl;
                while(1)
                {
                    input=getch();
                    switch(input)
                    {
						case 'Z': case 'z': return;
                        //case 'R': case 'r': goto restart;
                        //case 'Q': case 'q': goto restartSame;
                        case '9':
                        dialogSL(STF_L);
//                        system("color 1f");
                        goto regetch;
                    }
                }
            }
            firstRound=0;
            if(roundPassed)
            {
                round++;
                refreshDisplay();
                if(doMoved==1||doAdded==1){
                //while(needGen==1)
                genNew2();
            }
//determine gameover again
                gridFull=1;

                for(i=0;i<grdX;i++)
                {
                    for(j=0;j<grdY;j++)
                    {
                        if(data[i][j]==0)gridFull=0;
                    }
                }
                int isAddable=0;
				for(i=0;i<grdX;i++)
                {
                    for(int j=0;j<grdY-1;j++)
                    {
                        if(data[i][j]==data[i][j+1])isAddable=1;
                    }
                }
				for(i=0;i<grdY;i++)
                {
                    for(int j=0;j<grdX-1;j++)
                    {
                        if(data[j][i]==data[j+1][i])isAddable=1;
                    }
                }
                if(isAddable==0&&gridFull==1)
                {
                    refreshDisplay();
                    flushMessage();
//                    system("color 4f");
                    cout<<"You lose the game!!"<<endl;
                    cout<<"Your score is: ";
                    if(noSL==1)cout<<score<<endl;
                    else cout<<score/2<<endl;
                    cout<<"[B]Quit [Y]Load"<<endl;
                    //cout<<"or Q to quickly restart using previous settings."<<endl;
                    while(1)
                    {
                        input=getch();
                        switch(input)
                        {
							case 'Z': case 'z': return;
                            //case 'R': case 'r': goto restart;
                            //case 'Q': case 'q': goto restartSame;
                            case '9':
                            dialogSL(STF_L);
//                            system("color 1f");
                            goto regetch;
                        }
                    }
                }
            }
            //for(int i=0;i<=7;i++)
            //    for(int j=0;j<=7;j++)
            //        lastData[i][j]=data[i][j];
            while(1)
            {
//accept inputs
                regetch: flushMessage();
                input=getch();
                if(input=='z'||input=='Z')
                {
                    while(1)
                    {
                        flushMessage();
                        cout<<"All your progress and saves,\nexcluding file saves, will be lost!"<<endl;
                        cout<<"[A]Confirm [B]Cancel"<<endl;
                        input=getch();
                        flushMessage();
                        cout<<"                       "<<endl;
                        if (input==13)
                        {
                            while(1)
                            {
                                flushMessage();
                                cout<<"Do you want to quit or restart?"<<endl;
                                cout<<"[A]Restart [B]Quit"<<endl;
                                input=getch();
                                if (input==13)goto restart;
                                else return;
                            }
                        }
                        else if (input=='z'||input=='Z') break;
                    }
                    if (input=='0') continue;
                }
                int inpCorr=0;
                switch(input)
                {
                    case 'w': case 'W':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
                        for(i=0;i<=7;i++)
                            for(j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(0);
                        //refreshDisplay();
                        doAdded=addAll(0);
                        //refreshDisplay();

                        break;
                    case 's': case 'S':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
						for(i=0;i<=7;i++)
							for(j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(2);
                        doAdded=addAll(2);
                        break;
                    case 'a': case 'A':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
						for(i=0;i<=7;i++)
							for(j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(1);
                        //refreshDisplay();
                        doAdded=addAll(1);
                        //refreshDisplay();
                        break;
                    case 'd': case 'D':
                        inpCorr=1;
                        fr2=0;
                        lastScore=score;
						for(i=0;i<=7;i++)
							for(j=0;j<=7;j++)
                                lastData[i][j]=data[i][j];
                        doMoved=moveAll(3);
                        doAdded=addAll(3);
                        break;
                    case '8': dialogSL(STF_S); noSL=0; continue;
                    case '9': dialogSL(STF_L); noSL=0; continue;
                    case 13:// case 'z':
                        if(fr2==1)
                        {
                            flushMessage();
                            cout<<"Unable to undo now."<<endl;
                            break;
                        }
                        fr2=1;
                        score=lastScore;
                        round--;
						for(i=0;i<=7;i++)
							for(j=0;j<=7;j++)
                                data[i][j]=lastData[i][j];
                                refreshDisplay();
                        continue;
                    //case 'P': case 'p':
                        //if(promptOnOverwrite==0)promptOnOverwrite=1;
                        //else if(promptOnOverwrite==1)promptOnOverwrite=0;
                        //refreshStatus(NOFILE);
                        //continue;
                }
                if (needRepaint==1) goto restartSame;
                if (inpCorr==1)
                    break;
            }
            //main game function ends here
            //getch();
        }
    }
}





