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

enum STATE {
  DISABLED_STATE = 0,
  IDLE_STATE = 1,
  RUNNING_STATE = 2,
  ERROR_STATE = 3
};

volatile STATE state = DISABLED_STATE;

bool last_button_state = false;

void setup() {
  // other setup...

  SET_INPUT(myDDRC, BUTTON_PIN);
  ENABLE_PULLUP(myPORTC, BUTTON_PIN);

  Serial.begin(9600);
}

void loop() {
  bool current_button_state = !IS_HIGH(myPINC, BUTTON_PIN);

  if (current_button_state && current_button_state != last_button_state) {
    if (state != DISABLED_STATE) {
      state = DISABLED_STATE;
    } else {
      state = IDLE_STATE;
    }
  }
  last_button_state = current_button_state;

  switch (state) {
  case DISABLED_STATE:
    // disabled handling...
    Serial.println("Disabled");
    break;
  case IDLE_STATE:
    // idle handling...
    Serial.println("Idle");
    break;
  case RUNNING_STATE:
    // running handling...
    break;
  case ERROR_STATE:
    // error handling...
    break;
  default:
    state = DISABLED_STATE;
  }
}
