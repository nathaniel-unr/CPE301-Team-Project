#define DECL_REG_U8(name, addr)                                                \
  volatile unsigned char *name = (volatile unsigned char *)addr;
#define DECL_REG_U16(name, addr)                                               \
  volatile unsigned int *name = (volatile unsigned int *)addr;

#define SET_OUTPUT(port, pin) *port |= (0x01 << pin);
#define SET_INPUT(port, pin) *port &= ~(0x01 << pin);

#define ENABLE_PULLUP(port, pin) *port |= (0x01 << pin);

#define SET_HIGH(port, pin) *port |= (0x01 << pin);
#define SET_LOW(port, pin) *port &= ~(0x01 << pin);

#define IS_HIGH(port, pin) ((*port & (0x01 << pin)) != 0)

DECL_REG_U8(myPORTA, 0x22);
DECL_REG_U8(myDDRA, 0x21);
DECL_REG_U8(myPINA, 0x20);

DECL_REG_U8(myPORTB, 0x25);
DECL_REG_U8(myDDRB, 0x24);
DECL_REG_U8(myPINB, 0x23);

DECL_REG_U8(myPORTH, 0x102);
DECL_REG_U8(myDDRH, 0x101);
DECL_REG_U8(myPINH, 0x100);

DECL_REG_U8(myPORTC, 0x28);
DECL_REG_U8(myDDRC, 0x27);
DECL_REG_U8(myPINC, 0x26);

DECL_REG_U8(myTCCR1B, 0x81);
DECL_REG_U16(myTCNT1, 0x84);
DECL_REG_U8(myTIFR1, 0x36);

#define BUTTON_PIN 4

#define YELLOW_LED_PIN 1
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN 5
#define RED_LED_PIN 7

enum STATE {
  DISABLED_STATE = 0,
  IDLE_STATE = 1,
  RUNNING_STATE = 2,
  ERROR_STATE = 3
};

volatile STATE state = DISABLED_STATE;

bool last_button_state = false;

void change_state(STATE new_state) {
  switch (state) {
  default:
  case DISABLED_STATE:
    SET_LOW(myPORTA, YELLOW_LED_PIN);
    break;
  case IDLE_STATE:
    SET_LOW(myPORTA, GREEN_LED_PIN);
    break;
  case RUNNING_STATE:
    SET_LOW(myPORTA, BLUE_LED_PIN);
    break;
  case ERROR_STATE:
    SET_LOW(myPORTA, RED_LED_PIN);
    break;
  }

  state = new_state;

  switch (new_state) {
  default:
  case DISABLED_STATE:
    SET_HIGH(myPORTA, YELLOW_LED_PIN);
    break;
  case IDLE_STATE:
    SET_HIGH(myPORTA, GREEN_LED_PIN);
    break;
  case RUNNING_STATE:
    SET_HIGH(myPORTA, BLUE_LED_PIN);
    break;
  case ERROR_STATE:
    SET_HIGH(myPORTA, RED_LED_PIN);
    break;
  }
}

void setup() {
  SET_INPUT(myDDRC, BUTTON_PIN);
  ENABLE_PULLUP(myPORTC, BUTTON_PIN);

  SET_OUTPUT(myDDRA, YELLOW_LED_PIN);
  SET_OUTPUT(myDDRA, GREEN_LED_PIN);

  Serial.begin(9600);

  change_state(DISABLED_STATE);
}

void loop() {
  bool current_button_state = !IS_HIGH(myPINC, BUTTON_PIN);

  // TODO: Debounce. USe ISR?
  if (current_button_state && current_button_state != last_button_state) {
    if (state != DISABLED_STATE) {
      change_state(DISABLED_STATE);
    } else {
      change_state(IDLE_STATE);
    }
  }
  last_button_state = current_button_state;

  switch (state) {
  case DISABLED_STATE:
    Serial.println("DISABLED");
    // disabled handling...
    break;
  case IDLE_STATE:
    Serial.println("IDLE");
    // idle handling...
    break;
  case RUNNING_STATE:
    Serial.println("RUNNING");
    // running handling...
    break;
  case ERROR_STATE:
    Serial.println("ERROR");
    // error handling...
    break;
  default:
    change_state(DISABLED_STATE);
  }
}
