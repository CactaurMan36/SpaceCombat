#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include "Quaternion.h"
#include <glm/glm.hpp>

class Player
{
public:
	float hitPoints;
	int turnsForLaser;
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 forward; //represents the forward vector of the ship
	Quaternion rotation;
	
	Player(void);
	Player(glm::vec4 pos, Quaternion rot);
	~Player(void);
	void display();
	void getInput();
	void move();
	void damage(float distance);
	bool isDead();
};

