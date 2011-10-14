
// JuggleAnim.java
// Version 1.1 (6/22/96)
//
// Jack Boyce (jboyce@physics.berkeley.edu)
//
// See app_notes.html for release notes.  For a description of the applet
// parameters, please see the online HTML documentation.

import java.applet.*;
import java.awt.*;
import java.awt.image.*;
import java.net.*;
import java.util.*;

// This applet animates a juggling pattern by making a "movie" of the pattern
// and then looping through it, drawing the frames repeatedly.  This movie
// (an instance of the JuggleMovie class) is just an explicit list of screen
// coordinates for all the objects in the scene; since none of the pattern
// layout and calculation is done on the fly, the animation is fairly fast.
//
// The real work, of course, lies in building the JuggleMovie object.  I do this
// in as simple and general-purpose a manner as possible by dividing the task
// into three parts, as follows:
//
//    1.  Parse the pattern, and layout the balls to provide a list of instructions
//        such as "ball 1 is thrown by hand 0 at t=1.2 seconds and is caught by
//        hand 1 at t=2.5 seconds", etc.  Note that none of the spatial information
//        has been layed out yet.  You can specify different ball path types (e.g.
//        bounce juggling, etc.) just by extending the "BallPath" class.
//
//    2.  Lay out the positions of the hands as a function of time.  After this
//        stage, we can convert the ball-path instructions from step 1 above into
//        actual paths, since we now know where the hands are at the catching and
//        throwing times.  After telling each BallPath object in the list where
//        its starting and ending positions are, the objects in the list are
//        individually responsible for calculating ball positions at all times
//        between these endpoints defined by the hands.  (A BallPathAir object
//        uses a parabolic path in space, for example.)
//
//    3.  Draw the juggler, which is here assumed to be just a function of the
//        positions of its hands.


// Each of these steps is accomplished using an instance of one of the following
// classes, in order:

abstract class PhysicalPattern {
	protected PhysicalConst	con = null;
	protected BallPathList	bpl = null;
	
	public void				setConstants(PhysicalConst c) {
		con = new PhysicalConst(c);
	}
	
	public PhysicalConst	getConstants() {
		return new PhysicalConst(con);
	}
	
	public BallPathList		getBallPathList()	{ return bpl; }
	
	public abstract int		getStartupThrows();		// undefined here
	public abstract int		getLoopThrows();
	public abstract int		getMaxThrow();
	public abstract void	layoutPattern(double startup_time, double loop_time)
									throws JuggleException;
}


abstract class PhysicalHands {
	protected PhysicalConst	con = null;
	protected BallPathList	hpl = null;
	
	public void				setConstants(PhysicalConst c) {
		con = new PhysicalConst(c);
	}
	
	public PhysicalConst	getConstants() {
		return new PhysicalConst(con);
	}
	
	public BallPathList		getHandPathList()	{ return hpl; }

	public abstract int		getStartupThrows();		// undefined
	public abstract int		getLoopThrows();
	public abstract int		getHands();
	public abstract void	layoutHands(BallPathList bpl, double time) throws JuggleException;
	
}


class PhysicalJuggler {
	protected Coordinate	left = null, right = null;
	
	public void		placeHands(Coordinate right, Coordinate left) {
		this.left = new Coordinate(left);
		this.right = new Coordinate(right);
	}
	
	public int		getMaxLines() 		{ return 0; }
	public int		getMaxEllipses()	{ return 0; }
	public Vector	getLines() 			{ return null; }
	public Vector	getEllipses()		{ return null; }
}


// And the following class groups everything together into a cohesive unit:

class PhysicalGroup {
	protected PhysicalPattern	pat = null;
	protected PhysicalHands		hands = null;
	protected PhysicalJuggler	jug = null;
	protected PhysicalConst		con = null;
	protected int				startup_length, loop_period;
	
	
	PhysicalGroup(PhysicalPattern pat, PhysicalHands hands, PhysicalJuggler jug,
							PhysicalConst con) throws JuggleException {
		int				pat_period, hand_period;
	//	double			total_time;
		
		this.pat = pat;
		this.hands = hands;
		this.jug = jug;
		this.con = con;
		
		pat.setConstants(con);
		hands.setConstants(con);
		startup_length = Math.max(pat.getStartupThrows(), hands.getStartupThrows());
		pat_period = pat.getLoopThrows();
		hand_period = hands.getLoopThrows();

		loop_period = pat_period * hand_period / gcd(pat_period, hand_period);
	//	total_time = ((double)(startup_length + loop_period + 2)) / con.tps;
		
		pat.layoutPattern((double)startup_length / con.tps,
							(double)loop_period / con.tps);
		hands.layoutHands(pat.getBallPathList(), 
				(startup_length + loop_period + pat.getMaxThrow() + 2) / con.tps);
		pat.getBallPathList().fixBalls(hands.getHandPathList());
	}
	
	public BallPathList		getBallPathList()	{ return pat.getBallPathList(); }
	public BallPathList		getHandPathList()	{ return hands.getHandPathList(); }
	public PhysicalJuggler	getJuggler()		{ return jug; }
	
	protected int	gcd(int x, int y) {		// Euclid's algorithm (x>0, y>0)
		int	g = y;
		
		while (x > 0) {
			g = x;
			x = y % x;
			y = g;
		}
		return g;
	}
}


// The following class is used to control the applet from outside (another applet).

class JuggleControls {
	public String			modestring, patstring;
	public Image			ballimage = null;
	public double			accel = 9.8;
	public double			tps = 4.5;
	public double			dwell = 1.0;
	public double			balldiam = 0.1;
	public double			bouncefrac = 0.9;
	public double			slowdown = 1.0;
	public double			fps = 20.0;
	public double			handscoop = 0.2;
	public int				border = 0;
	public boolean			startPause = true;
	public boolean			dbuffer = true;
	public double[][]		handpath = null;
	public double			mat_hr = -1.0;	// for emulating Ken Matsuoka's format

	JuggleControls() { super(); }
	
	JuggleControls(JuggleControls jc) {
		if (jc.modestring != null)		this.modestring = jc.modestring;
		if (jc.patstring != null)		this.patstring = jc.patstring;
		if (jc.ballimage != null)		this.ballimage = jc.ballimage;
		if (jc.accel >= 0.0)			this.accel = jc.accel;
		if (jc.tps >= 0.0)				this.tps = jc.tps;
		if (jc.dwell >= 0.0)			this.dwell = jc.dwell;
		if (jc.balldiam >= 0.0)			this.balldiam = jc.balldiam;
		if (jc.bouncefrac >= 0.0)		this.bouncefrac = jc.bouncefrac;
		if (jc.slowdown >= 0.0)			this.balldiam = jc.balldiam;
		if (jc.fps >= 0.0)				this.fps = jc.fps;
		if (jc.handscoop >= 0.0)		this.handscoop = jc.handscoop;
		if (jc.border >= 0)				this.border = jc.border;
		this.startPause = jc.startPause;
		this.dbuffer = jc.dbuffer;
		if (jc.handpath != null)		this.handpath = jc.handpath;
		if (jc.mat_hr >= 0.0)			this.mat_hr = jc.mat_hr;
	}
}



// This class is the applet itself.  It parses the parameters given to it and
// creates PhysicalPattern, PhysicalHands, and PhysicalJuggler objects of
// the required types.  These objects are then used to create a JuggleMovie,
// which is animated by calling the JuggleMovie's draw_frame() method
// repeatedly from an independent thread that we start up.  Clicking within
// the applet pauses the animation.

public class JuggleAnim extends Applet implements Runnable {
	int				appWidth;
	int				appHeight;
	Thread			engine = null;
	JuggleMovie		jm = null;
	boolean			oktostart = false;
	boolean			loaded = false;
	boolean			userPause;
	JuggleException	exception = null;
	String			message = null;
	
	JuggleControls	jc = new JuggleControls();
	double			rightthrowx = 0.2;
	double			rightcatchx = 0.5;
	double			leftthrowx = -0.2;
	double			leftcatchx = -0.5;
	
	
    public String getAppletInfo() {
		return "Juggling animator by Jack Boyce (version 1.1, 6/22/96)";
    }
	
	public void init()  {		/* Overrides Applet.init() */
		String 	temp;
		int		tempint;
		double 	tempdouble;
		
		appWidth = this.size().width;
		appHeight = this.size().height;
		
		try {
			jc.modestring = getParameter("mode");
			if (jc.modestring == null)
				throw new JuggleException("No mode specified");
			
			temp = getParameter("border");
			if (temp != null)  {
				try {
					tempint = Integer.parseInt(temp);
					jc.border = tempint;
				} catch (NumberFormatException e) {
				}
			}
			
			temp = getParameter("startpaused");
			if (temp != null)
				userPause = jc.startPause = Boolean.valueOf(temp).booleanValue();
			
			temp = getParameter("dbuffer");
			if (temp != null)
				jc.dbuffer = Boolean.valueOf(temp).booleanValue();
				
			temp = getParameter("g");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.accel = tempdouble;
				} catch (NumberFormatException e) {
				}
				
			temp = getParameter("tps");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.tps = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("dwell");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					if ((tempdouble > 0.0) && (tempdouble < 1.9))
						jc.dwell = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("throwx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					rightthrowx = tempdouble;
					leftthrowx = -tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("rightthrowx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					rightthrowx = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("leftthrowx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					leftthrowx = -tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("catchx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					rightcatchx = tempdouble;
					leftcatchx = -tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("rightcatchx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					rightcatchx = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("leftcatchx");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					leftcatchx = -tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("balldiam");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.balldiam = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("bouncefrac");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.bouncefrac = tempdouble;
				} catch (NumberFormatException e) {
				}
				
			temp = getParameter("slowdown");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.slowdown = tempdouble;
				} catch (NumberFormatException e) {
				}
	
			temp = getParameter("fps");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.fps = tempdouble;
				} catch (NumberFormatException e) {
				}
				
			temp = getParameter("handscoop");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.handscoop = tempdouble;
				} catch (NumberFormatException e) {
				}
				
			jc.patstring = getParameter("pattern");
			if (jc.patstring == null)
				throw new JuggleException("No pattern specified");
				
			temp = getParameter("ballpic");
			if (temp != null) {
				URL	imageSource;
				
		    	try  {
		    		String	param = getParameter("imagebase");	
		    		imageSource = (param==null) ? getDocumentBase() :
		    				new URL(getDocumentBase(), param + "/");
		    	} catch (MalformedURLException e) {
		    		throw new JuggleException("Malformed imagebase specified");
		    	}
				jc.ballimage = getImage(imageSource, temp);
			}
			
			temp = getParameter("mat_style");
			if (temp != null) {
					// parse handpath here
				try {
					StringTokenizer	st1 = new StringTokenizer(temp, "}", false);
					StringTokenizer st2 = null;
					String			st = null;
					int				size = st1.countTokens();
					
					if ((size % 2) == 1)
						throw new JuggleException();
					boolean dbl = ((size%4)==0) ? false : true;
					jc.handpath = new double[dbl ? 2*size : size][2];
					try {
						for (tempint = 0; tempint < size/2; tempint++) {
							for (int i = 0; i < 2; i++) {
								st = st1.nextToken().replace('{', ' ');
								st2 = new StringTokenizer(st, ",", false);
								jc.handpath[2*tempint+i][0] = 0.025 *
										Double.valueOf(st2.nextToken()).doubleValue();
								jc.handpath[2*tempint+i][1] = 0.05 *
										Double.valueOf(st2.nextToken()).doubleValue();
							}
						}
					} catch (NumberFormatException e) {
						throw new JuggleException();
					} catch (NoSuchElementException e) {
						throw new JuggleException();
					}
					
					if (dbl) {
						for (tempint = size; tempint < (2*size); tempint++) {
							jc.handpath[tempint][0] = jc.handpath[tempint-size][0];
							jc.handpath[tempint][1] = jc.handpath[tempint-size][1];
						}
					}
					for (tempint = 2; tempint < (dbl?2*size:size); tempint+=4) {
						jc.handpath[tempint][0] *= -1;		// convert left hand to
						jc.handpath[tempint+1][0] *= -1;	// real coordinates
					}
				} catch (JuggleException je) {
					throw new JuggleException("Syntax error in hand path");
				}
			}
			if (temp == null) {
				jc.handpath = new double[4][2];
				jc.handpath[0][0] = rightcatchx;
				jc.handpath[0][1] = 0.0;
				jc.handpath[1][0] = rightthrowx;
				jc.handpath[1][1] = 0.0;
				jc.handpath[2][0] = leftcatchx;
				jc.handpath[2][1] = 0.0;
				jc.handpath[3][0] = leftthrowx;
				jc.handpath[3][1] = 0.0;
			}
			
			temp = getParameter("mat_DR");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.dwell = 2.0 * tempdouble;
				} catch (NumberFormatException e) {
				}
			
			temp = getParameter("mat_HR");
			if (temp != null)
				try {
					tempdouble = Double.valueOf(temp).doubleValue();
					jc.mat_hr = tempdouble;
				} catch (NumberFormatException e) {
				}
					
					
			oktostart = true;
			
		} catch (JuggleException je) {
			drawstring(je.getMessage());
			exception = je;
		}
   	}
	
    public void start() {		/* Overrides Applet.start() */
		if ((engine == null) && oktostart) {
			engine = new Thread(this);
			engine.start();
		}
    }

    public void stop() {		/* Overrides Applet.stop() */
		if (engine != null && engine.isAlive())
			engine.stop();
		engine = null;
		oktostart = false;		// prevents restarting the thread
    }
	
	public void restart(JuggleControls jc) {
		if (engine != null && engine.isAlive())
			engine.stop();
		this.jc = new JuggleControls(jc);
		engine = new Thread(this);
		engine.start();
	}
	
	
	public void run()  {		/* Called when this object becomes a thread */
		Graphics 			g = this.getGraphics();
		Graphics			offg = null;
		Image				offscreen = null;
		PhysicalPattern		pat = null;
		PhysicalHands		hands = null;
		PhysicalJuggler		jug = null;
		PhysicalGroup		group = null;
		Color				backcolor = null, jugcolor = null;
		long				time_start, time_wait;
		
		Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
		
		oktostart = false;		// don't try to restart
		
		try {
				// First create a PhysicalPattern of the type requested
			drawstring(message = "Parsing pattern");
	
			if (jc.modestring.equals("siteswap")) {
					// could get siteswap-specific parameters here
				pat = new PhysicalAsyncSiteSwap(jc.patstring);
				hands = new PhysicalHandsDefault(2, jc.handpath);
				jug = new PhysicalJugglerDefault();
			} else if (jc.modestring.equals("syncsiteswap")) {
				pat = new PhysicalSyncSiteSwap(jc.patstring);
				hands = new PhysicalHandsDefault(2, jc.handpath);
				jug = new PhysicalJugglerDefault();
			} else
				throw new JuggleException("Unknown mode specified");
	
			if (pat != null) {
				Rectangle		r = null;
				PhysicalConst	con = null;

				r = new Rectangle(jc.border, jc.border,
							appWidth-2*jc.border, appHeight-2*jc.border);

					// The following is a hack which adjusts tps to
					// achieve the desired maximum throw height.
				if (jc.mat_hr > 0.0) {
					try {
						jc.tps = Math.sqrt(jc.accel / (8.0 * jc.mat_hr *
								(double)pat.getMaxThrow())) *
								((double)pat.getMaxThrow() - jc.dwell);
					} catch (ArithmeticException e) {
					}
				}
				
				con = new PhysicalConst(jc.accel, jc.tps, jc.dwell,
								jc.handscoop, jc.balldiam, jc.bouncefrac);

				drawstring(message = "Laying out pattern");

				group = new PhysicalGroup(pat, hands, jug, con);
				
					// Now we make the movie.
				drawstring(message = "Making movie");
				if (jc.ballimage == null)
					jm = new JuggleMovieSimple(group,
									jc.balldiam, this, r, jc.fps, jc.slowdown);
				else			
					jm = new JuggleMovieSimple(group,
									jc.ballimage, this, r, jc.fps, jc.slowdown);
				loaded = true;
			}
		
			if (!loaded)
				return;
			
			pat = null;					// we have our movie, now try to free up
			hands = null;				// some memory
			jug = null;
			group = null;
			jm.flush_coords();
			System.gc();
			
			if (jc.startPause) {
				drawstring(message = "Click to start");
				userPause = true;
				engine.suspend();		// wait until user clicks on applet
			} else
				userPause = false;
			
			message = null;
			if (jc.dbuffer) {
				offscreen = this.createImage(appWidth, appHeight);
				offg = offscreen.getGraphics();
			}
			backcolor = this.getBackground();
			jugcolor = Color.black;
			time_start = System.currentTimeMillis();
			
			while (true)  {
				if (jc.dbuffer) {
					offg.setColor(backcolor);
					offg.fillRect(0, 0, appWidth, appHeight);
					offg.setColor(jugcolor);
					jm.draw_frame(offg, this);
					g.drawImage(offscreen, 0, 0, this);
				} else {
					g.setColor(backcolor);
					g.fillRect(0, 0, appWidth, appHeight);
					g.setColor(jugcolor);
					jm.draw_frame(g, this);
				}
				try {
					time_wait = jm.get_duration()-System.currentTimeMillis()+time_start;
					if (time_wait > 0)
						Thread.sleep(time_wait);
					time_start = System.currentTimeMillis();
				} catch (InterruptedException ie)  {
					// What should we do here?
					throw new JuggleException("Animator was interrupted");
				}
				jm.advance_frame();
			}
				
		} catch (JuggleException je) {
			drawstring(je.getMessage());
			exception = je;
		}
	}

	public void paint(Graphics g) {		/* Overrides Applet.paint() */
		if (exception != null)
			drawstring(exception.getMessage());
		else if (message != null)
			drawstring(message);
		else if (loaded)
			jm.draw_frame(g, this);
	}
	
	protected void drawstring(String message) {
		int			x, y, width;
		Graphics	g = this.getGraphics();
		FontMetrics	fm = g.getFontMetrics();
		
		width = fm.stringWidth(message);
		x = (appWidth > width) ? (appWidth-width)/2 : 0;
		y = (appHeight + fm.getHeight()) / 2;
		g.setColor(this.getBackground());
		g.fillRect(0, 0, appWidth, appHeight);
		g.setColor(Color.black);
		g.drawString(message, x, y);
	}
	
    public boolean handleEvent(Event evt) {
		if (evt.id == Event.MOUSE_DOWN) {
			if (engine != null && engine.isAlive()) {
			    if (userPause)
					engine.resume();
			    else
					engine.suspend();
			    userPause = !userPause;
			} else if (oktostart) {
			    userPause = false;
			    engine = new Thread(this);
			    engine.start();
			}
		    return true;
		} else    
		    return super.handleEvent(evt);
    }

}



// This is our own exception class, which we use to handle juggling-related
// problems that occur.

class JuggleException extends Exception {
	JuggleException()  			{ super();	}
	JuggleException(String s)	{ super(s);	}
}



// A single frame in the JuggleMovie class defined below

class JuggleMovieFrame {
	public int			frame_duration;		// in milliseconds
	public int			frame_images;		// number of images
	public Coordinate[]	images_coord;
	public int[]		images_x;
	public int[]		images_y;
	public Image[]		images;
	public int			frame_lines;		// number of lines
	public Coordinate[]	lines_scoord;
	public Coordinate[] lines_ecoord;
	public int[]		lines_startx;
	public int[]		lines_starty;
	public int[]		lines_endx;
	public int[]		lines_endy;
	public int			frame_ellipses;
	public Coordinate[]	ellipses_scoord;
	public Coordinate[] ellipses_ecoord;
	public int[]		ellipses_startx;
	public int[]		ellipses_starty;
	public int[]		ellipses_endx;
	public int[]		ellipses_endy;
	
	JuggleMovieFrame(int images, int lines, int ellipses) {
		this.images_coord = new Coordinate[images];
		this.images_x = new int[images];
		this.images_y = new int[images];
		this.images = new Image[images];
		this.lines_scoord = new Coordinate[lines];
		this.lines_ecoord = new Coordinate[lines];
		this.lines_startx = new int[lines];
		this.lines_starty = new int[lines];
		this.lines_endx = new int[lines];
		this.lines_endy = new int[lines];
		this.ellipses_scoord = new Coordinate[ellipses];
		this.ellipses_ecoord = new Coordinate[ellipses];
		this.ellipses_startx = new int[ellipses];
		this.ellipses_starty = new int[ellipses];
		this.ellipses_endx = new int[ellipses];
		this.ellipses_endy = new int[ellipses];
	}
}



// This class represents a movie of a juggling pattern.  It provides facilities
// for creating a movie, adding frames to it, and then playing it back.  In
// this version, frames consist of collections of images and lines.

class JuggleMovie {
	protected int				max_images;
	protected int				max_lines;
	protected int				max_ellipses;
	protected int				movie_status;
	protected int				frame_status;
	protected int 				current_frame_num;
	protected int				loop_frame_num;
	protected int				num_frames;
	protected Vector			framelist = null;
	protected JuggleMovieFrame	current_frame = null;
	
	JuggleMovie(int images, int lines, int ellipses) {
		this.max_images = images;
		this.max_lines = lines;
		this.max_ellipses = ellipses;
		this.current_frame_num = 0;
		this.loop_frame_num = 0;
		this.framelist = new Vector(20, 20);
	}
		
	public void open_movie() throws JuggleException {
		if (movie_status != 0)
			throw new JuggleException("Can only open a new movie");
			
		movie_status = 1;
		framelist = new Vector(10, 10);
	}
	
	public void close_movie() throws JuggleException {
		if (movie_status < 1)
			throw new JuggleException("Can't close an unopened movie");
		else if (movie_status > 1)
			throw new JuggleException("Movie was already closed");
			
		movie_status = 2;
		num_frames = current_frame_num;
		framelist.trimToSize();
		rewind_movie();
	}
	
	public void open_frame(int ticks) throws JuggleException {
		if (movie_status != 1)
			throw new JuggleException("Can't open frame in unopened movie");
		if (frame_status == 1)
			throw new JuggleException("Frame is already open");
		frame_status = 1;
		current_frame = new JuggleMovieFrame(max_images, max_lines, max_ellipses);
		current_frame.frame_duration = ticks;
		framelist.addElement(current_frame);
	}
	
	public void close_frame() throws JuggleException {
		if (movie_status != 1)
			throw new JuggleException("Can't close frame in unopened movie");
		if (frame_status == 0)
			throw new JuggleException("Can't close unopened frame");
		frame_status = 0;
		current_frame_num++;
	}
	
	public void start_loop() throws JuggleException {
		if (movie_status != 1)
			throw new JuggleException("Can't start loop in unopened movie");
		if (frame_status == 1)
			throw new JuggleException("Can't start loop with frame open");
		loop_frame_num = current_frame_num;
	}
	
	public void add_image(Image img, Coordinate c) throws JuggleException {
		if (frame_status == 0)
			throw new JuggleException("Can't add image to unopened frame");
		
		int		temp = current_frame.frame_images;
		if (temp == max_images)
			throw new JuggleException("Too many images in frame");
		
		current_frame.images[temp] = img;
		current_frame.images_coord[temp] = c;
		current_frame.frame_images++;
	}
	
	public void add_line(Coordinate c_start, Coordinate c_end) throws JuggleException {
		if (frame_status == 0)
			throw new JuggleException("Can't add line to unopened frame");

		int		temp = current_frame.frame_lines;
		if (temp == max_lines)
			throw new JuggleException("Too many lines in frame");
		current_frame.lines_scoord[temp] = c_start;
		current_frame.lines_ecoord[temp] = c_end;
		current_frame.frame_lines++;
	}
			
	public void add_ellipse(Coordinate c_start, Coordinate c_end) throws JuggleException {
		if (frame_status == 0)
			throw new JuggleException("Can't add ellipse to unopened frame");

		int		temp = current_frame.frame_ellipses;
		if (temp == max_ellipses)
			throw new JuggleException("Too many ellipses in frame");
		current_frame.ellipses_scoord[temp] = c_start;
		current_frame.ellipses_ecoord[temp] = c_end;
		current_frame.frame_ellipses++;
	}
	
	public void	advance_frame() {
		if (++current_frame_num >= num_frames)
			current_frame_num = loop_frame_num;
		current_frame = (JuggleMovieFrame)framelist.elementAt(current_frame_num);
	}
	
	public void	rewind_frame() {
		if (--current_frame_num < loop_frame_num)
			current_frame_num = num_frames - 1;
		current_frame = (JuggleMovieFrame)framelist.elementAt(current_frame_num);
	}

	public void	rewind_movie() throws JuggleException {
		if (movie_status != 2)
			throw new JuggleException("Can't rewind unfinished movie");
			
		current_frame_num = 0;
		current_frame = (JuggleMovieFrame)framelist.elementAt(current_frame_num);
	}
	
	public void draw_frame(Graphics g, Component comp) {
		int			i, tempx, tempy;
		Image		img;

		for (i = 0; i < current_frame.frame_lines; i++)
			g.drawLine(current_frame.lines_startx[i], current_frame.lines_starty[i],
					current_frame.lines_endx[i], current_frame.lines_endy[i]);
				
		for (i = 0; i < current_frame.frame_ellipses; i++) {
			tempx = current_frame.ellipses_startx[i];
			tempy = current_frame.ellipses_starty[i];
			g.drawOval(tempx, tempy, current_frame.ellipses_endx[i] - tempx,
					current_frame.ellipses_endy[i] - tempy);
		}
		
		for (i = 0; i < current_frame.frame_images; i++)  {
			img = current_frame.images[i];
			g.drawImage(img, current_frame.images_x[i],
				current_frame.images_y[i], comp);
		}
	}
	
	public int get_duration() {
		return current_frame.frame_duration;
	}
	
	public void coord_to_xy(double zoom, int originx, int originy, int ballwidth,
												int ballheight) {
		int					i, j;
		JuggleMovieFrame	fr = null;
		
		for (i = 0; i < framelist.size(); i++) {
			fr = (JuggleMovieFrame)framelist.elementAt(i);
			for (j = 0; j < fr.frame_lines; j++) {
				fr.lines_startx[j] = originx + (int)(0.5 + zoom * fr.lines_scoord[j].x);
				fr.lines_starty[j] = originy - (int)(0.5 + zoom * fr.lines_scoord[j].y);
				fr.lines_endx[j] = originx + (int)(0.5 + zoom * fr.lines_ecoord[j].x);
				fr.lines_endy[j] = originy - (int)(0.5 + zoom * fr.lines_ecoord[j].y);
			}
			for (j = 0; j < fr.frame_ellipses; j++) {
				fr.ellipses_startx[j] = originx + (int)(0.5 + zoom * fr.ellipses_scoord[j].x);
				fr.ellipses_starty[j] = originy - (int)(0.5 + zoom * fr.ellipses_scoord[j].y);
				fr.ellipses_endx[j] = originx + (int)(0.5 + zoom * fr.ellipses_ecoord[j].x);
				fr.ellipses_endy[j] = originy - (int)(0.5 + zoom * fr.ellipses_ecoord[j].y);
			}
			for (j = 0; j < fr.frame_images; j++) {
				fr.images_x[j] = originx - ballwidth/2 + (int)(0.5 + zoom * fr.images_coord[j].x);
				fr.images_y[j] = originy - ballheight - (int)(0.5 + zoom * fr.images_coord[j].y);
			}
		}
	}
	
	public void flush_coords() {
		int					i, j;
		JuggleMovieFrame	fr = null;
		
		for (i = 0; i < framelist.size(); i++) {
			fr = (JuggleMovieFrame)framelist.elementAt(i);
			for (j = 0; j < fr.frame_lines; j++) {
				fr.lines_scoord[j] = null;
				fr.lines_ecoord[j] = null;
			}
			for (j = 0; j < fr.frame_ellipses; j++) {
				fr.ellipses_scoord[j] = null;
				fr.ellipses_ecoord[j] = null;
			}
			for (j = 0; j < fr.frame_images; j++)
				fr.images_coord[j] = null;
		}
	}
			
	public void find_max_min(Coordinate coordmax, Coordinate coordmin) {
		int					i, j;
		JuggleMovieFrame	fr = null;
		Coordinate			c = null;
		
		for (i = 0; i < framelist.size(); i++) {
			fr = (JuggleMovieFrame)framelist.elementAt(i);
			for (j = 0; j < fr.frame_lines; j++) {
				c = fr.lines_scoord[j];
				if (c.x > coordmax.x)	coordmax.x = c.x;
				if (c.x < coordmin.x)	coordmin.x = c.x;
				if (c.y > coordmax.y)	coordmax.y = c.y;
				if (c.y < coordmin.y)	coordmin.y = c.y;
				c = fr.lines_ecoord[j];
				if (c.x > coordmax.x)	coordmax.x = c.x;
				if (c.x < coordmin.x)	coordmin.x = c.x;
				if (c.y > coordmax.y)	coordmax.y = c.y;
				if (c.y < coordmin.y)	coordmin.y = c.y;
			}
			for (j = 0; j < fr.frame_ellipses; j++) {
				c = fr.ellipses_scoord[j];
				if (c.x > coordmax.x)	coordmax.x = c.x;
				if (c.x < coordmin.x)	coordmin.x = c.x;
				if (c.y > coordmax.y)	coordmax.y = c.y;
				if (c.y < coordmin.y)	coordmin.y = c.y;
				c = fr.ellipses_ecoord[j];
				if (c.x > coordmax.x)	coordmax.x = c.x;
				if (c.x < coordmin.x)	coordmin.x = c.x;
				if (c.y > coordmax.y)	coordmax.y = c.y;
				if (c.y < coordmin.y)	coordmin.y = c.y;
			}
			for (j = 0; j < fr.frame_images; j++) {
				c = fr.images_coord[j];
				if (c.x > coordmax.x)	coordmax.x = c.x;
				if (c.x < coordmin.x)	coordmin.x = c.x;
				if (c.y > coordmax.y)	coordmax.y = c.y;
				if (c.y < coordmin.y)	coordmin.y = c.y;
			}
		}
	}
	
	public void	set_image(Image ballimage) {
		int					i, j;
		JuggleMovieFrame	fr = null;
		
		for (i = 0; i < framelist.size(); i++) {
			fr = (JuggleMovieFrame)framelist.elementAt(i);
			for (j = 0; j < fr.frame_images; j++)
				if (fr.images[j] == null)
					fr.images[j] = ballimage;
		}
	}
	
}



// The following class provides a simple movie.  You give it a PhysicalGroup
// object and it creates a movie, scaling it to fit within the specified
// screen rectangle.
// In the constructor you can either specify a ball image to use, or let the
// program make one of the correct size.

class JuggleMovieSimple extends JuggleMovie {
	protected BallPathList		bpl = null;
	protected BallPathList		hpl = null;
	protected PhysicalJuggler	jug = null;
	protected Image				ballimage = null;
	protected double			balldiam;
	protected Component			comp;
	protected int				ballwidth, ballheight;
	protected Rectangle			r;
	protected Coordinate		coordmin, coordmax;
	
	
	JuggleMovieSimple(PhysicalGroup group, double balldiam, Component comp,
					Rectangle r, double fps, double slowdown) throws JuggleException {
		super(group.getBallPathList().getActors() +
				group.getHandPathList().getActors(),
				group.getJuggler().getMaxLines(), group.getJuggler().getMaxEllipses());
		
		this.bpl = group.getBallPathList();
		this.hpl = group.getHandPathList();
		this.jug = group.getJuggler();
		this.r = r;
		this.balldiam = balldiam;
		this.comp = comp;
		
		makeMovie(fps, slowdown);
	}
	
	
	JuggleMovieSimple(PhysicalGroup group, Image ballimage, Component comp,
					Rectangle r, double fps, double slowdown) throws JuggleException {
		super(group.getBallPathList().getActors() +
				group.getHandPathList().getActors(),
				group.getJuggler().getMaxLines(), group.getJuggler().getMaxEllipses());

		this.bpl = group.getBallPathList();
		this.hpl = group.getHandPathList();
		this.jug = group.getJuggler();
		this.r = r;
		
			// Use a MediaTracker object to wait for the image to finish loading.
		MediaTracker mt = new MediaTracker(comp);
		mt.addImage(ballimage, 0);
		try {
			mt.waitForID(0);
		} catch (InterruptedException e) {
			// what should we do here?
			throw new JuggleException("Image loading interrupted");
		}
		if (mt.isErrorID(0))
			throw new JuggleException("Error loading images");
			// at this point we know that the image has finished loading
			// with no errors, and the Image "ballimage" is valid.
		
		ballwidth = ballimage.getWidth(comp);
		ballheight = ballimage.getHeight(comp);
		this.ballimage = ballimage;
		
		makeMovie(fps, slowdown);
	}
	
	
	protected void makeMovie(double fps, double slowdown) throws JuggleException {	
		double		frame_width, frame_height;		// meters
		double		zoom;							// pixels per meter
		int			originx, originy;
		int			i, j;
		Vector		vec;
		int			x0, y0, x1, y1;
		double		t = 0.0;
		int			loop_frames = (int)(0.5 + slowdown * fps * bpl.getLoopTime());
		Coordinate	coord1 = null, coord2 = null;
		
		open_movie();
		
			// Adjust fps so that the loop contains an integer number of frames.
		fps = (double)loop_frames / slowdown / bpl.getLoopTime();
		
		while (t <= bpl.getStartupTime()) {
			open_frame((int)(0.5 + 1000/fps));
				// First draw the juggler.  Tell the PhysicalJuggler object where
				// the hands are, and then have it give us a list of lines.
			coord1 = hpl.getCoord(0,t);
			coord2 = hpl.getCoord(1,t);
			if ((coord1 != null) && (coord2 != null)) {
				jug.placeHands(coord1, coord2);
				vec = jug.getLines();
				for (i = 0; i < vec.size(); i += 2) {
					coord1 = (Coordinate)vec.elementAt(i);
					coord2 = (Coordinate)vec.elementAt(i + 1);
					add_line(coord1, coord2);
				}
				vec = jug.getEllipses();
				for (i = 0; i < vec.size(); i += 2) {
					coord1 = (Coordinate)vec.elementAt(i);
					coord2 = (Coordinate)vec.elementAt(i + 1);
					add_ellipse(coord1, coord2);
				}
			}
			for (i = 0; i < bpl.getActors(); i++) {
				coord1 = bpl.getCoord(i, t);
				if (coord1 != null)
					add_image(ballimage, coord1);
			}
			close_frame();
			t += 1.0 / fps / slowdown;
		}
		
		start_loop();
		
		for (i = 0; i < loop_frames; i++) {
			open_frame((int)(0.5 + 1000/fps));
			coord1 = hpl.getCoord(0,t);
			coord2 = hpl.getCoord(1,t);
			if ((coord1 != null) && (coord2 != null)) {
				jug.placeHands(coord1, coord2);
				vec = jug.getLines();
				for (j = 0; j < vec.size(); j += 2) {
					coord1 = (Coordinate)vec.elementAt(j);
					coord2 = (Coordinate)vec.elementAt(j + 1);
					add_line(coord1, coord2);
				}
				vec = jug.getEllipses();
				for (j = 0; j < vec.size(); j += 2) {
					coord1 = (Coordinate)vec.elementAt(j);
					coord2 = (Coordinate)vec.elementAt(j + 1);
					add_ellipse(coord1, coord2);
				}
			}
			for (j = 0; j < bpl.getActors(); j++) {
				coord1 = bpl.getCoord(j, t);
				if (coord1 != null)
					add_image(ballimage, coord1);
			}
			close_frame();
			t += 1.0 / fps / slowdown;
		}
		
		close_movie();
		
		Coordinate	coordmax = new Coordinate(0.0, 0.0);
		Coordinate	coordmin = new Coordinate(0.0, 0.0);
		find_max_min(coordmax, coordmin);
		
		if (ballimage == null) {		// need to make our own ball
			frame_width = 2.0 * Math.max(Math.abs(coordmax.x),
					Math.abs(coordmin.x)) + balldiam;
			frame_height = coordmax.y - coordmin.y + balldiam;
		
			zoom = Math.min((double)r.width/frame_width,
								(double)r.height/frame_height);
			int ball_pixel_size = (int)(0.5 + zoom * balldiam);
			if (ball_pixel_size < 1)
				ball_pixel_size = 1;
				
				// Now we should create a ball image of diameter ball_pixel_size
				// pixels and put it in the variable ballimage.
			ballimage = comp.createImage(ball_pixel_size, ball_pixel_size);
			Graphics g = ballimage.getGraphics();
			g.setColor(comp.getBackground());
			g.fillRect(0, 0, ball_pixel_size, ball_pixel_size);
			g.setColor(Color.red);
			g.fillOval(0, 0, ball_pixel_size, ball_pixel_size);

			set_image(ballimage);
			ballwidth = ballheight = ball_pixel_size;
		}
			// Now calculate the zoom factor that we need to fit the
			// pattern into the desired screen Rectangle r.
		frame_width = 2.0 * Math.max(Math.abs(coordmax.x), Math.abs(coordmin.x));
		frame_height = coordmax.y - coordmin.y;
		zoom = Math.min((double)(r.width - ballwidth) / frame_width,
					(double)(r.height - ballheight) / frame_height);
		originx = r.x + r.width / 2;
		originy = r.y + ballheight / 2 +
					(int)(0.5 + 0.5 * (r.height + zoom*(coordmax.y+coordmin.y)));
		coord_to_xy(zoom, originx, originy, ballwidth, ballheight);
	}
	
}
				
				
				
// Simple container class

class Coordinate {
	public double	x, y;
	
	Coordinate(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	Coordinate(Coordinate c) {
		this.x = c.x;
		this.y = c.y;
	}
	
	public static Coordinate max(Coordinate coord1, Coordinate coord2) {
		return new Coordinate(Math.max(coord1.x, coord2.x),
								Math.max(coord1.y, coord2.y));
	}
	
	public static Coordinate min(Coordinate coord1, Coordinate coord2) {
		return new Coordinate(Math.min(coord1.x, coord2.x),
								Math.min(coord1.y, coord2.y));
	}
}



// This class is used to describe the motion of a ball (or hand, or ...)
// from point (x0, y0) at one time to point (x1, y1) at a later time.  You
// define the path from time 0 to time t, and then use translateTime() to
// shift the time axis as preferred.  These objects are used by BallPathList
// to define a spacetime diagram for the entire pattern.
//
// Note that all distances are in meters and all times are in seconds.

abstract class BallPath {
	protected int			start_hand, end_hand;
	protected double		start_time, end_time;
	protected Coordinate	start_coord = null, end_coord = null;
	
	public void	setPath(int end_hand, double t) {
		this.start_time = 0.0;
		this.end_time = t;
		this.start_hand = start_hand;
		this.end_hand = end_hand;
	}
	
	public void	translateTime(double deltat) {
		start_time += deltat;
		end_time += deltat;
	}
	
	public void fixBall(BallPathList hpl) throws JuggleException {
		start_coord = hpl.getCoord(start_hand, start_time);
		end_coord = hpl.getCoord(end_hand, end_time);
		fixInternalVariables();
	}
	
	public int			getStartHand()			{ return start_hand; }
	public void			setStartHand(int sh)	{ start_hand = sh; }
	public int			getEndHand()			{ return end_hand; }
	public double		getStartTime()			{ return start_time; }
	public double		getEndTime()			{ return end_time; }
	public double		getDuration()			{ return (end_time-start_time); }
	
	protected abstract void		fixInternalVariables();	// undefined methods
	public abstract Coordinate 	getCoord(double time);
	public abstract Coordinate 	getMax();				// for screen layout purposes
	public abstract Coordinate 	getMin();
}



// This is a straight-line, constant velocity path

class BallPathLine extends BallPath {
	protected double	bx, cx;
	protected double	by, cy;
	
	protected void	fixInternalVariables() {
		cx = start_coord.x;
		cy = end_coord.x;
		bx = (end_coord.x - cx) / getDuration();
		by = (end_coord.y - cy) / getDuration();
	}
	
	public Coordinate getCoord(double time) {
		if ((time < start_time) || (time > end_time))
			return null;
		time -= start_time;
		return new Coordinate(cx+bx*time, cy+by*time);
	}
	
	public Coordinate getMax() {
		double	x, y;

		x = (bx > 0.0) ? (cx+bx*getDuration()) : cx;
		y = (by > 0.0) ? (cy+by*getDuration()) : cy;
		return new Coordinate(x, y);
	}
	
	public Coordinate getMin() {
		double	x, y;
		
		x = (bx > 0.0) ? cx : (cx+bx*getDuration());
		y = (by > 0.0) ? cy : (cy+by*getDuration());
		return new Coordinate(x, y);
	}
}



// This is a path in the air

class BallPathAir extends BallPath {
	protected double	bx, cx;
	protected double	ay, by, cy;
	
	BallPathAir(double accel) {
		ay = 0.5 * accel;
	}
	
	protected void	fixInternalVariables() {
		double	t = getDuration();
		
		if ((start_coord != null) && (end_coord != null)) {
			cx = start_coord.x;
			bx = (end_coord.x - start_coord.x) / t;
			cy = start_coord.y;
			by = (end_coord.y - start_coord.y) / t - ay * t;
		}
	}
	
	public Coordinate getCoord(double time) {
		if ((time < start_time) || (time > end_time))
			return null;
		time -= start_time;
		return new Coordinate(cx+bx*time, cy+time*(by+ay*time));
	}
	
	public Coordinate getMax() {
		double	x, y;
		double	duration = getDuration();
		double	temp = -by / (2.0 * ay);
		
		x = (bx > 0.0) ? (cx+bx*duration) : cx;
		
		if ((ay > 0.0) || (temp < 0.0) || (temp > duration))
			y = Math.max(cy, cy+duration*(by+ay*duration));
		else
			y = cy+temp*(by+ay*temp);
		return new Coordinate(x, y);
	}
	
	public Coordinate getMin() {
		double	x, y;
		double	duration = getDuration();
		double	temp = -by / (2.0 * ay);
		
		x = (bx > 0.0) ? cx : (cx+bx*duration);

		if ((ay < 0.0) || (temp < 0.0) || (temp > duration))
			y = Math.min(cy, cy+duration*(by+ay*duration));
		else
			y = cy+temp*(by+ay*temp);
		return new Coordinate(x, y);
	}
}


// This is a bounced ball.

class BallPathBounce extends BallPath {
	protected double	bx, cx;
	protected double	ay1, by1, cy1;		// before the bounce
	protected double	ay2, by2, cy2;		// after the bounce
	protected double	bounceplane;
	protected double	bouncefracsqrt;
	protected boolean	forced;				// true -> forced bounce
	protected double	bouncetime;
	
	BallPathBounce(double accel, double bounceplane, double bouncefrac, boolean forced) {
		ay1 = ay2 = 0.5 * accel;
		this.bounceplane = bounceplane;
		try {
			this.bouncefracsqrt = Math.sqrt(bouncefrac);
		} catch (ArithmeticException e) {
			this.bouncefracsqrt = 1.0;
		}
		this.forced = forced;
	}
	
		// The next function does all the real work of figuring out the ball's
		// path.  It solves a cubic equation to find the time when the ball hits
		// the ground
	protected void	fixInternalVariables() {
		double	t2 = getDuration();
		double	k0, k1, k2;
		double	q, r;
		
		if ((start_coord != null) && (end_coord != null)) {
				// First do the x coordinate.  This is simple.
			cx = start_coord.x;
			bx = (end_coord.x - start_coord.x) / t2;
			
			cy1 = start_coord.y;
			
				// The following are the coefficients of the cubic equation:
				//     bouncetime^3 + k2 * bouncetime^2 + k1 * bouncetime + k0 = 0
			k2 = -t2*(2*ay2+bouncefracsqrt*ay1)/(ay2+bouncefracsqrt*ay1);
			k1 = (ay2*t2*t2+bounceplane-end_coord.y+bouncefracsqrt*(bounceplane-cy1))/
								(ay2+bouncefracsqrt*ay1);
			k0 = -t2*bouncefracsqrt*(bounceplane-cy1)/(ay2+bouncefracsqrt*ay1);
				// Now look at the nature of the solution(s).  There is either one
				// or three real roots.
			q = k1/3.0 - k2*k2/9.0;
			r = k1*k2/6.0 - k0/2.0 - k2*k2*k2/27.0;
			
			if ((q*q*q + r*r) > 0.0) {
					// only one real root.  Find it.
				bouncetime = findRoot(k0, k1, k2, 0.0, t2);
			} else {
					// three real roots.  Decide which one to pick by looking
					// at the "forced" variable.  Bracket the desired root by
					// finding the extrema of our cubic.
				q = -k2 / 3.0;
				try {
					r = Math.sqrt(k2*k2-3.0*k1) / 3.0;
				} catch (ArithmeticException e) {
						// this should never happen, since extrema should be real
					r = 0.0;
				}
				if (forced)
					bouncetime = findRoot(k0, k1, k2, 0.0, q-r);
				else
					bouncetime = findRoot(k0, k1, k2, q-r, q+r);
			}
			
				// Now we've solved for bouncetime.  The rest is simple.
			by1 = -ay1*bouncetime + (bounceplane-cy1)/bouncetime;
			by2 = -2*ay2*bouncetime - bouncefracsqrt*ay1*bouncetime
						-bouncefracsqrt*(bounceplane-cy1)/bouncetime;
			cy2 = bounceplane - ay2*bouncetime*bouncetime - by2*bouncetime;
		}
	}
	
	static protected double findRoot(double k0, double k1, double k2, double t1, double t2) {
		double	val1, val2, valtemp, t;
		
		val1 = ((t1+k2)*t1+k1)*t1+k0;
		val2 = ((t2+k2)*t2+k1)*t2+k0;
		
		if (val1*val2 > 0.0)
			return (t1+t2)/2.0;			// should never happen!
		
		while (Math.abs(t1-t2) > 0.000001) {
			t = (t1 + t2) / 2.0;
			valtemp = ((t+k2)*t+k1)*t+k0;
			if (valtemp*val1 > 0.0) {
				t1 = t;
				val1 = valtemp;
			} else {
				t2 = t;
				val2 = valtemp;
			}
		}
		return t1;
	}
	
	
	public Coordinate getCoord(double time) {
		if ((time < start_time) || (time > end_time))
			return null;
		time -= start_time;
		
		double ypos;
		
		if (time < bouncetime)
			ypos = cy1 + time*(by1 + ay1*time);
		else
			ypos = cy2 + time*(by2 + ay2*time);
		return new Coordinate(cx+bx*time, ypos);
	}
	
	public Coordinate getMax() {
		double	x, y1, y2;
		double	duration = getDuration();
		double	temp = -by1 / (2.0 * ay1);
		
		x = (bx > 0.0) ? (cx+bx*duration) : cx;
		
		if ((ay1 > 0.0) || (temp < 0.0) || (temp > bouncetime))
			y1 = Math.max(cy1, cy1+bouncetime*(by1+ay1*bouncetime));
		else
			y1 = cy1+temp*(by1+ay1*temp);
			
		temp = -by2 / (2.0 * ay2);
		if ((ay2 > 0.0) || (temp < bouncetime) || (temp > duration))
			y2 = Math.max(cy2+bouncetime*(by2+ay2*bouncetime),
						cy2+duration*(by2+ay2*duration));
		else
			y2 = cy2+temp*(by2+ay2*temp);
			
		return new Coordinate(x, Math.max(y1, y2));
	}
	
	public Coordinate getMin() {
		double	x, y1, y2;
		double	duration = getDuration();
		double	temp = -by1 / (2.0 * ay1);
		
		x = (bx > 0.0) ? cx : (cx+bx*duration);

		if ((ay1 < 0.0) || (temp < 0.0) || (temp > bouncetime))
			y1 = Math.min(cy1, cy1+bouncetime*(by1+ay1*bouncetime));
		else
			y1 = cy1+temp*(by1+ay1*temp);
			
		temp = -by2 / (2.0 * ay2);
		if ((ay2 < 0.0) || (temp < bouncetime) || (temp > duration))
			y2 = Math.min(cy2+bouncetime*(by2+ay2*bouncetime),
						cy2+duration*(by2+ay2*duration));
		else
			y2 = cy2+temp*(by2+ay2*temp);
			
		return new Coordinate(x, Math.min(y1, y2));
	}
}


// This is a ball's path as it's carried in a hand, which just locks the ball
// to the hand.

class BallPathHand extends BallPath {
	protected BallPathList	hpl;
	
	public void 		fixBall(BallPathList hpl) throws JuggleException {
		this.hpl = hpl;
	}
	
	protected void		fixInternalVariables() {}		// unused
	
	public Coordinate 	getCoord(double time) {
		if ((time >= start_time) && (time <= end_time))
			return hpl.getCoord(start_hand, time);
		return null;
	}
	
	public Coordinate 	getMax() {
		return hpl.getMax(start_hand, start_time, end_time);
	}
	
	public Coordinate 	getMin() {
		return hpl.getMin(start_hand, start_time, end_time);
	}
}


// The next class trivially extends the above case to describe the period of time
// when a ball is considered "held", as opposed to that when it is "scooped".
// See BallPathList.findNextThrow() below.

class BallPathHold extends BallPathHand {

}


// This is the path of a hand.  Some of the BallPath variables are ignored
// here.

abstract class HandPath extends BallPath {
		// use a different form of setPath() for hands.
	public void	setPath(Coordinate start, Coordinate end, double t) {
		this.start_time = 0.0;
		this.end_time = t;
		this.start_coord = start;
		this.end_coord = end;
		fixInternalVariables();
	}
		// next method is empty, since path is already determined by setPath()
	public void	fixBall(BallPathList hpl) throws JuggleException {}
	
	// getCoord(), getMax(), getMin(), fixInternalVariables() are undefined
}



// This next class creates a list of these BallPath objects to describe a
// set of objects as they move through spacetime along different paths.

class BallPathList {
	protected int		actors;
	protected double	startup_time;
	protected double	loop_time;
	protected Vector[]	paths;
	protected double[]	current_times;
	protected int[]		current_hands;
	
	
	BallPathList(int actors, double startup_time, double loop_time) {
		this.actors = actors;
		this.startup_time = startup_time;
		this.loop_time = loop_time;
		paths = new Vector[actors];
		for (int i = 0; i < actors; i++)
			paths[i] = new Vector(10, 10);
		current_times = new double[actors];
		current_hands = new int[actors];
	}
	
	
	public void setStartPoint(int actor, int hand, double time) throws JuggleException {
		if (paths[actor].size() > 0)
			throw new JuggleException("Can't set time on nonempty path list");
		current_hands[actor] = hand;
		current_times[actor] = time;
	}
	
	
	public void	addPath(int actor, BallPath bp) {
		bp.translateTime(current_times[actor]);
		bp.setStartHand(current_hands[actor]);
		current_hands[actor] = bp.getEndHand();
		current_times[actor] += bp.getDuration();
		paths[actor].addElement(bp);
	}
	
	
	public Coordinate getCoord(int actor, double time) {
		int			i;
		Coordinate	coord = null;
		BallPath	bp = null;
		
		for (i = 0; i < paths[actor].size(); i++) {
			bp = (BallPath)paths[actor].elementAt(i);
			coord = bp.getCoord(time);
			if (coord != null)
				return coord;
		}
		return null;
	}
	
	
	public Coordinate getMax() {
		BallPath	bp;
		Coordinate	temp = new Coordinate(0.0, 0.0), tempmax = null;
		
		for (int i = 0; i < actors; i++) {
			for (int j = 0; j < paths[i].size(); j++) {
				bp = (BallPath)paths[i].elementAt(j);
				tempmax = bp.getMax();
				if (tempmax != null)
					temp = Coordinate.max(temp, tempmax);
			}
		}
		return temp;
	}
	
	
	public Coordinate getMin() {
		BallPath	bp;
		Coordinate	temp = new Coordinate(0.0, 0.0), tempmin = null;
		
		for (int i = 0; i < actors; i++) {
			for (int j = 0; j < paths[i].size(); j++) {
				bp = (BallPath)paths[i].elementAt(j);
				tempmin = bp.getMin();
				if (tempmin != null)
					temp = Coordinate.min(temp, tempmin);
			}
		}
		return temp;
	}
	
	
		// The next two methods don't do exactly what we'd like, which is to
		// find the max and min coordinates of some path over an interval
		// (start, end).  These definitions extend the interval to the nearest
		// ball path endpoint.
	public Coordinate getMax(int actor, double start, double end) {
		BallPath	bp = null;
		Coordinate	coord = null, coordmax = null;
		int			i = 0, j;
	
		if (paths[actor].size() == 0)
			return new Coordinate(0.0, 0.0);
		do {
			bp = (BallPath)paths[actor].elementAt(i++);
			coord = bp.getCoord(start);
		} while ((i < paths[actor].size()) && (coord == null));
		
		if (coord == null)
			return new Coordinate(0.0, 0.0);
		j = i;
		coordmax = coord;
		
		while ((++j < paths[actor].size()) && (coord != null)) {
			bp = (BallPath)paths[actor].elementAt(j);
			coord = bp.getCoord(end);
			if (coord != null)
				coordmax = Coordinate.max(coord, coordmax);
		}
		return coordmax;
	}
		
		
	public Coordinate getMin(int actor, double start, double end) {
		BallPath	bp = null;
		Coordinate	coord = null, coordmin = null;
		int			i = 0, j;
	
		if (paths[actor].size() == 0)
			return new Coordinate(0.0, 0.0);
		do {
			bp = (BallPath)paths[actor].elementAt(i++);
			coord = bp.getCoord(start);
		} while ((i < paths[actor].size()) && (coord == null));
		
		if (coord == null)
			return new Coordinate(0.0, 0.0);
		j = i;
		coordmin = coord;
		
		while ((++j < paths[actor].size()) && (coord != null)) {
			bp = (BallPath)paths[actor].elementAt(j);
			coord = bp.getCoord(end);
			if (coord != null)
				coordmin = Coordinate.min(coord, coordmin);
		}
		return coordmin;
	}
	
	
	public void		fixBalls(BallPathList hpl) throws JuggleException {
		int		i, j;
		
		for (i = 0; i < actors; i++) {
			for (j = 0; j < paths[i].size(); j++)
				((BallPath)paths[i].elementAt(j)).fixBall(hpl);
		}
	}
		
	public int 		getActors() 		{ return actors; }
	public double 	getStartupTime() 	{ return startup_time; }
	public double 	getLoopTime() 		{ return loop_time; }
	
	
		// The following method returns the next BallPath describing a throw
		// out of the given hand (after the specified time).  The returned
		// BallPath's getStartTime() and getDuration() methods can then be used
		// to get timing information.  This method is useful mainly for
		// implementing PhysicalHands objects.
	public BallPath	findNextThrow(int hand, double time, boolean holds) {
		BallPath	bp = null, bptemp = null;
		double		mintime = 0.0, delta;
		int			i, j;
		
		for (i = 0; i < actors; i++) {
			for (j = 0; j < paths[i].size(); j++) {
				bptemp = (BallPath)paths[i].elementAt(j);
				if (bptemp.getStartHand() != hand)
					continue;
				if (holds) {
					if ((bptemp instanceof BallPathHand) &&
							(!(bptemp instanceof BallPathHold)))
						continue;
				} else {
					if (bptemp instanceof BallPathHand)
						continue;
				}

				delta = bptemp.getStartTime();
				if (delta > startup_time)
					while (delta < time)
						delta += loop_time;
				delta -= time;
				if (delta >= 0.0)
					if ((delta < mintime) || (bp == null)) {
						bp = bptemp;
						mintime = delta;
					}
			}
		}
		
		return bp;
	}
	
}




// This class contains common constants that nearly all PhysicalPatterns
// will need.  Some fields may be ignored by certain types of pattern.

class PhysicalConst {
	public double	g;				// acceleration of gravity (m/s^2)
	public double	tps;			// throws per second (average)
	public double	dwell;			// number of throw time units to spend in hand
	public double	handscoop;		// hand scoop below catch/throw pos. (m)
	public double	balldiam;		// ball diameter (m)
	public double	bouncefrac;		// fraction of energy ball retains after bounce
	
	PhysicalConst(double g, double tps, double dwell, double hs, double balldiam,
						double bouncefrac) {
		this.g = g;
		this.tps = tps;
		this.dwell = dwell;
		this.handscoop = hs;
		this.balldiam = balldiam;
		this.bouncefrac = bouncefrac;
	}
	
	PhysicalConst(PhysicalConst c)  {		// copy constructor
		this.g = c.g;
		this.tps = c.tps;
		this.dwell = c.dwell;
		this.handscoop = c.handscoop;
		this.balldiam = c.balldiam;
		this.bouncefrac = c.bouncefrac;
	}
}



// This class represents a physical instance of an asynchronous (normal) site
// swap juggling pattern.

class PhysicalAsyncSiteSwap extends PhysicalPattern {
	protected int[][]			pattern;			// throw values
	protected char[][]			mods;				// throw modifiers
	protected int[]				pattern_throws;		// # of throws
	protected int[][]			states;
	protected int				balls;
	protected int				max_throw = 0;
	protected int				length;
	protected int				max_occupancy = 1;
	
	
	PhysicalAsyncSiteSwap(String pat) throws JuggleException {
		int			i, j, k, sum = 0;
		int			pat_index, mult_index;
		int			last_pat_index, last_mult_index;
		boolean		in_braces, mod_ok;
		char[]		input = pat.toCharArray();
		char		ch;
		
		for (i = 0; i < 2; i++) {
			pat_index = mult_index = 0;
			last_pat_index = last_mult_index = 0;
			in_braces = false;
			mod_ok = false;
			
			for (j = 0; j < input.length; j++) {
				ch = input[j];
				
				if (Character.isDigit(ch) || Character.isLowerCase(ch)) {
					k = Character.digit(ch, 36);
					if ((i == 1) && (k > 0)) {
						pattern[pat_index][mult_index] = k;
						pattern_throws[pat_index]++;
						last_pat_index = pat_index;
						last_mult_index = mult_index;
						mod_ok = true;
					}
					if (in_braces) {
						if (k > 0)
							mult_index++;
					} else
						pat_index++;
				} else if (Character.isUpperCase(ch)) {
					if (i == 1) {
						if (mod_ok)
							mods[last_pat_index][last_mult_index] = ch;
						else
							throw new JuggleException("Misplaced throw modifier in pattern");
						mod_ok = false;
					}
				} else if (ch == '[') {
					if (in_braces)
						throw new JuggleException("Mismatched brackets in pattern");
					in_braces = true;
					mod_ok = false;
				} else if (ch == ']') {
					if (!in_braces)
						throw new JuggleException("Mismatched brackets in pattern");
					if (mult_index > max_occupancy)
						max_occupancy = mult_index;
					pat_index++;
					mult_index = 0;
					in_braces = false;
					mod_ok = false;
				}
			}
			
			if (in_braces)
				throw new JuggleException("Mismatched brackets in pattern");

			if (i == 0) {
				this.length = pat_index;
				pattern = new int[pat_index][max_occupancy];
				mods = new char[pat_index][max_occupancy];
				pattern_throws = new int[pat_index];
			}
		}
		
		try {
			for (i = 0; i < length; i++) {
				for (j = 0; j < max_occupancy; j++) {
					sum += pattern[i][j];
					if (pattern[i][j] > max_throw)
						max_throw = pattern[i][j];
				}
			}
		
			states = new int[length][max_throw];
			
			if ((sum % length) != 0)
				throw new JuggleException();
			balls = sum / length;
		
			for (i = 0; i < max_throw; i++) {
				k = (length - 1) - i % length;
				for (j = 0; j < pattern_throws[k]; j++) {
					sum = pattern[k][j];		// sum is just a temp variable
					if (sum > i)
						states[0][sum-i-1]++;
				}
			}
	
			if (states[0][0] != pattern_throws[0])
				throw new JuggleException();
				
			for (i = 1; i < length; i++) {
				for (j = 1; j < max_throw; j++)
					states[i][j-1] = states[i-1][j];
				states[i][max_throw-1] = 0;
				for (j = 0; j < pattern_throws[i-1]; j++) {
					k = pattern[i-1][j];
					if (k > 0)
						states[i][k-1]++;
				}
				if (states[i][0] != pattern_throws[i])
					throw new JuggleException();
			}
	
		} catch (JuggleException je) {
			throw new JuggleException("Pattern is invalid");
		} catch (IndexOutOfBoundsException e)  {
			throw new JuggleException("PASS: Internal error");
		}
	}
	
	
	public int	getStartupThrows() {
		int i, startup_throws = 0;
		
		for (i = 0; i < max_throw; i++)
			if (states[0][i] != 0)
				startup_throws = i + 1;
		return startup_throws;
	}
	
	public int	getLoopThrows() { return length; }
	public int	getMaxThrow() 	{ return max_throw; }
	
	
	public void	layoutPattern(double startup_time, double loop_time) throws JuggleException {
		int			i, throw_value; //, next_throw_value;
		char		mod_value;
		BallPath	bp = null;
		int			throw_index, throw_hand, mult_index;
		double		temp, time, total_time = startup_time + loop_time + 3.0/con.tps;
		double		borrow_time;
		int[]		used;
		
			// First create a BallPathList object, which conveniently
			// describes how the balls move.
		bpl = new BallPathList(balls, startup_time, loop_time);
		
		used = new int[2 + (int)(total_time * con.tps)];	// should be big enough
		
			// Go through the balls individually, telling the BallPathList
			// where they're going.
		for (i = 0; i < balls; i++) {
				// First figure out on which throw number the ith ball shows
				// up on.  Find the ith nonzero entry in states[0] to do this.
			throw_index = 0;
			while (pattern_throws[throw_index % length] == used[throw_index])
				throw_index++;
				
			time = throw_index / con.tps;
			borrow_time = 0.0;
			
				// Tell the BallPathList when this ball starts
			bpl.setStartPoint(i, (throw_index%2), time);
			
				// Now, keep adding to list until we have more than enough
				// of the ball's path defined.  It doesn't hurt to define
				// more than we need.
			while (time < total_time) {
					// First do the path through the air
				mult_index = used[throw_index]++;
				throw_value = pattern[throw_index % length][mult_index];
				mod_value = mods[throw_index % length][mult_index];
				throw_hand = throw_index % 2;
//				next_throw_value =
//					pattern[(throw_index+throw_value)%length][used[throw_index+throw_value]];

				if (throw_value == 1) {
					temp = (con.dwell - borrow_time) / con.tps;
					bp = new BallPathHand();
					bp.setPath(throw_hand, temp);
					bpl.addPath(i, bp);
					time += temp;
					temp = (1.0 - 0.5 * con.dwell) / con.tps;
					if (mod_value == 'B')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, false);
					else if (mod_value == 'F')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, true);
					else
						bp = new BallPathAir(-con.g);
					bp.setPath(1 - throw_hand, temp);
					bpl.addPath(i, bp);
					time += temp;
					borrow_time = 0.5 * con.dwell;
				} else if (throw_value == 2) {
					temp = (con.dwell - borrow_time) / con.tps;
					bp = new BallPathHand();
					bp.setPath(throw_hand, temp);
					bpl.addPath(i, bp);
					time += temp;
					temp = (2.0 - con.dwell) / con.tps;
					bp = new BallPathHold();
					bp.setPath(throw_hand, temp);
					bpl.addPath(i, bp);
					time += temp;
					borrow_time = 0.0;
				} else {
					temp = (con.dwell - borrow_time) / con.tps;
					bp = new BallPathHand();
					bp.setPath(throw_hand, temp);
					bpl.addPath(i, bp);
					time += temp;
					temp = ((double)throw_value - con.dwell) / con.tps;
					if (mod_value == 'B')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, false);
					else if (mod_value == 'F')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, true);
					else
						bp = new BallPathAir(-con.g);
					bp.setPath((throw_value%2==0)?throw_hand:(1-throw_hand), temp);
					bpl.addPath(i, bp);
					time += temp;
					borrow_time = 0.0;
				}
				throw_index += throw_value;
			}
		}

	}
	
}



// A physical synchronous site swap.

class PhysicalSyncSiteSwap extends PhysicalPattern {
	protected int[][][]			pattern;
	protected char[][][]		mods;
	protected int[][]			pattern_throws;
	protected int[][][]			states;
	protected int				balls;
	protected int				max_throw = 0;
	protected int				length;
	protected int				max_occupancy = 1;
	
	
	PhysicalSyncSiteSwap(String pat) throws JuggleException {
		int			i, j, k, l, m = 0, n;
		int			pat_index, hand_index, mult_index;
		int			last_pat_index, last_hand_index, last_mult_index;
		boolean		in_parens, in_braces;
		char[]		input = pat.toCharArray();
		char		ch;
		boolean		mod_ok;
		
		try {
			for (i = 0; i < 2; i++) {
				pat_index = mult_index = 0;
				hand_index = 1;
				last_pat_index = last_hand_index = last_mult_index = 0;
				in_parens = in_braces = false;
				mod_ok = false;
				
				for (j = 0; j < input.length; j++) {
					ch = input[j];
					
					if (ch == 'x') {
						throw new JuggleException();
					} else if (Character.isDigit(ch) || Character.isLowerCase(ch)) {
						if (!in_parens)
							throw new JuggleException();
						if (!in_braces && (mult_index > 0))
							throw new JuggleException();
							
						k = Character.digit(ch, 36);
						if (k > 0) {
							if ((k % 2) != 0)
								throw new JuggleException();
							if (i == 1) {
								pattern[pat_index][hand_index][mult_index] = k;
								pattern_throws[pat_index][hand_index]++;
								last_pat_index = pat_index;
								last_hand_index = hand_index;
								last_mult_index = mult_index;
								mod_ok = true;
							}
							if (((j+1) < input.length) && (input[j+1] == 'x')) {
								j++;
								if (i == 1)
									pattern[pat_index][hand_index][mult_index] *= -1;
							}
						}
						
						if (!in_braces || (k > 0))
							mult_index++;
					} else if (Character.isUpperCase(ch)) {
							// process modifiers here
						if (i == 1) {
							if (mod_ok)
								mods[last_pat_index][last_hand_index][last_mult_index] = ch;
							else
								throw new JuggleException();
							mod_ok = false;
						}
					} else if (ch == '(') {
						if (in_braces || in_parens)
							throw new JuggleException();
						in_parens = true;
						hand_index = 1;
						mult_index = 0;
						mod_ok = false;
					} else if (ch == ')') {
						if (in_braces || !in_parens || (hand_index != 0))
							throw new JuggleException();
						in_parens = false;
						pat_index++;
						mod_ok = false;
					} else if (ch == ',') {
						if (in_braces || !in_parens)
							throw new JuggleException();
						if (hand_index-- == 0)
							throw new JuggleException();
						mult_index = 0;
						mod_ok = false;
					} else if (ch == '[') {
						if (in_braces || (mult_index > 0))
							throw new JuggleException();
						in_braces = true;
						mod_ok = false;
					} else if (ch == ']') {
						if (!in_braces)
							throw new JuggleException();
						if (mult_index > max_occupancy)
							max_occupancy = mult_index;
						in_braces = false;
						mod_ok = false;
					}
				}
				
				if (in_braces || in_parens)
					throw new JuggleException();
			
				if (i == 0) {
					this.length = pat_index;
					pattern = new int[pat_index][2][max_occupancy];
					mods = new char[pat_index][2][max_occupancy];
					pattern_throws = new int[pat_index][2];
				}
			}
		} catch (JuggleException je) {
			throw new JuggleException("Syntax error in pattern");
		}

		
		try {
			for (i = 0; i < length; i++) {
				for (j = 0; j < max_occupancy; j++) {
					k = Math.abs(pattern[i][0][j]);
					l = Math.abs(pattern[i][1][j]);
					m += k + l;
					if (k > max_throw)
						max_throw = k;
					if (l > max_throw)
						max_throw = l;
				}
			}
		
			states = new int[length][2][max_throw/2];
			if ((balls % (2 * length)) != 0)
				throw new JuggleException();
			balls = m / length / 2;
		
			for (i = 0; i < max_throw/2; i++) {
				l = length - 1 - i%length;
				for (j = 0; j < 2; j++) {
					for (k = 0; k < pattern_throws[l][j]; k++) {
						m = pattern[l][j][k] / 2;
						n = Math.abs(m);
						
						if (n > i)
							states[0][(m<0)?(1-j):j][n-i-1]++;
					}
				}
			}
			if (states[0][0][0] != pattern_throws[0][0])
				throw new JuggleException();
			if (states[0][1][0] != pattern_throws[0][1])
				throw new JuggleException();
				
			for (i = 1; i < length; i++) {
				for (j = 1; j < max_throw/2; j++) {
					states[i][0][j-1] = states[i-1][0][j];
					states[i][1][j-1] = states[i-1][1][j];
				}
				states[i][0][max_throw/2-1] = states[i][1][max_throw/2-1] = 0;
				for (j = 0; j < pattern_throws[i-1][0]; j++) {
					k = pattern[i-1][0][j] / 2;
					l = Math.abs(k);
					if (l > 0)
						states[i][(k>0)?0:1][l-1]++;
				}
				for (j = 0; j < pattern_throws[i-1][1]; j++) {
					k = pattern[i-1][1][j] / 2;
					l = Math.abs(k);
					if (l > 0)
						states[i][(k>0)?1:0][l-1]++;
				}
				if (states[i][0][0] != pattern_throws[i][0])
					throw new JuggleException();
				if (states[i][1][0] != pattern_throws[i][1])
					throw new JuggleException();
			}
			
		} catch (IndexOutOfBoundsException e)  {
			throw new JuggleException("PSSS: Internal Error 2");
		} catch (JuggleException je) {
			throw new JuggleException("Pattern is invalid");
		}
	}
	
	
	public int	getStartupThrows() {
		int i, startup_throws = 0;
		
		for (i = 0; i < max_throw; i += 2)
			if ((states[0][0][i/2] != 0) || (states[0][1][i/2] != 0))
				startup_throws = i + 2;
		return startup_throws;
	}
	
	public int	getLoopThrows() { return 2*length; }
	public int	getMaxThrow() 	{ return max_throw; }
	
	
	public void layoutPattern(double startup_time, double loop_time) throws JuggleException {
		int			i, j, k;
		BallPath	bp = null;
		int			throw_index, throw_value, hand_index, mult_index;
		char		mod_value;
		double		temp, time, total_time = startup_time + loop_time + 3.0/con.tps;
		int[][]		used;
		
		bpl = new BallPathList(balls, startup_time, loop_time);
		
		used = new int[2 + (int)(total_time * con.tps / 2)][2];
		
		for (i = 0; i < balls; i++) {
			throw_index = 0;
			hand_index = 0;
			while (used[throw_index/2][hand_index] ==
							pattern_throws[throw_index/2 % length][hand_index]) {
				if (hand_index == 1)
					throw_index += 2;
				hand_index = 1 - hand_index;
			}
			time = (double)throw_index / con.tps;
				
			bpl.setStartPoint(i, hand_index, time);
			
			while (time < total_time) {
				mult_index = used[throw_index/2][hand_index]++;
				throw_value = pattern[throw_index/2 % length][hand_index][mult_index];
				mod_value = mods[throw_index/2 % length][hand_index][mult_index];

				k = Math.abs(throw_value);
				
				if (throw_value == 2) {
					temp = con.dwell / con.tps;
					bp = new BallPathHand();
					bp.setPath(hand_index, temp);
					time += temp;
					bpl.addPath(i, bp);
					temp = (2.0 - con.dwell) / con.tps;
					bp = new BallPathHold();
					bp.setPath(hand_index, temp);
					time += temp;
					bpl.addPath(i, bp);
				} else {
					temp = con.dwell / con.tps;
					time += temp;
					bp = new BallPathHand();
					bp.setPath(hand_index, temp);
					bpl.addPath(i, bp);
					temp = ((double)k - con.dwell) / con.tps;
					time += temp;

					if (mod_value == 'B')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, false);
					else if (mod_value == 'F')
						bp = new BallPathBounce(-con.g, -1.04, con.bouncefrac, true);
					else
						bp = new BallPathAir(-con.g);
						
					if (throw_value < 0)
						hand_index = 1 - hand_index;
					bp.setPath(hand_index, temp);
					bpl.addPath(i, bp);
				}
				throw_index += k;
			}
		}

	}
	
}



class HandPathDefault extends HandPath {
	protected double	bx, cx;
	protected double	ay, by, cy;
	protected double	handscoop;
	
	HandPathDefault(double handscoop)	{ this.handscoop = handscoop; }
	
	protected void	fixInternalVariables() {
		double	t = getDuration();
		
		ay = -4.0 * handscoop / (t * t);
		cx = start_coord.x;
		bx = (end_coord.x - start_coord.x) / t;
		cy = start_coord.y;
		by = (end_coord.y - start_coord.y) / t - ay * t;
	}
	
	public Coordinate getCoord(double time) {
		if ((time < start_time) || (time > end_time))
			return null;
		time -= start_time;
		return new Coordinate(cx+bx*time, cy+time*(by+ay*time));
	}
	
	public Coordinate getMax() {
		double	x, y;
		double	duration = getDuration();
		double	temp = -by / (2.0 * ay);
		
		x = (bx > 0.0) ? (cx+bx*duration) : cx;
		
		if ((ay > 0.0) || (temp < 0.0) || (temp > duration))
			y = Math.max(cy, cy+duration*(by+ay*duration));
		else
			y = cy+temp*(by+ay*temp);
		return new Coordinate(x, y);
	}
	
	public Coordinate getMin() {
		double	x, y;
		double	duration = getDuration();
		double	temp = -by / (2.0 * ay);
		
		x = (bx > 0.0) ? cx : (cx+bx*duration);

		if ((ay < 0.0) || (temp < 0.0) || (temp > duration))
			y = Math.min(cy, cy+duration*(by+ay*duration));
		else
			y = cy+temp*(by+ay*temp);
		return new Coordinate(x, y);
	}
}


class PhysicalHandsDefault extends PhysicalHands {
	protected int			hands;
	protected int			len;
	protected int			loop_throws;
	protected double[][]	pos_list;
	
	public int	getStartupThrows()		{ return 0; }
	public int	getLoopThrows()			{ return loop_throws; }
	public int	getHands()				{ return hands; }
	
	PhysicalHandsDefault(int hands, double[][] pos_list) throws JuggleException {
		this.len = pos_list.length;
		this.hands = hands;
		if ((len % (2*hands)) != 0)
			throw new JuggleException("Hand path not multiple of "+(2*hands));
		this.loop_throws = len / 2;
		this.pos_list = pos_list;
	}
	
	public void	layoutHands(BallPathList bpl, double total_time) throws JuggleException {
		int					i, j;
		double				time, delay;
		HandPathDefault		hp = null;
		Coordinate			start = null;
		Coordinate			end = null;
		BallPath			bptemp, bptemp2;
		
		this.hpl = new BallPathList(hands, bpl.getStartupTime(), bpl.getLoopTime());
		
		for (i = 0; i < hands; i++) {
			time = -4.0 / con.tps;
			hpl.setStartPoint(i, 0, time);
			j = 2 * i;
			start = new Coordinate(pos_list[j%len][0], pos_list[j%len][1]);
			
			bptemp = bpl.findNextThrow(i, time, true);		// include holds
			
			if (bptemp == null) {		// hand is inactive for entire pattern
				hp = new HandPathDefault(0.0);
				hp.setPath(start, start, total_time-time+1.0);
				hpl.addPath(i, hp);
			} else {
				delay = bptemp.getStartTime() - time - con.dwell/con.tps;
				hp = new HandPathDefault(0.0);
				hp.setPath(start, start, delay);
				hpl.addPath(i, hp);
				time += delay;
				
				while (time < total_time) {
					end = new Coordinate(pos_list[(j+1)%len][0], pos_list[(j+1)%len][1]);
					
					bptemp = bpl.findNextThrow(i, time, true);		// include holds
					
					delay = bptemp.getStartTime() - time;
					while (delay < 0.0)
						delay += bpl.getLoopTime();
					bptemp2 = bpl.findNextThrow(i, time, false);	// skip holds
					
					if ((bptemp2 == null) || (Math.abs(bptemp.getStartTime() -
								bptemp2.getStartTime()) > 0.001/con.tps) ||
								(delay > (con.dwell+0.001)/con.tps)) {
									// next throw is a hold only or a 0 throw
						if ((pos_list[j%len][0] == pos_list[(j+2*hands)%len][0]) &&
								(pos_list[j%len][1] == pos_list[(j+2*hands)%len][1])) {
									// if this catch position and next catch position are
									// identical, just sit in one spot.
							if (delay > (con.dwell+0.001)/con.tps)
								delay = 2.0 / con.tps;	// next throw is a zero
							else
								delay += (2.0 - con.dwell) / con.tps;
							hp = new HandPathDefault(0.0);
							hp.setPath(start, start, delay);
							hpl.addPath(i, hp);
							j += 2 * hands;		// don't need to update 'start'
							time += delay;
							continue;
						}
					}
					
					if (delay > (con.dwell+0.001)/con.tps)
						delay = con.dwell / con.tps;
						
						// scoop to throw
					hp = new HandPathDefault(-con.handscoop);
					hp.setPath(start, end, delay);
					hpl.addPath(i, hp);
						// go to next catch position
					j += 2 * hands;
					start = new Coordinate(pos_list[j%len][0], pos_list[j%len][1]);
					hp = new HandPathDefault(con.handscoop);
					hp.setPath(end, start, 2.0/con.tps - delay);
					hpl.addPath(i, hp);
					time += 2.0 / con.tps;
				}
			}
		}
	}
	
}



//  Here are the implementations of our own jugglers

class PhysicalJugglerDefault extends PhysicalJuggler {
	public int		getMaxLines()  		{ return 10; }
	public int		getMaxEllipses()	{ return 1; }
	
	public final static double shoulder_hw = 0.23;	// shoulder half-width (m)
	public final static double shoulder_h = 0.4;	// throw pos. to shoulder
	public final static double waist_hw = 0.17;		// waist half-width
	public final static double waist_h = -0.05;
	public final static double elbow_hw = 0.3;		// elbow "home"
	public final static double elbow_h = 0.06;
	public final static double elbow_slop = 0.12;
	public final static double hand_out = 0.05;		// outside width of hand
	public final static double hand_in = 0.05;
	public final static double head_hw = 0.10;		// head half-width
	public final static double head_h = 0.26;		// head height
	public final static double neck_h = 0.05;		// neck height
	
	
	public Vector	getLines() {
		Vector		vec = new Vector(20, 5);
		Coordinate	temp = null, lshoulder = null, rshoulder = null;
		
		lshoulder = new Coordinate(-shoulder_hw, shoulder_h);
		rshoulder = new Coordinate( shoulder_hw, shoulder_h);
		
		vec.addElement(lshoulder);
		vec.addElement(rshoulder);								// shoulders
		vec.addElement(rshoulder);
		vec.addElement(temp = new Coordinate(waist_hw, waist_h));// right side
		vec.addElement(temp);
		vec.addElement(temp = new Coordinate(-waist_hw, waist_h));	// waist
		vec.addElement(temp);
		vec.addElement(lshoulder);								// left side
		
		double relbow_x = elbow_hw + slop_func(right.x-elbow_hw, elbow_slop,
									-elbow_slop, 0.5, 0.5);
		double relbow_y = elbow_h + slop_func(right.y-elbow_h, elbow_slop,
									-elbow_slop, 0.5, 0.5);
		double lelbow_x = -elbow_hw - slop_func(-left.x-elbow_hw, elbow_slop,
									-elbow_slop, 0.5, 0.5);
		double lelbow_y = elbow_h + slop_func(left.y-elbow_h, elbow_slop,
									-elbow_slop, 0.5, 0.5);
		
		Coordinate	lelbow = new Coordinate(lelbow_x, lelbow_y);
		Coordinate	relbow = new Coordinate(relbow_x, relbow_y);
		
		vec.addElement(lshoulder);
		vec.addElement(lelbow);									// left upper arm
		vec.addElement(lelbow);
		vec.addElement(left);									// left forearm
		vec.addElement(rshoulder);
		vec.addElement(relbow);									// right upper arm
		vec.addElement(relbow);
		vec.addElement(right);									// right forearm
		vec.addElement(new Coordinate(left.x-hand_out, left.y));
		vec.addElement(new Coordinate(left.x+hand_in, left.y));	// left hand
		vec.addElement(new Coordinate(right.x-hand_in, right.y));
		vec.addElement(new Coordinate(right.x+hand_out, right.y));	// right hand
		
		return vec;
	}
	
	public Vector	getEllipses() {
		Vector		vec = new Vector(2, 5);
		
		vec.addElement(new Coordinate(-head_hw, shoulder_h+neck_h+head_h));
		vec.addElement(new Coordinate(head_hw, shoulder_h+neck_h));
		
		return vec;
	}
	
	double slop_func(double delta, double pos_slop, double neg_slop, double pos_frac, double neg_frac) {
		if (delta > pos_slop)
			return pos_frac * (delta - pos_slop);
		else if (delta < neg_slop)
			return neg_frac * (delta - neg_slop);
		return 0.0;
	}
}
