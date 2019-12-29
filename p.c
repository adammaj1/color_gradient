/*

How do I get the length of a dynamically allocated array in C? You can't.  You have to pass the length as a parameter to your function.
https://stackoverflow.com/questions/5126353/get-the-length-of-dynamically-allocated-array-in-c

-------------------


--------------


gcc p.c -Wall -lm

./a.out >a.txt

ls -l *.ppm

===================
 plot "1.txt" using 1:2 with  linespoint title "R"
gnuplot> plot "1.txt" using 1:3 with  linespoint title "G"
gnuplot> plot "1.txt" using 1:4 with  linespoint title "B"



*/

#include <stdio.h>
#include <string.h> // strncat
#include <stdlib.h> // malloc
#include <math.h> // log10

// color = RGB triplet = (thus three bytes per pixel) in the order red, green, then blue
// color = 3 bytes
// color component ( channel) = 1 byte =  number from 0 to 255 = unsigned char 


// size of virtual 2D array of pixels
// each piexel has a RGB color
int iWidth = 600;
int iHeight ; // 


// size of the dynamic 1D array 
unsigned char * data;
size_t ColorSize = 3; // RGB = number of color components = channels
size_t ArrayLength; // number of 1D array's elements = ENumber = iWidth*iHeight*ColorSize
size_t ElementSize; // size of array's element in bytes
size_t ArraySize; // size of array in bytes = ElementSize*ArrayLength 

// ppm P6 file
size_t HeaderSize ; // size of the P6 file  header in bytes
size_t FileSize; // = HeaderSize +ArraySize [bytes]







// gives position of 2D point (ix,iy) in 1D array  ; uses also global variables: iWidth , ColorSize
int Give_i ( int iX, int iY)
{
  return (iX + iY * iWidth) * ColorSize;  
}

/* 

based on Delphi function by Witold J.Janik  
https://commons.wikimedia.org/wiki/File:HSV-RGB-comparison.svg 

input : position
output: array c = RGB color 
 */
void GiveRainbowColor(double position, unsigned char c[])
{
  	unsigned char nmax=6; /* number of color segments */
  	double m=nmax* position;
  
  	int n=(int)m; // integer of m
  
  	double f=m-n;  // fraction of m
  	unsigned char t=(int)(f*255);
  	
  	/* if position > 1 then we have repetition of colors it maybe useful    */
      
	if (position>1.0){if (position-(int)position==0.0)position=1.0; else position=position-(int)position;}

  	// gradient with 6 segments
	switch( n){
   		case 0: { c[0] = 255; 		c[1] = t; 	c[2] = 0; 	break; };
   		case 1: { c[0] = 255 -t;	c[1] = 255;	c[2] = 0; 	break; };
   		case 2: { c[0] = 0;		c[1] = 255;	c[2] = t; 	break; };
   		case 3: { c[0] = 0;		c[1] = 255 -t; 	c[2] = 255;	break; };
   		case 4: { c[0] = t;		c[1] = 0;	c[2] = 255;	break; };
   		case 5: { c[0] = 255;		c[1] = 0;	c[2] = 255 -t;	break; };
   		default:{ c[0] = 255;		c[1] = 0;	c[2] = 0;	break; };
	}; // case
}




/*
Your new colormap is different and ugly-ish. The line between red-and-yellow is much much worse than before.  the red-yellow discontinuity is ... confusing, annoying. .. to me, at least.
https://gitlab.com/adammajewski/LinasArtGallery_MandelbrotSet
http://linas.org/art-gallery/index.html

http://linas.org/art-gallery/src/fractal/image/flo2mtv.c


struct rgb {
   char r;
   char g;
   char b;
};

static struct rgb vlt[256];





void make_cmap (void) {
    int i, j;
    struct rgb black;
    black.r = black.g = black.b = 0x0;
    for (i=0; i<256; i++) vlt[i] = black;

    // set up a default look up table 
    // ramp up to blue 
    for (i=0; i<60; i++) {
            vlt[i].r = 0;
            vlt[i].g = 0;
            vlt[i].b = (char) i*3;
        }
    // ramp down from blue, up to green 
    for (i=60; i<120; i++) {
            vlt[i].r = 0;
            vlt[i].g = (char) (i-60)*3;
            vlt[i].b = (char) (120-i)*3;
        }
    // ramp from green to yellow 
    for (i=120; i<180; i++) {
            // vlt[i].r = (char) (((i-120)*7) / 2); 
            vlt[i].r = (char) (210 - (7*(180-i)*(180-i)) / 120);
            vlt[i].g = (char) (210 -i/4);
            vlt[i].b = 0;
        }
    // ramp from yellow to red (pink) 
    for (i=180; i<240; i++) {
            vlt[i].r = (char) (210 + (3*(i-180))/4);
            vlt[i].g = (char) (510 - 2*i);
            vlt[i].b = (char) (i-180)/3;
        }
}


*/


   
void GiveLinasColor(double position ,  unsigned char c[])
{
  /* based on the code by Linas Vepstas January 16 1994 : void make_cmap (void) */

   
  int i;
  int iMax = 239;
  i=(int)(iMax-1)*position;  
  c[0] = c[1] = c[2] = 0; /* set up a default look up table */
  
  
  // gradient with 4 segments 
  /* ramp from black to blue */
  if (i<60) {
    c[0] = 0;
    c[1] = 0;
    c[2] = (unsigned char) i*3;
  }
  /* ramp down from blue, up to green */
  if (i>=60 && i<120) {
    c[0] = 0;
    c[1] = (unsigned char) (i-60)*3;
    c[2] = (unsigned char) (120-i)*3;
  }
  /* ramp from green to yellow */
  if (i >=120 && i<180) {
    /* vlt[i].r = (char) (((i-120)*7) / 2); */
    c[0] = (unsigned char) (210 - (7*(180-i)*(180-i)) / 120);
    c[1] = (unsigned char) (210 -i/4);
    c[2] = 0;
  }
  /* ramp from yellow to red (pink) */
  if (i>=180 && i<iMax) {
    c[0] = (unsigned char) (210 + (3*(i-180))/4);
    c[1] = (unsigned char) (510 - 2*i);
    c[2] = (unsigned char) (i-180)/3;
  }
   
}

// https://github.com/Gnuplotting/gnuplot-palettes/blob/master/magma.pal
void GiveMagmaColor(double position, unsigned char c[]){
	
	double x, x2, x3, x4,x5,x6, x7, x8;
	
	double R, G, B;
	
	// 
	x = position;
	x2 = x*x;
	x3 = x*x2;
	x4 = x*x3;
	x5 = x*x4;
	x6 = x*x5;
	x7 = x*x6;
	x8 = x*x7;
	
	// found using https://arachnoid.com/polysolve/
	R = -2.1104070317295411e-002 +  1.0825531148278227e+000 * x -7.2556742716785472e-002 * x2 + 6.1700693562312701e+000 * x3 -1.1408475082678258e+001*x4 +  5.2341915705822935e+000*x5;
	if (R<0.0) R = 0.0; // small correction
	
	G = (-9.6293819919380796e-003 +  8.1951407027674095e-001 * x -2.9094991522336970e+000 * x2 + 5.4475501043849874e+000 * x3 -2.3446957347481536e+000*x4);
	if (G<0.0) G = 0.0;
	
	B = 3.4861713828180638e-002 -5.4531128070732215e-001*x + 4.9397985434515761e+001*x2 -3.4537272622690250e+002*x3 + 1.1644865375431577e+003*x4 -2.2241373781645634e+003*x5 + 2.4245808412415154e+003*x6 -1.3968425226952077e+003*x7 
	+3.2914755310075969e+002*x8;
	
	// change range 
	c[0] = (unsigned char) 255*R; //R
	c[1] = (unsigned char) 255*G; // G
	c[2] = (unsigned char) 255*B; // B	
	

}

void GiveGrayColorL(double position, unsigned char c[]){
	
	
	unsigned char X =  255- 255*position;
	// change range 
	c[0] = X; //R
	c[1] = X; // G
	c[2] = X; // B	
	

}

void GiveGrayColorNL2(double position, unsigned char c[]){
	
	
	unsigned char X =  255- 255*(position*position);
	// change range 
	c[0] = X; //R
	c[1] = X; // G
	c[2] = X; // B	
	

}


void GiveGrayColorNL3(double position, unsigned char c[]){
	
	
	unsigned char X =  255- 255*(position*position*position);
	// change range 
	c[0] = X; //R
	c[1] = X; // G
	c[2] = X; // B	
	

}


void GiveGrayColorSqrt(double position, unsigned char c[]){
	
	
	unsigned char X =  255*sqrt(position);
	// change range 
	c[0] = X; //R
	c[1] = X; // G
	c[2] = X; // B	
	

}



// from green to black = 
void GiveColorGreen(double position, unsigned char c[]){
	
	
	unsigned char X =  255- 255*(position*position*position);
	// change range 
	c[0] = 0; //R
	c[1] = X; // G
	c[2] = 0; // B	
	

}



void GiveLinas2Color(double position ,  unsigned char c[])
{
  /* based on the code by Linas Vepstas January 16 1994 : void make_cmap (void) */

   
   
  
  
  // gradient with 4 segments 0-0.25-0.5-0.75-1.0
  /* ramp from black to blue = (0.0 ; 0.25)) */
  if (position<0.25) {
    	c[0] = 0;
    	c[1] = 0;
    	c[2] = 708*position;; // B
    	return;
  }
  /* ramp down from blue, up to green = (0.25 ; 0.5)*/
  if (position<0.5) {
  	  
  	c[0] = 0; //R
    	c[1] =  -177+708*position; // G
    	c[2] =  354 - 708* position;; // B
    	return;
  }
  /* ramp from green to yellow  = (0.5 ; 0.75) */
  if (position<0.75) {
    	
    	c[0] = -420+840*position; //R
    	c[1] =  219-84*position; // G
    	c[2] = 0;
    	return;
  }
  /* position>0.75 :  ramp from yellow to red (pink) */
  	
	c[0] =  84+168*position; //R
    	c[1] = 516-480*position; // G
    	c[2] = -57 + 76*position; // B

    
   
}



// http://www.kennethmoreland.com/color-maps/
void GiveColorCoolWarm(double position, unsigned char c[]){
	
	
	double R,G,B;
	double x = position;
	double x2 = x*x;
	double x3 = x*x2;
	double x4 = x*x3;
	double x5 = x*x4;
	double x6 = x*x5;
	
	 
	
	R =  2.4070949725529692e-001 + 8.3340565013768031e-001*x + 2.6191922175556543e+000*x2 - 4.0994936709055061e+000*x3 + 1.1014553405733734e+000*x4;
	G =  2.8978300321243283e-001 + 2.2641158553110725e+000*x - 6.8483016873914799e+000*x2 + 3.0238558676188145e+001*x3 - 7.0431595279051223e+001*x4 + 6.8583306445298092e+001*x5 - 2.4054295028042432e+001*x6;
	B =  7.4391703318514535e-001 + 1.8345430120497781e+000*x - 3.1885763361607244e+000*x2 - 8.4015787106949880e-001*x3 + 1.6162754134259683e+000*x4;

	// change range 
	c[0] = (unsigned char) 255*R; //R
	c[1] = (unsigned char) 255*G; // G
	c[2] = (unsigned char) 255*B; // B	
	
	

}


//
int GiveColor(double position, int n, unsigned char c[]){

	switch(n){
	
	case 0: {GiveRainbowColor(position, c); break;}
	case 1: {GiveLinasColor(position,c); break;}
	case 2: {GiveMagmaColor(position,c); break;}
	case 3: {GiveGrayColorL(position,c); break;}
	case 4: {GiveGrayColorNL2(position,c); break;}
	case 5: {GiveGrayColorNL3(position,c); break;}
	case 6: {GiveGrayColorSqrt(position,c); break;}
	case 7: {GiveColorGreen(position,c); break;}
	case 8: {GiveLinas2Color(position,c); break;}
	case 9: {GiveColorCoolWarm(position,c); break;}
	default:{GiveRainbowColor(position, c);}
	}
	
	return 0;


}


int PlotPoint(unsigned char A[], int i, unsigned char color[]){

	A[i]   = color[0]; /* Red*/
    	A[i+1] = color[1]; /* Green */
    	A[i+2] = color[2];  /* Blue */
    	return 0;


}


void PrintColor( FILE *fp, double position, unsigned char color[]){
	// normalized to [0.0, 1.0] range RGB color channels
	double R = color[0]/255.0; 
	double G = color[1]/255.0;
	double B = color[2]/255.0;
	// [Relative luminance is formed as a weighted sum of linear RGB components](https://en.wikipedia.org/wiki/Luma_(video)) Y = 0.2126 R + 0.7152 G + 0.0722 B
	double Y = 0.2126*R + 0.7152*G + 0.0722*B;
	
	fprintf(fp, "%f\t %f\t%f\t%f \t %f \n", position, R,G,B,Y);

}



// --------------------
int FillArray (unsigned char A[] , int n){

	int iX;
	int iXmax = iWidth;
	int iY;
	int iYmax = iHeight;
	int i; //  index of 1D array  
	double position; // number form 0.0 to 1.0 used for color gradient
	unsigned char color[3]; // 
	
	// text file
	char name [100]; /* name of file */
  	snprintf(name, sizeof name, "%d", n); /*  */
  	char *filename =strncat(name,".txt", 4);
  	FILE *fp = fopen(filename, "w");
  	if (fp==NULL) {
    		printf("Error opening text file!\n");
    		return 1;
		}
	fprintf(fp, "# position \t\t R \t\t G \t\tB \t\tY\n"); // header of the text file
	
	
	//
	for(iX=0; iX<iXmax; ++iX){    
      		position = (double) iX / iXmax;
      		GiveColor(position, n, color);
      		PrintColor(fp, position,color); // 
      		
      		for(iY=0; iY<iYmax; ++iY){
      			i = Give_i(iX, iY);
      			PlotPoint(A, i , color);
      			}
        		
         			
      		}


	fclose(fp);
	return 0;
}





// --------------- save dynamic "A" array of uinsigned char to the binary ppm file ( P6 ) --------------------------------
int SaveArray2PPM (unsigned char A[], size_t ASize,   int k)
{

  FILE *fp;
  const unsigned char MaxColorComponentValue = 255;	/* color component is coded from 0 to 255 ;  it is 8 bit color file */
  
  char name [100]; /* name of file */
  snprintf(name, sizeof name, "%d", k); /*  */
  char *filename =strncat(name,".ppm", 4);
  
  

  /* save image to the pgm file  */
  fp = fopen (filename, "wb");	/*create new file,give it a name and open it in binary mode  */
  if (fp == NULL) 
  	{	printf("File open error"); 
  		return 1;}
  	else {
  		fprintf (fp, "P6\n%u %u\n%u\n", iWidth, iHeight, MaxColorComponentValue);	/*write header to the file */
  		fwrite (A, ASize, 1, fp);	// write dynamic A array to the binary file in one step  
 
  		printf ("File %s saved. \n", filename);
  		fclose (fp);
  		return 0;}
  
}



// n = nummber of the gradient function
int MakeGradientImage(unsigned char A[],  int n){


	FillArray(data, n);
	SaveArray2PPM(data, ArraySize, n+iWidth);
	return 0;

}



int setup(){

	iHeight = iWidth/3; 
	// 1D array
	ArrayLength = iWidth*iHeight*ColorSize;
	ElementSize = sizeof(unsigned char);
	ArraySize = ElementSize*ArrayLength ; 
	HeaderSize = 11 + (size_t) (log10(iHeight) +log10(iWidth)); 
	
	FileSize = HeaderSize + ArraySize; 
	
	/* create dynamic 1D array for RGB colors  */
  	data = malloc (ArraySize);
  	if (data == NULL ){
    		printf ( "Could not allocate memory for the array\n");
    		return 1;}

	
	return 0;
}


void info(){

	printf("ppm (P6) header size = %zu bytes\n", HeaderSize);
	printf("Array Size  = %zu bytes\n", ArraySize);
	printf("PPM file size  = %zu bytes\n", FileSize);

	
}



int end(){


  printf (" allways free memory (deallocate )  to avoid memory leaks \n"); // https://en.wikipedia.org/wiki/C_dynamic_memory_allocation
  free (data);
  info();
  return 0;

}



// ================================== main ============================================

int main (){

	int n;
	setup();
	//
	for (n = 0; n< 10; ++n)
		MakeGradientImage(data, n);
	
	end();

	return 0;
}
