// ############################################
// 
// 4x4x4 LED Cube project
// By Christian Moen 2008
// chr@syntaks.org
// Lisence: GPL
//
// ############################################

// 6 frame animation of line spinning around the center of the cube
// the animation is in 2 dimensions.
const unsigned char spinning_line[6][2] PROGMEM =
{
	{ 0x84, 0x21 },
	{ 0x0c, 0x30 },
	{ 0x03, 0xc0 },
	{ 0x12, 0x48 },
	{ 0x22, 0x44 },
	{ 0x44, 0x22 },
};