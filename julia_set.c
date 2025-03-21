#include <stdio.h>
#include "raylib.h"
#include "limits.h"
#include <stdint.h>

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

void juliaSet(int imgWidth, int imgHeight){
    const float cx = 0.7885;
    const float R = 2;
    const float e = 2.71828;
    const int pixelSurface = 202500;

    int rectWidth = 1;
    int rectHeight = 1;
    for(int i = 0; i < imgHeight; i++){
        for(int x = 0; x < imgWidth; x++){

            float zx = (x/imgWidth) * (2*R) - R; 
            float zy = (i/imgWidth) * (2*R) - R;

            int iteration = 0;
            int max_iteration = 500;

            while ((zx * zx) + (zy * zy) < R * R && iteration < max_iteration){
                
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
    const int windowHeight = 450;
    const int windowWidth = 450;

    InitWindow(windowWidth, windowHeight, "hex colors");

    SetTargetFPS(120);

    while(!WindowShouldClose()){

        BeginDrawing();

            ClearBackground(BLACK);

            //WaitTime(1);
            colorMatrix(10, 10);

        EndDrawing();
    
    }
    CloseWindow();

    return 0; 
}

//compile with: gcc -march=native -mrdrnd beej.c -o beej ../raylib-master/src/libraylib.a -lm -lpthread -ldl -lrt -lX11