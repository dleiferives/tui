#include <stdio.h>
#include <term.h>
#include <err.h>

int main(void){
        char *cup;
        if(setupterm(0, 1, 0))
                errx(1, "setupterm failed");
        if(!(cup = tigetstr("cup")))
                errx(1, "no cursor addressing in terminal");
        tputs(tigetstr("smcup"), 1, putchar);

        tputs(tiparm(cup, 13, 13), 1, putchar);
        printf("HELLO");        /* or whatever you like */
        getchar();

        tputs(tigetstr("rmcup"), 1, putchar);
}
