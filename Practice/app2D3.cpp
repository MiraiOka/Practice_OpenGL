#include <GLUT/GLUT.h>

void init();
void idle();
void display();
void drawRectangle();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);

//affine変換用変数
float pos[] = {0.0, 0.0, 0.0};
float size[] = {1.0, 1.0, 1.0};
float angle[] = {0.0, 0.0, 0.0};

//アフィン変換フラグ
bool flagTranslate = true;
bool flagRotate = false;
bool flagScale = false;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    //ダブルバッファリング:表のバッファ(フロントバッファ、可視化バッファ)と裏のバッファ(バッグバッファ)という色や明るさを保存するためのバッファメモリが2つ用意されている。描画コマンドが実行されると裏バッファに書き込まれる。その間にディスプレイ上で見ている画像は前回書き込まれた表バッファの内容です。描画処理が終了した時点で2つもバッファを切り替えます。このダブルバッファの機能がなければ、書き込み中の画像を見ることになり画像がちらつく。
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("アフィン変換(App2D3)");
    
    //何も処理がする必要がなくなった時に呼ばれるイベント
    glutIdleFunc(idle);
    
    glutDisplayFunc(display);
    
    //キーボードが押された時のイベント
    glutKeyboardFunc(keyboard);
    
    //矢印やファンクションキーなど特殊なキーボードを押した時のイベント
    glutSpecialFunc(special);

    init();
    glutMainLoop();
    return 0;
}

void idle() {
    //最新のシーンが描画される
    glutPostRedisplay();
}

void init() {
    glClearColor(0.2, 0.3, 0.2, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle();
    
    //ダブルバッファリング機能を使用した時、表示関数の最後にこのコマンドをコールし、バッファの交換を行う必要がある。glFlush()をglutSawpBuffersで置き換える
    glutSwapBuffers();
}

void drawRectangle() {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //アフィン変換
    //この後に行われる変換操作が他のオブジェクトに影響しないようにする
    glPushMatrix();
    
    //平行移動するメソッド(①x軸方向 ②y軸方向 ③z軸方向)
    glTranslatef(pos[0], pos[1], pos[2]); //平行移動
    
    //回転するメソッド(①回転角度(°) ②③④x,y,zの方向ベクトル)
    glRotatef(angle[2], 0.0, 0.0, 1.0); //z軸回転
    glRotatef(angle[1], 0.0, 1.0, 0.0); //y軸回転
    glRotatef(angle[0], 1.0, 0.0, 0.0); //x軸回転
    
    //スケーリングのメソッド(①x軸方向, ②y軸方向 ③z軸方向)
    glScaled(size[0], size[1], size[2]); //スケーリング
    
    //四角形の描画
    glBegin(GL_QUADS);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);
    glEnd();
    
    //2つ以上のオブジェクトを描画する時はそれぞれ別個に座標変換を行う必要がある
    //スタック領域に退避していた変換行列を取り出す
    //最後に入れた情報が最初に取り出される
    glPopMatrix();
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
            size[0] = size[1] = size[2] = 1.0;
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
                size[0] += 0.1;
                break;
            case GLUT_KEY_LEFT:
                size[0] -= 0.1;
                break;
            case GLUT_KEY_UP:
                if (glutGetModifiers() == 0) size[1] += 0.1;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) size[2] += 0.1;
                break;
            case GLUT_KEY_DOWN:
                if (glutGetModifiers() == 0) size[1] -= 0.1;
                else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) size[2] -= 0.1;
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