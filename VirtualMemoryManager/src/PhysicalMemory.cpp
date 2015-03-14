/*
 * PhysicalMemory.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 *
 *      This class acts as the physical memory for the Virtual Memory Manager.
 *      The class has a vector that acts like the stack LRU from Section 9.4.
 */

#include <algorithm>
#include "PhysicalMemory.h"
#include "DataSizes.h"
#include "Statistics.h"
#include "Swap.h"
#include "PageTable.h"
#include <iostream>

PhysicalMemory::PhysicalMemory(const int maxPages, Statistics &statistics,
		Swap &swap, PageTable &pageTable) :
		m_maxPages(maxPages), m_currentPageIndex(0), m_pages(
				new Page[DataSizes::getInstance()->getPhysicalMemorySize()]), m_dirtyBit(
				new int[DataSizes::getInstance()->getPhysicalMemorySize()]), m_statistics(
				statistics), m_swap(swap), m_pageTable(pageTable) {

	for (int i = 0; i < DataSizes::getInstance()->getPhysicalMemorySize();
			i++) {
		m_dirtyBit[i] = 'R'; //default all actions to read
	}
}

PhysicalMemory::~PhysicalMemory() {
}

int PhysicalMemory::addPage(const Page & newPage, const int action,
		const int pageNumber) {
	std::pair<Page, int> newPair;
	newPair.first = newPage;
	newPair.second = -1; //default value
	bool incrementCurrentPageIndex = false;

	int indexOfPage = m_currentPageIndex;

	//Check if page already exists in memory
	std::vector<std::pair<Page, int> >::iterator it;
	for (it = m_pageUsage.begin(); it != m_pageUsage.end(); it++) {
		//If the page already exists, save the old index
		if ((*it).first == newPage)
			newPair.second = (*it).second;
	}

	//If the main memory is full
	if ((int) m_pageUsage.size()
			== DataSizes::getInstance()->getPhysicalMemorySize()) {
		//Get index of least recently used so we can use that slot for the new page
		m_currentPageIndex = (*m_pageUsage.begin()).second;

		//If we had the dirty bit set
		if (m_dirtyBit[m_currentPageIndex] == 'W') {
			m_swap.addPageToSwap(pageNumber);
			m_dirtyBit[m_currentPageIndex] = 'R';
		}

		//Update the page table to reflect the removal from physical memory
		if (m_pageTable.isPageActive(m_pages[m_currentPageIndex].pageNumber))
			m_pageTable.resetFrameNumberForPage(m_pages[m_currentPageIndex].pageNumber);

		//Remove the first item in the vector
		m_pageUsage.erase(m_pageUsage.begin());

		m_statistics.incrementNumberOfPageReplacements();
	} else
		incrementCurrentPageIndex = true;

	//Save off the new page in the available frame slot
	m_pages[m_currentPageIndex] = newPage;
	m_dirtyBit[m_currentPageIndex] = action;

	indexOfPage = m_currentPageIndex;
	newPair.second = m_currentPageIndex;

	//If the page already exists, remove it
	if (it != m_pageUsage.end())
		m_pageUsage.erase(it);

	//Add the page to the back of the vector to indicate most recently used
	m_pageUsage.push_back(newPair);

	if (incrementCurrentPageIndex)
		m_currentPageIndex++;

	return indexOfPage;
}

Page PhysicalMemory::getPageAtFrame(const int frameNumber) {
	return m_pages[frameNumber];
}
