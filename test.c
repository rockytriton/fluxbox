#include <X11/Xlib.h>

#include <stdio.h>

int main(int argc, char **argv) {

    Display *d = XOpenDisplay(argv[1]);

    printf("DISP: %X\n", d);

    return 0;

}

