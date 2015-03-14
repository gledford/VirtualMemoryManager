/*
 * Statistics.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: Garry Ledford
 *
 *      This class hold the metrics for the Virtual Memory Manager
 */

#include "Statistics.h"

Statistics::Statistics()
: m_numberOfVirtualAddressesRead(0),
  m_numberOfPageFaults(0),
  m_numberOfPagesRead(0),
  m_numberOfTlbHits(0),
  m_numberOfPageReplacements(0){
}

Statistics::~Statistics() {
}

void Statistics::incrementNumberOfVirtualAddressesRead() {
	m_numberOfVirtualAddressesRead++;
}

int Statistics::getNumberOfVirtualAddressesRead() {
	return m_numberOfVirtualAddressesRead;
}

void Statistics::incrementPageFaults() {
	m_numberOfPageFaults++;
}

void Statistics::incrementNumberOfPagesRead() {
	m_numberOfPagesRead++;
}

double Statistics::getPageFaultRate() {
	return ((double)m_numberOfPageFaults / (double)m_numberOfPagesRead) * 100;
}

int Statistics::getNumberOfPageFaults() {
	return m_numberOfPageFaults;
}

void Statistics::incrementTlbHit() {
	m_numberOfTlbHits++;
}

double Statistics::getTlbHitRate() {
	return ((double)m_numberOfTlbHits / (double)m_numberOfPagesRead) * 100;
}

int Statistics::getNumberOfTblHits() {
	return m_numberOfTlbHits;
}

void Statistics::incrementNumberOfPageReplacements() {
	m_numberOfPageReplacements++;
}


int Statistics::getNumberOfPageReplacements() {
	return m_numberOfPageReplacements;
}
