/*
 * PageTable.h
 *
 *  Created on: Mar 2, 2015
 *      Author: gledford
 */

#ifndef PAGETABLE_H_
#define PAGETABLE_H_

class PageTable {
public:
	PageTable(const int maxPages);
	virtual ~PageTable();
	void setPageFramePair(const int pageNumber, const int frameNumber);
	bool isPageActive(const int pageNumber);
	int getFrameNumber(const int pageNumber);
	void resetFrameNumberForPage(const int pageNumber);

private:
	int m_maxPages;
	int *m_pageToFrameXref;
};

#endif /* PAGETABLE_H_ */
