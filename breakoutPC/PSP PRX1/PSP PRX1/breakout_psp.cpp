/**
 * @file 		breakout_psp.cpp
 * @author		kmurphy
 * @assignment  Breakout
 * @brief       PSP specific code for breakout (GLFW+PSP).
 *
 * @notes
 * 
 * I have tried to write this file so that it is similar to pong_glfw
 * however, the PSP libraries tend to be lower level (for efficiency 
 * purposes) than the corresponding OpenGL API and so the use of the 
 * PSP libraries tend to require the setting of more parameters, 
 * and require explicit allocation of memory in advance of call 
 * to library functions.	
 *
 */

// ===============================================
// Headers
// ===============================================
#include "breakout.h"

#ifdef PSP

// The PSP program execution model is different from that used on PCs. 
// On a PSP a program is loaded as a module and the executed on a thread. 
// How this thread runs — shared resources or exclusive, as a singleton 
// or as multiple instances — is specified by the SCE_MODULE_INFO macro
// as
// 		SCE_MODULE_INFO (name, attribute, major, minor)
// where
// 		name 		Name of the module and can be up to 27 characters in 
//					length and follows standard C rules for identifiers. 
//					The module name is used by the debugger to identify modules.
//		attribute	Flag used to permit/stop loading of modules with same name.
//		major 		Major version number 
// 		minor 		Minor version number
// Every program module must have a name and a module version 
// (see page 5 PSP Programming Tutorial).
SCE_MODULE_INFO( breakout, 0, 1, 1 );

// Allocate memory for storing the vertices of the graphic primitives 
//
// In order to the minimise memory used all memory allocation is the 
// responsibility of the programmer. Here we allocate memory to be 
// used to store the vertices of the graphical primitives (points, 
// line, triangle, rectangles, etc), While the statement is a simple 
// array declaration there are a few points to note:
// 	  * The information stored will be floats but the data type here is char. 
//		Why? The type used in allocation is of no importance — just the number 
//		of bytes allocated. Later the base address and the size of the array 
//		will be passed to the graphics sub-system.
//	  * The length of the array 0x1000 = 4096 is picked as is a power of two 
//		large enough for our needs.
//	  * The __attribute__ (( aligned (64))) advises the compiler/linker to 
//		allocate memory so that the array elements are aligned to word boundaries 
//		in memory — thereby getting faster access while possibly losing some memory.

#define MAX_LIST_SIZE 0x2000
static char				disp_list[MAX_LIST_SIZE] __attribute__((aligned(64)));

// Allocate memory for matrices used 3D (including 2d) rendering 
//
// We allocate memory to store up to 6 matrices that can be used to 
// transform (scale, translate, scale and shear) graphical objects. 
// Again, there are some items to note:
// 	  * The decomposition of 6 into 2+4+4+0 is to aid me later when passing 
// 		this memory to the graphic subsystem.
//	  * The matrix type, ScePspFMatrix4, is a 3 × 4 matrix of float and 
//		represents a general transformation in 4D Homogeneous coordinates.
//    * The keyword static is used on a file-scope (external) declaration 
//		to ensure that the identifier ( matrix_stack ) is not visible 
//		outside the file, thereby reducing the possibility of 
//		a “duplicate symbol” error when linking.
//		For this project, the use of static allows us to have file-scope 
//		identifiers with identical names in both pong_g3d.c and pong_psp.c 
//		without resulting in linker errors.

static ScePspFMatrix4	matrix_stack[2+4+4+0];


// Data to draw a unit square
//
// The PSP graphic libraries draw rectangles (as apposed to 
// more general quads in OpenGL). Hence, in order to specify 
// the rectangles we only need to pass vertex information for 
// any two diagonally opposing corners (in contrast to the vertex 
// information for all four corners in OpenGL).
//
// (the keyword static here means that the identifier 
// box is only visible in thie file.)

static const float box [] = {0,0,0, 1,1,0};


// The function init is similar to that in the pong_g3d.c file :
//    * Initialises the graphics subsystem and passes the address 
//		and size of the memory allocated for constructing the graphic objects.
//    * Activate the analog input on the controller.
int init() {

	if (SCE_OK != sceGuInit()) {
		printf("Error in initialising graphics library\n");
		return 1;
	}

	// After initialising the graphics sub-system we pass the 
	// address and size of the memory we allocated for storing 
	// the vertex information.
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));

	// Setup two buffers for double buffer animation. 
	// The depth buffer stores the depth of each pixel in the frame.
	sceGuDrawBuffer(SCEGU_PF5551, SCEGU_VRAM_BP_0, SCEGU_VRAM_WIDTH);
	sceGuDispBuffer(SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT,
		SCEGU_VRAM_BP_1, SCEGU_VRAM_WIDTH);			
	sceGuDepthBuffer(SCEGU_VRAM_BP_2, SCEGU_VRAM_WIDTH);

	// Specify offset used when transferring from 
	// screen coordinate system to drawing coordinate system
	sceGuOffset(SCEGU_SCR_OFFSETX, SCEGU_SCR_OFFSETY);

	// Set the viewport: x and y of top left corner and screen width, height
	sceGuViewport(2048, 2048, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);

	// The depth range for display list primitives.
	sceGuDepthRange(10000, 50000);

	// Next we specify what happens to vertices outside the viewport.
	sceGuScissor(0, 0, SCEGU_SCR_WIDTH, SCEGU_SCR_HEIGHT);
	sceGuEnable(SCEGU_SCISSOR_TEST);

	// Set the background colour: red,green,blue,alpha
	sceGuColor(0x00ff00ff);

	// Initialise the matrix stacks by allocating separate 
	// stack space for projection, view, world and texture matrices 
	// using memory allocated on line 79.
	sceGumSetMatrixStack(matrix_stack, 2, 4, 4, 0);

	// Set the matrix mode. Can be projection, view, world, or texture
	// Reset the current matrix stack (projection) by loading the identity matrix
	sceGumMatrixMode(SCEGU_MATRIX_PROJECTION);
	sceGumLoadIdentity();

	// Specify the project mode: Orthographic (2d) or perspective (3D).
	//    * For orthographic mode the parameters represent the range of 
	//		x, y and z  values that bound the cuboid viewing region.
	//    * For perspective mode we call function sceGumPerspective 
	//		and pass in camera angle of view, screen aspect ratio, 
	//		and z range giving screen near clipping plane and screen 
	//		far clipping plane
	sceGumOrtho(0,ASPECT, 0,1, -100.0f,100.0f);

	// Now that the desired projection is created we switch to model view.
	sceGumMatrixMode(SCEGU_MATRIX_WORLD);

	// Call secGuFinish to indicate that the display list creation is 
	// finished and it returns the amount of memory used in the construction. 
	// This must not exceed amount allocated in line 60.
	int size = sceGuFinish();
	if (size>MAX_LIST_SIZE) {
		fprintf(stderr, 
			"Error − Insufficient memory alloced for display_list (%d allocated, %d required) .\n", 
			MAX_LIST_SIZE, size); 
		return 1;		
	}

	// Tell drawing processor to wait for end of screen before drawing.
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);

	// Put the drawing thread in wait state until the 
	// start of next VBLANK interval
	sceDisplayWaitVblankStart();

	// Turn screen display on.
	sceGuDisplay(SCEGU_DISPLAY_ON);
		
	// Activate the analog stick — by default 
	// it is turned off to conserve power.
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITALANALOG) ;

	// timing information - not used

	return 0;	// success
}


// As in the OpenGL version the deinit function is just 
// a call the terminate the graphics subsystem.
// We could have allocated the memory for the display list 
// and the transformation matrices using malloc in function 
// init and then in this function released this memory. 
// This alternative approach would be useful for games where:
//    * The amount of memory needed to construct the display 
//		list varies significantly — have scenes consisting of 
//		large number of vertices.
//    * Larger matrix stacks are needed — larger number of 
//		transformations (rotations/translations/scaling) 
// 		are used to render objects.
int deinit() {	
	sceGuTerm();
	return 0;
}



// The function render is similar to that used in the OpenGL 
// version, since we have hidden the actual drawing in the 
// function drawRectangle.
// The only difference is the setting of the color and the
// setup at start and end of frame
int render() {
	
	sceGuStart(SCEGU_IMMEDIATE, disp_list, sizeof(disp_list));
	sceGuClear(SCEGU_CLEAR_ALL);
	
	// border 
	sceGuColor(0xffc08040);
	drawRectangle(0, 1-MARGIN_SIZE-BORDER_SIZE, ASPECT, BORDER_SIZE); 
	drawRectangle(0, 0, ASPECT, BORDER_SIZE); 
	drawRectangle(ASPECT-BORDER_SIZE, 0, ASPECT, 1-MARGIN_SIZE-BORDER_SIZE);

	// wall
	sceGuColor(0xff88ffff);
	for (int r=0; r<ROWS; r++)
		for (int c=0; c<COLS; c++) {
			if(wallLives[r][c]==5)
				sceGuColor(0x33333333);
			else if(wallLives[r][c]==3)
				sceGuColor(0x0000ffff);
			else if(wallLives[r][c]==2)
				sceGuColor(0xff0000ff);
			else
				sceGuColor(0x00ffff00);
			float x = WALL_X + (float)c*BRICK_WIDTH;
			float y = WALL_Y + (float)r*BRICK_HEIGHT;
			if (wall[r][c]) drawRectangle(x, y, BRICK_WIDTH-BRICK_GAP, BRICK_HEIGHT-BRICK_GAP);
		}

	// paddle
    if (paddle.human)
		sceGuColor(0xff0000ff);
    else 
		sceGuColor(0xffff00ff);
	drawRectangle(0, paddle.y, PADDLE_WIDTH, paddle.height); 

	// ball
	for(int i=0;i<balls.size();i++){
		sceGuColor(0x0000ffff);
		drawRectangle(balls[i].x, balls[i].y, BALL_SIZE, BALL_SIZE); 
	}
	
	// status message
	statusMessage();

	// signal end of drawing and check memory usage
	int size = sceGuFinish();
	if (size>MAX_LIST_SIZE) {
		fprintf(stderr, 
			"Error − Insufficient memory alloced for display_list (%d allocated, %d required) .\n", 
			MAX_LIST_SIZE, size); 
		return 1;		
	}
	
	// Tell drawing processor to wait for end of screen before drawing.
	sceGuSync(SCEGU_SYNC_FINISH, SCEGU_SYNC_WAIT);

	// Put the drawing thread in wait state until the 
	// start of next VBLANK interval
	sceDisplayWaitVblankStart();

	// swap the draw and display buffers
	sceGuSwapBuffers();
	
	// update frame timer - not done
	dt = 0.01f;	// fix the update rate on the PSP

	return 0;
}


void drawRectangle(float x, float y, float width, float height)  {


	sceGumLoadIdentity();

	ScePspFVector3 pos;
	pos.x = x;		pos.y = y;		pos.z = 0;
	sceGumTranslate(&pos);
	
	ScePspFVector3 scale;
	scale.x = width;		scale.y = height;		scale.z = 1;
	sceGumScale(&scale);

	// We call secGumDrawArray to draw a sequence of primitives 
	// using vertices stored in a array. The parameters are
	// 		type of primitive: points, lines, line strip, triangles, . . . 
	//		data type used to specify coordinates: u8-bit, u16-bit, float 
	//		number of vertices to draw
	//		pointer to index array (more on this later)
	//		pointer to vertex array
	// The use of display lists allows for more efficient rendering 
	// (see http://www.songho.ca/opengl/gl_displaylist.html).
	sceGumDrawArray(SCEGU_PRIM_RECTANGLES, SCEGU_VERTEX_FLOAT, 2, NULL, box);	
	sceGumPopMatrix();	
}

// output status message
// Very basic text output is possible using secGuDubugPrint 
// later we will use proper fonts.
// secGuDubugPrint uses pixel coordinates (not scaled coodinates)
void statusMessage() {
	
	// buffer to hold output message
	static char mess[100];

	sprintf(mess, 
		"FPS = %4.0f        Score = %3d    Lives = %1d", 1.0/dt, 1, lives);

	sceGuDebugPrint(20, WINDOW_HEIGHT-10, 0x00ffffff, mess);
}

// Finally we have function processInput which deals with 
// input from the controller. Notice that are significant 
// differences between keyboard input and PSP input. Namely:
//    * The keyboard is a relatively simple serial input 
//		device with a large set of keys and a limited number 
//		of modifier keys.
//		In contract the PSP has a limited set of keys but 
//		all key combinations need to be supported.
//    * The keyboard has limited configuration setting - delay 
//		before key repeating and key repeat rate.
//		Depending on the game we would like arbitrary short 
//		delay before key repeating (i.e., want instantaneous 
//		key repeating) and want arbitrary fast key repeating 
//		(i.e., want continuous mode).
// To accomplish the exacting gamer demands the processing of 
// input needs to be very efficient =⇒ use bit manipulation 
// to determine input.
int processInput() {
	
	static u_int32	prev;					// button status on previous call
	u_int32 		cont;					// current button status
	u_int32		 	padd;					// when buttons have JUST BE PRESSED
 	SceCtrlData		buf;					// store both button and analog status

	sceCtrlReadBufferPositive(&buf, 1);		// populate buf from input queue
	cont = buf.Buttons;						// extract current buttons status 
	padd = cont & (cont ^ prev);			// which buttons has just been pressed?
	prev = cont;							// store button status for next call

	// Check button status for controlling game states.
	// The identifiers SCE_CTRL_SELECT etc are defined in ctrlsvc.h
	if (padd & SCE_CTRL_SELECT) {			
		gameState = GAME_QUIT;
		return 0;
	}

	if (padd & SCE_CTRL_START) {
		gameState = GAME_START;
		return 0;
	}
	
	if (padd & SCE_CTRL_SQUARE) {
		paddle.human = !paddle.human;
	}
	
	// control the paddle using digital buttons
	if (paddle.human) {
		if (cont & SCE_CTRL_CIRCLE) {
			paddle.dy = -1.0f;
		} else if (cont & SCE_CTRL_CROSS) {
			paddle.dy = 1.0f;
		} else {
			paddle.dy = 0.0f;
		}
	}
		
	// control the paddle using analog stick
	//
	// The analog input returns an integer in range [0, 255], 
	// This is first converted to a float in interval [−1, 1] and 
	// we ignore small inputs as otherwise the paddle would “drift” when 
	// the analog stick is released.	
	if (paddle.human) {
		float dy = ( buf.Ly - 128 ) / 128.0f ;
		if ( dy < -0.75)
			paddle.dy = -dy;
		else if (dy > 0.75f) 
			paddle.dy = -dy;
		else 
			paddle.dy = 0.0f;
	}
}

#endif
