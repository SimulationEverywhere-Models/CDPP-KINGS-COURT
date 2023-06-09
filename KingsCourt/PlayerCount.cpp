/*******************************************************************
*
*  DESCRIPTION: Atomic Model PlayerCount
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 27/10/2007
*
*******************************************************************/
#include "randlib.h"         // Random numbers library
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h" 
#include "PlayerCount.h"

PlayerCount::PlayerCount( const string &name ) : 
Atomic( name ), 
NEW( addInputPort( "NEW" ) ), 
MISS1( addInputPort( "MISS1" ) ), 
MISS2( addInputPort( "MISS2" ) ), 
MISS3( addInputPort( "MISS3" ) ), 
MISS4( addInputPort( "MISS4" ) ), 
PLAY( addOutputPort( "PLAY" ) ),
time(0,0,0,1)
{
	
}


/* 
 * initFunction
 * Initiates the model.
 */
Model &PlayerCount::initFunction(){
	count = 0;
	pState = notFull;
	sendPlay = false;
	passivate();
	return *this;
}

/* 
 * externalFunction
 * Check to see if there are a enough players to start a game
 * or if a player has left the game and a new player is needed
 * from the queue.
 */
Model &PlayerCount::externalFunction( const ExternalMessage &msg ){
	if((msg.port() == MISS1 || msg.port() == MISS2 || msg.port() == MISS3
			|| msg.port() == MISS4)){
		pState = notFull;
		count--;
		sendPlay = false;
		passivate();
	}
	else{
		count++;
		if (count==4){
			 sendPlay = true;
			 pState = full;
			 holdIn(active, time);
		}
		else{
			 sendPlay = false;
			passivate();	
		}
	}
	return *this;
}

/* 
 * internalFunction
 * Wait for a player to miss the ball or
 * for a new player to join the game.
 */
Model &PlayerCount::internalFunction( const InternalMessage &msg ){
	passivate();
	return *this;
}

/* 
 * outputFunction
 * Sends the output
 */
Model &PlayerCount::outputFunction( const InternalMessage &msg ){
	if(sendPlay){
		sendOutput(msg.time(), PLAY, 5);
	}
	return *this;
}