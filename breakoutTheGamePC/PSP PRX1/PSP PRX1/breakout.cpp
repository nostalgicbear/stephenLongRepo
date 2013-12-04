/**
 * @file 		breakout.cpp
 * @author		kmurphy
 * @assignment  Pong
 * @brief		Main code (game loop, global identifiers ..) for breakout (GLFW+PSP).
 *
 * @notes
 *			
 */

// ===============================================
// Headers
// ===============================================

#include "breakout.h"

// ===============================================
// Global identifiers
// ===============================================

// timing information
double dt, startTime, previousTime, currentTime;

// state for main game loop
GameState gameState;
bool done;
int currentLevel =0;
// ball
Ball ball;
float ballSpeed = BALL_MAX_SPEED;
int lives=0;
// paddles
Paddle paddle = {0, BORDER_SIZE, 0,0, PADDLE_MAX_HEIGHT, false};

// wall
bool wall[ROWS][COLS];
int wallLives[ROWS][COLS];
std::vector<Ball> balls;

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
				// do nothing here yet TODO
				gameState = GAME_START;
				printf ("Game state changed from GAME_INTRO to GAME_START\n");
				break;
			}

			// Run setup code needed at start of game 
			case(GAME_START): {
				gameState = LEVEL_ONE_START;
				 // place ball at center with random direction TODO
                ball.x = (ASPECT+BALL_SIZE)/4.0f;
                ball.y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                ball.dx = 1;
                ball.dy = 1;
				ball.visable=1;
				ball.canBreak =1;
				balls.push_back(ball);
				printf ("Game state changed from GAME_START to LEVEL_START\n");
				lives =3;
				break;
			}
			case(LEVEL_ONE_START): {
				currentLevel=1;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
               
				
				// reset wall;
				bool vis=true;
				for (int r=0; r<ROWS; r++){
					if(r%2==0)
						vis=true;
					else
						vis=false;
					for(int c=0; c<COLS; c++){
						
						vis=!vis;
						wall[r][c] = vis;
						wallLives[r][c]=1;
					}
				}
				wallLives[2][4]= 5;
				
				
                
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			}


			// Create level using data in file and start playing level
			case(LEVEL_THREE_START): {
				currentLevel=3;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
                // place ball at center with random direction TODO
                balls[0].x = (ASPECT+BALL_SIZE)/4.0f;
                balls[0].y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                balls[0].dx = 1;
                balls[0].dy = 1;

				
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++){
						wall[r][c] = true;
						wallLives[r][c]=(rand()%3)+1;
					}
				wallLives[2][4]= 5;
				
				
                
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			}
			
			case(LEVEL_TWO_START): {
				currentLevel=2;
				// position paddles
                paddle.height = PADDLE_MAX_HEIGHT;
                paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
                
                // place ball at center with random direction TODO
                balls[0].x = (ASPECT+BALL_SIZE)/4.0f;
                balls[0].y = (1-MARGIN_SIZE-2*BORDER_SIZE+BALL_SIZE)/2.0f;
                balls[0].dx = 1;
                balls[0].dy = 1;

				
				// reset wall
				for (int r=0; r<ROWS; r++)
					for(int c=0; c<COLS; c++){
						wall[r][c] = true;
						wallLives[r][c]=(rand()%3)+1;
					}
					wall[2][2]=false;
					ball.x = WALL_X + (2*BRICK_WIDTH)+.001;
					ball.y = WALL_Y + (float)2*BRICK_HEIGHT;
					ball.dx = 1;
					ball.dy = 1;
					ball.visable = 1;
					ball.canBreak=0;
					balls.push_back(ball);
				
				
                
				gameState = LEVEL_PLAY;
				printf ("Game state changed from LEVEL_START to LEVEL_PLAY\n");
				break;
			}

			case(LEVEL_PLAY): {
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


int update() {
	
		
	float sdt = (float) (SPEED*dt);
	for(int i =0; i<balls.size();i++){
		// update paddle
		if (!paddle.human &&balls[i].dx<0&& balls[i].x<(ASPECT*5/8)) {
			paddle.y =  (paddle.y+(paddle.height/2)>balls[i].y) ? paddle.y-.007f : (paddle.y+(paddle.height/2)<balls[i].y+BALL_SIZE) ? paddle.y+.007f : paddle.y; 
			paddle.dy=0;
		}
		paddle.y += sdt*PADDLE_SPEED*paddle.dy;
		paddle.y = clamp(paddle.y, BORDER_SIZE, COURT_TOP-paddle.height);
	   
		// update balls[i]
		balls[i].x += sdt*ballSpeed*balls[i].dx;
		balls[i].y += sdt*ballSpeed*balls[i].dy;
		
	    
		// collisions: balls[i]-border vertical
		if (balls[i].y<=BORDER_SIZE) {
			balls[i].dy = -balls[i].dy;
			balls[i].y = clamp(balls[i].y, BORDER_SIZE, COURT_TOP-BALL_SIZE);
		} else if (balls[i].y>=COURT_TOP-BALL_SIZE) {
			balls[i].dy = -balls[i].dy;
			balls[i].y = clamp(balls[i].y, BORDER_SIZE, COURT_TOP-BALL_SIZE);
		} 
		
	    
		// collisions: balls[i]-border right
		if (balls[i].x+BALL_SIZE>=ASPECT-BORDER_SIZE) {
			balls[i].dx = -balls[i].dx;
		}
		
		// collision: balls[i]-paddle
		if (balls[i].x<PADDLE_WIDTH) {
			if (balls[i].y+BALL_SIZE>paddle.y && balls[i].y<paddle.y+paddle.height) {
				balls[i].dx = -balls[i].dx;   
			} else { //miss
				lives--;
				balls.erase(balls.begin() +i);
				if(balls.size() ==0)
					balls.push_back(ball);
				if (lives<1)
					gameState = LEVEL_OVER;       
			}
		}
		
		// balls[i] - wall
		if (! checkPointBoxCollision(balls[i].x, balls[i].y, WALL_X-BALL_SIZE, WALL_Y-BALL_SIZE, 
			COLS*BRICK_WIDTH+BALL_SIZE, ROWS*BRICK_HEIGHT+BALL_SIZE)){}
		else{
			

		
		// possible balls[i] -brick collision so need to do more careful testing
		if (DEBUG) ballSpeed = 0.2*BALL_MAX_SPEED;	// slow balls[i] down 
		
		// calculate balls[i] position with respect to blocks row and column
		int ballCol = (int) ((balls[i].x - WALL_X ) / (BRICK_WIDTH));
		int ballRow = (int) ((balls[i].y - WALL_Y ) / (BRICK_HEIGHT));

		bool top=false, bottom=false, left=false, right=false;
		float const D=BALL_SIZE/2.0f;		// temporary values to save on typing 

		// only check the set of 9 possible bricks around the balls[i] current position
		int col, row;
			for (col=ballCol-1; col<=ballCol+1; col++) {
				for (row=ballRow-1; row<=ballRow+1; row++) {
					// top
					top = checkPointBrickCollision(balls[i].x+D, balls[i].y+2*D, row, col,balls[i]) || top;			
					// bottom
					bottom = checkPointBrickCollision(balls[i].x+D, balls[i].y, row, col,balls[i]) || bottom;
					// left
					left = checkPointBrickCollision(balls[i].x, balls[i].y+D, row, col,balls[i]) || left;
					// right
					right = checkPointBrickCollision(balls[i].x+2*D, balls[i].y+D, row, col,balls[i]) || right;
					
					}


				}
			

		
		
		
		// Now update balls[i] if found any collisions 
		if (top) {
			balls[i].dy = -balls[i].dy;
			balls[i].y -= D; 
		}
		if (bottom) {
			balls[i].dy = -balls[i].dy;
			balls[i].y += D; 
		}
		if (left) {
			balls[i].dx = -balls[i].dx;
			balls[i].x += D; 
		}
		if (right) {
			balls[i].dx = -balls[i].dx;
			balls[i].x -= D; 
		}
		if(!balls[i].canBreak){
			for (col=1; col<=3; col++) 
				for (row=1; row<=3; row++) 
					if (!wall[row][col])
						if(row != 2 || col != 2){
							balls[i].canBreak=1;
							
						}
			
		}
		}
	}
	bool fin = true;
	for(int i=0; i<ROWS; i++)
		for (int j=0; j<COLS;j++)
			if (wall[i][j])
				fin=false;
	if(fin)
		if(currentLevel==1)
			gameState=LEVEL_TWO_START;
		else if(currentLevel==2)
			gameState=LEVEL_THREE_START;
		else if (currentLevel ==3)
			gameState = LEVEL_ONE_START;



	//	exit(1);
	return 0;   // success
}

bool checkPointBoxCollision(float x, float y, float xStart, float yStart, float width, float height) {

	return (x>=xStart &&x<=xStart+width && y>=yStart &&y<=yStart+height);
}
	
bool checkPointBrickCollision(float x, float y, int row, int col, Ball ballTest) {
	
	if (row>=0 && row<ROWS && col>=0 && col<COLS && wall[row][col]>0) {
		float xStart = WALL_X + (float)col*BRICK_WIDTH;
		float yStart = WALL_Y + (float)row*BRICK_HEIGHT;
		if (checkPointBoxCollision(x, y, xStart, yStart, BRICK_WIDTH, BRICK_HEIGHT)) {
			if(wallLives[row][col]==5){
					wall[row][col] =false;
					Ball ball1;
					ball1.x=balls[0].x;
					ball1.y = balls[0].y;
					ball1.dx = -balls[0].dx;
					ball1.dy = -balls[0].dy;
					ball1.visable=ball1.canBreak=true;
					balls.push_back(ball1);
			}
			if(ballTest.canBreak)
				wallLives[row][col] --;
			if(wallLives[row][col]==0)
				wall[row][col] = false;
			return true;		
		}
	}
	return false;
}
