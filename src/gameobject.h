#pragma once

#include <string>

using namespace std;

class GameObject {

	float pos_x, pos_y, size_x, size_y, orientation;
	bool terminate;
	string texture;

public:

	GameObject(float pos_x, float pos_y, float size_x, float size_y, float orientation, string texture);
	virtual ~GameObject();

	virtual void update();
	virtual void draw();

	float getPosX();
	float getPosY();
	float getSizeX();
	float getSizeY();
	float getOrientation();
	float getRadius();
	bool getTerminate();
	string getTexture();

	void setPosX(float pos_x);
	void setPosY(float pos_y);
	void setTerminate(bool terminate);

	virtual bool collidable();

};