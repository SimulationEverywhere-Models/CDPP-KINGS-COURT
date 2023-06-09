/*******************************************************************
*
*  DESCRIPTION: Atomic Model PlayerCount
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 29/10/2007
*
*******************************************************************/
#ifndef __PLAYERCOUNT_H
#define __PLAYERCOUNT_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class PlayerCount: public Atomic
{
public:
	PlayerCount( const string &name = "PlayerCount" ) ;	 // Default constructor

	virtual string className() const
		{return "PlayerCount";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &NEW;
	const Port &MISS1;
	const Port &MISS2;
	const Port &MISS3;
	const Port &MISS4;
	Port &PLAY;
	enum PlayerState{full, notFull};
	PlayerState pState;
	int count;
	bool sendPlay;
	Time time;
};	// class PlayerCount


#endif    //__PLAYERCOUNT_H
