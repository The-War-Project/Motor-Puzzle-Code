#include "circ-buffer.h"

CircBuffer::CircBuffer(void){}

/* Initialize a circular buffer
 */
CircBufferStatus_t CircBuffer::init(uint8_t length){
	// check max length
	if(length > MAX_BUF_SIZE){
		return CB_ERROR;
	}
	
	// check if buffer has not yet been initalized
	if(this->buffer != NULL){
		return CB_NOT_NULL;
	}

	// allocate memory for the buffer
	this->buffer = (float*)malloc(sizeof(float)*length);
	if(this->buffer == NULL){
		return CB_NOT_INITIALIZED;
	}
	
	// initialize attributes
	this->length = length;
	this->head = 0;
	this->tail = 0;
	this->fill = 0;
	this->avg = 0;

	return CB_SUCCESS;
}

/* Reset the buffer
 */ 
void CircBuffer::reset(void){
	// re-init attributes (memory is not cleared)
	this->head = 0;
	this->tail = 0;
	this->fill = 0;
	this->avg = 0;
}

/* Returns true when the buffer is empty, and false otherwise.
 */
bool CircBuffer::isEmpty(void){
	// We define empty as head == tail
	return (this->head == this->tail);
}

/* Returns the number of values stored in the buffer.
 */
uint8_t CircBuffer::getFill(void){
	return this->fill;
}

/* Returns the sum of all the values stored in the buffer.
 */
float CircBuffer::getSum(void){
	return this->sum;
}

/* Returns the average of all the values stored in the buffer.
 */
float CircBuffer::getAverage(void){
	return this->avg;
}

/* Put a value in the buffer
 */
CircBufferStatus_t CircBuffer::put(float data){
	
	// check if buffer is initalized
	if(this->buffer != NULL){
		// store value at the head of the buffer
		this->buffer[this->head] = data;
		// move head
		this->head = (this->head + 1) % this->length;
		// increase number of elements
		this->fill++;
		// increase sum
		this->sum += data;
		// check if last byte has been overwritten (pushed out)
		if(this->head == this->tail){
			//decrease sum
			this->sum -= this->buffer[this->tail];
			// move tail
			this->tail = (this->tail + 1) % this->length;
			// correct fill
			this->fill = this->length;
		}
		//update average
		this->avg = this->sum/(this->fill-1);

		return CB_SUCCESS;
	}

	return CB_NOT_INITIALIZED;
}

/* Get a value from the buffer
 */
CircBufferStatus_t CircBuffer::get(float * data){
	// check for NULL pointer
	if(data == NULL){
		return CB_ARG_NULL;
	}
	// check if buffer is initalized
	if(this->buffer == NULL){
		return CB_NOT_INITIALIZED;
	}
	// check if buffer is empty
	if(!this->isEmpty()){
		// return last value in the buffer
		*data = this->buffer[this->tail];
		// move the tail
		this->tail = (this->tail + 1) % this->length;

		return CB_SUCCESS;
	}

	return CB_EMPTY;
}