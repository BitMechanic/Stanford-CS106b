/**
 * File: dominosa-graphics.h
 * -------------------------
 */

#ifndef _dominosa_display_
#define _dominosa_display_

#include "gwindow.h"
#include "grid.h"
#include "dominosa-types.h"

class DominosaDisplay : private GWindow {

public:
    
	DominosaDisplay();
	~DominosaDisplay();
	void drawBoard(const Grid<int>& board);
	void provisonallyPair(const coord& one, const coord& two);
	void certifyPairing(const coord& one, const coord& two);
	void vetoProvisionalPairing(const coord& one, const coord& two);
	void eraseProvisionalPairing(const coord& one, const coord& two);
	
private:
	void drawDominosaPair(coord one, coord two, const std::string& color);
	void drawBox(double ulx, double uly,
                 double width, double height, const std::string& color);
    void drawFilledBox(double ulx, double uly,
                       double width, double height,
                       const std::string& fill, const std::string& border);
    void drawCenteredNumber(int number, double cx, double cy, const std::string& color);
 
    Grid<int> board;
    double width;
    double height;
    double cellDimension;
    double boardulx;
    double boarduly;
};

#endif
