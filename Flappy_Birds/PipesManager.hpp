#pragma once
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Pipes.hpp"

class PipesManager
{
	unsigned short generator_timer;

	std::uniform_int_distribution<unsigned short> y_distribution;

	std::vector<Pipes> pipes;
public:
	PipesManager();

	void draw(sf::RenderWindow& i_window);
	void reset();
	void update(std::mt19937_64& i_random_engine);

	std::vector<Pipes> get_pipes();
};