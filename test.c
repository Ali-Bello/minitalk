#include <stdio.h>

// ANSI escape codes for text formatting
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
#define UNDERLINE "\x1b[4m"

int main() {
    printf(RED "This text is red.\n" RESET);
    printf(GREEN "This text is green.\n" RESET);
    printf(YELLOW "This text is yellow.\n" RESET);
    printf(BLUE "This text is blue.\n" RESET);
    printf(MAGENTA "This text is magenta.\n" RESET);
    printf(CYAN "This text is cyan.\n" RESET);
    printf(BOLD RED"This text is bold.\n" RESET);
    printf(UNDERLINE "This text is underlined.\n" RESET);
    printf("This text is default color.\n");

    return 0;
}
