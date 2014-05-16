// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

//IS A MOVABLE BLOCK, but not companion cube

#ifndef _BLOCK_H                 // Prevent multiple definitions if this 
#define _BLOCK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "square.h"
#include "constants.h"

namespace blockNS
{
	const int	BLOCK_START_FRAME = 0;
	const int	BLOCK_END_FRAME = 14;
	const float	BLOCK_ANIMATION_DELAY = 0.1F;
	const int	BLOCK_COLS = 3;
	const float SPEED = 250.0f;            // pixels per second

	enum CRACK_SIDE {LEFT, RIGHT, TOP, BOTTOM, NONE};
}

// inherits from Entity class
class Block : public Square
{
private:
	//which side crack is on
	blockNS::CRACK_SIDE crackSide;
	bool nextLevel;
	bool isCompanion;

public:
    // constructor
    Block();

    // inherited member functions
    virtual void draw();
    void update(float frameTime);
	void setCrackSide(blockNS::CRACK_SIDE side)   {crackSide = side;}
	blockNS::CRACK_SIDE getCrackSide() {return crackSide;}

	void setMovable(bool m) {movable = m;}
	bool getMovable() {return movable;}

	void setNextLevel(bool n) {nextLevel = n;}
	

};
#endif

