#include "square.h"

//=============================================================================
// default constructor
//=============================================================================
 Square::Square() : Entity()
{
    spriteData.width = squareNS::WIDTH;           
    spriteData.height = squareNS::HEIGHT;
    spriteData.x = squareNS::X;                  
    spriteData.y = squareNS::Y;
    spriteData.rect.bottom = squareNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = squareNS::WIDTH;
    collisionType = entityNS::BOX;
	edge.bottom = squareNS::HEIGHT/2;
	edge.top = -squareNS::HEIGHT/2;
	edge.right = squareNS::WIDTH/2;
	edge.left = -squareNS::WIDTH/2;
	movable = false;
	isTorch = false;
	isCompanion = false;
}
 
//=============================================================================
// draw the ship
//=============================================================================
void Square::draw()
{
    Image::draw();              
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Square::update(float frameTime)
{
		if(animate) {
			Entity::update(frameTime);
			if(!isTorch && !getIsCompanion() && this->getCurrentFrame() == this->getEndFrame()) {
					this->setActive(false);
					this->setAnimate(false);
		}
	}
}

