#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int readline(int fd, char *str);

int main(void)
{
   int fd;
   char str[100];

   mkfifo("/tmp/myfifo",0660);
   fd=open("/tmp/myfifo",O_RDONLY); //fd=open("/tmp/myfifo",O_RDWR);
   
   while(readline(fd,str))
      printf("%s",str);

   close(fd);
   return 0;
}

int readline(int fd, char *str)
{
   int n;
   do {
      n = read(fd,str,1);
   } while (n > 0 && *str++ != '\0');

   return (n > 0);
}

/*
   O processo leitor termina mal o processo escritor termina pois quando o terminal do fifo for fechado pelo escritor a chamada read devolve 0 (EOF).

   (explicação do prof)
   O comportamento é indefinido quando um FIFO é aberto em modo RD_WR. Porque os Fifos funcionam de forma a que um dos lado escreve e o outro lê (bloqueando). 
   Caso seja feito RD_WR, como o fifo vai estar em modo non-blocking, podes ter diferentes comportamentos. Um deles pode ser:
      -Abrindo o FIFO em modo de leitura e escrita, quando o escritor terminar o read não vai devolver (0) EOF porque o fifo ainda está aberto para escrita
      (pelo próprio reader)

*/