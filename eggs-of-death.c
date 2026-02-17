// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>  

#include <SDL3/SDL_main.h>

#include <stdio.h>
int WINDOW_WIDTH = 700;
int WINDOW_HEIGHT = 700;
int SNAKE_SIZE = 1;  
int BAD_EGG_SIZE = 0;
enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

void drawSnake(SDL_FRect snake[], SDL_Renderer * renderer, enum Direction dir, int snakeSize) {
  float prev_x = snake[0].x;
  float prev_y = snake[0].y;
  float curr_x;
  float curr_y;
  for (int i = 0; i < snakeSize; i++) {
    
    if (i == 0) {
      if (dir == RIGHT) {
        snake[i].x += 25;
      } else if (dir == LEFT) {
        snake[i].x -= 25;
      } else if (dir == UP) {
        snake[i].y -= 25;
      } else if (dir == DOWN) {
        snake[i].y += 25;
      }
    SDL_SetRenderDrawColor(renderer, 252, 244, 3, 1);
    SDL_RenderRect(renderer, &snake[i]);
    SDL_RenderFillRect(renderer, &snake[i]);
    } else {
      curr_x = snake[i].x;
      curr_y = snake[i].y;
    snake[i].x = prev_x;
    snake[i].y = prev_y;
    SDL_SetRenderDrawColor(renderer, 252, 244, 3, 1);
    SDL_RenderRect(renderer, &snake[i]);
    SDL_RenderFillRect(renderer, &snake[i]);
    prev_x = curr_x;
    prev_y = curr_y;
    }
    
    //SDL_Log("x: %f, y: %f", snake[i].x, snake[i].y);
  }

  
}

int didCollideWithListOfPoints(SDL_FRect point, SDL_FRect pointList[], int listSize) {
  for(int i = 0; i < listSize; i++) {
    if(point.x == pointList[i].x && point.y== pointList[i].y) {
      return 1;
    }
  }
  return 0;
}

int withinCollision(int coord1, int coord2) {
  if((coord1 > coord2 - 40 && coord1 < coord2 + 40) || (coord1 > coord2 + 40 && coord1 < coord2 - 40)) {
    return 1;
  }
  return 0;
}

void spawnGoodEgg(SDL_FRect * goodEgg, SDL_FRect badEggs [], SDL_FRect snake[], int * badEggSize) {

  goodEgg -> x = SDL_rand(WINDOW_WIDTH - 25);
  goodEgg -> y = SDL_rand(WINDOW_HEIGHT - 25);
  for(int i = 0; i <= *badEggSize; i++){
  while((withinCollision(goodEgg -> x, badEggs[i].x) && withinCollision(goodEgg -> y, badEggs[i].y)) || (withinCollision( badEggs[i].x ,goodEgg -> x) && withinCollision(badEggs[i].y , goodEgg -> y))
	|| didCollideWithListOfPoints(*goodEgg, snake, SNAKE_SIZE)) {
    goodEgg -> x = SDL_rand(WINDOW_WIDTH - 25);
    goodEgg -> y = SDL_rand(WINDOW_HEIGHT - 25);
  }}
}

void spawnBadEgg(SDL_FRect badEggs [], SDL_FRect * goodEgg, SDL_FRect snake[], int * badEggSize ) {
  int counter = 0;
  SDL_FRect badEgg = {
    300,
    500,
    25,
    25
  };
  badEgg.x = SDL_rand(WINDOW_WIDTH - 25);
  badEgg.y = SDL_rand(WINDOW_HEIGHT - 25);
  if(counter <= *badEggSize){
  while((withinCollision(goodEgg -> x, badEggs[counter].x) && withinCollision(goodEgg -> y, badEggs[counter].y)) || (withinCollision(badEggs[counter].x , goodEgg -> x) && withinCollision(badEggs[counter].y , goodEgg -> y))
	|| didCollideWithListOfPoints(badEggs[counter], snake, SNAKE_SIZE)) {
    badEgg.x = SDL_rand(WINDOW_WIDTH - 25);
    badEgg.y = SDL_rand(WINDOW_HEIGHT - 25);

  }
  counter++;
  } 
  SDL_Log("Egg size before: %d", *badEggSize);
  badEggs[*badEggSize] = badEgg;
  *badEggSize = *badEggSize + 1;
  SDL_Log("Egg size after: %d", *badEggSize);
  
  
}

void drawGoodEgg(SDL_FRect * goodEgg, SDL_Renderer * renderer) {
  SDL_SetRenderDrawColor(renderer, 3, 36, 252, 1); // this is the color of the squares
  SDL_RenderRect(renderer, goodEgg);
  SDL_RenderFillRect(renderer, goodEgg);
}

void drawBadEggs(SDL_FRect badEggs[], SDL_Renderer * renderer, int badEggSize) {
  for(int i = 0; i <= badEggSize; i++) {
    SDL_SetRenderDrawColor(renderer, 235, 64, 52, 25);
    SDL_RenderRect(renderer, &badEggs[i]);
    SDL_RenderFillRect(renderer, &badEggs[i]);
  }
  
}


int wallDeath(SDL_FRect * snake, SDL_Renderer * renderer) {
  
  if (snake -> x >= WINDOW_WIDTH || snake -> y >= WINDOW_HEIGHT || snake -> x <= 0 || snake -> y <= 0) {
    //SDL_Log("You have died D:\n");
    snake -> x = 500;
    snake -> y = 500;
    return 1;
    
  }
}

void Reset(int *BAD_EGG_SIZE, int *SNAKE_SIZE, SDL_FRect badeggs[]){
  *SNAKE_SIZE = (*SNAKE_SIZE- *SNAKE_SIZE) + 1;  
  *BAD_EGG_SIZE = (*BAD_EGG_SIZE - *BAD_EGG_SIZE); 
  SDL_FRect reseter[1] = {0,0,0,0}; 
  for(int i = 0; i < *BAD_EGG_SIZE; i++){
    badeggs[i] = reseter[0];
  }


}
/*---------------------NEED BAD EGGS TO RESET TO 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int main(int argc, char * argv[]) {
  int SNAKE_LIMIT = 101;
  int BAD_EGG_LIMIT = 10;

  SDL_Window * window; // Declare a pointer
  SDL_Renderer * renderer;
  SDL_FRect badEggs[BAD_EGG_LIMIT];
  SDL_FRect snakeBody[SNAKE_LIMIT];
  SDL_FRect snakeHead = {
    100,
    200,
    25,
    25
  }; // these are the sizes o the squares
  snakeBody[0] = snakeHead;
  SDL_FRect goodEgg = {
    200,
    200,
    25,
    25
  };
  SDL_FRect badEgg = {
    300,
    500,
    25,
    25
  };
  badEggs[0] = badEgg;
  bool done = false;
  enum Direction dir = RIGHT;

  SDL_Init(SDL_INIT_VIDEO); // Initialize SDL3

  
  // Create an application window with the following settings:
  window = SDL_CreateWindow(
    "An SDL3 window", // window title
    WINDOW_WIDTH, // width, in pixels
    WINDOW_HEIGHT, // height, in pixels
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE // flags - see below
  );
  renderer = SDL_CreateRenderer(window, NULL);

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  Uint64 elapsedTime = SDL_GetTicks();
  Uint64 lastTime = 0;
  Uint64 currentTime = 0;
  int frames = 0;
  while (!done) {
    SDL_Event event;

    while (SDL_PollEvent( & event)) {
        
      if (event.type == SDL_EVENT_QUIT) {
        done = true;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        enum Direction block = dir;
        //SDL_Log("THe block is: %d",block);
        //SDL_Log("A key was pressed: %d", event.key.key);

        if (event.key.key == 1073741906) {
          //SDL_Log("Up key was pressed");
           dir = UP;
          if (block == DOWN){
            dir = DOWN;
          }
        }
        if (event.key.key == 1073741905) {
          //SDL_Log("Down key was pressed");    
            dir = DOWN;
            if (block == UP){
            dir = UP;
          }
          
        }
        if (event.key.key == 1073741904) {
          //SDL_Log("Left key was pressed");       
          dir = LEFT;
          if (block == RIGHT){
            dir = RIGHT;
          }
          
        }
        if (event.key.key == 1073741903) {
          //SDL_Log("Right key was pressed");  
          dir = RIGHT;
          if (block == LEFT){
            dir = LEFT;
          }
          
        }

      }
      
    }
    //check for collision
    
    for(int i = 2; i < SNAKE_SIZE; i++){
      if((snakeBody[1].x > snakeBody[i].x - 25 && snakeBody[1].x < snakeBody[i].x + 25) &&(snakeBody[1].y > snakeBody[i].y - 25 && snakeBody[1].y < snakeBody[i].y + 25) ){
        Reset(&BAD_EGG_SIZE , &SNAKE_SIZE, badEggs);
        snakeBody[0].x = 500;
        snakeBody[0].y = 500;
      }

    }

    if ((snakeBody[0].x > goodEgg.x - 30 && snakeBody[0].x < goodEgg.x + 30) && (snakeBody[0].y > goodEgg.y - 30 && snakeBody[0].y < goodEgg.y + 30)) {
      SDL_Log("We hit the egg!");
      if (SNAKE_SIZE < SNAKE_LIMIT) {
        snakeBody[SNAKE_SIZE].x = snakeBody[0].x;
        snakeBody[SNAKE_SIZE].y = snakeBody[0].y;
        snakeBody[SNAKE_SIZE].w = 25;
        snakeBody[SNAKE_SIZE].h = 25;
        SNAKE_SIZE++;
      }
      spawnGoodEgg(&goodEgg, badEggs, snakeBody, &BAD_EGG_SIZE);
      spawnBadEgg(badEggs, &goodEgg, snakeBody, &BAD_EGG_SIZE);
      SDL_Log("Egg size from line 251 %d", BAD_EGG_SIZE);
      

    }
    for(int i = 0; i < BAD_EGG_SIZE; i++){
    if ((snakeBody[0].x > badEggs[i].x - 25 && snakeBody[0].x < badEggs[i].x + 25) && (snakeBody[0].y > badEggs[i].y - 25 && snakeBody[0].y < badEggs[i].y + 25)) {
      //SDL_Log("You have died D:\n");
      goodEgg.x = SDL_rand(611);
      goodEgg.y = SDL_rand(401);
      badEggs[i].x = SDL_rand(500);
      badEggs[i].y = SDL_rand(700);
      // Make a reset snake function
      Reset(&BAD_EGG_SIZE , &SNAKE_SIZE, badEggs);
      snakeBody[0].x = 500;
      snakeBody[0].y = 500;
      // x > 0,  x < 610, y > 0, y < 400

    }}

    if (frames % 10 == 0) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      drawGoodEgg( & goodEgg, renderer);
      drawBadEggs( badEggs, renderer, BAD_EGG_SIZE);
      drawSnake(snakeBody, renderer, dir, SNAKE_SIZE);
      if(wallDeath( & snakeBody[0], renderer) == 1){ 
        Reset(&BAD_EGG_SIZE , &SNAKE_SIZE, badEggs);
      SDL_Log(" Reset!!!!!!!!!!\n");
      SDL_Log(" %d : BAD_EGG_SIZE, %d :  SNAKE_SIZE\n", BAD_EGG_SIZE, SNAKE_SIZE);
    };
      SDL_RenderPresent(renderer);

    }

    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000) {
      lastTime = currentTime;
      //SDL_Log("Frames per second: %d", frames);
      frames = 0;
    }

    frames++;
    // Figure a way to calculate the exact number of milliseconds to delay to achive 60 fps. 
    SDL_Delay(16);
    // Do game logic, present a frame, etc.
  }

  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  // Clean up
  SDL_Quit();
  return 0;
}
