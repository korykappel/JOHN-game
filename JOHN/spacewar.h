// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "block.h"
#include "avatar.h"
#include "textDX.h"
#include <sstream>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
	TextureManager avatarTexture;
	TextureManager upBlockTexture, leftRightBlockTexture, downBlockTexture;
	TextureManager obTexture;
	TextureManager spikeBlockTexture;
	TextureManager sideWallTexture;
	TextureManager bottomWallTexture;
	TextureManager topWallTexture;
	TextureManager companionTexture;
	TextureManager largeGateTexture;
	TextureManager smallGateTexture;
	TextureManager splashScreenTexture, creditsTexture, endScreenTexture, scoreTexture;
	TextureManager torchTexture;
	Image splashScreen, credits, endScreen, score;
	Avatar	avatar;
	Square leftWall, rightWall, bottomWall, topLeftWall, topRightWall, largeGate, smallGate, torch1, torch2;

	int level;
	int blocksLeft;
	bool smallGateOpen, largeGateOpen;
	bool gameStart;
	bool cubeDead;
	int startTime;

	TextDX *endFont;

	Block a[23];

	enum BLOCKS {leftBlock1, leftBlock2, rightBlock1, downBlock1, downBlock2, downBlock3, upBlock1, upBlock2, companion, obstacle1, obstacle2, obstacle3, obstacle4, obstacle5, obstacle6, obstacle7, obstacle8, obstacle9, spike1, spike2, spike3, spike4, spike5};
	
public:
    // Constructor
    Spacewar();
	
    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void initializeLevel(int level);
};

#endif
