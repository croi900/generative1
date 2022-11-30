
#include "include/raylib.h"
#include "include/generative.h"

#include <functional>
#include <iostream>
#include <queue>
#include <thread>

#define RGB(r,g,b) ((Color){r,g,b,255})
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int screenWidth = 800;
const int screenHeight = 450;

template<typename T>
struct triplet{
    T x, y, z;
};

auto perl_fn = [](float i, float j){
                        gen::perlin::noise n;
                        unsigned char r = 255 * n.get(i/20. + 0.3, j/20. + 0.3, GetTime());
                        unsigned char g = 255 * n.get(i/20.*sin(GetTime()) - 0.1, j/20.*sin(GetTime()) + 0.1, GetTime());
                        unsigned char b = 255 * n.get(i/20.*cos(GetTime()) + 0.2, j/20.*cos(GetTime()) + 0.2, GetTime());

                        triplet<unsigned char> tr;
                        tr.x = r;
                        tr.y = g;
                        tr.z = b;
                        return tr;
                    };
gen::perlin::noise n;


void process(int cx, int cy, float t){
    auto si = cx * screenHeight / 4;
    auto ei = (cx + 1) * screenHeight / 4;

    auto sj = cy * screenWidth / 4;
    auto ej = (cy + 1) * screenWidth / 4;

    for(int i = si ; i < ei; ++i){
        for(int j = sj ; j < ej; ++j){ 
            
            unsigned char r = 255 * n.get(i/20. + 0.3, j/20. + 0.3, t);
            unsigned char g = 255 * n.get(i/20.*sin(t) - 0.1, j/20.*sin(t) + 0.1, t);
            unsigned char b = 255 * n.get(i/20.*cos(t) + 0.2, j/20.*cos(t) + 0.2, t);
            //unsigned char r = i, g = j, b = i + j;
            DrawPixel(j,i,RGB(r,g,b));
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    std::queue<std::thread> thread_q;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    float layer = 0;

    int fps;
    char fps_s[32];
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(IsKeyDown(KEY_DOWN))
            layer -= 1;
        if(IsKeyDown(KEY_UP))
            layer += 1;

        if(IsKeyPressed(KEY_SPACE)){
            ToggleFullscreen();
        }

        fps = GetFPS();
        sprintf(fps_s,"%d",fps);
        
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            int t = GetTime();
      

            // for(int ci = 0 ; ci < 4; ++ci){
            //     for(int cj = 0; cj < 4; ++cj){

            //        // process(ci,cj,t);
            //         //std::thread t(process,ci,cj,t);

            //        // thread_q.push(t);
            //     }
            // }
            process(0,0,t);

            DrawText(fps_s,8,8,12,BLACK);
           
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

      // for(int i = 0 ; i < screenHeight/4; ++i){
            //     for(int j = 0; j < screenWidth/4; ++j){
            //         // //std::cout<<n.get(j,i,0.3)<<std::endl;
            //         // unsigned char r = (float)255 * n.get(i/60.0 - GetTime()/10 , GetTime()/10 + i/60.0,PI) + GetTime() * 10;;//* sin((i + j));
            //         // unsigned char g = (float)255 * n.get(i/60.0 - GetTime()/10 , GetTime()/10 + i/60.0,PI) + GetTime() * 10;//* sin((i + j));
            //         // unsigned char b = (float)255 * n.get(j/20.0,i/20.0,abs(i-j)/10.0) ;//* sin((i + j));

            //         unsigned char r = 255 * n.get(i/20. + 0.3, j/20. + 0.3, GetTime());
            //         unsigned char g = 255 * n.get(i/20.*sin(GetTime()) - 0.1, j/20.*sin(GetTime()) + 0.1, GetTime());
            //         unsigned char b = 255 * n.get(i/20.*cos(GetTime()) + 0.2, j/20.*cos(GetTime()) + 0.2, GetTime());
                    
            //        // if(g>r && g>b)
            //             DrawPixel(j,i,RGB(r,g,b));
            //     }
            // }

             // while(thread_q.empty() == false){
            //     thread_q.front().join();
            //     thread_q.pop();
            // }
            // std::cout<<GetFPS()<<'\n';
            //DrawCircle(160,160,16,RGB(255,120,0));
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);