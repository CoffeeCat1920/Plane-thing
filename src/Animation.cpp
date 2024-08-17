#include "../include/Animation.h"

void SpriteAnimation::Init() {

  texture = LoadTextureFromImage( this->image );

}

void SpriteAnimation::AddAnimation( std::string name, int startFrame, int endFrame ) {

  this->animations[name] = Animation(startFrame, endFrame);

}

void SpriteAnimation::PlayAnimation( float positionX, float positionY, std::string name ) {

  auto it = animations.find(name);
  if (it == animations.end()) {
    std::cerr << "Animation not found: " << name << std::endl;
     return;
  }

  const Animation& animation = it->second;

  currentTime += GetFrameTime();
  if (currentTime >= frameTime) {
    currentTime -= frameTime;
    currentFrame++;
    if (currentFrame > animation.endFrame) {
      currentFrame = animation.startFrame;
    }
  }

  Rectangle source = {(float)currentFrame * frameSize, 0, (float)frameSize, (float)frameSize};
  DrawTexturePro(texture, source, Rectangle{positionX, positionY, (float)frameSize, (float)frameSize}, Vector2{0, 0}, 0.0f, WHITE);

}
