#include"graphics"
using G::canvas;
using G::pixel;
using G::line;
#include<iostream>
using std::cout;
using std::endl;
#include<cmath>

void dda1(float x0,float y0,float xe,float ye){

	int v2[]={xe, ye}, dd[]={x0<xe?1:-1, y0<ye?1:-1}, u=fabs(ye-y0)>fabs(xe-x0);
	float q[]={(float)x0, (float)y0}, n=dd[u]*(v2[!u]-q[!u])/(v2[u]-q[u]+1e-6);
	
	for(;abs(v2[u]-q[u])>0; q[u]+=dd[u],q[!u]+=n)
		pixel(q[0], q[1], 255, 255, 255);
	pixel(q[0], q[1], 255, 255, 255);
}


void dda2(float xa,float ya,float xb,float yb){

	int dx=xb-xa, dy=yb-ya, steps, k;
	float xinc, yinc, x=xa, y=ya;
	if(abs(dx)>abs(dy)) steps=abs(dx);
	else steps=abs(dy);
	
	xinc=dx/(float)steps;
	yinc=dy/(float)steps;
	
	pixel(x,y,255,255,255);
	for(k=0;k<steps;k++){
		x+=xinc;
		y+=yinc;
		pixel(x,y,255,255,255);
	}
	
}

int main()
{
  cout << "processing" << endl;
  const int W = 960;
  const int H = 560;
  const char * file = "rgb.png";
  canvas(W, H, file);
  
  for(float t=0;t<2*M_PI;t+=M_PI/10){
  	dda1(200 + 20*cos(t), 200 + 20*sin(t), 200 + 100*cos(t), 200 + 100*sin(t));
  	dda2(400 + 20*cos(t), 400 + 20*sin(t), 400 + 100*cos(t), 400 + 100*sin(t));
  }
  cout << "writing " << file << endl;
  return 0;
}
