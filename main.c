#include <stdio.h>
#include <term.h>
#include <stdlib.h>
// This is written for linux, bash really. If it does not work for you I am very sorry

typedef struct{
	int width;
	int height;
	char * buffer;
	char * rep_buffer;
	char * cu;
}Terminal_t;

Terminal_t Terminal_t_init(void)
{
	Terminal_t result;
	result.width = 0;
	result.height =0;
	result.buffer = NULL;
	result.rep_buffer =NULL;
	result.cu = NULL;
	return result;
}

void Terminal_t_create(Terminal_t * t)
{
	if(setupterm(0, 1, 0))
	{
		fprintf(stderr, "setupterm failed");
		exit(1);
	}
	if(!(t->cu = tigetstr("cup")))
	{
		fprintf(stderr, "no cursor addressing in terminal");
		exit(1);
	}
	tputs(tigetstr("smcup"), 1, putchar);
	t->width = tigetnum((char *)"cols");
	t->height = tigetnum((char *)"lines");
	if ((t->width < 1) || (t->height < 1))
	{
		fprintf(stderr, "could not read the size of terminal");
		exit(1);
	}
	tputs(tiparm(tigetstr("civis")), 1, putchar);
}

void Terminal_t_destroy(Terminal_t * t)
{
	tputs(tigetstr("rmcup"), 1, putchar);
	tputs(tiparm(tigetstr("cnorm")), 1, putchar);
}

void Terminal_t_move_cursor(Terminal_t *t, unsigned short x, unsigned y)
{
	tputs(tiparm(t->cu, y, x), 1, putchar);
}

void Terminal_t_repeat_char(Terminal_t *t,char c, int n)
{
	tputs(tiparm(tigetstr("rep"),c,n), 1, putchar);
}

void Terminal_t_delete_lines(Terminal_t *t,int n)
{
	tputs(tiparm(tigetstr("dl"),n),1,putchar);
}


int main()
{
	Terminal_t t = Terminal_t_init();
	Terminal_t_create(&t);
	getchar();
	Terminal_t_destroy(&t);

     
    return 0;
}

