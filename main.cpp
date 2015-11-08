#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colors.cpp"

struct room {
	int n, e, s, w;
	char const* description;

	room();
};
room::room() {
	n = 0;
	s = 0;
	e = 0;
	w = 0;
}

struct item {
	int location, has;
	char const* name;

	item();
};
item::item() {
	location = -1;
	has = 0;
}

room island[9];
item inventory[7];
int pos = 0;
int food = 5;
int done = 0;


void printANSI(const char* filename) {
	int a, b, i, length;
	a = 0;
	b = 0;
	length = 65;
	FILE* in;
	in = fopen(filename, "rb");
	if (in == NULL) {
	    printf("ERROR: Cannot open file %s\n", filename);
	    return;
	}
	i = 0;
	a = (int)fgetc(in);
	b = (int)fgetc(in);
	while (a != EOF) {
		textcolor(b);
		printf("%c", (char)a);
		
		a = (int)fgetc(in);
		b = (int)fgetc(in);

		i++;
		if (i >= length) {
			i = 0;
		    textcolor(0);
			printf("\n");
		}
	}
	fclose(in);
}

void displayIntro() {
    printANSI("theisland.bin");
    
    textcolor(9);
    printf("you stand on a beach, your head hurts, you vaguely remember what just happened\n");
    printf("you hear the humm of the engines, the isle empty, bright morning sunshine \n");
    printf("entering through the window.\n");
    printf("you hear some commotion among the flight attendants, you feel the weightless,\n");
    printf("as in an elevator, the engine hum becomes louder, and strained, then powerfully pitched\n");
    printf("then silenced.\n");
    printf("the passengers pierced with fear, quaveringly placing their trust on the pilot\n");
    printf(" 'hey, they're trained for this' you say to yourself\n");
    printf("\n");
    printf("you cant remember much else.\n");
    printf("you look around, and you see the burning wreck of your plane\n");
    printf("you assume the best, and you begin to look for survivors, just as you take your\n");
    printf("first step, your blown back off your feet, and land hard on your back\n");
    printf("you now assume the worst, and despair all hopes of survivors.\n");
    printf("\n");
    printf("\n");
}

void setup() {
    for (int i = 0; i < 6; i++) {
        island[i].s = 1;
    }
    for (int i = 8; i > 2; i--) {
        island[i].n = 1;
    }
    for (int i = 1; i < 3; i++) {
        for (int o = 0; o < 3; o++) {
            island[o*3 + i].w = 1;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int o = 0; o < 3; o++) {
            island[o*3 + i].e = 1;
        }
    }
    island[4].s = 0;
    island[4].e = 0;
    island[5].w = 0;
    island[7].n = 0;
    
    island[0].description = "you stand alongside a plane wreck, ripped apart by devastating force \nthere is ocean to the north and west of you \nthis is where your first memory of the island is\n";
    island[1].description = "you are walking along the sand of the beach you see ocean to the north,\nyou see palm trees to the south of you\n";
    island[2].description = "you walk along coarse beach sand, \nyou see various boulders around you, but they are far to heavy to lift\nthere is ocean to the north and east of you\n";
    island[3].description = "you walk along the beach, there is ocean to the west, and a few palm trees\nto the east.\nthe tide is coming in from the west, and there is a cool breeze running through your hair\n";
    island[4].description = "you see various palm trees, \nyou are upon the highest point of the island, \nand thus you observe you are on on the center of the island\nyou are on top a cliff face facing south and east\n";
    island[5].description = "you stand on rocky beach, there are a few boulders, far to heavy to lift, \nthere is a cliff face to the west, there is ocean to the east\nthe tide is going out to the east, and you see another island out in the ocean\nbut it is far too far to swim\n";
    island[6].description = "you stand on very fine sand there is ocean to the south and west,\nthe tide is coming in from the west\n";
    island[7].description = "you stand on the beach\nthere is pools of sea salt around you, however you want to be hydrated\nthere is ocean to the south of you\nand a cliff face to the north\n";
    island[8].description = "you stand among rock pools, however you look, and there is no fish.\nthere is ocean to the south and east of you\n";

    inventory[0].name = "knife";
    inventory[0].location = 0;
    inventory[1].name = "berries";
    inventory[1].location = 1;
    inventory[2].name = "tin sail";
    inventory[2].location = 2;
    inventory[3].name = "rock";
    inventory[3].location = 3;
    inventory[4].name = "blackberries";
    inventory[4].location = 4;
    inventory[5].name = "vines";
    inventory[5].location = 7;
    inventory[6].name = "wood";
    inventory[6].location = 4;
    
    textcolor(8);
}

void showfood() {
    textcolor(8);
    if (food == 0) {
    	textcolor(12);
        printf("You are deadly hungry!!!\n\n");
    } else if (food == 1) {
    	textcolor(4);
        printf("You are starving!\n\n");
    } else if (food == 2) {
        printf("You are getting very hungry...\n\n");
    } else if (food == 3) {
        printf("You are getting hungry...\n\n");
    }
}

void display() {
    
    textcolor(2);
    printf("\n\n%s\n", island[pos].description);
    showfood();
    textcolor(8);

    printf("Exits:");
    if (island[pos].n == 1)
        printf(" North");
    if (island[pos].e == 1)
        printf(" East");
    if (island[pos].s == 1)
        printf(" South");
    if (island[pos].w == 1)
        printf(" West");
        
    printf("\n");
    
    printf("items:");
    for (int i = 0; i < 7; i++) {
        if ((inventory[i].has == 0) && (inventory[i].location == pos))
            printf(" \'%s\'", inventory[i].name);
    }
    printf("\n");


    //DRAW COMPASS
    savecursorposition();
    cursorup(3);
    cursorhorisontalpos(60);
    
    textcolor(8);
    printf("/ ");
    if (island[pos].n == 1) {
    	textcolor(9);
    } else {
    	textcolor(12);
    }
    printf("N");
    textcolor(8);
    printf(" \\");

    cursorhorisontalpos(60);
    cursordown(1);

    if (island[pos].w == 1) {
    	textcolor(9);
    } else {
    	textcolor(12);
    }
    printf("W");
    textcolor(9);
    printf(" * ");
    if (island[pos].e == 1) {
    	textcolor(9);
    } else {
    	textcolor(12);
    }
    printf("E");

    cursorhorisontalpos(60);
    cursordown(1);

    textcolor(8);
    printf("\\ ");
    if (island[pos].s == 1) {
    	textcolor(9);
    } else {
    	textcolor(12);
    }
    printf("S");
    textcolor(8);
    printf(" /");

    restorecursorposition();

}

void get_one() {
    int singular = 0;
    int index = 0;
    for (int i = 0; i < 7; i++) {
        if ((inventory[i].location == pos) && (inventory[i].has == 0)) {
            singular = singular + 1;
            index = i;
        }
    }
    if (singular == 1) {
        inventory[index].has = 1;
        printf("you have picked up %s\n", inventory[index].name);
    } else if (singular == 0) {
        printf("there is nothing to pick up\n");
    } else {
        printf("there are many things to pick up - which do you mean?\n");
    }
}

void get(char* s) {
    for (int i = 0; i < 7; i++) {
        if ((inventory[i].location == pos) && (inventory[i].has == 0) && (strcmp(s, inventory[i].name) == 0)) {
            inventory[i].has = 1;
            printf("you have picked up %s\n", inventory[i].name);
            return;
        }
    }
    printf("there is no %s to pick up.\n", s);
}

void drop(char* s) {
    int haveit = 0;
    for (int i = 0; i < 7; i++) {
        if ((inventory[i].has == 1) && (strcmp(inventory[i].name, s) == 0)) {
            inventory[i].location = pos;
            inventory[i].has = 0;
            printf("you have dropped %s\n", inventory[i].name);
            haveit = 1;
        }
    }
    if (haveit == 0)
        printf("You cannot drop %s\n", s);
}

void eat(char* s) {
    int has = 0;
    int index = 0;
    for (int i = 0; i < 7; i++) {
        if ((strcmp(inventory[i].name, s) == 0) && (inventory[i].has == 1)) {
            has = 1;
            index = i;
        }
    }
    if (has == 0) {
        printf("you do not have this\n");
    } else if ((strcmp(s, "berries") == 0) || (strcmp(s, "blackberries") == 0)) {
        printf("YUM\n");
        food = food + 5;
        inventory[index].has = 0;
        inventory[index].location = -1;
    } else 
        printf("you cannot eat this\n");
}

void inv() {
    printf("\n-Inventory-\n");
    for (int i = 0; i < 7; i++) {
        if (inventory[i].has == 1)
            printf("%s\n", inventory[i].name);
    }
}

void quitgame() {
    done = 1;
}

int checklocation() {
    if (pos == 5) {
        printf("You have found the correct location\n");
        return 1;
    }
    printf("the surf is to rough to launch any raft here\n");
    return 0;
}

int checkitems() {
    int hasknife = 0;
    int hastinsail = 0;
    int haswood = 0;
    int hasvines = 0;

    for (int i = 0; i < 7; i++) {
        if ((strcmp(inventory[i].name, "knife") == 0) && (inventory[i].has == 1))
            hasknife = 1;
        if ((strcmp(inventory[i].name, "tin sail") == 0) && (inventory[i].has == 1))
            hastinsail = 1;
        if ((strcmp(inventory[i].name, "wood") == 0) && (inventory[i].has == 1))
            haswood = 1;
        if ((strcmp(inventory[i].name, "vines") == 0) && (inventory[i].has == 1))
            hasvines = 1;
    }
    if ((hasknife == 1) && (hastinsail == 1) && (haswood == 1) && (hasvines == 1)) {
        printf("You have found all of the items\n");
        return 1;
    }
    if (hasknife == 0)
        printf("You need the knife\n");
    if (hastinsail == 0)
        printf("You need the tin sail\n");
    if (haswood == 0)
        printf("You need the wood\n");
    if (hasvines == 0)
        printf("You need the vines\n");
    return 0;
}

void makeraft() {
    if ((checkitems() == 1) && (checklocation() == 1)) {
        printf("Congratulations, you have made it off the island\n");
        printANSI("end.bin");
        done = 1;
    }
}

void commandhelp() {
	textcolor(11);
    printf("\n");
    printf("-Commands-\n");
    printf("\n");
    printf("n or 8 = Move North\n");
    printf("s or 2 = Move South\n");
    printf("e or 6 = Move East\n");
    printf("w or 4 = Move West\n");
    printf("inv = Display Inventory\n");
    printf("get <item[optional]> = Pick up that item\n");
    printf("eat <item> = Eat that item\n");
    printf("drop <item> = drop that item on current board\n");
    printf("make raft = if on correct board make the raft\n");
    printf("quit = exit the program\n");
}


void checkfood() {
    if (food == -1) {
        printANSI("death.bin");
        textcolor(12);
        printf("You have starved to death!\n");
        done = 1;
    }
}

void checkinput() {
    int repeat = 1;
    char temp[40];
    while (repeat == 1) {
        textcolor(7);
        printf("\n: ");
        if (fgets(temp, 39, stdin) == NULL) {
            printf("error reading console input, please type 'help' for commands or 'quit' to exit");
            repeat = 1;
        } else {
            if (strlen(temp) > 0)
                temp[strlen(temp)-1] = (char)0;
            if ((strcmp(temp, "n") == 0) || (strcmp(temp, "8") == 0)) {
                if (island[pos].n == 1) {
                    pos = pos - 3;
                    food = food - 1;
                    repeat = 0;
                } else {
                    printf("You cannot move North\n");
                }
            } else if ((strcmp(temp, "s") == 0) || (strcmp(temp, "2") == 0)) {
                if (island[pos].s == 1) {
                    pos = pos + 3;
                    food = food - 1;
                    repeat = 0;
                } else {
                    printf("You cannot move South\n");
                }
            } else if ((strcmp(temp, "e") == 0) || (strcmp(temp, "6") == 0)) {
                if (island[pos].e == 1) {
                    pos = pos + 1;
                    food = food - 1;
                    repeat = 0;
                } else {
                    printf("You cannot move East\n");
                }
            } else if ((strcmp(temp, "w") == 0) || (strcmp(temp, "4") == 0)) {
                if (island[pos].w == 1) {
                    pos = pos - 1;
                    food = food - 1;
                    repeat = 0;
                } else {
                    printf("You cannot move West\n");
                }
            } else if (strncmp(temp, "eat ", 4) == 0) {
                eat((char*)(temp + 4));
            } else if (strcmp(temp, "get") == 0) {
                get_one();
            } else if (strncmp(temp, "get ", 4) == 0) {
                get((char*)(temp + 4));
            } else if (strcmp(temp, "quit") == 0) {
                repeat = 0;
                quitgame();
            } else if (strncmp(temp, "drop ", 5) == 0) {
                drop((char*)(temp + 5));
            } else if (strcmp(temp, "inv") == 0) {
                inv();
            } else if (strcmp(temp, "make raft") == 0) {
                makeraft();
            } else if (strcmp(temp, "help") == 0) {
                commandhelp();
            } else {
                printf("I do not understand you, type \'help\' if you need it.\n");
            }
        }
        if (done == 1) {
            repeat = 0;
        }
    }
    checkfood();
}

int main() {
    clrscr();
	setup();
	displayIntro();
	while (done == 0) {
		display();
		checkinput();
	}
	textcolor(7);
	return 0;
}

