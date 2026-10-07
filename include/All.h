#pragma once
#include <iostream>
#include <windows.h>
#include <deque>
#include <conio.h>
#include <random>

const int Height = 25;        // 范围y：高
const int Width = 100;        // 范围x：宽
const char Space_ch = '#';    // 墙
const char S_front_ch = '0';  // 蛇头
const char S_back_ch = 'o';   // 蛇身
const char S_food_ch = '*';   // 食物

// 结构体-蛇和食物为点坐标
struct Point {
  int X;
  int Y;
  Point(int x = Width / 2, int y = Height / 2) : X(x), Y(y) {};
};

enum class Direction { Up, Down, Left, Right };

void Menu();                                                            // 菜单
void Interface(std::deque<Point>& snake, const Point& f, int score);    // 界面
bool Move(std::deque<Point>& snake, Direction dir, const Point& food);  // 蛇的移动
Direction readDirection(Direction current);
bool isOnSnake(const std::deque<Point>& snake, const Point& food);
void spawnFood(const std::deque<Point>& snake, Point& food, std::mt19937& rng,
               std::uniform_int_distribution<int>& x, std::uniform_int_distribution<int>& y);
bool isOpposite(Direction a, Direction b);
