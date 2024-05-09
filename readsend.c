#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define DEVICE "/dev/ttyUSB0"

int main(int argc, char *argv[]){
  struct termios old_tio, tio;
  
  int boardfd = open(DEVICE, O_RDWR);
  if (boardfd == -1) {
    perror("Error opening tty");
    exit(EXIT_FAILURE);
  }
  
  if (tcgetattr(boardfd, &old_tio) != 0) {
    perror("Error getting serial port attributes");
    return -1;
  }

  tio.c_cflag = B115200 | CREAD | CLOCAL | CS8;
  tio.c_lflag = 0;
  tio.c_iflag = 0;
  tio.c_oflag = 0;

  tcflush(boardfd, TCIFLUSH);
  if (tcsetattr(boardfd, TCSANOW, &tio) != 0) {
    perror("Error setting serial port attributes");
    return -1;
  }
    
  //Initialization of serial interface complete. Set arduino to B115200;

  FILE *datafile=fopen(argv[1],"r");
  if (datafile == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  
  char dataline[32];
  while(fgets(dataline, sizeof(dataline), datafile)!=NULL){
    write(boardfd, dataline, strlen(dataline));
  }


  tcflush(boardfd, TCIFLUSH);
  tcsetattr(boardfd, TCSANOW, &old_tio);

  // Close file and serial port
  fclose(datafile);
  close(boardfd);

  
  return 0;
}
