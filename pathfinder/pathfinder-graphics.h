/**
 * File: pathfinder-graphics.h
 * ---------------------------
 * The pathfinder-graphics.h file defines the interface for a set of functions
 * that help draw the necessary parts of the Pathfinder maps.  The
 * pathfinder-graphics.h interface uses screen coordinates in which distances
 * on the screen are expressed in pixels and in which the origin in the
 * upper left corner of the window.  Several of the functions defined
 * in this package use values of type GPoint, which is simply a pair of
 * x and y coordinate values, as defined in the point.h interface.
 *
 * This interface also exports several methods for creating buttons
 * in a control strip and for responding to button and mouse clicks.
 * The general approach parallels the standard model used in modern
 * event-driven systems.  The client application creates a series of
 * buttons, each of which supplies a callback function that is
 * invoked whenever that button is clicked.  The application then
 * calls pathfinderEventLoop, which waits for events generated in
 * response to user actions.
 */

#ifndef _pathfinder_graphics_
#define _pathfinder_graphics_

#include "gtypes.h"
#include "gobjects.h"

/**
 * Constants
 * ---------
 * A few program-wide constants concerning the graphical display.
 * All coordinate values and distances are expressed in pixels.
 */

const int kWindowWidth = 655;
const int kWindowHeight = 400;
const int kControlStripHeight = 40;
const double kNodeRadius = 3.5;           /* Radius of the node circle    */
const string kArcColor = "DarkGray";      /* Normal arc color             */
const string kNodeColor = "Black";        /* Normal node color            */
const string kHighlightColor = "Red";     /* Color of chosen path/nodes   */
const string kDimColor = "Gray";          /* Color of unchosen path/nodes */
const string kLabelFont = "Helvetica-10"; /* Font for node labels         */

/**
 * Function: initPathfinderGraphics
 * Usage: initPathfinderGraphics();
 * --------------------------------
 * Initializes the graphics window for Pathfinder.  This call should
 * be the first statement in main.
 */
void initPathfinderGraphics(GWindow & gw);

/**
 * Function: drawPathfinderMap
 * Usage: drawPathfinderMap(mapFile);
 * ----------------------------------
 * Clears the graphics window and then draws the image contained in
 * the specified image file, which will typically live in an images
 * subdirectory of the project directory.
 */
void drawPathfinderMap(const string& mapFile);

/**
 * Function: drawPathfinderNode
 * Usage: drawPathfinderNode(center, color, label);
 * ------------------------------------------------
 * Draw a node circle whose center is at the coordinate position
 * specified by the first argument and that is filled in the specified
 * color.  If a third argument is provided, the function draws a label
 * to the right of the circle containing the specified text.
 */
void drawPathfinderNode(const GPoint& center, const string& color, const string& label = "");

/**
 * Function: drawPathfinderArc
 * Usage: drawPathfinderArc(start, end, color);
 * --------------------------------------------
 * Draws a line on the screen connecting the two specified coordinate
 * positions using the indicated color.
 */
void drawPathfinderArc(const GPoint& start, const GPoint& end, const string& color);

/**
 * Function: addButton
 * Usage: addButton(name, actionFn);
 *        addButton(name, actionFn, data);
 * ---------------------------------------
 * Adds a button to the window and assigns it an action function.
 * When the button is clicked, the program will invoke
 *
 *       actionFn()
 * or
 *       actionFn(data)
 *
 * depending on whether the data parameter is supplied.  The data
 * parameter is passed by reference, so that the action function
 * can modify the program state.
 */
void addButton(const string& name, void (*actionFn)());

template <typename ClientType>
void addButton(const string& name, void (*actionFn)(ClientType& data), ClientType& data);

/**
 * Function: defineClickListener
 * Usage: defineClickListener(clickFn);
 *        defineClickListener(clickFn, data);
 * ------------------------------------------
 * Designates a function that will be called whenever the user
 * clicks the mouse in the graphics window.  If a click listener
 * has been specified by the program, the event loop will invoke
 *
 *       clickFn(pt)
 *
 * or
 *
 *       clickFn(pt, data)
 *
 * depending on whether the data parameter is supplied.  In either
 * case, pt is the GPoint at which the click occurred and data
 * is a parameter of any type appropriate to the application.  The
 * data parameter is passed by reference, so that the click function
 * can modify the program state.
 */
void defineClickListener(void (*actionFn)(const GPoint& pt));

template <typename ClientType>
void defineClickListener(void (*actionFn)(const GPoint& pt, ClientType & data), ClientType & data);

/**
 * Function: pathfinderEventLoop
 * Usage: pathfinderEventLoop();
 * -----------------------------
 * Initiates a loop that repeatedly waits for the user to click
 * on a button and calls the action function associated with that
 * button.  Moreover, if the client has registered a click listener,
 * pathfinderEventLoop will call that listener whenever the mouse is
 * clicked inside the window.
 *
 * Note that pathfinderEventLoop never returns, so programs that need
 * to exit on user command need to call the exit() function in the
 * standard libraries.
 */
void pathfinderEventLoop();

/**
 * Function: getMouseClick
 * Usage: pt = getMouseClick();
 * ----------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */

GPoint getMouseClick();

#include "pathfinder-graphics-impl.h"

#endif
