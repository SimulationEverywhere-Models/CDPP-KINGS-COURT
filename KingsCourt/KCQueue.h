/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue (named KCQueue)
*
*  AUTHOR: Karen Widish
*
*  EMAIL: kwidish@connect.carleton.ca
*
*  DATE: 30/10/2007
*
*******************************************************************/
#ifndef __KCQUEUE_H
#define __KCQUEUE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** declarations **/
class KCQueue: public Atomic
{
public:
	KCQueue( const string &name = "KCQueue" ) ;	 // Default constructor

	virtual string className() const
		{return "KCQueue";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage &msg );

	Model &internalFunction( const InternalMessage &msg );

	Model &outputFunction( const InternalMessage &msg );

private:
	const Port &IN;
	const Port &MISS;
	Port &NEW;
	int count;
	int fourCount;
	bool send;
	Time movingTime;
};	// class KCQueue

#endif    //__KCQUEUE_H