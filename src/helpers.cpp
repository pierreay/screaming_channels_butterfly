#include "helpers.h"

uint32_t bytewise_bit_swap(uint32_t inp)
{
	inp = (inp & 0xF0F0F0F0) >> 4 | (inp & 0x0F0F0F0F) << 4;
	inp = (inp & 0xCCCCCCCC) >> 2 | (inp & 0x33333333) << 2;
	return (inp & 0xAAAAAAAA) >> 1 | (inp & 0x55555555) << 1;
}

void sort_array(uint32_t tab[], size_t size) {
	for (size_t i=size-1;i>0;i--) {
		for (size_t j=0;j<i;j++) {
			if (tab[j+1] < tab[j]) {
				uint32_t tmp = tab[j];
				tab[j] = tab[j+1];
				tab[j+1] = tmp;
			}
		}
	}
}

bool compareBuffers(uint8_t *buffer1, uint8_t *buffer2,size_t size) {
	for (size_t i=0;i<size;i++) {
		if (buffer1[i] != buffer2[i]) return false;
	}
	return true;
}



uint8_t dewhiten_byte_ble(uint8_t byte, int position, int channel) {
	int i,j;
	uint8_t c;
	uint8_t lfsr = bytewise_bit_swap(channel) | 2;
	for (i=0; i<position; i++) {
		for (j=7; j>=0; j--) {
		if (lfsr & 0x80) {
			lfsr ^= 0x11;
		}
		lfsr <<= 1;
		}
	}
	c = bytewise_bit_swap(byte);
	for (j=7; j>=0; j--) {
		if (lfsr & 0x80) {
			lfsr ^= 0x11;
			c ^= (1<<j);
		}
		lfsr <<= 1;
	}
	return bytewise_bit_swap(c);
}

void dewhiten_ble(uint8_t *data, int len, int channel){
	int i,j;
	uint8_t c;
	uint8_t lfsr = bytewise_bit_swap(channel) | 2;

	for (i=0; i<len; i++) {
		c = bytewise_bit_swap(data[i]);
		for (j=7; j>=0; j--) {
			if (lfsr & 0x80) {
				lfsr ^= 0x11;
				c ^= (1<<j);
			}
			lfsr <<= 1;
		}
		data[i] = bytewise_bit_swap(c);
	}
}

int hamming(uint8_t *demod_buffer,uint8_t *pattern) {
	int count = 0;
	for (int i=0;i<4;i++) {
		for (int j=0;j<8;j++) {
			if (((pattern[i] >> (7-j)) & 0x01) != (((demod_buffer[i] & (i==0 && j==0 ? 0x7F : 0xFF)) >> (7-j)) & 0x01)) {
				count++;
			}
		}
	}
	return count;
}

void shift_buffer(uint8_t *demod_buffer,int size) {
	for (int i=0;i<size;i++) {
		if (i != 0) {
			demod_buffer[i-1]=((demod_buffer[i] & 0x80) >> 7) | demod_buffer[i-1];
		}
		demod_buffer[i] = demod_buffer[i] << 1;
	}
}

uint16_t update_fcs_dot15d4(uint8_t byte, uint16_t fcs) {
	uint16_t q = (fcs ^ byte) & 15;
	fcs = (fcs / 16) ^ (q * 4225);
	q = (fcs ^ (byte / 16)) & 15;
	fcs = (fcs / 16) ^ (q * 4225);
	return fcs;
}

uint16_t calculate_fcs_dot15d4(uint8_t data[], int size) {
	uint16_t fcs = 0;
	for (int i=2; i<size-2;i++) {
		fcs = update_fcs_dot15d4(data[i],fcs);
	}
	return fcs;
}

bool check_fcs_dot15d4(uint8_t data[],int size) {
	uint16_t fcs = calculate_fcs_dot15d4(data,size);
	return ((fcs & 0xFF) == data[size-2]) && (((fcs >> 8) & 0xFF) == data[size-1]);
}

bool correct_size_dot15d4(uint8_t data[],int max) {
	int i=2;
	uint16_t fcs = 0;
	int correctSize = 0;
	while (i < max-2) {
		correctSize++;
		fcs = update_fcs_dot15d4(data[i],fcs);
		if (((fcs & 0xFF) == data[i+1]) && (((fcs >> 8) & 0xFF) == data[i+2])) {
			data[1] = correctSize+2;
			return true;
		}
		i++;
	}
	return false;
}


unsigned short calculate_crc_mosart(uint8_t *ptr, int count)
{
   uint16_t  crc;
   uint8_t i;
   crc = 0;
   while (--count >= 0)
   {
      crc = crc ^ (int) *ptr++ << 8;
      i = 8;
      do
      {
         if (crc & 0x8000)
            crc = crc << 1 ^ 0x1021;
         else
            crc = crc << 1;
      } while(--i);
   }
   return (crc);
}
