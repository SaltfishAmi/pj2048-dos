#include "MAIN.H"
void saveToFile(char *fileName)
{
    ofstream outfile;
    outfile.open(fileName,ios::out|ios::trunc);
    outfile<<grdX<<" "<<grdY<<" ";
    outfile<<score<<" "<<round<<" ";
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            outfile<<data[i][j]<<" ";
    outfile.close();
}
//------------------------------------------------------------------------------
int checkFile(char *fileName)
{
    ifstream infile;
    infile.open(fileName);
    if(!infile) return 0;
    else return 1;
}
//------------------------------------------------------------------------------
int loadFromFile(char *fileName)
{
    int tmpX=grdX, tmpY=grdY;
    if(checkFile(fileName)==0)
        return 0;
    ifstream infile;
    infile.open(fileName,ios::in);//|ios::nocreate);
    infile>>tmpX>>tmpY;
    if(tmpX!=grdX||tmpY!=grdY)
    {
        flushMessage();
        cout<<"Your current grid size is "<<grdX<<" x "<<grdY<<"."<<endl;
        cout<<"Grid size stored in file is "<<tmpX<<" x "<<tmpY<<"."<<endl;
        cout<<"Press A to continue loading, or press B to abandon loading."<<endl;
        char input=getch();
        if(input==13)return 2;
        else if (input=='z'||input=='Z')
        {
            paintGrid(tmpX, tmpY);
            loadFromFile(fileName);
            refreshAll();
            return 3;
        }
    }
    infile>>score>>round;
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            infile>>data[i][j];
    infile.close();
    refreshDisplay();
    return 1;
}
//------------------------------------------------------------------------------
void cleanFile()
{
    if(checkFile("1.424")==1)system("del \"1.424\"");
    if(checkFile("2.424")==1)system("del \"2.424\"");
    if(checkFile("3.424")==1)system("del \"3.424\"");
}