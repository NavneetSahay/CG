/*

NAME   : NAVNEET KUMAR SAHAY

*/

#include"graphics"
#include<math.h>
struct  dcPt 
{  int  x,  y; 	};
typedef  struct  tEdge 
{
int  yUpper;
float  xIntersect,  dxPerScan; 
struct  tEdge *  next;
} Edge;

/*  Inserts  edge  into  list  in  order  of  increasing  xIntersect  field.*/ 
void  insertEdge(Edge *  list,  Edge *  edge)
{
Edge *p,*q 	=  list;
p =  q->next;
while(p	!=  NULL)
{
if(edge->xIntersect< p->xIntersect)
p= NULL;
else{
q  = p;
p=  p->next;
}
}
edge->next	=  q->next;
q->next	= edge;
}
/*  For  an  index,   return  y-coordinate  of  next  nonhorizontal  line 	*/
int  yNext(int  k, int cnt, dcPt*  pts)
{
int  j;
if((k+1)>(cnt-1))
j=0;
else
j=k+1;
while(pts[k].y == pts[j].y)
if((j+1)>(cnt-1))
j=0;
else
j++;
return	(pts[j]	.y)	;
}

/*  Store  lower-y  coordinate  and  inverse  slope  for  each  edge. 	Adjust
and  store  upper-y  coordinate  for  edges  that  are  the  lower  member 
	of  a  monotically  increasing or  decreasing pair  of  edges */ 
void makeEdgeRec(dcPt  lower,dcPt  upper,int  yComp, Edge* edge,Edge*  edges[])
{
edge->dxPerScan	=(float)(upper.x-lower.x)/(upper.y-lower.y);
edge->xIntersect=  lower.x;
if(upper.y<  yComp)
edge->yUpper= upper.y-1;
else
edge->yUpper=upper.y;
insertEdge(edges[lower.y], edge);
}
void buildEdgeList (int cnt,dcPt*  pts,Edge*  edges[])
{
Edge	*  edge;
dcPt  v1,  v2;
int i,yPrev=  pts[cnt-2].y;
v1.x= pts[cnt-1].x;
v1.y= pts[cnt-1].y;
for(i=0;i<cnt; i++)
{
v2= pts[i];
if(v1.y	!= v2.y){
/*  nonhorizontal  line	*/
edge=(Edge*) malloc(sizeof(Edge));
if(v1.y	<  v2.y)
/*  up-going  edge	*/
makeEdgeRec(v1,v2,yNext(i,cnt,pts),edge,edges);
else	
/*  down-going  edge	*/

makeEdgeRec (v2,  v1,   yPrev,  edge,  edges);
}
yPrev= v1.y;
v1= v2;
}
}
void buildActiveList(int scan, Edge*  active,Edge* edges[])
{
Edge	*p,*q;
p= edges[scan]->next;
while(p){
q  =  p->next;
insertEdge(active,  p);
p = q;
}
}
void  fillScan 	(int  scan, Edge *active,   int  r,   int  g,  int  b)
{
Edge *p1,*p2; 
int  i;
p1 =  active->next; 
while	(p1){
p2 	= p1->next;

for(i=p1->xIntersect;  i<p2->xIntersect;  i++)
pixel((int)   i,   scan,   r,  g,  b);
p1 = p2->next;
}
}
void  deleteAfter(Edge	*  q)
{
Edge*  p=  q->next;
q->next	= p->next;
free	(p)	;
}
/*  Delete  completed edges.  Update  ixIntersecti  field for others	*/
void updateActiveList(int  scan,  Edge	*  active)
{
Edge *q	= active,*p=  active->next;
while	(p)
if(scan>= p->yUpper){
p= p->next;
deleteAfter(q);
}
else{
p->xIntersect= p->xIntersect+ p->dxPerScan;
q  = p;
p=  p->next;
}
}
void  resortActiveList	(Edge	*  active)
{
Edge*  q,	*  p	=  active->next;
active->next	=  NULL;
while	(p)	{
q  =  p->next;
insertEdge 	(active,  p); 
p  =  q;
}
}

void  scanFill 	(int  cnt,  dcPt*  pts,   int  r,   int  g,   int  b)
{ 
int  i,   scan,  h = pts[0].y;
for(i=1;  i<cnt;++i) if(h<pts[i].y) h =pts[i].y;
Edge*  edges[h],* active;
for	(i=0;   i<h;   i++)	{
edges[i]	=	(Edge*)  malloc	(sizeof	(Edge));
edges[i]->next	= NULL;}
buildEdgeList(cnt,  pts,  edges);
active	=	(Edge	*)   malloc	(sizeof	(Edge));
active->next	=  NULL;
for	(scan=0;   scan<h;   scan++)	{
buildActiveList	(scan,  active,   edges);
if	(active->next)	{
fillScan	(scan,  active,   r,  g,  b);
updateActiveList	(scan,  active);
resortActiveList	(active);
}
}
/*  Free  edge  records  that  have  been  malloc'ed 	*/ 
}
void  testPolygonFill(int  w,  int  h){
const  int  WINDOW_WIDTH=800,  WINDOW_HEIGHT=400;
/*  A bow-tie  polygon	*/
dcPt  pts[]	={
w/4,  h/4,
3*w/4,	3*h/4,
3*w/4,	h/4,
w/2,  h-1,
w/2,	1,
w/4,	3*h/4
};
scanFill	(6,  pts,	25,	250,	120)	;
}
int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 
  
//DDA Function for line generation 
void dda(int X0, int Y0, int X1, int Y1,int r,int g,int b) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
        pixel (X,Y,r,g,b);  // put pixel at (X,Y) 
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step           // for visualization of line- 
                             // generation step by step 
    } 
} 

class Polygon{
public:
int n;
int p[100][2];
float cx, cy;


void draw(int r=255, int g=255, int b=255)
{
	for(int i=0;i<n;i++){
	dda(p[i][0],p[i][1],p[(i+1)%n][0],p[(i+1)%n][1],r,g,b);}
}

void fill(int r, int g, int b){
scanFill(n,(dcPt*)p,r,g,b);
}


Polygon translate(int dx, int dy){
Polygon output = *this;
for(int i=0;i<n;i++){
	output.p[i][0]=p[i][0]+dx;
	output.p[i][1]=p[i][1]+dy;}
return output;
}

Polygon center(){
Polygon output = *this;
cx=cy=0;

for(int i=0;i<n;i++){
cx+=p[i][0];
cy+=p[i][1];
}
cx/=n;
cy/=n;
return translate(-cx,-cy);
}

Polygon uncenter(){
return translate(cx,cy);
}



Polygon rotate(int angle){
Polygon output = *this;
for(int i=0;i<n;i++){
	output.p[i][0] =p[i][0]*cos(angle) - p[i][1]*sin(angle); 
        output.p[i][1] = p[i][0]*sin(angle) + p[i][1]*cos(angle); }
return output;
}

Polygon scale(float sx, float sy){
Polygon output = *this;
for(int i=0;i<n;i++){
	output.p[i][0] =p[i][0]*sx; 
        output.p[i][1] = p[i][1]*sy; }
return output;
}

Polygon reflect(bool x, bool y){
Polygon output = *this;
if(x){
for(int i=0;i<n;i++){
	output.p[i][0] =p[i][0]; 
        output.p[i][1] = - p[i][1]; }

}
if(y){
for(int i=0;i<n;i++){
	output.p[i][0] = - p[i][0]; 
        output.p[i][1] = p[i][1]; }

}
return output;
}

Polygon shear(float sx, float sy){
Polygon output = *this;
for(int i=0;i<n;i++){
        
	output.p[i][0] =p[i][0]+ p[i][1]*sx; 
        output.p[i][1] = p[i][0]*sy + p[i][1]; }
return output;
}
};

int main()
{
const int W = 960;
const int H = 560;
canvas(W, H, "output.png");
Polygon p = {4, {50, 150, 50, 250, 100, 250, 100, 150}};
p.draw();
p.translate(100, 0).draw();
p.center().rotate(-70).uncenter().translate(200,0).draw();
p.translate(350, 0).center().scale(0.5,1.5).rotate(-60).reflect(true,false).uncenter().draw();
p.center().scale(0.75,0.75).shear(0.5,0).uncenter().translate(500,0).draw(150,255,150);
p.center().scale(0.75,0.75).shear(0,0.5).uncenter().translate(600,0).fill(150,255,150);
p.center().scale(0.75,0.75).shear(0.5,0.5).uncenter().translate(700,0).draw(150,255,150);

return 0;
}
