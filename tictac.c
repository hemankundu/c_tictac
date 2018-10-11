#include <stdio.h>
#include <stdlib.h>
char *CLR[]={"\x1B[31m","\x1B[34m","\x1B[33m"};
int clr;
void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}

void draw_X_O(char ch,int i,int j)
{
 	int x = 31+(j*7), y = 10+(i*3);
 	gotoxy(x,y);
 	printf("%s%c",CLR[clr],ch);
}

void boardPrint()
{
 	int i,j,c;
 	system("clear");
 	for(i=9;i<17;i++)
 	{
  		gotoxy(35,i);
  		printf("|       |");
 	}
 	gotoxy(28,11);
 	printf("-----------------------");
 	gotoxy(28,14);
 	printf("-----------------------");
 	clr=2;
 	for(i=0,c=0;i<3;i++)
 		for(j=0;j<3;j++,c++)
 			draw_X_O(49+c,i,j);
}

int isWon(int board[3][3])
{
	int val,i,draw=1;
	for(i=0;i<3;i++)
	{
		val=board[i][0]*board[i][1]*board[i][2];
		draw*=val;
		if(val==8) return 2;
		else if(val==1) return 1;
	}
	for(i=0;i<3;i++)
	{
		val=board[0][i]*board[1][i]*board[2][i];
		if(val==8) return 2;
		else if(val==1) return 1;
	}
	val=board[0][0]*board[1][1]*board[2][2];
	if(val==8) return 2;
	else if(val==1) return 1;
	val=board[0][2]*board[1][1]*board[2][0];
	if(val==8) return 2;
	else if(val==1) return 1;
	return (draw)?3:0;
}

void winnerFound(int n,char pname[2][10])
{
	gotoxy(31,23);
	if(n==3)
		printf("\nDraw game\n\n");
	else
		printf("\n%s won.\n\n",pname[n-1]);
}

void startGame(int board[3][3],char pname[2][10])
{
	int turn=0,pos,i,j,winner=0;
    boardPrint();
	while(winner==0)
	{
		gotoxy(31,20);
		clr=turn;
		printf("%s's turn",pname[turn]);
		printf("\nEnter choice: \b");
		scanf("%d",&pos);
		if(pos==0) exit(0);
		if(pos>0&&pos<10)
		{
			i=(pos-1)/3;
			j=(pos-1)%3;
			if(board[i][j]) continue;
			board[i][j]=turn+1;
			draw_X_O((turn)?'X':'O',i,j);
		}
		else continue;
		winner=isWon(board);
		turn=(turn)?0:1;
	}
	winnerFound(winner,pname);
}

int main()
{
	system("clear");
	int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
    char pname[2][10];
	printf("\n2 player mode\n::");
	printf("\nEnter player1 name: ");
	scanf("%s",pname[0]);
	printf("\nEnter player2 name: ");
    scanf("%s",pname[1]);
	startGame(board,pname);
	return 0;
}
