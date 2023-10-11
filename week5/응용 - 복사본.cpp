#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define ANSI_COLOR_WHITE 	"\033[0m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RED		"\033[0;31m"


int intro_game(void);
char AU_ready(void);
void make_ready(void);
void draw_check02(int r, int c);
void gotoxy(int x, int y);
void number_display(int n);
void display_rule(int n, char question[][10]);
void make_question(int n, char question[][10]);
void game_control(char question[][10], int n, int *countA, int *countB, int *turn);
void clear_text(void);

int main(void){
	int n, countA =0; 
	int countB=0;
	int turn=1;
	char r;

	char question[10][10]={0};
	char answer[10][10]={0};
	long pst, seconds, minutes;
	clock_t start, end;
	srand(time(NULL));
	
	r= AU_ready();
	system("cls");
	
	if(r!='Y'){
		printf("\n\n\n\n\n������ �����մϴ�. \n\n");
		return 0;
	}else{

		n=intro_game();
		system("cls");
		
		draw_check02(n, n);
		number_display(n);
		display_rule(n, question);
		
		number_display(n);
		start=clock();
		
		gotoxy(28, 3);
		printf("�� ���� ����: %d", n*2);
			gotoxy(28, 2);
			printf("[�÷��̾� A]");

		gotoxy(28, 5);
		printf("���� ����:%2d", countA);
		gotoxy(28, 7);
		printf("���� ����:%2d", countB);
		
		do{
			game_control(question, n, &countA, &countB, &turn);
		}while(countA+countB<n*n/2);
		
		gotoxy(2, 18);
		printf("��� �¾ҽ��ϴ�. �����մϴ�. \n");
		end=clock();
		pst=(end-start)/CLK_TCK;
		minutes=pst/60;
		seconds=pst-minutes*60;
		gotoxy(2, 17);
		if(countA>countB){
			printf("�÷��̾� A �¸�!!");
		}else if(countA<countB){
			printf("�÷��̾� B �¸�!!");
		}else{ 
			printf("���º�");
		}
		
		gotoxy(2, 19);	
		printf("����ð� : %ld�� %ld ��\n", minutes, seconds);
		
		return 0;	
	} 
}

char AU_ready(void)
{
	char r;
	system("cls");
	printf("\n\n������ �����Ͻðڽ��ϱ�? \n");
	printf("�����ϰ� �����ôٸ� PLAY�� �����ּ���");
	make_ready();
	
while (1) {
    if (GetAsyncKeyState(VK_LBUTTON)) {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        if (cursorPos.x > 120 && cursorPos.x < 190 && cursorPos.y > 310 && cursorPos.y < 380) {
            r = 'Y';
            break; // 'Y'�� �ԷµǸ� ������ �����մϴ�.
        } else if (cursorPos.x > 260 && cursorPos.x < 340 && cursorPos.y > 310 && cursorPos.y < 380) {
            r = 'N';
            break; // 'N'�� �ԷµǸ� ������ �����մϴ�.
        }
    }
    Sleep(100);
}

    
	return r;
}

int intro_game(void)
{
	int n;
	system("cls");
	printf("���� ���� ���߱� \n\n");
	printf("���ڸ���� �ǿ� ������ �� ���� ���ڸ� ã�� \n");
	printf("�����Դϴ�. \n\n");
	printf("���� ����(4 �Ǵ� 6)�� �Է��ϰ� Enter>");
	scanf("%d",&n);
	
	if(n==4 || n==6){
		return n;
	}else{
		system("cls");
		printf("���� ���� ���߱� \n\n");
		printf("���ڸ���� �ǿ� ������ �� ���� ���ڸ� ã�� \n");
		printf("�����Դϴ�. \n\n");
		printf("���� ����(4 �Ǵ� 6)�� �Է��ϰ� Enter>");
		printf(" 4�Ǵ� 6�� �Է����ּ���.");
		Sleep(1500);
		
		return intro_game();
	}

}

void display_rule(int n, char question[][10])
{
 //[�Լ� 11.3.2]�� ���� �κ� ����
	gotoxy(2,14);
	printf(ANSI_COLOR_WHITE "���� ���� ���ڸ���� ���� �ڿ��� \n");
	gotoxy(2,15);
	printf("���� ����� ���ڰ� �ΰ��� ���� �ֽ��ϴ�. \n");
	gotoxy(2,16);
	printf("�ƹ�Ű�� ������ ����ȭ���� ��� ��Ÿ���ϴ�. \n");
	getch();
	clear_text();
	
	make_question(n, question);
	gotoxy(2,14);
	printf(ANSI_COLOR_WHITE "����ȭ���� ���� �����ϴ�. \n");
	gotoxy(2,15);
	printf("5�� �ڿ� ���� Ǯ�̸� �����մϴ�. \n");
	Sleep(5000);
	clear_text();
}

void game_control(char question[][10], int n, int *countA, int *countB, int *turn)
{
 //[�Լ� 11.3.3]�� ���� �κ� ����
	int user1, user2, row1, row2, col1, col2;
	int T = *turn;
	
	if(T%2==0){
		gotoxy(28, 2);
		printf("[�÷��̾� B]");
	}else{ 
		gotoxy(28, 2);
		printf("[�÷��̾� A]");
		}
	
	gotoxy(2, 14);
	printf("ù��° ���ڸ� �Է��ϰ� Enter>");
	scanf("%d", &user1);
	row1=user1/n;
    col1=user1%n;
    
	gotoxy(2, 15);
	printf("�ι�° ���ڸ� �Է��ϰ� Enter>");
	scanf("%d", &user2);
	row2=user2/n;
	col2=user2%n;
	
	if (question[row1][col1]==question[row2][col2]){
		if(T%2==1){
			*countA=*countA+1;
			gotoxy(28, 2);
		}else{
			*countB=*countB+1; 
			gotoxy(28, 2);}
		
		  gotoxy(28, 5);
		  printf(ANSI_COLOR_WHITE "���� ����:%2d��", *countA);
		  gotoxy(28, 7);
		  printf(ANSI_COLOR_WHITE "���� ����:%2d��", *countB);
		  
		if(T%2==0){
			gotoxy(3+4*col1, 2+2*row1);
			printf(ANSI_COLOR_CYAN "%2c", question[row1][col1]);
		  	gotoxy(3+4*col2, 2+2*row2);
		  	printf(ANSI_COLOR_CYAN "%2c", question[row2][col2]);
			
		}else{ 
			gotoxy(3+4*col1, 2+2*row1);
			printf(ANSI_COLOR_RED "%2c", question[row1][col1]);
		  	gotoxy(3+4*col2, 2+2*row2);
		  	printf(ANSI_COLOR_RED "%2c", question[row2][col2]);
			}
		  
		  
		  Beep(261.63, 500);
		  Beep(329.63, 500);
		  Beep(392.00, 500);
		  Beep(523.25, 500);

		  
	  	  gotoxy(2, 16);
	      printf(ANSI_COLOR_WHITE "�¾ҽ��ϴ�. ���͸� ������ �Ѿ�ϴ�. \n");
	      getch();
	    (*turn)++;
		  clear_text();
	}
	else{
		  Beep(392.00, 800);
		  
		if(T%2==0){
			gotoxy(3+4*col1, 2+2*row1);
			printf(ANSI_COLOR_CYAN "%2c", question[row1][col1]);
		  	gotoxy(3+4*col2, 2+2*row2);
		  	printf(ANSI_COLOR_CYAN "%2c", question[row2][col2]);
			
		}else{ 
			gotoxy(3+4*col1, 2+2*row1);
			printf(ANSI_COLOR_RED "%2c", question[row1][col1]);
		  	gotoxy(3+4*col2, 2+2*row2);
		  	printf(ANSI_COLOR_RED "%2c", question[row2][col2]);
			}
		
	Sleep(3000);
		
		gotoxy(3+4*col1, 2+2*row1);
		printf(ANSI_COLOR_WHITE "%2d", user1);
		gotoxy(3+4*col2, 2+2*row2);
		printf(ANSI_COLOR_WHITE "%2d", user2);
		
		
	  	gotoxy(2, 16);
	    printf("Ʋ�Ƚ��ϴ�. ���͸� ������ �Ѿ�ϴ�. \n");
		getch();
	    (*turn)++;
		clear_text();
	}
}

void clear_text(void)
{
	int i, j;
	for(i=14;i<20;i++)
	{
		gotoxy(2, i);
		for(j=0;j<50;j++)
			printf(" ");
	}
}

void number_display(int n)
{
  int i, j, count=0;
  for(i=0;i<n;i++)
	  for(j=0;j<n;j++)
	  {
		  gotoxy(3+4*j, 2+2*i);
		  printf(ANSI_COLOR_WHITE "%2d", count);
		  count++;
	  }
}
void make_question(int n, char question[][10])
{
	  int number, i, j, ran, count1=0, count2=0;
	  char chr1[26], chr2[26], temp;
	  srand(time(NULL));
	  number=n*n/2;
	  
  for(i=0;i<26;i++)   {
	  chr1[i]=65+i;
	  chr2[i]=i;
  }
  
  for(i=0;i<number;i++)   {
	  ran=rand()%number;
	  temp=chr1[i];
	  chr1[i]=chr1[ran];
	  chr1[ran]=temp;
  }
  
  
  for(i=0;i<number;i++)   {
	  ran=rand()%number;
	  temp=chr2[i];
	  chr2[i]=chr2[ran];
	  chr2[ran]=temp;
  }
  
   for(i=0;i<n;i++){
   
	   for(j=0;j<n;j++){
		   if (count1<number){
				question[i][j]=chr1[count1];
				count1++;
		   }
		   else{
			   question[i][j]=chr1[chr2[count2]];
			   count2++;
		   }
	   }
}
   for(i=0;i<n;i++)    {
	   for(j=0;j<n;j++) 	   {
		  gotoxy(3+4*j, 2+2*i);
		  printf(ANSI_COLOR_WHITE "%2c", question[i][j]);
		 }
          }
      
}
void draw_check02(int r, int c)
{
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[12]; 
    for(i=1;i<12;i++)
	b[i]=0xa0+i;
    printf("%c%c",a, b[3]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    printf("%c%c", a, b[1]);
    
    for(i=0;i<c-1;i++)
    {
	    printf("%c%c", a, b[8]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
    }
    
    printf("%c%c", a, b[4]);
    printf("\n");
    
    
    for(i=0;i<r-1;i++){
	printf("%c%c", a, b[2]);
		for(j=0;j<c;j++){
			printf("   ");
			printf("%c%c",a, b[2]);
		}
		printf("\n");
		
		printf("%c%c", a, b[7]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
		
		for(j=0;j<c-1;j++){
			printf("%c%c", a, b[11]);
			printf("%c%c", a, b[1]);
			printf("%c%c", a, b[1]);
			printf("%c%c", a, b[1]);
		}

	printf("%c%c",a, b[9]);
	printf("\n");
    }
	
	printf("%c%c", a, b[2]);
	for(j=0;j<c;j++){
		printf("   ");
		printf("%c%c",a, b[2]);
	}

    printf("\n");
    printf("%c%c", a, b[6]);
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[1]);
	printf("%c%c", a, b[1]);
    
    
    for(i=0;i<c-1;i++){
		printf("%c%c", a, b[10]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
		printf("%c%c", a, b[1]);
    }

    printf("%c%c", a, b[5]);
    printf("\n");
}


void make_ready(void){

		int size=3;
    int i, j;
    unsigned char a=0xa6;
    unsigned char b[7]; 
    for(i=1;i<7;i++)
   	b[i]=0xa0+i;

	gotoxy(4, 10);
    printf("%c%c",a, b[3]);
    for(i=0;i<=size*2;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    
        gotoxy(4, 11);
 		printf("%c%c", a, b[2]);
		for(j=0;j<= size*2 ;j++) { printf(" ");}
		printf("%c%c",a, b[2]);
		
		gotoxy(4, 12);
 		printf("%c%c", a, b[2]);
		printf(" PLAY! ");
		printf("%c%c",a, b[2]);
		
		gotoxy(4, 13);
 		printf("%c%c", a, b[2]);
		for(j=0;j<= size*2 ;j++) { printf(" ");}
		printf("%c%c",a, b[2]);
		
    
    gotoxy(4, 14);
    printf("%c%c", a, b[6]);
    for(i=0;i<=size*2;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
    			
    
    
    gotoxy(20, 10);
    printf("%c%c",a, b[3]);
    for(i=0;i<=size*2;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);

        gotoxy(20, 11);
 		printf("%c%c", a, b[2]);
		for(j=0;j<= size*2 ;j++) { printf(" ");}
		printf("%c%c",a, b[2]);
		
		gotoxy(20,12);
 		printf("%c%c", a, b[2]);
		printf("  NO!  ");
		printf("%c%c",a, b[2]);
		
		gotoxy(20, 13);
 		printf("%c%c", a, b[2]);
		for(j=0;j<= size*2 ;j++) { printf(" ");}
		printf("%c%c",a, b[2]);
    
    gotoxy(20, 14);
    printf("%c%c", a, b[6]);
    for(i=0;i<=size*2;i++)
	printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
    
}
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
