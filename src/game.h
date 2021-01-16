#pragma once

#include "gameobject.h"
#include "player.h"

using namespace std;

class Game {

	int game_state, object_counter, score;
	float last_enemy_spawn_time, last_kamikaze_spawn_time;
	float game_time_started, pressed_space;
	GameObject * game_objects[1000];
	Player * player;

	void updateStartScreen();
	void drawStartScreen();

	void updateGame();
	void drawGame();

	void updateGameOverScreen();
	void drawGameOverScreen();

	bool checkCollision(GameObject * ob1, GameObject * ob2);

public:

	Game();
	~Game();

	void update();
	void draw();

	void addObject(GameObject * object);

};