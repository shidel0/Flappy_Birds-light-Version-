#pragma once
#include "Global.hpp"
class Bird
{
    bool dead;

    float vertical_speed;
    float y;

    short x;

    unsigned fitness;

    unsigned short score;
public:
    Bird();

    bool get_dead();
    float get_gap_difference(std::vector<Pipes> i_pipes);
    float get_y();
    unsigned get_fitness();
    unsigned short get_score();
    void draw(sf::RenderWindow& i_window);
    void reset();
    void update(bool i_move, std::vector<Pipes> i_pipes);

    void jump() {
        if (!dead) {  // Прыгать можно только если птичка жива
            vertical_speed = FLAP_SPEED;  // Задаем скорость вверх
        }
    }


    // Добавим оператор сравнения для сортировки
    bool operator<(const Bird& other) const {
        return fitness < other.fitness;
    }
    bool operator>(const Bird& other) const {
        return fitness > other.fitness;
    }
};