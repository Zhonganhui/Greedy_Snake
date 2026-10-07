#include "All.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);  // windowsAPI接口，控制编码为UTF-8
  int n = 0;                    // 1.开始游戏，0.退出游戏

  do {
    Menu();  // 菜单选项

    std::cout << "请输入你的选项：";
    std::cin >> n;

    switch (n) {
      case 1: {
        int score = 0;
        Direction dir = Direction::Right;

        std::deque<Point> snake;                            // 声明蛇的对象
        snake.push_front(Point(Width / 2, Height / 2));     // 初始蛇头位置
        snake.push_back(Point(Width / 2 - 1, Height / 2));  // 初始蛇身位置
        snake.push_back(Point(Width / 2 - 2, Height / 2));  // 初始蛇尾位置

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> x(1, Width - 2);   // 食物X的随机数范围
        std::uniform_int_distribution<int> y(1, Height - 2);  // 食物Y的随机数范围

        Point food;
        spawnFood(snake, food, rng, x, y);

        bool running = true;
        while (running) {
          dir = readDirection(dir);
          running = Move(snake, dir, food);

          if (snake[0].X == food.X && snake[0].Y == food.Y) {
            score++;
            spawnFood(snake, food, rng, x, y);
          }

          Interface(snake, food, score);

          Sleep(200);
        }
      } break;
      case 0:
        std::cout << "游戏已退出，欢迎下次再玩！" << std::endl;
        return 0;
      default:
        std::cout << "选项无效，请重新输入：" << std::endl;
        break;
    }
  } while (n);

  return 0;
}
