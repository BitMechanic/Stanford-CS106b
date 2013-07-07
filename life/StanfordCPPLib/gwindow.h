/*
 * File: gwindow.h
 * ---------------
 * This interface defines the GWindow class which supports drawing lines,
 * rectangles, ovals, arcs, polygons, images, and strings.
 */

#ifndef _graphics_h
#define _graphics_h

#include <string>
#include "gtypes.h"
#include "vector.h"

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
 * Closes the window and reclaims its internal storage.
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
 * Method: clear
 * Usage: gw.clear();
 * ------------------
 * Clears the contents of the graphics window.
 */

   void clear();

/*
 * Method: setVisible
 * Usage: gw.setVisible(flag);
 * ---------------------------
 * Determines whether the window is visible on the screen.  Windows start
 * out in an invisible state and must be made visible before they appear.
 */

   void setVisible(bool flag);

/*
 * Method: isVisible
 * Usage: if (gw.isVisible()) . . .
 * --------------------------------
 * Tests whether the window is visible.
 */

   bool isVisible() const;

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
 * Method: drawArc
 * Usage: gw.drawArc(bounds, start, sweep);
 *        gw.drawArc(x, y, width, height, start, sweep);
 * -----------------------------------------------------
 * Draws an elliptical arc inscribed in a rectangle.  The parameters
 * <code>x</code>, <code>y</code>, <code>width</code>, and <code>height</code>
 * (or, equivalently, the <code>GRectangle</code> <code>bounds</code>)
 * specify the coordinates and dimensions of the bounding rectangle.
 * The <code>start</code> parameter indicates the angle at which the
 * arc begins and is measured in degrees counterclockwise from the
 * +<i>x</i> axis.  Thus, a <code>start</code> angle of 0 indicates
 * an arc that begins along the line running eastward from the center,
 * a <code>start</code> angle of 135 begins along the line running
 * northwest, and a <code>start</code> angle of -90 begins along
 * the line running south.  The <code>sweep</code> parameter indicates
 * the extent of the arc and is also measured in degrees counterclockwise.
 * A <code>sweep</code> angle of 90 defines a quarter circle extending
 * counterclockwise from the <code>start</code> angle, and a
 * <code>sweep</code> angle of -180 defines a semicircle extending
 * clockwise.
 */

   void drawArc(const GRectangle & bounds, double start, double sweep);
   void drawArc(double x, double y, double width, double height,
                                    double start, double sweep);

/*
 * Method: fillArc
 * Usage: gw.fillArc(bounds, start, sweep);
 *        gw.fillArc(x, y, width, height, start, sweep);
 * -----------------------------------------------------
 * Fills a wedge-shaped area of an elliptical arc.  The parameters are
 * interpreted in the same way as those for <code>drawArc</code>.
 */

   void fillArc(const GRectangle & bounds, double start, double sweep);
   void fillArc(double x, double y, double width, double height,
                                 double start, double sweep);

/*
 * Method: drawImage
 * Usage: gw.drawImage(filename, pt);
 *        gw.drawImage(filename, x, y);
 *        gw.drawImage(filename, bounds);
 *        gw.drawImage(filename, x, y, width, height);
 * ---------------------------------------------------
 * Draws the image from the specified file with its upper left corner
 * at the specified point.  The forms of the call that include the
 * bounds scale the image so that it fits inside the specified rectangle.
 */

   void drawImage(std::string filename, const GPoint & pt);
   void drawImage(std::string filename, double x, double y);
   void drawImage(std::string filename, const GRectangle & bounds);
   void drawImage(std::string filename, double x, double y,
                                        double width, double height);

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
 * Method: drawPolygon
 * Usage: gw.drawPolygon(polygon);
 *        gw.drawPolygon(polygon, pt);
 *        gw.drawPolygon(polygon, x, y);
 * -------------------------------------
 * Draws the outline of the specified polygon.  The optional <code>pt</code>
 * or <code>x</code> and <code>y</code> parameters shift the origin
 * of the polygon to the specified point.
 */

   void drawPolygon(const Vector<GPoint> & polygon);
   void drawPolygon(const Vector<GPoint> & polygon, const GPoint & pt);
   void drawPolygon(const Vector<GPoint> & polygon, double x, double y);

/*
 * Method: fillPolygon
 * Usage: gw.fillPolygon(polygon);
 *        gw.fillPolygon(polygon, pt);
 *        gw.fillPolygon(polygon, x, y);
 * -------------------------------------
 * Fills the frame of the specified polygon.  The optional <code>pt</code>
 * or <code>x</code> and <code>y</code> parameters shift the origin
 * of the polygon to the specified point.
 */

   void fillPolygon(const Vector<GPoint> & polygon);
   void fillPolygon(const Vector<GPoint> & polygon, const GPoint & pt);
   void fillPolygon(const Vector<GPoint> & polygon, double x, double y);

/*
 * Method: drawString
 * Usage: gw.drawString(str, pt);
 *        gw.drawString(str, x, y);
 * --------------------------------
 * Draws the string <code>str</code> so that its origin appears at
 * the specified point.  The text appears in the current font and color.
 */

   void drawString(std::string str, const GPoint & pt);
   void drawString(std::string str, double x, double y);

/*
 * Method: getStringWidth
 * Usage: double width = gw.getStringWidth(str);
 * ---------------------------------------------
 * Returns the width of the string <code>str</code> when displayed in
 * the current font.
 */

   double getStringWidth(std::string str);

/*
 * Method: setFont
 * Usage: gw.setFont(font);
 * ------------------------
 * Sets a new font.  The <code>font</code> parameter is a string in the
 * form <i>family</i><code>-</code><i>style</i><code>-</code><i>size</i>.
 * In this string, <i>family</i> is the name of the font family;
 * <i>style</i> is either missing (indicating a plain font) or one
 * of the strings <code>Bold</code>, <code>Italic</code>, or
 * <code>BoldItalic</code>; and <i>size</i> is an integer
 * indicating the point size.  If any of these components is
 * specified as an asterisk, the existing value is retained.
 */

   void setFont(std::string font);

/*
 * Method: getFont
 * Usage: string font = gw.getFont();
 * ----------------------------------
 * Returns the current font.
 */

   std::string getFont() const;

/*
 * Method: getFontHeight
 * Usage: double height = getFontHeight();
 * ---------------------------------------
 * Returns the <i>height</i> of the current font, which is the separation
 * in pixels between successive text lines.
 */

   double getFontHeight() const;

/*
 * Method: getFontAscent
 * Usage: double height = getFontAscent();
 * ---------------------------------------
 * Returns the <i>ascent</i> of the current font, which is defined to be
 * the maximum distance in pixels that characters rise above the baseline.
 */

   double getFontAscent() const;

/*
 * Method: getFontDescent
 * Usage: double height = getFontDescent();
 * ----------------------------------------
 * Returns the <i>descent</i> of the current font, which is defined to be
 * the maximum distance in pixels that characters extend below the baseline.
 */

   double getFontDescent() const;

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

/*
 * Method: getColor
 * Usage: string color = gw.getColor();
 * ------------------------------------
 * Returns the current color as a string in the form <code>"#rrggbb"</code>.
 * In this string, the values <code>rr</code>, <code>gg</code>,
 * and <code>bb</code> are two-digit hexadecimal values representing
 * the red, green, and blue components of the color, respectively.
 */

   std::string getColor() const;

/*
 * Method: saveGraphicsState
 * Usage: gw.saveGraphicsState();
 * ------------------------------
 * Saves the state of the graphics context.  This function is used
 * in conjunction with <code>restoreGraphicsState()</code> to avoid
 * changing the state set up by the client.
 */

   void saveGraphicsState();

/*
 * Method: restoreGraphicsState
 * Usage: gw.restoreGraphicsState();
 * ---------------------------------
 * Restores the graphics state from the most recent call to
 * <code>saveGraphicsState()</code>.
 */

   void restoreGraphicsState();

/*
 * Method: getWidth
 * Usage: double width = gw.getWidth();
 * ------------------------------------
 * Returns the width of the graphics window in pixels.
 */

   double getWidth() const;

/*
 * Method: getHeight
 * Usage: double height = gw.getHeight();
 * --------------------------------------
 * Returns the height of the graphics window in pixels.
 */

   double getHeight() const;

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

   std::string getWindowTitle() const;

#include "private/gwindowpriv.h"

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
