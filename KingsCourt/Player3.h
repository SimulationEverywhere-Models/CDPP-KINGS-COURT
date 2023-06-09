/*******************************************************************
*
*  DESCRIPTION: Atomic Model Player3
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 26/10/2007
*
*******************************************************************/
#ifndef __PLAYER3_H
#define __PLAYER3_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class Player3: public Atomic
{
public:
	Player3( const string &name = "Player3" ) ;	 // Default constructor

	virtual string className() const
		{return "Player3";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &PLAY;
	const Port &MISS;
	const Port &BB3;
	Port &BB2;
	Port &BB1;	
	Port &BBK;
	Port &MISS_Out;
	bool sendBB2;
	bool sendBB1;
	bool sendBBK;
	bool sendMISS;
	double random;
	Time thinkingTime;
	enum PlayerState{attacking, defending, idle};
	PlayerState pState;
};	// class Player3


#endif    //__PLAYER3_H
