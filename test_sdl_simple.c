// test_sdl_simple.c
#include <stdio.h>
#include <stdlib.h>
#include "SDL3/SDL.h"

int main(int argc, char *argv[]) {
    printf("=== SDL3 Simple Test ===\n");
    
    // Try with different flags
    printf("\n1. Testing SDL_Init(SDL_INIT_VIDEO)...\n");
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        printf("✅ SUCCESS!\n");
        SDL_Quit();
        return 0;
    }
    printf("❌ Failed: %s\n", SDL_GetError());
    
    printf("\n2. Testing SDL_Init(SDL_INIT_EVENTS)...\n");
    if (SDL_Init(SDL_INIT_EVENTS) == 0) {
        printf("✅ SUCCESS!\n");
        SDL_Quit();
        return 0;
    }
    printf("❌ Failed: %s\n", SDL_GetError());
    
    printf("\n3. Testing SDL_Init(SDL_INIT_AUDIO)...\n");
    if (SDL_Init(SDL_INIT_AUDIO) == 0) {
        printf("✅ SUCCESS!\n");
        SDL_Quit();
        return 0;
    }
    printf("❌ Failed: %s\n", SDL_GetError());
    
    printf("\n4. Testing SDL_Init(0)...\n");
    if (SDL_Init(0) == 0) {
        printf("✅ SUCCESS!\n");
        SDL_Quit();
        return 0;
    }
    printf("❌ Failed: %s\n", SDL_GetError());
    
    return 1;
}