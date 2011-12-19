/* 
 * 4x4x4 LED Cube project
 * By Christian Moen 2008
 * chr@syntaks.org
 * Lisence: GPL
 *
 * Low level graphic functions
 */

void set_voxel(int x, int y, int z);
void clear_voxel(int x, int y, int z);
unsigned char get_voxel(int x, int y, int z);
unsigned char in_range(int x, int y, int z);
void flip_voxel(int x, int y, int z);
void alter_voxel(int x, int y, int z, int state);
void set_z_plane(int z);
void clear_z_plane(int z);
void set_x_plane(int x);
void clear_x_plane(int x);
void set_y_plane(int y);
void clear_y_plane_y(int y);
void set_plane(unsigned char plane, int i, int state);
void set_z_line(int x, int y, int z1, int z2);
void set_x_line(int z, int y, int x1, int x2);
void set_y_line(int z, int x, int y1, int y2);
void clear_z_line(int x, int y, int z1, int z2);
void clear_x_line(int z, int y, int x1, int x2);
void clear_y_line(int z, int x, int y1, int y2);
void draw_line_plane(int x2, int y2, int x1, int y1,unsigned char anchor);
void fill(unsigned char pattern);
void tmp_to_cube(void);
void cube_to_tmp(void);


/* 
 * Set a voxel in the cube buffer. 
 */
void set_voxel(int x, int y, int z)
{ 
    if (in_range(x, y, z)) {
	cube[z][y] |= (1 << x);
    }
}

/* 
 * Clear a voxel in the cube buffer. 
 */
void clear_voxel(int x, int y, int z)
{
    if (in_range(x, y, z)) {
	cube[z][y] &= ~(1 << x);
    }
}

/* 
 * Get the current status of a voxel. 
 */
unsigned char get_voxel(int x, int y, int z)
{
    if (in_range(x, y, z)) {
	if (cube[z][y] & (1 << x)) {
	    return 0x01;
	} else {
	    return 0x00;
	}
    }

    /* TODO: What do we return if the requested voxel is not in range? */
    return 0x00;
}

/* 
 * This function validates that we are drawing inside the cube. 
 */
unsigned char in_range(int x, int y, int z)
{
    if (x >= 0 && x < 4 && y >= 0 && y < 4 && z >= 0 && z < 4) {
	return 0x01;
    } else {
	/* One of the coordinates was outside the cube. */
	return 0x00;
    }
}

/* 
 * Alter the state of a voxel in the cube buffer. This function was made in
 * order to make set and clr versions of other functions without writing two
 * almost identical functions. 
 */
void alter_voxel(int x, int y, int z, int state)
{
    if (state == 1) {
	set_voxel(x,y,z);
    } else {
	clear_voxel(x,y,z);
    }
}

/* 
 * Flip the state of a voxel. 
 */
void flip_voxel(int x, int y, int z)
{
    if (in_range(x, y, z)) {
	cube[z][y] ^= (1 << x);
    }
}

/* 
 * Sets all the leds in the x and y for a given z. I.e. draws a horizonal
 * plane on a given level (z). 
 */
void set_z_plane(int z)
{
    int i;
 
    /* Loop the 4 rows on the given level and write 1 to the bits. */
    for (i=0;i<4;i++) {
	cube[z][i] = 0x0f;
    }
}

/* 
 * Clears all the leds on x and y for a given z. 
 */
void clear_z_plane(int z)
{
    int iy;

    for (iy = 0; iy < 4; ++iy) {
	cube[z][iy] = 0x00;
    }
}

/* 
 * Sets all the leds on y and z for a given x. 
 */
void set_x_plane(int x)
{
    int z;
    int y;

    /* Since coordinates along the X axis are the actual bits in each row of
     * each layer, we loop them all, and set the apropriate bit. */
    for (z = 0; z < 4; ++z) {
	for (y = 0;y < 4; ++y) {
	    /* Set a bit, and shift it inwards to the right x. */
	    cube[z][y] |= (0x01 << x);
	}
    }
}

/* 
 * Clear all the LEDs on y and z for a given x. 
 */
void clear_x_plane(int x)
{
    int z;
    int y;

    for (z = 0; z < 4; ++z) {
	for (y = 0; y < 4; ++y) {
	    cube[z][y] &= ~(0x01 << x);
	}
    }
}

/* 
 * Sets all the LEDs on x and z for a given y. 
 */
void set_y_plane (int y)
{
    int iz;

    for (iz = 0; iz < 4; ++iz) {
	cube[iz][y] = 0x0f; 
    }
}

/* 
 * Clears all the LEDs on x and z for a given y. 
 */
void clear_y_plane (int y)
{
    int iz;

    for (iz = 0; iz < 4; ++iz) {
	cube[iz][y] = 0x00; 
    }
}

/* 
 * Sets a plane using the functions above. 
 */
void set_plane(unsigned char plane, int i, int state)
{
    if (plane == 'x') {
	if (state > 0) {
	    set_x_plane(i);
	} else {
	    clear_x_plane(i);
	}
    }
	
    if (plane == 'y') {
	if (state > 0) {
	    set_y_plane(i);
	} else {
	    clear_y_plane(i);
	}
    }
	
    if (plane == 'z') {
	if (state > 0) {
	    set_z_plane(i);
	} else {
	    clear_z_plane(i);
	}
    }
}


/* 
 * Draw a line along the Z axis. If state = 0 then this clears a line of
 * voxels, and if state = 1 this sets a line of voxels. 
 */
void line_z(int x, int y, int z1, int z2, int state)
{
    int i;

    if (z1 > z2) {
	int tmp;
	tmp = z1;
	z1 = z2;
	z2 = tmp;
    }

    for (i = z1; i <= z2; ++i) {
	alter_voxel(x, y, i, state);
    }
}

/* 
 * Draw a line along the X axis. 
 */
void line_x(int z, int y, int x1, int x2, int state)
{
    int i;

    if (x1 > x2) {
	int tmp;
	tmp = x1;
	x1 = x2;
	x2 = tmp;
    }

    for (i = x1; i <= x2; ++i) {
	alter_voxel(i, y, z, state);
    }
}

/* 
 * Draw a line along the Y axis. 
 */
void line_y(int z, int x, int y1, int y2, int state)
{
    int i;

    if (y1 > y2) {
	int tmp;
	tmp = y1;
	y1 = y2;
	y2 = tmp;
    }

    for (i = y1; i <= y2; ++i) {
	alter_voxel(x, i, z, state);
    }
}

/* 
 * Draws a plane on any diagonal angle. The unsigned char anchor is the
 * plane that is constant. ("x","y", or "z"). 
 */
void draw_line_plane(int x2, int y2, int x1, int y1, unsigned char anchor)
{
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
    int curpixel;
	
    if (x2 >= x1) {
	/* The x-values are increasing. */
	xinc1 = 1;
	xinc2 = 1;
    } else {
	/* The x-values are decreasing. */
	xinc1 = -1;
	xinc2 = -1;
    }
	
    if (y2 >= y1) {
	/* The y-values are increasing. */
	yinc1 = 1;
	yinc2 = 1;
    } else {
	/* The y-values are decreasing. */
	yinc1 = -1;
	yinc2 = -1;
    }
	
    if (deltax >= deltay) {
	/* There is at least one x-value for every y-value. */
	xinc1 = 0;      /* Don't change the x when numerator >= denominator. */
	yinc2 = 0;      /* Don't change the y for every iteration. */
	den = deltax;
	num = deltax / 2;
	numadd = deltay;
	numpixels = deltax;  /* There are more x-values than y-values. */
    } else {
	/* There is at least one y-value for every x-value. */
	xinc2 = 0;      /* Don't change the x for every iteration. */
	yinc1 = 0;      /* Don't change the y when numerator >= denominator. */
	den = deltay;
	num = deltay / 2;
	numadd = deltax;
	numpixels = deltay;  /* There are more y-values than x-values. */
    }

    for (curpixel = 0; curpixel <= numpixels; ++curpixel) {
	/* XXX: Replace series of if statements with if...else if... */
	/* XXX: Comparing unsigned char with char* string. */
	if (anchor == 'z') {
	    /* Draw the current pixels. */
	    set_voxel(x, y, 3);
	    set_voxel(x, y, 2);
	    set_voxel(x, y, 1);
	    set_voxel(x, y, 0);
	}
		
	if (anchor == 'x') {
	    /* Draw the current pixels. */
	    set_voxel(x, 3, y);
	    set_voxel(x, 2, y);
	    set_voxel(x, 1, y);
	    set_voxel(x, 0, y);
	}
		
	if (anchor == 'y') {
	    /* Draw the current pixels. */
	    set_voxel(3, y, x);
	    set_voxel(2, y, x);
	    set_voxel(1, y, x);
	    set_voxel(0, y, x);
	}
		
	/* Increase the numerator by the top of the fraction. */
	num += numadd;

	/* Check if numerator >= denominator. */
	if (num >= den)	{
	    num -= den;  /* Calculate the new numerator value. */
	    x += xinc1;  /* Change the x as appropriate. */
	    y += yinc1;  /* Change the y as appropriate. */
	}
	x += xinc2;      /* Change the x as appropriate. */
	y += yinc2;      /* Change the y as appropriate. */
    }
}

/*
 * Copy the temp cube onto the real cube.
 */
void tmp_to_cube(void)
{
    int y;
    int z;

    for (z=0; z < 4; ++z) {
	for (y = 0; y < 4;++y) {
	    cube[z][y] = tmpcube[z][y];
	}
    }
}

/*
 * Copy the cube into the temp buffer. 
 */
void cube_to_tmp(void)
{
    int y;
    int z;

    for (z = 0; z < 4; ++z) {
	for (y = 0; y < 4; ++y) {
	    tmpcube[z][y] = cube[z][y];
	}
    }
}

/*
 * Fill the cube with a given pattern. Calling fill(0x00) clears the cube
 * and calling fill(0xff) lights all leds. 
 */
void fill(unsigned char pattern)
{
    int z;
    int y;

    for (z = 0; z < 4; ++z) {
	for (y = 0; y < 4; ++y) {
	    cube[z][y] = pattern;
	}
    }
}
