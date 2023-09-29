#include <stdio.h>
#include <term.h>
// This is written for linux, bash really. If it does not work for you I am very sorry :(
static const char * AEC = "\33[";

void move_cursor_to(unsigned short x, unsigned short y)
{
	printf("%s%d;%dH",AEC,x+1,y+1);
}
int main()
{
    printf("%s2J", AEC);
    move_cursor_to(0,0);
    for(int i =0;i<1000; i++)
    {
	    putchar('d');
	    putchar('i');
    }
    printf("%s=0h",AEC);


    putchar(10);

    printf("%d\n",);
    return 0;
}

