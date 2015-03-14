/*
 * Swap.h
 *
 *  Created on: Mar 5, 2015
 *      Author: gledford
 */

#ifndef SWAP_H_
#define SWAP_H_

#include <vector>

class Swap {
public:
	Swap();
	virtual ~Swap();
	void addPageToSwap(const int pageNumber);
	int getSizeOfSwap();

private:
	std::vector<int> m_swapPages; //pages that need to be written back to the disk
};

#endif /* SWAP_H_ */
