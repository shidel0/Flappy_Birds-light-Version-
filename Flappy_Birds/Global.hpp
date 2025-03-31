#pragma once

// Физика птицы
constexpr float FLAP_SPEED = -4.0f; // Скорость взмаха крыльев (отрицательное значение означает движение вверх)
constexpr float GRAVITY = 0.25f;     // Сила гравитации, воздействующая на птицу

// Параметры птицы
constexpr unsigned char BIRD_SIZE = 16;      // Размер птицы (вероятно, в пикселях)
constexpr unsigned char BIRD_SPEED = 1;     // Базовая горизонтальная скорость птицы
constexpr unsigned char BIRD_START_X = 37;   // Начальная позиция птицы по оси X

// Графика и интерфейс
constexpr unsigned char FONT_HEIGHT = 32;    // Высота шрифта для текста
constexpr unsigned char SCREEN_RESIZE = 3;   // Коэффициент масштабирования экрана

// Параметры труб
constexpr unsigned char GAP_SIZE = 64;       // Размер промежутка между верхней и нижней трубой
constexpr unsigned char PIPE_INDENT = 32;    // Минимальный отступ труб от земли и потолка
constexpr unsigned char PIPE_SPEED = 1;      // Скорость движения труб (горизонтальная)
constexpr unsigned short GENERATOR_TIMER_DURATION = 128; // Частота генерации новых труб (в кадрах)

// Параметры экрана и окружения
constexpr unsigned short GROUND_Y = 288;     // Y-координата земли
constexpr unsigned short SCREEN_HEIGHT = 320; // Высота экрана
constexpr unsigned short SCREEN_WIDTH = 180;  // Ширина экрана

// Параметры ИИ (если используется)
constexpr unsigned char POPULATION_SIZE = 8; // Размер популяции если я захочу добавить онлайн режим
constexpr std::chrono::microseconds FRAME_DURATION(16667);