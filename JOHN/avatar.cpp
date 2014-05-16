#include "avatar.h"

//=============================================================================
// default constructor
//=============================================================================
Avatar::Avatar() : Entity()
{
	spriteData.scale = avatarNS::AVATAR_SCALE;
    spriteData.width = avatarNS::WIDTH;        
    spriteData.height = avatarNS::HEIGHT;
    spriteData.x = avatarNS::X;                   // location on screen
    spriteData.y = avatarNS::Y;
    spriteData.rect.bottom = avatarNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = avatarNS::WIDTH;
    frameDelay = avatarNS::AVATAR_ANIMATION_DELAY;
    startFrame = avatarNS::AVATAR_START_FRAME;     // first frame of avatar animation
    endFrame     = avatarNS::AVATAR_END_FRAME;     // last frame of avatar animation
    currentFrame = startFrame;
    radius = avatarNS::WIDTH/2.0;
    //mass = avatarNS::MASS;
    collisionType = entityNS::BOX;
	edge.bottom = avatarNS::HEIGHT/2;
	edge.top = -avatarNS::HEIGHT/2;
	edge.right = avatarNS::WIDTH/2;
	edge.left = -avatarNS::WIDTH/2;

	nextLevel = false;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Avatar::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Avatar::draw()
{
    Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Avatar::update(float frameTime)
{
    // Walls
	if (spriteData.x > GAME_WIDTH-(squareNS::WIDTH * squareNS::SCALE)-(avatarNS::WIDTH * avatarNS::AVATAR_SCALE))    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-(squareNS::WIDTH * squareNS::SCALE)-(avatarNS::WIDTH)*avatarNS::AVATAR_SCALE;    // position at right screen edge
        velocity.x = 0;								
	} else if (spriteData.x < squareNS::WIDTH*squareNS::SCALE)                    // else if hit left screen edge
    {
        spriteData.x = squareNS::WIDTH*squareNS::SCALE;                           // position at left screen edge
        velocity.x = 0;                   
    }
	if (spriteData.y > GAME_HEIGHT-(squareNS::HEIGHT * squareNS::SCALE)-(avatarNS::HEIGHT)*avatarNS::AVATAR_SCALE)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-(squareNS::HEIGHT * squareNS::SCALE)-(avatarNS::HEIGHT)*avatarNS::AVATAR_SCALE;  // position at bottom screen edge
        velocity.y = 0;                  
    } else if (spriteData.y < 2*(squareNS::HEIGHT*squareNS::SCALE))                    // else if hit top screen edge
    {
		if(!nextLevel) {
			spriteData.y = 2*(squareNS::HEIGHT*squareNS::SCALE);                           // position at top screen edge
			velocity.y = 0; 
		} else {
			if((spriteData.x < 7*(squareNS::WIDTH * squareNS::SCALE) || spriteData.x > 8*(squareNS::WIDTH * squareNS::SCALE)) && getDirectionFacing() == avatarNS::UP) {
				spriteData.y = 2*(squareNS::HEIGHT*squareNS::SCALE);                           // position at top screen edge
				velocity.y = 0;                
			}
			if(spriteData.x < 7*(squareNS::WIDTH * squareNS::SCALE) && getDirectionFacing() == avatarNS::LEFT) {
				spriteData.x = 7*(squareNS::WIDTH * squareNS::SCALE);                         
				velocity.x = 0;                
			}
			if(spriteData.x > 8*(squareNS::WIDTH * squareNS::SCALE) && getDirectionFacing() == avatarNS::RIGHT) {
				spriteData.x = 8*(squareNS::WIDTH * squareNS::SCALE);                           
				velocity.x = 0;                
			}
			if (spriteData.y < 0) {
				spriteData.y = 0;
				velocity.y = 0;
			}
		}
    }

	velocity.x = 0;
	velocity.y = 0;

	if(input->isKeyDown(VK_RIGHT) && !input->isKeyDown(VK_UP) && !input->isKeyDown(VK_DOWN)){   //puts precedence over vertical movement if multiple keys held
		if(direction != avatarNS::RIGHT) {
			direction = avatarNS::RIGHT;
			setCurrentFrame(8);
		}
		velocity.x = avatarNS::SPEED; 
		setFrames(8, 11); 	
		Entity::update(frameTime);
		audio->playCue(WALKING);
	}
	if(input->isKeyDown(VK_LEFT) && !input->isKeyDown(VK_UP) && !input->isKeyDown(VK_DOWN)){
		if(direction != avatarNS::LEFT) {
			setDirectionFacing(avatarNS::LEFT);
			setCurrentFrame(4);
		}
		velocity.x = -avatarNS::SPEED; 
		setFrames(4, 7); 	
		Entity::update(frameTime);
		audio->playCue(WALKING);
	}
	if(input->isKeyDown(VK_UP)) {
		if(direction != avatarNS::UP) {
			setDirectionFacing(avatarNS::UP);
			setCurrentFrame(12);
		}
		velocity.y = -avatarNS::SPEED; 
		setFrames(12, 15); 	
		Entity::update(frameTime);
		audio->playCue(WALKING);
	}
	if(input->isKeyDown(VK_DOWN)) {
		if(direction != avatarNS::DOWN) {
			setDirectionFacing(avatarNS::DOWN);
			setCurrentFrame(0);
		}
		velocity.y = avatarNS::SPEED; 
		setFrames(0, 3); 	
		Entity::update(frameTime);
		audio->playCue(WALKING);
	}

	spriteData.x += frameTime * velocity.x;         // move ship along X 
    spriteData.y += frameTime * velocity.y;         // move ship along Y

}
