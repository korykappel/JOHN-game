// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spacewar.h"
using std::stringstream;

//enum directions {LEFT, RIGHT, UP, DOWN};  //WHERE SHOULD THIS GO??

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	///////////////////////
	// Initialize Textures
	///////////////////////
	// avatar texture
    if (!avatarTexture.initialize(graphics,AVATAR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing avatar texture"));

	// block textures
    if (!leftRightBlockTexture.initialize(graphics,LEFTRIGHTBLOCK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block texture"));
	if (!upBlockTexture.initialize(graphics,UPBLOCK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block texture"));
	if (!downBlockTexture.initialize(graphics,DOWNBLOCK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block texture"));

	//obstacle texture
	if (!obTexture.initialize(graphics,OBSTACLE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	// spike block texture
	if (!spikeBlockTexture.initialize(graphics,SPIKEBLOCK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	// wall textures
	if (!topWallTexture.initialize(graphics,TOPWALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!bottomWallTexture.initialize(graphics,BOTTOMWALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));
	if (!sideWallTexture.initialize(graphics,SIDEWALL_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall texture"));

	// gate textures
	if (!largeGateTexture.initialize(graphics,LARGEGATE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing large gate texture"));
	if (!smallGateTexture.initialize(graphics,SMALLGATE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing small gate texture"));

	// companion texture
	if (!companionTexture.initialize(graphics,COMPANION_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing companion texture"));

	// splash texture
	if (!splashScreenTexture.initialize(graphics,SPLASHSCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	// credits texture
	if (!creditsTexture.initialize(graphics,CREDITS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credits texture"));
	// endscreen texture
	if (!endScreenTexture.initialize(graphics,ENDSCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing endscreen texture"));
	// score texture
	if (!scoreTexture.initialize(graphics,SCORE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score texture"));

	// torch texture
	if (!torchTexture.initialize(graphics,TORCH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	

	/////////////////////
	// Initialize Objects
	/////////////////////

	//SPIKES
	if (!a[spike1].initialize(this, 0, 0, 0, &spikeBlockTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	if (!a[spike2].initialize(this, 0, 0, 0, &spikeBlockTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	if (!a[spike3].initialize(this, 0, 0, 0, &spikeBlockTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	if (!a[spike4].initialize(this, 0, 0, 0, &spikeBlockTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	if (!a[spike5].initialize(this, 0, 0, 0, &spikeBlockTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	a[spike1].setVisible(false);
	a[spike1].setActive(false);
	a[spike2].setVisible(false);
	a[spike2].setActive(false);
	a[spike3].setVisible(false);
	a[spike3].setActive(false);
	a[spike4].setVisible(false);
	a[spike4].setActive(false);
	a[spike5].setVisible(false);
	a[spike5].setActive(false);
	a[spike1].setX(10*squareNS::WIDTH*MASTER_SCALE);
	a[spike1].setY(9*squareNS::WIDTH*MASTER_SCALE);
	a[spike2].setX(11*squareNS::WIDTH*MASTER_SCALE);
	a[spike2].setY(4*squareNS::WIDTH*MASTER_SCALE);
	a[spike3].setX(4*squareNS::WIDTH*MASTER_SCALE);
	a[spike3].setY(10*squareNS::WIDTH*MASTER_SCALE);
	a[spike4].setX(5*squareNS::WIDTH*MASTER_SCALE);
	a[spike4].setY(3*squareNS::WIDTH*MASTER_SCALE);
	a[spike5].setX(2*squareNS::WIDTH*MASTER_SCALE);
	a[spike5].setY(8*squareNS::WIDTH*MASTER_SCALE);
	a[spike1].setCrackSide(blockNS::NONE);
	a[spike2].setCrackSide(blockNS::NONE);
	a[spike3].setCrackSide(blockNS::NONE);
	a[spike4].setCrackSide(blockNS::NONE);
	a[spike5].setCrackSide(blockNS::NONE);

	// torch
    if (!torch1.initialize(this, 64, 64, 3, &torchTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	torch1.setFrames(0,2);
	torch1.setIsTorch(true);
	torch1.setFrameDelay(.1F);
	torch1.setAnimate(true);
	torch1.setX(6*squareNS::WIDTH*MASTER_SCALE);
	torch1.setY(1*squareNS::WIDTH*MASTER_SCALE);
	if (!torch2.initialize(this, 64, 64, 3, &torchTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing torch"));
	torch2.setFrames(0,2);
	torch2.setIsTorch(true);
	torch2.setFrameDelay(.1F);
	torch2.setAnimate(true);
	torch2.setX(9*squareNS::WIDTH*MASTER_SCALE);
	torch2.setY(1*squareNS::WIDTH*MASTER_SCALE);
	

	// splash
    if (!splashScreen.initialize(graphics, 0, 0, 0, &splashScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash"));
	// credits
    if (!credits.initialize(graphics, 0, 0, 0, &creditsTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing credits"));
	// end screen
    if (!endScreen.initialize(graphics, 0, 0, 0, &endScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing end screen"));
	// score screen
    if (!score.initialize(graphics, 0, 0, 0, &scoreTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score screen"));

	// avatar
    if (!avatar.initialize(this, avatarNS::WIDTH, avatarNS::HEIGHT, avatarNS::COLS, &avatarTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing avatar"));
    
	// blocks
	if (!a[downBlock1].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &downBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[downBlock1].setCrackSide(blockNS::BOTTOM);
	if (!a[downBlock2].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &downBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[downBlock2].setCrackSide(blockNS::BOTTOM);
	if (!a[downBlock3].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &downBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[downBlock3].setCrackSide(blockNS::BOTTOM);
	if (!a[leftBlock1].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &leftRightBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[leftBlock1].setCrackSide(blockNS::LEFT);
	if (!a[leftBlock2].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &leftRightBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[leftBlock2].setCrackSide(blockNS::LEFT);
	if (!a[rightBlock1].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &leftRightBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[rightBlock1].setCrackSide(blockNS::RIGHT);
	a[rightBlock1].flipHorizontal(true);
	if (!a[upBlock1].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &upBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[upBlock1].setCrackSide(blockNS::TOP);
	if (!a[upBlock2].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &upBlockTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing block"));
	a[upBlock2].setCrackSide(blockNS::TOP);
	

	 //obstacles
	if (!a[obstacle1].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle1]"));
	a[obstacle1].setCrackSide(blockNS::NONE);
	if (!a[obstacle2].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle2].setCrackSide(blockNS::NONE);
	if (!a[obstacle3].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle3].setCrackSide(blockNS::NONE);
	if (!a[obstacle4].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle4].setCrackSide(blockNS::NONE);
	if (!a[obstacle5].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle5].setCrackSide(blockNS::NONE);
	if (!a[obstacle6].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle6].setCrackSide(blockNS::NONE);
	if (!a[obstacle7].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle7].setCrackSide(blockNS::NONE);
	if (!a[obstacle8].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle8].setCrackSide(blockNS::NONE);
	if (!a[obstacle9].initialize(this, 0, 0, 0, &obTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing a[obstacle2]"));
	a[obstacle9].setCrackSide(blockNS::NONE);

	 //walls
	 if (!topLeftWall.initialize(this, 0, 0, 0, &topWallTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing top left wall"));
	 topLeftWall.setX(0);
	 topLeftWall.setY(0);
	 if (!topRightWall.initialize(this, 0, 0, 0, &topWallTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	 topRightWall.setX(9*squareNS::WIDTH*MASTER_SCALE);
	 topRightWall.setY(0);
	 if (!bottomWall.initialize(this, 0, 0, 0, &bottomWallTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	 bottomWall.setX(0);
	 bottomWall.setY(12*squareNS::HEIGHT*MASTER_SCALE);
	 if (!leftWall.initialize(this, 0, 0, 0, &sideWallTexture)) 
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	 leftWall.setX(0);
	 leftWall.setY(2*squareNS::HEIGHT*MASTER_SCALE);
	 if (!rightWall.initialize(this, 0, 0, 0, &sideWallTexture)) 
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	 rightWall.setX(15*squareNS::WIDTH*MASTER_SCALE);
	 rightWall.setY(2*squareNS::HEIGHT*MASTER_SCALE);

	 //Companion cube
	 if (!a[companion].initialize(this, squareNS::WIDTH, squareNS::HEIGHT, blockNS::BLOCK_COLS, &companionTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing companion"));
	 a[companion].setCrackSide(blockNS::NONE);
	 a[companion].setIsCompanion(true);

	 //Large Gate
	 if (!largeGate.initialize(this, squareNS::WIDTH*2, squareNS::HEIGHT*2, 5, &largeGateTexture))  
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing large gate"));
	 largeGate.setFrameDelay(.35F);
	 largeGate.setFrames(0, 4);
	 largeGate.setX(7*squareNS::WIDTH*MASTER_SCALE);
	 largeGate.setY(0);

	 //Small Gate
	 if (!smallGate.initialize(this, squareNS::WIDTH, squareNS::HEIGHT*2, 4, &smallGateTexture))   
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing small gate"));
	 smallGate.setFrameDelay(.35);
	 smallGate.setFrames(0, 3);
	 smallGate.setY(0*squareNS::HEIGHT*MASTER_SCALE);

	 //Score
	 endFont = new TextDX();
	 if(endFont->initialize(graphics, 75, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));


	endFont->setFontColor(graphicsNS::WHITE);
	startTime = GetTickCount()/1000;

	gameStart = false;
	splashScreen.setVisible(true);
	level = 1;
	cubeDead = false;
	audio->playCue(INTRO);

    return;
}

void Spacewar::initializeLevel(int level) {
	if(level == 1) {

		audio->stopCue(INTRO);
		audio->playCue(CHOPIN);

		blocksLeft = 2;
		avatar.setNextLevel(false);
		smallGateOpen = false;
		largeGateOpen = false;

		a[companion].setVelocity(VECTOR2(0,0));
		a[downBlock1].setVelocity(VECTOR2(0,0));
		a[leftBlock1].setVelocity(VECTOR2(0,0));
	
		avatar.setX(7*squareNS::WIDTH*MASTER_SCALE);
		avatar.setY(11*squareNS::HEIGHT*MASTER_SCALE);
		avatar.setCurrentFrame(13);

		a[downBlock1].setVisible(true); 
		a[downBlock1].setActive(true);
		a[downBlock1].setX(2*squareNS::WIDTH*MASTER_SCALE);
		a[downBlock1].setY(4*squareNS::HEIGHT*MASTER_SCALE);
		a[downBlock1].setAnimate(false);
		a[downBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[downBlock1].setMovable(true);

		a[leftBlock1].setVisible(true); 
		a[leftBlock1].setActive(true);
		a[leftBlock1].setX(5*squareNS::WIDTH*MASTER_SCALE);
		a[leftBlock1].setY(4*squareNS::HEIGHT*MASTER_SCALE);
		a[leftBlock1].setAnimate(false);
		a[leftBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[leftBlock1].setMovable(true);

		a[obstacle1].setX(6*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setY(4*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setVisible(true); 
		a[obstacle1].setActive(true);

		a[companion].setAnimate(false);
		a[companion].setVisible(true);
		a[companion].setActive(true);
		a[companion].setNextLevel(false);
		a[companion].setX(5*squareNS::WIDTH*MASTER_SCALE);
		a[companion].setY(9*squareNS::WIDTH*MASTER_SCALE);

		largeGate.setAnimate(false);
		largeGate.setActive(true);
		largeGate.setCurrentFrame(0);

		smallGate.setAnimate(false);
		smallGate.setActive(true);
		smallGate.setCurrentFrame(0);	
		smallGate.setX(5*squareNS::WIDTH*MASTER_SCALE);

		//NOT USED THIS LEVEL:
		a[leftBlock2].setVisible(false);
		a[leftBlock2].setActive(false);
		a[rightBlock1].setVisible(false);
		a[rightBlock1].setActive(false);
		a[downBlock2].setVisible(false);
		a[downBlock2].setActive(false);
		a[downBlock3].setVisible(false);
		a[downBlock3].setActive(false);
		a[upBlock1].setVisible(false);
		a[upBlock1].setActive(false);
		a[upBlock2].setVisible(false);
		a[upBlock2].setActive(false);
		a[obstacle2].setVisible(false);
		a[obstacle2].setActive(false);
		a[obstacle3].setVisible(false);
		a[obstacle3].setActive(false);
		a[obstacle4].setVisible(false);
		a[obstacle4].setActive(false);
		a[obstacle5].setVisible(false);
		a[obstacle5].setActive(false);
		a[obstacle6].setVisible(false);
		a[obstacle6].setActive(false);
		a[obstacle7].setVisible(false);
		a[obstacle7].setActive(false);
		a[obstacle8].setVisible(false);
		a[obstacle8].setActive(false);
		a[obstacle9].setVisible(false);
		a[obstacle9].setActive(false);
	}
	if(level == 2) {
		blocksLeft = 5;
		avatar.setNextLevel(false);
		smallGateOpen = false;
		largeGateOpen = false;

		a[companion].setVelocity(VECTOR2(0,0));
		a[downBlock1].setVelocity(VECTOR2(0,0));
		a[leftBlock1].setVelocity(VECTOR2(0,0));
		a[leftBlock2].setVelocity(VECTOR2(0,0));
		a[rightBlock1].setVelocity(VECTOR2(0,0));
		a[upBlock1].setVelocity(VECTOR2(0,0));
	
		avatar.setX(7*squareNS::WIDTH*MASTER_SCALE);
		avatar.setY(11*squareNS::HEIGHT*MASTER_SCALE);
		avatar.setCurrentFrame(13);

		a[downBlock1].setVisible(true); 
		a[downBlock1].setActive(true);
		a[downBlock1].setX(3*squareNS::WIDTH*MASTER_SCALE);
		a[downBlock1].setY(3*squareNS::HEIGHT*MASTER_SCALE);
		a[downBlock1].setAnimate(false);
		a[downBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[downBlock1].setMovable(true);

		a[leftBlock1].setVisible(true); 
		a[leftBlock1].setActive(true);
		a[leftBlock1].setX(10*squareNS::WIDTH*MASTER_SCALE);
		a[leftBlock1].setY(3*squareNS::HEIGHT*MASTER_SCALE);
		a[leftBlock1].setAnimate(false);
		a[leftBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[leftBlock1].setMovable(true);

		a[leftBlock2].setVisible(true); 
		a[leftBlock2].setActive(true);
		a[leftBlock2].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[leftBlock2].setY(4*squareNS::HEIGHT*MASTER_SCALE);
		a[leftBlock2].setAnimate(false);
		a[leftBlock2].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[leftBlock2].setMovable(true);

		a[rightBlock1].setVisible(true); 
		a[rightBlock1].setActive(true);
		a[rightBlock1].setX(3*squareNS::WIDTH*MASTER_SCALE);
		a[rightBlock1].setY(4*squareNS::HEIGHT*MASTER_SCALE);
		a[rightBlock1].setAnimate(false);
		a[rightBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[rightBlock1].setMovable(true);

		a[upBlock1].setVisible(true); 
		a[upBlock1].setActive(true);
		a[upBlock1].setX(3*squareNS::WIDTH*MASTER_SCALE);
		a[upBlock1].setY(9*squareNS::HEIGHT*MASTER_SCALE);
		a[upBlock1].setAnimate(false);
		a[upBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[upBlock1].setMovable(true);

		a[companion].setAnimate(false);
		a[companion].setVisible(true);
		a[companion].setActive(true);
		a[companion].setNextLevel(false);
		a[companion].setX(13*squareNS::WIDTH*MASTER_SCALE);
		a[companion].setY(8*squareNS::WIDTH*MASTER_SCALE);

		largeGate.setAnimate(false);
		largeGate.setActive(true);
		largeGate.setCurrentFrame(0);

		smallGate.setAnimate(false);
		smallGate.setActive(true);
		smallGate.setCurrentFrame(0);	
		smallGate.setX(13*squareNS::WIDTH*MASTER_SCALE);

		a[obstacle1].setX(4*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setY(10*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setVisible(true); 
		a[obstacle1].setActive(true);
		a[obstacle2].setX(12*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle2].setY(6*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle2].setVisible(true); 
		a[obstacle2].setActive(true);
		a[obstacle3].setX(12*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle3].setY(7*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle3].setVisible(true); 
		a[obstacle3].setActive(true);
		a[obstacle4].setX(13*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle4].setY(6*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle4].setVisible(true); 
		a[obstacle4].setActive(true);
		a[obstacle5].setX(13*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle5].setY(7*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle5].setVisible(true); 
		a[obstacle5].setActive(true);
		a[obstacle6].setX(10*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle6].setY(9*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle6].setVisible(true); 
		a[obstacle6].setActive(true);

		//NOT USED THIS LEVEL:
		a[downBlock2].setVisible(false);
		a[downBlock2].setActive(false);
		a[downBlock3].setVisible(false);
		a[downBlock3].setActive(false);
		a[upBlock2].setVisible(false);
		a[upBlock2].setActive(false);
		a[obstacle7].setVisible(false);
		a[obstacle7].setActive(false);
		a[obstacle8].setVisible(false);
		a[obstacle8].setActive(false);
		a[obstacle9].setVisible(false);
		a[obstacle9].setActive(false);
	}
	if(level == 3) {
		blocksLeft = 8;
		avatar.setNextLevel(false);
		smallGateOpen = false;
		largeGateOpen = false;

		a[companion].setVelocity(VECTOR2(0,0));
		a[downBlock1].setVelocity(VECTOR2(0,0));
		a[downBlock2].setVelocity(VECTOR2(0,0));
		a[downBlock3].setVelocity(VECTOR2(0,0));
		a[leftBlock1].setVelocity(VECTOR2(0,0));
		a[leftBlock2].setVelocity(VECTOR2(0,0));
		a[rightBlock1].setVelocity(VECTOR2(0,0));
		a[upBlock1].setVelocity(VECTOR2(0,0));
		a[upBlock2].setVelocity(VECTOR2(0,0));
	
		avatar.setX(8*squareNS::WIDTH*MASTER_SCALE);
		avatar.setY(11*squareNS::HEIGHT*MASTER_SCALE);
		avatar.setCurrentFrame(13);

		a[downBlock1].setVisible(true); 
		a[downBlock1].setActive(true);
		a[downBlock1].setX(5*squareNS::WIDTH*MASTER_SCALE);
		a[downBlock1].setY(6*squareNS::HEIGHT*MASTER_SCALE);
		a[downBlock1].setAnimate(false);
		a[downBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[downBlock1].setMovable(true);

		a[downBlock2].setVisible(true); 
		a[downBlock2].setActive(true);
		a[downBlock2].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[downBlock2].setY(4*squareNS::HEIGHT*MASTER_SCALE);
		a[downBlock2].setAnimate(false);
		a[downBlock2].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[downBlock2].setMovable(true);

		a[downBlock3].setVisible(true); 
		a[downBlock3].setActive(true);
		a[downBlock3].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[downBlock3].setY(7*squareNS::HEIGHT*MASTER_SCALE);
		a[downBlock3].setAnimate(false);
		a[downBlock3].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[downBlock3].setMovable(true);

		a[leftBlock1].setVisible(true); 
		a[leftBlock1].setActive(true);
		a[leftBlock1].setX(6*squareNS::WIDTH*MASTER_SCALE);
		a[leftBlock1].setY(6*squareNS::HEIGHT*MASTER_SCALE);
		a[leftBlock1].setAnimate(false);
		a[leftBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[leftBlock1].setMovable(true);

		a[leftBlock2].setVisible(true); 
		a[leftBlock2].setActive(true);
		a[leftBlock2].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[leftBlock2].setY(6*squareNS::HEIGHT*MASTER_SCALE);
		a[leftBlock2].setAnimate(false);
		a[leftBlock2].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[leftBlock2].setMovable(true);

		a[rightBlock1].setVisible(true); 
		a[rightBlock1].setActive(true);
		a[rightBlock1].setX(7*squareNS::WIDTH*MASTER_SCALE);
		a[rightBlock1].setY(6*squareNS::HEIGHT*MASTER_SCALE);
		a[rightBlock1].setAnimate(false);
		a[rightBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[rightBlock1].setMovable(true);

		a[upBlock1].setVisible(true); 
		a[upBlock1].setActive(true);
		a[upBlock1].setX(12*squareNS::WIDTH*MASTER_SCALE);
		a[upBlock1].setY(9*squareNS::HEIGHT*MASTER_SCALE);
		a[upBlock1].setAnimate(false);
		a[upBlock1].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[upBlock1].setMovable(true);

		a[upBlock2].setVisible(true); 
		a[upBlock2].setActive(true);
		a[upBlock2].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[upBlock2].setY(9*squareNS::HEIGHT*MASTER_SCALE);
		a[upBlock2].setAnimate(false);
		a[upBlock2].setCurrentFrame(blockNS::BLOCK_START_FRAME);
		a[upBlock2].setMovable(true);

		a[companion].setAnimate(false);
		a[companion].setVisible(true);
		a[companion].setActive(true);
		a[companion].setNextLevel(false);
		a[companion].setX(14*squareNS::WIDTH*MASTER_SCALE);
		a[companion].setY(10*squareNS::WIDTH*MASTER_SCALE);

		largeGate.setAnimate(false);
		largeGate.setActive(true);
		largeGate.setCurrentFrame(0);

		smallGate.setAnimate(false);
		smallGate.setActive(true);
		smallGate.setCurrentFrame(0);	
		smallGate.setX(14*squareNS::WIDTH*MASTER_SCALE);

		a[obstacle1].setX(4*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setY(3*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle1].setVisible(true); 
		a[obstacle1].setActive(true);
		a[obstacle2].setX(5*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle2].setY(3*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle2].setVisible(true); 
		a[obstacle2].setActive(true);
		a[obstacle3].setX(6*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle3].setY(3*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle3].setVisible(true); 
		a[obstacle3].setActive(true);
		a[obstacle4].setX(7*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle4].setY(3*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle4].setVisible(true); 
		a[obstacle4].setActive(true);
		a[obstacle5].setX(8*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle5].setY(3*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle5].setVisible(true); 
		a[obstacle5].setActive(true);
		a[obstacle6].setX(11*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle6].setY(9*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle6].setVisible(true); 
		a[obstacle6].setActive(true);
		a[obstacle7].setX(11*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle7].setY(10*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle7].setVisible(true); 
		a[obstacle7].setActive(true);
		a[obstacle8].setX(13*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle8].setY(9*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle8].setVisible(true); 
		a[obstacle8].setActive(true);
		a[obstacle9].setX(11*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle9].setY(11*squareNS::WIDTH*MASTER_SCALE);
		a[obstacle9].setVisible(true); 
		a[obstacle9].setActive(true);

		//NOT USED THIS LEVEL:
	}
	if(level == 4)
	{
		audio->stopCue(CHOPIN);
		audio->playCue(BELL);

		a[companion].setHealth(5);
		avatar.setNextLevel(false);
		smallGateOpen = true;
		largeGateOpen = false;
		cubeDead = false;

		a[companion].setVelocity(VECTOR2(0,0));

		a[spike1].setVisible(true);
		a[spike1].setActive(true);
		a[spike2].setVisible(true);
		a[spike2].setActive(true);
		a[spike3].setVisible(true);
		a[spike3].setActive(true);
		a[spike4].setVisible(true);
		a[spike4].setActive(true);
		a[spike5].setVisible(true);
		a[spike5].setActive(true);
	
		avatar.setX(7*squareNS::WIDTH*MASTER_SCALE);
		avatar.setY(11*squareNS::HEIGHT*MASTER_SCALE);
		avatar.setCurrentFrame(13);

		a[companion].setAnimate(false);
		a[companion].setVisible(true);
		a[companion].setActive(true);
		a[companion].setNextLevel(false);
		a[companion].setX(10*squareNS::WIDTH*MASTER_SCALE);
		a[companion].setY(10*squareNS::WIDTH*MASTER_SCALE);
		a[companion].setCurrentFrame(0);
		a[companion].setMovable(true);

		largeGate.setAnimate(false);
		largeGate.setActive(true);
		largeGate.setCurrentFrame(0);

		//NOT USED THIS LEVEL:
		a[leftBlock1].setVisible(false);
		a[leftBlock1].setActive(false);
		a[leftBlock2].setVisible(false);
		a[leftBlock2].setActive(false);
		a[rightBlock1].setVisible(false);
		a[rightBlock1].setActive(false);
		a[downBlock1].setVisible(false);
		a[downBlock1].setActive(false);
		a[downBlock2].setVisible(false);
		a[downBlock2].setActive(false);
		a[downBlock3].setVisible(false);
		a[downBlock3].setActive(false);
		a[upBlock1].setVisible(false);
		a[upBlock1].setActive(false);
		a[upBlock2].setVisible(false);
		a[upBlock2].setActive(false);
		a[obstacle1].setVisible(false);
		a[obstacle1].setActive(false);
		a[obstacle2].setVisible(false);
		a[obstacle2].setActive(false);
		a[obstacle3].setVisible(false);
		a[obstacle3].setActive(false);
		a[obstacle4].setVisible(false);
		a[obstacle4].setActive(false);
		a[obstacle5].setVisible(false);
		a[obstacle5].setActive(false);
		a[obstacle6].setVisible(false);
		a[obstacle6].setActive(false);
		a[obstacle7].setVisible(false);
		a[obstacle7].setActive(false);
		a[obstacle8].setVisible(false);
		a[obstacle8].setActive(false);
		a[obstacle9].setVisible(false);
		a[obstacle9].setActive(false);
	}
	
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if(input->isKeyDown(VK_RETURN) && !gameStart) {
		gameStart = true;
		initializeLevel(level);
	}

		if(input->isKeyDown(VK_RETURN) && !gameStart && level >= 5) {
			level = 1;
			gameStart = true;
			initializeLevel(level);
	}

	if(input->wasKeyPressed(VK_ESCAPE)) {  //restart level
		initializeLevel(level);
	}
	avatar.update(frameTime);
	a[companion].update(frameTime);
	largeGate.update(frameTime);
	smallGate.update(frameTime);
	torch1.update(frameTime);
	torch2.update(frameTime);

	//blocks:
	a[downBlock1].update(frameTime);
	a[leftBlock1].update(frameTime);
	a[leftBlock2].update(frameTime);
	a[rightBlock1].update(frameTime);
	a[downBlock2].update(frameTime);
	a[downBlock3].update(frameTime);
	a[upBlock1].update(frameTime);
	a[upBlock2].update(frameTime);

	if(blocksLeft == 0 && !smallGateOpen) {  //open little gate
		audio->playCue(SMALL_GATE);
		smallGateOpen = true;
		a[companion].setNextLevel(true);
		smallGate.setAnimate(true);
	}
	
	if(a[companion].getY() == squareNS::HEIGHT*MASTER_SCALE && !largeGateOpen)  //open large gate
	{
		audio->playCue(LARGE_GATE);
		largeGateOpen = true;
		largeGate.setAnimate(true);
		avatar.setNextLevel(true);
		if (level != 4)
			audio->playCue(NEXT_LEVEL);
	}

	if(avatar.getY() == 0) {    //go to next level
		level++;
		initializeLevel(level);
	}

	if(level == 4)
	{
		smallGate.setVisible(false);
		if(!largeGateOpen && cubeDead)
		{
			audio->playCue(LARGE_GATE);
			largeGateOpen = true;
			largeGate.setAnimate(true);
			avatar.setNextLevel(true);
			if (level != 4)
				audio->playCue(NEXT_LEVEL);
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
 VECTOR2 collisionVector;

	//AVATAR COLLISIONS
	for(int i = 0; i < 23; i++)
	{
		if(avatar.collidesWith(a[i], collisionVector))
		{
			if((avatar.getY()+avatar.getHeight()*avatar.getScale() > a[i].getY())&&(avatar.getY()<a[i].getY()+a[i].getHeight()*a[i].getScale())) {
				if(avatar.getX() < a[i].getCenterX()) { //coming from left
					if(avatar.getVelocity().x > 0)
						avatar.setX(a[i].getX()-avatar.getWidth()*avatar.getScale());
					if(input->isKeyDown(VK_SPACE)&&avatar.getDirectionFacing()==avatarNS::RIGHT && a[i].getMovable() && (avatar.getY() < a[i].getCenterY() && avatar.getY()+squareNS::WIDTH*MASTER_SCALE > a[i].getCenterY())) {
						audio->playRandomCue(PUSH1, PUSH2, PUSH3);
						a[i].setVelocity(VECTOR2(blockNS::SPEED, 0));
					}
				}
				else if(avatar.getX() > a[i].getCenterX()) { //coming from right
					if(avatar.getVelocity().x < 0)
						avatar.setX(a[i].getX()+a[i].getWidth()*a[i].getScale());
					if(input->isKeyDown(VK_SPACE)&&avatar.getDirectionFacing()==avatarNS::LEFT && a[i].getMovable() && (avatar.getY() < a[i].getCenterY() && avatar.getY()+squareNS::WIDTH*MASTER_SCALE > a[i].getCenterY())) {
						a[i].setVelocity(VECTOR2(-blockNS::SPEED, 0));
						audio->playRandomCue(PUSH1, PUSH2, PUSH3);
					}
				}
			}
			if((avatar.getX()+avatar.getWidth()*avatar.getScale() > a[i].getX())&&(avatar.getX()<a[i].getX()+a[i].getWidth()*a[i].getScale())) {
				if(avatar.getY() < a[i].getCenterY()) { //coming from top
					if(avatar.getVelocity().y > 0)
						avatar.setY(a[i].getY()-avatar.getHeight()*avatar.getScale());
					if(input->isKeyDown(VK_SPACE)&&avatar.getDirectionFacing()==avatarNS::DOWN && a[i].getMovable() && (avatar.getX() < a[i].getCenterX() && avatar.getX()+squareNS::WIDTH*MASTER_SCALE > a[i].getCenterX())) {
						a[i].setVelocity(VECTOR2(0, blockNS::SPEED));
						audio->playRandomCue(PUSH1, PUSH2, PUSH3);
					}
				}
				else if(avatar.getY() > a[i].getCenterY()) { //coming from bottom
					if(avatar.getVelocity().y < 0)
						avatar.setY(a[i].getY()+a[i].getHeight()*a[i].getScale());
					if(input->isKeyDown(VK_SPACE)&&avatar.getDirectionFacing()==avatarNS::UP && a[i].getMovable() && (avatar.getX() < a[i].getCenterX() && avatar.getX()+squareNS::WIDTH*MASTER_SCALE > a[i].getCenterX())) {
						a[i].setVelocity(VECTOR2(0, -blockNS::SPEED));
						audio->playRandomCue(PUSH1, PUSH2, PUSH3);
					}
				}
			}
		}
	}

	//COLLISIONS BETWEEN BLOCKS
	for(int i = 0; i < 23; i++)
	{
		for(int j = 0; j < i; j++)
		{
			//collision for a[j]  and a[i] 
			if(a[j].collidesWith(a[i], collisionVector))
				{
					if(a[j].getCenterY() == a[i].getCenterY()) {
						if(a[j].getX() < a[i].getX()) {  //a[j] on left and a[i] on right
							if(a[j].getVelocity().x != 0)	{
								a[j].setX(a[i].getX()-a[i].getWidth()*a[i].getScale());
								a[j].setVelocity(VECTOR2(0,0));
								//a[j].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::LEFT) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else 
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::RIGHT) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
							else if(a[i].getVelocity().x != 0)
							{
								a[i].setX(a[j].getX()+a[j].getWidth()*a[j].getScale());
								a[i].setVelocity(VECTOR2(0,0));
								//a[i].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::LEFT) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else 
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::RIGHT) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
						}
						else {   //a[j] on right and a[i] on left
							if(a[j].getVelocity().x != 0) {
								a[j].setX(a[i].getX()+a[i].getWidth()*a[i].getScale());
								a[j].setVelocity(VECTOR2(0,0));
								//a[j].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::RIGHT) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else 
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::LEFT) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
							else if(a[i].getVelocity().x != 0)
							{
								a[i].setX(a[j].getX()-a[i].getWidth()*a[i].getScale());
								a[i].setVelocity(VECTOR2(0,0));
								//a[i].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::RIGHT) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::LEFT) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
						}
					}
					else if(a[j].getCenterX() == a[i].getCenterX()) {
						if(a[j].getY() < a[i].getY()) {    //a[j] on top and a[i] on bottom
							if(a[j].getVelocity().y != 0)	 {
								a[j].setVelocity(VECTOR2(0,0));
								a[j].setY(a[i].getY()-a[i].getHeight()*a[i].getScale());
								//a[j].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::TOP) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::BOTTOM) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else 
									audio->playCue(HIT);
							}
							else if(a[i].getVelocity().y != 0)
							{
								a[i].setVelocity(VECTOR2(0,0));
								a[i].setY(a[j].getY()+a[j].getHeight()*a[j].getScale());
								//a[i].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::TOP) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::BOTTOM) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
				
						}
						else {     //a[j] on bottom and a[i] on top
							if(a[j].getVelocity().y != 0) {
								a[j].setVelocity(VECTOR2(0,0));
								a[j].setY(a[i].getY()+a[i].getHeight()*a[i].getScale());
								//a[j].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::BOTTOM) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::TOP) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
							else if(a[i].getVelocity().y != 0)
							{
								a[i].setVelocity(VECTOR2(0,0));
								a[i].setY(a[j].getY()-a[i].getHeight()*a[i].getScale());
								//a[i].setHealth(a[j].getHealth()-1);
								if(a[i].getCrackSide() == blockNS::BOTTOM) {
									a[i].setActive(false);
									a[i].setAnimate(true);
									a[i].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
								if(a[j].getCrackSide() == blockNS::TOP) {
									a[j].setActive(false);
									a[j].setAnimate(true);
									a[j].setMovable(false);
									blocksLeft--;
								}
								else
									audio->playCue(HIT);
							}
						}
					}
				}
		}
	}

	//special case for breaking the companion cube at the end

			if(a[spike5].collidesWith(a[companion], collisionVector))
			{
								a[companion].setX(a[spike5].getX()+a[spike5].getWidth()*a[spike5].getScale() + 1);
								a[companion].setVelocity(VECTOR2(0,0));
								cubeDead = true;
								a[companion].setAnimate(true);
			}
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	
	if(level != 5)
	{
		topLeftWall.draw();
		topRightWall.draw();
		leftWall.draw();
		rightWall.draw();
		bottomWall.draw();
		largeGate.draw();
		smallGate.draw();
		avatar.draw();
		a[obstacle1].draw();
		a[obstacle2].draw();
		a[obstacle3].draw();
		a[obstacle4].draw();
		a[obstacle5].draw();
		a[obstacle6].draw();
		a[obstacle7].draw();
		a[obstacle8].draw();
		a[obstacle9].draw();

		a[spike1].draw();
		a[spike2].draw();
		a[spike3].draw();
		a[spike4].draw();
		a[spike5].draw();
	
		//blocks:
		a[downBlock1].draw();
		a[leftBlock1].draw();
		a[leftBlock2].draw();
		a[rightBlock1].draw();
		a[downBlock2].draw();
		a[downBlock3].draw();
		a[upBlock1].draw();
		a[upBlock2].draw();
		a[companion].draw();

		torch1.draw();
		torch2.draw();

	}

	if(!gameStart)
		splashScreen.draw();

	if(level >= 5)
	{
		audio->stopCue(CHOPIN);
		audio->playCue(END_CREDITS);

		avatar.setActive(false);
		static int finalTime = GetTickCount()/1000;
		score.draw();
		stringstream ss;
		ss << "Final score: ";
		ss << finalTime - startTime;
		ss << " seconds";
		endFont->print(ss.str(),GAME_WIDTH/2 - 300, GAME_HEIGHT/2 - 75);
		
		
		static int start = GetTickCount();
		if(GetTickCount() - start >= 5000)
		{
			credits.draw();

			static int start1 = GetTickCount();
			if(GetTickCount() - start1 >= 8000)
			{
				endScreen.draw();
				gameStart = false;
			}
		}
	}


    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
  
	avatarTexture.onLostDevice();
	leftRightBlockTexture.onLostDevice();
	upBlockTexture.onLostDevice();
	downBlockTexture.onLostDevice();
	obTexture.onLostDevice();
	spikeBlockTexture.onLostDevice();
	sideWallTexture.onLostDevice();
	bottomWallTexture.onLostDevice();
	topWallTexture.onLostDevice();
	companionTexture.onLostDevice();
	largeGateTexture.onLostDevice();
	smallGateTexture.onLostDevice();
	splashScreenTexture.onLostDevice();
	creditsTexture.onLostDevice();
	endScreenTexture.onLostDevice();
	scoreTexture.onLostDevice();
	torchTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
  
	avatarTexture.onResetDevice();
	leftRightBlockTexture.onResetDevice();
	upBlockTexture.onResetDevice();
	downBlockTexture.onResetDevice();
	obTexture.onResetDevice();
	spikeBlockTexture.onResetDevice();
	sideWallTexture.onResetDevice();
	bottomWallTexture.onResetDevice();
	topWallTexture.onResetDevice();
	companionTexture.onResetDevice();
	largeGateTexture.onResetDevice();
	smallGateTexture.onResetDevice();
	splashScreenTexture.onResetDevice();
	creditsTexture.onResetDevice();
	endScreenTexture.onResetDevice();
	scoreTexture.onResetDevice();
	torchTexture.onResetDevice();
    
	Game::resetAll();
    return;
}
