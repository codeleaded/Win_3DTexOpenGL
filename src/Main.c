//#include "C:/Wichtig/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/WindowEngineGL1.0.h"
#include "/home/codeleaded/System/Static/Library/Files.h"
#include "./Math3D.h"


float cameraPos[3] = {0.0f, 0.0f, -5.0f};
float cameraFront[3] = {0.0f, 0.0f, 1.0f};
float cameraUp[3] = {0.0f, 1.0f, 0.0f};
float yaw = -90.0f, pitch = 0.0f;
float lastX = 400, lastY = 300;
char firstMouse = 1;
float angle = 0.0f;

void mouseCallback(int xPos, int yPos){
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = 0;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // Umkehren der Y-Achse
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    float front[3];
    front[0] = cosf(yaw * (F32_PI / 180.0f)) * cosf(pitch * (F32_PI / 180.0f));
    front[1] = sinf(pitch * (F32_PI / 180.0f));
    front[2] = sinf(yaw * (F32_PI / 180.0f)) * cosf(pitch * (F32_PI / 180.0f));

    cameraFront[0] = front[0];
    cameraFront[1] = front[1];
    cameraFront[2] = front[2];
}
void renderCube(float w->ElapsedTime) {
    glPushMatrix();
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glRotatef(angle * 0.66f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    // Vorderseite
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    // Rückseite
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    // Oben
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    // Unten
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    // Rechts
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    // Links
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}
void renderScene(float w->ElapsedTime) {
    int width = GetWidth();
    int height = GetHeight();

    float aspect = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Projektionsmatrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspect, 0.1, 100.0);

    // View-Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float target[3] = {
        cameraPos[0] + cameraFront[0],
        cameraPos[1] + cameraFront[1],
        cameraPos[2] + cameraFront[2]
    };
    gluLookAt(
        cameraPos[0], cameraPos[1], cameraPos[2],
        target[0], target[1], target[2],
        cameraUp[0], cameraUp[1], cameraUp[2]
    );

    renderCube(w->ElapsedTime);
}

void Setup(AlxWindow* w){
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Update(AlxWindow* w){
    angle += 45.0f * w->ElapsedTime;
    
    if (Stroke(ALX_KEY_W).DOWN)
        cameraPos[2] += 0.1f;
    else if (Stroke(ALX_KEY_S).DOWN)
        cameraPos[2] -= 0.1f;
    else if (Stroke(ALX_KEY_A).DOWN)
        cameraPos[0] += 0.1f;
    else if (Stroke(ALX_KEY_D).DOWN)
        cameraPos[0] -= 0.1f;

    mouseCallback(GetMouse().x,GetMouse().y);

    renderScene(w->ElapsedTime);
}

void Delete(AlxWindow* w){

}

int main(){
    if(Create("3D Tex OpenGL",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}