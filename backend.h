#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
// #include <ncurses.h>
#define memExit -1

int  getRandom(int max){
  static int r;
  int i;
  time_t t;
  int lower =3;
  srand((unsigned) time(&t));
  // r = rand()%max;
  r = (rand() % (max - lower + 1)) + lower;
  return r; 
}

typedef enum{
  RIGHT, LEFT, UP, DOWN
}dir;
dir last_dir = RIGHT;



//dlugosc snakea
typedef struct move{
  int x;
  int y;
  struct move *next;
  struct move *prev;
}Move;
Move *head = NULL;
Move *tail = NULL;

// void pushEnd(int x, int y) {

//   Move* element;

//   if( (element = (Move*)malloc(sizeof(Move))) == NULL ) {
//     fprintf(stderr, "To small memory\n");
//      exit(memExit);
//   }
//     element->x = x;
//     element->y = y;
//     if (head == NULL){
//         element->next = head;
//         element->prev = tail;
//         head = element;
//         tail = element;
//         return;

//     }
//     element -> next = head;
//     element->prev = tail;
//     tail->next = element;
//     head->prev = element;
//     tail = element;

// }

void pushFirst(int x, int y) {

  Move* element;

  if( (element = (Move*)malloc(sizeof(Move))) == NULL ) {
    fprintf(stderr, "Memory error\n");
    exit(memExit);
  }
    element->x = x;
    element->y = y;
    if (head == NULL){
        element->next = head;
        element->prev = tail;
        head = element;
        tail = element;
        return;
    }
    element -> next = head;
    element->prev = tail;
    tail->next = element;
    head->prev = element;
    head = element;
}

int popTail(){
  int defaultVaule = -1;

  if(head == NULL || tail == NULL){
    return defaultVaule;
  }

  if(head==tail)
  {
        head = NULL;
        tail = NULL;
        return -1;
  }

  head->prev = tail->prev;
  tail->prev->next = head;
  free(tail);
  tail = head->prev;
  return -1;


}