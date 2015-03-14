/*
 * PhysicalMemory.h
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 */

#ifndef PHYSICALMEMORY_H_
#define PHYSICALMEMORY_H_

#include "Page.h"
#include <vector>

class Statistics;
class Swap;
class PageTable;

class PhysicalMemory {
public:
	PhysicalMemory(const int maxPages, Statistics &statistics, Swap &swap, PageTable &pageTable);
	virtual ~PhysicalMemory();
	int addPage(const Page &newPage, const int action, const int pageNumber);
	Page getPageAtFrame(const int frameNumber);

private:
	int m_maxPages;
	int m_currentPageIndex;
	Page *m_pages;
	std::vector<std::pair<Page, int> > m_pageUsage;
	int *m_dirtyBit;
	Statistics &m_statistics;
	Swap &m_swap;
	PageTable &m_pageTable;
};

#endif /* PHYSICALMEMORY_H_ */
