// aclark -- jot

import java.applet.Applet;
import java.awt.*;
        
public class MyApplet extends Applet implements Runnable
{
	Thread t;
        int x=0,y=0,z=0;
	public void start()
	{
		t=new Thread(this);
		t.start();
	}

	public void run()
	{
		while (true)
		{
			repaint();
			try 
			{
				t.sleep(10);
			} 
			catch (Exception e){}
		}
	}

	public static void main (String args[])
	{
		MyApplet myapplet;
		myapplet=new MyApplet ();
		Frame f;
		f=new Frame();
		f.add(myapplet);
		f.pack();
		f.show();
		f.setSize(180,500);
		myapplet.start();

	}


      	public void paint(Graphics g)
      	{   	
           	g.drawString("A",23,420); 
           	g.drawString("L",63,420); 
           	g.drawString("E",103,420); 
           	g.drawString("X",143,420); 
	   	g.fillOval(x,y,10,10);
           	y=(z*z);		 
   	   	x++; z++;
	   	if(z==20) z=-20;   
	   	if(x==156) 
		{
			x=0;
			y=0;
			z=0;
		}
      	}
}
