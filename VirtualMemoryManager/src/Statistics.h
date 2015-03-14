/*
 * Statistics.h
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics {
public:
	Statistics();
	virtual ~Statistics();
	void incrementNumberOfVirtualAddressesRead();
	int getNumberOfVirtualAddressesRead();
	void incrementPageFaults();
	void incrementNumberOfPagesRead();
	double getPageFaultRate();
	int getNumberOfPageFaults();
	void incrementTlbHit();
	double getTlbHitRate();
	int getNumberOfTblHits();
	void incrementNumberOfPageReplacements();
	int getNumberOfPageReplacements();

private:
	int m_numberOfVirtualAddressesRead;
	int m_numberOfPageFaults;
	int m_numberOfPagesRead;
	int m_numberOfTlbHits;
	int m_numberOfPageReplacements;
};

#endif /* STATISTICS_H_ */
