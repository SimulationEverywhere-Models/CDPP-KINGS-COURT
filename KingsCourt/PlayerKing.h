/*******************************************************************
*
*  DESCRIPTION: Atomic Model PlayerKing
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 26/10/2007
*
*******************************************************************/
#ifndef __PLAYERKING_H
#define __PLAYERKING_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class PlayerKing: public Atomic
{
public:
	PlayerKing( const string &name = "PlayerKing" ) ;	 // Default constructor

	virtual string className() const
		{return "PlayerKing";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &PLAY;
	const Port &MISS;
	const Port &BBK;
	Port &BB2;
	Port &BB3;	
	Port &BB1;
	Port &MISS_Out;
	bool sendBB2;
	bool sendBB3;
	bool sendBB1;
	bool sendMISS;
	double random;
	Time thinkingTime;
	enum PlayerState{attacking, defending, idle};
	PlayerState pState;
};	// class PlayerKing


#endif    //__PLAYERKING_H
