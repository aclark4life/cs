import java.applet.Applet;
import java.awt.*;

public class point extends Applet {
  protected int x;
  protected int y;

  public void init() {
    Panel childPanel = new Panel();
    add(childPanel);
  }

  point add(point p2) {
    return (new point(x + p2.x, y + p2.y));
  }

  /* no return type */ point() {
    x = y = 0;
  }

  public String toString() { return ("(" + x + "," + y + ")"); }

  point(int x0, int y0) {
    x = x0;
    y = y0;
  }

  void moveby(point p) {
    x += p.x;
    y += p.y;
  }
}

