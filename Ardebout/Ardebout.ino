/* Ardebout: tiny project to have simple alarm clock (one led) to indicate to a child when he can wake up */
/* TODO: add temperature sensor to have child room temperature */

#include <Arduino.h>



/**
 * MYSENSORS
 **/
/* Enable debug prints to serial monitor */
#define MY_DEBUG
/* Enable and select radio type attached (NRF24) */
#define MY_RADIO_NRF24
/* Enable repeater functionality for this node */
#define MY_REPEATER_FEATURE

/* do not use to high baud rate when not needed */
#define MY_BAUD_RATE 9600
/* CE/CS PIN for NRF24L01+ can be redefined (9 and 10 by default but use by IR to have PWM) */
#define MY_RF24_CE_PIN 5
#define MY_RF24_CS_PIN 6

/* node id used for gateway (must be uniq) */
/* when not set it leave the gateway to assign an id (do not work always) */
#define MY_NODE_ID 63

/* MySensors will override usual function of a sketch, it for a node it need a gateway to start */
#include <MySensors.h>


/* Sensor id to present and finally received */
#define SENSOR_ID_LED_WAKE_UP  (0)

/* PIN number of wake up led */
#define PIN_ID_LED_WAKE_UP (9)

/* led state */
#define LED_STATE_ON (HIGH)
#define LED_STATE_OFF (LOW)


void before()
{
  /* everything before MySensors execution */
  pinMode(PIN_ID_LED_WAKE_UP, OUTPUT);

  /* make sure led is off at start */
  digitalWrite(PIN_ID_LED_WAKE_UP, LED_STATE_OFF);
}

void setup()
{
  //This pipes to the serial monitor
  /* Serial.begin(9600); */
}

void presentation()
{
  /* Send the sketch version information to the gateway and Node */
  sendSketchInfo("OK To Wake-Up System", "1.0");
  /* everything to present each sensors/actuators on this node to the gateway (so domotic box will register it) */
  present(SENSOR_ID_LED_WAKE_UP, S_BINARY);
}

void loop()
{
    /* TODO add temperature sensor pooling */
}

void receive(const MyMessage &message)
{
  Serial.println("Message received!");
  if (message.type == V_STATUS)
  {
    switch(message.sensor)
    {
      case SENSOR_ID_LED_WAKE_UP:
        digitalWrite(PIN_ID_LED_WAKE_UP, message.getBool() ? LED_STATE_ON : LED_STATE_OFF);
        break;

      default:
        Serial.println("Message received with unknown sensor ID.");
        break;
    }
  }
  else
  {
    Serial.println("Message received with unknown type.");
  }
}
