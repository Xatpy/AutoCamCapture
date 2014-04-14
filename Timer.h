#pragma once

#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer 
{
	private:
		unsigned long begTime;

	public:
		void start() {
			begTime = clock();
		}

		unsigned long elapsedTime() {
			return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
		}

		bool isTimeout(unsigned long seconds) {
			return seconds <= elapsedTime();
		}
};

#endif