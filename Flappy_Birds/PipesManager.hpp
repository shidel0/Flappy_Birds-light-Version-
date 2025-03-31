#pragma once  // Защита от множественного включения заголовочного файла

#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include "Pipes.hpp"  // Включаем заголовок класса Pipes для использования

class PipesManager
{
private:
    // Таймер для генерации новых труб (в кадрах)
    unsigned short generator_timer;

    // Распределение для случайной Y-координаты генерации труб
    std::uniform_int_distribution<unsigned short> y_distribution;

    // Контейнер для хранения всех активных труб
    std::vector<Pipes> pipes;

public:
    // Конструктор - инициализирует распределение и таймер
    PipesManager();

    // Отрисовывает все трубы в указанном окне
    void draw(sf::RenderWindow& i_window);

    // Сбрасывает состояние менеджера (очищает трубы и сбрасывает таймер)
    void reset();

    // Обновляет состояние всех труб и генерирует новые
    // Принимает генератор случайных чисел для определения позиции новых труб
    void update(std::mt19937_64& i_random_engine);

    // Возвращает копию вектора всех текущих труб
    // (используется для проверки столкновений в классе Bird)в
    std::vector<Pipes> get_pipes();
};