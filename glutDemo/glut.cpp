//=============================================================
// 导入OpenGL
//=============================================================
#ifdef _WIN32  // windows 平台
#include <gl/glew.h> // opengl 扩展封装头文件
#include <gl/glut.h>
#pragma comment(lib, "glew32.lib") // 导入lib

#elif defined(__APPLE__) || defined(MACOSX) // OS X 平台
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

//=============================================================
// 函数声明
//=============================================================
void Initialize();		// 初始化应用程序
void Uninitialize();	// 清理应用程序
void DrawFunc();									// glut描绘回调函数
void ReshapeFunc(int width, int height);			// glut窗口重置回调函数
void KeyboardFunc(unsigned char key, int x, int y);	// glut键盘回调函数
void MouseFunc(int button, int state, int x, int y);// glut鼠标按下与释放回调函数
void MotionFunc(int x, int y);						// glut鼠标移动回调函数
void IdleFunc();									// glut空闲处理回调函数
//void DrawText(const char* text, float x, float y);	// 在屏幕上显示文本


//=============================================================
// 全局变量
//=============================================================
const static float EPSILON = 0.000001f;
const static float PI = 3.1415926f;


// 窗口相关
const static int g_WindowPosX = 240;
const static int g_WindowPosY = 200;
int g_WindowWidth = 512;
int g_WindowHeight = 384;
const char* g_WindowTitle = "OpenGL";
// 显示模式:双缓冲，RGBA，深度缓存
const static int g_DisplayMode = (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// GLUT_STENCIL GLUT_ACCUM
const static float g_fov = 60.0f;
float g_rotateY = 0.0f;		// 绕Y轴旋转变量
float g_posX = 0.0f;


//=============================================================
// main 函数
//=============================================================
int main(int argc, char** argv)
{
	// 初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(g_DisplayMode);
//	glewInit();
    
	// 创建window
	glutInitWindowPosition(g_WindowPosX, g_WindowPosY);
	glutInitWindowSize(g_WindowWidth, g_WindowHeight);
	glutCreateWindow(g_WindowTitle);
	
	// 初始化应用程序
	Initialize() ;
	
	// 设定glut回调函数
	glutDisplayFunc(DrawFunc);
	glutReshapeFunc(ReshapeFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutIdleFunc(IdleFunc);
    
    
	// 进入glut事件处理循环
	glutMainLoop();
	
    // 清理应用程序
	Uninitialize();
	
	return 0;
}
//=============================================================
// 函数定义
//=============================================================

// 初始化应用程序
void Initialize()
{
	// 设置清屏颜色
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// 设置视口，投影信息
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_fov, (GLfloat)g_WindowWidth/g_WindowHeight, 1.0, 30.0);
}
// 清理应用程序
void Uninitialize()
{
	// nothing
}
// 空闲处理
void IdleFunc()
{
	g_rotateY += 0.2f;
	// 请求重绘
	glutPostRedisplay();
}
// 描绘函数
void DrawFunc()
{
	// 清屏
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glPushMatrix();
        glTranslatef(g_posX, 0.0f, -5.0f);
        // 描绘圆环
        glPushMatrix();
            glColor3f (0.0f, 0.0f, 1.0f);
            glRotatef(g_rotateY, 0.0f, 1.0f, 0.0f);
            glutSolidTorus(0.2f ,1.0f, 20, 40);
        glPopMatrix();
    
        // 描绘矩形
        glPushMatrix();
            glColor3f (0.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
            glVertex3f (2.0f, -1.5f, 2.0f);
            glVertex3f (-2.0f, -1.5f, 2.0);
            glVertex3f (-2.0f, -1.5f, -2.0);
            glVertex3f (2.0f, -1.50f, -2.0);
            glEnd();
        glPopMatrix();
	glPopMatrix();
    
//	// 显示文本信息
//	float x = 10.0f;
//	float y = 20.0f;
//	DrawText("Author: kesalin@gmail.com", x, y);
//	DrawText("Push /'A/' or /'D/' to move the torus.", x, y + 20.0f);
	// 交换显示缓冲区
	glutSwapBuffers() ;
}
// 响应窗口重置事件
void ReshapeFunc(int width, int height)
{
	g_WindowWidth = width;
	g_WindowHeight = height;
	glViewport(0, 0, g_WindowWidth, g_WindowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(g_fov, (GLfloat)g_WindowWidth/g_WindowHeight, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// 响应按键事件
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'A':
		case 'a':
			// 向左移动
			g_posX -= 0.05f;
			if( g_posX < -4.0f )
			{
				g_posX = -4.0f;
			}
			break;
		case 'D':
		case 'd':
			// 向右移动
			g_posX += 0.05f;
			if( g_posX > 4.0f )
			{
				g_posX = 4.0f;
			}
			break;
		default:
			break;
	}
}
// 响应鼠标按下与释放事件
void MouseFunc(int button, int state, int x, int y)
{
#if 0 // 默认不启动鼠标键监听
	switch( button )
	{
		case GLUT_LEFT_BUTTON:
		{
			if( state == GLUT_UP )
			{
			}
			else if( state == GLUT_DOWN )
			{
			}
		}
            break;
		case GLUT_RIGHT_BUTTON:
		{
			if( state == GLUT_UP )
			{
			}
			else if( state == GLUT_DOWN )
			{
			}
		}
            break;
            
		case GLUT_MIDDLE_BUTTON:
		{
			if( state == GLUT_UP )
			{
			}
			else if( state == GLUT_DOWN )
			{
			}
		}
            break;
	}
#endif
}
// 响应鼠标移动事件
void MotionFunc(int x, int y)
{
	// nothing
}

// 在屏幕上显示文本，x 和 y 为屏幕坐标
//void DrawText(const char* text, float x, float y)
//{
//	// 检查OpenGL状态
//	bool isDepthOpen = false;
//	bool isStencilOpen = false;
//	bool isLightOpen = false;
//	bool isFogOpen = false;
//
//	if(glIsEnabled(GL_DEPTH_TEST))
//	{
//		isDepthOpen = true;
//		glDisable(GL_DEPTH_TEST);
//	}
//	if(glIsEnabled(GL_STENCIL_TEST))
//	{
//		isStencilOpen = true;
//		glDisable(GL_STENCIL_TEST);
//	}
//	if(glIsEnabled(GL_LIGHTING))
//	{
//		isLightOpen = true;
//		glDisable(GL_LIGHTING);
//	}
//	if(glIsEnabled(GL_FOG))
//	{
//		isFogOpen = true;
//		glDisable(GL_FOG);
//	}
//
//	int font = (int)GLUT_BITMAP_8_BY_13;
//	// 设置字体颜色
//	glColor3f(1.0, 1.0, 0.0);
//
//	/*
//	 * 设置正投影
//	 */
//	glMatrixMode(GL_PROJECTION);
//	// 保存当前投影矩阵
//	glPushMatrix();
//    glLoadIdentity();
//    gluOrtho2D( 0, g_WindowWidth, 0, g_WindowHeight );
//    // 反转Y轴（朝下为正方向）(与窗口坐标一致)
//    glScalef(1, -1, 1);
//    // 将原点移动到屏幕左上方(与窗口坐标一致)
//    glTranslatef(0, -g_WindowHeight, 0);
//    glMatrixMode(GL_MODELVIEW);
//
//    // 保存当前模型视图矩阵
//    glPushMatrix();
//    glLoadIdentity();
//
//    // 设置文字位置
//    glRasterPos2f( x, y );
//
//    // 依次描绘所有字符(使用显示列表)
//    for(const char* c = text; *c != '/0'; c++)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//    // 恢复之前保存的模型视图矩阵
//    glPopMatrix();
//
//    glMatrixMode(GL_PROJECTION);
//
//	// 恢复之前保存的投影矩阵
//	glPopMatrix();
//	// 返回模型视图矩阵状态
//	glMatrixMode(GL_MODELVIEW);
//
//	// 恢复OpenGL状态
//	if(isDepthOpen)
//	{
//		glEnable(GL_DEPTH_TEST);
//	}
//	if(isStencilOpen)
//	{
//		glEnable(GL_STENCIL_TEST);
//	}
//	if(isLightOpen)
//	{
//		glEnable(GL_LIGHTING);
//	}
//	if(isFogOpen)
//	{
//		glEnable(GL_FOG);
//	}
//}


