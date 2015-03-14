/*
 * DataSizes.h
 *
 *  Created on: Mar 2, 2015
 *      Author: gledford
 */

#ifndef DATASIZES_H_
#define DATASIZES_H_

class DataSizes {
public:
	static DataSizes* getInstance();
	void setPageLength(const int pageLength);
	int getPageLength();
	void setPhysicalMemorySize(const int physicalMemorySize);
	int getPhysicalMemorySize();
	void setNumberOfPages(const int numberOfPages);
	int getNumberOfPages();
	void setTlbSize(const int tlbSize);
	int getTlbSize();

private:
	DataSizes();
	virtual ~DataSizes();

	static DataSizes* m_instance;

	int m_pageLength;
	int m_physicalMemorySize;
	int m_numberOfPages;
	int m_tlbSize;
};

#endif /* DATASIZES_H_ */
