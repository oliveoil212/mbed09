#include "mbed.h"
#include "mbed_rpc.h"
#include "stm32l475e_iot01_accelero.h"
BufferedSerial pc(USBTX, USBRX);
void getAcc(Arguments *in, Reply *out);

RPCFunction rpcAcc(&getAcc, "getAcc");

int main() {
   // Enable the the accelerometer
   printf("Start accelerometer init\n");
   BSP_ACCELERO_Init();

   char buf[256], outbuf[256];

   FILE *devin = fdopen(&pc, "r");
   FILE *devout = fdopen(&pc, "w");

   while (true) {
      memset(buf, 0, 256);      // clear buffer
      for(int i=0; i<255; i++) {
         char recv = fgetc(devin);
         if (recv == '\r' || recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
      RPC::call(buf, outbuf);
      printf("%s\r\n", outbuf);
   }
}

void getAcc(Arguments *in, Reply *out) {
   int16_t pDataXYZ[3] = {0};
        char buffer[200];
   BSP_ACCELERO_AccGetXYZ(pDataXYZ);
   sprintf(buffer, "Accelerometer values: (%d, %d, %d)", pDataXYZ[0], pDataXYZ[1], pDataXYZ[2]);
   out->putData(buffer);
}