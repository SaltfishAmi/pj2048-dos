#include "MAIN.H"
int moveAll(int direction)
{
int doMoved=0;
if(direction==0){     //w
    for(int i=0;i<grdX;i++)
    {
        for(int j=0;j<grdY-1;j++)
        {
            if(data[i][j]==0)
            {
                if(data[i][j+1]!=0)doMoved=1;
                int isEmptyLine=1;
                for(int k=j;k<grdY-1;k++)
                {
                    data[i][k]=data[i][k+1];
                    data[i][k+1]=0;
                    if(data[i][k]>0)isEmptyLine=0;
                    //refreshDisplay();
                    //waitSec(1);
                }
                if(data[i][j]==0&&isEmptyLine==0)j--;
            }
        }
    }
}
else if(direction==1){  //a
    for(int i=0;i<grdY;i++)
    {
        for(int j=0;j<grdX-1;j++)
        {
            if(data[j][i]==0)
            {   if(data[j+1][i]!=0)doMoved=1;
                int isEmptyLine=1;
                for(int k=j;k<grdX-1;k++)
                {
                    data[k][i]=data[k+1][i];
                    data[k+1][i]=0;
                    if(data[k][i]>0)isEmptyLine=0;
                    //refreshDisplay();
                    //waitSec(1);
                }
                if(data[j][i]==0&&isEmptyLine==0)j--;
            }
        }
    }
}
else if(direction==2){  //s
    for(int i=0;i<grdX;i++)
    {
        for(int j=grdY-1;j>1;j--)
        {
            if(data[i][j]==0)
            {   if(data[i][j-1]!=0)doMoved=1;
                int isEmptyLine=1;
                for(int k=j;k>0;k--)
                {
                    data[i][k]=data[i][k-1];
                    data[i][k-1]=0;
                    if(data[i][k]>0)isEmptyLine=0;
                    //refreshDisplay();
                    //waitSec(1);
                }
                if(data[i][j]==0&&isEmptyLine==0)j++;
            }
        }
    }
}
else if(direction==3){  //d
    for(int i=0;i<grdY;i++)
    {
        for(int j=grdX-1;j>1;j--)
        {   if(data[j-1][i]!=0)doMoved=1;
            if(data[j][i]==0)
            {
                int isEmptyLine=1;
                for(int k=j;k>0;k--)
                {
                    data[k][i]=data[k-1][i];
                    data[k-1][i]=0;
                    if(data[k][i]>0)isEmptyLine=0;
                    //refreshDisplay();
                    //waitSec(1);
                }
                if(data[j][i]==0&&isEmptyLine==0)j++;
            }
        }
    }
}
return doMoved;
}
//------------------------------------------------------------------------------
void moveLine(int direction, int lineNumber)//lineNumber starts at 0
{
if(direction==0) //w
    for(int j=0;j<grdY-1;j++)
    {
        if(data[lineNumber][j]==0)
        {
            int isEmptyLine=1;
            for(int k=j;k<grdY-1;k++)
            {
                data[lineNumber][k]=data[lineNumber][k+1];
                data[lineNumber][k+1]=0;
                if(data[lineNumber][k]>0)isEmptyLine=0;
                //refreshDisplay();
                //waitSec(1);
            }
            if(data[lineNumber][j]==0&&isEmptyLine==0)j--;
        }
    }
else if(direction==1) //a
    for(int j=0;j<grdX-1;j++)
    {
        if(data[j][lineNumber]==0)
        {
            int isEmptyLine=1;
            for(int k=j;k<grdX-1;k++)
            {
                data[k][lineNumber]=data[k+1][lineNumber];
                data[k+1][lineNumber]=0;
                if(data[k][lineNumber]>0)isEmptyLine=0;
                //refreshDisplay();
                //waitSec(1);
            }
            if(data[j][lineNumber]==0&&isEmptyLine==0)j--;
        }
    }
else if(direction==2) //s
    for(int j=grdY-1;j>1;j--)
    {
        if(data[lineNumber][j]==0)
        {
            int isEmptyLine=1;
            for(int k=j;k>0;k--)
            {
                data[lineNumber][k]=data[lineNumber][k-1];
                data[lineNumber][k-1]=0;
                if(data[lineNumber][k]>0)isEmptyLine=0;
                //refreshDisplay();
                //waitSec(1);
            }
            if(data[lineNumber][j]==0&&isEmptyLine==0)j++;
        }
    }
else if(direction==3)
    for(int j=grdX-1;j>1;j--)
    {
        if(data[j][lineNumber]==0)
        {
            int isEmptyLine=1;
            for(int k=j;k>0;k--)
            {
                data[k][lineNumber]=data[k-1][lineNumber];
                data[k-1][lineNumber]=0;
                if(data[k][lineNumber]>0)isEmptyLine=0;
                //refreshDisplay();
                //waitSec(1);
            }
            if(data[j][lineNumber]==0&&isEmptyLine==0)j++;
        }
    }
}
//------------------------------------------------------------------------------
int addAll(int direction)
{
int doAdded=0;
if(direction==0) //w
{
    for(int i=0;i<grdX;i++)
    {
        for(int j=0;j<grdY-1;j++)
        {
            if(data[i][j]==data[i][j+1]&&data[i][j]>0)
            {
                data[i][j]*=base;
                score+=data[i][j];
                doAdded=1;
                data[i][j+1]=0;
                moveLine(0,i);
                //refreshDisplay();
                //break;
            }
        }
    }
}
else if(direction==1) //a
{
    for(int i=0;i<grdY;i++)
    {
        for(int j=0;j<grdX-1;j++)
        {
            if(data[j][i]==data[j+1][i]&&data[j][i]>0)
            {
                data[j][i]*=base;
                score+=data[i][j];
                doAdded=1;
                data[j+1][i]=0;
                moveLine(1,j);
                //refreshDisplay();
                //break;
            }
        }
    }
}
else if(direction==2) //s
{
    for(int i=0;i<grdX;i++)
    {
        for(int j=grdY-1;j>0;j--)
        {
            if(data[i][j]==data[i][j-1]&&data[j][i]>0)
            {
                data[i][j]*=base;
                score+=data[i][j];
                doAdded=1;
                data[i][j-1]=0;
                moveLine(2,i);
               // break;
            }
        }
    }
}
else if(direction==3) //d
{
    for(int i=0;i<grdY;i++)
    {
        for(int j=grdX-1;j>0;j--)
        {
            if(data[j][i]==data[j-1][i]&&data[j][i]>0)
            {
                data[j][i]*=base;
                score+=data[i][j];
                doAdded=1;
                data[j-1][i]=0;
                moveLine(3,i);
                //break;
            }
        }
    }
}
return doAdded;
}
//------------------------------------------------------------------------------
