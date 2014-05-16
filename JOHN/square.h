#ifndef _SQUARE_H                 // Prevent multiple definitions if this 
#define _SQUARE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace squareNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const float SCALE = MASTER_SCALE;              // starting AVATAR scale	
}

// inherits from Entity class
class Square : public Entity
{
private:
protected:
	bool movable;
	bool isTorch;
	bool isCompanion;
public:
    // constructor
    Square();

    // inherited member functions
    virtual void draw();
    void update(float frameTime);
 
	void setIsTorch(bool t) {isTorch = t;}
	void setIsCompanion(bool x) {isCompanion = x;}
	bool getIsCompanion() {return isCompanion;}
};
#endif
