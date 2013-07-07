/*
 * File: gobjects.h
 * ----------------
 * This interface exports a hierarchy of graphical shapes based on
 * the ACM Java Graphics model.
 */

#ifndef _gobjects_h
#define _gobjects_h

#include "gtypes.h"
#include "gwindow.h"
#include "vector.h"

class GCompound;

/*
 * Class: GObject
 * --------------
 * This class is the root of the graphical object hierarchy.
 */

class GObject {

public:

/*
 * Destructor: ~GObject
 * --------------------
 * Frees the storage for the object.
 */

   virtual ~GObject();

/*
 * Method: getX
 * Usage: double x = gobj.getX();
 * ------------------------------
 * Returns the x-coordinate of the object.
 */

   double getX() const;

/*
 * Method: getY
 * Usage: double y = gobj.getY();
 * ------------------------------
 * Returns the y-coordinate of the object.
 */

   double getY() const;

/*
 * Method: getLocation
 * Usage: GPoint pt = gobj.getLocation();
 * --------------------------------------
 * Returns the location of this object as a <code>GPoint</code>.
 */

   GPoint getLocation() const;

/*
 * Method: setLocation
 * Usage: gobj.setLocation(pt);
 *        gobj.setLocation(x, y);
 * ------------------------------
 * Sets the location of this object to the specified point.
 */

   void setLocation(const GPoint & pt);
   void setLocation(double x, double y);

/*
 * Method: move
 * Usage: gobj.move(dx, dy);
 * -------------------------
 * Moves the object on the screen using the displacements
 * <code>dx</code> and <code>dy</code>.
 */

   void move(double dx, double dy);

/*
 * Method: getWidth
 * Usage: double width = gobj.getWidth();
 * --------------------------------------
 * Returns the width of this object, which is defined to be
 * the width of the bounding box.
 */

   double getWidth() const;

/*
 * Method: getHeight
 * Usage: double height = gobj.getHeight();
 * ----------------------------------------
 * Returns the height of this object, which is defined to be
 * the height of the bounding box.
 */

   double getHeight() const;

/*
 * Method: getSize
 * Usage: GDimension size = gobj.getSize();
 * ----------------------------------------
 * Returns the size of the object as a <code>GDimension</code>.
 */

   GDimension getSize() const;

/*
 * Method: getBounds
 * Usage: GRectangle rect = gobj.getBounds();
 * ------------------------------------------
 * Returns the bounding box of this object, which is defined to be the
 * smallest rectangle that covers everything drawn by the figure.  The
 * coordinates of this rectangle do not necessarily match the location
 * returned by <code>getLocation</code>.  Given a <code>GLabel</code>
 * object, for example, <code>getLocation</code> returns the coordinates
 * of the point on the baseline at which the string begins;
 * <code>getBounds</code>, by contrast, returns a rectangle that covers
 * the entire window area occupied by the string.
 */

   virtual GRectangle getBounds() const = 0;

/*
 * Method: setColor
 * Usage: gobj.setColor(color);
 * ----------------------------
 * Sets the color used to display this object.  The <code>color</code>
 * string is usually one of the predefined color names from Java:
 *
 *    <code>BLACK</code><br>
 *    <code>BLUE</code><br>
 *    <code>CYAN</code><br>
 *    <code>DARK_GRAY</code><br>
 *    <code>GRAY</code><br>
 *    <code>GREEN</code><br>
 *    <code>LIGHT_GRAY</code><br>
 *    <code>MAGENTA</code><br>
 *    <code>ORANGE</code><br>
 *    <code>PINK</code><br>
 *    <code>RED</code><br>
 *    <code>WHITE</code><br>
 *    <code>YELLOW</code><br>
 *
 * <p>The case of the individual letters in the color name is ignored,
 * as are spaces and underscores, so that the Java color
 * <code>DARK_GRAY</code> could be written as <code>"Dark Gray"</code>.
 *
 * <p>The color can also be specified as a string in the form
 * <code>"#rrggbb"</code> where <code>rr</code>, <code>gg</code>, and
 * <code>bb</code> are pairs of hexadecimal digits indicating the
 * red, green, and blue components of the color.
 */

   void setColor(std::string color);
   void setColor(int rgb);

/*
 * Method: getColor
 * Usage: string color = gobj.getColor();
 * --------------------------------------
 * Returns the color used to display this object.  This color is
 * always returned as a string in the form <code>"#rrggbb"</code>,
 * where <code>rr</code>, <code>gg</code>, and <code>bb</code> are
 * the red, green, and blue components of the color, expressed as
 * two-digit hexadecimal values.
 */

   std::string getColor() const;

/*
 * Method: setVisible
 * Usage: gobj.setVisible(flag);
 * -----------------------------
 * Sets whether this object is visible.
 */

   void setVisible(bool flag);

/*
 * Method: isVisible
 * Usage: if (gobj.isVisible()) . . .
 * ----------------------------------
 * Returns <code>true</code> if this object is visible.
 */

   bool isVisible() const;

/*
 * Method: sendForward
 * Usage: gobj.sendForward();
 * --------------------------
 * Moves this object one step toward the front in the <i>z</i> dimension.
 * If it was already at the front of the stack, nothing happens.
 */

   void sendForward();

/*
 * Method: sendToFront
 * Usage: gobj.sendToFront();
 * --------------------------
 * Moves this object to the front of the display in the <i>z</i> dimension.
 * By moving it to the front, this object will appear to be on top of the
 * other graphical objects on the display and may hide any objects that
 * are further back.
 */

   void sendToFront();

/*
 * Method: sendBackward
 * Usage: gobj.sendBackward();
 * ---------------------------
 * Moves this object one step toward the back in the <i>z</i> dimension.
 * If it was already at the back of the stack, nothing happens.
 */

   void sendBackward();

/*
 * Method: sendToBack
 * Usage: gobj.sendToBack();
 * -------------------------
 * Moves this object to the back of the display in the <i>z</i> dimension.
 * By moving it to the back, this object will appear to be behind the other
 * graphical objects on the display and may be obscured by other objects
 * in front.
 */

   void sendToBack();

/*
 * Method: contains
 * Usage: if (gobj.contains(pt)) . . .
 *        if (gobj.contains(x, y)) . . .
 * -------------------------------------
 * Returns <code>true</code> if the specified point is inside the object.
 */

   bool contains(GPoint pt) const;
   virtual bool contains(double x, double y) const;

/*
 * Method: getType();
 * Usage: string type = gobj.getType();
 * ------------------------------------
 * Returns the concrete type of the object as a string, as in
 * <code>"GOval"</code> or <code>"GRect"</code>.
 */

   virtual std::string getType() const = 0;

/*
 * Method: toString
 * Usage: gobj.toString();
 * -----------------------
 * Returns a printable representation of the object.
 */

   virtual std::string toString() const = 0;

/*
 * Method: getParent
 * Usage: GCompound *parent = gobj.getParent();
 * --------------------------------------------
 * Returns a pointer to the <code>GCompound</code> that contains this
 * object.  Every <code>GWindow</code> is initialized to contain a single
 * <code>GCompound</code> that is aligned with the window.  Adding
 * objects to the window adds them to that <code>GCompound</code>,
 * which means that every object you add to the window has a parent.
 * Calling <code>getParent</code> on the top-level <code>GCompound</code>
 * returns <code>NULL</code>.
 */

   GCompound *getParent() const;

/* Private section */

private:
   const GObject & operator=(const GObject & src) { return *this; }
   GObject(const GObject & rhs) { }

/* Instance variables */

   double x;                       /* The x coordinate of the origin    */
   double y;                       /* The y coordinate of the origin    */
   std::string color;              /* The color of the object           */
   bool visible;                   /* Indicates if object is visible    */
   GCompound *parent;              /* Pointer to the parent             */

protected:
   GObject();

   friend class GArc;
   friend class GButton;
   friend class GCompound;
   friend class GImage;
   friend class GLabel;
   friend class GLine;
   friend class GOval;
   friend class GPolygon;
   friend class GRect;
   friend class GRoundRect;
   friend class G3DRect;

};

/*
 * Class: GRect
 * ------------
 * The <code>GRect</code> class represents a graphical object whose
 * appearance consists of a rectangular box.
 */

class GRect : public GObject {

public:

/*
 * Constructor: GRect
 * Usage: GRect rect(width, height);
 *        GRect rect(x, y, width, height);
 * ---------------------------------------
 * Constructs a new rectangle with the specified width and height.  The
 * first form is positioned at the origin; the second at the coordinates
 * given by <code>x</code> and <code>y</code>.
 */

   GRect(double width, double height);
   GRect(double x, double y, double width, double height);

/*
 * Destructor: ~GRect
 * ------------------
 * Frees any resources maintained by this object.
 */

   virtual ~GRect();

/*
 * Method: setSize
 * Usage: rect.setSize(size);
 *        rect.setSize(width, height);
 * -----------------------------------
 * Changes the size of this rectangle to the specified width and height.
 */

   void setSize(const GDimension & size);
   void setSize(double width, double height);

/*
 * Method: setBounds
 * Usage: rect.setBounds(rect);
 *        rect.setBounds(x, y, width, height);
 * -------------------------------------------
 * Changes the bounds of this rectangle to the specified values.
 */

   void setBounds(const GRectangle & size);
   void setBounds(double x, double y, double width, double height);

/*
 * Method: setFilled
 * Usage: rect.setFilled(flag);
 * ----------------------------
 * Sets the fill status for the rectangle, where <code>false</code> is
 * outlined and <code>true</code> is filled.
 */

   void setFilled(bool flag);

/*
 * Method: isFilled
 * Usage: if (rect.isFilled()) . . .
 * ---------------------------------
 * Returns <code>true</code> if the rectangle is filled.
 */

   bool isFilled() const;

/*
 * Method: setFillColor
 * Usage: rect.setFillColor(color);
 * --------------------------------
 * Sets the color used to display the filled region of this rectangle.
 */

   void setFillColor(std::string color);
   void setFillColor(int rgb);

/*
 * Method: getFillColor
 * Usage: string color = rect.getFillColor();
 * ------------------------------------------
 * Returns the color used to display the filled region of this rectangle.  If
 * none has been set, <code>getFillColor</code> returns the empty string.
 */

   std::string getFillColor() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual std::string getType() const;
   virtual std::string toString() const;

protected:

/* Instance variables */

   double width;           /* The width of the rectangle              */
   double height;          /* The height of the rectangle             */
   bool fillFlag;          /* Indicates whether the object is filled  */
   std::string fillColor;  /* Color used to fill the object           */

/* Protected methods */

   GRect();
   virtual void create(double width, double height);

};

/*
 * Class: GRoundRect
 * -----------------
 * The <code>GRoundRect</code> class represents a graphical object whose
 * appearance consists of a rectangular box with rounded corners.
 */

class GRoundRect : public GRect {

public:

/*
 * Constructor: GRoundRect
 * Usage: GRoundRect rect(width, height);
 *        GRoundRect rect(width, height, corner);
 *        GRoundRect rect(x, y, width, height);
 *        GRoundRect rect(x, y, width, height, corner);
 * ----------------------------------------------------
 * Constructs a new rectangle with the specified width and height.  If
 * the <code>x</code> and <code>y</code> parameters are specified, they
 * are used to specify the origin.  The <code>corner</code> parameter
 * specifies the diameter of the arc forming the corner.
 */

   GRoundRect(double width, double height);
   GRoundRect(double width, double height, double corner);
   GRoundRect(double x, double y, double width, double height);
   GRoundRect(double x, double y, double width, double height, double corner);

/*
 * Destructor: ~GRoundRect
 * -----------------------
 * Frees any resources maintained by this object.
 */

   virtual ~GRoundRect();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

protected:

   double corner;

/* Protected methods */
    using GRect::create;
    void create(double width, double height, double corner);
};

/*
 * Class: G3DRect
 * --------------
 * The <code>G3DRect</code> class represents a graphical object whose
 * appearance consists of a rectangular box with rounded corners.
 */

class G3DRect : public GRect {

public:

/*
 * Constructor: G3DRect
 * Usage: G3DRect rect(width, height);
 *        G3DRect rect(width, height, raised);
 *        G3DRect rect(x, y, width, height);
 *        G3DRect rect(x, y, width, height, raised);
 * -------------------------------------------------
 * Constructs a new 3D rectangle with the specified width and height.  If
 * the <code>x</code> and <code>y</code> parameters are specified, they
 * are used to specify the origin.  The <code>raised</code> parameter
 * determines whether the rectangle should be drawn with highlights that
 * suggest that it is raised about the background.
 */

   G3DRect(double width, double height);
   G3DRect(double width, double height, bool raised);
   G3DRect(double x, double y, double width, double height);
   G3DRect(double x, double y, double width, double height, bool raised);

/*
 * Destructor: ~G3DRect
 * --------------------
 * Frees any resources maintained by this object.
 */

   virtual ~G3DRect();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

protected:

   bool raised;

/* Protected methods */

    using GRect::create;
    void create(double width, double height, bool raised);
};

/*
 * Class: GOval
 * ------------
 * The <code>GOval</code> class represents a graphical object whose
 * appearance consists of an oval inscribed in a rectangular box.
 */

class GOval : public GObject {

public:

/*
 * Constructor: GOval
 * Usage: GOval oval(width, height);
 *        GOval oval(x, y, width, height);
 * ---------------------------------------
 * Constructs a new oval inscribed in the specified rectangle.  The
 * first form is positioned at the origin; the second at the coordinates
 * given by <code>x</code> and <code>y</code>.
 */

   GOval(double width, double height);
   GOval(double x, double y, double width, double height);

/*
 * Destructor: ~GOval
 * ------------------
 * Frees any resources maintained by this object.
 */

   virtual ~GOval();

/*
 * Method: setSize
 * Usage: oval.setSize(size);
 *        oval.setSize(width, height);
 * -----------------------------------
 * Changes the size of the bounding rectangle to the specified width
 * and height.
 */

   void setSize(const GDimension & size);
   void setSize(double width, double height);

/*
 * Method: setBounds
 * Usage: oval.setBounds(rect);
 *        oval.setBounds(x, y, width, height);
 * -------------------------------------------
 * Changes the bounds of the oval to the specified values.
 */

   void setBounds(const GRectangle & size);
   void setBounds(double x, double y, double width, double height);

/*
 * Method: setFilled
 * Usage: oval.setFilled(flag);
 * ----------------------------
 * Sets the fill status for the oval, where <code>false</code> is
 * outlined and <code>true</code> is filled.
 */

   void setFilled(bool flag);

/*
 * Method: isFilled
 * Usage: if (oval.isFilled()) . . .
 * ---------------------------------
 * Returns <code>true</code> if the oval is filled.
 */

   bool isFilled() const;

/*
 * Method: setFillColor
 * Usage: oval.setFillColor(color);
 * --------------------------------
 * Sets the color used to display the filled region of this oval.
 */

   void setFillColor(std::string color);
   void setFillColor(int rgb);

/*
 * Method: getFillColor
 * Usage: string color = oval.getFillColor();
 * ------------------------------------------
 * Returns the color used to display the filled region of this oval.  If
 * none has been set, <code>getFillColor</code> returns the empty string.
 */

   std::string getFillColor() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual bool contains(double x, double y) const;
   virtual std::string getType() const;
   virtual std::string toString() const;

protected:

/* Instance variables */

   double width;           /* The width of the bounding oval          */
   double height;          /* The height of the bounding oval         */
   bool fillFlag;          /* Indicates whether the object is filled  */
   std::string fillColor;  /* Color used to fill the object           */

/* Protected methods */

   void create(double width, double height);

};

/*
 * Class: GArc
 * -----------
 * The <code>GArc</code> class is a graphical object whose appearance consists
 * of an arc.  If unfilled, the arc is simply a portion of the circumference of
 * an ellipse; if filled, the arc is a pie-shaped wedge connected to the center
 * of the figure.
 */

class GArc : public GObject {

public:

/*
 * Constructor: GArc(width, height, start, sweep)
 * Usage: GArc arc(width, height, start, sweep);
 *        GArc arc(x, y, width, height, start, sweep);
 * ---------------------------------------------------
 * Creates a new <code>GArc</code> object consisting of an elliptical arc
 * located at the point (0,&nbsp;0) in the first form, or at the point
 * (<code>x</code>, <code>y</code>) in the second.
 */

   GArc(double width, double height, double start, double sweep);
   GArc(double x, double y, double width, double height,
                            double start, double sweep);

/*
 * Method: setStartAngle
 * Usage: arc.setStartAngle(start);
 * --------------------------------
 * Sets the starting angle for this <code>GArc</code> object.
 */

   void setStartAngle(double start);

/*
 * Method: getStartAngle
 * Usage: double angle = arc.getStartAngle();
 * ------------------------------------------
 * Returns the starting angle for this <code>GArc</code> object.
 */

   double getStartAngle() const;

/*
 * Method: setSweepAngle
 * Usage: arc.setSweepAngle(start);
 * --------------------------------
 * Sets the sweep angle for this <code>GArc</code> object.
 */

   void setSweepAngle(double start);

/*
 * Method: getSweepAngle
 * Usage: double angle = arc.getSweepAngle();
 * ------------------------------------------
 * Returns the sweep angle for this <code>GArc</code> object.
 */

   double getSweepAngle() const;

/*
 * Method: getStartPoint
 * Usage: GPoint pt = arc.getStartPoint();
 * ---------------------------------------
 * Returns the point at which the arc starts.
 */

   GPoint getStartPoint() const;

/*
 * Method: getEndPoint
 * Usage: GPoint pt = arc.getEndPoint();
 * -------------------------------------
 * Returns the point at which the arc ends.
 */

   GPoint getEndPoint() const;

/*
 * Method: setFrameRectangle
 * Usage: arc.setFrameRectangle(rect);
 *        arc.setFrameRectangle(x, y, width, height);
 * --------------------------------------------------
 * Changes the boundaries of the rectangle used to frame the arc.
 */

   void setFrameRectangle(const GRectangle & rect);
   void setFrameRectangle(double x, double y, double width, double height);

/*
 * Method: getFrameRectangle
 * Usage: GRectangle rect = arc.getFrameRectangle();
 * -------------------------------------------------
 * Returns the boundaries of the rectangle used to frame the arc.
 */

   GRectangle getFrameRectangle() const;

/*
 * Method: setFilled
 * Usage: arc.setFilled(flag);
 * ---------------------------
 * Sets the fill status for the arc, where <code>false</code> is
 * outlined and <code>true</code> is filled.
 */

   void setFilled(bool flag);

/*
 * Method: isFilled
 * Usage: if (arc.isFilled()) . . .
 * --------------------------------
 * Returns <code>true</code> if the arc is filled.
 */

   bool isFilled() const;

/*
 * Method: setFillColor
 * Usage: arc.setFillColor(color);
 * -------------------------------
 * Sets the color used to display the filled region of this arc.
 */

   void setFillColor(std::string color);
   void setFillColor(int rgb);

/*
 * Method: getFillColor
 * Usage: string color = arc.getFillColor();
 * -----------------------------------------
 * Returns the color used to display the filled region of this arc.  If
 * none has been set, <code>getFillColor</code> returns the empty string.
 */

   std::string getFillColor() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual bool contains(double x, double y) const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:

   GPoint getArcPoint(double theta) const;
   bool containsAngle(double theta) const;
   void create(double width, double height, double start, double sweep);

/* Instance variables */

   double start;                   /* Starting angle of the arc       */
   double sweep;                   /* How many degrees the arc runs   */
   double frameWidth;              /* The width of the bounding box   */
   double frameHeight;             /* The height of the bounding box  */
   std::string fillColor;          /* The color of the interior       */
   bool fillFlag;                  /* Indicates if the arc is filled  */

};

/*
 * Class: GCompound
 * ----------------
 * This class defines a graphical object that consists of a collection
 * of other graphical objects.  Once assembled, the internal objects
 * can be manipulated as a unit.
 */

class GCompound : public GObject {

public:

/*
 * Constructor: GCompound
 * Usage: GCompound comp();
 * ------------------------
 * Creates a <code>GCompound</code> object with no internal components.
 */

   GCompound();

/*
 * Method: add
 * Usage: comp.add(gobj);
 *        comp.add(gobj, x, y);
 * ----------------------------
 * Adds a new graphical object to the <code>GCompound</code>.  The second
 * form moves the object to the point (<code>x</code>, <code>y</code>) first.
 */

   void add(GObject *gobj);
   void add(GObject *gobj, double x, double y);

/*
 * Method: remove
 * Usage: comp.remove(gobj);
 * -------------------------
 * Removes the specified object from the <code>GCompound</code>.
 */

   void remove(GObject *gobj);

/*
 * Method: removeAll
 * Usage: comp.removeAll();
 * ------------------------
 * Removes all graphical objects from the <code>GCompound</code>.
 */

   void removeAll();

/*
 * Method: getElementCount
 * Usage: int n = comp.getElementCount();
 * --------------------------------------
 * Returns the number of graphical objects stored in the
 * <code>GCompound</code>.
 */

   int getElementCount();

/*
 * Method: getElement
 * Usage: GObject *gobj = comp.getElement(index);
 * ----------------------------------------------
 * Returns a pointer to the graphical object at the specified index,
 * numbering from back to front in the the <i>z</i> dimension.
 */

   GObject *getElement(int index);

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual bool contains(double x, double y) const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   void sendForward(GObject *gobj);
   void sendToFront(GObject *gobj);
   void sendBackward(GObject *gobj);
   void sendToBack(GObject *gobj);
   int findGObject(GObject *gobj);
   void removeAt(int index);

/* Instance variables */

   Vector<GObject *> contents;
   GWindow *gw;

/* Friend declarations */

   friend class GObject;

};

/*
 * Class: GImage
 * -------------
 * The <code>GImage</code> class represents an image that can be displayed
 * on the screen.
 */

class GImage : public GObject {

public:

/*
 * Constructor: GImage
 * Usage: GImage image(filename);
 *        GImage image(filename, x, y);
 * ------------------------------------
 * This method constructs a new image by loading the image from the specified
 * file, which is either in the current directory or a subdirectory named
 * <code>images</code>.  By default, the upper left corner of the image
 * appears at the origin; the second form automatically resets the location
 * to the point (<code>x</code>, <code>y</code>).
 */

   GImage(std::string filename);
   GImage(std::string filename, double x, double y);

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   std::string filename;
   double width;
   double height;

   void create(std::string filename);

};

/*
 * Class: GLabel
 * -------------
 * The <code>GLabel</code> class represents a text string displayed in the
 * window.
 */

class GLabel : public GObject {

public:

/*
 * Method: GLabel
 * Usage: GLabel label(str);
 *        GLabel label(str, x, y);
 * -------------------------------
 * Creates a <code>GLabel</code> object containing the specified string.
 * By default, the baseline of the first character appears at the origin;
 * the second form automatically resets the location of the
 * <code>GLabel</code> to the point (<code>x</code>, <code>y</code>).
 */

   GLabel(std::string str);
   GLabel(std::string str, double x, double y);

/*
 * Method: setFont
 * Usage: label.setFont(font);
 * ---------------------------
 * Changes the font used to display the <code>GLabel</code> as specified by
 * the string <code>font</code>, which has the following format:
 *
 *<pre>
 *    family-style-size
 *</pre>
 *
 * where both <code>style</code> and <code>size</code> are optional.
 * If any of these elements are missing or specified as an asterisk,
 * the existing value is retained.
 */

   void setFont(std::string font);

/*
 * Method: getFont
 * Usage: string font = label.getFont();
 * -------------------------------------
 * Returns the current font for the <code>GLabel</code>.
 */

   std::string getFont() const;

/*
 * Method: setLabel
 * Usage: label.setLabel(str);
 * ---------------------------
 * Changes the string stored within the <code>GLabel</code> object, so that
 * a new text string appears on the display.
 */

   void setLabel(std::string str);

/*
 * Method: getLabel
 * Usage: string str = label.getLabel();
 * -------------------------------------
 * Returns the string displayed by this object.
 */

   std::string getLabel() const;

/*
 * Method: getFontAscent
 * Usage: double ascent = getFontAscent();
 * ---------------------------------------
 * Returns the maximum distance strings in this font extend above
 * the baseline.
 */

   double getFontAscent() const;

/*
 * Method: getFontDescent
 * Usage: double descent = getFontDescent();
 * -----------------------------------------
 * Returns the maximum distance strings in this font descend below
 * the baseline.
 */

   double getFontDescent() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:

/* Instance variables */

   std::string str;                /* The string displayed by the label */
   std::string font;               /* The font string of the label      */

   void create(const std::string & str);

};

/*
 * Class: GLine
 * ------------
 * The <code>GLine</code> class is a graphical object whose appearance consists
 * of a line segment.
 */

class GLine : public GObject {

public:

/*
 * Constructor: GLine
 * Usage: GLine gline(x0, y0, x1, y1);
 * -----------------------------------
 * Constructs a line segment from its endpoints.  The point
 * (<code>x0</code>,&nbsp;<code>y0</code>) defines the start of the
 * line and the point (<code>x1</code>,&nbsp;<code>y1</code>) defines
 * the end.
 */

   GLine(double x0, double y0, double x1, double y1);

/*
 * Method: setStartPoint
 * Usage: line.setStartPoint(x, y);
 * --------------------------------
 * Sets the initial point in the line to (<code>x</code>,&nbsp;<code>y</code>),
 * leaving the end point unchanged.  This method is therefore different from
 * <code>setLocation</code>, which moves both components of the line segment.
 */

   void setStartPoint(double x, double y);

/*
 * Method: getStartPoint
 * Usage: GPoint pt = line.getStartPoint();
 * ----------------------------------------
 * Returns the point at which the line starts.
 */

   GPoint getStartPoint() const;

/*
 * Method: setEndPoint
 * Usage: line.setEndPoint(x, y);
 * ------------------------------
 * Sets the end point in the line to (<code>x</code>,&nbsp;<code>y</code>),
 * leaving the start point unchanged.  This method is therefore different from
 * <code>setLocation</code>, which moves both components of the line segment.
 */

   void setEndPoint(double x, double y);

/*
 * Method: getEndPoint
 * Usage: GPoint pt = line.getEndPoint();
 * --------------------------------------
 * Returns the point at which the line ends.
 */

   GPoint getEndPoint() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual bool contains(double x, double y) const;
   virtual std::string getType() const;
   virtual std::string toString() const;

protected:

/* Instance variables */

   double dx;                   /* The x displacement of the line */
   double dy;                   /* The y displacement of the line */

};

/*
 * Class: GPolygon
 * ---------------
 * The <code>GPolygon</code> class represents a polygon bounded by
 * line segments.
 */

class GPolygon : public GObject {

public:

/*
 * Constructor: GPolygon
 * Usage: GPolygon poly;
 * ---------------------
 * Constructs a new empty polygon at the origin.
 */

   GPolygon();

/*
 * Method: addVertex
 * Usage: poly.addVertex(x, y);
 * ----------------------------
 * Adds a vertex at (<code>x</code>, <code>y</code>) relative to the polygon
 * origin.
 */

   void addVertex(double x, double y);

/*
 * Method: addEdge
 * Usage: poly.addEdge(dx, dy);
 * ----------------------------
 * Adds an edge to the polygon whose components are given by the displacements
 * <code>dx</code> and <code>dy</code> from the last vertex.
 */

   void addEdge(double dx, double dy);

/*
 * Method: addPolarEdge
 * Usage: poly.addPolarEdge(r, theta);
 * -----------------------------------
 * Adds an edge to the polygon specified in polar coordinates.  The length
 * of the edge is given by <code>r</code>, and the edge extends in
 * direction <code>theta</code>, measured in degrees counterclockwise
 * from the +x axis.
 */

   void addPolarEdge(double r, double theta);

/*
 * Method: getVertices
 * Usage: Vector<GPoint> vec = poly.getVertices();
 * -----------------------------------------------
 * Returns a vector of the points in the polygon.
 */

   Vector<GPoint> getVertices() const;

/*
 * Method: setFilled
 * Usage: poly.setFilled(flag);
 * ----------------------------
 * Sets the fill status for the polygon, where <code>false</code> is
 * outlined and <code>true</code> is filled.
 */

   void setFilled(bool flag);

/*
 * Method: isFilled
 * Usage: if (poly.isFilled()) . . .
 * ---------------------------------
 * Returns <code>true</code> if the polygon is filled.
 */

   bool isFilled() const;

/*
 * Method: setFillColor
 * Usage: poly.setFillColor(color);
 * --------------------------------
 * Sets the color used to display the filled region of this polygon.
 */

   void setFillColor(std::string color);
   void setFillColor(int rgb);

/*
 * Method: getFillColor
 * Usage: string color = poly.getFillColor();
 * ------------------------------------------
 * Returns the color used to display the filled region of this polygon.  If
 * none has been set, <code>getFillColor</code> returns the empty string.
 */

   std::string getFillColor() const;

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual bool contains(double x, double y) const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:

/* Instance variables */

   Vector<GPoint> vertices;        /* The vertices of the polygon   */
   double cx;                      /* The most recent x coordinate  */
   double cy;                      /* The most recent y coordinate  */
   std::string fillColor;          /* The color of the interior     */
   bool fillFlag;                  /* Indicates if object is filled */

};

/*
 * Class: GButton
 * --------------
 * The <code>GButton</code> class represents an onscreen button.
 */

class GButton : public GObject {

public:
   GButton(std::string label);

/*
 * Method: setSize
 * Usage: button.setSize(size);
 *        button.setSize(width, height);
 * -------------------------------------
 * Changes the size of the button to the specified width and height.
 */

   void setSize(const GDimension & size);
   void setSize(double width, double height);

/*
 * Method: setBounds
 * Usage: button.setBounds(rect);
 *        button.setBounds(x, y, width, height);
 * ---------------------------------------------
 * Changes the bounds of the button to the specified values.
 */

   void setBounds(const GRectangle & size);
   void setBounds(double x, double y, double width, double height);

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;
   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   std::string label;

};

#endif
