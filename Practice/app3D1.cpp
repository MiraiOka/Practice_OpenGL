//3DCGのワイヤーフレームモデル

#include <GLUT/GLUT.h>

void init();
void idle();
void display();
void draw();
void drawCube();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void resize(int w, int h);

float pos[] = {0.0, 0.0, 0.0};
float scale[] = {1.0, 1.0, 1.0};
float angle[] = {0.0, 0.0, 0.0};

bool flagTranslate = true;
bool flagRotate = false;
bool flagScale = false;

//視野角
double fovY = 30.0;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("座標変換(App3D1)");
    
    //表示ウィンドウのサイズを変更した時のイベント
    glutReshapeFunc(resize);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}

void idle() {
    glutPostRedisplay();
}

void init() {
    glClearColor(0.2, 0.2, 0.3, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    //視点を変える時はこの位置に必要
    glLoadIdentity();
    
    //gluLookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ)
    //eye:視点の位置 center:注視点　up:ビューアップベクトル
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    draw();
    glutSwapBuffers();
}

void draw() {
    glColor3d(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glPolygonMode(GL_FRONT, GL_LINE);
    
    //見えないやつは点に
    glPolygonMode(GL_BACK, GL_POINT);
    
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(angle[2], 0.0, 0.0, 1.0);
    glRotatef(angle[1], 0.0, 1.0, 0.0);
    glRotatef(angle[0], 1.0, 0.0, 0.0);
    glScalef(scale[0], scale[1], scale[2]);
    drawCube();
    glPopMatrix();
}

void drawCube() {
    float p[8][3] = {
        {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5}, {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}
    };
    
    glBegin(GL_QUADS);
    //z方向
    glVertex3fv(p[0]); glVertex3fv(p[1]);
    glVertex3fv(p[2]); glVertex3fv(p[3]);
    
    //x方向(正面)
    glVertex3fv(p[0]); glVertex3fv(p[3]);
    glVertex3fv(p[7]); glVertex3fv(p[4]);
    
    //y方向
    glVertex3fv(p[0]); glVertex3fv(p[4]);
    glVertex3fv(p[5]); glVertex3fv(p[1]);
    
    //-x方向
    glVertex3fv(p[1]); glVertex3fv(p[5]);
    glVertex3fv(p[6]); glVertex3fv(p[2]);
    
    //-y方向
    glVertex3fv(p[2]); glVertex3fv(p[6]);
    glVertex3fv(p[7]); glVertex3fv(p[3]);
    
    //-z方向
    glVertex3fv(p[4]); glVertex3fv(p[7]);
    glVertex3fv(p[6]); glVertex3fv(p[5]);
    
    glEnd();
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovY, (double)w / (double)h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch ((unsigned char)key) {
        case 27: //esc
            return;
            break;
        case 'r':
            flagTranslate = false;
            flagRotate = true;
            flagScale = false;
            break;
        case 's':
            flagTranslate = false;
            flagRotate = false;
            flagScale = true;
            break;
        case 'R':
            pos[0] = pos[1] = pos[2] = 0.0;
            scale[0] = scale[1] = scale[2] = 1.0;
            angle[0] = angle[1] = angle[2] = 0.0;
            break;
        default:
            break;
    }
}

void special(int key, int x, int y) {
    if(flagTranslate) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                pos[0] += 0.1;
                break;
            case GLUT_KEY_LEFT:
                pos[0] -= 0.1;
                break;
            case GLUT_KEY_UP:
                if (glutGetModifiers() == 0) pos[1] += 0.1; //[Shift],[Ctrl],[Alt]キー以外ならy方向に+1
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) pos[2] -= 0.1; //z方向
                break;
            case GLUT_KEY_DOWN:
                if (glutGetModifiers() == 0) pos[1] -= 0.1; //[Shift],[Ctrl],[Alt]キー以外ならy方向に-1
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) pos[2] += 0.1; //-z方向
                break;
            default:
                break;
        }
    } else if (flagScale) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                scale[0] += 0.1;
                break;
            case GLUT_KEY_LEFT:
                scale[0] -= 0.1;
                break;
            case GLUT_KEY_UP:
                if (glutGetModifiers() == 0) scale[1] += 0.1;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) scale[2] += 0.1;
                break;
            case GLUT_KEY_DOWN:
                if (glutGetModifiers() == 0) scale[1] -= 0.1;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) scale[2] -= 0.1;
                break;
            default:
                break;
        }
    } else if (flagRotate) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                angle[0] += 10;
                break;
            case GLUT_KEY_LEFT:
                angle[0] -= 10;
                break;
            case GLUT_KEY_UP:
                if (glutGetModifiers() == 0) angle[1] += 10;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) angle[2] += 10;
                break;
            case GLUT_KEY_DOWN:
                if (glutGetModifiers() == 0) angle[1] -= 10;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) angle[2] -= 10;
                break;
            default:
                break;
        }
    }
}