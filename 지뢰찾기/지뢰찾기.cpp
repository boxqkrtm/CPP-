// 지뢰찾기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <time.h>

//테두리에 무조건 숫자가 있을때까지 염

using namespace std;

class Mine
{
public:
    vector< vector <int> > minefield;//지뢰 
    vector< vector<string> > viewfield;//화면
    int usercolor = 1;
    Mine() {
        //9x9 mine
        srand(time(NULL));
        for (int i = 0; i < 9; i++)
        {
            vector<int> temp1;
            for (int j = 0; j < 9; j++)
            {
                temp1.push_back(rand()%15);
            }
            minefield.push_back(temp1);
        }
        for (int i = 0; i < 9; i++)
        {
            vector<string> temp1;
            for (int j = 0; j < 9; j++)
            {
                temp1.push_back("___");
            }
            viewfield.push_back(temp1);
        }
    }
    void print(int x, int y)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (i == y && j == x)
                {
                    if(usercolor == 1)cout << "□.";
                    else cout << "■.";
                    usercolor *= -1;
                }
                else
                {
                    cout << viewfield[i][j];
                }
                
            }
            cout << endl;
        }
    }
    bool select(int x, int y)
    {
        if (minefield[y][x] == 1)
        {
            cout << "boom" << endl;
            return false;
        }
        else if(viewfield[y][x] == "___")
        {
            //viewfield[y][x] = "[ ]";
            bool visit[9][9];
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    visit[i][j] = false;
            //근처열기
            dfs(x, y, visit);
        }
        return true;
    }

    void flag(int x, int y)
    {
        if (viewfield[y][x] == "___")
        {
            viewfield[y][x] = "△.";
        }
        else if (viewfield[y][x] == "△.")
        {
            viewfield[y][x] = "___";
        }

        bool isClear = true;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (minefield[i][j] == 1 && viewfield[i][j] != "△.")
                {
                    isClear = false;
                }
                if (minefield[i][j] == 0 && viewfield[i][j] == "△.")
                {
                    isClear = false;
                }
            }
        }
        if (isClear == true)
        {
            cout << " clear " << endl;
            system("PAUSE");
            system("PAUSE");
            system("PAUSE");
            system("PAUSE");
            system("PAUSE");
        }
        
    }
    void dfs(int x, int y, bool visit[][9])
    {
        int dx[5] = { 0, 0, 1 ,0 ,-1 };
        int dy[5] = { 0, 1, 0 ,-1 ,0 };
        int dx2[8] = { 0, 1 ,0 ,-1,1 ,-1 ,-1, 1};
        int dy2[8] = { 1, 0 ,-1 ,0 ,1,-1 ,1, -1};
        for (int i = 0; i < 5; i++)
        {
            int isSideBomb = 0;//상하좌우대각선에 폭탄 있는지 검사
            if (x + dx[i] < 0 || x + dx[i] >= 9 || y + dy[i] < 0 || y + dy[i] >= 9//맵 나감
                || visit[y + dy[i]][x + dx[i]] == true//이미 정복
                || minefield[y + dy[i]][x + dx[i]] == 1//폭탄 있음
                ) continue;

            for (int j = 0; j < 8; j++)
            {
                if (x + dx[i] + dx2[j] < 0 || x + dx[i] + dx2[j] >= 9 || y + dy[i] + dy2[j] < 0 || y +dy[i] + dy2[j] >= 9) continue;
                if (minefield[y + dy[i] + dy2[j]][x + dx[i] + dx2[j]] == 1)
                    isSideBomb++;
            }
            visit[y + dy[i]][x + dx[i]] = true;
            if (isSideBomb == 0)
            {
                viewfield[y + dy[i]][x + dx[i]] = "[ ]";
                dfs(x + dx[i], y + dy[i], visit);
            }
            else
            {
                viewfield[y + dy[i]][x + dx[i]] = "[" + to_string(isSideBomb) + "]";
                
            }
        }
    }
};

void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    system("chcp 65001");
    system("cls");
    Mine m = Mine();
    int x, y;
    x = 0; y = 0;
    m.print(x, y);
    while (true)
    {
        int key = _getch();
        //cout << key << endl;
        if (key == 32) {//스페이스
            if (m.select(x, y) == false) return 0;
        }
        if (key == 72) {
            y--;
            if (y < 0) y = 0;
        }
        if (key == 80) {
            y++;
            if (y >= 9) y = 8;
        }
        if (key == 75) {
            x--;
            if (x < 0)x = 0;
        }
        if (key == 77) {
            x++;
            if (x >= 9) x =8;
        }
        if (key == 97) {
            m.flag(x, y);
        }
        //system("cls");
        gotoxy(0, 0);
        m.print(x,y);
    }
}