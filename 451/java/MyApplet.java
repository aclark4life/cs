// aclark -- jot
//
// Originally a Java Applet for CS451 PA7 (Jot, due 12/9/96): rewritten
// as a standalone Swing app since java.applet.Applet was removed from
// the JDK. Run with `java MyApplet`.

import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class MyApplet extends JPanel implements Runnable {
  Thread t;
  int x = 0, y = 0, z = 0;

  public void start() {
    t = new Thread(this);
    t.start();
  }

  public void run() {
    while (true) {
      repaint();
      try {
        Thread.sleep(10);
      } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
      }
    }
  }

  public static void main(String args[]) {
    SwingUtilities.invokeLater(() -> {
      MyApplet myapplet = new MyApplet();
      JFrame f = new JFrame("Jot");
      f.add(myapplet);
      f.pack();
      f.setSize(180, 500);
      f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      f.setVisible(true);
      myapplet.start();
    });
  }

  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    g.drawString("A", 23, 420);
    g.drawString("L", 63, 420);
    g.drawString("E", 103, 420);
    g.drawString("X", 143, 420);
    g.fillOval(x, y, 10, 10);
    y = (z * z);
    x++;
    z++;
    if (z == 20)
      z = -20;
    if (x == 156) {
      x = 0;
      y = 0;
      z = 0;
    }
  }
}

