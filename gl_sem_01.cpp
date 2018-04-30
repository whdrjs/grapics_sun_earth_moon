#include<glut.h>
#include <math.h>
#include<stdio.h>
/**
*
* @brief solar system for graphics
* @author Jong keon Kim 201433676
* @date 2018-04-05
* @version 0.0.1
*
*/
static GLfloat day = 0, time = 0, md = 0;
int delay = 1;
int i = 0,m=0,d=0;

void display() {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.3, 50, 50);  //(radius slices stacks) 세로방향의 선의개수/ 가로방향선의 개수
//earth
	glPushMatrix();
	glRotatef(day, 0.0, 1.0, 0.0); // 지구공전
	glTranslatef(0.85, 0.0, 0.0);//정점 이동 변환 태양의 중점으로부터 떨어진 거리x축
	if (day < 180)// 지구자전축
		glRotatef(23.5, 1.0, 0, 0); 
	else
		glRotatef(-23.5, 1.0, 0, 0); 
	glRotatef(time, 0.0, 1.0, 0.0); // 지구자전
	glColor3f(0.2, 0.5, 1.0);		//blue~green
	glutWireSphere(0.06, 20, 20); // 지구 원래는 109배
	 //달
		glPushMatrix();
		glRotatef(md, 0.0, 1.0, 0.0); // 달 공전, 달의 공전축도 기울어져있기 때문에(23.5도 아니지만) 그대로
		glTranslatef(0.14, 0.0, 0.0);
		glColor3f(0.8, 0.8, 0.8);		
		glutWireSphere(0.02, 10, 10); // 달은 원래 400배
		glPopMatrix();	//달
	glPopMatrix();//지구
	glutSwapBuffers();
}

void timer(int t) {
	day = day + 0.04186335;	//한시간에 0.041863...도 씩 ((360/365)/24) 
	d++;						
	//cause, magnetic axis(자전축) turn around over 180
	if (day < 180)			
	{
		time += 15;		//한시간에 15도씩
		md -= 14.5;		//지구 자전에 따ㄱ라가지 않기위해 -15 ,30일에 한바퀴 위에 한시간에 0.5도씩
	}
	else if(day>=180)	//위와 같지만 축의 방향이 바뀌어 같은 방향으로 회전을 위해
	{
		time -= 15;		
		md += 14.5;
	}
	
	//0 ~ 360도 코딩시 쉽게 계산하기위해
	if (day >= 360)
		day -= 360;
	if (time >= 360)
	{
		time -= 360;
		i++;
	}
	if (time <= -360)
	{
		time += 360;
		i++;

	}
	if (md <= -360)
	{
		md += 360;
		m++;
	}
	//일 수 계산
	if (d % 24 == 0)
	{
		printf("\n day : %d\n", i);
	}
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
}

//시간 단위로 구동하여 delay수정이 불가피해져 사실상 사용 불가능 해졌다
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'u') 
		delay -= 15;
	if (key == 'd')
		delay += 15;
	if (key == 's')
		delay = 0;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutCreateWindow("HW1 : Solar System");
	glutKeyboardFunc(keyboard_handler);

	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}