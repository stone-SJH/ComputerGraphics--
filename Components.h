#include <GL/glut.h>  
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>  
#include <string>
#include <cmath>
#include "macro.h"
using namespace std;
class CueBall{
public:
	float wx;
	float wy;
	float wspeed = 0.10f;
	float wspeed_edge = 0.10f;//恒定速度
	float wspeed_edge2 = 0.04f;//停止模糊速度
	int wflag;
	float directRotate;
	float Rspeed = 5.0f;
	int score = -50;

	CueBall();
	void draw();
};

class MoveBalls{
public:
	float mspeed_edge = 0.04f;//最小恒定速度
	float mspeed_edge2 = 0.08f;//最大速度
	float mspeed[MNUM];//当前速度
	float movex[MNUM], movey[MNUM];//位置
	int moveflag[MNUM];//是否存在
	float moverotate[MNUM];
	int movex_edge = 6, movey_edge = 2;
	int score = -20;

	MoveBalls();
	void draw();
};

class GhostBalls{
public:
	float gspeed[GNUM];
	float ghostx[GNUM], ghosty[GNUM];
	int ghostflag[GNUM];
	float ghostrotate[GNUM];
	int score = 300;

	GhostBalls();
	void draw();
};

class SnitchBall{
public:
	int timer;
	int timer_max = 500;
	int drop_time = 2;// 1/drop_time是落地的概率
	int drop_max = 150;// 落地持续的时间
	int drop_flag;

	float sspeed = 0.2f;
	float snitchx, snitchy, snitchz;
	int snitchflag;
	int snitchrotate;
	int score = 5000;

	void get_new();
	SnitchBall();
	void draw();
};

class Table{
private:
	static BITMAP GetBmp(LPCTSTR title);
	BITMAP tb_bmp;
	BITMAP wd_bmp;
	void wd_texture_display();
	void tb_texture_display();
public:
	float xedge = 9.0f;
	float yedge = 3.6f;

	Table();
	void draw();
};