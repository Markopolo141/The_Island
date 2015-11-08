
int cgatoansi(int c) {
    c = c % 16;
    int bright = (c >> 3);
    c = c % 8;
    int ret = c;
    if (c == 1) {
        ret = 4;
    } else if (c == 4) {
        ret = 1;
    }
    if (c == 3) {
        ret = 6;
    } else if (c == 6) {
        ret = 3;
    }
    return ret + bright * 8;
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}
void clrscr() {
    printf("\033[2J");
    gotoxy(1, 1);
}
void delline() {
    printf("\033[K");
}
void savecursorposition() {
    printf("\033[s");
}
void restorecursorposition() {
    printf("\033[u");
}
void screennormalize() {
    printf("\033[m");
}


void cursorup(int x) {
    printf("\033[%dA", x);
}
void cursordown(int x) {
    printf("\033[%dB", x);
}
void cursorforward(int y) {
    printf("\033[%dC", y);
}
void cursorbackward(int y) {
    printf("\033[%dD", y);
}
void cursorhorisontalpos(int x) {
    printf("\033[%dG", x);
}


void textcolor(int color) {
    int fg = cgatoansi(color);
    int bg = cgatoansi(color>>4);
    if (fg > 7) {
        //printf("\033[38;5;%dm", cgatoansi(color)%16);
        //printf("\033[48;5;%dm", cgatoansi(color>>4)%16);
        printf("\033[1;%dm", (fg-8) + 30);
    } else {
        printf("\033[0;%dm", fg + 30);
    }
    printf("\033[%dm", bg + 40);
}




