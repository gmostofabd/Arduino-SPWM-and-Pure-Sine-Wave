
int i=0;
int x=0;
int OK=0;
int sinPWM[]={1,3,6,9,12,15,18,21,24,26,29,32,35,38,41,44,47,50,53,56,59,62,65,68,71,73,76,79,82,85,88,91,93,96,
99,102,104,107,110,112,115,118,120,123,126,128,131,133,136,138,141,143,146,148,151,153,155,158,160,
162,165,167,169,171,173,176,178,180,182,184,186,188,190,192,194,196,197,199,201,203,205,206,208,210,
211,213,214,216,217,219,220,222,223,224,226,227,228,229,230,232,233,234,235,236,237,238,239,239,240,
241,242,243,243,244,244,245,246,246,247,247,247,248,248,248,249,249,249,249,249,249,249,249,249,249,
249,249,248,248,248,247,247,247,246,246,245,244,244,243,243,242,241,240,239,239,238,237,236,235,234,233,
232,230,229,228,227,226,224,223,222,220,219,217,216,214,213,211,210,208,206,205,203,201,199,197,196,194,
192,190,188,186,184,182,180,178,176,173,171,169,167,165,162,160,158,155,153,151,148,146,143,141,138,136,
133,131,128,126,123,120,118,115,112,110,107,104,102,99,96,93,91,88,85,82,79,76,73,71,68,65,62,59,56,53,50,
47,44,41,38,35,32,29,26,24,21,18,15,12,9,6,3,1};

void setup() {
Serial.begin(9600);

pinMode(5, OUTPUT);
pinMode(6,OUTPUT);

cli();// stop interrupts
TCCR0A=0;//reset the value
TCCR0B=0;//reset the value
TCNT0=0;//reset the value
//0b allow me to write bits in binary
TCCR0A=0b10100001;//phase correct pwm mode
TCCR0B=0b00000001; //no prescaler
TCCR1A=0;//reset the value
TCCR1B=0;//reset the value
TCNT1=0;//reset the value
OCR1A=509;// compare match value
TCCR1B=0b00001001; //WGM12 bit is 1 and no prescaler

TIMSK1 |=(1 << OCIE1A);

sei();// enable interrupts
}
ISR(TIMER1_COMPA_vect){// interrupt when timer 1 match with OCR1A value
if(i>260 && OK==0){// final value from vector for pin 6
i=0;// go to first value of vector
OK=1;//enable pin 5
}
if(i>260 && OK==1){// final value from vector for pin 5
i=0;//go to firs value of vector
OK=0;//enable pin 6
}
x=sinPWM[i];// x take the value from vector corresponding to position i(i is zero indexed)
i=i+1;// go to the next position
if(OK==0){
OCR0B=0;//make pin 5 0
OCR0A=x;//enable pin 6 to corresponding duty cycle
}
if(OK==1){
OCR0A=0;//make pin 6 0
OCR0B=x;//enable pin 5 to corresponding duty cycle
}
}
void loop() {

}
