#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h> 

#include "backend.h"
#define ZA_MALO_PAMIECI -1
 //gcc nazwa.c -lncurses = .bashrc
/*Plan;
 */
int score = 0;
bool quit = false;
bool is_food=false;
// void show_snake();

void show_frame(){
  int lenx = 55, leny=20;
  for (int x=1; x<lenx+1 ; x++)
    mvaddstr(1, x, "#");
  for (int x=lenx; x>0 ; x--)
    mvaddstr(leny, x, "#");
  for (int y=leny;y>1; y--)
    mvaddstr(y, 1, "##");
  for (int y=1;y<leny; y++)
    mvaddstr(y, lenx, "##");
}

void show_score(){
  char s = score+'0';
  move(1, 8);
  addch(s);
  mvaddstr( 1, 1, "Score:");
    
}

 //gcc nazwa.c -lncurses = .bashrc


typedef struct food{
  int x;
  int y;
  struct food *next;
}Food;
Food *korzen = NULL;

// typedef enum{
//   RIGHT, LEFT, UP, DOWN
// }dir;
// dir last_dir = RIGHT;

Food *nowyFood(int x, int y){
  Food *nowy; 
  
  if( (nowy = (Food*)malloc(sizeof(Food))) == NULL ) {
    fprintf(stderr, "Memory error!\n");
    exit(ZA_MALO_PAMIECI);
  }
  nowy->x = x;
  nowy->y = y;
  nowy->next=NULL;
  // mvaddstr(nowy->x,nowy->y, "*");
  return nowy;
}

Food *now_food=NULL;
Food *add_food(){//create_cell(rand() % xmax, rand() % ymax);
  //Food *nowy = (*Food)malloc(sizeof(Food));
  Food *new;
  int r1 = getRandom(19);
  int r2 = getRandom(39);
  if (korzen==NULL){
    new = nowyFood(r1,r2);}
  else{
    new->x =r1;
    new->y =r2;}
  mvaddstr(new->x,new->y, "$");
  return new;
}

// Food *now_food = korzen;


// void snake_move(int x, int y){
//   mvaddstr(x, y, "s");
//   for(int i=0; i<score; i++){
//      int temp = x - i - 1;
//      mvaddstr(temp, y, "o");
//   }}

void check_move(){
  // pushFirst(head->x,head->y);
  // pushEnd()
  switch(last_dir){
    case UP:
        head->y--; // dodac zeby sprawdzalo czy dotykasz ogona
        break;
    case RIGHT:
        head->x++;
        break;
    case DOWN:
        head->y++;
        break;
    case LEFT:  
        head->x--;
        break;
    default:
      break;
  }
}



//-----------------------------------

int main(void) 
{
  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW * mainwin=newwin(10,xMax-2, yMax-2, 5);
  // box(mainwin, 0,0);
  // Initializacja ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  noecho();     // nie pokazuj wpisywanych danych
  cbreak();     // disables line buffering and erase/kill character-processing
  timeout(500); // wait 500ms for key press


  //keypad(stdscr, true); // make keys work
  curs_set(0); // hide cursor

  refresh();
  // wrefresh(mainwin);
  keypad(mainwin, true); 

  
  int x=10, y=5;


  
  // mvaddstr(10, 0, "s");
  // head = (Move*)malloc(sizeof(Move));
  // head->next = NULL;
  // head->prev = NULL;
  // head -> x = 10;
  // head -> y = 10;

  // pushEnd(x, y);
  pushFirst(x, y);

  // mvaddstr(head->y, head->x, "@");

  do {

      // int c = wgetch(mainwin);
      int c = getch();

      switch (c) 
      {
        case 'q':
          quit = true;
          break;
        case KEY_UP:
          if (last_dir != UP )
            x--;
          last_dir=UP;
          break;
        case KEY_DOWN:
          x++;
          last_dir=DOWN;
          break;  
        case KEY_LEFT:
          y--;
          last_dir=LEFT;
          break;
        case KEY_RIGHT:
          y++;
          last_dir=RIGHT;
          break;

        default:
          if (last_dir==RIGHT)
            y++;
          else if(last_dir==UP)
            x--;
          else if(last_dir==LEFT)
            y--;
          else if(last_dir==DOWN)
            x++;
          break;
      }

      Food* newf;
      if(is_food && y==newf->y && x==newf->x ){
        is_food=false;
        score++;
        // pushEnd(x, y); //new
      }else{
        mvaddstr(tail->x, tail->y, " ");
        popTail();
      }
      // clear();
      show_frame();
      show_score();
      pushFirst(x, y);

      mvaddstr(head->x,head->y, "S");

      for(int i=0; i<score; i++){
        mvaddstr(head->next->x ,head->next->y, "o");
      }

      
      
      if(is_food == false){
        newf = add_food();
        is_food = true;
      }else{
        mvaddstr(newf->x,newf->y, "$");
      }

      refresh();

  } while( !quit );
  clear();
  
  quit = false;

  char *choices[]={ "Score:", "Again? press a","If You want to quit press q"};
  do{
    int c = wgetch(mainwin);
      switch (c) 
      {
        case 'q':
          quit = true;
          break;
        case 'a':
          main();
          break;
      }

    mvaddstr( 1, 1, choices[0]);
    move( 1, 8);
    char temps= score+'0';
    addch(temps);

    for(int i=1;i<3;i++){

      //wattron(mainwin, A_REVERSE)
      mvaddstr( i+1, 1, choices[i]);
    }
    refresh();
  } while(!quit);




  // Czyszczenie
  nocbreak();
  echo();
  refresh();
  delwin(mainwin);
  endwin();
  return EXIT_SUCCESS;
}
