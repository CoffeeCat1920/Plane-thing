#include "./include/raylib.h"
#include "./include/Animation.h"

int main (int argc, char *argv[]) {
  
  SpriteAnimation animation = SpriteAnimation( "./assets/player.png", 3 );

  animation.AddAnimation( "walk" , 0, 2); 

  InitWindow( 64*5 , 64*5, "Animation Test");

  animation.Init();

  while ( !WindowShouldClose() )
  { 

    BeginDrawing();

    animation.PlayAnimation( 64 * 3.5 , 64 * 3.5 , "walk" );

    ClearBackground(GRAY);

    EndDrawing();
    
  }

  CloseWindow();

  return 0;
}
