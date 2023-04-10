/* Memory */
#define DDR_BASE              0x00000000
#define DDR_END               0x3FFFFFFF
#define A9_ONCHIP_BASE        0xFFFF0000
#define A9_ONCHIP_END         0xFFFFFFFF
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_ONCHIP_END       0xC803FFFF
#define FPGA_CHAR_BASE        0xC9000000
#define FPGA_CHAR_END         0xC9001FFF

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define JP1_BASE              0xFF200060
#define JP2_BASE              0xFF200070
#define PS2_BASE              0xFF200100
#define PS2_DUAL_BASE         0xFF200108
#define JTAG_UART_BASE        0xFF201000
#define JTAG_UART_2_BASE      0xFF201008
#define IrDA_BASE             0xFF201020
#define TIMER_BASE            0xFF202000
#define TIMER_2_BASE          0xFF202020
#define AV_CONFIG_BASE        0xFF203000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define AUDIO_BASE            0xFF203040
#define VIDEO_IN_BASE         0xFF203060
#define ADC_BASE              0xFF204000

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) CPU interface(s) */
#define MPCORE_GIC_CPUIF      0xFFFEC100    // PERIPH_BASE + 0x100
#define ICCICR                0x00          // offset to CPU interface control reg
#define ICCPMR                0x04          // offset to interrupt priority mask reg
#define ICCIAR                0x0C          // offset to interrupt acknowledge reg
#define ICCEOIR               0x10          // offset to end of interrupt reg

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030

#define INT_DISABLE            0b11000000
#define IRQ_MODE                0b10010
#define SVC_MODE                0b10011
#define INT_ENABLE             0b11000000 

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) distributor interface(s) */
#define MPCORE_GIC_DIST       0xFFFED000    // PERIPH_BASE + 0x1000
#define ICDDCR                0x00          // offset to distributor control reg
#define ICDISER               0x100         // offset to interrupt set-enable regs
#define ICDICER               0x180         // offset to interrupt clear-enable regs
#define ICDIPTR               0x800         // offset to interrupt processor targets regs
#define ICDICFR               0xC00         // offset to interrupt configuration regs

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

void disable_A9_interrupts(void);
void set_A9_IRQ_stack(void);
void config_GIC(void);
void enable_A9_interrupts(void);
void config_KEYs(void);
void config_mouse(void);
void pushbutton_ISR(void);
void config_interrupt(int, int);

int mouse_x_pos = 0;
int mouse_y_pos = 0;

volatile int pixel_buffer_start; // global variable
volatile int * pixel_ctrl_ptr = (int *)0xFF203020;

int main(void)
{
  disable_A9_interrupts();
    set_A9_IRQ_stack(); // initialize the stack pointer for IRQ mode
    config_GIC(); // configure the general interrupt controller
  config_KEYs();
    config_mouse();
    enable_A9_interrupts(); // enable interrupt

    pixel_buffer_start = *pixel_ctrl_ptr;
    //clear_screen();
    while(1){
  }
}

void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

void clear_screen(){
  for(int x = 0; x < RESOLUTION_X; x++){
    for(int y = 0; y < RESOLUTION_Y; y++){
      plot_pixel(x,y,0x0000);
    }
  }
}

void wait_for_v_sync(){
  register int status; 
  *pixel_ctrl_ptr = 1; //start synchronization
  status = *(pixel_ctrl_ptr +3);
  while(status&0x01){
    status = *(pixel_ctrl_ptr +3);
  }
}

void set_A9_IRQ_stack(void)
{
    int stack, mode;
    stack = A9_ONCHIP_END - 7; // top of A9 onchip memory, aligned to 8 bytes
    /* change processor to IRQ mode with interrupts disabled */
    mode = INT_DISABLE | IRQ_MODE;
    asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
    /* set banked stack pointer */
    asm("mov sp, %[ps]" : : [ps] "r"(stack));
    /* go back to SVC mode before executing subroutine return! */
    mode = INT_DISABLE | SVC_MODE;
    asm("msr cpsr, %[ps]" : : [ps] "r"(mode));
}
/*
* Turn on interrupts in the ARM processor
*/
void enable_A9_interrupts(void)
{
    int status = 0b01010011;
  asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

void config_GIC(void) {
  config_interrupt (73, 1); // configure the FPGA KEYs interrupt (73)
  // Set Interrupt Priority Mask Register (ICCPMR). Enable interrupts of all
  // priorities
  config_interrupt(79,1);
  *((int *) 0xFFFEC104) = 0xFFFF;
  // Set CPU Interface Control Register (ICCICR). Enable signaling of
  // interrupts
  *((int *) 0xFFFEC100) = 1;
  // Configure the Distributor Control Register (ICDDCR) to send pending
  // interrupts to CPUs
  *((int *) 0xFFFED000) = 1;
}

void config_interrupt(int N, int CPU_target) {
  int reg_offset, index, value, address;
  /* Configure the Interrupt Set-Enable Registers (ICDISERn).
  * reg_offset = (integer_div(N / 32) * 4
  * value = 1 << (N mod 32) */
  reg_offset = (N >> 3) & 0xFFFFFFFC;
  index = N & 0x1F;
  value = 0x1 << index;
  address = 0xFFFED100 + reg_offset;
  /* Now that we know the register address and value, set the appropriate bit */
  *(int *)address |= value;
  reg_offset = (N & 0xFFFFFFFC);
  index = N & 0x3;
  address = 0xFFFED800 + reg_offset + index;
  /* Now that we know the register address and value, write to (only) the
  * appropriate byte */
  *(char *)address = (char)CPU_target;
}

void config_interval_timer()
{
    volatile int * interval_timer_ptr =
    (int *)TIMER_BASE; // interal timer base address
    /* set the interval timer period for scrolling the HEX displays */
    int counter = 5000000; // 1/(100 MHz) x 5x10^6 = 50 msec
    *(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
    *(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
    /* start interval timer, enable its interrupts */
    *(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
}
    /* setup the KEY interrupts in the FPGA */
void MOUSE_ISR(){
  volatile int * PS2_ptr = (int *)PS2_BASE;
  int PS2_data, RVALID;
  char d = 0, state = 0;
  PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port
  RVALID = PS2_data & 0x8000; // extract the RVALID field
  char byte1 = 0, byte2 = 0, byte3 = 0;
  // PS/2 mouse needs to be reset (must be already plugged in)
  
  //while there is data to be read
  while (RVALID) {
    PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port
    RVALID = PS2_data & 0x8000; // extract the RVALID field
    state = PS2_data & 0xFF;
    d = PS2_data >> 8 & 0xFF; //read the second byte which is relative x
    int rel_x = d - ((state << 4) & 0x100);
    d = PS2_data >> 16 & 0xFF; //extract the third byte
    int rel_y = d - ((state << 3) & 0x100);
    mouse_x_pos = mouse_x_pos + rel_x;
      mouse_y_pos = mouse_y_pos + rel_y;
    /* shift the next data byte into the display */
    byte1 = byte2;
    byte2 = byte3;
    byte3 = PS2_data & 0xFF;

    if ((byte2 == (char)0xAA) && (byte3 == (char)0x00)){
      // mouse inserted; initialize sending of data
        *(PS2_ptr) = 0xF4;
    }
    
    //only plot the pixel is the right mouse was clicked
    if(state & 0x2){
      plot_pixel(mouse_x_pos, mouse_y_pos, 0x0000FF);
    } 
  }
}

void config_KEYs() {
  volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY base address
  *(KEY_ptr + 2) = 0xF; // enable interrupts for the two KEYs
}




void config_mouse(){
    volatile int* PS2_BASE_ptr = (int *) PS2_BASE;
    //enable interrupts - set the RE bit
  *(PS2_BASE_ptr) = 0xFF; 
    *(PS2_BASE_ptr + 1) = 0x1;
}

void __attribute__((interrupt)) __cs3_isr_irq(void)
{
    int interrupt_ID = *((int *)0xFFFEC10C);
  if (interrupt_ID == 73) {// check if interrupt is from the KEYs
    while(1){
      ;
    }
  }
  if (interrupt_ID == 79) {// check if interrupt is from the KEYs
    MOUSE_ISR();
  }
  else
    while (1); // if unexpected, then stay here
// Write to the End of Interrupt Register (ICCEOIR)
  *((int *)0xFFFEC110) = interrupt_ID;
}

void disable_A9_interrupts(void) {
  int status = 0b11010011;
  asm("msr cpsr, %[ps]" : : [ps] "r"(status));
}

// Define the remaining exception handlers
void __attribute__((interrupt)) __cs3_reset(void)
{
while (1)
;
}
void __attribute__((interrupt)) __cs3_isr_undef(void)
{
while (1)
;
}
void __attribute__((interrupt)) __cs3_isr_swi(void)
{
while (1)
;
}
void __attribute__((interrupt)) __cs3_isr_pabort(void)
{
while (1);
}
void __attribute__((interrupt)) __cs3_isr_dabort(void)
{
while (1)
;
}
void __attribute__((interrupt)) __cs3_isr_fiq(void)
{
while (1)
;
}


