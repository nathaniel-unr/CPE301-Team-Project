enum STATE { DISABLED = 0, IDLE = 1, RUNNING = 2, ERROR = 3 };

volatile STATE state = DISABLED;

void setup() {
  // other setup...

  Serial.begin(9600);
}

void loop() {
  switch (state) {
  case DISABLED:
    // disabled handling...
    break;
  case IDLE:
    // idle handling...
    break;
  case RUNNING:
    // running handling...
    break;
  case ERROR:
    // error handling...
    break;
  default:
    state = DISABLED;
  }
}
