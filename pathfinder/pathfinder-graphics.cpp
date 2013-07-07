/**
 * File: pathfinder-graphics.cpp
 * -----------------------------
 * The pathfinder-graphics.cpp file implements a set of functions that help draw the
 * necessary parts of the Pathfinder maps.
 */

#include <iostream>
#include <string>
#include "gevents.h"
#include "gobjects.h"
#include "pathfinder-graphics.h"
#include "gwindow.h"
#include "point.h"
using namespace std;

/* Constants */

const string kControlStripColor = "#E5E5E5";
const double kButtonWidth = 90;
const double kButtonHeight = 29;
const double kButtonSeparation = 6;
const double kStartupDelay = 50;

/* Class for buttons */

class ActionButton : public GButton {
public:
   ActionButton(const string& label, ButtonFunction *fn) : GButton(label) {
      this->fn = fn;
   }

   void execute() {
      fn->execute();
   }

private:
   ButtonFunction *fn;
};

/* Global data */

static GWindow *gwp;
static ClickFunction *clickHook = NULL;
static double nextButtonX = kButtonSeparation;

/* Prototypes */

void drawCircle(double x, double y, double r);
void fillCircle(double x, double y, double r);

/* Exported functions */

void initPathfinderGraphics(GWindow& gw) {
   gwp = &gw;
   GRect strip(0, kWindowHeight, kWindowWidth, kControlStripHeight);
   strip.setColor(kControlStripColor);
   strip.setFilled(true);
   gwp->draw(strip);
   gwp->setWindowTitle("Pathfinder");
   pause(kStartupDelay);
}

void drawPathfinderMap(const string& mapFile) {
   gwp->setColor("WHITE");
   gwp->fillRect(0, 0, kWindowWidth, kWindowHeight);
   gwp->setColor("BLACK");
   if (mapFile != "") {
      GImage map(mapFile);
      gwp->draw(map);
   }
}

void drawPathfinderNode(const GPoint& center, const string& color, const string& str) {
   gwp->setColor(color);
   fillCircle(center.getX(), center.getY(), kNodeRadius);
   if (!str.empty()) {
      GLabel label(str);
      label.setFont(kLabelFont);
      label.setLocation(center.getX() + kNodeRadius + 2, center.getY() + 5);
      gwp->draw(label);
   }
}

void drawPathfinderArc(const GPoint& start, const GPoint& end, const string& color) {
   gwp->setColor(color);
   gwp->drawLine(start.getX(), start.getY(), end.getX(), end.getY());
}

/*
 * Implementation notes: addButton
 * -------------------------------
 * This function creates a button and adds it to the vector of buttons
 * at the next available position in the control strip.
 */

void addButton(const string& name, void (*actionFn)()) {
   addButton(name, new ButtonFunctionWithoutData(actionFn));
}

void addButton(const string& name, ButtonFunction *fn) {
   double x = nextButtonX;
   double y = kWindowHeight + (kControlStripHeight - kButtonHeight) / 2;
   ActionButton *button = new ActionButton(name, fn);
   button->setBounds(x, y, kButtonWidth, kButtonHeight);
   gwp->add(button);
   nextButtonX += kButtonWidth + kButtonSeparation;
}

/*
 * Implementation notes: defineClickListener
 * -----------------------------------------
 * This function designates a listener for mouse clicks in the window.
 */

void defineClickListener(void (*clickFn)(const GPoint& pt)) {
   defineClickListener(new ClickFunctionWithoutData(clickFn));
}

void defineClickListener(ClickFunction *callback) {
   clickHook = callback;
}

void pathfinderEventLoop() {
   while (true) {
      GEvent e;
      waitForClick(e);
      if (e.getEventClass() == ACTION_EVENT) {
         ActionButton *bp = (ActionButton *) ((GActionEvent) e).getSource();
         bp->execute();
      } else if (e.getEventClass() == MOUSE_EVENT && clickHook != NULL) {
         GMouseEvent me = (GMouseEvent) e;
         if (me.getEventType() == MOUSE_CLICKED) {
            clickHook->execute(GPoint(me.getX(), me.getY()));
         }
      }
   }
}

/*
 * Implementation notes: getMouseClick
 * -----------------------------------
 * getMouseClick waits for the mouse button to go down and then up again,
 * at which point the function returns the mouse position at the time of
 * release.
 */

GPoint getMouseClick() {
   GMouseEvent e;
   waitForClick(e);
   return GPoint(e.getX(), e.getY());
}

/* Helper functions */

/*
 * Implementation notes: drawCircle, fillCircle
 * --------------------------------------------
 * These functions are useful tools that draw an outlined and a filled
 * circle, respectively.  If you are extending the Pathfinder assignment,
 * you might well want to export these methods through the gpathfinder.h
 * interface.
 */

void drawCircle(double x, double y, double r) {
   gwp->drawOval(x - r, y - r, 2 * r, 2 * r);
}

void fillCircle(double x, double y, double r) {
   gwp->fillOval(x - r, y - r, 2 * r, 2 * r);
}

/*
 * Implementation notes: Implementation of the callback classes
 * ------------------------------------------------------------
 * The remaining functions in this file support the implementation
 * of the various callback classes.
 */

ButtonFunctionWithoutData::ButtonFunctionWithoutData(void (*fn)()) {
   this->fn = fn;
}

void ButtonFunctionWithoutData::execute() {
   fn();
}

ClickFunctionWithoutData::ClickFunctionWithoutData(void (*fn)(const GPoint&)) {
   this->fn = fn;
}

void ClickFunctionWithoutData::execute(const GPoint& pt) {
   fn(pt);
}
