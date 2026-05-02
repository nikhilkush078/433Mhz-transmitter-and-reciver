#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8
#define EN  3   // COMMON PWM PIN

void setup()
{
  driver.init();

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN, OUTPUT);
}

void loop()
{
  uint8_t buf[20];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))
  {
    buf[buflen] = '\0';

    char direction;
    int speedValue;

    sscanf((char*)buf, "%c,%d", &direction, &speedValue);

    analogWrite(EN, speedValue);   // COMMON PWM

    switch(direction)
    {
      case 'F':
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;

      case 'B':
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;

      case 'L':
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        break;

      case 'R':
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        break;

      default:
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        analogWrite(EN, 0);
        break;
    }
  }
}
