/**
 * @file 		breakout.cpp
 * @author		Stephen Long
 * @assignment  Brekaout
 * @brief		Main code (game loop, global identifiers ..) for breakout (GLFW+PSP).
 *
 * @notes:I had problems adding the second ball. I thought it would be fine to add them the same way I did in my pong game, but Visual
 Studio kept telling me I had an error with a non-existant semi-colon, so rather than argue with this primitive software, I just 
 added attempted to hardcode the second ball, however when I mess with the dx & dy values of ball2, it affects collisions for both 
 balls. So this prevented me from adding a trapped ball. I added a value called "isActive" to the struct Ball so I could make the 
 second ball bounce of bricks without breaking them (while it was trapped), but it messed up collisions on my first ball. 
 So to conclude, there are brick lives, multiple levels, extras, a level where the first ball is trapped momentarily, but there
 is no trapped ball that you free by breaking blocks.
 *			
 */

// ===============================================
// Headers
// ===============================================

#include "breakout.h"
int randRow;
int randCol;
// ===============================================
// Global identifiers
// ===============================================


// timing information
double dt, startTime, previousTime, currentTime;

// state for main game loop
GameState gameState;
bool done;

// ball
Ball ball;
Ball ball2;
float ballSpeed = BALL_MAX_SPEED;

// paddles
Paddle paddle = {0, BORDER_SIZE, 0,0, PADDLE_MAX_HEIGHT, false};

// wall
int wall[ROWS][COLS];

//life
Life life1 = {0.05 * 3, COURT_TOP + .025f, true};
Life life2 = {0.05*2, COURT_TOP + .025f, true};
Life life3 = {0.05, COURT_TOP + .025f, true};

//extras
int score = 0;
bool sacrifice = true;
int counter = ROWS*COLS;
int playerLives = 3;
int level = 0;

// ===============================================
// @function main
// ===============================================

int main() {
	

 	init();			// initial graphics/sound components
	gameState = GAME_INTRO;
	done = false;
        
	while (!done) {
		switch (gameState) {
			
			// Display game intro screen etc
			// not implemented - just switches to state START_GAME 
			case(GAME_INTRO): {
				srand ((unsigned int)time(NULL));
				// do nothing here yet TODO
				gameState = GAME_START;
				printf ("Game state changed from GAME_INTRO to GAME_START\n");
				break;
			}

			// Run setup code needed at start of game 
			case(GAME_START): {
				gameState = LEVEL_FOUR_START;
				printf ("Game state changed from GAME_START to LEVEL_START\n");
				break;
			}

			// Create level using data in file and start playing level
			case(LEVEL_ONE_START): {
				level=1;
				playerLives=3;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
                // place ball at center with random direction TODO
                ball.x = (ASPECT+BALL_SIZE)/4.0f;
                ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                ball.dx = 1;
                ball.dy = 1;
				
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++)
						wall[r][c] = 1;
                
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
				}
			case(LEVEL_TWO_START): {
				level=2;
				counter = ROWS*COLS;
				playerLives=3;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
                // place ball at center with random direction TODO
                ball.x = (ASPECT+BALL_SIZE)/4.0f;
                ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                ball.dx = 1;
                ball.dy = 1;
				
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++)
						wall[r][c] = 3;

				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			  }

		   case(LEVEL_THREE_START): {
			   level=3;
				counter = 9;
				playerLives=3;
				// position paddles
				paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
                // place ball at center with random direction TODO
                ball.x = (ASPECT+BALL_SIZE)/4.0f;
                ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                ball.dx = 1;
                ball.dy = 1;
				
				// reset wall
				for (int r=1; r<ROWS; r++)
					for(int c=2; c<COLS; c++)
						wall[r][c] = 3;

				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			  }

			case(LEVEL_FOUR_START): {
				
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++)
						wall[r][c] = 3;

				randRow = rand()% 2 + 1;
				randCol = rand() %  3 + 1;
				wall[randRow][randCol]=0;
				ball.x = WALL_X + (float)randCol*(BRICK_WIDTH) + (BRICK_WIDTH/2);
				ball.y = WALL_Y + (float)randRow*(BRICK_HEIGHT) + (BRICK_HEIGHT/2);
				ball.dx=1;
				ball.dy=1;

			    level=4;
				counter = (ROWS*COLS)-1;
				playerLives=3;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);   
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			  }

			case(LEVEL_FIVE_START): {	
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++)
						wall[r][c] = 3;

				randRow = rand()% 2 + 1;
				randCol = rand() %  3 + 1;
				wall[randRow][randCol]=0;
				ball.x = (ASPECT+BALL_SIZE)/4.0f;
                ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
				ball.dx=1;
				ball.dy=1;

				ball2.x = WALL_X + (float)randCol*(BRICK_WIDTH) + (BRICK_WIDTH/2);
				ball2.y = WALL_Y + (float)randRow*(BRICK_HEIGHT) + (BRICK_HEIGHT/2);
				ball2.dx=1;
				ball2.dy=1;
				
			    level=5;
				counter = (ROWS*COLS)-1;
				playerLives=3;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
					}

			case(LEVEL_PLAY): {
				printf("\rLives remaining: %i \n", playerLives);
				render();
				processInput();
				update();
				break;

			}

			// move to next level or game over - TODO
			case(LEVEL_OVER): {
				gameState = GAME_OVER;
				printf ("Game state changed from LEVEL_OVER to GAME_OVER\n");
				break;
			}

			// restart game or quit game - TODO
			case(GAME_OVER): {
				gameState = GAME_QUIT;
				printf ("Game state changed from GAME_OVER to GAME_QUIT\n");
				break;
			}

			// state - GAME_QUIT
			case(GAME_QUIT): {
				printf ("Game state changed to GAME_QUIT\n");
				done = true;
				break;
			}

			default: {
				fprintf (stderr, "Game state %d is not valid.\n", gameState);
				return 1;
			}
		}
	
	}
	deinit();

	return 0;
}

//Method for resetting ball when it passes paddle
void resetBall()
	{
		ball.x = ASPECT*2/4-0.2f;
		ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
		ball.dx = -1;
		ball.dy = -0.8;
	}

int update() {

    float sdt = (float) (SPEED*dt);
	
    // update paddle
    if (!paddle.human)
	{
        paddle.dy =  (paddle.y>ball.y) ? -1 : (paddle.y+paddle.height<ball.y+BALL_SIZE) ? 1 : 0; 
    }
    paddle.y += sdt*PADDLE_SPEED*paddle.dy;
    paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
   
    // update ball
    ball.x += sdt*ballSpeed*ball.dx;
    ball.y += sdt*ballSpeed*ball.dy;

	//update ball 2
	ball2.x += sdt*ballSpeed*ball2.dx;
    ball2.y += sdt*ballSpeed*ball2.dy;
    
    // collisions: ball-border vertical
    if (ball.y<=BORDER_SIZE) 
	{
        ball.dy = -ball.dy;
    } else if (ball.y>=COURT_TOP-BALL_SIZE) 
	{
        ball.dy = -ball.dy;
    } 
    
    // collisions: ball-border right
    if (ball.x+BALL_SIZE>=ASPECT-BORDER_SIZE)
	{
        ball.dx = -ball.dx;
	}

	//collisions ball2 ball-border
	if (ball2.y<=BORDER_SIZE) 
	{
        ball2.dy = -ball2.dy;
    } else if (ball2.y>=COURT_TOP-BALL_SIZE)
	{
        ball2.dy = -ball2.dy;
    } 

	if (ball2.x+BALL_SIZE>=ASPECT-BORDER_SIZE) 
	{
        ball2.dx = -ball2.dx;
	}

    // collision: ball-paddle

	if(level==3)
	{
		if (ball.x<PADDLE_WIDTH) 
		{
			if (ball.y+BALL_SIZE>paddle.y && ball.y<paddle.y+paddle.height) 
		{
            ball.dx = -ball.dx;
			paddle.height=paddle.height-0.01f;

        } else { //miss
            resetBall();
			paddle.height=paddle.height-0.03f;
			playerLives=playerLives-1;
			score = score - 50;
        }
	}
	}
	
	else{
    if (ball.x<PADDLE_WIDTH) 
	{
        if (ball.y+BALL_SIZE>paddle.y && ball.y<paddle.y+paddle.height)
		{
            ball.dx = -ball.dx;

        } else { //miss
            resetBall();
			playerLives=playerLives-1;
			score = score - 50;
        }
	}

	 if (ball2.x<PADDLE_WIDTH) 
		{
        if (ball2.y+BALL_SIZE>paddle.y && ball2.y<paddle.y+paddle.height)
		{
            ball2.dx = -ball2.dx;

        }
	 }

		if(playerLives<=0)
			gameState=GAME_OVER;
    }

    // ball - wall
    if (! checkPointBoxCollision(ball.x, ball.y, WALL_X-BALL_SIZE, WALL_Y-BALL_SIZE, 
			COLS*BRICK_WIDTH+BALL_SIZE, ROWS*BRICK_HEIGHT+BALL_SIZE))
		return 0;

	// possible ball -brick collision so need to do more careful testing
	if (DEBUG) ballSpeed = 0.2*BALL_MAX_SPEED;	// slow ball down 
	
	// calculate ball position with respect to blocks row and column
	int ballCol = (int) ((ball.x - WALL_X ) / (BRICK_WIDTH));
	int ballRow = (int) ((ball.y - WALL_Y ) / (BRICK_HEIGHT));

	bool top=false, bottom=false, left=false, right=false;
	float const D=BALL_SIZE/2.0f;		// temporary values to save on typing 

	// only check the set of 9 possible bricks around the ball current position
	for (int col=ballCol-1; col<=ballCol+1; col++) {
		for (int row=ballRow-1; row<=ballRow+1; row++) {
			// top
			top = checkPointBrickCollision(ball.x+D, ball.y+2*D, row, col) || top;			
			// bottom
			bottom = checkPointBrickCollision(ball.x+D, ball.y, row, col) || bottom;
			// left
			left = checkPointBrickCollision(ball.x, ball.y+D, row, col) || left;
			// right
			right = checkPointBrickCollision(ball.x+2*D, ball.y+D, row, col) || right;


			if(counter==0)
			{
				if(level==1)
				{
				gameState = LEVEL_TWO_START;
				}
				else if(level==2)
				{
					gameState=LEVEL_THREE_START;
				}
				else if(level==3)
				{
					gameState =LEVEL_FOUR_START;
				}
				else if(level==4)
				{
					gameState = LEVEL_FIVE_START;
				}
				else if(level==5)
				{
					gameState = GAME_OVER;
				}
			}
		}		
	}

	// Now update ball if found any collisions 
	if (top) {
		ball.dy = -ball.dy;
		ball.y -= D;
		//score = score + 10;
	}
	if (bottom) {
		ball.dy = -ball.dy;
		ball.y += D; 
		//score = score + 10;
	}
	if (left) {
		ball.dx = -ball.dx;
		ball.x += D; 
		//score = score + 10;
	}
	if (right) {
		ball.dx = -ball.dx;
		ball.x -= D; 
		//score = score + 10;
	}

	ball.y = clamp(ball.y,BORDER_SIZE,COURT_TOP-BALL_SIZE);

	//	exit(1);
	return 0;   // success
}

bool checkPointBoxCollision(float x, float y, float xStart, float yStart, float width, float height) {

	return (x>=xStart &&x<=xStart+width && y>=yStart &&y<=yStart+height);
}
	
bool checkPointBrickCollision(float x, float y, int row, int col) {
	
	if (row>=0 && row<ROWS && col>=0 && col<COLS && wall[row][col]>0) {
		float xStart = WALL_X + (float)col*BRICK_WIDTH;
		float yStart = WALL_Y + (float)row*BRICK_HEIGHT;
		if (checkPointBoxCollision(x, y, xStart, yStart, BRICK_WIDTH, BRICK_HEIGHT)) {
			if(wall[row][col]==1)
				counter--;
			wall[row][col]--;
			score = score + 10;
			return true;		
		}
	}
	return false;

}
