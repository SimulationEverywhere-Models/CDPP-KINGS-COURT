/*******************************************************************
*
*  DESCRIPTION: Atomic Model Player2
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
#include "Player2.h"

Player2::Player2( const string &name ) : 
Atomic( name ), 
thinkingTime(0,0,0,1),
PLAY( addInputPort( "PLAY" ) ), 
MISS( addInputPort( "MISS" ) ), 
BB2( addInputPort( "BB2" ) ), 
BB1( addOutputPort( "BB1" ) ), 
BB3( addOutputPort( "BB3" ) ), 
BBK( addOutputPort( "BBK" ) ), 
MISS_Out( addOutputPort( "MISS_Out" ) )
{
	
}


/* 
 * initFunction
 * Initiates the model.
 */
Model &Player2::initFunction(){
	pState = idle;
	sendBB1 = false;
	sendBB3 = false;
	sendBBK = false;
	sendMISS = false;
	random = 0;
	passivate();
	return *this;
}

/* 
 * externalFunction
 * 
 */
Model &Player2::externalFunction( const ExternalMessage &msg ){
	if(msg.port() == MISS && (pState==attacking || pState==defending)){
		pState = idle;
		sendBB1 = false;
		sendBB3 = false;
		sendBBK = false;
		sendMISS = false;
		random = 0;
		passivate();	
		return *this;	
	}
	else if(msg.port() == PLAY && pState == idle){
		// player was in idle state and now there
		// is enough players to begin playing the game.
		pState = defending;
		passivate();
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
				sendBB1 = true;
			}
			else if(random < 0.67){
				sendBB3 = true;
			}
			else{
				sendBBK = true;
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
Model &Player2::internalFunction( const InternalMessage &msg ){
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
Model &Player2::outputFunction( const InternalMessage &msg ){
	if(sendBB1){
		sendOutput( msg.time(), BB1, 2);	
	}
	else if(sendBB3){
		sendOutput( msg.time(), BB3, 2);
	}
	else if(sendBBK){
		sendOutput( msg.time(), BBK, 2);
	}
	else{
		sendOutput( msg.time(), MISS_Out, 2);
		pState = idle;
		sendBB1 = false;
		sendBB3 = false;
		sendBBK = false;
		sendMISS = false;
		random = 0;
		passivate();	
		return *this;
	}
	// reset the booleans
	sendBB1 = false;
	sendBB3 = false;
	sendBBK = false;
	sendMISS = false;
	return *this;
}