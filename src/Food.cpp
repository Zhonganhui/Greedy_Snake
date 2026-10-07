#include "All.h"

bool isOnSnake(const std::deque<Point>& snake, const Point& food) {
  for (int i = 0; i < snake.size(); i++) {
    if (snake[i].X == food.X && snake[i].Y == food.Y) {
      return true;
    }
  }
  return false;
}

void spawnFood(const std::deque<Point>& snake, Point& food, std::mt19937& rng,
               std::uniform_int_distribution<int>& x, std::uniform_int_distribution<int>& y) {
  do {
    food = Point(x(rng), y(rng));  // 声明一个食物对象
  } while (isOnSnake(snake, food));
}
