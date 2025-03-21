#include <stdio.h>
#include "raylib.h"
#include "limits.h"
#include <stdint.h>
#include <math.h>

//Generate random number using built in intel processor 
//RERAND generator.
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

void juliaSet(int imgWidth, int imgHeight, float a){
    
    const float R = 2.0f;
    const float e = 2.71828;
    const float cx = 0.7885 * cos(a);
    const float cy = 0.7885 * sin(a);

    Color color = (Color) {0, 0, 139, 255};
    

    for(int i = 0; i < imgHeight; i++){
        for(int x = 0; x < imgWidth; x++){
            
            float zx = ((float)(x)/(float)(imgWidth)) * (2.0f*R) - R; 
            float zy = ((float)(i)/(float)(imgHeight)) * (2.0f*R) - R;

            int iteration = 0;
            int max_iteration = 500;

            while ((zx * zx) + (zy * zy) < R * R && iteration < max_iteration){

                float temp = (zx*zx) - (zy*zy);
                zy = 2 * zx * zy + cy;
                zx = temp + cx;

                iteration++;
            }

            if(iteration == max_iteration){
                DrawPixel(x, i, color);
            }else{
                // Create a gradient based on iteration count
                unsigned char brightness = (unsigned char)(255 * iteration / max_iteration);
                Color gradientColor = (Color){
                    (unsigned char)((color.r * brightness) / 255),
                    (unsigned char)((color.g * brightness) / 255),
                    (unsigned char)((color.b * brightness) / 255),
                    255
                };
                DrawPixel(x, i, gradientColor);
            }
            
        }
    }
    
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

int main(void)
{ 
    const int windowHeight = 400;
    const int windowWidth = 450;

    InitWindow(windowWidth, windowHeight, "--");

    bool hasRendered = false;
    float range = 0.0f;

    SetTargetFPS(30);

    while(!WindowShouldClose()){

        BeginDrawing();


            
            ClearBackground(WHITE);


            if(range <= 2*PI){
                juliaSet(windowWidth, windowHeight, range);
                range += 0.05f;
            }
            

        EndDrawing();
    
    }
    CloseWindow();

    return 0; 
}

//compile with: gcc -march=native -mrdrnd julia_set.c -o julia_set ../../raylib-master/src/libraylib.a -lm -lpthread -ldl -lrt -lX11