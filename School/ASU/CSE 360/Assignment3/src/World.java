/**
 *  Name:	WeiChieh Huang
 *	ASUID:	1215427213
 *	CoursID:70605-CSE360
 *	Assignment# 3
 *	Description: The main function that creates the panel and call to make
 *				 the graphs.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class World extends JFrame implements ActionListener
{
	int numClicks = 0;
	Source source = new Source();

	/**
	 * World Constructor create 3 panels and one Run button. The Bar plot
	 * contains marked plot and simple plot. The marked plot contains simple
	 * plot. Put all the panel in Grid Layout.
	 */
	
	public World()
	{
		JButton run = new JButton("Run");
		SimplePlot simplePlot = new SimplePlot();
		MarkedPlot markedPlot = new MarkedPlot();
		BarPlot barPlot = new BarPlot();

		markedPlot.add(simplePlot);
		barPlot.add(markedPlot);
		
		PlotPanel plotPane1 = new PlotPanel(barPlot);
		PlotPanel plotPane2 = new PlotPanel(markedPlot);
		PlotPanel plotPane3 = new PlotPanel(simplePlot);
		
		source.addObserver(plotPane1);

		run.addActionListener(this);
		
		setLayout(new GridLayout(4,1));

		add(plotPane1);
		add(plotPane2);		
		add(plotPane3);
		add(run);

	}
	/**
	 * main program that call world constructor and set the size of the window.
	 * @param args
	 */
	public static void main(String[] args)
	{
		World world = new World();
		world.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		world.setSize(550, 1000);
		world.setVisible(true);
	}

	/**
	 * Action listener for mouse event. When the mouse is clicked. Then source
	 * create a random value and repaint the plot.
	 */
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		source.create();
		repaint();
	}
}
