#pragma once

#include "../include/raylib.h"

#include <string>
#include <unordered_map>

#include <iostream>

struct Animation {
  Animation() {}
  Animation( int startFrame, int endFrame ) : startFrame(startFrame), endFrame(endFrame) {}
  int startFrame;
  int endFrame;
};

class SpriteAnimation {

private:
  
  Image image;
  Texture2D texture;

  int frameCount;
  int frameSize;

  std::unordered_map< std::string, Animation > animations;


  float frameTime;
  float currentTime;
  int currentFrame;

  float framesPerSecond;

public:

  SpriteAnimation( std::string filepath, int frameCount ) {
    
    this->image = LoadImage( filepath.c_str() );

    this->frameCount = frameCount; 
    this->frameSize = image.width / frameCount;

    this->framesPerSecond = 10.0f;

    this->frameTime = 1.0f / framesPerSecond;
    this->currentTime = 0.0f;
    this->currentFrame = 0;

  } 

  ~SpriteAnimation() {
    UnloadImage(image);
    UnloadTexture(texture);
  } 

  void Init();

  void AddAnimation( std::string name, int startFrame, int endFrame );
  void PlayAnimation( float positionX, float positionY, std::string name );

};
