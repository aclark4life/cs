import java.applet.Applet;
import java.awt.*;


abstract class shape
{
    protected point center;                     // an attribute
    void translate(int x_by, int y_by)          // a method
    {
        center.moveby( new point(x_by, y_by) );
    }

    public abstract String toString();
    shape(int x, int y)
    {
        center = new point(x,y);
    }

}
