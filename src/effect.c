// ############################################
// 
// 4x4x4 LED Cube project
// By Christian Moen 2008
// chr@syntaks.org
// Lisence: GPL
//
// Graphic effects
//
// ############################################

void effect_spiral(int direction, int iterations, int delay);
void effect_spinning_plane(int direction, int iterations, int delay);
void effect_rain (int iterations, int delay, int hold, int speed);
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay);
void sendplane_rand_z (unsigned char z, int delay, int wait);
void blinky(void);
void flyplane (unsigned char plane,unsigned char direction, int delay);
void loadbar(int delay);
void random_1 (int iterations, int voxels, int delay);
void random_2 (void);
void random_filler (int iterations, int pixels, int delay, int state);
void random_filler2 (int delay, int state);
void planeflip (unsigned char axis1, int pos1, unsigned char axis2, int pos2, int delay);
void flip_playback (int delay, unsigned char flip_x, unsigned char flip_y, unsigned char flip_z);
void boingboing (uint16_t iterations, int delay, unsigned char mode, unsigned char drawmode);

// Shows an animation of a spinning spiral
void effect_spiral(int direction, int iterations, int delay)
{
	int i;
	int z;		// cube level

	for (i=0;i<iterations;i++)
	{
		// Loop cube levels
		for (z=0;z<4;z++)
		{
			// Read the animation from program memory and put it in the cube buffer.
			// y=0 and y=2 is stored in the upper nibble of the byte, and must be bitshifted into place.
			cube[z][0] = (pgm_read_byte(&spinning_line[(i+z)%6][0]) >> 4);
			cube[z][1] = pgm_read_byte(&spinning_line[(i+z)%6][0]);
			cube[z][2] = (pgm_read_byte(&spinning_line[(i+z)%6][1]) >> 4);
			cube[z][3] = pgm_read_byte(&spinning_line[(i+z)%6][1]);
			// the +z makes the animation iterate one step for each plane
			// making it into a spiral
		}
		delay_ms(delay);
	}
}

// Shows an animation of a spinning plane.
void effect_spinning_plane(int direction, int iterations, int delay)
{
	int i;
	int z;		// cube level

	for (i=0;i<iterations;i++)
	{
		// Loop cube levels.
		for (z=0;z<4;z++)
		{
			cube[z][0] = (pgm_read_byte(&spinning_line[(i)%6][0]) >> 4);
			cube[z][1] = pgm_read_byte(&spinning_line[(i)%6][0]);
			cube[z][2] = (pgm_read_byte(&spinning_line[(i)%6][1]) >> 4);
			cube[z][3] = pgm_read_byte(&spinning_line[(i)%6][1]);
		}
		delay_ms(delay);
	}
}

// Random voxels light up at the top layer and falls to the bottom layer.
void effect_rain (int iterations, int delay, int hold, int speed)
{
	int i;
	int p;		// Position of the raindrop on Z
	int z;		// cube layer
	int y;		// byte
	
	fill(0x00);
	
	for (i = 0; i < iterations; i++)
	{
		// Start by setting a random pixel on layer 3.
		setvoxel(rand()%4,rand()%4,3);
		delay_ms(hold);
		
		// The raindrop has to step down one layer 4 times
		// in order to travel from the top, and exit out the bottom.
		for (p=1;p<4;p++)
		{
			// Shift all the layers one position down,
			for (z=0;z<3;z++)
			{
				for (y=0;y<4;y++)
				{
					cube[z][y] = cube[z+1][y];
				}
			}
			
			// and a blank image on the top layer.
			cube[3][0] = 0x00;
			cube[3][1] = 0x00;
			cube[3][2] = 0x00;
			cube[3][3] = 0x00;
			
			// Accelerate the raindrop as it falls.
			// (speed/p) will decrease as p increases.
			delay_ms(speed+(speed/p));
		}
		
		fill(0x00);
		delay_ms(delay);
	}
}

// Send a voxel flying from one side of the cube to the other
// It its at the bottom, send it to the top..
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delay)
{
	int i, ii;
	for (i=0; i<4; i++)
	{
		if (z == 3)
		{
			ii = 3-i;
			clrvoxel(x,y,ii+1);
		} else
		{
			ii = i;
			clrvoxel(x,y,ii-1);
		}
		setvoxel(x,y,ii);
		delay_ms(delay);
	}
}

// Send all the voxels from one side of the cube to the other
// Start at z and send to the opposite side.
// Sends in random order.
void sendplane_rand_z (unsigned char z, int delay, int wait)
{
	unsigned char loop = 16;
	unsigned char x, y;

	fill(0x00);

	setplane_z(z);
	
	// Send voxels at random untill all 16 have crossed the cube.
	while(loop)
	{
		x = rand()%4;
		y = rand()%4;
		if (getvoxel(x,y,z))
		{
			// Send the voxel flying
			sendvoxel_z(x,y,z,delay);
			delay_ms(wait);
			loop--; // one down, loop-- to go. when this hits 0, the loop exits. 
		}
	}
}

// For each coordinate along X and Y, a voxel is set either at level 0 or at level 3
// for n iterations, a random voxel is sent to the opposite side of where it was.
void sendvoxels_rand_z (int iterations, int delay, int wait)
{
	unsigned char loop = 16;
	unsigned char x, y, last_x, last_y, i;

	fill(0x00);

	// Loop through all the X and Y coordinates
	for (x=0;x<4;x++)
	{
		for (y=0;y<4;y++)
		{
			// Then set a voxel either at the top or at the bottom
			if (rand()%2 == 0)
			{
				setvoxel(x,y,0);
			} else
			{
				setvoxel(x,y,3);
			}
		}
	}

	for (i=0;i<iterations;i++)
	{
		// Pick a random x,y position
		x = rand()%4;
		y = rand()%4;
		// but not the sameone twice in a row
		if (y != last_y && x != last_x)
		{
			// If the voxel at this x,y is at the bottom
			if (getvoxel(x,y,0))
			{
				// send it to the top
				sendvoxel_z(x,y,0,delay);
			} else
			{
				// if its at the top, send it to the bottom
				sendvoxel_z(x,y,3,delay);
			}
			delay_ms(wait);
			
			// Remember the last move
			last_y = y;
			last_x = x;
		}
	}

}

// Set n number of voxels at random positions
void random_1 (int iterations, int voxels, int delay)
{
	int i;
	int v;
	for (i = 0; i < iterations; i++)
	{
		for (v=0;v<=voxels;v++)
			setvoxel(rand()%4,rand()%4,rand()%4);
			
		delay_ms(delay);
		fill(0x00);
	}
}

// blink 1 random voxel, blink 2 random voxels..... blink 20 random voxels
// and back to 1 again.
void random_2 (void)
{
	int i;
	
	for (i=1;i<20;i++)
	{
		random_1(5,i,500);
	}
	
	for (i=20;i>=1;i--)
	{
		random_1(5,i,500);
	}
	
}

// Randomly fill or empty the cube with n voxels.
void random_filler (int iterations, int pixels, int delay, int state)
{
	int i;
	int p;
	for (i = 0; i < iterations; i++)
	{
		for (p=0;p<=pixels;p++)
			altervoxel(rand()%4,rand()%4,rand()%4,state);
			
		delay_ms(delay);
	}
}

// Set or clear exactly 64 voxels in a random order.
void random_filler2 (int delay, int state)
{
	int x,y,z;
	int loop = 0;
	
	while (loop<63)
	{
		x = rand()%4;
		y = rand()%4;
		z = rand()%4;

		if ((state == 0 && getvoxel(x,y,z) == 0x01) || (state == 1 && getvoxel(x,y,z) == 0x00))
		{
			altervoxel(x,y,z,state);
			delay_ms(delay);
			loop++;
		}	
	}
}

// ...to be continiued
void planeflip (unsigned char axis1, int pos1, unsigned char axis2, int pos2, int delay)
{
	
}


// Light all leds layer by layer,
// then unset layer by layer
void loadbar(int delay)
{
	fill(0x00);
	
	int z,y;
	
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
			cube[z][y] = 0xff;
			
		delay_ms(delay);
	}
	
	delay_ms(delay*3);
	
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
			cube[z][y] = 0x00;
			
		delay_ms(delay);
	}
}

void flyplane (unsigned char plane,unsigned char direction, int delay)
{
	int i,ii;
	
	fill(0x00);
	
	for (i=0;i<4;i++)
	{
		if (direction != 0)
		{
			ii = 3-i;
		} else
		{
			ii = i;
		}
		
		setplane(plane,ii,1);
		delay_ms(delay);
		setplane(plane,ii,0);
	}
	
	for (i=2;i>=0;i--)
	{
		if (direction != 0)
		{
			ii = 3-i;
		} else
		{
			ii = i;
		}
		
		setplane(plane,ii,1);
		delay_ms(delay);
		setplane(plane,ii,0);
	}
}

void blinky()
{
	int a;

	fill(0x00);
	delay_ms(2000);
	
	for (a=0;a<3;a++)
	{
		fill(0xff);
		delay_ms(50);
		fill(0x00);
		
		delay_ms(1500);
		
		fill(0xff);
		delay_ms(30);
		fill(0x00);
		
		delay_ms(7000);
	}
	
	
}

void blinky2()
{
	int i,r;
	fill(0x00);
	
	for (r=0;r<5;r++)
	{
		i = 750;
		while (i>0)
		{
			fill(0x00);
			delay_ms(i);
			
			fill(0xff);
			delay_ms(100);
			
			i = i - (15+(1000/(i/10)));
		}
		
		delay_ms(1000);
		
		i = 750;
		while (i>0)
		{
			fill(0x00);
			delay_ms(751-i);
			
			fill(0xff);
			delay_ms(100);
			
			i = i - (15+(1000/(i/10)));
		}
	}

}



// Big ugly function :p but it looks pretty
void boingboing(uint16_t iterations, int delay, unsigned char mode, unsigned char drawmode)
{
	fill(0x00);		// Blank the cube

	int x, y, z;		// Current coordinates for the point
	int dx, dy, dz;	// Direction of movement
	int lol, i;		// lol?
	unsigned char crash_x, crash_y, crash_z;

	// Coordinate array for the snake.
	int snake[8][3];
	for (i=0;i<8;i++)
	{
		snake[i][0] = 4;
		snake[i][1] = 4;
		snake[i][2] = 4;
	}
	
	y = rand()%4;
	x = rand()%4;
	z = rand()%4;
	
	dx = 1;
	dy = 1;
	dz = 1;
	
	while(iterations)
	{
		crash_x = 0;
		crash_y = 0;
		crash_z = 0;
	

		// Let's mix things up a little:
		if (rand()%3 == 0)
		{
			// Pick a random axis, and set the speed to a random number.
			lol = rand()%3;
			if (lol == 0)
				dx = rand()%3 - 1;
			
			if (lol == 1)
				dy = rand()%3 - 1;
				
			if (lol == 2)
				dz = rand()%3 - 1;
		}

	
		if (dx == -1 && x == 0)
		{
			crash_x = 0x01;
			if (rand()%3 == 1)
			{
				dx = 1;
			} else
			{
				dx = 0;
			}
		}
		
		if (dy == -1 && y == 0)
		{
			crash_y = 0x01;
			if (rand()%3 == 1)
			{
				dy = 1;
			} else
			{
				dy = 0;
			}
		}
		
		if (dz == -1 && z == 0)
		{
			crash_z = 0x01;
			if (rand()%3 == 1)
			{
				dz = 1;
			} else
			{
				dz = 0;
			}
		}
			
		if (dx == 1 && x == 3)
		{
			crash_x = 0x01;
			if (rand()%3 == 1)
			{
				dx = -1;
			} else
			{
				dx = 0;
			}
		}
		
		if (dy == 1 && y == 3)
		{
			crash_y = 0x01;
			if (rand()%3 == 1)
			{
				dy = -1;
			} else
			{
				dy = 0;
			}
		}
		
		if (dz == 1 && z == 3)
		{
			crash_z = 0x01;
			if (rand()%3 == 1)
			{
				dz = -1;
			} else
			{
				dz = 0;
			}
		}
		
		// mode bit 0 sets crash action enable
		if (mode | 0x01)
		{
			if (crash_x)
			{
				if (dy == 0)
				{
					if (y == 3)
					{
						dy = -1;
					} else if (y == 0)
					{
						dy = +1;
					} else
					{
						if (rand()%2 == 0)
						{
							dy = -1;
						} else
						{
							dy = 1;
						}
					}
				}
				if (dz == 0)
				{
					if (z == 3)
					{
						dz = -1;
					} else if (z == 0)
					{
						dz = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dz = -1;
						} else
						{
							dz = 1;
						}
					}	
				}
			}
			
			if (crash_y)
			{
				if (dx == 0)
				{
					if (x == 3)
					{
						dx = -1;
					} else if (x == 0)
					{
						dx = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dx = -1;
						} else
						{
							dx = 1;
						}
					}
				}
				if (dz == 0)
				{
					if (z == 3)
					{
						dz = -1;
					} else if (z == 0)
					{
						dz = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dz = -1;
						} else
						{
							dz = 1;
						}
					}	
				}
			}
			
			if (crash_z)
			{
				if (dy == 0)
				{
					if (y == 3)
					{
						dy = -1;
					} else if (y == 0)
					{
						dy = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dy = -1;
						} else
						{
							dy = 1;
						}
					}	
				}
				if (dx == 0)
				{
					if (x == 3)
					{
						dx = -1;
					} else if (x == 0)
					{
						dx = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dx = -1;
						} else
						{
							dx = 1;
						}
					}	
				}
			}
		}
		
		// mode bit 1 sets corner avoid enable
		if (mode | 0x02)
		{
			if (	// We are in one of 8 corner positions
				(x == 0 && y == 0 && z == 0) ||
				(x == 0 && y == 0 && z == 3) ||
				(x == 0 && y == 3 && z == 0) ||
				(x == 0 && y == 3 && z == 3) ||
				(x == 3 && y == 0 && z == 0) ||
				(x == 3 && y == 0 && z == 3) ||
				(x == 3 && y == 3 && z == 0) ||
				(x == 3 && y == 3 && z == 3) 				
			)
			{
				// At this point, the voxel would bounce
				// back and forth between this corner,
				// and the exact opposite corner
				// We don't want that!
			
				// So we alter the trajectory a bit,
				// to avoid corner stickyness
				lol = rand()%3;
				if (lol == 0)
					dx = 0;
				
				if (lol == 1)
					dy = 0;
					
				if (lol == 2)
					dz = 0;
			}
		}
	
		// Finally, move the voxel.
		x = x + dx;
		y = y + dy;
		z = z + dz;
		
		if (drawmode == 0x01) // show one voxel at time
		{
			setvoxel(x,y,z);
			delay_ms(delay);
			clrvoxel(x,y,z);	
		} else if (drawmode == 0x02) // flip the voxel in question
		{
			flpvoxel(x,y,z);
			delay_ms(delay);
		} if (drawmode == 0x03)
		{
			for (i=7;i>=0;i--)
			{
				snake[i][0] = snake[i-1][0];
				snake[i][1] = snake[i-1][1];
				snake[i][2] = snake[i-1][2];
			}
			snake[0][0] = x;
			snake[0][1] = y;
			snake[0][2] = z;
				
			for (i=0;i<8;i++)
			{
				setvoxel(snake[i][0],snake[i][1],snake[i][2]);
			}
			delay_ms(delay);
			for (i=0;i<8;i++)
			{
				clrvoxel(snake[i][0],snake[i][1],snake[i][2]);
			}
		}
		
	
		iterations--;
	}
}




































