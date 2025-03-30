#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


#include "Global.hpp"
#include "Pipes.hpp"
#include "Bird.hpp"

Bird::Bird()
{
	reset();
}

bool Bird::get_dead()
{
	return dead;
}

float Bird::get_gap_difference(std::vector<Pipes> i_pipes)
{
	for (Pipes& a : i_pipes)
	{
		//I made the width of the pipes twice the size of the bird.
		if (x < a.get_x() + 2 * BIRD_SIZE)
		{
			return GAP_SIZE + a.get_y() - BIRD_SIZE - y;
		}
	}

	return 0;
}

float Bird::get_y()
{
	return y;
}

unsigned Bird::get_fitness()
{
	return fitness;
}

unsigned short Bird::get_score()
{
	return score;
}

void Bird::draw(sf::RenderWindow& i_window)
{
	sf::Sprite sprite;
	sf::Texture texture;

	texture.loadFromFile("Images/Bird" + std::to_string(BIRD_SIZE) + ".png");
	sprite.setTexture(texture);

	sprite.setPosition(x, round(y));
	sprite.setTextureRect(sf::IntRect(BIRD_SIZE * (0 >= vertical_speed), BIRD_SIZE * dead, BIRD_SIZE, BIRD_SIZE));

	i_window.draw(sprite);
}

void Bird::reset()
{
	dead = 0;

	vertical_speed = 0;
	y = 0.5f * (GROUND_Y - BIRD_SIZE);

	x = BIRD_START_X;

	fitness = 0;

	score = 0;
}

void Bird::update(bool i_move, std::vector<Pipes> i_pipes)
{
	vertical_speed += GRAVITY;
	y += vertical_speed;

	if (0 == dead)
	{
		/*if (0 <= vertical_speed && 0 <= y && 1 == do_ai_stuff(i_pipes))
		{
			vertical_speed = FLAP_SPEED;
		}*/

		for (Pipes& a : i_pipes)
		{
			if (x < a.get_x() + 2 * BIRD_SIZE && x > a.get_x() - BIRD_SIZE)
			{
				if (y < a.get_y() || y > GAP_SIZE + a.get_y() - BIRD_SIZE)
				{
					dead = 1;

					vertical_speed = 0;
				}
			}
			//This doesn't work when the bird is faster.
			//So don't make it faster.
			else if (x == a.get_x() + 2 * BIRD_SIZE)
			{
				score++;
			}
		}
	}

	if (y >= GROUND_Y - BIRD_SIZE)
	{
		dead = 1;

		vertical_speed = 0;
		y = GROUND_Y - BIRD_SIZE;
	}

	if (0 == dead)
	{
		fitness += BIRD_SPEED;
	}
	else if (1 == i_move)
	{
		x = std::max(-BIRD_SIZE, x - BIRD_SPEED);
	}
}

