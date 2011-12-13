// ############################################
// 
// 4x4x4 LED Cube project
// By Christian Moen 2008
// chr@syntaks.org
// Lisence: GPL
//
// Low level graphic functions
//
// ############################################

void setvoxel(int x, int y, int z);
void clrvoxel(int x, int y, int z);
unsigned char getvoxel(int x, int y, int z);
unsigned char inrange(int x, int y, int z);
void flpvoxel(int x, int y, int z);
void altervoxel(int x, int y, int z, int state);
void setplane_z(int z);
void clrplane_z(int z);
void setplane_x(int x);
void clrplane_x(int x);
void setplane_y(int y);
void clrplane_y(int y);
void setplane(unsigned char plane, int i, int state);
void setline_z(int x, int y, int z1, int z2);
void setline_x(int z, int y, int x1, int x2);
void setline_y(int z, int x, int y1, int y2);
void clrline_z(int x, int y, int z1, int z2);
void clrline_x(int z, int y, int x1, int x2);
void clrline_y(int z, int x, int y1, int y2);
void drawline_plane(int x2, int y2, int x1, int y1,unsigned char anchor);
void fill (unsigned char pattern);
void tmp2cube(void);
void cube2tmp(void);


// Set a voxel in the cube buffer
void setvoxel(int x, int y, int z)
{ 
	if (inrange(x, y, z))
		cube[z][y] |= (1 << x);
}

// Clear a voxel in the cube buffer
void clrvoxel(int x, int y, int z)
{
	if (inrange(x, y, z))
	cube[z][y] &= ~(1 << x);
}

// Get the current status of a voxel
unsigned char getvoxel(int x, int y, int z)
{
	if (inrange(x, y, z))
	{
		if (cube[z][y] & (1 << x))
		{
			return 0x01;
		} else
		{
			return 0x00;
		}
	}
}

// This function validates that we are drawing inside the cube.
unsigned char inrange(int x, int y, int z)
{
	if (x >= 0 && x < 4 && y >= 0 && y < 4 && z >= 0 && z < 4)
	{
		return 0x01;
	} else
	{
		// One of the coordinates was outside the cube.
		return 0x00;
	}
}

// Alter the state of  a voxel in the cube buffer
// This function was made in order to make set and clr versions
// of other functions without writing two almost identical functions
void altervoxel(int x, int y, int z, int state)
{
	if (state == 1)
	{
		setvoxel(x,y,z);
	} else
	{
		clrvoxel(x,y,z);
	}
}

// Flip the state of a voxel.
// If the voxel is 1, its turned into a 0, and vice versa.
void flpvoxel(int x, int y, int z)
{
	if (inrange(x, y, z))
		cube[z][y] ^= (1 << x);
}

// Sets all the leds in the X and Y for a given Z
// i.e. draws a horizonal plane on a given level (z)
void setplane_z (int z)
{
	int i;
	// Loop the 4 rows on the given level and write 1 to the bits.
	for (i=0;i<4;i++)
		cube[z][i] = 0x0f;
}

// Clears all the leds on X and Y for a given Z
void clrplane_z (int z)
{
	int iy;
	for (iy=0;iy<4;iy++)
		cube[z][iy] = 0x00;
}

// Sets all the leds on Y and Z for a given X
void setplane_x (int x)
{
	int z;
	int y;
	// Since coordinates along the X axis are
	// the actual bits in each row of each layer
	// We loop them all, and set the apropriate bit.
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
		{
			// Set a bit, and shift it inwards to the right X
			cube[z][y] |= (0x01 << x);
		}
	}
}

// Clear all the leds on Y and Z for a given X
void clrplane_x (int x)
{
	int z;
	int y;
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
		{
			cube[z][y] &= ~(0x01 << x);
		}
	}
}

// Sets all the leds on X and Z for a given Y
void setplane_y (int y)
{
	int iz;
	for (iz=0;iz<4;iz++)
		cube[iz][y] = 0x0f; 
}

// Sets all the leds on X and Z for a given Y
void clrplane_y (int y)
{
	int iz;
	for (iz=0;iz<4;iz++)
		cube[iz][y] = 0x00; 
}

// Set a plane using the functions above
void setplane(unsigned char plane, int i, int state)
{
	if (plane == "x")
	{
		if (state > 0)
		{
			setplane_x(i);
		} else
		{
			clrplane_x(i);
		}
	}
	
	if (plane == "y")
	{
		if (state > 0)
		{
			setplane_y(i);
		} else
		{
			clrplane_y(i);
		}
	}
	
	if (plane == "z")
	{
		if (state > 0)
		{
			setplane_z(i);
		} else
		{
			clrplane_z(i);
		}
	}
}


// Draw a line along the Z axis
// state=0 clears a line of voxels,
// state=1 sets a line of voxels.
void line_z(int x, int y, int z1, int z2, int state)
{
	if (z1>z2)
	{
		int tmp;
		tmp = z1;
		z1= z2;
		z2 = tmp;
	}
	int i;
	for (i=z1;i<=z2;i++)
	{
		altervoxel(x,y,i,state);
	}
}

// Draw a line along the X axis
void line_x(int z, int y, int x1, int x2, int state)
{
	if (x1>x2)
	{
		int tmp;
		tmp = x1;
		x1= x2;
		x2 = tmp;
	}
	int i;
	for (i=x1;i<=x2;i++)
	{
		altervoxel(i,y,z,state);
	}
}

// Draw a line along the Y axis.
void line_y(int z, int x, int y1, int y2, int state)
{
	if (y1>y2)
	{
		int tmp;
		tmp = y1;
		y1= y2;
		y2 = tmp;
	}
	int i;
	for (i=y1;i<=y2;i++)
	{
			altervoxel(x,i,z,state);
	}
}

// Draws a plane on any diagonal angle
// unsigned char anchor is the plane that is constant. ("x","y", or "z")
void drawline_plane(int x2, int y2, int x1, int y1,unsigned char anchor){
	int deltax = abs(x2 - x1);        // The difference between the x's
	int deltay = abs(y2 - y1);        // The difference between the y's
	int x = x1;                       // Start x off at the first pixel
	int y = y1;                       // Start y off at the first pixel
	int xinc1;
	int xinc2;
	int yinc1;
	int yinc2;
	int den;
	int num;
	int numadd;
	int numpixels;
	
	if (x2 >= x1)                 // The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                          // The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}
	
	if (y2 >= y1)                 // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                          // The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}
	
	if (deltax >= deltay)         // There is at least one x-value for every y-value
	{
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else                          // There is at least one y-value for every x-value
	{
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
	int curpixel;
	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		if (anchor == "z")
		{
			// Draw the current pixels
			setvoxel(x, y, 3);
			setvoxel(x, y, 2);
			setvoxel(x, y, 1);
			setvoxel(x, y, 0);
		}
		
		if (anchor == "x")
		{
			// Draw the current pixels
			setvoxel(x, 3, y);
			setvoxel(x, 2, y);
			setvoxel(x, 1, y);
			setvoxel(x, 0, y);
		}
		
		if (anchor == "y")
		{
			// Draw the current pixels
			setvoxel(3, y, x);
			setvoxel(2, y, x);
			setvoxel(1, y, x);
			setvoxel(0, y, x);
		}
		
		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den)             // Check if numerator >= denominator
		{
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
}

// Copy the temp cube onto the real cube
void tmp2cube(void)
{
	int y, z;
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
		{
			cube[z][y] = tmpcube[z][y];
		}
	}
}

// Copy the cube into the temp buffer
void cube2tmp(void)
{
	int y, z;
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
		{
			tmpcube[z][y] = cube[z][y];
		}
	}
}

// Fill the cube with a given pattern.
// fill(0x00); clears the cube
// fill(0xff); lights all leds
void fill (unsigned char pattern)
{
	int z;
	int y;
	for (z=0;z<4;z++)
	{
		for (y=0;y<4;y++)
		{
			cube[z][y] = pattern;
		}
	}
}



