/**
 * @file 		pong_glfw.cpp
 * @author		kmurphy
 * @assignment  Pong
 * @brief		GLFW specific code for pong (GLFW+PSP).
 *
 * @notes
 *			
 */

// ===============================================
// Headers
// ===============================================
#include "breakout.h"

#ifndef PSP


int init() {

	glfwInit(); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if( !glfwOpenWindow(WINDOW_WIDTH,WINDOW_HEIGHT, 0,0,0,0,0,0, GLFW_WINDOW) ) { 
		glfwTerminate(); 
		return 1; 
	} 
	glfwSetWindowPos(100,100);
	glfwSetWindowTitle(WINDOW_NAME);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ASPECT, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	
	// frame information
    startTime = currentTime = glfwGetTime();

    return 0;   //success
}


int deinit() {
	glfwTerminate(); 

    return 0;   //success
}


void statusMessage() {

	
}

int render() {
	glClear(GL_COLOR_BUFFER_BIT); 
	
    // border
    glColor3f(1, 0, 0);
	drawRectangle(0, 1-MARGIN_SIZE-BORDER_SIZE, ASPECT, BORDER_SIZE); 
	drawRectangle(0, 0, ASPECT, BORDER_SIZE); 
	drawRectangle(ASPECT-BORDER_SIZE, 0, ASPECT, 1-MARGIN_SIZE-BORDER_SIZE);

	// wall
	for (int c=0; c<COLS; c++) {
		for (int r=0; r<ROWS; r++) {
			if (wallLives[r][c]==5)
				glColor3f(.3f,.3f,.3f);
			else if (wallLives[r][c]==3)
				glColor3f(1, 1, 1);
			else if(wallLives[r][c]==2)
				glColor3f(1,0,1);
			else
				glColor3f(1,0,0);
			float x = WALL_X + (float)c*BRICK_WIDTH;
			float y = WALL_Y + (float)r*BRICK_HEIGHT;
			if (wall[r][c]) drawRectangle(x, y, BRICK_WIDTH-BRICK_GAP, BRICK_HEIGHT-BRICK_GAP);
		}
	}
		
	// paddle
    if (paddle.human)
        glColor3f(0, 1, 0);
    else 
        glColor3f(1, 1, 0);
	drawRectangle(0, paddle.y, PADDLE_WIDTH, paddle.height); 

	// ball
	for(int i=0;i<balls.size(); i++)
	{
		Ball ball = balls[i];
		glColor3f(0, 0, 1);
		drawRectangle(ball.x, ball.y, BALL_SIZE, BALL_SIZE); 
	}

	statusMessage();	

	glfwSwapBuffers(); 

	// update frame timer
	previousTime = currentTime;
    currentTime = glfwGetTime();
	dt = clamp ((float) (currentTime - previousTime), 0.0f, 0.05f);
	
	return 0;   // success
}

void drawRectangle(float x, float y, float width, float height)  {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(width, height, 1);
    glBegin(GL_QUADS);
    	glVertex3f(0, 0, 0);
    	glVertex3f(1, 0, 0);
    	glVertex3f(1, 1, 0);
    	glVertex3f(0, 1, 0);
    glEnd();	
    glPopMatrix();
}
    

int processInput() {

	if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {
	    gameState = GAME_QUIT;
	    return 0;
    }

    if (glfwGetKey(GLFW_KEY_UP)) {
        paddle.dy = 1.0f;
    } else if (glfwGetKey(GLFW_KEY_DOWN)) {
        paddle.dy = -1.0f;
    } else {
        paddle.dy = 0.0f;
    }	
    	
    if (glfwGetKey('A')) paddle.human = !paddle.human;
    
    return 0;   //success
}

#endif

