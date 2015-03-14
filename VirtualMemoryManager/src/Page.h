/*
 * Page.h
 *
 *  Created on: Mar 1, 2015
 *      Author: gledford
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <cstring>
#include "DataSizes.h"

struct Page
{
	Page()
	: data(new unsigned char[DataSizes::getInstance()->getPageLength()]),
	  pageNumber(0){
	}

	void initializePage(const int pageLength) {
		for (int i = 0; i < DataSizes::getInstance()->getPageLength(); i ++)
		{
			data[i] = 0;
		}
	}

	Page& operator=(const Page &inputPage)	{
		memcpy(data,
				inputPage.data,
				sizeof(unsigned char) * DataSizes::getInstance()->getPageLength());

		pageNumber = inputPage.pageNumber;

		return *this;
	}

	bool operator==(const Page &other) const {
		return(!memcmp(this, &other, sizeof(Page)));
	}

	unsigned char *data;
	int pageNumber;
};

#endif /* PAGE_H_ */
