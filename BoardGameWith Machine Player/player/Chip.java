/*Chip.java*/

package player;

/*
 * This is a Chip class, shows the propoties of a chip
 */
public class Chip{
	
	//This is for color, EMPTY means this chip is empty
	public final static int BLACK = 0;
	public final static int WHITE = 1;
	public final static int EMPTY = 2;
	
	//This is for the visit flag
	public final static int UNVISITED = 0;
	public final static int VISITED = 1;

	public int color = EMPTY;//initialized as EMPTY
	public int visitedOrNot = UNVISITED;//initialized as not visited
	public int x;//the x coordinate of this chip on the board (begin with 0)
	public int y;//the y coordinate of this chip on the board (begin with 0)
	
	//construct an empty Chip which is unvisited
	public Chip(){
		color = EMPTY;
		visitedOrNot = UNVISITED;
	}
	
	//construct an empty with col color
	public Chip(int col){
		color = col;
	}
}
