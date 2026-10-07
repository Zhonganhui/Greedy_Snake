#include "All.h"

// 界面
void Interface(std::deque<Point>& snake, const Point& f,
               int score) {  // 将整个一帧画面拼成一个字符串打印
  char cell;
  std::string str;

  // 将光标移动到(0,0)
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD Space;
  Space.X = 0;                                // 行
  Space.Y = 0;                                // 列
  SetConsoleCursorPosition(hConsole, Space);  // WindowsAPI，将光标移动到指定位置
  str.clear();                                // 清空字符串，下次继续写入

  for (int i = 0; i < Height; i++) {   // 高
    for (int j = 0; j < Width; j++) {  // 宽

      bool isBody = false;
      for (int k = 1; k < snake.size(); k++) {
        if (snake[k].X == j && snake[k].Y == i) {
          isBody = true;
          break;
        }
      }

      if (i == 0 || i == Height - 1)
        cell = Space_ch;  // 打印上下的墙
      else if (j == 0 || j == Width - 1)
        cell = Space_ch;  // 打印左右的墙
      else if (snake.front().X == j && snake.front().Y == i)
        cell = S_front_ch;  // 打印蛇头
      else if (isBody)
        cell = S_back_ch;  // 打印蛇尾
      else if (f.X == j && f.Y == i)
        cell = S_food_ch;  // 打印食物
      else
        cell = ' ';  // 打印空格

      str += cell;
    }
    str += '\n';
  }
  str += "分数为：" + std::to_string(score) + '\n';
  std::cout << str << '\n';
}
