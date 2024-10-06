#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Init(SDL_INIT_VIDEO);

  if (TTF_Init() == -1) {
    printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
    SDL_Quit();
    return 1;
  }
  SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
  TTF_Font *font = TTF_OpenFont(
      "/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 24);
  if (!font) {
    printf("Failed to find font! TTF Error: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }
  SDL_Color textColor = {255, 255, 255, 255};
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font, "Hello world!", textColor);
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  // Main loop
  int running = 1;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Draw the text in the first column and row
    SDL_Rect dstRect = {50, 50, 0, 0}; // Position (50, 50)
    SDL_QueryTexture(textTexture, NULL, NULL, &dstRect.w,
                     &dstRect.h); // Get the width and height of the texture
    SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);

    // Present the renderer
    SDL_RenderPresent(renderer);
  }

  // Clean up
  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  SDL_Delay(5000);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
