#include "Components.h"

CueBall::CueBall(){
	wx = 0;
	wy = 0;
	wflag = 0;
	directRotate = 0;
}

void CueBall::draw(){
	//��ĸ��
	glPushMatrix();
	glTranslatef(wx, wy, -0.6);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(R, 10, 10);
	glPopMatrix();

	//��������
	if (!wflag){
		glPushMatrix();
		glTranslatef(wx, wy, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glRotatef(directRotate, 0, 0, 1);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, -0.6);
		glVertex3f(2, 0, -0.6);
		glEnd();
		glPopMatrix();
	}
}

MoveBalls::MoveBalls(){
	for (int i = 0; i < MNUM; i++){
		mspeed[i] = mspeed_edge;
		if (i % 2 == 0){
			movex[i] = -1 * rand(movex_edge * 10) / 10;
			movey[i] = rand(movey_edge * 10) / 10;
		}
		else{
			movex[i] = rand(movex_edge * 10) / 10;
			movey[i] = -1 * rand(movey_edge * 10) / 10;
		}
		moveflag[i] = 1;
		moverotate[i] = rand(360);
	}
}

void MoveBalls::draw(){
	for (int i = 0; i < MNUM; i++){
		if (moveflag[i]){
			glPushMatrix();
			glTranslatef(movex[i], movey[i], -0.6);
			glColor3f(1.0f, 0.3f, 1.0f);
			glutSolidSphere(R, 10, 10);
			glPopMatrix();
		}
	}
}

GhostBalls::GhostBalls(){
	ghostx[0] = 1.0f; ghosty[0] = -0.4f;
	ghostx[1] = -2.0f; ghosty[1] = 2.2f;
	ghostx[2] = -3.0f; ghosty[2] = 2.4f;
	ghostx[3] = 3.3f; ghosty[3] = 2.3f;
	ghostx[4] = -0.6f; ghosty[4] = -3.3f;
	ghostx[5] = 6.6f; ghosty[5] = -0.3f;
	for (int i = 0; i < GNUM; i++){
		gspeed[i] = 0;
		ghostflag[i] = 1;
		ghostrotate[i] = 0;
	}
}

void GhostBalls::draw(){
	for (int i = 0; i < GNUM; i++){
		if (ghostflag[i]){
			glPushMatrix();
			glTranslatef(ghostx[i], ghosty[i], -0.6);
			glColor3f(0.0f, 0.2f, 0.3f);
			glutSolidSphere(R, 10, 10);
			glPopMatrix();
		}
	}
}

Table::Table(){
	xedge = 9.0f;
	yedge = 3.6f;
}

BITMAP Table::GetBmp(LPCTSTR title)
{
	static HBITMAP hbmp = 0;
	hbmp = (HBITMAP)::LoadImage(GetModuleHandle(0), title, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	static BITMAP bmp = { 0 };
	GetObject(hbmp, sizeof(BITMAP), &bmp);
	return bmp;
}

void Table::tb_texture_display(){
	glColor3f(0, 0, 0);
	static GLuint texid;
	BITMAP tb_bmp = tb_bmp = GetBmp(L"D:/pictures/table.bmp");
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tb_bmp.bmWidth, tb_bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, tb_bmp.bmBits);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-10.2, 4.7, -0.5);
	glTexCoord2f(1, 0); glVertex3f(10.2, 4.7, -0.5);
	glTexCoord2f(1, 1); glVertex3f(10.2, -4.7, -0.5);
	glTexCoord2f(0, 1); glVertex3f(-10.2, -4.7, -0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

void Table::wd_texture_display(){
	{
		glColor3f(0, 0, 0);
		static GLuint texid;
		BITMAP wd_bmp = GetBmp(L"D:/pictures/wood.bmp");
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, wd_bmp.bmWidth, wd_bmp.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, wd_bmp.bmBits);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texid);
		glColor4f(1, 1, 1, 1);

		glFrontFace(GL_CCW);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-10.2, 4.7, 0.5);
		glTexCoord2f(1, 0); glVertex3f(10.2, 4.7, 0.5);
		glTexCoord2f(1, 1); glVertex3f(10.2, 4.7, -0.5);
		glTexCoord2f(0, 1); glVertex3f(-10.2, 4.7, -0.5);
		glEnd();

		glFrontFace(GL_CW);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-10.2, -4.7, 0.5);
		glTexCoord2f(1, 0); glVertex3f(10.2, -4.7, 0.5);
		glTexCoord2f(1, 1); glVertex3f(10.2, -4.7, -0.5);
		glTexCoord2f(0, 1); glVertex3f(-10.2, -4.7, -0.5);
		glEnd();

		glFrontFace(GL_CW);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(10.2, -4.7, 0.5);
		glTexCoord2f(1, 0); glVertex3f(10.2, 4.7, 0.5);
		glTexCoord2f(1, 1); glVertex3f(10.2, 4.7, -0.5);
		glTexCoord2f(0, 1); glVertex3f(10.2, -4.7, -0.5);
		glEnd();

		glFrontFace(GL_CCW);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-10.2, -4.7, 0.5);
		glTexCoord2f(1, 0); glVertex3f(-10.2, 4.7, 0.5);
		glTexCoord2f(1, 1); glVertex3f(-10.2, 4.7, -0.5);
		glTexCoord2f(0, 1); glVertex3f(-10.2, -4.7, -0.5);

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glFlush();
	};
}

void Table::draw(){	
	glColor3f(0.7f, 0.8f, 0.8f);
	//����
	glPushMatrix();
	glTranslatef(8, 4.0, 0.0);
	GLUquadricObj *cylinder_obj_1;
	cylinder_obj_1 = gluNewQuadric();
	glPushMatrix();
	gluCylinder(cylinder_obj_1, 0.5, 0.5, 6.0, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0, 4.0, 0.0);
	GLUquadricObj *cylinder_obj_2;
	cylinder_obj_2 = gluNewQuadric();
	glPushMatrix();
	gluCylinder(cylinder_obj_2, 0.5, 0.5, 6.0, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-8.0, -4.0, 0.0);
	GLUquadricObj *cylinder_obj_3;
	cylinder_obj_3 = gluNewQuadric();
	glPushMatrix();
	gluCylinder(cylinder_obj_3, 0.5, 0.5, 6.0, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8.0, -4.0, 0.0);
	GLUquadricObj *cylinder_obj_4;
	cylinder_obj_4 = gluNewQuadric();
	glPushMatrix();
	gluCylinder(cylinder_obj_4, 0.5, 0.5, 6.0, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//����
	glPushMatrix();
	glTranslatef(0, 4.6, 0);
	glColor3f(0.6, 0.2, 0.0);
	glScalef(20.2, 0.2, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -4.6, 0);
	glColor3f(0.6, 0.2, 0.0);
	glScalef(20.2, 0.2, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.1, 0, 0);
	glColor3f(0.6, 0.2, 0.0);
	glScalef(0.2, 9.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.1, 0, 0);
	glColor3f(0.6, 0.2, 0.0);
	glScalef(0.2, 9.4, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//����
	glPushMatrix();
	glColor3f(0, 1.0f, 0);
	glScalef(20.0, 9.0, 0.8);
	glutSolidCube(1.0);
	glPopMatrix();

	//��������
	/*glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_POINT);

	glPushMatrix();
	glFrontFace(GL_CCW);
	texture_display();
	glPopMatrix();

	glPushMatrix();
	wood_texture_display();
	glPopMatrix();
	*/
}