/*
 * File: gwindowpriv.h
 * -------------------
 * This file contains the private section of the GWindow class.
 */

public:

   GWindow(bool visible);
   GWindow(double width, double height, bool visible);

   GWindow(int id) {
      this->id = id;
      color = "BLACK";
   }

   GRectangle getImageBounds(std::string filename);

   void pause(double milliseconds);

/*
 * Method: setPainter
 * Usage: gw.setPainter(painter);
 * ------------------------------
 * Sets a painter for this window, which is called each time the
 * screen is refreshed after painting the offscreen memory.  The
 * <code>painter</code> parameter is either a procedure that takes
 * a <code>GWindow</code> argument or an object that has a
 * <code>paint</code> method.
 */

   void setPainter(void (*painter)(GWindow & gw));
   template <typename Type>
   void setPainter(Type & painter);

private:
   int id;
   std::string color;
