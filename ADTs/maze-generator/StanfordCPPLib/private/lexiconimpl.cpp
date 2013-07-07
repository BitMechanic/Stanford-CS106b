/*
 * File: lexiconimpl.cpp
 * ---------------------
 * This file contains the implementation of the lexicon.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _lexicon_h

template <typename FunctorType>
void Lexicon::mapAll(FunctorType fn) const {
   foreach (string word in *this) {
      fn(word);
   }
}

#endif
