#include <pigpiod_if2.h>
#include <iostream>

const int LED = 5;

using namespace std;


int PigpioSetup()
{
   char *addrStr = NULL;
   char *portStr = NULL;
   //handshake with daemon and get pi handle
   int pi = pigpio_start(addrStr, portStr);

   //set the pin mode and intialize to low
   set_mode(pi, LED, PI_OUTPUT);
   gpio_write(pi, LED, 0);

   return pi;
}

int main()
{
   //initialize pipiod interface
   int pi = PigpioSetup();
   //check that handshake went ok
   if(pi>=0)
   {
      cout<<"daemon interface started ok at "<<pi<<endl;
   }
   else
   {
      cout<<"Failed to connect to PIGPIO Daemon - Try running sudo pigpiod and try again."<<endl;
      return -1;
   }

   //set pin 6 high to turn Led on
   gpio_write(pi, LED, 1);
   //sleep for 3.2 seconds
   time_sleep(3.2);
   //turn led off
   gpio_write(pi, LED, 0);

   //disconnect from pigpio daemon
   pigpio_stop(pi);
   return 0;
}
