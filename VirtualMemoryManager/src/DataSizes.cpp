/*
 * DataSizes.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: gledford
 */

#include "DataSizes.h"

DataSizes* DataSizes::m_instance = 0;

DataSizes* DataSizes::getInstance() {
	if (!m_instance)
		m_instance = new DataSizes();

	return m_instance;
}

DataSizes::DataSizes()
: m_pageLength(0),
  m_physicalMemorySize(0),
  m_numberOfPages(0),
  m_tlbSize(0){

}

DataSizes::~DataSizes() {
}

void DataSizes::setPageLength(const int pageLength) {
	m_pageLength = pageLength;
}

int DataSizes::getPageLength() {
	return m_pageLength;
}

void DataSizes::setPhysicalMemorySize(const int physicalMemorySize) {
	m_physicalMemorySize = physicalMemorySize;
}

int DataSizes::getPhysicalMemorySize() {
	return m_physicalMemorySize;
}

void DataSizes::setNumberOfPages(const int numberOfPages) {
	m_numberOfPages = numberOfPages;
}

int DataSizes::getNumberOfPages() {
	return m_numberOfPages;
}

void DataSizes::setTlbSize(const int tlbSize) {
	m_tlbSize = tlbSize;
}

int DataSizes::getTlbSize() {
	return m_tlbSize;
}
