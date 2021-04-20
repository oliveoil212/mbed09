#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
// DigitalOut myled1(LED1);
// DigitalOut myled3(LED3);
BufferedSerial pc(USBTX, USBRX);
// void LEDControl(Arguments *in, Reply *out);
// RPCFunction rpcLED(&LEDControl, "blink");
void blinkControl(Arguments *in, Reply *out);
RPCFunction rpcBlink(&blinkControl, "blink");
double x, y;
void blinking(){
    char buffer[200], outbuf[256];
    char strings[20];
    int led1 = x;
    int led3 = y;
    // sprintf(strings, "/myled%d/write %d", led, on);
    // strcpy(buffer, strings);
    // RPC::call(buffer, outbuf);
    // if (1) {
    //     out->putData(buffer);
    // } else {
    //     out->putData("Failed to execute LED control.");
    // }
     while (1) {
        if(x == 1) {
            led1 = !led1;
            sprintf(strings, "/myled1/write %d", led1);
            strcpy(buffer, strings);
            RPC::call(buffer, outbuf);
        }
        if(y == 1) {
            led3 = !led3;
            sprintf(strings, "/myled3/write %d", led3);
            strcpy(buffer, strings);
            RPC::call(buffer, outbuf);
        }
        ThisThread::sleep_for(500ms);
        // led = 3;
        // on = 1;
        // sprintf(strings, "/myled%d/write %d", led, on);
        // strcpy(buffer, strings);
        // RPC::call(buffer, outbuf);
         
        // led = 3;
        // on = 0;
        // sprintf(strings, "/myled%d/write %d", led, on);
        // strcpy(buffer, strings);
        // RPC::call(buffer, outbuf);
        // led = 1;
        // on = 1;
        // sprintf(strings, "/myled%d/write %d", led, on);
        // strcpy(buffer, strings);
        // RPC::call(buffer, outbuf);
   
    }
    // int led_blue = 0;
    // int led_green = 0;
    // while(1){
    //     if(y == 1) {
    //         led_blue =! led_blue;
    //     } else {
    //         led_blue =  0;
    //     }
    //     if(x == 1) {
    //         led_green = !led_green;
    //     } else {
    //         led_green = 0;
    //     }
    //     myled1 = led_green;
    //     myled3 = led_blue;
    //     ThisThread::sleep_for(200ms);
    // }
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
    char strings[20];
    // sprintf(strings, "blink Green %d   Blue %d", x, y);
    strcpy(buffer, strings);
    if (1) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED control.");
    }
    // if(x == 1) strcat
}
// // Make sure the method takes in Arguments and Reply objects.
// void LEDControl (Arguments *in, Reply *out)   {
//     bool success = true;

//     // In this scenario, when using RPC delimit the two arguments with a space.
//     x = in->getArg<double>();
//     y = in->getArg<double>();

//     // Have code here to call another RPC function to wake up specific led or close it.
//     char buffer[200], outbuf[256];
//     char strings[20];
//     int led1 = x;
//     int led3 = y;
//     // sprintf(strings, "/myled%d/write %d", led, on);
//     // strcpy(buffer, strings);
//     // RPC::call(buffer, outbuf);
//     if (success) {
//         out->putData(buffer);
//     } else {
//         out->putData("Failed to execute LED control.");
//     }
//      while (1) {
//         if(x == 1) {
//             led1 = !led1;
//             sprintf(strings, "/myled1/write %d", led1);
//             strcpy(buffer, strings);
//             RPC::call(buffer, outbuf);
//         }
//         if(y == 1) {
//             led3 = !led3;
//             sprintf(strings, "/myled3/write %d", led3);
//             strcpy(buffer, strings);
//             RPC::call(buffer, outbuf);
//         }
//         ThisThread::sleep_for(500ms);
//         // led = 3;
//         // on = 1;
//         // sprintf(strings, "/myled%d/write %d", led, on);
//         // strcpy(buffer, strings);
//         // RPC::call(buffer, outbuf);
         
//         // led = 3;
//         // on = 0;
//         // sprintf(strings, "/myled%d/write %d", led, on);
//         // strcpy(buffer, strings);
//         // RPC::call(buffer, outbuf);
//         // led = 1;
//         // on = 1;
//         // sprintf(strings, "/myled%d/write %d", led, on);
//         // strcpy(buffer, strings);
//         // RPC::call(buffer, outbuf);
   
//     }
// }