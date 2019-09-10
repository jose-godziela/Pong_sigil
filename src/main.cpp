#include "sl.h"
#define PLAYER1 0
#define PLAYER2 1

const int screenWidth = 800;
const int screenHeight = 450;
const int recHeight = 100;
const int recWidth = 20;
const int cant_players = 2;
const float speed = 7.0f;
int radius = 20;
struct players {
	float x;
	float y;
	float width;
	float height;
}players[cant_players];
float J1recX = screenWidth / 15;
float J1recY = screenHeight / 2;
float J2recX = screenWidth - (screenWidth / 17);
float J2recY = screenHeight / 2;
float circleX = screenWidth / 2;
float circleY = screenWidth / 2;
bool movVert = false;
bool movHor = false;

int main()
{
	for (int i = 0; i < cant_players; i++) {
		players[i].x = screenWidth / 15;
		players[i].y = screenHeight / 2;

	}
	// set up our window and a few resources we need
	slWindow(screenWidth, screenHeight, "This ain't a pipboy", false);
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		slSetForeColor(0.1, 0.9, 0.2, 0.4);
		
		//Dibujo jugadores
		slRectangleOutline(J1recX, J1recY, recWidth, recHeight);
		slRectangleOutline(J2recX, J2recY, recWidth, recHeight);
		
		//Dibujo Pelota
		slCircleFill(circleX, circleY, radius, 15);

		//Movement
		if (slGetKey('W'))
			J1recY += speed;
		if (slGetKey('S'))
			J1recY -= speed;	
		if (slGetKey(SL_KEY_UP))
			J2recY += speed;
		if (slGetKey(SL_KEY_DOWN))
			J2recY -= speed;
		//Limit
		if (J1recY >= screenHeight - (recHeight / 2))
			J1recY = screenHeight - (recHeight / 2);
		if (J1recY <= recHeight / 2)
			J1recY = recHeight / 2;
		if (J2recY >= screenHeight - (recHeight / 2))
			J2recY = screenHeight - (recHeight / 2);
		if (J2recY <= recHeight / 2)
			J2recY = recHeight / 2;

		if(movHor)
			circleX += speed;
		else
			circleX -= speed;
		if(movVert)
			circleY += speed;
		else
			circleY -= speed;

		if (circleX <= radius)
			movHor = true;
		if (circleX <= J1recX + radius && circleY == J1recY)
			movHor = true;
		if (circleX >= J2recX - radius && circleY == J2recY)
			movHor = false;
		if (circleX >= screenWidth - radius)
			movHor = false;

		if (circleY <= radius)
			movVert = true;
		if (circleY >= screenHeight - radius)
			movVert = false;



		slRender();
	}
	slClose();
	return 0;
}