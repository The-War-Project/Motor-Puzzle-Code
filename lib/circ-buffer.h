#ifndef __CIRC_BUFFER_H__
#define	__CIRC_BUFFER_H__

#include <Arduino.h>

#define MAX_BUF_SIZE 128

typedef enum circBufferStatuses{
	CB_SUCCESS,
	CB_EMPTY,
	CB_NOT_INITIALIZED,
	CB_NOT_NULL,
	CB_ARG_NULL,
	CB_ERROR
} CircBufferStatus_t;

class CircBuffer{
	public:
		CircBuffer(void);
		CircBufferStatus_t init(uint8_t length);
		void reset(void);
		bool isEmpty(void);
		uint8_t getFill();
		CircBufferStatus_t put(float data);
		CircBufferStatus_t get(float * data);
		float getSum(void);
		float getAverage(void);
	
	private:
		float * buffer;
		uint8_t head;
		uint8_t tail;
		uint8_t length;
		uint8_t fill;
		float avg;
		float sum;
};

#endif	/* __CIRC_BUFFER_H__ */

