#ifndef POWERUP_H
#define POWERUP_H

#include "globals.h"

// Define the maximum number of power-ups
#define MAX_POWERUPS 10

// Power-up dimensions
#define POWERUP_WIDTH 32
#define POWERUP_HEIGHT 16

// Power-up falling speed
#define POWERUP_SPEED 2.0


typedef enum {
    POWERUP_LASER,   // L
    POWERUP_PLAYER,  // P
    POWERUP_CATCH,   // C
    POWERUP_DIVIDE,  // D
    POWERUP_EXPAND,  // E
    POWERUP_BREAK,   // B
    POWERUP_SLOW,    // S
    POWERUP_TOTAL    // Total number of power-ups
} PowerUpType;

typedef struct {
    double x, y;        // Position
    double vy;          // Vertical speed
    PowerUpType type;   // Type of power-up
    bool isActive;      // Is the power-up active
    int animationFrame; // Current frame of the animation
} PowerUp;

extern PowerUp powerUps[MAX_POWERUPS]; // Declaration
extern int activePowerUps; 


// Function prototypes
void spawnPowerUp(double x, double y, PowerUpType type);
void updatePowerUps();
void renderPowerUps();
void handlePowerUpCollection();
void initializePowerUps();
SDL_Rect* getCurrentPowerUpSprite(PowerUp* powerUp);

#endif // POWERUP_H
