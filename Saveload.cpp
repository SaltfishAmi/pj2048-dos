#include "MAIN.H"
void saveProgress(int slotNumber)
{
    if(slotEmpty[slotNumber]==0)
    {
        slotEmpty[0]=0;
        for(int i=0;i<=7;i++)
        {
            for(int j=0;j<=7;j++)
            {
                switch(lastOverwrittenNumber)
                {
                    case 1:   lastOverwritten[i][j]=slot1[i][j]; break;
                    case 2:   lastOverwritten[i][j]=slot2[i][j]; break;
                    case 3:   lastOverwritten[i][j]=slot3[i][j]; break;
                    case EOF:
                        lastOverwritten[i][j]=0;
                        slotEmpty[0]=1;
                        break;
                }
            }
        }
        slotData[0][0]=slotData[slotNumber][0];
        slotData[0][1]=slotData[slotNumber][1];
    }
    for(int i=0;i<=7;i++)
    {
        for(int j=0;j<=7;j++)
        {
            switch(slotNumber)
            {
                case 1: slot1[i][j]=data[i][j]; break;
                case 2: slot2[i][j]=data[i][j]; break;
                case 3: slot3[i][j]=data[i][j]; break;
            }
        }
    }
    slotData[slotNumber][0]=round;
    slotData[slotNumber][1]=score;
    slotEmpty[slotNumber]=0;
    lastOverwrittenNumber=slotNumber;
}
//------------------------------------------------------------------------------
int loadProgress(int slotNumber)
{
    if(slotEmpty[slotNumber]==0)
    {
        for(int i=0;i<=7;i++)
        {
            for(int j=0;j<=7;j++)
            {
                switch(slotNumber)
                {
                    case 0: data[i][j]=lastOverwritten[i][j]; break;
                    case 1: data[i][j]=slot1[i][j];         break;
                    case 2: data[i][j]=slot2[i][j];         break;
                    case 3: data[i][j]=slot3[i][j];         break;
                }
            }
        }
        round=slotData[slotNumber][0];
        score=slotData[slotNumber][1];
        refreshDisplay();
        return 1;
    }
    else return 0;
}
//------------------------------------------------------------------------------
void cleanData()
{
    for(int i=0;i<=7;i++)
    {
        if(i<=3)slotEmpty[i]=1;
        for(int j=0;j<=7;j++)
        {
            if(i<=3&&j<=1)slotData[i][j]=0;
            slot1[i][j]=0;
            slot2[i][j]=0;
            slot3[i][j]=0;
            lastOverwritten[i][j]=0;
        }
    }
}