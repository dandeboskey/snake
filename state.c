#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  struct game_state_t *game_state = malloc(sizeof(game_state_t));
  struct snake_t *snake = malloc(sizeof(snake_t));

  game_state->num_rows = 18;
  game_state->num_snakes = 1;
  game_state->board = malloc(sizeof(char*) * game_state->num_rows);
  game_state->snakes = malloc(sizeof(snake_t) * game_state->num_snakes);

  snake->tail_row = 2;
  snake->tail_col = 2;
  snake->head_row = 2;
  snake->head_col = 4;
  snake->live = true;
  game_state->snakes[0] = *snake;

  int i;
  for (i = 0; i < game_state->num_rows; i++) {
    game_state->board[i] = malloc(sizeof(char)*21);
    if (i != 0 || i != 2 || i != (game_state->num_rows - 1)) {
      strcpy(game_state->board[i], "#                  #");
    }
  }
  strcpy(game_state->board[0], "####################");
  strcpy(game_state->board[game_state->num_rows - 1], "####################");
  strcpy(game_state->board[2], "# d>D    *         #");
  free(snake);
  return game_state;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  int i;
  for (i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);
  free(state->snakes);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  int i;
  for (i = 0; i < state->num_rows; i++) {
    fprintf(fp, "%s\n", state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c == 'a' || c == 'w' || c == 's' || c == 'd') {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c == 'A' || c == 'W' || c == 'S' || c == 'D'|| c == 'x') {
    return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if (c == 'A' || c == 'W' || c == 'S' || c == 'D'|| c == 'x') {
    return true;
  } if (c == 'a' || c == 'w' || c == 's' || c == 'd') {
    return true;
  } if (c == '^' || c == '<' || c == 'v' || c == '>') {
    return true;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  if (c == '^') { return 'w';}
  if (c == '<') { return 'a';} 
  if (c == 'v') { return 's';}
  if (c == '>') { return 'd';}
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  if (c == 'W') { return '^';}
  if (c == 'A') { return '<';} 
  if (c == 'S') { return 'v';}
  if (c == 'D') { return '>';}
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (c == 'v' || c == 's' || c == 'S') { return cur_row + 1;}
  if (c == '^' || c == 'w' || c == 'W') { return cur_row - 1;}
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c == '>' || c == 'd' || c == 'D') { return cur_col + 1;}
  if (c == '<' || c == 'a' || c == 'A') { return cur_col - 1;}
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  struct snake_t snake = state->snakes[snum]; 
  unsigned int row = snake.head_row;
  unsigned int col = snake.head_col;
  char headVal = get_board_at(state, row, col);
  unsigned int newrow = get_next_row(row, headVal);
  unsigned int newcol = get_next_col(col, headVal);
  return get_board_at(state, newrow, newcol);
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  struct snake_t snake = state->snakes[snum];
  unsigned int row = snake.head_row;
  unsigned int col = snake.head_col;
  char headVal = get_board_at(state, row, col);
  unsigned int newrow = get_next_row(row, headVal);
  unsigned int newcol = get_next_col(col, headVal);
  set_board_at(state, newrow, newcol, headVal);
  set_board_at(state, row, col, head_to_body(headVal));
  snake.head_row = newrow;
  snake.head_col = newcol;
  state->snakes[snum] = snake;
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  struct snake_t snake = state->snakes[snum];
  unsigned int row = snake.tail_row;
  unsigned int col = snake.tail_col;
  char tailVal = get_board_at(state, row, col);
  unsigned int newrow = get_next_row(row, tailVal);
  unsigned int newcol = get_next_col(col, tailVal);
  char newTail = get_board_at(state, newrow, newcol);
  set_board_at(state, newrow, newcol, body_to_tail(newTail));
  set_board_at(state, row, col, ' ');
  snake.tail_row = newrow;
  snake.tail_col = newcol;
  state->snakes[snum] = snake;
  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  unsigned int i;
  for (i = 0; i < state->num_snakes; i++) {
    struct snake_t snake = state->snakes[i];
    unsigned int row = snake.head_row;
    unsigned int col = snake.head_col;
    char headVal = get_board_at(state, row, col);
    unsigned int newrow = get_next_row(row, headVal);
    unsigned int newcol = get_next_col(col, headVal);
    char nextTile = get_board_at(state, newrow, newcol);
    if ((is_snake(nextTile) && !(is_tail(nextTile) || is_head(nextTile))) || nextTile == '#') {
      set_board_at(state, row, col, 'x');  
      snake.live = false;
      state->snakes[i] = snake;
    } if (nextTile == '*') {
      update_head(state, i);
      add_food(state);
    } if (nextTile == ' ') {
      update_head(state, i);
      update_tail(state, i);
    }
  }
  return;
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  struct game_state_t *game_state = malloc(sizeof(game_state_t));

  FILE * input = fopen(filename, "r");

  char * line = NULL;
  size_t len = 0;
  size_t read;

  game_state->num_rows = 0;
  game_state->board = malloc(sizeof(char*));
  /* fgets() */
  while ((read = getline(&line, &len, input)) != -1) { 
    game_state->board = realloc(game_state->board, (game_state->num_rows + 1) * sizeof(char*));
    game_state->board[game_state->num_rows] = malloc(sizeof(char)*(strlen(line)));
    line[strcspn(line, "\n")] = 0;
    strcpy(game_state->board[(game_state->num_rows)], line);
    game_state->num_rows++;
  }

  fclose(input);
  
  return game_state;

}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  struct snake_t snake = state->snakes[snum];
  unsigned int row = snake.tail_row;
  unsigned int col = snake.tail_col;
  unsigned int a; 
  unsigned int b;
  while (!is_head(get_board_at(state, row, col))) {
    a = get_next_row(row, get_board_at(state, row, col));
    b = get_next_col(col, get_board_at(state, row, col));
    row = a;
    col = b;
  }
  snake.head_row = row;
  snake.head_col = col;
  state->snakes[snum] = snake;
  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  unsigned int i, j, k;
  k = 0;
  char * s;
  state->num_snakes = 0;
  state->snakes = malloc(sizeof(snake_t) * k);
  for (i = 0; i < state->num_rows; i++) {
    s = state->board[i];
    for (j = 0; j < strlen(s); j++) {
      if (is_tail(get_board_at(state, i, j))) {

        k++;

        state->snakes = realloc(state->snakes, k * sizeof(snake_t));
        struct snake_t *snake = malloc(sizeof(snake_t));

        snake->tail_row = i;
        snake->tail_col = j;
        snake->head_row = 0;
        snake->head_col = 0;
        snake->live = true;
        state->num_snakes++;
        state->snakes[k-1] = *snake;

        find_head(state, (k - 1));
        free(snake);
      }
    }
  }
  return state;
}
