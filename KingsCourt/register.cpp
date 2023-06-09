/*******************************************************************
*  DESCRIPTION: Simulator::registerNewAtomics()
*  AUTHOR: Karen Widish
*  EMAIL: kwidish@connect.carleton.ca
*  DATE: 29/10/2007
*******************************************************************/
#include "modeladm.h" 
#include "mainsimu.h"

//my header files
#include "Player1.h"        // class Player1
#include "Player2.h"        // class Player2
#include "Player3.h"        // class Player3
#include "PlayerKing.h"        // class PlayerKing
#include "PlayerCount.h"	// class PlayerCount
#include "KCQueue.h"	// class KCQueue


void MainSimulator::registerNewAtomics()
{
	//my atomic models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Player1>() , "Player1" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Player2>() , "Player2" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Player3>() , "Player3" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PlayerKing>() , "PlayerKing" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PlayerCount>() , "PlayerCount" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<KCQueue>() , "KCQueue" ) ;
}
