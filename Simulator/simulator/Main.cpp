#include <iostream>
#include <string>

#include <queue>
#include <stack>
#include "API.h"

const int dx[] = {0, -1, 0, 1};
const int dy[] = {1, 0, -1, 0};

#define DIR_UP 0
#define DIR_LEFT 1
#define DIR_DOWN 2
#define DIR_RIGHT 3

#define LOOK_FORWARD 0
#define LOOK_LEFT 1
#define LOOK_BACKWARD 2
#define LOOK_RIGHT 3
#define STOP_MOUSE 4

#define DEST_CENTER 0
#define DEST_SOURCE 1

#define MAZESIDE_SIZE 16

#define START_DIR DIR_UP

/* End parameters to change */

#define INF 99
typedef unsigned char u8;
typedef unsigned int u32;

#define dir_change(x, y) (x + y) % 4

u8 m_dir;
u8 m_x, m_y;
u8 m_destination;
char wall[4] = {'n', 'w', 's', 'e'};
std::queue<std::pair<u32, u32>> q, q_update;
std::stack<std::pair<u32, u32>> s;
struct MazeSquare
{
    bool blocked[4];
    u32 distance_to_dest;
    bool visited;
};

MazeSquare maze[MAZESIDE_SIZE][MAZESIDE_SIZE];

void log(const std::string &text)
{
    std::cerr << text << std::endl;
}

void initFloodfill()
{
    m_dir = START_DIR;
    m_destination = DEST_CENTER;
    m_x = 0;
    m_y = 0;
    for (int i = 0; i < MAZESIDE_SIZE; i++)
    {
        for (int j = 0; j < MAZESIDE_SIZE; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                maze[i][j].blocked[k] = 0;
            }
            maze[i][j].distance_to_dest = 0;
            maze[i][j].visited = 0;
        }
    }
    for (int i = 0; i < MAZESIDE_SIZE; i++)
    {
        API::setWall(0, i, 'w');
        maze[0][i].blocked[DIR_LEFT] = 1;

        API::setWall(MAZESIDE_SIZE - 1, i, 'e');
        maze[MAZESIDE_SIZE - 1][i].blocked[DIR_RIGHT] = 1;

        API::setWall(i, MAZESIDE_SIZE - 1, 'n');
        maze[i][MAZESIDE_SIZE - 1].blocked[DIR_UP] = 1;

        API::setWall(i, 0, 's');
        maze[i][0].blocked[DIR_DOWN] = 1;
    }
}
void floodfillToCenter()
{
    for (u8 i = 0; i < MAZESIDE_SIZE; i++)
    {
        for (u8 j = 0; j < MAZESIDE_SIZE; j++)
        {
            maze[i][j].distance_to_dest = INF;
        }
    }
    for (u8 i = MAZESIDE_SIZE / 2 - 1; i <= MAZESIDE_SIZE / 2; i++)
    {
        for (u8 j = MAZESIDE_SIZE / 2 - 1; j <= MAZESIDE_SIZE / 2; j++)
        {
            maze[i][j].distance_to_dest = 0;
            q.push(std::make_pair(i, j));
        }
    }
    // q.push(std::make_pair(4, 4));
    // maze[4][4].distance_to_dest = 0;
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (u8 i = 0; i < 4; i++)
        {
            if (!maze[u.first][u.second].blocked[i] && maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest == INF)
            {
                maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest = maze[u.first][u.second].distance_to_dest + 1;
                q.push(std::make_pair(u.first + dx[i], u.second + dy[i]));
            }
        }
    }
}

void floodfillToSource()
{
    for (u8 i = 0; i < MAZESIDE_SIZE; i++)
    {
        for (u8 j = 0; j < MAZESIDE_SIZE; j++)
        {
            maze[i][j].distance_to_dest = INF;
        }
    }
    maze[0][0].distance_to_dest = 0;
    q.push(std::make_pair(0, 0));
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (u8 i = 0; i < 4; i++)
        {
            if (!maze[u.first][u.second].blocked[i] && maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest == INF)
            {
                maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest = maze[u.first][u.second].distance_to_dest + 1;
                q.push(std::make_pair(u.first + dx[i], u.second + dy[i]));
            }
        }
    }
}

bool checkFinish(u8 destination)
{
    return (destination == DEST_CENTER && MAZESIDE_SIZE / 2 - 1 <= m_x && m_x <= MAZESIDE_SIZE / 2 && MAZESIDE_SIZE / 2 - 1 <= m_y && m_y <= MAZESIDE_SIZE / 2) || (destination == DEST_SOURCE && m_x == 0 && m_y == 0);
    // return (destination == DEST_CENTER  && m_x == 4 && m_y == 4);
}

void printMaze()
{
    for (int i = 0; i < MAZESIDE_SIZE; i++)
    {
        for (int j = 0; j < MAZESIDE_SIZE; j++)
        {
            int num = maze[i][j].distance_to_dest;
            char text[5];
            sprintf(text, "%d", num);
            API::setText(i, j, text);
        }
    }
}

void printMazeShortest()
{
    while (!s.empty()) {
        auto u = s.top();
        s.pop();
        API::setColor(u.first, u.second, 'G');
    }
}


void updateWalls(u8 m_view[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (i == DIR_DOWN)
            continue;
        u8 new_dir = dir_change(m_dir, i);
        maze[m_x][m_y].blocked[new_dir] = m_view[i];
        if (m_view[i])
        {
            API::setWall(m_x, m_y, wall[new_dir]);
        }
    }
    maze[m_x][m_y].visited = 1;
}

u8 minDistanceNeighbort(u8 m_x, u8 m_y)
{
    u8 min_dist = INF;
    for (int i = 0; i < 4; i++)
    {
        if (!maze[m_x][m_y].blocked[i] && maze[m_x + dx[i]][m_y + dy[i]].distance_to_dest < min_dist)
        {
            min_dist = maze[m_x + dx[i]][m_y + dy[i]].distance_to_dest;
        }
    }
    return min_dist;
}

u8 bestDir(u8 m_x, u8 m_y, u8 current_dist)
{
    u8 best_dir = LOOK_FORWARD;
    // ưu tiên đi thẳng nếu các ô cung quanh ô hiện tại có cùng giá trị
    for (int i = 3; i >= 0; i--)
    {
        u8 new_dir = dir_change(m_dir, i);
        if (!maze[m_x][m_y].blocked[new_dir] && maze[m_x + dx[new_dir]][m_y + dy[new_dir]].distance_to_dest < current_dist)
        {
            best_dir = i;
        }
    }
    return best_dir;
}
void floodfill(u8 x, u8 y)
{
    q_update.push(std::make_pair(x, y));
    while (!q_update.empty())
    {
        auto u = q_update.front();
        q_update.pop();
        u8 minimunValue = minDistanceNeighbort(u.first, u.second);
        if (maze[u.first][u.second].distance_to_dest <= minimunValue)
        {
            maze[u.first][u.second].distance_to_dest = minimunValue + 1;
            for (int i = 0; i < 4; i++)
            {
                if (!maze[u.first][u.second].blocked[i])
                {
                    q_update.push(std::make_pair(u.first + dx[i], u.second + dy[i]));
                }
            }
        }
    }
}
u8 getNextCommand(u8 forward_blocked, u8 left_blocked, u8 right_blocked)
{
    // mặc định hướng bên dưới mouse = 0
    u8 view_blocked[4] = {forward_blocked, left_blocked, 0, right_blocked};
    if (checkFinish(m_destination))
    {
        // m_destination = 1 - m_destination;
        // if (m_destination) {
        //     floodfillToSource();
        // }
        // else floodfillToCenter();
        return STOP_MOUSE;
    }
    if (!maze[m_x][m_y].visited)
    {
        s.push(std::make_pair(m_x, m_y)); // lưu ô đã đi vào stack
        updateWalls(view_blocked);
    }

    u8 best_dist = minDistanceNeighbort(m_x, m_y);
    if (best_dist >= maze[m_x][m_y].distance_to_dest)
    {
        floodfill(m_x, m_y);
    }
    u8 best_dir = bestDir(m_x, m_y, maze[m_x][m_y].distance_to_dest);
    return best_dir;
}
void goForward()
{
    m_x += dx[m_dir];
    m_y += dy[m_dir];
}
void controll()
{
    u8 forward_blocked = API::wallFront() ? 1 : 0;
    u8 left_blocked = API::wallLeft() ? 1 : 0;
    u8 right_blocked = API::wallRight() ? 1 : 0;

    u8 command = getNextCommand(forward_blocked, left_blocked, right_blocked);

    if (command == 0)
    {
        API::moveForward();
    }
    if (command == 1)
    {
        API::turnLeft();
        API::moveForward();
    }
    if (command == 2)
    {
        API::turnLeft();
        API::turnLeft();
        API::moveForward();
    }
    if (command == 3)
    {
        API::turnRight();
        API::moveForward();
    }
    if (command == 4)
    {
        log("Done!");
        printMazeShortest();
        return;
        // Để lần sau gọi câu lệnh goForward thì giá trị m_x m_y ko bị đổi vì khi đến đích xe sẽ dừng mà giá trị ô (m_x, m_y) giữ nguyên
        m_x -= dx[m_dir];
        m_y -= dy[m_dir];
    }
    m_dir = dir_change(m_dir, command);
    goForward();

    if (maze[m_x][m_y].visited) {
        s.pop();
    }
}
int main(int argc, char *argv[])
{
    log("Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "start");
    initFloodfill();
    floodfillToCenter();
    while (true)
    {
        controll();
        printMaze();
    }
}
