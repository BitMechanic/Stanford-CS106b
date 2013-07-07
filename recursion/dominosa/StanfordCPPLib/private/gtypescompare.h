/*
 * File: gtypescompare.h
 * ---------------------
 * This file defines the comparison and hashCode functions for GPoint,
 * GDimension, and GRectangle.
 */

bool operator==(const GPoint & p1, const GPoint & p2);
bool operator!=(const GPoint & p1, const GPoint & p2);
bool operator<(const GPoint & p1, const GPoint & p2);
bool operator<=(const GPoint & p1, const GPoint & p2);
bool operator>(const GPoint & p1, const GPoint & p2);
bool operator>=(const GPoint & p1, const GPoint & p2);
int hashCode(const GPoint & pt);

bool operator==(const GDimension & d1, const GDimension & d2);
bool operator!=(const GDimension & d1, const GDimension & d2);
bool operator<(const GDimension & d1, const GDimension & d2);
bool operator<=(const GDimension & d1, const GDimension & d2);
bool operator>(const GDimension & d1, const GDimension & d2);
bool operator>=(const GDimension & d1, const GDimension & d2);
int hashCode(const GDimension & dim);

bool operator==(const GRectangle & r1, const GRectangle & r2);
bool operator!=(const GRectangle & r1, const GRectangle & r2);
bool operator<(const GRectangle & r1, const GRectangle & r2);
bool operator<=(const GRectangle & r1, const GRectangle & r2);
bool operator>(const GRectangle & r1, const GRectangle & r2);
bool operator>=(const GRectangle & r1, const GRectangle & r2);
int hashCode(const GRectangle & r);
