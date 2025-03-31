#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Global.hpp"
#include "Pipes.hpp"
#include "Bird.hpp"

// Конструктор класса Bird - вызывает reset() для инициализации
Bird::Bird()
{
    reset();
}

// Возвращает состояние птицы (мертва/жива)
bool Bird::get_dead()
{
    return dead;
}

// Вычисляет разницу между позицией птицы и ближайшим промежутком между трубами
float Bird::get_gap_difference(std::vector<Pipes> i_pipes)
{
    for (Pipes& a : i_pipes)
    {
        // Проверяем, находится ли птица в зоне текущей трубы
        if (x < a.get_x() + 2 * BIRD_SIZE)
        {
            // Возвращаем разницу между центром промежутка и позицией птицы
            return GAP_SIZE + a.get_y() - BIRD_SIZE - y;
        }
    }

    return 0;
}

// Возвращает текущую Y-координату птицы
float Bird::get_y()
{
    return y;
}

// Возвращает "фитнес" птицы (пройденное расстояние)
unsigned Bird::get_fitness()
{
    return fitness;
}

// Возвращает счет (количество пройденных труб)
unsigned short Bird::get_score()
{
    return score;
}

// Отрисовка птицы
void Bird::draw(sf::RenderWindow& i_window)
{
    sf::Sprite sprite;
    sf::Texture texture;

    // Загрузка текстуры птицы (размер зависит от BIRD_SIZE)
    texture.loadFromFile("Images/Bird" + std::to_string(BIRD_SIZE) + ".png");
    sprite.setTexture(texture);

    // Установка позиции и текстуры (анимация в зависимости от скорости и состояния)
    sprite.setPosition(x, round(y));
    sprite.setTextureRect(sf::IntRect(BIRD_SIZE * (0 >= vertical_speed), BIRD_SIZE * dead, BIRD_SIZE, BIRD_SIZE));

    i_window.draw(sprite);
}

// Сброс состояния птицы к начальным значениям
void Bird::reset()
{
    dead = 0; // Птица жива
    vertical_speed = 0; // Сброс вертикальной скорости
    y = 0.5f * (GROUND_Y - BIRD_SIZE); // Стартовая позиция по Y (середина экрана)
    x = BIRD_START_X; // Стартовая позиция по X
    fitness = 0; // Сброс фитнес-значения
    score = 0; // Сброс счета
}

// Обновление состояния птицы
void Bird::update(bool i_move, std::vector<Pipes> i_pipes)
{
    // Применяем гравитацию
    vertical_speed += GRAVITY;
    y += vertical_speed;

    if (0 == dead) // Если птица жива
    {
        // Проверка столкновений с трубами
        for (Pipes& a : i_pipes)
        {
            // Если птица в зоне трубы по X
            if (x < a.get_x() + 2 * BIRD_SIZE && x > a.get_x() - BIRD_SIZE)
            {
                // Если птица столкнулась с верхней или нижней трубой
                if (y < a.get_y() || y > GAP_SIZE + a.get_y() - BIRD_SIZE)
                {
                    dead = 1; // Птица погибла
                    vertical_speed = 0; // Остановка движения
                }
            }
            // Проверка прохождения трубы (увеличение счета)
            // Работает только если скорость птицы не слишком высокая
            else if (x == a.get_x() + 2 * BIRD_SIZE)
            {
                score++;
            }
        }
    }

    // Проверка столкновения с землей
    if (y >= GROUND_Y - BIRD_SIZE)
    {
        dead = 1; // Птица погибла
        vertical_speed = 0; // Остановка движения
        y = GROUND_Y - BIRD_SIZE; // Фиксация на земле
    }

    // Обновление фитнес-значения (если птица жива)
    if (0 == dead)
    {
        fitness += BIRD_SPEED;
    }
    // Если птица мертва и нужно двигать ее влево
    else if (1 == i_move)
    {
        x = std::max(-BIRD_SIZE, x - BIRD_SPEED); // Движение влево, но не за пределы экрана
    }
}