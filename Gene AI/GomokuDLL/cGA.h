#include<Windows.h>
#include<stdio.h>
#include<assert.h>
#include<process.h>
#include <math.h>
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;

#pragma warning(disable: 4996)
#define UNITY_INTERFACE_API __stdcall
#define UNITY_INTERFACE_EXPORT __declspec(dllexport)

#define MAPSIZE 21
#define WHITE 1
#define BLACK 2

struct Vector2f
{
	float x;
	float y;
	Vector2f() {}
	Vector2f(float Tx, float Ty)
	{
		x = Tx;
		y = Ty;
	}
};

#ifndef GA_H
#define GA_H
struct GENE
{
	char g[10];
	float re;
	int x;
	int y;
};

class cGA
{
private:
	float			m_fg;
	vector<GENE>	m_GeneList;
	int				m_nInitGeneCount;
	int				m_nMaxgeneration;
	int				m_nMyID;
	int				(*m_ppMap)[MAPSIZE];
	Vector2f		m_vUserPos;
public:

private:
	void			onCreateGene();
	void			onMatingGene();
	void			onReleaseGene();
	float			GetCheckGene(int id);
	float			GetCheckWinrate(int mid, int x, int y);
public:
	cGA();
	~cGA();

	void			Init(int(*data)[MAPSIZE], int myid);
	Vector2f		FrameMove(int x, int y);
	void			Release();
};

#endif