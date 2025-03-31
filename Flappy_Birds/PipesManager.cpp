#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Global.hpp"
#include "Pipes.hpp"
#include "PipesManager.hpp"

// Конструктор менеджера труб
PipesManager::PipesManager() :
    // Инициализация распределения для случайной Y-координаты труб
    // (между верхним и нижним допустимыми пределами)
    y_distribution(PIPE_INDENT, GROUND_Y - GAP_SIZE - PIPE_INDENT),
    // Инициализация таймера генерации новых труб
    generator_timer(GENERATOR_TIMER_DURATION)
{
    // Пустое тело конструктора - вся инициализация в списке инициализации
}

// Отрисовка всех труб
void PipesManager::draw(sf::RenderWindow& i_window)
{
    for (Pipes& a : pipes)
    {
        a.draw(i_window);  // Отрисовка каждой трубы
    }
}

// Сброс состояния менеджера (при рестарте игры)
void PipesManager::reset()
{
    generator_timer = GENERATOR_TIMER_DURATION;  // Сброс таймера генерации
    pipes.clear();  // Очистка вектора труб
}

// Обновление состояния менеджера и всех труб
void PipesManager::update(std::mt19937_64& i_random_engine)
{
    // Генерация новых труб
    if (0 == generator_timer)  // Если таймер генерации истек
    {
        generator_timer = GENERATOR_TIMER_DURATION;  // Сброс таймера

        // Добавление новой трубы:
        // - X-координата: правый край экрана (SCREEN_WIDTH)
        // - Y-координата: случайное значение в допустимом диапазоне
        pipes.push_back(Pipes(SCREEN_WIDTH, y_distribution(i_random_engine)));
    }
    generator_timer--;  // Уменьшение таймера генерации

    // Обновление всех труб
    for (Pipes& a : pipes)
    {
        a.update();  // Обновление состояния каждой трубы
    }

    // Удаление труб, вышедших за границы экрана
    for (std::vector<Pipes>::iterator a = pipes.begin(); a != pipes.end(); a++)
    {
        if (1 == a->is_gone())  // Если труба вышла за левую границу экрана
        {
            pipes.erase(a);  // Удаление трубы
            break;  // Выход из цикла после удаления (для безопасности итератора)
        }
    }
}

// Получение копии вектора всех труб
std::vector<Pipes> PipesManager::get_pipes()
{
    return pipes;  // Возвращаем копию вектора труб
}