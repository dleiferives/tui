// Little library to help me make teminal based applications.
// Dylan Leifer-Ives 9-28-2023
// It uses the term.h, which uses terminfo, which uses the ncurses library
// TODO: reimplement functions using ascii escape sequences. 
// TODO: stop depending on ncurses and get the information right out of the tty/ ssh connection
// TODO: handle errors if they occur

#include <stdio.h>
#include <term.h>
#include <stdlib.h>

#ifndef dleiferives_tui
#define dleiferives_tui

// The terminal struct that is the basis of the tui library
// width is the terminal width
// height is the terminal height
// buffer and rep_buffer are not yet implemented.
// they will be switched. And used for computing minimum character change.
typedef struct{
	int width;
	int height;
	char * buffer;
	char * rep_buffer;
	char * cu;
}Terminal_t;

// Initilizes a zeroed terminal
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

// sets up a terminal
void Terminal_t_create(Terminal_t * t)
{
	// sets up the terminal
	if(setupterm(0, 1, 0))
	{
		fprintf(stderr, "setupterm failed");
		exit(1);
	}
	// sets the cursor up
	if(!(t->cu = tigetstr("cup")))
	{
		fprintf(stderr, "no cursor addressing in terminal");
		exit(1);
	}
	// sets the screen cursor up
	tputs(tigetstr("smcup"), 1, putchar);
	// fills in the width and height
	t->width = tigetnum((char *)"cols");
	t->height = tigetnum((char *)"lines");

	// if there is no good data from one or both. just dont do anything
	if ((t->width < 1) || (t->height < 1))
	{
		fprintf(stderr, "could not read the size of terminal");
		exit(1);
	}
}

// closes the terminal, resets the cursor by force
void Terminal_t_destroy()
{
	tputs(tigetstr("rmcup"), 1, putchar);
	tputs(tiparm(tigetstr("cnorm")), 1, putchar);
}

// makes the cursor invisible
void Terminal_t_cursor_invis(void)
{
	tputs(tiparm(tigetstr("civis")),1,putchar);
}

// moves the cursor to some x y
void Terminal_t_move_cursor(Terminal_t *t, unsigned short x, unsigned y)
{
	tputs(tiparm(t->cu, y, x), 1, putchar);
}

// repeats a character n times
void Terminal_t_repeat_char(Terminal_t *t,char c, int n)
{
	tputs(tiparm(tigetstr("rep"),c,n), 1, putchar);
}

// deletes n lines -- not really working right now
void Terminal_t_delete_lines(Terminal_t *t,int n)
{
	tputs(tiparm(tigetstr("dl"),n),1,putchar);
}

// clears to the screens end. this means the entire screen gets cleared
void Terminal_t_clear_to_screen_end(Terminal_t *t)
{
	tputs(tiparm(tigetstr("ed")),1,putchar);
}

// clears to the end of the line. from the cursor to the end.
void Terminal_t_clear_to_l_end(Terminal_t *t)
{
	tputs(tiparm(tigetstr("el")),1,putchar);
}
#endif
