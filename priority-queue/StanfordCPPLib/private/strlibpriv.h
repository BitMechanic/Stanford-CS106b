/*
 * File: strlibpriv.h
 * ------------------
 * This file defines the functions in strlib.h that are used only
 * internally within the StanfordCPPLib package.
 */

/*
 * Function: readQuotedString
 * Usage: readQuotedString(infile, str);
 * -------------------------------------
 * Reads the next string from infile into the reference parameter str.
 * If the first character (other than whitespace) is either a single
 * or a double quote, this function reads characters up to the
 * matching quote, processing standard escape sequences as it goes.
 * If not, readString reads characters up to any of the characters
 * in the string STRING_DELIMITERS in the implementation file.
 * The readQuotedString function returns the stream.
 */

std::istream & readQuotedString(std::istream & is, std::string & str);

/*
 * Function: writeQuotedString
 * Usage: writeQuotedString(outfile, str);
 * ---------------------------------------
 * Writes the string str to outfile surrounded by double quotes,
 * converting special characters to escape sequences, as necessary.
 * The writeQuotedString function returns the stream.
 */

std::ostream & writeQuotedString(std::ostream & os, const std::string & str);
