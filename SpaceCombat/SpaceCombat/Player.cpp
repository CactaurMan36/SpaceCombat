#include "Player.h"


Player::Player(void)
{
}

Player::Player(glm::vec4 pos, Quaternion rot)
{
	position = pos;
	rotation = rot;
}


Player::~Player(void)
{
}

void Player::display()
{
	//use gl drawing for position and rotation

	//display position, figure out shape, then draw based on that shape
	glBegin(GL_POLYGON)
	{
		glVertex3f(
	}


	//change orientation to matrix form
	glm::mat4 rotationMatrix = Quaternion::quaternionToMatrix(rotation);
}

void Player::getInput()
{
	//input from arrow keys, implementation can be updated later
	if(glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
	{
		velocity += glm::vec4(0, 1, 0, 0);
	}

	if(glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
	{
		velocity += glm::vec4(0, -1, 0, 0);
	}

	if(glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
	{
		velocity += glm::vec4(-1, 0, 0, 0);
	}

	if(glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
	{
		velocity += glm::vec4(1, 0, 0, 0);
	}

	//mouse for rotation?
}

//find velocity and apply to position to get new position
void Player::move()
{
	position += velocity;
	
}

//called when a player takes damage
void Player::damage(float distance)
{
	float dmg = 900.0f / (distance * distance);
	hitPoints -= dmg;
}

bool Player::isDead()
{
	return (hitPoints <= 0);
}
