#include "mbed.h"
#include "TextLCD.h"
#include "mbed_rpc.h"
void doDisplay(Arguments *in, Reply *out);
void doLocate(Arguments *in, Reply *out);
RPCFunction rpcdisplay(&doDisplay, "doDisplay");
RPCFunction rpclocate(&doLocate, "doLocate");
BufferedSerial pc(USBTX, USBRX);

// I2C Communication
I2C i2c_lcd(D14,D15); // SDA, SCL

TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2);  // I2C bus, PCF8574 Slaveaddress, LCD Type

int main() {
   lcd.setCursor(TextLCD::CurOff_BlkOn);
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

void doDisplay(Arguments *in, Reply *out) {
   const char *tmp = in->getArg<const char*>();
   printf("[str arg]%s", tmp);
   for(int i = 0; tmp[i] != 0; i++) {
      lcd.putc(tmp[i]);
   }
}

void doLocate(Arguments *in, Reply *out) {
   int x = in->getArg<int>();
   int y = in->getArg<int>();
   lcd.locate(x,y);
   printf("locate (col,row)=(%d,%d)", x, y);
}