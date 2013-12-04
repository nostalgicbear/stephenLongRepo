/**
 * @file 		breakout.h
 * @author		kmurphy
 * @assignment  Pong
 * @brief		Header file for breakout (GLFW+PSP).
 *
 * @notes
 *			
 */

#ifndef BREAKOUT_H
#define BREAKOUT_H

// uncomment next line for PSP executable
#define PSP 1
 
// ===============================================
// Includes - both platform specific and commmon
// ===============================================
#ifdef PSP								// PSP specific headers
	#include <psptypes.h>
	#include <kernel.h>
	#include <psperror.h>		
	#include <displaysvc.h>
	#include <ctrlsvc.h>				// controller 
	#include <libgu.h>					// basic graphics
	#include <libgum.h>					// 3D "OpenGLish" graphics 
#else 									// using GLFW (OpenGL) 
	#ifdef _WIN32   						// Windows system specific
		#include <GL/glfw.h> 
	#else
	    #ifdef __APPLE__                // OS X
    		#include <OpenGL/gl.h>          
	    	#include <OpenGL/glu.h>         
	    	#include <OpenGL/freeglut.h>  
	    	#include <GL/glfw.h> 
	    #else				            // linux
		    #include <GL/gl.h>          
	    	#include <GL/glu.h>         
		    #include <GL/freeglut.h>  
		    #include <GL/glfw.h>
	    #endif 
	#endif
#endif

#include <stdio.h>      				// for sprintf()
#include <stdlib.h>     				// for atof() 
#include <string.h>     				// for strcpy()
#include <math.h>       				// for cos(), sin()
#include <vector>

// ===============================================
// Global identifiers
// ===============================================

// window & scene
#ifdef PSP
	const int WINDOW_WIDTH = 480;
	const int WINDOW_HEIGHT = 272;
#else
	const float SCALE = 2.0f; 
	const int WINDOW_WIDTH = (int) (480*SCALE);
	const int WINDOW_HEIGHT = (int) (272*SCALE);
	const char WINDOW_NAME [] = "Breakout";
#endif
const float ASPECT = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);

// screen background dimensions
const float MARGIN_SIZE = 0.05f;
const float BORDER_SIZE = 0.01f;
const float COURT_TOP = 1.0f - MARGIN_SIZE - BORDER_SIZE;

// timing information
extern double dt, startTime, previousTime, currentTime;
extern int lives;
const float SPEED =5.0f;

// state for main game loop
enum GameState {GAME_INTRO, GAME_START, LEVEL_ONE_START, LEVEL_TWO_START, LEVEL_THREE_START, LEVEL_PLAY, LEVEL_OVER, GAME_OVER, GAME_QUIT};
extern GameState gameState;
extern bool done;

#define DEBUG 0

// ball
const float BALL_SIZE = 0.02f;
const float BALL_MAX_SPEED = 0.15f;
extern float ballSpeed;

struct Ball {
	float x, y;
	float dx, dy;
	bool visable, canBreak;
};
extern Ball ball;
extern std::vector<Ball> balls;

// paddle
const float PADDLE_WIDTH = 0.03f;
const float PADDLE_SPEED = 0.15f;
const float PADDLE_MAX_HEIGHT = 0.2f;
const float PADDLE_MIN_HEIGHT = 0.1f;
struct Paddle {
	float x, y;
	float dx, dy;
	float height;
	bool human;
};
extern Paddle paddle;

// used to output messages/status
const int STATUS_LENGTH = 250;
extern char status[STATUS_LENGTH];			// used to display game text

// wall
const int ROWS = 6;
const int COLS = 8;
extern bool wall[ROWS][COLS];
extern int wallLives[ROWS][COLS];

const float WALL_V_GAP = 0.2f;
const float WALL_H_GAP = 0.1f;
const float BRICK_GAP = 0.005f;
const float BRICK_HEIGHT = (COURT_TOP-BORDER_SIZE-2*WALL_V_GAP) / ROWS;
const float WALL_Y = BORDER_SIZE + WALL_V_GAP;
const float WALL_X = 1.0;
const float BRICK_WIDTH = (ASPECT-WALL_X-BORDER_SIZE-WALL_H_GAP) / COLS;

// ===============================================
// Function prototypes
// ===============================================

// ensure that x is in range [low..high]
inline float clamp(float x, float low=0.0f, float high=1.0f) {
	return x<low? low : (x>high?high:x);
}

// return the square of distance between two points
inline float distanceSqr(float x1, float y1, float x2, float y2) {
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

// platform generic functions
int update();							// update game entities
int startLevel();

bool checkPointBoxCollision(float x, float y, float xStart, float yStart, float width, float height);
bool checkPointBrickCollision(float x, float y, int col, int row,Ball ballText);

// platform specific functions
int init();								// initialise graphics and other subsystems
int deinit();							// release all resources
int processInput();						// process keyboard/controler input
int render();							// draw scene
void drawRectangle(float x, float y, float width, float height);
void statusMessage();	

#endif
