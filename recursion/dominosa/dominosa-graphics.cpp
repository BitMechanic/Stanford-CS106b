/*
 *  gdominosa.cpp
 *  dominosa
 *
 *  Created by Jerry Cain on 1/22/11.
 *  Copyright 2011 Stanford University. All rights reserved.
 *
 */

#include "dominosa-graphics.h"

static const double kDominosaWindowWidth = 960;
static const double kDominosaWindowHeight = 360;
static const string kDominosaWindowTitle = "Dominosa";

static const string kWhite = "#ffffff";
static const string kProvisionalColor = "#b0c4de";
static const string kVetoedColor = "#ff6347";
static const string kCertifiedColor = "#32cd32";

static const int kShortDelay = 50;

DominosaDisplay::DominosaDisplay() : GWindow(kDominosaWindowWidth, kDominosaWindowHeight) {
    setWindowTitle(kDominosaWindowTitle);
    width = kDominosaWindowWidth;
    height = kDominosaWindowHeight;
    cellDimension = boardulx = boarduly = 0;
}

DominosaDisplay::~DominosaDisplay() {
    close();
}

static const double kWidthInset = 18;
static const double kCellPadding = 2;
static const double kFontSizeScale = 0.7;
void DominosaDisplay::drawBoard(const Grid<int>& board) {
    clear();
    this->board = board;
	cellDimension = (width - 2 * kWidthInset) / board.numCols();
	boardulx = (width - board.numCols() * cellDimension) / 2;
	boarduly = height/2 - cellDimension;
	setFont("Times-Bold-" + integerToString(kFontSizeScale * cellDimension));
	
	drawBox(boardulx, boarduly, width - 2 * kWidthInset, 2 * cellDimension, "Black");
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			double ulx = boardulx + col * cellDimension + kCellPadding;
			double uly = boarduly + row * cellDimension + kCellPadding;
			double side = cellDimension - 2 * kCellPadding;
			drawFilledBox(ulx, uly, side, side, "White", "Gray");
			drawCenteredNumber(board.get(row, col), ulx + side/2, uly + side/2, "Black");
		}
	}
}

void DominosaDisplay::provisonallyPair(const coord& one, const coord& two) {
	drawDominosaPair(one, two, kProvisionalColor);
	::pause(kShortDelay);
}

void DominosaDisplay::vetoProvisionalPairing(const coord& one, const coord& two) {
	drawDominosaPair(one, two, kVetoedColor);
	::pause(kShortDelay);
}

void DominosaDisplay::certifyPairing(const coord& one, const coord& two) {
	drawDominosaPair(one, two, kCertifiedColor);
	::pause(kShortDelay);
}

void DominosaDisplay::eraseProvisionalPairing(const coord& one, const coord& two) {
	drawDominosaPair(one, two, kWhite);
}

void DominosaDisplay::drawDominosaPair(coord one, coord two, const string& color) {
    if (two < one) swap(one, two);

	double oneulx = boardulx + one.col * cellDimension + kCellPadding;
	double oneuly = boarduly + one.row * cellDimension + kCellPadding;
	double twoulx = oneulx;
	double twouly = oneuly;
	
	double pairingllx = boardulx + one.col * cellDimension + 4 * kCellPadding;
	double pairinglly = boarduly + one.row * cellDimension + 4 * kCellPadding;
	double pairingWidth = cellDimension - 8 * kCellPadding;
	double pairingHeight = cellDimension - 8 * kCellPadding;

	if (one.col < two.col) {
		pairingWidth += cellDimension;
		twoulx += cellDimension;
	} else {
		pairingHeight += cellDimension;
		twouly += cellDimension;
	}
	
	drawFilledBox(pairingllx, pairinglly, pairingWidth, pairingHeight, color, color);
	double side = cellDimension - 2 * kCellPadding;
	drawBox(oneulx, oneuly, side, side, "Gray");
	drawBox(twoulx, twouly, side, side, "Gray");
	drawCenteredNumber(board[one.row][one.col], oneulx + side/2, oneuly + side/2, "Black");
	drawCenteredNumber(board[two.row][two.col], twoulx + side/2, twouly + side/2, "Black");
}

void DominosaDisplay::drawBox(double ulx, double uly,
                              double width, double height, const string& color) {
    setColor(color);
    drawRect(ulx, uly, width, height);
}

void DominosaDisplay::drawFilledBox(double ulx, double uly,
                                    double width, double height,
                                    const std::string& fill, const std::string& border) {
    setColor(fill);
    fillRect(ulx, uly, width, height);
    setColor(border);
    drawRect(ulx, uly, width, height);
}

void DominosaDisplay::drawCenteredNumber(int number, double cx, double cy, const string& color) {
    string str = integerToString(number);
    double ulx = cx - getStringWidth(str)/2;
    double uly = cy + getFontAscent()/2;
    setColor(color);
    drawString(str, ulx, uly);
}
