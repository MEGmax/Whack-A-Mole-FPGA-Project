#include "address_map_arm.h"
#include <stdbool.h>
#include <stdbool.h>

#define ABS(x) (((x) > 0) ? (x) : -(x))
#define BLACK 0x0000
#define WHITE 0xFFFF

//globals
volatile int pixel_buffer_start; // global variable
volatile int * pixel_ctrl_ptr = (int *)0xFF203020; //front buffer address
volatile int * pixel_ctrl_ptr_back = (int *)0xFF20302C; //back buffer address
volatile char * character_buffer = (char *) 0x09000000;


//function prototypes
void displayStartScreen();
void setBackgroundColour(short int colour);
void drawMole(int xPos, int yPos);
void drawStartBox();
void draw_line(int x1, int y1, int x2, int y2, int hexColour);
void plot_pixel(int x, int y, short int colour);
void swap(int* v1, int* v2);
void write_text(int x, int y, char *text);

int modeSelScreen();
void drawModeSelScreen();
int livesSelScreen();
void drawLivesSelScreen();
int timeSelScreen();
void drawtimeSelScreen();
int endGameScreen();
void drawEndGameScreen();
int getNumOnes(int input);
int pollForKeyboardIn();

int main (void)
{
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;
    displayStartScreen();
    return 0;
}

//was thinking something more on the speed of this below
void main()
{
	while(1)
	{
		//startScreen();
		
		int mode = modeSelScreen();
		
		int modeData;
		if(mode==1)
		{ modeData = livesSelScreen(); }
		else if(mode==2)
		{ modeData = timeSelScreen(); }
		else
		{
			//send user to hell
		}
		
		//gameplayScreen();
		endGameScreen();
	}
	//we could make it so if a certain char on keyboard is pressed we end the game loop and display a photo of my ass?
}





void displayStartScreen()
{
    setBackgroundColour(BLACK);
    drawStartBox();
}

void drawStartBox()
{
    draw_line(40, 30, 40, 210, WHITE); //top left to bottom left
    draw_line(40, 30, 280, 30, WHITE); //top left to top right
    draw_line(280, 30, 280, 210, WHITE); //top right to bottom right
    draw_line(40, 210, 280, 210, WHITE); //bottom left to bottom right

    draw_line(38, 28, 38, 212, WHITE); //top left to bottom left
    draw_line(38, 28, 282, 28, WHITE); //top left to top right
    draw_line(282, 28, 282, 212, WHITE); //top right to bottom right
    draw_line(38, 212, 282, 212, WHITE); //bottom left to bottom right

    char* text = "PRESS ANY BUTTON TO START";
    write_text(30, 30, text);
}
//this function draws a line
void draw_line(int x1, int y1, int x2, int y2, int hexColour)
{
	//first determine if the line is steep by checking if the y is increasing more than the x
	bool isSteep = ABS(y2 - y1) > ABS(x2 - x1);
	
	//if it is steep swap the x starting postion with the y starting position
	//and the x final position with the y final position
	//(100, 0) to (100, 240) ---> (0, 100) to (240, 100)
	if(isSteep)
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
	}
	//if the intial x is greater than the final x, swap the "to and "from"
	//(100, 0) to (90, 240) ---> (90, 240) to (100, 0)
	if(x1 > x2)
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}
	//define variables
	int deltaX = ABS(x1-x2); //change in x
	int deltaY = ABS(y1-y2); //change in y
	int error = -1*deltaX/2; //error margin
	int y = y1; //current y
	int yStep; //how much y value to go over
	
	//if the y beginning is less than the y end then we need to go down
	//so yStep should be 1 since (0,1) will go to (0, 2) after stepping once
	if(y1 < y2)
	{
		yStep = 1;
	}
	//reverse logic for going up
	else
	{
		yStep = -1;
	}
	
	//loop through all the x values that the line takes up
	for(int x = x1; x < x2; x++)
	{
		//if it is steep we plot along the y axis rather than the x
		//since we swapped from before this will still plot (x, y) rather
		//than (y, x)
		if(isSteep)
		{
			plot_pixel(y, x, hexColour);
		}
		//if not steep plot normally
		else
		{
			plot_pixel(x, y, hexColour);
		}
		
		error += deltaY;
		if(error > 0) //if there is an error relative distance between height and width is "noticable"
		{
			y += yStep; //increment y in the correct direction
			error -= deltaX; //update error
		}
	}
}

void setBackgroundColour(short int colour)
{
	for(int x = 0; x < 320; x++) //320 pixels wide
	{
		for(int y = 0; y < 240; y++) //240 pixels tall
		{
			plot_pixel(x, y, colour); //plot a black pixel on EVERY pixel on the screen
		}
	}
}

void drawMole(int xPos, int yPos)
{
    
}

void swap(int* v1, int* v2)
{
	int temp;
	temp = *v1;
	*v1 = *v2;
	*v2 = temp;
}


void write_text(int x, int y, char *text) 
{
    char currCharacter = *text;
    while(*text)
    {
        character_buffer = (char *) (0x09000000 + (y<<7) + x); //updates location
        *character_buffer = currCharacter; //assigns value
        x++;
        text++;
        currCharacter = *text;
    }
}


//this function plots a pixel using the VGA pixel bufger
void plot_pixel(int x, int y, short int colour)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = colour;
}


int modeSelScreen()
{
	drawModeSelScreen();

	int mode=0;
	while(!mode)
	{
		volatile int *keyboardIn =(int *)0xff20050; //<---------change to wasd
		if (*keyboardIn == 97) //97:a
		{
			int mode =1;
		}
		else if(*keyboardIn == 100 ) //100:d
		{
			int mode =2;
		}
	}

	return mode;
}

int livesSelScreen()
{
	drawLivesSelScreen();
	int lives=0;
	volatile int *switchIn =(int *)0xff20000;//switches
	volatile int *keyboardIn =(int *)0xff20050; //<---------change to wasd
	while(!lives)
	{
		lives = getNumOnes(*switchIn);
	}
	return lives;
}

int timeSelScreen()
{
	drawtimeSelScreen();
	int time=0;
	volatile int *switchIn =(int *)0xff20000;//switches
	volatile int *keyboardIn =(int *)0xff20050; //<---------change to wasd
	while(!time)
	{
		time = getNumOnes(*switchIn);
	}
	return time;
}

int getNumOnes(int input)
{
	int numberOfOnes=0;
	while(input) // only when input = all zeros will it stop
	{
		numberOfOnes+=(input&1); //either adds zero or a 1 to our numOfOnes
		input >> 1; //preforms LSR(?), im assuming input is binary and we manipulate it as such
		//input/=10;//if input is binary but we can manipulate it like an int 
	}
	return numberOfOnes;
}

int endGameScreen()
{
	drawEndGameScreen();
	int input = pollForKeyboardIn();
	return input;
}

int pollForKeyboardIn()
{
	int input=0;
	volatile int *keyboardIn =(int *)0xff20050;
	while(!input)
	{
		input =*keyboardIn;
	}
	return input;
}

//this will reset the screen to black
void clear_screen()
{
	for(int x = 0; x < 320; x++) //320 pixels wide
	{
		for(int y = 0; y < 240; y++) //240 pixels tall
		{
			plot_pixel(x, y, 0x0000); //plot a black pixel on EVERY pixel on the screen
		}
	}
}
