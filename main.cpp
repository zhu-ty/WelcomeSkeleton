#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include"colormod.h"
using namespace std;

void move(int s, char d)
{
    printf("\033[%d%c",s,d);
    fflush(stdout);
}


void draw2(int co = 0)
{
    //Color::Modifier green(Color::FG_GREEN);
    Color::Modifier c((co == 0) ? Color::FG_WHITE : Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    //cout<<blue<<"K"<<def;
    cout<<c;
    printf("  ########  ");
    move(12,'D');
    move(1,'B');
    printf(" ##      ## ");
    move(12,'D');
    move(1,'B');
    printf("##        ##");
    move(12,'D');
    move(1,'B');
    printf("#          #");
    move(12,'D');
    move(1,'B');
    printf("#          #");
    move(12,'D');
    move(1,'B');
    printf("###   ##   #");
    move(12,'D');
    move(1,'B');
    printf("### # ##   #");
    move(12,'D');
    move(1,'B');
    printf("#         ##");
    move(12,'D');
    move(1,'B');
    printf("##      ####");
    move(12,'D');
    move(1,'B');
    printf(" # # #  ##  ");
    move(12,'D');
    move(1,'B');
    printf(" #########  ");
    move(12,'D');
    move(10,'A');
    fflush(stdout);
    move(1,'D');
    cout<<def;
}


void draw_at(int x, int y, int c = 0)
{
   // for(int i = 0;i < y;i++)
   //     printf("\n");
    move(x,'C');
    move(y,'B');

    draw2(c);
    
    move(x,'D');
    move(y,'A');
}


int main()
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier white(Color::FG_WHITE);
    //cout << "This ->" << red << "word" << def << "<- is red." << endl;
    //cout << "HelloWorld" << endl;
    //printf("HelloWorld\nhaha");
    //fflush(stdout);
    //sleep(1);
    //cout << "\033[A\r" << red << "come on" << def << endl;
    int lines = 12;
    for(int k = 0;k < 2;k++)
    {
        //int lines = 12;
        for(int i = 0;i < lines;i++)
            printf("\n");
        move(lines,'A');
        for(int i = 0;i < 4;i++)
            draw_at(i*13+1,1,(k+i)%2);
        move(lines+1,'B');
    }
    sleep(1);
    //move(lines,'A');
    //cout<<"                "<<white<<"Welcome to SK system"<<def;
    //move(lines,'B');
    //cout<<endl;
    //sleep(1);
    cout<<"Initializing"<<endl;
    move(2*lines+1,'A');
    cout<<red;
    for(int i = 0;i < 13 * 2; i++)
    {
        for(int j = 0;j < 13 * 4; j++)
        {
            printf("*");
            fflush(stdout);
            usleep(5000);
        }
        printf("\r");
        move(1,'B');
    }
    cout<<def;
    cout<<endl<<"done!"<<endl;;
    sleep(1);
    move(lines,'A');
    cout<<red<<"****************"<<white<<"Welcome to SK system"<<def;
    move(lines-1,'B');
    cout<<endl;
    return 0;
}




/*
up vote
12
down vote
Some worthwhile subtleties...

\33[2K erases the entire line your cursor is currently on

\033[A moves your cursor up one line, but in the same column i.e. not to the start of the line

\r brings your cursor to the beginning of the line (r is for rewind) but does not erase anything

In xterm specifically, I tried the replies mentioned above and the only way I found to erase the line and start again at the beginning is the sequence (from the comment above posted by @Stephan202 as well as @vlp and @mantal) \33[2K\r

On an implementation note, to get it to work properly for example in a countdown scenario since I wasn't using a new line character '\n' at the end of each fprintf(), so I had to fflush() the stream each time (to give you some context, I started xterm using a fork on a linux machine without redirecting stdout, I was just writing to the buffered FILE pointer fdfile with a non-blocking file descriptor I had sitting on the pseudo terminal address which in my case was /dev/pts/21):

fprintf(fdfile, "\33[2K\rT minus %d seconds...", i);
fflush(fdfile);
Note that I used both the \33[2K sequence to erase the line followed by the \r rewind sequence to reposition the cursor at the beginning of the line. I had to fflush() after each fprintf() because I don't have a new line character at the end '\n'. The same result without needing fflush() would require the additional sequence to go up a line:

fprintf(fdfile, "\033[A\33[2K\rT minus %d seconds...\n", i);
Note that if you have something on the line immediately above the line you want to write on, it will get over-written with the first fprintf(). You would have to leave an extra line above to allow for the first movement up one line:

i = 3;
fprintf(fdfile, "\nText to keep\n");
fprintf(fdfile, "Text to erase****************************\n");
while(i > 0) { // 3 second countdown
    fprintf(fdfile, "\033[A\33[2KT\rT minus %d seconds...\n", i);
    i--;
    sleep(1);
}

Position the Cursor: \033[;H Or \033[L;Cf puts the cursor at line L and column C.
Move the cursor up N lines: \033[NA
Move the cursor down N lines: \033[NB
Move the cursor forward N columns: \033[NC
Move the cursor backward N columns: \033[ND
Clear the screen, move to (0,0): \033[2J
Erase to end of line: \033[K
Save cursor position: \033[s
Restore cursor position: \033[u
*/
