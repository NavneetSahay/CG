/*

NAME   : NAVNEET KUMAR SAHAY
ROLL   : 1705330
BATCH  : CS-5
BRANCH : CSE

*/

#include"graphics"
#include<math.h>
namespace G { void line(int,int,int,int,int,int,int); }

class Matrix {
 public:
 float m[16]; //Row major format
 float& operator[](int i) { return m[i]; }
};

class Cube {
 public:
 float corners[8][3] = { -1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, 1,-1, -1, 1, -1, 1, 1, 1, -1, 1, 1, 1 };
 
 
void draw1(int p1, int p2, int r, int g, int b) {
 for(int i=0;i<8;++i){
 line(corners[p1][0]+random()%2, corners[p1][1]+random()%2, corners[p2][0]+random()%2, corners[p2][1]+random()%2, r, g, b);
 }
}


void draw() {
 int data[]= {1, 5, 5, 4, 4, 6, 6, 2, 2, 3, 3, 1, 3, 7, 5, 7, 6, 7};
 for(int i=0; i < 18; i+=2) {
 int c = 128-(corners[data[i]][2]+corners[data[i+1]][2])/2.5;
 draw1(data[i], data[i+1], c, c, c);
 }
 draw1(0, 1, 160, 160, 255);
 draw1(0, 2, 0, 255, 128);
 draw1(0, 4, 255, 160, 0);
}


Cube transform(Matrix m) {
 Cube c;
 for(int i = 0; i < 8; ++i) {
 float x = corners[i][0], y = corners[i][1], z = corners[i][2];
 float w = x*m[12]+y*m[13]+z*m[14]+m[15];
 for(int j=0; j<3; ++j)
 c.corners[i][j] = (x*m[4*j]+y*m[4*j+1]+z*m[4*j+2]+m[4*j+3])/w; 
 }
 return c;
 }
};

class T { // T for transformation
public:
static Matrix translate(float dx, float dy, float dz) {
Matrix m;
m[3]=dx;
m[7]=dy;
m[11]=dz;
m[0]=m[5]=m[10]=m[15]=1.0;
m[1]=m[2]=m[4]=m[6]=m[8]=m[9]=m[12]=m[13]=m[14]=0.0;
return m;
};
static Matrix rotate(float theta, float a, float b, float c0) {
float L = (a*a + b * b + c0 * c0);
theta = theta * M_PI / 180; 
float ad = a * a;
float bd = b * b;
float cd = c0 * c0; 
Matrix m;
m[0] = (ad + (bd + cd) * cos(theta)) / L;
m[1] = (a * b * (1 - cos(theta)) - c0 * sqrt(L) * sin(theta)) / L;
m[2] = (a * c0 * (1 - cos(theta)) + b * sqrt(L) * sin(theta)) / L;
m[3] = 0; 
m[4] = (a * b * (1 - cos(theta)) + c0 * sqrt(L) * sin(theta)) / L;
m[5] = (bd + (ad + cd) * cos(theta)) / L;
m[6] = (b * c0 * (1 - cos(theta)) - a * sqrt(L) * sin(theta)) / L;
m[7] = 0; 
m[8] = (a * c0 * (1 - cos(theta)) - b * sqrt(L) * sin(theta)) / L;
m[9] = (b * c0 * (1 - cos(theta)) + a * sqrt(L) * sin(theta)) / L;
m[10] = (cd + (ad + bd) * cos(theta)) / L;
m[11] = 0; 
m[12] = 0;
m[13] = 0;
m[14] = 0;
m[15] = 1;
return m;
};
static Matrix scale(float sx, float sy, float sz) {
Matrix m;
m[0]=sx;
m[5]=sy;
m[10]=sz;
m[15]=1;
m[1]=m[2]=m[3]=m[4]=m[6]=m[7]=m[8]=m[9]=m[11]=m[12]=m[13]=m[14]=0;
return m;
}
};


int main() {
const int W = 960;
const int H = 560;
const char * file = "output1.png";
canvas(W, H, file);
int i;
Cube cube;
cube = cube.transform(T::rotate(5,1,0,0)).transform(T::rotate(5,0,1,0));
Matrix s[] = {
T::scale(75,75,75), T::scale(75,75,75), T::scale(75,75,75),
T::scale(120,25,25), T::scale(120,50,5), T::scale(50,50,50)},
t[6], r[]= {
T::rotate(40,1,0,0), T::rotate(40,0,1,0), T::rotate(40,0,0,1),
T::rotate(45,1,1,0), T::rotate(45,0,1,1), T::rotate(-45,1,1,1)};
for(i=0; i < 6; ++i) {
t[i] = T::translate(150+i%3*300,150+i/3*250,0);
cube.transform(s[i]).transform(r[i]).transform(t[i]).draw();
}
cout << "writing " << file << endl;
return 0;
}
