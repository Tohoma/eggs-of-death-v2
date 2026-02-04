// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

    void drawSnake(SDL_FRect* snake, SDL_Renderer* renderer, enum Direction dir) {
          SDL_SetRenderDrawColor(renderer, 252, 244, 3, 1);
          SDL_RenderRect(renderer, snake);
          SDL_RenderFillRect(renderer, snake);
          if(dir == RIGHT) {
            snake-> x += 10;
          } else if (dir == LEFT) {
            snake-> x -= 10;
          } else if (dir == UP) {
            snake-> y -= 10;
          } else if (dir == DOWN){
            snake-> y += 10;
          }
          SDL_Log("x: %f, y: %f", snake-> x, snake-> y);
          }
void drawGoodEgg(SDL_FRect* goodEgg, SDL_Renderer* renderer) {
     SDL_SetRenderDrawColor(renderer, 3, 36, 252, 1); // this is the color of the squares
          SDL_RenderRect(renderer, goodEgg);
          SDL_RenderFillRect(renderer, goodEgg);
}
void drawBadEgg(SDL_FRect* badEgg, SDL_Renderer* renderer) {
     SDL_SetRenderDrawColor(renderer, 235, 64, 52, 25);
          SDL_RenderRect(renderer, badEgg);
          SDL_RenderFillRect(renderer, badEgg);
}

void wallDeath(SDL_FRect* snake, SDL_Renderer* renderer ){

    if(snake -> x >= 2000 || snake -> y >= 1000 || snake -> x <= 0 || snake -> y <= 0 ){
        SDL_Log("You have died D:\n");
        snake -> x = 500;
        snake -> y = 500;
    }
}
int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer *renderer;
    SDL_FRect snake = {100, 200, 25, 25}; // these are the sizes o the squares
    SDL_FRect goodEgg = {200,200, 25, 25};
    SDL_FRect badEgg = {300,500, 25, 25};

    bool done = false;
    enum Direction dir = RIGHT;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        2000,                               // width, in pixels
        1000,                               // height, in pixels
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE                 // flags - see below
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

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
	      SDL_Log("A key was pressed: %d", event.key.key);

	      if(event.key.key == 1073741906) {
		SDL_Log("Up key was pressed");
            dir = UP;
	      }
          if(event.key.key == 1073741905) {
		SDL_Log("Down key was pressed");
            dir = DOWN;
	      }
          if(event.key.key == 1073741904) {
		SDL_Log("Left key was pressed");
            dir = LEFT;
	      }
           if(event.key.key == 1073741903) {
		SDL_Log("Right key was pressed");
            dir = RIGHT;
	      }
           
           
	    }
        }
        //check for collision
        if ((snake.x > goodEgg.x - 25 && snake.x < goodEgg.x + 25) && (snake.y > goodEgg.y - 25 && snake.y < goodEgg.y + 25)){
            SDL_Log("We hit the egg!");
            goodEgg.x = SDL_rand(611);
            goodEgg.y = SDL_rand(401);
            badEgg.x = SDL_rand(500);
            badEgg.y = SDL_rand(700);
            while((badEgg.x > goodEgg.x - 25 && badEgg.x < goodEgg.x + 25) && (badEgg.y > goodEgg.y - 25 && badEgg.y < goodEgg.y + 25)){
            badEgg.x = SDL_rand(500);
            badEgg.y = SDL_rand(700);
            }
            // x > 0,  x < 610, y > 0, y < 400

        }
        if ((snake.x > badEgg.x - 25 && snake.x < badEgg.x + 25) && (snake.y > badEgg.y - 25 && snake.y < badEgg.y + 25)){
            SDL_Log("You have died D:\n");
            goodEgg.x = SDL_rand(611);
            goodEgg.y = SDL_rand(401);
            badEgg.x = SDL_rand(500);
            badEgg.y = SDL_rand(700);
            snake.x = 500;
            snake.y = 500;
            // x > 0,  x < 610, y > 0, y < 400

        }
        
	if (frames %10 == 0) {
	  SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	  SDL_RenderClear(renderer);
      drawGoodEgg(&goodEgg, renderer);
      drawBadEgg(&badEgg, renderer);
	 drawSnake(&snake, renderer, dir);
   wallDeath(&snake, renderer);
     SDL_RenderPresent(renderer);
     
	}
	






	
	currentTime = SDL_GetTicks();
	if (currentTime > lastTime + 1000){
	  lastTime = currentTime;
	  SDL_Log("Frames per second: %d", frames);
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
