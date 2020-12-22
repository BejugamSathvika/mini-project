#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define SIZE 4
#define BORDER 219
#define ESC '\x1b'

int Matrix[SIZE+1][SIZE+1]={0};
int score=0,last=2048;

void starting();
void wait();
void waitL();
void Display();
void print();
void Action(int);
void Random_Values_creator();
void Starting_Values();
int Maximum();
void Down();
void Up();
void Left();
void Right();

void SetColor(int ForgC)      // to set the colour of the strings
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     //A return value... indicating how many chars were written
     //   not used but we need to capture this since it will be
     //   written anyway (passing NULL causes an access violation).
     DWORD count;
     //This is a structure containing all of the console info
     // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC) // To set Both background and text colour
{
     WORD wColor = ((BackC & 0x0F) << 8) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void starting()     //To print instructions
{
    ClearConsoleToColors(25,0);
    printf("\n\n\n\n\n");
    printf("\n\t\t\t        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    printf("\n\t\t\t        *                  WELCOME                  *");
    printf("\n\t\t\t        *                    TO                     *");
    printf("\n\t\t\t        *               2048   GAME                 *");
    printf("\n\t\t\t        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");


    waitL();
    waitL();

    printf("\n\n\n\n\n\n\n\t\t\t\t");
    waitL();
    waitL();
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    printf("\n\n\n\n\t");
    printf("\n\n\n\n\t\t");
    waitL();
    waitL();
    system("cls");
    printf("\n\n\t\t\t\t\t");
    printf("\n\n\t");
    waitL();
    waitL();
    system("cls");
    ClearConsoleToColors(10,0);
    printf("\n\n\n\t\t\t**********INSTRUCTIONS TO PLAY GAME***********\n\n\n");
    printf(" 1.  Enter arrow key to move\n\n");
    printf(" 2.  For winning this game any one box have value 2048\n\n");
    printf(" 3.  Enter Esc to quit the game in the middle\n\n");
    printf(" 4.  PRESS ANY KEY TO PLAY\n\n\n");
    while(!kbhit());
}

void wait()
{
    int i;
    for(i=0;i<4500000;i++);
}
void waitL()
{
    int i;
    for(i=0;i<25;i++)
    {
        wait();
    }
}
void Action(int Arrow)
{

    switch(Arrow)
    {
        case UP:
            {
                Up();
                break;
            }
        case DOWN:
            {
                Down();
                break;
            }
        case LEFT:
            {
                Left();
                break;
            }
        case RIGHT:
            {
                Right();
                break;
            }
        default:
            {
                return;
            }
    }
    Random_Values_creater();
    Display();
}

void Random_Values_creater()
{
    int temp1,temp2,add,i,j;
    srand(time(NULL));
    temp1=rand()%SIZE;  

    srand(time(NULL));
    temp2=rand()%SIZE;  

    if((temp1+temp2)%2==0)
        add=2;
    else
        add=4;

    for(i=0;i<temp1;i++)
    {
        for(j=temp2;j<SIZE;j++)
        {
            if(Matrix[i][j]==0)
            {
                Matrix[i][j]=add;
                return;
            }
        }
    }
}

void Display()
{
    ClearConsoleToColors(30,0);
    int i,j;
    system("cls");
    print();
    for(i=0;i<SIZE;i++)
    {
        printf("\t\t\t %c",BORDER);
        for(j=0;j<SIZE;j++)
        {
            if(Matrix[i][j]==0)
            {
                printf("      ");
            }
            else
                printf(" %4d ",Matrix[i][j]);
        }
        printf("%c\n\t\t\t %c                        %c\n",BORDER,BORDER,BORDER);
    }
    printf("\t\t\t %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n",BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER);
}
//To display the highest score
void print()
{
    printf("\n\n\n\t\t\t***********TWO-ZERO-FOUR-EIGHT************\n");
    printf("\t\t\t\t\t\t\t\t SCORE  : %d\n\n\n\n",score);
    printf("\t\t\t %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER,BORDER);

}
//Initialising some values in the box to play the game
void Starting_Values()
{
    Matrix[3][1]=2;
    Matrix[2][2]=4;
    Matrix[2][3]=2;
    Matrix[1][2]=2;

    Display();
}
/* TO FIND MAX VALUE FROM WHOLE MATRIX */
int Maximum()
{
    int temp=0,i,j;

    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            if(Matrix[i][j]==2048)
                return(1);
            if(Matrix[i][j]==0)
                temp=1;
        }
    }
    if(temp==1)
    {
        last=2048;
        return(-99);
    }
    else
    {
        if(last==1)
        {
            return(0);
        }
        last=1;
        return(-99);
    }
}

void Down()   //To move the numbers towards down side
{
    int i,j;
    for(j=0;j<SIZE;j++)
    {
        i=2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==-1)
                    break;
                i--;
            }
            if(i==-1)
                break;
            while(i<SIZE-1 && (Matrix[i+1][j]==0 || Matrix[i][j]==Matrix[i+1][j]))
            {

                if(Matrix[i][j]==Matrix[i+1][j])
{
                    Matrix[i+1][j]+=Matrix[i][j];
                    score=score+Matrix[i+1][j];
                }
                else
{
                    Matrix[i+1][j]=Matrix[i][j];
                }
                Matrix[i][j]=0;
                i++;
            }
            i--;
        }
    }
}
void Up()   //To move the numbers towards up side
{
    int i,j;
    for(j=0;j<SIZE;j++)
    {
        i=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(i==SIZE)
                    break;
                i++;
            }
            if(i==SIZE)
                break;
            while(i>0 && (Matrix[i-1][j]==0 || Matrix[i][j]==Matrix[i-1][j]))
            {
                if(Matrix[i][j]==Matrix[i-1][j])
{
                Matrix[i-1][j]+=Matrix[i][j];
                score=score+Matrix[i-1][j];
                }
                else
{
                     Matrix[i-1][j]=Matrix[i][j];
                }
                Matrix[i][j]=0;
                i--;
            }
            i++;
        }
    }
}
void Right()   //To move the numbers towards right side
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        j=2;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==-1)
                    break;
                j--;
            }
            if(j==-1)
                break;
            while(j<SIZE-1 && (Matrix[i][j+1]==0 || Matrix[i][j]==Matrix[i][j+1]))
            {
                 if(Matrix[i][j]==Matrix[i][j+1])
{
                     Matrix[i][j+1]+=Matrix[i][j];
                     score=score+Matrix[i][j+1];
                 }
                 else
{
                    Matrix[i][j+1]=Matrix[i][j];
                 }
                Matrix[i][j]=0;
                j++;
            }
            j--;
        }
    }
}
void Left()   //To move the numbers towards left side
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        j=1;
        while(1)
        {
            while(Matrix[i][j]==0)
            {
                if(j==SIZE)
                    break;
                j++;
            }
            if(j==SIZE)
                break;
            while(j>0 && (Matrix[i][j-1]==0 || Matrix[i][j]==Matrix[i][j-1]))
            {
                if(Matrix[i][j]==Matrix[i][j-1])
{
                Matrix[i][j-1]+=Matrix[i][j];
                    score=score+Matrix[i][j-1];
                }
                else
{
                     Matrix[i][j-1]=Matrix[i][j];
                }
                Matrix[i][j]=0;
                j--;
            }
            j++;
        }
    }
}
int main()
{
    ClearConsoleToColors(20,0);
    int aro;
    char Arrow;
    int temp;
    starting();
    Starting_Values();
    Arrow=DOWN;
    //  HERE IF USER WANT TO EXIT THEN PRESS ESC KEY
    while(Arrow!=ESC)  
    {
        Arrow=getch();
        aro=Arrow;
        Action(Arrow);
        temp=Maximum();
        if(temp==1)
        {
            printf("\n\t\t\tYOU WON");
            break;
        }
        if(temp==0 || score>2048)
        {
            printf("\n\t\t\tSORRY !  GAME OVER\n");
            break;
        }
    }

    system("cls");
    printf("\n\n\n\t");
    printf("THANKS FOR PLAYING, GOOD LUCK FOR NEXT TIME ");
}


