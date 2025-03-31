#pragma once

// ������ �����
constexpr float FLAP_SPEED = -4.0f; // �������� ������ ������� (������������� �������� �������� �������� �����)
constexpr float GRAVITY = 0.25f;     // ���� ����������, �������������� �� �����

// ��������� �����
constexpr unsigned char BIRD_SIZE = 16;      // ������ ����� (��������, � ��������)
constexpr unsigned char BIRD_SPEED = 1;     // ������� �������������� �������� �����
constexpr unsigned char BIRD_START_X = 37;   // ��������� ������� ����� �� ��� X

// ������� � ���������
constexpr unsigned char FONT_HEIGHT = 32;    // ������ ������ ��� ������
constexpr unsigned char SCREEN_RESIZE = 3;   // ����������� ��������������� ������

// ��������� ����
constexpr unsigned char GAP_SIZE = 64;       // ������ ���������� ����� ������� � ������ ������
constexpr unsigned char PIPE_INDENT = 32;    // ����������� ������ ���� �� ����� � �������
constexpr unsigned char PIPE_SPEED = 1;      // �������� �������� ���� (��������������)
constexpr unsigned short GENERATOR_TIMER_DURATION = 128; // ������� ��������� ����� ���� (� ������)

// ��������� ������ � ���������
constexpr unsigned short GROUND_Y = 288;     // Y-���������� �����
constexpr unsigned short SCREEN_HEIGHT = 320; // ������ ������
constexpr unsigned short SCREEN_WIDTH = 180;  // ������ ������

// ��������� �� (���� ������������)
constexpr unsigned char POPULATION_SIZE = 8; // ������ ��������� ���� � ������ �������� ������ �����
constexpr std::chrono::microseconds FRAME_DURATION(16667);