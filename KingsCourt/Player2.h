/*******************************************************************
*
*  DESCRIPTION: Atomic Model Player2
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 26/10/2007
*
*******************************************************************/
#ifndef __PLAYER2_H
#define __PLAYER2_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Player2: public Atomic
{
public:
	Player2( const string &name = "Player2" ) ;	 // Default constructor

	virtual string className() const
		{return "Player2";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &PLAY;
	const Port &MISS;
	const Port &BB2;
	Port &BB1;
	Port &BB3;	
	Port &BBK;
	Port &MISS_Out;
	bool sendBB1;
	bool sendBB3;
	bool sendBBK;
	bool sendMISS;
	double random;
	Time thinkingTime;
	enum PlayerState{attacking, defending, idle};
	PlayerState pState;
};	// class Player2


#endif    //__PLAYER2_H
