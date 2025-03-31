#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Global.hpp"
#include "Pipes.hpp"

// Конструктор трубы
Pipes::Pipes(short i_x, unsigned short i_y) :
    direction(rand() % 2),  // Случайное начальное направление (0 - вверх, 1 - вниз)
    x(i_x),                 // Установка начальной позиции по X
    y_movement_timer(PIPE_SPEED), // Таймер движения (частота обновления)
    y(i_y)                  // Установка начальной позиции по Y
{
    // Пустое тело конструктора - вся инициализация в списке инициализации
}

// Получение текущего направления движения трубы
bool Pipes::get_direction()
{
    return direction;
}

// Проверка, вышла ли труба за левую границу экрана
bool Pipes::is_gone()
{
    return x <= -2 * BIRD_SIZE;  // Труба считается "ушедшей", когда полностью скрыта
}

// Получение текущей X-координаты трубы
short Pipes::get_x()
{
    return x;
}

// Получение текущей Y-координаты трубы
unsigned short Pipes::get_y()
{
    return y;
}

// Отрисовка трубы (и ее пары)
void Pipes::draw(sf::RenderWindow& i_window)
{
    sf::Sprite sprite;
    sf::Texture texture;

    // Загрузка текстуры трубы (размер зависит от BIRD_SIZE)
    texture.loadFromFile("Images/Pipes" + std::to_string(BIRD_SIZE) + ".png");
    sprite.setTexture(texture);

    // Отрисовка ВЕРХНЕЙ трубы:
    // Позиционируем спрайт и используем правую часть текстуры (2*BIRD_SIZE)
    sprite.setPosition(x, static_cast<float>(y - SCREEN_HEIGHT));
    sprite.setTextureRect(sf::IntRect(2 * BIRD_SIZE, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));
    i_window.draw(sprite);

    // Отрисовка НИЖНЕЙ трубы:
    // Используем тот же спрайт, но меняем позицию и часть текстуры
    // (левая часть текстуры - 0)
    sprite.setPosition(x, static_cast<float>(GAP_SIZE + y));
    sprite.setTextureRect(sf::IntRect(0, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));
    i_window.draw(sprite);

    // Оптимизация: используем один спрайт и одну текстуру для обеих труб
}

// Обновление состояния трубы
void Pipes::update()
{
    // Движение трубы влево (к птице)
    x -= BIRD_SPEED;

    // Проверка границ для изменения направления движения по Y
    if (PIPE_INDENT >= y)  // Если достигли верхней границы
    {
        direction = 1;     // Меняем направление вниз
    }
    else if (y == GROUND_Y - GAP_SIZE - PIPE_INDENT)  // Если достигли нижней границы
    {
        direction = 0;      // Меняем направление вверх
    }

    // Обновление вертикального положения с учетом таймера
    if (0 == y_movement_timer)  // Если таймер истек
    {
        y_movement_timer = PIPE_SPEED;  // Сброс таймера

        // Изменение Y-координаты в зависимости от направления
        if (0 == direction)  // Если направление вверх
        {
            y--;
        }
        else  // Если направление вниз
        {
            y++;
        }
    }
    else  // Если таймер еще не истек
    {
        y_movement_timer--;  // Уменьшаем таймер
    }
}