#include "base.h"

void clearmap(){//simply makes it dark
int i = 0, j = 0;
	while(i < MAP_ARRAY_SIZE_X){
		while(j < MAP_ARRAY_SIZE_Y){
		mvaddch(j, i, ' ' );
		j++;
		
		}

	j = 0;
	i++;
}
}








void drawcreature(creature *ent){
	int s = ent->colour;
	static int derp = 0;
	
	init_pair(ent->pairid , s, COLOR_BLACK);
	attron(COLOR_PAIR(ent->pairid));
	mvaddch(ent->y, ent->x, ent->display);
	attroff(COLOR_PAIR(ent->pairid));



}
int collisiontile(creature *one, entity *two){
	if (one->x == two->x && one->y == two->y && two->blocked == true){

	return 1;

	}
	if(one->x == two->x && one->y == two->y && two->stairsdown == true){
	
		return 2;
	
	}
	else{
		return 0;
	}



}
void init(){
	initscr();
	raw();
	
	keypad(stdscr, TRUE);
	start_color();



}

void deinit(){
	refresh();
	endwin();
	exit(0);

}
void takeinp(creature *ent, entity **map, item *itemarray){
	int takeinp;
	entity **tempmap = map;
	item *tempitem = itemarray;
	takeinp = getch();
	int derpcount = 0;
	
	
	switch(takeinp){
		
		case KEY_LEFT:
			mvaddch(ent->y, ent->x, ' ');
			ent->x--;
			break;
		case KEY_RIGHT:
			mvaddch(ent->y, ent->x, ' ');
			ent->x++;
			break;
		case KEY_UP:
			mvaddch(ent->y, ent->x, ' ');
			ent->y--;
			break;
		case KEY_DOWN:
			mvaddch(ent->y, ent->x, ' ');
			ent->y++;
			break;
		case 27:
			deinit();
			break;
		case KEY_A1:
			mvaddch(ent->y, ent->x, ' ');
			ent->x--;
			ent->y--;
			break;
		case KEY_A2:
			mvaddch(ent->y, ent->x, ' ');
			ent->y--;
			break;
		case KEY_A3:
			mvaddch(ent->y, ent->x, ' ');
			ent->x++;
			ent->y--;
			
			break;
		case KEY_B1:
			mvaddch(ent->y, ent->x, ' ');
			ent->x--;
			
			break;
		case KEY_B3:
			mvaddch(ent->y, ent->x, ' ');
			ent->x++;
			
			break;
		case KEY_C1:
			mvaddch(ent->y, ent->x, ' ');
			ent->x--;
			ent->y++;
			
			break;
		case KEY_C2:
			mvaddch(ent->y, ent->x, ' ');
			ent->y++;
		
			break;
		case KEY_C3:
			mvaddch(ent->y, ent->x, ' ');
			ent->x++;
			ent->y++;
			
			break;
		case 62:
			if(collisiontile(ent, &map[ent->x][ent->y]) == 2){
				redefinemap(tempmap,tempitem);
			
			
			}
			break;
		case 'g'://added
			
			while(derpcount < DUNGEON_ITEMS){
				if(collisionitem(ent, &itemarray[derpcount]) == true){
				
					pickupitem(ent, &itemarray[derpcount]);
					
					break;
				}
			
				derpcount++;
			}
		
		break;
		case 'i'://added
		
			inventoryscreen(ent);
			
			break;
		default:
			break;


	}
	
	itemarray = tempitem;
	map = tempmap;



}


entity *drawarray(entity *ent){
	int arraycount = 0;
	entity *returnar = ent;
	
	
	while(arraycount < MAP_ARRAY_SIZE_Y){
		int s = ent->colour;
		init_pair(ent->pairid , s, COLOR_BLACK);
		if(ent->isvisible == true){
			attron(COLOR_PAIR(ent->pairid));
			if (ent->pairid == 4){
		
				attron(A_STANDOUT | A_BOLD);
		
			}	
			mvaddch(ent->y, ent->x, ent->display);
			attroff(COLOR_PAIR(ent->pairid));
			if(ent->pairid == 4){
				attroff(A_STANDOUT | A_BOLD);
		
			}
		}
		arraycount++;
		ent++;
		
	
	
	}
	return returnar;


}

void defineplayer(creature *ent){
		ent->x = 30;
		ent->y = 20;
		ent->display = '@';
		ent->colour = 4;
		ent->pairid = ent->colour;
		ent->combatant = true;
		ent->inventory = malloc(sizeof(item) * 27);
		
		
		
		
}

void definefloor(entity *ent, int x, int y){
	
	static int isstairs = 0;
	static int dungeonlevel = 0;
	static int totalsquares = 0;
	int terraintype = rand() % 100 + 1;
	if(terraintype > 70 && terraintype < 96){
		ent->x = x;
		ent->y = y;
		ent->display = '#';
		ent->colour = 7;
		ent->pairid = ent->colour;
		ent->blocked = true;
		ent->stairsdown = false;
		ent->isvisible = true;
	
	
	}
	else if(terraintype == 99 && isstairs == dungeonlevel){
		ent->x = x;
		ent->y = y;
		ent->display = '>';
		ent->colour = 3;
		ent->pairid = ent->colour;
		ent->blocked = false;
		ent->stairsdown = true;
		ent->isvisible = true;
		isstairs++;
		
	
	}
	else{
		ent->x = x;
		ent->y = y;
		ent->display = '.';
		ent->colour = 7;	
		ent->pairid = ent->colour;
		ent->blocked = false;
		ent->stairsdown = false;
		ent->isvisible = true;
	}
	totalsquares++;
	if(totalsquares == 2000){
		totalsquares = 0;
		dungeonlevel++;
	
	
	}

}
void redefinemap(entity **map, item *items){
	unsigned int i,j,itemdecider,itemcounter;
	i = 0;
	j = 0;
	itemdecider = 0;
	itemcounter = 0;
	while(i < MAP_ARRAY_SIZE_X)
	{
		while(j < MAP_ARRAY_SIZE_Y)
		{
			itemdecider = rand() % 50 + 1;
			definefloor(&map[i][j], i , j);//defines the thing
			
			j++;
		}
		j = 0;
		i++;
		
	}
	i = 0;
	j = 0;
	while(itemcounter < DUNGEON_ITEMS){
		i = rand() % 79 + 1;
		j = rand() % 24 + 1;
		itemdecider = rand() % 5 + 1;
		if(itemdecider == 5 && map[i][j].blocked != true && itemcounter < DUNGEON_ITEMS)
		{
		
			defineitem(&items[itemcounter], i, j);
		
			itemcounter++;
		}
	
	
	}
	



}
int collisionitem(creature *one, item *two){//added
	if(one->x == two->x && one->y == two->y){
		return 1;
	
	
	}
	else{
	
	
	}



}
void inventoryscreen(creature *ent){//added, so unchecked by GCC as are the others
	clearmap();
	int rowno = 5;
	int counter = 1;
	char slotaddress = 'A';
	creature *temp = ent;
	int mover = 0;
	while(rowno < 31){
		if(ent->inventory[counter].x == 0){
				break;
		
		}
		int colour = ent->inventory[counter].colour;
		
		init_pair(colour, colour, COLOR_BLACK);
		mvaddch(rowno, 1 + mover, slotaddress);
		addch(' ');
		attron(COLOR_PAIR(colour));
		addch(ent->inventory[counter].display);
		addstr(ent->inventory[counter].name);
		attroff(COLOR_PAIR(colour));
		
		rowno++;
		counter++;
		slotaddress++;
		if(counter == 27){
			break;
		
		}
		if(rowno > 20){
			mover = 14;
			rowno = 5;
		
		
		}
		
	}
	getch();// this is temporary
	ent = temp;

}






