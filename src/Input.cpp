#include "All.h"

Direction readDirection(Direction current) {
  if (!_kbhit()) return current;

  int ch = _getch();
  // std::cout << "ch = " << ch << "  (hex: " << std::hex << ch << std::dec << ")\n";
  Direction newDir = current;  // 默认不变

  if (ch == 0 || ch == 224) {
    ch = _getch();
    switch (ch) {
      case 72:
        newDir = Direction::Up;
        break;
      case 75:
        newDir = Direction::Left;
        break;
      case 80:
        newDir = Direction::Down;
        break;
      case 77:
        newDir = Direction::Right;
        break;
    }
  }
  switch (ch) {
    case 'w':
    case 'W':
      newDir = Direction::Up;
      break;
    case 'a':
    case 'A':
      newDir = Direction::Left;
      break;
    case 's':
    case 'S':
      newDir = Direction::Down;
      break;
    case 'd':
    case 'D':
      newDir = Direction::Right;
      break;
  }
  if (isOpposite(current, newDir)) {
    return current;
  }
  return newDir;
}
