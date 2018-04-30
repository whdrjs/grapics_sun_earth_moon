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
	glutWireSphere(0.3, 50, 50);  //(radius slices stacks) ���ι����� ���ǰ���/ ���ι��⼱�� ����
//earth
	glPushMatrix();
	glRotatef(day, 0.0, 1.0, 0.0); // ��������
	glTranslatef(0.85, 0.0, 0.0);//���� �̵� ��ȯ �¾��� �������κ��� ������ �Ÿ�x��
	if (day < 180)// ����������
		glRotatef(23.5, 1.0, 0, 0); 
	else
		glRotatef(-23.5, 1.0, 0, 0); 
	glRotatef(time, 0.0, 1.0, 0.0); // ��������
	glColor3f(0.2, 0.5, 1.0);		//blue~green
	glutWireSphere(0.06, 20, 20); // ���� ������ 109��
	 //��
		glPushMatrix();
		glRotatef(md, 0.0, 1.0, 0.0); // �� ����, ���� �����൵ �������ֱ� ������(23.5�� �ƴ�����) �״��
		glTranslatef(0.14, 0.0, 0.0);
		glColor3f(0.8, 0.8, 0.8);		
		glutWireSphere(0.02, 10, 10); // ���� ���� 400��
		glPopMatrix();	//��
	glPopMatrix();//����
	glutSwapBuffers();
}

void timer(int t) {
	day = day + 0.04186335;	//�ѽð��� 0.041863...�� �� ((360/365)/24) 
	d++;						
	//cause, magnetic axis(������) turn around over 180
	if (day < 180)			
	{
		time += 15;		//�ѽð��� 15����
		md -= 14.5;		//���� ������ �������� �ʱ����� -15 ,30�Ͽ� �ѹ��� ���� �ѽð��� 0.5����
	}
	else if(day>=180)	//���� ������ ���� ������ �ٲ�� ���� �������� ȸ���� ����
	{
		time -= 15;		
		md += 14.5;
	}
	
	//0 ~ 360�� �ڵ��� ���� ����ϱ�����
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
	//�� �� ���
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

//�ð� ������ �����Ͽ� delay������ �Ұ������� ��ǻ� ��� �Ұ��� ������
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