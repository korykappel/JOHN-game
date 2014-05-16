// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "block.h"

//=============================================================================
// default constructor
//=============================================================================
 Block::Block() : Square()
{
    frameDelay = blockNS::BLOCK_ANIMATION_DELAY;
    startFrame = blockNS::BLOCK_START_FRAME;     
    endFrame     = blockNS::BLOCK_END_FRAME;     
    currentFrame = startFrame;	
	crackSide = blockNS::LEFT;
	movable = true;
	nextLevel = false;
	isCompanion = false;
}

//=============================================================================
// Initialize the Block.
// Post: returns true if successful, false if failed
//=============================================================================
//bool Block::initialize(Game *gamePtr, int width, int height, int ncols,
//    TextureManager *textureM)
//{
//}

//=============================================================================
// draw the ship
//=============================================================================
void Block::draw()
{
    Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Block::update(float frameTime)
{
    spriteData.x += frameTime * velocity.x;         
    spriteData.y += frameTime * velocity.y;         

    // Slide into screen edge and stop
    if (spriteData.x > GAME_WIDTH- 2*(squareNS::WIDTH * squareNS::SCALE))    // if hit right screen edge
    {
		audio->playCue(HIT);
		spriteData.x = GAME_WIDTH-2*(squareNS::WIDTH*squareNS::SCALE);   
        velocity.x = 0;		
    } else if (spriteData.x < (squareNS::WIDTH*squareNS::SCALE))                    // else if hit left screen edge
    {
		audio->playCue(HIT);
        spriteData.x = (squareNS::WIDTH*squareNS::SCALE);                          
        velocity.x = 0;		
    }
	if (spriteData.y > GAME_HEIGHT-2*(squareNS::HEIGHT*squareNS::SCALE))  // if hit bottom screen edge
    {
		audio->playCue(HIT);
		spriteData.y = GAME_HEIGHT-2*(squareNS::HEIGHT*squareNS::SCALE);  
        velocity.y = 0;	
    } else if (spriteData.y < 2*(squareNS::HEIGHT*squareNS::SCALE))                    // else if hit top screen edge
    {
		if(!nextLevel)
		{
			audio->playCue(HIT);
			spriteData.y = 2*(squareNS::HEIGHT*squareNS::SCALE);  
		}
		else 
			spriteData.y = (squareNS::HEIGHT*squareNS::SCALE);  
		velocity.y = 0;	
    }
	
	if(animate) {
		audio->playCue(BREAK);
		Square::update(frameTime);
		if(this->getCurrentFrame() == this->getEndFrame()) {
				setAnimate(false);
				setMovable(false);
				if(!getIsCompanion())
				{
					this->setVisible(false);
					this->setActive(false);
				}
		}
	}

}
