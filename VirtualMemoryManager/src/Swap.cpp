/*
 * Swap.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: gledford
 */

#include "Swap.h"

Swap::Swap() {
}

Swap::~Swap() {
}

void Swap::addPageToSwap(const int pageNumber) {
	m_swapPages.push_back(pageNumber);
}

int Swap::getSizeOfSwap() {
	return m_swapPages.size();
}
