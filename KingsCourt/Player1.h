/*******************************************************************
*
*  DESCRIPTION: Atomic Model Player1
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 26/10/2007
*
*******************************************************************/
#ifndef __PLAYER1_H
#define __PLAYER1_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Player1: public Atomic
{
public:
	Player1( const string &name = "Player1" ) ;	 // Default constructor

	virtual string className() const
		{return "Player1";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &PLAY;
	const Port &MISS;
	const Port &BB1;
	Port &BB2;
	Port &BB3;	
	Port &BBK;
	Port &MISS_Out;
	bool sendBB2;
	bool sendBB3;
	bool sendBBK;
	bool sendMISS;
	double random;
	Time thinkingTime;
	enum PlayerState{attacking, defending, idle};
	PlayerState pState;
};	// class Player1


#endif    //__PLAYER1_H
