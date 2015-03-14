/*
 * PageTable.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: gledford
 */

#include "PageTable.h"
#include <iostream>

PageTable::PageTable(const int maxPages) :
		m_maxPages(maxPages), m_pageToFrameXref(new int[maxPages]) {

	for (int i = 0; i < m_maxPages; i++) {
		m_pageToFrameXref[i] = -1; //initialize the index to -1 to indicate page not loaded
	}
}

PageTable::~PageTable() {
	delete m_pageToFrameXref;
	m_pageToFrameXref = 0;
}

void PageTable::setPageFramePair(const int pageNumber, const int frameNumber) {
	if (pageNumber < m_maxPages) {
		m_pageToFrameXref[pageNumber] = frameNumber;
	}
}

bool PageTable::isPageActive(const int pageNumber) {
	bool returnValue = false;

	if (pageNumber < m_maxPages) {
		if (m_pageToFrameXref[pageNumber] != -1) {
			returnValue = true;
		}
	}

	return returnValue;
}

int PageTable::getFrameNumber(const int pageNumber) {
	int returnValue = -1;

	if (isPageActive(pageNumber)) {
		returnValue = m_pageToFrameXref[pageNumber];
	}

	return returnValue;
}

void PageTable::resetFrameNumberForPage(const int pageNumber) {
	if (isPageActive(pageNumber)) {
		m_pageToFrameXref[pageNumber] = -1; //clear frame index
	}
}
