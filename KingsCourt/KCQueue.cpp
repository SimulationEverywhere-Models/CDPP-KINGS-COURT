/*******************************************************************
*
*  DESCRIPTION: Atomic Model KCQueue
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 30/10/2007
*
*******************************************************************/
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h" 
#include "KCQueue.h"

KCQueue::KCQueue( const string &name ) : 
Atomic( name ), 
movingTime(0,0,0,1),
IN( addInputPort( "IN" ) ), 
MISS( addInputPort( "MISS" ) ), 
NEW( addOutputPort( "NEW" ) )
{
	
}


/* 
 * initFunction
 * Initiates the model.
 */
Model &KCQueue::initFunction(){
	count = 0;
	fourCount = 0;
	send = false;
	return *this;
}

/* 
 * externalFunction
 * 
 */
Model &KCQueue::externalFunction( const ExternalMessage &msg ){
	if(msg.port() == IN){
		if(fourCount<4){
			// used in the beginning to send first
			// 4 players directly into game and when
			// the ball is missed and a new player is needed.
			fourCount++;
			holdIn(active, movingTime);
			send = true;
		}
		else{
			// add another person to the line waiting to play
			count++;
			if(send){
				holdIn(active, 0);
			}
			else{
				passivate();
			}
		}
	}
	else if(msg.port() == MISS){
		if(count==0){ // no one waiting to play
			fourCount--; // next player who comes goes straight to game
			passivate();
		}
		else{ // remove someone from the line and send to the game
			send = true;
			count--;
			holdIn(active, movingTime);
		}
	}
	return *this;
}

/* 
 * internalFunction
 */
Model &KCQueue::internalFunction( const InternalMessage &msg ){
	passivate();
	return *this;	
}

/* 
 * outputFunction
 * Sends the output
 */
Model &KCQueue::outputFunction( const InternalMessage &msg ){
	if(send){
		sendOutput(msg.time(), NEW, 1);
	}
	send = false;
	return *this;
}