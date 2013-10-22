/*Board.java*/

package player;

/**
 * This is Board class that contains all the chips. Every player
 * should have their own internal board
 */
 
public class Board{
	
	//board is made with 2 dimentional array of Chip objects
    public int width;
    public int height;
    public Chip[][] board;
	
	//construct a new board with a width and height, all the chips are unvisited
	public Board(int width, int height){
		board = new Chip[width][height];
		this.width=width;
		this.height=height;
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				board[i][j]=new Chip();//newly added
				board[i][j].x=i;
				board[i][j].y=j;
			}
		}
		//System.out.println("width: " + width);
		//System.out.println("width: " + this.width);
		//System.out.println("Create board done");
	}
	
	
	/**
	 *It takes in a color and determine whether this 
	 *color has won on the current board. It calls explore();
	 *@return True as has won
	 *This is to be implemented. 
	 */ 
	public boolean hasWon(int color){
	    /*int chipCount=0;
	    loop:
	    for(int j=0; j<this.width; j++)//count already placed chips
	  {
	      for(int k=0; k<this.height; k++)
		  {
		      if(board[j][k].color == color)
			  chipCount++;
		      if(chipCount>5)
			  break loop;
		  }
	  }
	    if(chipCount<6)//return false if not enough chips to make network
		return false;*/

		if(color==Chip.BLACK){//for black, we only detect the up goal area
		    //System.out.println("hasWon(): start to check black");
			for(int i=1;i<(width-1);i++){
				int j=0;
				if(board[i][j].color!=Chip.EMPTY){//only explore it when it's not empty
				    if(board[i][j].color==Chip.WHITE) //System.out.println("Error: White chip in black goal!!");
					setAllUnvisited();//set the whole board unvisited
					//if we find a net work begin with this goal chip
					if(explore(Chip.BLACK,board[i][j],0,0)){
					    //System.out.println("Black has a network");
						return true;
					}else{
						continue;
					}
				}
			}
			//System.out.println("Black doesn't has a network");
		}
		if(color==Chip.WHITE){//for white, we only detect the left goal area
		    //System.out.println("hasWon(): start to check white");
			int i=0;
			for(int j=1;j<height-1;j++){
				if(board[i][j].color!=Chip.EMPTY){//only explore it when it's not empty
				    if(board[i][j].color==Chip.BLACK) //System.out.println("Error: black chip in white goal!!");
					setAllUnvisited();//set the whole board unvisited
					//if we find a net work begin with this goal chip
					if(explore(Chip.WHITE,board[i][j],0,0)){
					    //System.out.println("White has a network");
						return true;
					}else{
						continue;
					}
				}
			}
			//System.out.println("White doesn't has a network");	
		}
		
		return false;
	}
	
	
	/**
	 * This method is called by hasWon(), which helps to determin if 
	 * there is a network for given color. It looks to every direction
	 * to find a "neighbor" chip with same color
	 * 
	 * @param color is the color we are exploring
	 * @param chip is the current chip we are standing on
	 * @param length is the # of chips we have already visited, 
	 * 		  not including the current one
	 * @param dir is the previous direction (where we came from
	 * @return boolean. true for there is a network
	 * 
	 */
	public boolean explore(int color, Chip chip, int length, int dir){
		
	    //System.out.println("explore(): exploring chip at index:"+chip.x+","+chip.y+" Current length is:"
	    //+length+" Prev direction is:"+dir);
		//store the x and y coordinate of chip into tempx and tempy;
		int tempx=chip.x;
		int tempy=chip.y; 
		
		//set this chip to visited
		chip.visitedOrNot=Chip.VISITED;
		
		//for each direction
		for(int i=-1;i<=1;i++){
			for(int j=-1;j<=1;j++){
				if(i==0&&j==0) continue;//00 means itself
				
				//if we are in the same direction, cotinue
				if((i*10+j)==dir){
					continue;
				}
				
				//find the neighbor in this direction, store the neighbor color in int col, x and y in x,y 
				//if no neighbor, outOfRange=0
				int outOfRangeFlag=0;//0 indicates that it is out of range, 1 is for find a neighbor
				Chip temChip=new Chip();
				for(int k=1;;k++){
					if((tempx+k*i)>=width||(tempx+k*i)<0){//x is out of board
						break;//out of range,no neighbor found
					}
					if((tempy+k*j)>=height||(tempy+k*j)<0){//y is out of board
						break;//out of range,no neighbor found
					}	
					//if find one, get out
					if(board[tempx+k*i][tempy+k*j].color!=Chip.EMPTY){
						outOfRangeFlag=1;
						temChip=board[tempx+k*i][tempy+k*j];
						break;
					}
				}
				
				
				if(outOfRangeFlag==0){//if no neighbor found
					continue;
				}
				if(temChip.color!=color){//if the neighbor is not the same color
					continue;
				}
				//detect if neighbor is in start goal
				if(color==Chip.BLACK){
					if(temChip.y==0) continue;
				}
				if(color==Chip.WHITE){
					if(temChip.x==0) continue;
				}
				
				if(temChip.visitedOrNot==Chip.VISITED){//if it has already been visited
					continue;
				}
				//if we reach the end goal
				if((color==Chip.BLACK)&&(temChip.y==(height-1))||(color==Chip.WHITE)&&(temChip.x==(width-1))){
					if(length>=4){
					    //System.out.println("We have reach the end goal!");
						return true;
					}
				}else{//if we haven't reach it yet
					if(explore(color,temChip,length+1,i*10+j)) return true;
				}
			}
		}
		chip.visitedOrNot=Chip.UNVISITED;
		return false;
	}
	
	
	/**
	 * This is used in score(),to help check the possibility to form a network
	 * depending on how many chips it is connect
	 * 
	 */
	 public int exploreInScore(int color, Chip chip, int length, int dir){
		//System.out.println("exploreInScore(): exploring chip at index:"+chip.x+","+chip.y+" Current length is:"
	    					  //+length+" Prev direction is:"+dir);
		int tempx=chip.x;
		int tempy=chip.y; 
		
		//set this chip to visited
		chip.visitedOrNot=Chip.VISITED;
		
		//for each direction
		for(int i=-1;i<=1;i++){
			for(int j=-1;j<=1;j++){
				//System.out.println("exploring direction: "+i+j);
				if(i==0&&j==0) continue;//00 means itself
				
				//if we are in the same direction, cotinue
				if((i*10+j)==dir||(i*10+j)==(0-dir)){
					continue;
				}
				
				//find the neighbor in this direction, store the neighbor color in int col, x and y in x,y 
				//if no neighbor, outOfRange=0
				int outOfRangeFlag=0;//0 indicates that it is out of range, 1 is for find a neighbor
				Chip temChip=new Chip();
				for(int k=1;;k++){
					if((tempx+k*i)>=width||(tempx+k*i)<0){//x is out of board
						break;//out of range,no neighbor found
					}
					if((tempy+k*j)>=height||(tempy+k*j)<0){//y is out of board
						break;//out of range,no neighbor found
					}	
					//if find one, get out
					if(board[tempx+k*i][tempy+k*j].color!=Chip.EMPTY){
						outOfRangeFlag=1;
						temChip=board[tempx+k*i][tempy+k*j];
						break;
					}
				}
				
				
				if(outOfRangeFlag==0){//if no neighbor found
					continue;
				}
				if(temChip.color!=color){//if the neighbor is not the same color
					continue;
				}
				//detect if neighbor is in start goal
				/*if(color==Chip.BLACK){
					if(temChip.y==0) continue;
				}
				if(color==Chip.WHITE){
					if(temChip.x==0) continue;
				}*/
				
				if(temChip.visitedOrNot==Chip.VISITED){//if it has already been visited
					continue;
				}
				//if we reach the end goal
				if( (color==Chip.BLACK)&&((temChip.y==(height-1))||(temChip.y==0))
					||(color==Chip.WHITE)&&((temChip.x==(width-1))||(temChip.x==0)) ){
					if(length>=4){
					    //System.out.println("We have reach the end goal!");
						return 4;
					}else{
						return length;
					}
					
				}else{//if we haven't reach it yet
					int k=exploreInScore(color,temChip,length+1,i*10+j);
					if(k>=0) {
						//System.out.println("k is: "+k);
						return k;
					}else{
						continue;
					}
				}
			}
		}
		chip.visitedOrNot=Chip.UNVISITED;
		return -1;
		 
	 }
	 
	/**
     * This method will give a score to a move on the current board 
     * -100 means error
     * should pass the legal test first!!
     */
	public int score(Move m,int color){
		//if this is a quit move,return -100
		if(m.moveKind==Move.QUIT){
			System.out.println("Quit Move");
			return -100;
		}
		
		int col=0,oppCol=0;//to store my color and opp's color
		if(color==Chip.WHITE){
			col=Chip.WHITE;
			oppCol=Chip.BLACK;
		}
		if(color==Chip.BLACK){
			col=Chip.BLACK;
			oppCol=Chip.WHITE;
		}
		if(color==Chip.EMPTY){
			System.out.println("ERROR in method score()! Given color is EMPTY!");
			return -100;
		}
		
		//creating a new board for using in this method
		Board b=new Board(this.width,this.height);
		for(int i=0;i<width;i++){//copying the current board to the new board
			for(int j=0;j<height;j++){
				b.board[i][j].color=this.board[i][j].color;
			}
		}
		b.forceMove(m,color);//apply the move to the new board
		
		//Now start giving score!!
		
		//1.if the other color win after this step, give a -50 score (must be judged before 2)
		if(b.hasWon(1-col)) return -50;		
		
		//2.if the color will win, score 100
		if(b.hasWon(col)) return 100;		
		
		/*//3.giveing score according to potential
		int l=exploreInScore(col,b.board[m.x1][m.y1],0,0);
		int scoreOfPotential=0;
		if(l!=-1){
			scoreOfPotential=(l+1)*8;
		}
		System.out.println("The potential of making a network is: "+scoreOfPotential);*/
		
		//3.(1)if the current move has a same color neigbor arround it,add 8 to every neighbor
		//  	*if the neighbor is next to it, only add 6 (easy to form cluster)
		// 	 	*if we find a neighbor in a given direction, 
		//			then we -1 everytimewe we find another in the same direction
		//	(2)if this move will add a block to the opponent color (move is between two opponent chips), add add 2 in ADD or 6 in STEP
		int scoreForNeighbor=0;				//storing the score
		int tempx=m.x1,tempy=m.y1;
		int[] oppBlockArray=new int[23];	//for storing flags for blocking opponent lines
		for(int i=0;i<23;i++){					//initializing the array
			oppBlockArray[i]=0;
		}
		//for each direction,check neighbor
		for(int i=-1;i<=1;i++){	
			for(int j=-1;j<=1;j++){
				if(i==0&&j==0) continue;	//00 means it is itself
				int firstFindFlag=0;		//0 indicate it's the first time finding in the same direction
				for(int k=1;;k++){
					if((tempx+k*i)>=width||(tempx+k*i)<0){//x is out of board
						break;				//out of range,no neighbor found
					}
					if((tempy+k*j)>=height||(tempy+k*j)<0){//y is out of board
						break;				//out of range,no neighbor found
					}	
					//if find one, do something and get out of the inner "for"
					if(b.board[tempx+k*i][tempy+k*j].color!=Chip.EMPTY){
						if(b.board[tempx+k*i][tempy+k*j].color==(1-col)){
							if(oppBlockArray[(0-i)*10+(0-j)+11]==1){
								//System.out.println("It is blocking a opponent chip in the line direction: "+i+j+
													//" add 2 in ADD or 6 in STEP");
								if(m.moveKind==Move.ADD){
									scoreForNeighbor+=2;
								}else{
									scoreForNeighbor+=6;
								}
							}else{
								oppBlockArray[i*10+j+11]=1;
							}
						}
						if(b.board[tempx+k*i][tempy+k*j].color==col){//if it's the same color
							if(firstFindFlag==0){//if this is the first time find a neighbor
								if(k==1){//if it's next to it
								    //System.out.println("Find a neighbor right next to it,in dir: "+i+j+" ,add 6");
									scoreForNeighbor+=6;
								}else{
								    //System.out.println("Find a neighbor NOT right next to it,in dir: "+i+j+",add 8");
									scoreForNeighbor+=8;
								}
								firstFindFlag++;
							}else{
							    //System.out.println("Find a neighbor in same dir,minus 1");
								scoreForNeighbor-=1;
							}
							continue;//go on to detect the next one in this direction
						}
						break;
					}
				}
			}
		}
		
		//4. if it's in a goal area and it's the only chip in this goal area after the step, add 8 to the score. 
		//   If there're 2 in it, add 6.
		int goalAreaScore=0;
		int flag=0;//storing the number of chip in this goal area
		tempx=m.x1;
		tempy=m.y1;
		if(tempx==0||tempy==0||tempx==7||tempy==7){
			if(tempx==0||tempx==7){
				for(int i=0;i<8;i++){
					if(b.board[tempx][i].color==color) flag++;
				}
			}
			if(tempy==0||tempy==7){
				for(int i=0;i<8;i++){
					if(b.board[i][tempy].color==color) flag++;
				}
			}
			if(flag==1){
				//System.out.println("This is the only chip in this goal area! score+8");
				goalAreaScore+=8;
			}
			if(flag==2){
				goalAreaScore+=6;
			}
		}
		
		int finalScore=scoreForNeighbor+goalAreaScore;
		//making the final score
		//System.out.println("In score(), checking move: "+m+" color: "+color+" giving score: "+finalScore);
		return finalScore;
		
	}
	/**
	 * This is used in Board.score(), to apply a move to a board. In Board.java The one in MachinePlayer.java will call this one
	 */
	 public void forceMove(Move m, int col){
		 if(m.moveKind==Move.ADD){
			 this.board[m.x1][m.y1].color=col;
		 }
		 if(m.moveKind==Move.STEP){
			 this.board[m.x2][m.y2].color=Chip.EMPTY;
			 this.board[m.x1][m.y1].color=col;
		 }
	 }
	
	
	/**
	 * Set all chips on the board to unvisited, called in method hasWon().
	 */
	public void setAllUnvisited(){
	    //System.out.println("setAllUnvisited() begin");//4 test
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(i==0&&(j==0||j==(height-1))) continue;//if it's one of the left corners, skip
				if(i==(width-1)&&(j==0||j==(height-1))) continue;//if it's one of the right corners, skip
				board[i][j].visitedOrNot=Chip.UNVISITED;
			}
		}
		//System.out.println("setAllUnvisited() done");//4 test
	}
	
	 public static void main(String[] args){
		 Board test=new Board(8,8);
		 test.board[1][1].color=Chip.WHITE;
		 test.board[7][1].color=Chip.WHITE;
		 //test.board[4][2].color=Chip.WHITE;
		 test.board[0][3].color=Chip.WHITE;
		 test.board[4][4].color=Chip.WHITE;
		 test.board[5][4].color=Chip.WHITE;
		 test.board[3][1].color=Chip.WHITE;
		 test.board[2][4].color=Chip.BLACK;
		 test.board[4][2].color=Chip.BLACK;
		 Move m2=new Move(3,3);
		 int s2=test.score(m2,Chip.WHITE);
	}
}
