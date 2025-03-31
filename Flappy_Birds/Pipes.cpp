#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Global.hpp"
#include "Pipes.hpp"

// ����������� �����
Pipes::Pipes(short i_x, unsigned short i_y) :
    direction(rand() % 2),  // ��������� ��������� ����������� (0 - �����, 1 - ����)
    x(i_x),                 // ��������� ��������� ������� �� X
    y_movement_timer(PIPE_SPEED), // ������ �������� (������� ����������)
    y(i_y)                  // ��������� ��������� ������� �� Y
{
    // ������ ���� ������������ - ��� ������������� � ������ �������������
}

// ��������� �������� ����������� �������� �����
bool Pipes::get_direction()
{
    return direction;
}

// ��������, ����� �� ����� �� ����� ������� ������
bool Pipes::is_gone()
{
    return x <= -2 * BIRD_SIZE;  // ����� ��������� "�������", ����� ��������� ������
}

// ��������� ������� X-���������� �����
short Pipes::get_x()
{
    return x;
}

// ��������� ������� Y-���������� �����
unsigned short Pipes::get_y()
{
    return y;
}

// ��������� ����� (� �� ����)
void Pipes::draw(sf::RenderWindow& i_window)
{
    sf::Sprite sprite;
    sf::Texture texture;

    // �������� �������� ����� (������ ������� �� BIRD_SIZE)
    texture.loadFromFile("Images/Pipes" + std::to_string(BIRD_SIZE) + ".png");
    sprite.setTexture(texture);

    // ��������� ������� �����:
    // ������������� ������ � ���������� ������ ����� �������� (2*BIRD_SIZE)
    sprite.setPosition(x, static_cast<float>(y - SCREEN_HEIGHT));
    sprite.setTextureRect(sf::IntRect(2 * BIRD_SIZE, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));
    i_window.draw(sprite);

    // ��������� ������ �����:
    // ���������� ��� �� ������, �� ������ ������� � ����� ��������
    // (����� ����� �������� - 0)
    sprite.setPosition(x, static_cast<float>(GAP_SIZE + y));
    sprite.setTextureRect(sf::IntRect(0, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));
    i_window.draw(sprite);

    // �����������: ���������� ���� ������ � ���� �������� ��� ����� ����
}

// ���������� ��������� �����
void Pipes::update()
{
    // �������� ����� ����� (� �����)
    x -= BIRD_SPEED;

    // �������� ������ ��� ��������� ����������� �������� �� Y
    if (PIPE_INDENT >= y)  // ���� �������� ������� �������
    {
        direction = 1;     // ������ ����������� ����
    }
    else if (y == GROUND_Y - GAP_SIZE - PIPE_INDENT)  // ���� �������� ������ �������
    {
        direction = 0;      // ������ ����������� �����
    }

    // ���������� ������������� ��������� � ������ �������
    if (0 == y_movement_timer)  // ���� ������ �����
    {
        y_movement_timer = PIPE_SPEED;  // ����� �������

        // ��������� Y-���������� � ����������� �� �����������
        if (0 == direction)  // ���� ����������� �����
        {
            y--;
        }
        else  // ���� ����������� ����
        {
            y++;
        }
    }
    else  // ���� ������ ��� �� �����
    {
        y_movement_timer--;  // ��������� ������
    }
}