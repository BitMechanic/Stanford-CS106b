/*
 * File: gwindow.h
 * ---------------
 * This interface defines the GWindow class which supports drawing lines,
 * rectangles, ovals, arcs, polygons, images, and strings.
 */

#ifndef _gwindow_h
#define _gwindow_h

#include <string>
#include "gtypes.h"
#include "vector.h"

class GCompound;
class GObject;

/*
 * Class: GWindow
 * --------------
 * This class represents a graphics window that serves as a drawing surface.
 */

class GWindow {

public:

/*
 * Constructor: GWindow
 * Usage: GWindow gw;
 *        GWindow gw(width, height);
 * ---------------------------------
 * Creates a window, either of the specified size or a default size.
 */

   GWindow();
   GWindow(double width, double height);

/*
 * Destructor: ~GWindow
 * --------------------
 * Reclaims the internal storage for the window.  Note that the window
 * is not closed by this operation, but persists until it is closed by
 * the client or the user exits the program.
 */

   ~GWindow();

/*
 * Method: close
 * Usage: gw.close();
 * ------------------
 * Deletes the window from the screen.
 */

   void close();

/*
 * Method: requestFocus
 * Usage: gw.requestFocus();
 * -------------------------
 * Asks the system to assign the keyboard focus to the window, which
 * brings it to the top and ensures that key events are delivered to
 * the window.  Clicking in the window automatically requests the focus.
 */

   void requestFocus();

/*
 * Method: clear
 * Usage: gw.clear();
 * ------------------
 * Clears the contents of the window.
 */

   void clear();

/*
 * Method: setVisible
 * Usage: gw.setVisible(flag);
 * ---------------------------
 * Determines whether the window is visible on the screen.
 */

   void setVisible(bool flag);

/*
 * Method: isVisible
 * Usage: if (gw.isVisible()) . . .
 * --------------------------------
 * Tests whether the window is visible.
 */

   bool isVisible();

/*
 * Method: drawLine
 * Usage: gw.drawLine(p0, p1);
 *        gw.drawLine(x0, y0, x1, y1);
 * -----------------------------------
 * Draws a line connecting the specified points.
 */

   void drawLine(const GPoint & p0, const GPoint & p1);
   void drawLine(double x0, double y0, double x1, double y1);

/*
 * Method: drawPolarLine
 * Usage: GPoint p1 = gw.drawPolarLine(p0, r, theta);
 *        GPoint p1 = gw.drawPolarLine(x0, y0, r, theta);
 * ------------------------------------------------------
 * Draws a line of length <code>r</code> in the direction <code>theta</code>
 * from the initial point.  The angle <code>theta</code> is measured in
 * degrees counterclockwise from the +<i>x</i> axis.  The method returns
 * the end point of the line.
 */

   GPoint drawPolarLine(const GPoint & p0, double r, double theta);
   GPoint drawPolarLine(double x0, double y0, double r, double theta);

/*
 * Method: drawOval
 * Usage: gw.drawOval(bounds);
 *        gw.drawOval(x, y, width, height);
 * ----------------------------------------
 * Draws the frame of a oval with the specified bounds.
 */

   void drawOval(const GRectangle & bounds);
   void drawOval(double x, double y, double width, double height);

/*
 * Method: fillOval
 * Usage: gw.fillOval(bounds);
 *        gw.fillOval(x, y, width, height);
 * ----------------------------------------
 * Fills the frame of a oval with the specified bounds.
 */

   void fillOval(const GRectangle & bounds);
   void fillOval(double x, double y, double width, double height);

/*
 * Method: drawRect
 * Usage: gw.drawRect(bounds);
 *        gw.drawRect(x, y, width, height);
 * ----------------------------------------
 * Draws the frame of a rectangle with the specified bounds.
 */

   void drawRect(const GRectangle & bounds);
   void drawRect(double x, double y, double width, double height);

/*
 * Method: fillRect
 * Usage: gw.fillRect(bounds);
 *        gw.fillRect(x, y, width, height);
 * ----------------------------------------
 * Fills the frame of a rectangle with the specified bounds.
 */

   void fillRect(const GRectangle & bounds);
   void fillRect(double x, double y, double width, double height);

/*
 * Method: setColor
 * Usage: gw.setColor(color);
 * --------------------------
 * Sets the color used for drawing.  The <code>color</code> parameter is
 * usually one of the predefined color names from Java: <code>BLACK</code>,
 * <code>BLUE</code>, <code>CYAN</code>, <code>DARK_GRAY</code>,
 * <code>GRAY</code>, <code>GREEN</code>, <code>LIGHT_GRAY</code>,
 * <code>MAGENTA</code>, <code>ORANGE</code>, <code>PINK</code>,
 * <code>RED</code>, <code>WHITE</code>, or <code>YELLOW</code>.
 * The case of the individual letters in the color name is ignored,
 * as are spaces and underscores, so that the Java color
 * <code>DARK_GRAY</code> could be written as <code>"Dark&nbsp;Gray"</code>.
 *
 * <p>The color can also be specified as a string in the form
 * <code>"#rrggbb"</code> where <code>rr</code>, <code>gg</code>, and
 * <code>bb</code> are pairs of hexadecimal digits indicating the
 * red, green, and blue components of the color.
 */

   void setColor(std::string color);
   void setColor(int color);

/*
 * Method: getColor
 * Usage: string color = gw.getColor();
 * ------------------------------------
 * Returns the current color as a string in the form <code>"#rrggbb"</code>.
 * In this string, the values <code>rr</code>, <code>gg</code>,
 * and <code>bb</code> are two-digit hexadecimal values representing
 * the red, green, and blue components of the color, respectively.
 */

   std::string getColor();

/*
 * Method: getWidth
 * Usage: double width = gw.getWidth();
 * ------------------------------------
 * Returns the width of the graphics window in pixels.
 */

   double getWidth();

/*
 * Method: getHeight
 * Usage: double height = gw.getHeight();
 * --------------------------------------
 * Returns the height of the graphics window in pixels.
 */

   double getHeight();

/*
 * Method: repaint
 * Usage: gw.repaint();
 * --------------------
 * Schedule a repaint on this window.
 */

   void repaint();

/*
 * Method: setWindowTitle
 * Usage: gw.setWindowTitle(title);
 * --------------------------------
 * Sets the title of the graphics window.
 */

   void setWindowTitle(std::string title);

/*
 * Method: getWindowTitle
 * Usage: string title = gw.getWindowTitle();
 * ------------------------------------------
 * Returns the title of the graphics window.
 */

   std::string getWindowTitle();

/*
 * Method: draw
 * Usage: gw.draw(gobj);
 *        gw.draw(gobj, x, y);
 * ---------------------------
 * Draws the <code>GObject</code> on the background layer.  For convenience,
 * the <code>gobj</code> parameter may be passed either as a constant
 * reference or as a pointer.  If the <code>x</code> and <code>y</code>
 * parameters are included, the object is moved to that location before
 * drawing.
 */

   void draw(const GObject & gobj);
   void draw(GObject *gobj);
   void draw(const GObject *gobj);
   void draw(GObject & gobj, double x, double y);
   void draw(GObject *gobj, double x, double y);

/*
 * Method: add
 * Usage: gw.add(gobj);
 *        gw.add(gobj, x, y);
 * --------------------------
 * Adds the <code>GObject</code> to the foreground layer of the window.
 * The second form of the call sets the location of the object to
 * (<code>x</code>, <code>y</code>) first.
 */

   void add(GObject *gobj);
   void add(GObject *gobj, double x, double y);

// Document

   void remove(GObject *gobj);
   GObject *getGObjectAt(double x, double y);

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

   GWindow(bool visible);
   GWindow(double width, double height, bool visible);

private:

   double windowWidth;
   double windowHeight;
   std::string windowTitle;
   std::string color;
   bool visible;
   GCompound *topCompound;

   void initGWindow(double width, double height, bool visible);

   friend class Platform;

};

/*
 * Function: repaint
 * Usage: repaint();
 * -----------------
 * Issues a request to update all graphics windows.  This function
 * is called automatically when the program pauses, waits for an
 * event, waits for user input on the console, or terminates.  As
 * a result, most clients never need to call repaint explicitly.
 */

void repaint();

/*
 * Function: pause
 * Usage: pause(milliseconds);
 * ---------------------------
 * Pauses for the indicated number of milliseconds.  This function is
 * useful for animation where the motion would otherwise be too fast.
 */

void pause(double milliseconds);

/*
 * Function: getScreenWidth
 * Usage: width = getScreenWidth();
 * --------------------------------
 * Returns the width of the entire display screen.
 */

double getScreenWidth();

/*
 * Function: getScreenHeight
 * Usage: height = getScreenHeight();
 * ----------------------------------
 * Returns the height of the entire display screen.
 */

double getScreenHeight();

/*
 * Function: convertColorToRGB
 * Usage: int rgb = convertColorToRGB(colorName);
 * ----------------------------------------------
 * Converts a color name into an integer that encodes the
 * red, green, and blue components of the color.
 */

int convertColorToRGB(std::string colorName);

/*
 * Function: convertRGBToColor
 * Usage: int colorName = convertRGBToColor(rgb);
 * ----------------------------------------------
 * Converts an <code>rgb</code> value into a color name in the
 * form <code>"#rrggbb"</code>.  Each of the <code>rr</code>,
 * <code>gg</code>, and <code>bb</code> values are two-digit
 * hexadecimal numbers indicating the intensity of that component.
 */

std::string convertRGBToColor(int rgb);

/*
 * Function: waitForClick
 * Usage: waitForClick();
 * ----------------------
 * Waits for a mouse click to occur anywhere in any window.
 */

void waitForClick();

/*
 * Function: exitGraphics
 * Usage: exitGraphics();
 * ----------------------
 * Closes all graphics windows and exits from the application without
 * waiting for any additional user interaction.
 */

void exitGraphics();

#include "console.h"
#include "private/main.h"

#endif
