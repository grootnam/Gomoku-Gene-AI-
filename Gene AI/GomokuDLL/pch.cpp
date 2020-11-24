// pch.cpp: 미리 컴파일된 헤더에 해당하는 소스 파일

#include "pch.h"
#include "cGA.h"


cGA* m_pGAAI = NULL;
int m_GomokuMap[MAPSIZE][MAPSIZE];
Vector2f m_vUserPos;

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  IsWin(int mid, int x, int y)
{
	int count[4] = { 0, };
	bool left = false;
	bool right = false;

	for (int i = 1; i < 8; i++)
	{
		if (right == true && left == true)
			break;

		int dx1 = x - i;
		int dx2 = x + i;

		if (m_GomokuMap[dx1][y] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE)
		{
			count[0]++;
		}
		else
			left = true;
		if (m_GomokuMap[dx2][y] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE)
		{
			count[0]++;
		}
		else
			right = true;
	}

	left = false;
	right = false;
	for (int i = 1; i < 8; i++)
	{
		if (right == true && left == true)
			break;

		int dy1 = y - i;
		int dy2 = y + i;

		if (m_GomokuMap[x][dy1] == mid && left == false && dy1 >= 0 && dy1 < MAPSIZE)
		{
			count[1]++;
		}
		else
			left = true;
		if (m_GomokuMap[x][dy2] == mid && right == false && dy2 >= 0 && dy2 < MAPSIZE)
		{
			count[1]++;
		}
		else
			right = true;
	}

	left = false;
	right = false;
	for (int i = 1; i < 8; i++)
	{
		if (right == true && left == true)
			break;

		int dx1 = x + i;
		int dy1 = y - i;

		int dx2 = x - i;
		int dy2 = y + i;

		if (m_GomokuMap[dx1][dy1] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE && dy1 >= 0 && dy1 < MAPSIZE)
		{
			count[2]++;
		}
		else
			left = true;
		if (m_GomokuMap[dx2][dy2] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE && dy2 >= 0 && dy2 < MAPSIZE)
		{
			count[2]++;
		}
		else
			right = true;
	}

	left = false;
	right = false;
	for (int i = 1; i < 8; i++)
	{
		if (right == true && left == true)
			break;

		int dx1 = x + i;
		int dy1 = y + i;

		int dx2 = x - i;
		int dy2 = y - i;

		if (m_GomokuMap[dx1][dy1] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE && dy1 >= 0 && dy1 < MAPSIZE)
		{
			count[3]++;
		}
		else
			left = true;
		if (m_GomokuMap[dx2][dy2] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE && dy2 >= 0 && dy2 < MAPSIZE)
		{
			count[3]++;
		}
		else
			right = true;
	}


	int Max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (Max <= count[i])
			Max = count[i];
	}

	if (Max >= 4)
		return true;
	else
		return false;
}
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  Init()
{
	AllocConsole();
	freopen("conout$", "wt", stdout);
	m_vUserPos = Vector2f(0, 0);
	m_pGAAI = new cGA();
	m_pGAAI->Init(m_GomokuMap, BLACK);
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			m_GomokuMap[i][j] = 0;
		}
	}
	printf("Init \n");
}

extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  SetBlackStone(int x, int y)
{
	if (m_GomokuMap[x][y] == 0)
	{
		m_GomokuMap[x][y] = BLACK;
		m_vUserPos = Vector2f(x, y);
		return true;
	}
	else
		return false;
}
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  FrameMove(float* x, float* y)
{
	if (m_pGAAI != NULL)
	{
		Vector2f wp = m_pGAAI->FrameMove(m_vUserPos.x, m_vUserPos.y);

		m_GomokuMap[(int)wp.x][(int)wp.y] = WHITE;
		*x = wp.x;
		*y = wp.y;
		printf("FrameMove %d %d\n", (int)wp.x, (int)wp.y);

	}

}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  Release()
{
	if (m_pGAAI != NULL)
	{
		delete m_pGAAI;
		m_pGAAI = NULL;
	}
	printf("Release \n");
}