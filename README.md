贪吃蛇项目描述
项目概况

一个用 C++17 编写的 Windows 控制台贪吃蛇游戏，使用 CMake 构建，VS Code 开发。
技术栈

    语言：C++17

    构建：CMake

    平台：Windows（依赖 <windows.h>、<conio.h>）

    渲染：控制台字符画，每帧拼成字符串，用 SetConsoleCursorPosition 回位覆盖输出

    输入：_kbhit() + _getch() 非阻塞读取，支持 WASD 和方向键

    随机数：std::mt19937 + std::uniform_int_distribution

游戏功能

已完成：

    25 × 100 的棋盘，# 为墙

    蛇初始 3 节，0 为蛇头，o 为蛇身

    蛇整体移动（加头删尾）

    WASD 和方向键转向

    禁止 180 度反向

    食物随机生成（*），且不会生成在蛇身上

    吃到食物：加分、变长、食物重新生成

    撞墙、撞自己：游戏结束

    每局方向、分数、蛇、食物都重置

    棋盘下方显示分数

    控制台编码设为 UTF-8，中文正常显示

未完成：

    游戏结束后显示“最终分数”，等待按键再回菜单

    速度随分数加快

    暂停

    最高分保存

    颜色

    跨平台

项目结构
text

Greedy_Snake/
├── CMakeLists.txt
├── include/
│   └── All.h              // 常量、Point、Direction、函数声明
└── src/
    ├── Main.cpp           // 入口，菜单循环，一局游戏的主循环
    ├── Menu.cpp           // 菜单打印
    ├── Interface.cpp      // 拼帧、渲染
    ├── Move.cpp           // 蛇的移动、撞墙、撞自己、isOpposite
    ├── Food.cpp           // isOnSnake、spawnFood
    └── Input.cpp          // readDirection，键盘解析 + 反向保护

核心设计

数据

    Point { int X, Y; }：坐标

    std::deque<Point> snake：蛇，front() 是蛇头，back() 是蛇尾

    Point food：食物位置

    Direction dir：当前方向

    int score：分数

模块职责
文件	职责
Main.cpp	主循环：读方向 → 移动 → 判断吃食物 → 渲染 → 等待
Input.cpp	readDirection：非阻塞读取，解析按键，反向保护
Move.cpp	Move：算新头 → 判撞墙 → 加头 → 判吃食物决定删不删尾 → 判撞自己；isOpposite
Food.cpp	isOnSnake 判断坐标是否在蛇身；spawnFood 反复随机直到不在蛇身上
Interface.cpp	每帧拼一个字符串，回位 (0,0) 后一次输出，末尾附分数
Menu.cpp	打印开始/退出菜单

关键技巧

    拼帧 + 覆盖：每帧把整个画面拼成一个 std::string，光标回 (0,0) 后一次 cout，避免闪烁和滚动。

    加头删尾：移动 = push_front(新头) + pop_back()，O(1)。

    吃到食物不删尾：蛇变长的本质就是少一次 pop_back()。

    状态跨帧：蛇、食物、方向、分数都定义在 case 1 里、while 外面，只初始化一次。

    nextDir 缓冲：按键只改“下一步方向”，每帧开始才应用，避免同帧内方向乱跳。

走过的坑（学习记录）

    头文件定义全局变量 → multiple definition，改成局部或 extern。

    角落重复输出 → 两个独立 if 改成 if / else if。

    == 写成 = → 判断变赋值。

    Move 里 for 循环跑 size() 次 → 一次移动只需一次加头删尾。

    isOpposite 逻辑反了 → 表现为“只能左右动”。

    spawnFood 的 rng 传值 → 引擎状态没推进，改成引用。

    撞自己遍历从 i = 3 开始 → 蛇长够大时漏判，严格来说应从 i = 1。

    编码问题：VS Code 终端正常，双击 exe 乱码 → SetConsoleOutputCP(CP_UTF8)。

一句话总结

    一个模块化拆分的 Windows 控制台贪吃蛇，用“拼帧覆盖”做渲染，用 deque 加头删尾做移动，用非阻塞键盘输入做控制，已完成移动、转向、吃食物、变长、计分、撞墙、撞自己等核心玩法，处于体验优化阶段。
