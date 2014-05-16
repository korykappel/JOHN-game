#ifndef _AVATAR_H                 // Prevent multiple definitions if this 
#define _AVATAR_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "square.h"
#include "Random.h"

namespace avatarNS
{
	const int  WIDTH = 64;                 // width of AVATAR image
	const int  HEIGHT = 64;                // height of AVATAR image           
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const int  AVATAR_START_FRAME = 0;            // starting frame of AVATAR animation
	const int  AVATAR_END_FRAME = 15;              // last frame of AVATAR animation
	const float AVATAR_ANIMATION_DELAY = 0.15f;    // time between frames of AVATAR animation
	const int  COLS = 4;                   // AVATAR texture has 4 columns
	const float SPEED = 225.0f;            // pixels per second
	const float AVATAR_SCALE = .75;              // starting AVATAR scale

	enum DIRECTION_FACING {LEFT, RIGHT, UP, DOWN};
}

// inherits from Entity class
class Avatar : public Entity
{
private:
	//which side crack is on
	avatarNS::DIRECTION_FACING direction;
	bool nextLevel;
public:
    // constructor
    Avatar();

	int getDirectionFacing() {return direction;}
	void setDirectionFacing(avatarNS::DIRECTION_FACING d) {direction = d;}

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

	virtual void setNextLevel(bool n) {nextLevel = n;}
    
};
#endif

