#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup()
{
  driver.init();
}

void loop()
{
  int x = analogRead(A0);
  int y = analogRead(A1);

  char direction = 'S';
  int speedValue = 0;

  if (y > 550)
  {
    direction = 'F';
    speedValue = map(y, 550, 1023, 0, 255);
  }
  else if (y < 470)
  {
    direction = 'B';
    speedValue = map(y, 470, 0, 0, 255);
  }
  else if (x > 550)
  {
    direction = 'R';
    speedValue = map(x, 550, 1023, 0, 255);
  }
  else if (x < 470)
  {
    direction = 'L';
    speedValue = map(x, 470, 0, 0, 255);
  }

  char data[10];
  sprintf(data, "%c,%d", direction, speedValue);

  driver.send((uint8_t *)data, strlen(data));
  driver.waitPacketSent();

  delay(50);
}
