/*
 * File: gdimensionpriv.h
 * ----------------------
 * This file contains the private section of the GDimension class.  This
 * information is stored in a separate file to ensure that the client
 * doesn't see this information when reading the interface.
 */

private:

/* Instance variables */

   double width;                   /* The width of the GDimension       */
   double height;                  /* The height of the GDimension      */

/* Friend declarations */

friend bool operator==(const GDimension & d1, const GDimension & d2);
friend bool operator!=(const GDimension & d1, const GDimension & d2);
friend bool operator<(const GDimension & d1, const GDimension & d2);
friend bool operator<=(const GDimension & d1, const GDimension & d2);
friend bool operator>(const GDimension & d1, const GDimension & d2);
friend bool operator>=(const GDimension & d1, const GDimension & d2);
friend int hashCode(const GDimension & dim);
