#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <libdragon.h>

// Screen dimensions inside Libdragon's text console
#define MAP_WIDTH 60
#define MAP_HEIGHT 20

int main(void)
{
    /* Initialize N64 core hardware systems */
    dfs_init(DFS_DEFAULT_LOCATION);
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    
    // Joypad subsystem handles Delta controller inputs smoothly
    joypad_init();

    // Spawn text console for crisp 60fps rendering without requiring external textures
    console_init();
    console_set_render_mode(RENDER_MANUAL);

    // Initial game variables
    int player_x = 10;
    int player_y = 10;
    int food_x = 25;
    int food_y = 5;
    int score = 0;

    /* Infinite loop running the engine */
    while(1) 
    {
        // Poll for fresh framework events and hardware input
        joypad_poll();
        
        // Grab inputs assigned to port 0 (Player 1)
        joypad_inputs_t input = joypad_get_inputs(JOYPAD_PORT_1);
        joypad_buttons_t pressed = input.btn;

        // D-Pad navigation controls
        if (pressed.d_left  && player_x > 0)              player_x--;
        if (pressed.d_right && player_x < MAP_WIDTH - 1)  player_x++;
        if (pressed.d_up    && player_y > 0)              player_y--;
        if (pressed.d_down  && player_y < MAP_HEIGHT - 1) player_y++;

        // Reset game state if user taps the 'Start' button
        if (pressed.start) {
            score = 0;
            player_x = 10;
            player_y = 10;
        }

        // Collision detection logic (When Player 'X' touches Food 'o')
        if (player_x == food_x && player_y == food_y) {
            score += 10;
            
            // Relocate target food across the text field pseudo-randomly
            food_x = (food_x * 7 + 13) % MAP_WIDTH;
            food_y = (food_y * 3 + 7) % MAP_HEIGHT;
            
            // Safety bounds check
            if(food_x < 1) food_x = 5;
            if(food_y < 1) food_y = 5;
        }

        // Begin frame draw sequence
        console_clear();
        
        // Top interface bar
        printf("\n  ===[ DELTA N64 HOMEBREW GAME ]===\n");
        printf("  SCORE: %05d   |   START: Reset position\n", score);
        printf("  --------------------------------------------------\n\n");

        // Build playfield grid
        for (int y = 0; y < MAP_HEIGHT; y++) {
            printf("  "); // Padding offset from side border
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (x == player_x && y == player_y) {
                    printf("X"); // Player asset representation
                } else if (x == food_x && y == food_y) {
                    printf("o"); // Food item asset representation
                } else {
                    printf(" "); // Open environment map grid node
                }
            }
            printf("\n");
        }

        // Send fully formed text matrix block directly to the screen display
        display_show(console_render());
    }
}
