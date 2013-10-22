/* MachinePlayer.java */

package player;

/**
 *  An implementation of an automatic Network player.  Keeps track of moves
 *  made by both players.  Can select a move for itself.
 */
public class MachinePlayer extends Player {
	
	//fields, may need more...
    public Board board;
    public int color;
    public int searchDepth;
    private int currentDepth;

  // Creates a machine player with the given color.  Color is either 0 (black)
  // or 1 (white).  (White has the first move.)
  public MachinePlayer(int color) {
      this.color = color;
      this.searchDepth = 1;
      this.board = new Board(7,7);
  }

  // Creates a machine player with the given color and search depth.  Color is
  // either 0 (black) or 1 (white).  (White has the first move.)
  public MachinePlayer(int color, int searchDepth) {
      this.color = color;
      this.searchDepth = searchDepth;
      this.board = new Board(7,7);
  }

  // Returns a new move by "this" player.  Internally records the move (updates
  // the internal game board) as a move by "this" player.
  public Move chooseMove() {

      Move[] availableMoves = allLegalMoves(color, board);
      Move bestMove = availableMoves[0];
      int temp;
      int currentMax = 0;

      for(int i=0; i<availableMoves.length; i++)
	  {
	      temp= minimaxTree(availableMoves[i]);//test moves as add moves
	      if(temp>currentMax)
		  {
		      currentMax = temp;
		      bestMove = availableMoves[i];
		  }

	      for(int j=0; j<board.width-1; j++)//test move as step from each already placed chip
		  {
		      for(int k=0; k<board.height-1; k++)
			  {
			      if(board.board[j][k].color == color)
				  {
				      Move tempMove =
					  new Move(availableMoves[i].x1,
						   availableMoves[i].x2,
						   j, k);

				      temp = minimaxTree(tempMove);
				      if(temp>currentMax)
					  {
					      currentMax = temp;
					      bestMove = tempMove;
					  }
				  }
			  }
		  }
	  }

      board.board[bestMove.x1][bestMove.y1].color=color;

    return bestMove;
  } 

  // If the Move m is legal, records the move as a move by the opponent
  // (updates the internal game board) and returns true.  If the move is
  // illegal, returns false without modifying the internal state of "this"
  // player.  This method allows your opponents to inform you of their moves.
  public boolean opponentMove(Move m) {
      if(!isLegalMove(1-color,m,board)) return false;
	  board.forceMove(m,1-color);
	  return true;
  }

  // If the Move m is legal, records the move as a move by "this" player
  // (updates the internal game board) and returns true.  If the move is
  // illegal, returns false without modifying the internal state of "this"
  // player.  This method is used to help set up "Network problems" for your
  // player to solve.
  public boolean forceMove(Move m) {
      if(!isLegalMove(color,m,board)) return false;
      board.forceMove(m,color);
      return true;
  }
  
 /**
  * This would dertermine if the current move on the board is valid
  * Will call isCluster().
  * @param color is the color of chip that we are determine. It is benefitial 
  * 		if it's an add move, but not step move.
  * @param move is the move that we need to determine.
  * @param board is the board... Emm.. Hopefully it's stored internally
  * @return boolean. True if the move is leagel.
  * 
  * This needs to be implemented
  */
  public boolean isLegalMove(int color, Move move, Board board){

      /* System.out.println("x1: " + move.x1);
      System.out.println("y1: " + move.y1);
      System.out.println("width: " + this.board.width);
      System.out.println("height: " + this.board.height);*/

      if(move.x1 == move.x2 && move.y1 == move.y2)//stepping to same space
	  return false;

//cant be in corners
      if(move.x1 == 0 && move.y1 == 0)
	return false;
      if(move.x1 == 0 && move.y1 == 7)
	  return false;
      if(move.x1 == 7 && move.y1 == 0)
	  return false;
      if(move.x1 == 7 && move.y1 == 7)
	  return false;

      if(color == Chip.WHITE) //white, cant be in top or bottom
	      if(move.y1== 0 || move.y1 == 7)
		  return false;

      if(color == Chip.BLACK) // black, cant be in sides
	  if(move.x1 == 0 || move.x1 == 7)
	      return false;
	      
      
      if(board.board[move.x1][move.y1] == null)
	  {}
      else
	  {
	      if(board.board[move.x1][move.y1].color != Chip.EMPTY) //space cant be filled
		  return false;
	  }
	  

      if(isCluster(color, move, board))
	  return false;

     
      return true; //passed all rules

  }
   
 /**
  * This is to determine whether the current move will form a cluster.
  * Will be called by isLegalMove().
  * @param color is the color of chip that we are determine.
  * @param move is the move that we need to determine.
  * @param er..board is the board...
  * @return boolean. true if it will form a cluster
  * 
  * This needs to be implemented
  */
  public boolean isCluster(int color, Move move, Board board){

      int counter = 0;
      int otherX=0, otherY=0;

      if(move.y1!=0)
      if(board.board[move.x1][move.y1-1].color!=Chip.EMPTY)
	  {
	      otherX= move.x1;
	      otherY = move.y1-1;
	      counter++;
	  }
      if(move.x1!=6 && move.y1!=0)
      if(board.board[move.x1+1][move.y1-1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1+1;
	      otherY = move.y1-1;
	      counter++;
	  }
      if(move.x1!=6)
      if(board.board[move.x1+1][move.y1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1+1;
	      otherY = move.y1;
	      counter++;
	  }
      if(move.x1!=6 && move.y1!=6)
      if(board.board[move.x1+1][move.y1+1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1+1;
	      otherY = move.y1+1;
	      counter++;
	  }
      if(move.y1!=6)
      if(board.board[move.x1][move.y1+1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1;
	      otherY = move.y1+1;
	      counter++;
	  }
      if(move.x1!=0 && move.y1!=6)
      if(board.board[move.x1-1][move.y1+1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1-1;
	      otherY = move.y1+1;
	      counter++;
	  }
      if(move.x1!=0)
      if(board.board[move.x1-1][move.y1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1-1;
	      otherY = move.y1;
	      counter++;
	  }
      if(move.x1!=0 && move.y1!=0)
      if(board.board[move.x1-1][move.y1-1].color!=Chip.EMPTY)
	  {
	      otherX = move.x1-1;
	      otherY = move.y1-1;
	      counter++;
	  }
	  

      if(counter>=2)
	  return true;
      if(counter==1)//check around the other piece
	  {
	      if(otherY!=0)
	      if(board.board[otherX][otherY-1].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=6 && otherY!=0)
	      if(board.board[otherX+1][otherY-1].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=6)
	      if(board.board[otherX+1][otherY].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=6 && otherY!=6)
	      if(board.board[otherX+1][otherY+1].color!=Chip.EMPTY)
		  counter++;
	      if(otherY!=6)
	      if(board.board[otherX][otherY+1].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=0 && otherY!=6)
	      if(board.board[otherX-1][otherY+1].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=0)
	      if(board.board[otherX-1][otherY].color!=Chip.EMPTY)
		  counter++;
	      if(otherX!=0 && otherY!=0)
	      if(board.board[otherX-1][otherY-1].color!=Chip.EMPTY)
		  counter++;

	      if(counter>1)
		  return true;
	  }
	  

      return false;
  }

    public Move[] allLegalMoves(int color, Board board)
    {

	Move[] moves = new Move[board.height*board.width];
	Move currentMove;
	int k = 0;

	for(int i=0; i<board.height; i++)
	    {
		for(int j=0; j<board.width; j++)
		    {
			currentMove = new Move(j,i);
			//System.out.println("kind:  " + currentMove.moveKind);
			if(isLegalMove(color, currentMove, board))
			    {
				moves[k] = currentMove;
				k++;
			    }

		    }
	    }

	return moves;

    }

    public int minimaxTree(Move m)
    {

	currentDepth++;

	int currentColor;
	if(currentDepth%2==1)
	    currentColor = color;
	else
	    currentColor = 1 - color;

	Board tempBoard = board;
	tempBoard.forceMove(m, currentColor);
	Move[] moveList = allLegalMoves(currentColor, tempBoard);
	int[] scores = new int[moveList.length];
	int score = 0;


	
	if(currentDepth==searchDepth)
	    score = tempBoard.score(m, currentColor);
	else
	    {
		loop:
		for(int i = 0; i<moveList.length; i++)
		    {
			if(moveList[i]==null)
			    break loop;
			scores[i] = minimaxTree(moveList[i]);

			if(currentColor!=color)
			    {
				if(scores[i]<score)
				    score = scores[i];
			    }
			else
			    if(scores[i]>score)
				score = scores[i];

		    }
	    }


	return score;

    }
    

}
