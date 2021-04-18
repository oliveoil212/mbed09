#include "mbed.h"
#include "mbed_rpc.h"

/**
*  This example program has been updated to use the RPC implementation in the new mbed libraries.
*  This example demonstrates using RPC over serial
*/

//Use the RPC enabled wrapped class  - see RpcClasses.h for more info
RpcDigitalOut myled(LED1,"myled");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
BufferedSerial pc(USBTX, USBRX);

int main() {
   //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class
   // receive commands, and send back the responses
   char buf[256], outbuf[256];

   FILE *devin = fdopen(&pc, "r");
   FILE *devout = fdopen(&pc, "w");

   while(1) {
      memset(buf, 0, 256);      // clear buffer

      for(int i=0; ; i++) {
            char recv = fgetc(devin);
            if (recv == '\n') {
               printf("\r\n");
               break;
            }
            buf[i] = fputc(recv, devout);
      }
      //Call the static call method on the RPC class
      RPC::call(buf, outbuf);
      printf("%s\r\n", outbuf);
   }
}