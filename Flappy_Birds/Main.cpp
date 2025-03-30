#include <array>
#include <chrono>
#include <random>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


#include "Pipes.hpp"
#include "Bird.hpp"
#include "DrawText.hpp"
#include "Global.hpp"
#include "Pipes.hpp"
#include "PipesManager.hpp"

unsigned short read_record()
{
	unsigned short record = 0;
	std::ifstream file("record.txt");

	if (file.is_open()) {
		file >> record;
		file.close();
	}

	return record;
}

// Функция для сохранения рекорда в файл
void save_record(unsigned record)
{
	std::ofstream file("record.txt");
	if (file.is_open()) {
		file << record;
		file.close();

	}
}


int main()
{

	unsigned short record_score = read_record();
	std::array<Bird, POPULATION_SIZE> birds;

	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	std::mt19937_64 random_engine(std::chrono::system_clock::now().time_since_epoch().count());

	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(2 * SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Sprite background_sprite;
	sf::Sprite ground_sprite;

	sf::Texture background_texture;
	background_texture.loadFromFile("Images/Background.png");

	sf::Texture ground_texture;
	ground_texture.loadFromFile("Images/Ground.png");

	PipesManager pipes_manager;

	srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));


	background_sprite.setTexture(background_texture);

	ground_sprite.setPosition(0, GROUND_Y);
	ground_sprite.setTexture(ground_texture);

	previous_time = std::chrono::steady_clock::now();

	bool game_over = false;
	bool start_screen = true;

	bool all_dead;
	// звук взмаха крыльев
	sf::SoundBuffer jumpSoundBuffer;
	jumpSoundBuffer.loadFromFile("audio/jump.wav");
	sf::Sound jumpSound;
	jumpSound.setBuffer(jumpSoundBuffer);

	jumpSound.setVolume(10.0f); // 30% от максимальной громкости


	// Изображение смерти
	sf::RectangleShape overlay(sf::Vector2f(2 * SCREEN_WIDTH, SCREEN_HEIGHT));
	overlay.setFillColor(sf::Color(0, 0, 0, 240));




	while (1 == window.isOpen())
	{
		//Someone said I should use chrono more often, and I did.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();

					break;
				}
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space) {
						if (start_screen) {
							start_screen = false; // Убираем стартовый экран
						}
						else if (!game_over) { // Прыжок только во время игры
							for (Bird& bird : birds) {
								if (!bird.get_dead()) {
									jumpSound.play();
									bird.jump();
								}
							}
						}
					}

				}

			}

			for (unsigned short a = 0; a < 1; a++)
			{
				all_dead = true;

				for (Bird& bird : birds)
				{
					if (!bird.get_dead())
					{

						all_dead = false;
						break;
					}
				}

				if (!all_dead && !game_over && !start_screen) {

					pipes_manager.update(random_engine);
					for (Bird& bird : birds) {
						bird.update(1, pipes_manager.get_pipes());
					}
				}
				else if (all_dead) {

					game_over = true;

					// Обработка рестарта
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

						game_over = false;
						std::sort(birds.begin(), birds.end(), std::greater());
						for (Bird& bird : birds) {
							bird.reset();
						}
						pipes_manager.reset();
					}
				}
			}

			if (FRAME_DURATION > lag)
			{
				unsigned short max_score = std::max_element(birds.begin(), birds.end())->get_score();

				//We make rectangle.
				sf::RectangleShape gui_background(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
				//We make rectangle black.
				gui_background.setFillColor(sf::Color(0, 0, 0));
				//We put rectangle right.
				gui_background.setPosition(SCREEN_WIDTH, 0);
				//Like I said, I'm explaining ONLY the important things.

				if (record_score < max_score)
				{
					record_score = max_score;
					save_record(record_score);
				}

				window.clear();
				window.draw(background_sprite);

				pipes_manager.draw(window);

				for (Bird& bird : birds)
				{
					bird.draw(window);
				}

				window.draw(ground_sprite);

				draw_text(1, 1, 0, 0, BIRD_SIZE, std::to_string(max_score), window);

				window.draw(gui_background);

				draw_text(0, 1, 1, SCREEN_WIDTH, 0, "Record\nscore\n" + std::to_string(record_score), window);


				if (start_screen)
				{
					// Стартовый экран
					sf::RectangleShape overlay(sf::Vector2f(2 * SCREEN_WIDTH, SCREEN_HEIGHT));
					overlay.setFillColor(sf::Color(0, 0, 0, 180));
					window.draw(overlay);

					draw_text(0, 1, 1, 100, -50, "FLAPPY BIRD", window);
					draw_text(0, 1, 1, 100, 15, "Press\nSPACE\n to start", window);
				}
				else if (game_over) {


					window.draw(overlay);
					draw_text(0, 1, 1, 100, -50, "GAME OVER", window);
					// Инструкция для рестарта (белый, поменьше)
					draw_text(0, 1, 1, 100, 15, "Press\nSPACE\n to restart", window);
				}

				window.display();
			}
		}
	}
}