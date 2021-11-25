/********************Logic for printing space-time diagram following data from an input file*******************/

package colorSpaceTime;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JViewport;

public class FileSpaceTimeLogic extends JPanel{
	/**
	 *  implements MouseMotionListener, MouseListener
	 */
	private static final long serialVersionUID = 1L;
	int state,cell;
	BufferedReader br;
	int[] initialState;
	int levelSpace = 1, maxStates,initialHeight = 1, colorHeight = 15, colorWidth = 15, colorSpace = 1, initialWidth = 1;
	int height, width;
	int currentX, currentY;
	private JScrollPane enclosingPane;
    private int lastMouseX, lastMouseY;
	  
	public FileSpaceTimeLogic(int s, int n,  BufferedReader br){
		this.state = s;
		this.cell = n;
		//initialState = new int [cell];
		this.br = br;   
		
		this.setLayout(null);
		
		initialState = new int [cell];
		
		maxStates =  (int) (Math.pow(state, cell));
		width = (cell * (colorWidth + colorSpace) + initialWidth * 2);
		height = 99999*colorHeight+initialHeight;
		
		this.setBackground(Color.PINK);
		}
	
	  public void setEnclosingPane (JScrollPane pane)
	    {
	        enclosingPane = pane;
	    }

	  public void paintState(Graphics g){
		  Graphics2D g2 = (Graphics2D) g;
		  g2.setStroke(new BasicStroke(2));
		  int i;
		  	
		  currentY = initialHeight+levelSpace;
		  
		  String numberString = new String();
		
		  try {
				while((numberString = br.readLine()) != null){
					currentX = initialWidth + colorSpace; //x for each starting cell
					//System.out.println(numberString);
					//System.out.println(currentX+" , "+currentY);
					
					
					for( i = 0; i<cell; i++){
						
						initialState[i] = Integer.parseInt(String.valueOf(numberString.charAt(i))); // store each character of the string into integer array
					
						// set color n print state in color
						if(initialState[i]==0) {		 		
							//g2.setColor(Color.BLUE);
							g2.setColor(Color.WHITE);
					 		g2.fillRect(currentX, currentY, colorWidth, colorHeight);
							}
				 		else if(initialState[i]==1){
				 				//g2.setColor(Color.GREEN);
				 				g2.setColor(Color.BLACK);
				 				g2.fillRect(currentX, currentY, colorWidth, colorHeight);
							}
				 		else if(initialState[i]==2){
				 				g2.setColor(Color.RED);
				 				g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 			}
				 		else if(initialState[i]==3){
							g2.setColor(Color.YELLOW);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==4){
							g2.setColor(Color.GREEN);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==5){
							g2.setColor(Color.BLUE);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==6){
							g2.setColor(Color.CYAN);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==7){
							g2.setColor(Color.DARK_GRAY);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==8){
							g2.setColor(Color.GRAY);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 		else if(initialState[i]==9){
							g2.setColor(Color.PINK);
							g2.fillRect(currentX, currentY, colorWidth, colorHeight);
				 		}
				 			//System.out.println("s = "+initialState[i]);	
				 		
				 		currentX= currentX + colorWidth + colorSpace;// update x for the next cell	 
						
						}
					currentY = currentY + colorHeight+ levelSpace; // update y for the next level
				}
			
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

		  
	  }
	
	public void paintComponent(Graphics g){   // paints the numbers from file
		super.paintComponent(g);
		
		
		paintState(g);
		
	}
		
	
	
/*		
	*//**
     * Adjusts the scroll pane's view by an amount equal to the mouse motion.
     *//*
    public void mouseDragged (MouseEvent e)
    {
        // Compute the offset from the last mouse location.
        
        int deltaX = e.getX() - lastMouseX;
        int deltaY = e.getY() - lastMouseY;
        
        // Adjust the scroll pane by the delta.  Note that to move the
        //   surface with the mouse, we must move the view in the opposite
        //   direction.  This means that we subtract the delta.
        
        JViewport view = enclosingPane.getViewport();
        Point pos = view.getViewPosition();
        view.setViewPosition(new Point(pos.x - deltaX, pos.y - deltaY));

        // Keep track of the last mouse location.  Note:  Because we moved
        //   the view, the logical location of the mouse moved an equal amount
        //   in the same direction.
        
        lastMouseX = e.getX() - deltaX;
        lastMouseY = e.getY() - deltaY;
        
        // Make sure the JViewPort fully repaints.  This will make the 
        // out-of-bounds area appear all gray instead of giving a
        // torn appearance.
    
        view.repaint();
    }

    *//**
     * Keeps track of the last mouse position.
     *//*
    public void mousePressed (MouseEvent e)
    {
        // Keep track of the last mouse location.
        
        lastMouseX = e.getX();
        lastMouseY = e.getY();
    }
    // Unused event handlers
    
    public void mouseMoved (MouseEvent e)       {}
    public void mouseClicked (MouseEvent e)  {}
    public void mouseEntered (MouseEvent e)  {}
    public void mouseExited (MouseEvent e)   {}
    public void mouseReleased (MouseEvent e) {}*/

}
