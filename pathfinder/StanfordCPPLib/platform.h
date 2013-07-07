/*
 * File: platform.h
 * ----------------
 * This interface defines the Platform class, which encapsulates the
 * platform-specific parts of the graphics package.  It is implemented
 * separately on each platform.  The class is used to create a singleton
 * object that is used to invoke all of the platform-specific code.
 */

#ifndef _platform_h
#define _platform_h

#include "gwindow.h"
#include "sound.h"

class Platform {
private:
   Platform();
   friend Platform *getPlatform();

public:
   ~Platform();
   void createGWindow(GWindow *gw, double width, double height,
                      GObject *topCompound);
   void deleteGWindow(GWindow *gw);
   void close(GWindow *gw);
   void requestFocus(GWindow *gw);
   void clear(GWindow *gw);
   void repaint(GWindow *gw);
   void setVisible(GWindow *gw, bool flag);
   void setResizable(GWindow *gw, bool flag);
   void setWindowTitle(GWindow *gw, std::string title);
   void pause(double milliseconds);
   double getScreenWidth();
   double getScreenHeight();
   bool getNextEvent(GEvent & e);
   void waitForEvent(GEvent & e);
   void waitForClick(GEvent & e);
   void exitGraphics();
   void createTimer(GTimer *timer, double delay);
   void deleteTimer(GTimer *timer);
   void startTimer(GTimer *timer);
   void stopTimer(GTimer *timer);
   void createSound(Sound *sound, std::string filename);
   void deleteSound(Sound *sound);
   void playSound(Sound *sound);
   void startSound(Sound *sound);
   void stopSound(Sound *sound);
   void createGRect(GObject *gobj, double width, double height);
   void createGRoundRect(GObject *gobj, double width, double height,
                                        double corner);
   void createG3DRect(GObject *gobj, double width, double height, bool raised);
   void createGOval(GObject *gobj, double width, double height);
   void createGArc(GObject *gobj, double width, double height,
                                  double start, double sweep);
   void setStartAngle(GObject *gobj, double angle);
   void setSweepAngle(GObject *gobj, double angle);
   void createGLine(GObject *gobj, double x1, double y1, double x2, double y2);
   void setStartPoint(GObject *gobj, double x, double y);
   void setEndPoint(GObject *gobj, double x, double y);
   void createGLabel(GObject *gobj, std::string label);
   GDimension createGImage(GObject *gobj, std::string filename);
   void createGPolygon(GObject *gobj);
   void addVertex(GObject *gobj, double x, double y);
   void createGButton(GObject *gobj, std::string label);
   void createGCompound(GObject *gobj);
   void deleteGObject(GObject *gobj);
   void add(GObject *compound, GObject *gobj);
   void remove(GObject *compound);
   void sendForward(GObject *gobj);
   void sendToFront(GObject *gobj);
   void sendBackward(GObject *gobj);
   void sendToBack(GObject *gobj);
   void setVisible(GObject *gobj, bool flag);
   void setColor(GObject *gobj, std::string color);
   void setLocation(GObject *gobj, double x, double y);
   void setSize(GObject *gobj, double width, double height);
   void setFrameRectangle(GObject *gobj, double x, double y,
                                         double width, double height);
   void draw(GWindow *gw, const GObject *gobj);
   void setFilled(GObject *gobj, bool flag);
   void setFillColor(GObject *gobj, std::string color);
   void setFont(GObject *gobj, std::string font);
   void setLabel(GObject *gobj, std::string str);
   double getFontAscent(const GObject *gobj);
   double getFontDescent(const GObject *gobj);
   GRectangle getGLabelBounds(const GObject *gobj);

};

Platform *getPlatform();

#endif
