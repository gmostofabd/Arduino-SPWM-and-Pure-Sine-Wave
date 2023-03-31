unsigned int sin_table[32]={0, 100, 199, 296, 390, 480, 566, 645, 718, 783, 840, 889, 928, 958, 979, 989, 989, 979, 958, 928, 889, 840, 783, 718, 645, 566, 480, 390, 296, 199, 100, 0};

//#define MOSA PORTD0_bit
//#define MOSB PORTD1_bit
//#define MOSC PORTD2_bit
//#define MOSD PORTD3_bit

unsigned int Direction = 0; //my own modification for Direction
//unsigned char FlagReg;
//#define Direction FlagReg.B0
//0 -> MOS A + D
//1 -> MOS B + C

unsigned int TBL_POINTER_NEW;
unsigned int TBL_POINTER_OLD;
unsigned int TBL_POINTER_SHIFT;
unsigned int SET_FREQ;
unsigned int TBL_temp;
unsigned char DUTY_CYCLE;

void setup(){
  SET_FREQ = 410;
  TBL_POINTER_SHIFT = 0;
  TBL_POINTER_NEW = 0;
  TBL_POINTER_OLD = 0;
  DUTY_CYCLE = 0;
  DDRC = 0xFF;
  DDRD = 0XFF;
  OCR1AH = 0;
  OCR1AL = 0;
  TCCR1A = 0x82;
  ICR1H = 0x03;
  ICR1L = 0xE7;
  //ICR1 = 999 -> TOP -> 16kHz
  //TIMSK = 0x04;
  TIMSK1 = 0x01; //sets TOIE1
  TCCR1B = 0x19;
  //SREG_I_bit = 1;
  pinMode(9, OUTPUT); //sets output at pin 9 OC1A
  sei();
}


void loop(){

}


ISR(TIMER1_OVF_vect){
  TBL_POINTER_NEW = TBL_POINTER_NEW + SET_FREQ;
  if (TBL_POINTER_NEW < TBL_POINTER_OLD){
    if (Direction == 0){
    PORTD = B00000110; //Sets PinD1 and PinD2 HIGH, PinD0 and PinD3 LOW
    Direction = 1;
    }
    else{
    PORTD = B00001001; //sets PinD0 and PinD3 HIGH, PinD1 and PinD2 LOW
    Direction = 0;
    }
  }
  TBL_POINTER_SHIFT = TBL_POINTER_NEW >> 11;
  DUTY_CYCLE = TBL_POINTER_SHIFT;
  TBL_POINTER_SHIFT = sin_table[DUTY_CYCLE];
  OCR1AH = TBL_POINTER_SHIFT >> 8;
  OCR1AL = TBL_POINTER_SHIFT & 0x0F;
  TBL_POINTER_OLD = TBL_POINTER_NEW;
}
