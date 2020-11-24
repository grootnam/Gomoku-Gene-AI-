#include "pch.h"
#include "cGA.h"

bool comp(GENE a, GENE b) {
	return (a.re > b.re);
}

cGA::cGA()
{
}

cGA::~cGA()
{
}
void cGA::Init(int(*data)[MAPSIZE], int myid)
{
	m_fg = 0.5;
	srand(time(NULL));
	m_ppMap = data;
	m_GeneList.clear();
	m_nMyID = myid;
	m_nMaxgeneration = 4;
	m_nInitGeneCount = 8;
}

void cGA::Release()
{
	m_GeneList.clear();
}

void cGA::onMatingGene()
{
	int count = m_GeneList.size();
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (i != j)
			{
				//교배
				int pt = rand() % 10 + 1;
				int pt1 = 10 - pt;
				GENE a;
				memcpy(a.g, m_GeneList[i].g, sizeof(char) * pt);
				memcpy(&a.g[pt], &m_GeneList[j].g[pt], sizeof(char) * pt1);
				
				//변이
				int r = rand() % 2;
				if (r == 1)
				{
					int t = rand() % 10;
					if (a.g[t] == 0)
						a.g[t] = 1;
					else
						a.g[t] = 0;
				}
				m_GeneList.push_back(a);
			}
		}
	}
}
void cGA::onReleaseGene()
{
	int count = m_GeneList.size() * 0.6;

	for (int i = 0; i < count; i++)
	{
		m_GeneList.erase(m_GeneList.end() - 1);
	}
}

void cGA::onCreateGene()
{
	m_GeneList.clear();
	for (int i = 0; i < m_nInitGeneCount; i++)
	{
		GENE a;
		for (int j = 0; j < 10; j++)
		{
			a.g[j] = rand() % 2;
		}
		m_GeneList.push_back(a);
	}

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			GENE a;
			int dx = m_vUserPos.x + x;
			int dy = m_vUserPos.y + y;

			if (dx <= 0)
				dx = 0;
			if (dy <= 0)
				dy = 0;
			if (dx >= (MAPSIZE - 1))
				dx = MAPSIZE - 1;
			if (dy >= (MAPSIZE - 1))
				dy = MAPSIZE - 1;
			a.x = dx;
			a.y = dy;
			
			for (int i = 0; i < 5; i++) 
			{
				a.g[i] = dx % 2;
				dx = dx / 2;
			}
			for (int i = 5; i < 10; i++) 
			{
				a.g[i] = dy % 2;
				dy = dy / 2;
			}
			m_GeneList.push_back(a);
		}
	}
}
float cGA::GetCheckWinrate(int mid, int x, int y)
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

		if (m_ppMap[dx1][y] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE) {
			count[0]++;
		}
		else
			left = true;
		if (m_ppMap[dx2][y] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE)
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

		if (m_ppMap[x][dy1] == mid && left == false && dy1 >= 0 && dy1 < MAPSIZE) {
			count[1]++;
		}
		else
			left = true;
		if (m_ppMap[x][dy2] == mid && right == false && dy2 >= 0 && dy2 < MAPSIZE)
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

		if (m_ppMap[dx1][dy1] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE && dy1 >= 0 && dy1 < MAPSIZE) {
			count[2]++;
		}
		else
			left = true;
		if (m_ppMap[dx2][dy2] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE && dy2 >= 0 && dy2 < MAPSIZE)
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

		if (m_ppMap[dx1][dy1] == mid && left == false && dx1 >= 0 && dx1 < MAPSIZE && dy1 >= 0 && dy1 < MAPSIZE) {
			count[3]++;
		}
		else
			left = true;
		if (m_ppMap[dx2][dy2] == mid && right == false && dx2 >= 0 && dx2 < MAPSIZE && dy2 >= 0 && dy2 < MAPSIZE)
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

	float p = (float)Max / (float)4.0f;
	return p;
}

float cGA::GetCheckGene(int id)
{
	int x = m_GeneList[id].g[0] + m_GeneList[id].g[1]*2 + m_GeneList[id].g[2] * 4 + m_GeneList[id].g[3] * 8 + m_GeneList[id].g[4] * 16;
	int y = m_GeneList[id].g[5] + m_GeneList[id].g[6]*2 + m_GeneList[id].g[7] * 4 + m_GeneList[id].g[8] * 8 + m_GeneList[id].g[9] * 16;
	m_GeneList[id].x = x;
	m_GeneList[id].y = y;

	if (y < MAPSIZE && x < MAPSIZE && x >= 0 && y >= 0)
	{
		if (m_ppMap[x][y] == 0)
		{
			float tw = GetCheckWinrate(WHITE, x, y);
			float tb = GetCheckWinrate(BLACK, x, y);
			float g1 = 1.0f - m_fg;
			m_GeneList[id].re = (tw * m_fg) + (tb * g1);
			return m_GeneList[id].re;
		}
		m_GeneList[id].re = 0;
		return 0;
	}
	else
	{
		m_GeneList[id].re = 0;
		return 0;
	}
}

Vector2f cGA::FrameMove(int x, int y)
{
	m_vUserPos = Vector2f(x, y);
	onCreateGene();

	for (int n = 0; n < m_nMaxgeneration; n++)
	{
		for (int i = 0; i < m_GeneList.size(); i++)
		{
			GetCheckGene(i);
		}
		sort(m_GeneList.begin(), m_GeneList.end(), comp);

		onReleaseGene();
		if (n != (m_nMaxgeneration - 1))
			onMatingGene();
	}
	Vector2f p = Vector2f(m_GeneList[0].x, m_GeneList[0].y);
	m_GeneList.clear();
	return p;
}
