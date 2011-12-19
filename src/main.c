/*
 * 4x4x4 LED Cube project
 * By Christian Moen 2008
 * chr@syntaks.org
 * License: GPL
 */
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


/* Define USART stuff: CPU speed and baud rate */
#define FOSC 14745600
#define BAUD 9600
/* Calculate the correct USART timings. */
#define MYUBRR (((((FOSC * 10) / (16L * BAUD)) + 5) / 10) - 1)

/* Define masks used for status LEDs and input buttons. */
#define LED_GREEN 0x01
#define LED_RED 0x02
#define BUTTON 0x08
/*  Define port used for status and input. */
#define LED_PORT PORTB
#define BUTTON_PORT PORTB

/* Define masks for the layer select. */
#define LAYER1 0x80
#define LAYER2 0x40
#define LAYER3 0x20
#define LAYER4 0x10
#define LAYERS 0xf0   /* All layers. */
#define LAYERS_R 0x0f /* The inverse of the above. */
#define LAYER_PORT PORTD

/* 
 * Define LED grid ports. Each of the grid ports are connected to two rows
 * of leds. The upper 4 bits is one row, the lower 4 bits are one row. 
 */
#define GRID1 PORTC
#define GRID2 PORTA

void init_io(void);                  /* Initiate IO on the AVR */
void boot_msg(void);                 /* Blink some leds on boot or reboot. */
void delay_ms(uint16_t x);           /* Delay function. */
void led_red(unsigned char state);   /* Turn LEDs on or off. */
void led_green(unsigned char state);
void launch_effect(int effect);      /* Launch an effect. */

/*
 * Cube Buffer
 * The 3D image displayed on the cube is buffered in a 2d array 'cube'.
 * The 1st dimension in this array is the z-axis of the cube.
 * The 2nd dimension of the array is the y-axis.
 * Each byte is a stripe of leds running along the X axis at the given
 * y- and z-coordinates.
 * Only the 4 lower bits are used, since the cube is only 4x4x4.
 * This buffer design was chosen to have code compatability with a 8x8x8 cube.
 * "volatile" makes the variables reachable from within the interrupt functions
 */
volatile unsigned char cube[4][4];

/* 
 * We sometimes want to draw into a temporary buffer so we can modify it
 * before writing it to the cube buffer, e.g. invert, flip, reverse the
 * cube.
 */
volatile unsigned char tmpcube[4][4];

/* What layer the interrupt routine is currently showing. */
volatile unsigned char current_layer;

/* Low level geometric functions. */
#include "draw.c"

/* Static animation data */
#include "frames.c"

/* Fancy animations to run on the cube */
#include "effect.c"


int main (void)
{
    int i = 0;

    /* Initiate IO ports and peripheral devices. */
    init_io();
	
    /* Indicate that the device has just booted. */
    boot_msg();

    /* Set the layer to start drawing at */
    current_layer = 0x00;
	
    /* 
     * Enable interrupts to start drawing the cube buffer. When interrupts
     * are enabled, ISR(TIMER2_COMP_vect) will run on timed intervals. 
     */
    sei();

    /* Main program loop. */
    while (1) {
	for (i = 0; i < 13; ++i) {
	    launch_effect(i);
	}
	/* Comment the loop above and uncomment the line below
	 * if you want the effects in random order (produced some bugs.) */
	/* launch_effect(rand() % 13); */
    }

}

/* Launches one of those fancy effects. */
void launch_effect(int effect)
{
    switch (effect) {
    case 0:
	/* Lights all the layers one by one. */
	load_bar(1000);
	break;
    case 1:
	/* A pixel bouncing randomly around. */
	boing_boing(150,500,0x03,0x01);
	break;
    case 2:
	/* Randomly fill and empty the cube. */
	fill(0x00);
	random_filler(100, 1, 500, 1);
	random_filler(100, 1, 500, 0);
	break;
    case 3:
	/* Send voxels randomly back and forth the z-axis. */
	send_voxels_rand_z(150, 500, 2000);
	break;
    case 4:
	/* Spinning spiral */
	effect_spiral(1, 75, 1000);
	break;
    case 5:
	/* A coordinate bounces randomly around the cube. For every position
	 * the status of that voxel is toggled. */
	boing_boing(150, 500, 0x03, 0x02);
	break;
    case 6:
	/* Random raindrops */
	effect_rain(20, 5000, 3000, 500);
	break;
		
    case 7:
	/* Snake: a snake randomly bounce around the cube. */
	boing_boing(150, 500, 0x03, 0x03);
	break;
    case 8:
	/* Spinning plane */
	effect_spinning_plane(1, 50, 1000);
	break;
    case 9:
	/* Set x number of random voxels, delay, unset them. x increases
	 * from 1 to 20 and back to 1. */
	random_2();
	break;
    case 10:
	/* Set then unset all 64 voxels in a random order. */
	random_filler2(200, 1);
	delay_ms(2000);
	random_filler2(200, 0);
	delay_ms(1000);
	break;
    case 11:
	/* Bounce a plane up and down all the directions. */
	fly_plane('z', 1, 1000);
	delay_ms(2000);
	fly_plane('y', 1, 1000);
	delay_ms(2000);
	fly_plane('x', 1, 1000);
	delay_ms(2000);
	fly_plane('z', 0, 1000);
	delay_ms(2000);
	fly_plane('y', 0, 1000);
	delay_ms(2000);
	fly_plane('x', 0, 1000);
	delay_ms(2000);
	break;
    case 12:
	/* Fade in and out at low framerate. */
	blinky2();
	break;
    }
}


/* Diagnostic led functions */

/* Set or unset the red LED. */
void led_red(unsigned char state)
{
    if (state == 0x00) {
	LED_PORT &= ~LED_RED;
    } else {
	LED_PORT |= LED_RED;
    }
}

/* Set or unset the green LED. */
void led_green(unsigned char state)
{
    if (state == 0x00) {
	LED_PORT &= ~LED_GREEN;
    } else {
	LED_PORT |= LED_GREEN;
    }
}

/* Cube buffer draw interrupt routine. */
ISR(TIMER2_COMP_vect)
{
    /* AND the reverse bitmask onto the layer port. This disables all the
     * layers. rendering all the leds off. We don't want to see the cube
     * updating. */
    LAYER_PORT &= LAYERS_R;

    /* Take the current 2D image at the current layer along the z-axis and
     * place it on the LED grid. */
    GRID1 = (0x0f & cube[current_layer][0]) | 
	(0xf0 & (cube[current_layer][1] << 4));
    GRID2 = (0x0f & cube[current_layer][2]) | 
	(0xf0 & (cube[current_layer][3] << 4));

    /* Enable the apropriate layer. */
    LAYER_PORT |= (0x01 << (7 - current_layer));

    /* The cube only has 4 layers (0, 1, 2, 3). If we are at layer 3 now, we
     * want to go back to layer 0. */
    if (current_layer++ == 3) {
	current_layer = 0;
    }
}

/* Initialize AVR I/O. */
void init_io(void)
{
    /* Data Direction Registers */
    /* A bit set to 1 means that pin works as an output, a bit set to 0
     * means that pin is an input. */
    DDRA = 0xff;	/* Inner cube byte */
    DDRB = 0xf7;	/* 0-1: LEDs, 3: button, 4-7: ISP */
    DDRC = 0xff;	/* Outer cube byte */
    DDRD = 0xff;	/* Layer select */
	
    /* Set all ports OFF,  and enable pull up resistors where needed. */
    PORTA = 0x00;
    PORTC = 0x00;
    PORTB = 0x08;       /* Enable pull up for button. */
    PORTD = 0x00;

    /* Initialize timers and USART. */

    /* Frame buffer interrupt */
    TCNT2 = 0x00;	   /* initial counter value = 0. */
    TIMSK |= (1 << OCIE2); /* Enable CTC interrupt. */
	
    /* Every 1024th cpu cycle, a counter is incremented. Every time that
     * counter reaches 15, it is reset to 0 and the interrupt routine is
     * executed.
     *
     * 14745600/1024/15 = 960 times per second
     * There are 4 layers to update.
     * 14745600/1024/15/4 = 240 FPS == flicker free :)
     */
    OCR2 = 15; 			/* Interrupt when the counter reaches 15. */
    TCCR2 = 0x05; 		/* prescaler = 1024 */
    TCCR2 |= (1 << WGM01);	/* Clear Timer on Compare Match (CTC) mode */

    /* Initialize RS232. */
    /* USART Baud rate: 9600 */
    UBRRH = MYUBRR >> 8;
    UBRRL = MYUBRR;

    /* UCSR0C - USART control register
     * bit 7-6      sync/ascyn 00 = async,   01 = sync
     * bit 5-4      parity 00 = disabled
     * bit 3        stop bits 0 = 1 bit  1 = 2 bits
     * bit 2-1      frame length 11 = 8
     * bit 0        clock polarity = 0 */
    UCSRC  = 0b10000110;
    /* Enable RS232,  TX and RX */
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UDR = 0x00; /* Send an empty byte to indicate powerup. */
}

/*
 * Blink the status LEDs a little to indicate that the device has just
 * booted. This is useful to see if an error is making the device reboot
 * when not supposed to. And it looks cool. 
 */
void boot_msg(void)
{
    int i = 0;
    LED_PORT |= LED_GREEN;
    for (i = 0; i < 2; i++) {
	/* blinky */
	delay_ms(1000);
	LED_PORT &= ~LED_GREEN;
	LED_PORT |= LED_RED;
	/* blink */
	delay_ms(1000);
	LED_PORT &= ~LED_RED;
	LED_PORT |= LED_GREEN;
    }
    delay_ms(1000);
    LED_PORT &= ~LED_GREEN;
}

/* 
 * Delay function used in graphical effects.
 */
void delay_ms(uint16_t x)
{
    uint8_t y = 0;
    uint8_t z = 0;

    for ( ; x > 0; --x) {
	for (y = 0; y < 90; y++) {
	    for (z = 0 ;z < 6 ;z++) {
		asm volatile ("nop");
	    }
	}
    }
}
