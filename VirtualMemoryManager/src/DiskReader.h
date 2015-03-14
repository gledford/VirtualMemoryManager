/*
 * DiskReader.h
 *
 *  Created on: Mar 4, 2015
 *      Author: Garry Ledford
 */

#ifndef DISKREADER_H_
#define DISKREADER_H_

class PageTable;
class PhysicalMemory;

class DiskReader {
public:
	DiskReader(PageTable &pageTable, PhysicalMemory &physicalMemory);
	virtual ~DiskReader();
	int readPageFromDisk(const int pageNumber, const char action);

private:
	PageTable &m_pageTable;
	PhysicalMemory &m_physicalMemory;
};

#endif /* DISKREADER_H_ */
