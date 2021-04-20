#include "mbed.h"
#include "mbed_rpc.h"

DigitalOut led1(LED1);
DigitalOut led3(LED3);
BufferedSerial pc(USBTX, USBRX);
void blinkControl(Arguments *in, Reply *out);
RPCFunction rpcBlink(&blinkControl, "blink");
double x, y;

void blinking(){
    char buffer[200], outbuf[256];
    char strings[20];
     while (1) {
        if(x == 1) {
            led1 = !led1;
        }
        if(y == 1) {
            led3 = !led3;
        }
        ThisThread::sleep_for(500ms);
    }
}
int main() {
    Thread blink_thread;
    blink_thread.start(blinking);
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class

    // receive commands, and send back the responses
    char buf[256], outbuf[256];

    FILE *devin = fdopen(&pc, "r");
    FILE *devout = fdopen(&pc, "w");

    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
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
void blinkControl(Arguments *in, Reply *out) {
    x = in->getArg<double>();
    y = in->getArg<double>();
    char buffer[200], outbuf[256];
    char strings[50];
    sprintf(strings, "Green %s Blue %s", (x==1)?"on":"off", (y==1)?"on":"off");
    strcpy(buffer, strings);
    if (1) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED control.");
    }
}
