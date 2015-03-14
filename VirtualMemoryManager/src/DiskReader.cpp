/*
 * DiskReader.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: Garry Ledford
 *
 *      This class is responsible for reading the binary file and getting
 *      pages from the binary file.
 */

#include "DiskReader.h"
#include "DataSizes.h"
#include "PageTable.h"
#include "PhysicalMemory.h"

DiskReader::DiskReader(PageTable &pageTable, PhysicalMemory &physicalMemory)
: m_pageTable(pageTable),
  m_physicalMemory(physicalMemory){
}

DiskReader::~DiskReader() {
}

int DiskReader::readPageFromDisk(const int pageNumber, const char action) {
	int frameNumber = 0;
	Page page;
	FILE *memoryFile = fopen("assets/BACKING_STORE.bin", "rb");

	if (memoryFile != NULL)
	{
		//seek to the page number X the size of a page
		fseek(memoryFile, pageNumber * DataSizes::getInstance()->getPageLength(), SEEK_SET);

		//read in a buffer of the size of a page
		fread(page.data, DataSizes::getInstance()->getPageLength(), 1, memoryFile);

		page.pageNumber = pageNumber;

		//add the new page to the physical memory
		frameNumber = m_physicalMemory.addPage(page, action, pageNumber);

		//add the new page and frame pair to the page table
		m_pageTable.setPageFramePair(pageNumber, frameNumber);
	}

	fclose(memoryFile);

	return frameNumber;
}
