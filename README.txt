Player1, Player2, Player3, PlayerKing
********************************************
The test files for the 4 players are similar.  They simulate the player receiving the message that the game has begun.  Each player is then sent the ball a couple of times to see that they either send the ball to someone else or miss it.  Finally they are sent the miss event to simulate notifying them that someone else has missed the ball.

PlayerCount
**************
The test file for this simulates players arriving into the game.  Once four players have arrived the PlayerCount should send out the Play message to the players.  When the PlayerCount receives the miss message, it means one of the players has missed the ball and the PlayerCount can accept a new player into the game.

KingsCourt
*************
The KingsCourt test is to test the 4 players together with the PlayerCount.  Here new messages are sent to the PlayerCount.  These are players entering the court.  The game should start once 4 players are on the court.  The log file should show the ball being passed around till it is missed.  The test then sends another person into the game much later (hopefully after a missed ball) to show that the game can wait for a player after a missed ball and start again.

KCQueue
************
The testing of the queue has two events, in and miss.  When an in event is received the player is joining the line.  If there are not 4 players in the game yet, the player should go straight to the game, this is the new message.  When a miss occurs, it means the game is looking for another player.  If there is someone in line they should be sent to the game right away, by having the queue send a new message.  If there is no one in line, as soon as someone joins the line they should be sent to the game.

Top
*****
The top test is the entire system working together.  The only events being sent is the people arriving in line.  All other systems should behave as described in their individual tests.