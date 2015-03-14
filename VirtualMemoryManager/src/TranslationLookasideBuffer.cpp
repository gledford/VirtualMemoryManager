/*
 * TranslationLookasideBuffer.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 *
 *      This class is the TLB for the Virtual Memory Manager.
 *      It uses the LRU algorithm to remove items and add others items.
 */

#include <algorithm>
#include "TranslationLookasideBuffer.h"
#include "DataSizes.h"
#include "Swap.h"

TranslationLookasideBuffer::TranslationLookasideBuffer(Swap &swap)
: m_currentSize(0),
  m_indexOfPages(new int[DataSizes::getInstance()->getNumberOfPages()]),
  m_actions(new char[DataSizes::getInstance()->getNumberOfPages()]),
  m_swap(swap){

	for (int i = 0; i < DataSizes::getInstance()->getNumberOfPages(); i++)
	{
		m_indexOfPages[i] = -1; //initialize the index to -1 to indicate not active
		m_actions[i] = 'R'; //default all actions to read
	}

}

TranslationLookasideBuffer::~TranslationLookasideBuffer() {
	delete [] m_indexOfPages;
	m_indexOfPages = 0;
}

void TranslationLookasideBuffer::addNew(
		const int pageNumber, const int frameNumber, const char action) {
	std::pair<int, int> newPair;
	newPair = std::make_pair(pageNumber, frameNumber);

	if (isPageActive(pageNumber))
	{
		//If the page is already in the tlb, remove it
		std::vector<std::pair<int, int> >::iterator it;
		it = std::find(m_pagesToFrames.begin(), m_pagesToFrames.end(), newPair);

		if (it != m_pagesToFrames.end())
		{
			m_indexOfPages[(*it).first] = -1;
			m_pagesToFrames.erase(it);
			m_currentSize--;
		}
	}

	//If the table is already full, remove the LRU element
	if (m_currentSize == DataSizes::getInstance()->getTlbSize())
	{
		//LRU is the head of the vector
		if (m_actions[m_pagesToFrames.front().first] == 'W')
		{
			m_swap.addPageToSwap(m_pagesToFrames.front().first); //add page number of swap
			m_actions[m_pagesToFrames.front().first] = 'R';
		}
		m_indexOfPages[m_pagesToFrames.front().first] = -1;
		m_pagesToFrames.erase(m_pagesToFrames.begin());
		m_currentSize--;
	}

	//Add the pair to the back of the vector indicating most recently used
	m_pagesToFrames.push_back(newPair);

	m_currentSize++;

	//Add frame number to cross reference table
	m_indexOfPages[pageNumber] = frameNumber;
	m_actions[pageNumber] = action;
}

bool TranslationLookasideBuffer::isPageActive(const int pageNumber) {
	bool returnValue = false;

	if (pageNumber <= DataSizes::getInstance()->getNumberOfPages())
	{
		if (m_indexOfPages[pageNumber] != -1)
			returnValue = true;
	}

	return returnValue;
}

int TranslationLookasideBuffer::getFrameNumber(const int pageNumber, const char action) {
	int returnValue = -1;

	if (pageNumber <= DataSizes::getInstance()->getNumberOfPages())
	{
		if (isPageActive(pageNumber))
		{
			//Return the frame number
			returnValue = m_indexOfPages[pageNumber];

			std::pair<int, int> newPair;
			newPair = std::make_pair(pageNumber, returnValue);

			//If the page is already in the tlb,
			//move it to the end of the queue for LRU algorithm
			std::vector<std::pair<int, int> >::iterator it;
			it = std::find(m_pagesToFrames.begin(), m_pagesToFrames.end(), newPair);

			if (it != m_pagesToFrames.end())
			{
				m_pagesToFrames.erase(it);
				m_pagesToFrames.push_back(newPair);
			}
		}
	}

	return returnValue;
}
