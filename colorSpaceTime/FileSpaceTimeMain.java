/********************Main file for exploration of state space according to input given from file*******************/

package colorSpaceTime;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.logging.Level;

import javax.imageio.ImageIO;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;

import GUI.SaveComponent;


public class FileSpaceTimeMain {
	static JButton bt;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
				
		final JFrame frame = new JFrame("State Space Diagram");
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLayout (new BorderLayout());
        try {
       
        int state = Integer.parseInt(JOptionPane.showInputDialog("Enter the number of states"));
		
		final int cell = Integer.parseInt(JOptionPane.showInputDialog("Enter the length of each number"));
		
		String infile = JOptionPane.showInputDialog("Enter the input .txt file name: ");
		
        BufferedReader br = new BufferedReader( new InputStreamReader(new DataInputStream(new FileInputStream(infile))));
        String outFile = JOptionPane.showInputDialog("Enter the output image file name: ");
		JLabel label = new JLabel();
		label.setText("State Space Diagram for "+state + " state PRNG of " +cell + " length number with filename '"+ infile+"'");
		label.setForeground(Color.RED);
		label.setBackground(Color.PINK);
		label.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		//label.setLocation(width - 50, height - 50);
		label.setVisible(true);
		frame.add(label,BorderLayout.NORTH);
		
		        
		final FileSpaceTimeLogic panel = new FileSpaceTimeLogic (state,cell,br);
		
        
        
        JScrollPane pane = new JScrollPane (panel);
        pane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        pane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
      
        pane.setBackground(Color.CYAN);
        frame.add (pane, BorderLayout.CENTER);
        
        
        // Register the pane with our panel.
        panel.setEnclosingPane(pane);
        
        
		panel.setMinimumSize(new Dimension(panel.width,7000));
		panel.setSize(new Dimension(panel.width, 7000));
	             

        pane.setMinimumSize(new Dimension(200,650));
       // pane.setPreferredSize(new Dimension(100, 1050));	
		pane.setSize(new Dimension(panel.width, panel.height));
		
		frame.setSize(new Dimension(panel.width, panel.height));
	      				
		BufferedImage image = new BufferedImage(panel.width, 7000, BufferedImage.TYPE_INT_ARGB);
		Graphics g = image.getGraphics();
		panel.paint(g);
		 try {
		        //ImageIO.write(image, "png", new File(infile.substring(0, infile.length()-4)+".png"));
			 ImageIO.write(image, "png", new File(outFile+".png"));
		    } catch (IOException ex) {
		    	ex.printStackTrace();
		   }
		
		  //  frame.pack();
     //   frame.setVisible (true);
      //  panel.paintState();
        
    	br.close();
 
       } catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
        
	}

	
	}

