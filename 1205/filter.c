#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h> 
#include <limits.h> 
#include <sys/types.h> 
#include <sys/stat.h>

#include "wavFile.h" 

#define READSIZE 1024
#define THRESHOLD 128

typedef union data_type{ 
	unsigned char c_data[2];
	short s_data; 
} data_t;

static int writeWavHeader(int fd, int format, int mode, int freq, unsigned long size);

int main(int argc, char** argv)
{
	int fd1, fd2, i, j, k; 
	long count; 
	int channels, format; 
	wavHeader wavheader; 
	data_t buf[READSIZE], out[READSIZE];
	
	/* Initialize Header of Wave */ 
	memset(&wavheader, 0, sizeof(wavHeader));
	if(argc <= 2) { 
		printf("usage : %s input output speed_rate\n", argv[0]); 
		return -1;
	}
	
	if((fd1 = open(argv[1], O_RDONLY)) == -1) { 
		printf("Could not open wave file : %s\n", argv[1]); 
		return -1;
	}
	
	// Read Head of wave file 
	if(read(fd1, &wavheader, sizeof(wavHeader)) < 1) {
		printf("Could not read wave header\n"); return -1;
	}
	
	
	if((fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC)) == -1)
		return -1; 
	channels = wavheader.nChannels;
	printf("Channel : %s\n", (channels-1)? "Stereo":"Mono");
	printf("Wave Bytes : %d\n", wavheader.nblockAlign); 
	
	switch(wavheader.nblockAlign) {
		case 1: 
			format = 0x08; 
			break;
		case 2: 
			format = (channels-1)?0x10:0x08; 
			break;
		case 4: 
			printf("Stereo Wave file\n"); 
			format = 0x10; 
			break;
		default: 
			printf("Unknown byte rate for sound\n"); 
			break;
	};

	printf("Wave Sampling Rate : %ld\n", wavheader.sampleRate); 	
	if(writeWavHeader(fd2, format, channels, wavheader.sampleRate, wavheader.dataLen/2) != 0)
		return -1;

	do { 
		memset(buf, 0, sizeof(data_t)*READSIZE); 
		if((count = read(fd1, buf, READSIZE)) <= 0) 
			break;
	
		for(i = 0, j = 0; i < count; i+=2, j++) { 
			if(format == 0x08) {		
				out[j].c_data[k] = buf[i].c_data[0] - buf[i].c_data[1];			
				for(k = 0; k <= 1; k++) { 
//					out[j].c_data[k] = buf[i].c_data[k] - buf[i+1].c_data[k];			
					out[j].c_data[k] = (out[j].c_data[k]>=255)?255:(out[j].c_data[k]<=0)?0:out[j].c_data[k];
				}; 
			} else {	
				out[j].s_data = buf[i].s_data - buf[i+1].s_data; 
				out[j].s_data = (out[j].s_data>=SHRT_MAX)?SHRT_MAX:(out[j].s_data<=SHRT_MIN)?SHRT_MIN:out [j].s_data;
			}	
		}	
	
		if(write(fd2, out, count/2) == -1) {	
			return -1;
		}
	} while(count == READSIZE);

	close( fd1 );
	close( fd2 ); 
	
	return 0;
}

int writeWavHeader(int fd, int format, int mode, int freq, unsigned long size)
{
	wavHeader wavheader;
	
	memset(&wavheader, 0, sizeof(wavHeader));
	
	/* WAV Header */
	memcpy(wavheader.riffID, "RIFF", 4);
	wavheader.riffLen = 16L+11025L+20L;
	memcpy(wavheader.waveID, "WAVE", 4);
	memcpy(wavheader.fmtID, "fmt ", 4);
	
	wavheader.fmtLen = 16L;
	wavheader.fmtTag = 1; /* PCM */
	wavheader.nChannels = mode;
	wavheader.sampleRate = freq;
	wavheader.avgBytesPerSec = freq;
	
	if(format==AFMT_U8 && wavheader.nChannels==1)
		wavheader.nblockAlign = 1;
	else if((format==AFMT_U8 && wavheader.nChannels==2) \
			|| (format==AFMT_S16_LE && wavheader.nChannels==1))
		wavheader.nblockAlign = 2;
	else if(format==AFMT_S16_LE && wavheader.nChannels==2)
		wavheader.nblockAlign = 4;
	
	if(format == AFMT_U8)
		wavheader.bitsPerSample = 8;
	else if(format == AFMT_S16_LE)
		wavheader.bitsPerSample = 16;
	
	memcpy(wavheader.dataID, "data", 4);
	
	wavheader.dataLen = size;
	
	write(fd, &wavheader, sizeof(wavHeader));
	
	return 0;
}
