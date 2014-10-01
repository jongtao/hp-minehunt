/* MINEHUNT
A port of the famous easter egg on the HP-48 Series calculators.

Jonathan Tao.
*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "curses.h"

#define CHK(x) (mines[x/32]&(1<<(x%32)))

const char* title="MINEHUNT";

int main(int argc, char** argv)
{
	short i, j, near, score, posx, posy;
	char key, state;
	uint32_t mines[4], seed;
	memset(mines,0,32);

	posx = posy = 0;
	near = state = 0;
	key = 0;
	score = 1;

	/*Generate*/
	if(argc>1)
	{
		seed = atoi(argv[1]);
		srand(seed);
		printf("Seed:\t%d", seed);
	} /*if a seed is provided*/
	else
	{
		srand((unsigned)(long)&seed);
		printf("Seed:\t%d", (unsigned)(long)&seed);
	} /*else create seed from seed via "random" memory address*/

	for(i=0;i<20;i++)
	{
		do {j=rand()&0X7F;} while(j==0 || j==127 || CHK(j));
		mines[j/32]|=(1<<(j%32));
	} /* 20 mines to place*/

	/* Init ncurses*/
	initscr();
	noecho();
	curs_set(0);

	mvaddch(0,0,ACS_LEQUAL);
	for(i=0;i<8;i++)
		mvaddch(i+2,0,*(title+i));
	mvaddch(10,0,164|A_ALTCHARSET);

	mvaddch(0,21,ACS_GEQUAL);
	for(i=0;i<8;i++)
		mvaddch(i+2,21,*(title+i));
	mvaddch(10,21,164|A_ALTCHARSET);

	mvaddch(1,2,ACS_ULCORNER); mvaddch(1,19,ACS_URCORNER);
	mvaddch(10,2,ACS_LLCORNER); mvaddch(10,19,ACS_LRCORNER);
	mvhline(1,3,ACS_HLINE,16);
	mvhline(10,3,ACS_HLINE,16);
	mvvline(2,2,ACS_VLINE,8);
	mvvline(2,19,ACS_VLINE,8);
	for(i=0;i<8;i++)
		mvhline(i+2,3,' '|A_STANDOUT,16);

	mvaddch(9,18,ACS_CKBOARD);
	mvprintw(0,3,"Near %d",near);
	mvprintw(0,11,"Score %d",score);
	mvaddch(2,3,ACS_DIAMOND);
	refresh();

	while(state==0)
	{
		key=getch();
		mvaddch(posy+2,posx+3,'.');

repoll:
		switch(key)
		{
			case 'h': if(posx!=0) posx--; break;
			case 'j': if(posy!=7) posy++; break;
			case 'k': if(posy!=0) posy--; break;
			case 'l': if(posx!=15) posx++; break;
			case 'y':	if(posx!=0 && posy!=0) {posx--; posy--;} break;
			case 'u':	if(posx!=15 && posy!=0) {posx++; posy--;} break;
			case 'b':	if(posx!=0 && posy!=7) {posx--; posy++;} break;
			case 'n':	if(posx!=15 && posy!=7) {posx++; posy++;} break;
			case 27: state=1; break;
			default:
				mvaddch(posy+2,posx+3,ACS_DIAMOND);
				key = getch();
				goto repoll;
		}; /*switch key*/

		mvaddch(posy+2,posx+3,ACS_DIAMOND);
		score++;

		j = posy*16+posx;
		if(state || mines[j/32]&(1<<(j%32)))
		{
			score--;
			for(i=0;i<128;i++)
				if(CHK(i))
					mvaddch((i/16)+2,(i%16)+3,164|A_ALTCHARSET);
			mvprintw(0,11,"Score %d",score);
			mvprintw(0,3,"YOU BLEW UP!!");
			mvaddch(posy+2,posx+3,'X');
			state=1;
			getch();
		} /*if lose*/
		else
			if(posx==15 && posy==7)
			{
				for(i=0;i<128;i++)
					if(CHK(i))
						mvaddch((i/16)+2,(i%16)+3,164|A_ALTCHARSET);
				mvprintw(0,11,"Score %d",score);
				mvprintw(0,3,"YOU MADE IT!!");
				mvaddch(posy+2,posx+3,'@');
				state=1;
				getch();
			} /*if win*/
			else
			{
				near=0;
				j=(posy-1)*16+(posx-1); /*Upper Left*/
				if(posy!=0 && posx!=0 && CHK(j)) near++;

				j=(posy-1)*16+posx; /*Up*/
				if(posy!=0 && CHK(j)) near++;

				j=(posy-1)*16+(posx+1); /*Upper Right*/
				if(posy!=0 && posx!=15 && CHK(j)) near++;

				j=posy*16+(posx+1); /*Right*/
				if(posx!=15 && CHK(j)) near++;

				j=(posy+1)*16+(posx+1); /*Lower Right*/
				if(posy!=7 && posx!=15 && CHK(j)) near++;

				j=(posy+1)*16+posx; /*Down*/
				if(posy!=7 && CHK(j)) near++;

				j=(posy+1)*16+(posx-1); /*Lower Left*/
				if(posy!=7 && posx!=0 && CHK(j)) near++;

				j=posy*16+(posx-1); /*Left*/
				if(posx!=0 && CHK(j)) near++;

				mvprintw(0,3,"Near %d",near);
				mvprintw(0,11,"Score %d",score);
			} /*else continue play*/
	} /*while continue*/

	endwin();
	printf("\nScore:\t%d\n",score);
	return 0;
} /* main() */
