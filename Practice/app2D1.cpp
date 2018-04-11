//// glut.hにgl.h,glu.hが取り込まれているので、glut.hだけでいい
//#include <GLUT/glut.h>
//// 関数の宣言
//void init();
//void display();
//void drawPoint();
//
//int main(int argc, char** argv) {
//    //他のgultコマンドよりも先に呼び出す必要がある
//    glutInit(&argc, argv);
//    
//    glutInitDisplayMode(GLUT_RGBA);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(100, 100);
//    //ウィンドウ作成
//    glutCreateWindow("2次元CG1(App2D1)");
//    
//    //ウィンドウが表示された時に呼ばれるイベント(ウィンドウが表示された時にdisplayメソッドが呼ばれる)
//    glutDisplayFunc(display);
//    init();
//    
//    //無限ループに入り、イベント待ちになる
//    glutMainLoop();
//    
//    return 0;
//}
//
//void init() {
//    glClearColor(0.2, 0.2, 0.3, 1.0);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    drawPoint();
//    glFlush();
//}
//
//void drawPoint() {
//    //点の色
//    glColor3f(1.0, 0.0, 0.0); //赤
//    //点の大きさ
//    glPointSize(20.0);
//    //点の作成
//    glBegin(GL_POINTS);
//        glVertex2d(0, 0);
//    glEnd();
//}

