/*
 * TranslationLookasideBuffer.h
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 */

#ifndef TRANSLATIONLOOKASIDEBUFFER_H_
#define TRANSLATIONLOOKASIDEBUFFER_H_

#include <utility>
#include <vector>

class Swap;

class TranslationLookasideBuffer {
public:
	TranslationLookasideBuffer(Swap &swap);
	virtual ~TranslationLookasideBuffer();
	void addNew(const int pageNumber, const int frameNumber, const char action);
	bool isPageActive(const int pageNumber);
	int getFrameNumber(const int pageNumber, const char action);

private:
	int m_currentSize;
	std::vector<std::pair<int, int> > m_pagesToFrames;
	int *m_indexOfPages;
	char *m_actions;
	Swap &m_swap;
};

#endif /* TRANSLATIONLOOKASIDEBUFFER_H_ */
