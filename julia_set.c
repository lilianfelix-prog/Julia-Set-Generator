#include <stdio.h>
#include "raylib.h"
#include "limits.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <rlgl.h>



//Generate random number using built in intel processor RERAND generator.
/*
int random(int min, int max)
{
    unsigned long long rand64;
    if(__builtin_ia32_rdrand64_step(&rand64)){
        return min + (int)((double)rand64 / ULLONG_MAX * (max - min + 1));
    }
    return min;
}

//Generate matrix of row * col of random colors
void colorMatrix( int row, int col)
{
    int rectWidth = 30;
    int rectHeight = 30;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            Color color = (Color) {random(0, 255), random(0, 255), random(0, 255), 255};
            DrawRectangle(i * rectWidth, j * rectWidth, rectWidth, rectHeight, color);
        }
    }
}
*/

void juliaSet(int imgWidth, int imgHeight, float a){

    
    const float R = 1.2f;
    //const float e = 2.71828f;
    const float cx = 0.7885f * (float)(cos(a));
    const float cy = 0.7885f * (float)(sin(a));

    Color color1 = (Color) {(unsigned char)(255),(unsigned char)(255), (unsigned char)(255),(unsigned char)(255)};
    Color color2 = (Color) {(unsigned char)(0),(unsigned char)(0), (unsigned char)(139),(unsigned char)(255)};
    

    for(int i = 0; i < imgHeight; i++){
        for(int x = 0; x < imgWidth; x++){
            
            float zx = ((float)(x)/(float)(imgWidth)) * (2.0f*R) - R; 
            float zy = ((float)(i)/(float)(imgHeight)) * (2.0f*R) - R;

            int iteration = 1;
            int max_iteration = 50;

            while ((zx * zx) + (zy * zy) < R * R && iteration < max_iteration){

                float temp = (zx*zx) - (zy*zy);
                zy = 2 * zx * zy + cy;
                zx = temp + cx;

                iteration++;
            }

            if(iteration == max_iteration){
                DrawPixel(x, i, color1);
            }else{
                // Create a gradient based on iteration count
                unsigned char brightness = (unsigned char)((iteration/max_iteration)*255);
                Color gradientColor = (Color){
                    (unsigned char)((color2.r + brightness)),
                    (unsigned char)((color2.g + brightness)),
                    (unsigned char)((color2.b + brightness)),
                    255
                };
                DrawPixel(x, i, gradientColor);
            }
            
        }
    }
    
}


int main(void)
{ 
    const int windowHeight = 350;
    const int windowWidth = 450;

    InitWindow(windowWidth, windowHeight, "--");

    
    float range = 0.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();


            if(range <= 2*PI){
                juliaSet(windowWidth, windowHeight, range);
                range += 0.03f;
            }
            

        EndDrawing();
    
    }
    CloseWindow();

    return 0; 
}



// z^2 + 0.7885e^ia (0 <= a <= 2pi)
/*
ex: c = −0.4 + 0.6i

cx = 0.7885
cy = e^ia
R^2 - R >= sqrt(0.7885^2 + cos(a2) + i*sin(a2))
R(R - 1)
R = escape radius  # choose R > 0 such that R**2 - R >= sqrt(cx**2 + cy**2)

for each pixel (x, y) on the screen, do:   
{
    zx = scaled x coordinate of pixel; # (scale to be between -R and R)
       # zx represents the real part of z.
    zy = scaled y coordinate of pixel; # (scale to be between -R and R)
       # zy represents the imaginary part of z.

    iteration = 0;
    max_iteration = 1000;
  
    while (zx * zx + zy * zy < R**2  AND  iteration < max_iteration) 
    {
        xtemp = zx * zx - zy * zy;
        zy = 2 * zx * zy  + cy;
        zx = xtemp + cx;
    
        iteration = iteration + 1;
    }
  
    if (iteration == max_iteration)
        return black;
    else
        return iteration;
}
*/