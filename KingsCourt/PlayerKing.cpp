/*******************************************************************
*
*  DESCRIPTION: Atomic Model PlayerKing
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
#include "PlayerKing.h"

PlayerKing::PlayerKing( const string &name ) : 
Atomic( name ), 
thinkingTime(0,0,0,1),
PLAY( addInputPort( "PLAY" ) ), 
MISS( addInputPort( "MISS" ) ), 
BBK( addInputPort( "BBK" ) ), 
BB2( addOutputPort( "BB2" ) ), 
BB3( addOutputPort( "BB3" ) ), 
BB1( addOutputPort( "BB1" ) ), 
MISS_Out( addOutputPort( "MISS_Out" ) )
{
	
}


/* 
 * initFunction
 * Initiates the model.
 */
Model &PlayerKing::initFunction(){
	pState = idle;
	sendBB2 = false;
	sendBB3 = false;
	sendBB1 = false;
	sendMISS = false;
	random = 0;
	passivate();
	return *this;
}

/* 
 * externalFunction
 * 
 */
Model &PlayerKing::externalFunction( const ExternalMessage &msg ){
	if(msg.port() == MISS && (pState==attacking || pState==defending)){
		pState = idle;
		sendBB1 = false;
		sendBB3 = false;
		sendBB2 = false;
		sendMISS = false;
		random = 0;
		passivate();	
		return *this;	
	}
	else if(msg.port() == PLAY && pState == idle){
		// player was in idle state and now there
		// is enough players to begin playing the game.
		// ball hit, decide who to hit too
		random = (double)rand()/(double)RAND_MAX;
		if(random < 0.33){
			sendBB2 = true;
		}
		else if(random < 0.67){
			sendBB3 = true;
		}
		else{
			sendBB1 = true;
		}
		pState = attacking;
		holdIn(active, thinkingTime);
	}
	else{
		random = (double)rand()/(double)RAND_MAX;
		if(random < 0.20){
			// ball missed or hit out of court
			sendMISS=true;
		}
		else{
			// ball hit, decide who to hit too
			random = (double)rand()/(double)RAND_MAX;
			if(random < 0.33){
				sendBB2 = true;
			}
			else if(random < 0.67){
				sendBB3 = true;
			}
			else{
				sendBB1 = true;
			}
		}
		pState = attacking;
		holdIn(active, thinkingTime);
	}
	return *this;
}

/* 
 * internalFunction
 * If the player was attacking they now return to the
 * defending state and wait until they are notified the
 * ball is in their square or the ball was missed.
 */
Model &PlayerKing::internalFunction( const InternalMessage &msg ){
	if(pState==attacking){
		pState=defending;
	}
	passivate();
	return *this;
}

/* 
 * outputFunction
 * Sends the output depending on decision
 * made when the player was attacking.
 */
Model &PlayerKing::outputFunction( const InternalMessage &msg ){
	if(sendBB2){
		sendOutput( msg.time(), BB2, 4);	
	}
	else if(sendBB3){
		sendOutput( msg.time(), BB3, 4);
	}
	else if(sendBB1){
		sendOutput( msg.time(), BB1, 4);
	}
	else{
		sendOutput( msg.time(), MISS_Out, 4);
		pState = idle;
		sendBB1 = false;
		sendBB3 = false;
		sendBB2 = false;
		sendMISS = false;
		random = 0;
		passivate();	
		return *this;
	}
	// reset the booleans
	sendBB2 = false;
	sendBB3 = false;
	sendBB1 = false;
	sendMISS = false;
	return *this;
}