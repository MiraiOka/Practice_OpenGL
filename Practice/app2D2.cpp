//2次元図形(直線と三角形)を描く
#include <GLUT/GLUT.h>

void init();
void display();
void drawLine();
void drawTriangle();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(300, 300);
    glutCreateWindow("2次元CG2(App2D2)");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    
    return 0;
}

void init() {
    glClearColor(0.2, 0.2, 0.3, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine();
    drawTriangle();
    glFlush();
}

void drawLine() {
    glColor3f(0.0, 1.0, 0.0);
    
    //線の幅(defaultは1)
    glLineWidth(5.0);
    
    glBegin(GL_LINES);
        glVertex2f(-0.5, 0.0);
        glVertex2f(0.5, 0.0);
    glEnd();
}

void drawTriangle() {
    glColor3f(1.0, 0.0, 0.0);
    
    glLineWidth(2.0);
    
    //第一引数(face)で指定した面を、第二引数(mode)で指定したようにする
    //mode: GL_LINE = 直線, GL_FILL = 塗りつぶし, GL_POINT = 点
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glPolygonMode(GL_BACK, GL_LINE);
//    glPolygonMode(GL_FRONT, GL_FILL);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    
    
    
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.75, -0.75);
    glVertex2f(0.75, -0.75);
    glVertex2f(0.0, 0.75);
    glEnd();
}


//メモ
//GL_POINT 与えられた全ての頂点座標に点を描画する
//GL_LINES 2つの頂点をペアとして、頂点間の直線を描画する
//GL_LINE_STRIP 最初の頂点から最後の頂点まで直線を連結して描画する
//GL_LINE_LOOP 最初の頂点から最後の頂点まで直線を連結して描画する。さらに、最初の頂点と最後の頂点を連結する
//GL_TRIANGLES 3頂点を1組として三角形を描画する
//GL_QUADS 4頂点を1組として四角形を描画する
//GL_TRIANGLE_STRIP 1辺を共有して帯状に連結した三角形を描画する
//GL_QUAD_STRIP 1辺を共有して帯状に連結した四角形を描画する
//GL_TRIANGLE_FAN 1辺を共有して扇状に連結した三角形を描画する
//GL_POLYGON 単独の多角形を描画する
