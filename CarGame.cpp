#include <fstream>
#include <conio>
#include <stdlib>
#include <stdio.h>
#include <ctype>
#include <windows>

typedef char string[70];

class player
{
	int score;
   string name;

   public :
   void getData()
   { printf("%-5s    :     %-5d",name,score); }

   player()
   {
   	strcpy(name,"No Name");
      score=0;
   }

   void setData(string nameArg,int scoreArg)
   {
     strcpy(name,nameArg);
     score=scoreArg;
	}
};

void printMultiLineStringAtXY(char* car,int posX,int posY)
{
   int x=0,y=0;
   for(int i=0;car[i];i++)
   {
   	if(car[i]=='\n')
      { y++; x=0; }

      gotoxy(posX+x,posY+y);
      cprintf("%c",car[i]);
   	x++;
   }
}

void  generateStartScreen()
{
   clrscr();
   textcolor(LIGHTRED+BLINK);
   char carASCII[]="                      __\n                _.--\"\" |\n.----.     _.-'   |/\\| |.--.\n| DR |__.-'   _________|  |_)  _______________  \n|  .-\"\"-.\"\"\"\"\" ___,    `----'\"))   __   .-\"\"-.\"\"\"\"--._  \n'-' ,--. `    |F1 |   .---.       |:.| ' ,--. `      _`.\n ( (    ) ) __|F1 |__ \\\\|// _..--  \\/ ( (    ) )--._\".-.\n  . `--' ;\\__________________..--------. `--' ;--------'\n   `-..-'                               `-..-'";
	printMultiLineStringAtXY(carASCII,33,5);
   textcolor(LIGHTBLUE+BLINK);
   int option=1;
	printMultiLineStringAtXY(" 1. NEW GAME\n2. VIEW HIGH SCORES\n\nEnter Option : ",45,15);
   cin>>option;
   if(option!=1 && option !=2)
   	option=1;

   switch(option)
   {
   	case 2:
      {
      	ifstream f("fileAR.dat",ios::binary);;
         player pla;
         int countY=15;
         printMultiLineStringAtXY("              \n                   \n\n                 ",45,15);
         while(f.read((char *)&pla,sizeof(pla)))
         {
         	gotoxy(48,countY);
            pla.getData();
            countY+=1;
         }

         if(countY==15)
         {  gotoxy(48,15);  cout<<"No scores added"; }

      	getch();
         break;
       }
   	case 1:
         return;
   }
}

int gameMain()
{
	for(int i=1;i<32;i++)
   {
   	gotoxy(25,i);
      cout<<char(178);
      gotoxy(95,i);
      cout<<char(178);
      gotoxy(24,i);
      cout<<char(178);
      gotoxy(96,i);
      cout<<char(178);
   }

   int carWidth=9,carHeight=5;
   string car="  0=[_]=0\n   /T\\\n  |(o)|\n[]=\\_/=[]\n  __V__\n '-----'";
   string carSpaces="         \n      \n         \n         \n       \n         ";
   string enemyCar="   ___\n /___\\\n.\" | \".\n(o_|_o)\n u   u";
   string enemyCarSpaces="      \n      \n       \n       \n        ";
   char dir='a';
  	int currCarX=50,currCarY=25,score=0,speed=0;

   gotoxy(9,15);
   cout<<"Use AWSD";

   randomize();
   gotoxy(48,15);
   cout<<"CLICK ON ANY KEY TO START";
   getch();
   gotoxy(48,15);
   cout<<"                         ";
   int i=1,pox,color;
   while(1)
   {
      while(!kbhit())
      {
         gotoxy(100,13);
         cout<<"Score : "<<score;
         gotoxy(100,15);
         cout<<"Speed : "<<speed<<" km/hr";
         if(i==1)
         {
      		pox=random(51)+35;
         	randomize();
				color=(random(14)+1)+BLINK;
         }
         textcolor(color);
         if(i-5>0)
         	printMultiLineStringAtXY(enemyCarSpaces,pox,i-5);
         printMultiLineStringAtXY(enemyCar,pox,i);

         textcolor(LIGHTRED + BLINK);
         switch(dir)
         {
      		case 'W':
            	if(currCarY-carHeight>1)
               	{printMultiLineStringAtXY(carSpaces,currCarX,currCarY); currCarY-=carHeight; }
               dir='`';
               break;
            case 'S':
            	if(currCarY+2*carHeight<31)
               	{ printMultiLineStringAtXY(carSpaces,currCarX,currCarY);currCarY+=carHeight; }
               dir='`';
               break;
            case 'A':
            	printMultiLineStringAtXY(carSpaces,currCarX,currCarY);
               currCarX-=carWidth;
               dir='`';
               break;
            case 'D':
            	printMultiLineStringAtXY(carSpaces,currCarX,currCarY);
               currCarX+=carWidth;
               dir='`';
               break;
         }
         printMultiLineStringAtXY(car,currCarX,currCarY);
         if(currCarX>=95 || currCarX<=25)
         	return score;

         if((pox>currCarX-4 && pox<currCarX+carWidth+2) && (i>currCarY-2 && i<currCarY+carHeight+2))
         	return score;
         Sleep(175-speed);

         if(i>=30)
         {
         	score++;
         	speed+=5;
         	printMultiLineStringAtXY(enemyCarSpaces,pox,i);
            i=1;
         }
         else
             i+=5;
      }
       dir=toupper(getch());
   }
   return 0;
}

void generateGameOverScreen(int score)
{
  for(int i=5;i<25;i++)
   {
   	gotoxy(25,i);
      cout<<char(178);
      gotoxy(95,i);
      cout<<char(178);
      gotoxy(24,i);
      cout<<char(178);
      gotoxy(96,i);
      cout<<char(178);
   }

  for(int i=25;i<96;i++)
  {
      gotoxy(i,4);
      cout<<char(178);
      gotoxy(i,5);
      cout<<char(178);
      gotoxy(i,24);
      cout<<char(178);
      gotoxy(i,25);
      cout<<char(178);
  }

  string name;

  gotoxy(54,10);
  cout<<"GAME OVER!!";
  gotoxy(30,17);
  cout<<"Your Score : "<<score;
  gotoxy(30,20);

  do
  {
     cout<<"Enter your name : ";
     gets(name);
  }while(strlen(name)==0);

  player user;
  user.setData(name,score);
  ofstream file("fileAR.dat",ios::app | ios::binary);
  file.write((char*)&user,sizeof(user));
  file.close();
  gotoxy(52,27);
  cout<<"Click any key to exit";
}

void main()
{
   system("color f3");
   generateStartScreen();
   clrscr();
   int score=gameMain();
   clrscr();
 	generateGameOverScreen(score);
   getch();
}