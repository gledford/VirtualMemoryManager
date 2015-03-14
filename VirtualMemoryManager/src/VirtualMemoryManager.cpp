/*
 * VirtualMemoryManager.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 */

#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include "DiskReader.h"
#include "PhysicalMemory.h"
#include "PageTable.h"
#include "TranslationLookasideBuffer.h"
#include "DataSizes.h"
#include "Statistics.h"
#include "Swap.h"

int main(int argc, char * const argv[]) {
	//Masks for bit shifting
	static const unsigned int pageNumMask = 0xFF00;
	static const unsigned int offsetMask = 0x00FF;

	DiskReader *diskReader = 0;
	PhysicalMemory *physicalMemory = 0;
	PageTable *pageTable = 0;
	TranslationLookasideBuffer *tlb = 0;
	Swap *swap = 0;
	Statistics *statistics = 0;

	bool dirtyBitSetting = false;

	//If we have input arguments
	if (argc >= 3) {
		//Set all of the constant values
		DataSizes::getInstance()->setNumberOfPages(256);
		DataSizes::getInstance()->setPageLength(256);
		DataSizes::getInstance()->setTlbSize(16);

		//If input indicates to run the smaller physical memory
		if (strcmp(argv[2], "-128") == 0)
			DataSizes::getInstance()->setPhysicalMemorySize(128);
		else if (strcmp(argv[2], "-256") == 0)
			DataSizes::getInstance()->setPhysicalMemorySize(256);
		else {
			printf("Usage - ./main FILENAME -256 | -128\n");
			return 0;
		}

		if (argv[3] != 0) {
			if (strcmp(argv[3], "-copyback") == 0)
				dirtyBitSetting = true;
		}

		statistics = new Statistics();

		swap = new Swap();

		pageTable = new PageTable(DataSizes::getInstance()->getNumberOfPages());

		physicalMemory = new PhysicalMemory(
				DataSizes::getInstance()->getPhysicalMemorySize(), *statistics,
				*swap, *pageTable);

		tlb = new TranslationLookasideBuffer(*swap);

		diskReader = new DiskReader(*pageTable, *physicalMemory);

		//Read argv[1] as the file name
		std::ifstream inputFile(argv[1]);

		//If the file doesn't exists or isn't value, terminate
		if (!inputFile.good()) {
			printf("Invalid input file: %s\n", argv[1]);
			return 0;
		}

		std::string inputLine;

		//Get file, line by line
		while (std::getline(inputFile, inputLine)) {
			char action = 'R';

			//Tokenize the address line to check for "r" or "w"
			char *addressCopy = strdup(inputLine.c_str());
			char *addressToken = strtok(addressCopy, " ");
			char *actionToken = strtok(0, " ");

			if (0 != actionToken) {
				if (actionToken[0] == 'W')
					action = 'W';
			}

			statistics->incrementNumberOfVirtualAddressesRead();
			statistics->incrementNumberOfPagesRead();

			int addressAsInt = atoi(addressToken);

			printf("Virtual address: %d ", addressAsInt);
			fflush(stdout);

			//Bit mask to get offset and page number
			int offset = (addressAsInt & offsetMask);
			int pageNumber = (addressAsInt & pageNumMask) >> 8;

			int frameNumber = 0;

			//Check if Page is in TLB first
			if (tlb->isPageActive(pageNumber)) {
				statistics->incrementTlbHit();
				frameNumber = tlb->getFrameNumber(pageNumber, action);
			}
			//Check if Page is loaded in the Page Table
			else if (pageTable->isPageActive(pageNumber)) {
				frameNumber = pageTable->getFrameNumber(pageNumber);
				tlb->addNew(pageNumber, frameNumber, action);
			}
			//Else not in TLB nor in Page table, load to main memory
			else {
				statistics->incrementPageFaults();
				frameNumber = diskReader->readPageFromDisk(pageNumber, action);
				tlb->addNew(pageNumber, frameNumber, action);
			}

			printf("Physical address: %u ",
					((DataSizes::getInstance()->getPageLength() * frameNumber)
							+ offset));
			fflush(stdout);

			Page currentPage = physicalMemory->getPageAtFrame(frameNumber);
			printf("Value: %d\n", (signed char) currentPage.data[offset]);
			fflush(stdout);

			//Add the page to the TLB
			tlb->addNew(pageNumber, frameNumber, action);

		}

		printf("Number of Translated Addresses = %d\n",
				statistics->getNumberOfVirtualAddressesRead());
		printf("Number of Page Faults = %d\n",
				statistics->getNumberOfPageFaults());
		printf("Page Fault Rate = %.2f%% \n", statistics->getPageFaultRate());
		printf("Number of TLB hits = %d\n", statistics->getNumberOfTblHits());
		printf("TLB Hit Rate = %.2f%% \n", statistics->getTlbHitRate());

		if (dirtyBitSetting)
			printf("Number of Writes Back to Memory (Swaps) = %d\n",
					swap->getSizeOfSwap());

		fflush(stdout);
	} else {
		printf("Usage - ./main FILENAME -256 | -128\n");
	}

	return 0;
}
