#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 20
#define HEIGHT 20
#define TILE_SIZE 32
#define MAX_SNAKE_LENGTH 400

int x, y;
int fruitx, fruity;
int score = 0;
int gameover = 0;
int flag = 4; // 1: down, 2: left, 3: up, 4: right
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];
int snakeLength = 1;

void spawnFruit() {
    int valid;
    do {
        fruitx = rand() % HEIGHT;
        fruity = rand() % WIDTH;
        valid = 1;
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == fruitx && snakeY[i] == fruity) {
                valid = 0;
                break;
            }
        }
    } while (!valid);
}

int checkCollisionWithBody(int x, int y) {
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[i] == x && snakeY[i] == y) return 1;
    }
    return 0;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake Byte",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE, 0);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("OpenSans.ttf", 24);
    if (!font) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Color white = {255, 255, 255, 255};

    srand((unsigned int)time(0));

    // Initialize snake start position
    x = HEIGHT / 2;
    y = WIDTH / 2;
    snakeX[0] = x;
    snakeY[0] = y;
    snakeLength = 1;

    spawnFruit();

    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();

    while (!gameover) {
        // Input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) gameover = 1;
            if (event.type == SDL_KEYDOWN) {
                int newFlag = flag;
                switch (event.key.keysym.sym) {
                    case SDLK_f: newFlag = 1; break; // down
                    case SDLK_d: newFlag = 2; break; // left
                    case SDLK_j: newFlag = 3; break; // up
                    case SDLK_k: newFlag = 4; break; // right
                    case SDLK_x: gameover = 1; break;
                }
                // Prevent snake from reversing directly
                if ((flag == 1 && newFlag != 3) ||
                    (flag == 3 && newFlag != 1) ||
                    (flag == 2 && newFlag != 4) ||
                    (flag == 4 && newFlag != 2)) {
                    flag = newFlag;
                }
            }
        }

        // Game logic (every 150ms)
        if (SDL_GetTicks() - lastTick > 150) {
            lastTick = SDL_GetTicks();

            // Move snake body
            for (int i = snakeLength - 1; i > 0; i--) {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }

            // Move snake head
            switch (flag) {
                case 1: x++; break;    // down
                case 2: y--; break;    // left
                case 3: x--; break;    // up
                case 4: y++; break;    // right
            }
            snakeX[0] = x;
            snakeY[0] = y;

            // Check collisions with wall or self
            if (x < 0 || x >= HEIGHT || y < 0 || y >= WIDTH || checkCollisionWithBody(x, y)) {
                gameover = 1;
            }

            // Eating fruit
            if (x == fruitx && y == fruity) {
                score += 5;
                // Add new tail segment at previous tail position
                snakeX[snakeLength] = snakeX[snakeLength - 1];
                snakeY[snakeLength] = snakeY[snakeLength - 1];
                snakeLength++;
                spawnFruit();
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Fruit
        SDL_Rect fruit = {fruity * TILE_SIZE, fruitx * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &fruit);

        // Snake
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int i = 0; i < snakeLength; i++) {
            SDL_Rect body = {snakeY[i] * TILE_SIZE, snakeX[i] * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &body);
        }

        // Score Text
        char scoreText[50];
        sprintf(scoreText, "Score: %d", score);
        SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {10, 10, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    printf("Game Over! Your final score: %d\n", score);
    return 0;
}

