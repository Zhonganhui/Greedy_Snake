#include "All.h"

// 判断方向不能180度反转
bool isOpposite(Direction a, Direction b) {
  switch (a) {
    case Direction::Up:
      return b == Direction::Down;
    case Direction::Down:
      return b == Direction::Up;
    case Direction::Left:
      return b == Direction::Right;
    case Direction::Right:
      return b == Direction::Left;
  }
  return false;
}

bool Move(std::deque<Point>& snake, Direction dir, const Point& food) {
  // 蛇的移动

  Point head = snake.front();
  switch (dir) {
    case Direction::Up:
      head.Y--;
      break;
    case Direction::Down:
      head.Y++;
      break;
    case Direction::Left:
      head.X--;
      break;
    case Direction::Right:
      head.X++;
      break;
  }
  if (head.X < 1 || head.X > Width - 2 || head.Y < 1 || head.Y > Height - 2) {
    return false;  // 蛇撞墙
  }
  snake.push_front(head);

  if (!(head.X == food.X && head.Y == food.Y)) {
    snake.pop_back();
  }

  for (int i = 3; i < snake.size(); i++) {
    if (head.X == snake[i].X && head.Y == snake[i].Y) {
      return false;
    }
  }

  return true;
}
