#include "Adafruit_GFX.h"
#include "RGBmatrixPanel.h"

#define CLK 8
#define LAT 10 // use A3 for v1 board
#define OE  9
#define SIZEOF_BITMAP 24
#define PACMAN_BITMAP (pacman_bitmaps)
#define PACMAN_LEFT_BITMAP (pacman_bitmaps+(SIZEOF_BITMAP * 6))
#define GHOST_BITMAP (pacman_bitmaps+(SIZEOF_BITMAP*12))
#define GHOST_EYES (GHOST_BITMAP+(SIZEOF_BITMAP*2))
#define GHOST_FACE (GHOST_BITMAP+(SIZEOF_BITMAP*3))
#define SCORE (pacman_bitmaps+(SIZEOF_BITMAP * 16))
#define SIZEOF_INVADER_BITMAP 18
#define INVADER0_BITMAP (invader_bitmaps)
#define INVADER1_BITMAP (invader_bitmaps+(SIZEOF_INVADER_BITMAP*2))
#define INVADER2_BITMAP (invader_bitmaps+(SIZEOF_INVADER_BITMAP*4))
#define N 0
#define O 1
#define T 2
#define R 3
#define P 4
#define I 5
#define C 6
#define D 7
#define E 8
#define S 9
#define G 10

#define PACMAN_START -11
#define GHOST_START -35
#define Y 3

const unsigned char PROGMEM pacman_bitmaps[] = {

// open

11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b00000000,
0b01111110,0b00000000,
0b11111100,0b00000000,
0b11111000,0b00000000,
0b11111100,0b00000000,
0b01111110,0b00000000,
0b01111111,0b00000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// half open
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b11111110,0b00000000,
0b11111000,0b00000000,
0b11111110,0b00000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// closed
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// shading, open

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// shading, half open

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00000001,0b00000000,
0b00000000,0b00000000,
0b00000001,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// shading, closed

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// left open

11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b00011111,0b11000000,
0b00001111,0b11000000,
0b00000111,0b11100000,
0b00000011,0b11100000,
0b00000111,0b11100000,
0b00001111,0b11000000,
0b00011111,0b11000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// left half open
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b00001111,0b11100000,
0b00000011,0b11100000,
0b00001111,0b11100000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// left closed
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b00111111,0b10000000,
0b00001110,0b00000000,

// left shading, open

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// left shading, half open

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00010000,0b00000000,
0b00000000,0b00000000,
0b00010000,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// left shading, closed

11,11,
0b00010001,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b10000000,0b00100000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010001,0b00000000,

// ghost pattern 1
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11001110,0b01100000,

// ghost pattern 2
11,11,
0b00001110,0b00000000,
0b00111111,0b10000000,
0b01111111,0b11000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b11111111,0b11100000,
0b10011011,0b00100000,

// ghost eyes (white)
11,11,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00011101,0b11000000,
0b00011101,0b11000000,
0b00011101,0b11000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

// blue ghost face  (pink)
11,11,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00011011,0b00000000,
0b00011011,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00010101,0b00000000,
0b00101010,0b10000000,
0b00000000,0b00000000,
0b00000000,0b00000000,

// 200
11,11,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01000100,0b01000000,
0b10101010,0b10100000,
0b00101010,0b10100000,
0b01001010,0b10100000,
0b11100100,0b01000000,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b00000000,0b00000000


};

const unsigned char invader_bitmaps[] PROGMEM = {


// 0a

11,8,
0b00000110,0b00000000,
0b00001111,0b00000000,
0b00011111,0b10000000,
0b00110110,0b11000000,
0b00111111,0b11000000,
0b00001001,0b00000000,
0b00010110,0b10000000,
0b00101001,0b01000000,


// 0b

11,8,
0b00000110,0b00000000,
0b00001111,0b00000000,
0b00011111,0b10000000,
0b00110110,0b11000000,
0b00111111,0b11000000,
0b00001001,0b00000000,
0b00010000,0b10000000,
0b00001001,0b00000000,

// 1a

11,8,
0b00100000,0b10000000,
0b10010001,0b00100000,
0b10111111,0b10100000,
0b11101110,0b11100000,
0b01111111,0b11000000,
0b00111111,0b10000000,
0b00100000,0b10000000,
0b01000000,0b01000000,

// 1b

11,8,
0b00100000,0b10000000,
0b00010001,0b00000000,
0b00111111,0b10000000,
0b01101110,0b11000000,
0b11111111,0b11100000,
0b10111111,0b10100000,
0b10100000,0b10100000,
0b00011011,0b00000000,

// 2a

11,8,
0b00001110,0b00000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11001110,0b01100000,
0b11111111,0b11100000,
0b00111111,0b10000000,
0b01101110,0b11000000,
0b11000000,0b01100000,

// 2b

11,8,
0b00001110,0b00000000,
0b01111111,0b11000000,
0b11111111,0b11100000,
0b11001110,0b01100000,
0b11111111,0b11100000,
0b00111111,0b10000000,
0b01101110,0b11000000,
0b00110001,0b10000000

};

const unsigned char letter_bitmaps[] PROGMEM = {

// n
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b11111111,0b00000000,
0b10000001,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,

// o
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b00000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b01111111,0b00000000,

//t
9,8,
0b00000000,0b00000000,
0b01000000,0b00000000,
0b11110000,0b00000000,
0b01000000,0b00000000,
0b01000000,0b00000000,
0b01000000,0b00000000,
0b01000000,0b10000000,
0b00111111,0b00000000,

//r
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b11111111,0b00000000,
0b10000001,0b10000000,
0b10000000,0b00000000,
0b10000000,0b00000000,
0b10000000,0b00000000,
0b10000000,0b00000000,

//p
9,10,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b11111111,0b00000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b11111111,0b00000000,
0b10000000,0b00000000,
0b10000000,0b00000000,

// i
1,8,
0b10000000,
0b00000000,
0b10000000,
0b10000000,
0b10000000,
0b10000000,
0b10000000,
0b10000000,

// c
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b00000000,
0b10000000,0b10000000,
0b10000000,0b00000000,
0b10000000,0b00000000,
0b10000000,0b10000000,
0b01111111,0b00000000,

// d
9,8,
0b00000000,0b10000000,
0b00000000,0b10000000,
0b01111111,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b01111111,0b10000000,

// e
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b00000000,
0b10000000,0b10000000,
0b11111111,0b10000000,
0b10000000,0b00000000,
0b10000000,0b10000000,
0b01111111,0b00000000,

// s
9,8,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b00000000,
0b10000000,0b10000000,
0b11111111,0b00000000,
0b00000001,0b10000000,
0b10000000,0b10000000,
0b01111111,0b00000000,

// g
9,11,
0b00000000,0b00000000,
0b00000000,0b00000000,
0b01111111,0b00000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b10000000,0b10000000,
0b01111111,0b10000000,
0b00000000,0b10000000,
0b11000001,0b10000000,
0b01111111,0b00000000


};

RGBmatrixPanel matrix(A0, A1, A2, CLK, LAT, OE, false);
uint16_t black = matrix.Color444(0, 0, 0);
uint16_t yellow = matrix.Color444(15, 15, 0);
uint16_t darkyellow = matrix.Color444(1, 1, 0);
uint16_t red = matrix.Color444(15, 0, 0);
uint16_t white = matrix.Color444(15, 15, 15);
uint16_t pink = matrix.Color444(15, 3, 15);
uint16_t palePink = matrix.Color444(15, 8, 15);
uint16_t blue = matrix.Color444(0, 0, 10);
uint16_t cyan = matrix.Color444(0, 15, 15);
uint16_t orange = matrix.Color444(15, 5, 0);
uint16_t darkOrange = matrix.Color444(15, 1, 0);
uint16_t green = matrix.Color444(0, 15, 0);


int direction = 1;
int ghostDirection = 1;
int currentPacmanBitmap = 0;
int currentGhostBitmap = 0;
int biteDirection = 1; //opening or closing
int pacmanX = PACMAN_START;
int ghost1X = GHOST_START;
int ghost2X = GHOST_START;
int ghost3X = GHOST_START;
int ghost4X = GHOST_START;
int dotsY = 8;
unsigned long loopCounter = 0;
boolean didChange = false;
boolean caught = false;
uint16_t pillColor = palePink;
const unsigned char *letterBitmaps[] = {(letter_bitmaps), (letter_bitmaps+18), (letter_bitmaps+36), (letter_bitmaps+54), (letter_bitmaps+72), (letter_bitmaps+94), (letter_bitmaps+104), (letter_bitmaps+122), (letter_bitmaps+140), (letter_bitmaps+158), (letter_bitmaps+176)};


void setup() {
  matrix.begin();
}

void drawPacMan(int x, int y) {
  const unsigned char *bitmapBase = PACMAN_BITMAP;
  if (direction < 0) {
    bitmapBase = PACMAN_LEFT_BITMAP;
  }
  drawBitmap(x, y, bitmapBase+(currentPacmanBitmap*SIZEOF_BITMAP), yellow);
  drawBitmap(x, y, bitmapBase+((currentPacmanBitmap+3)*SIZEOF_BITMAP), darkyellow);
}

void animatePacMan() {
  currentPacmanBitmap += biteDirection;
  if (currentPacmanBitmap < 0) {
    biteDirection = -biteDirection;
    currentPacmanBitmap = 1;
  }
  if (currentPacmanBitmap > 2) {
    biteDirection = -biteDirection;
    currentPacmanBitmap = 1;
  }
}

void drawDeadGhost(int x, int y) {
  drawBitmap(x, y, GHOST_BITMAP+(currentGhostBitmap*SIZEOF_BITMAP), blue);
  drawBitmap(x, y, GHOST_FACE, pink);
}

void drawGhost(int x, int y, uint16_t color, int direction) {
  drawBitmap(x, y, GHOST_BITMAP+(currentGhostBitmap*SIZEOF_BITMAP), color);
  if (direction > 0) {
    drawBitmap(x, y, GHOST_EYES, white);
    matrix.drawPixel(x+5, y+4, blue);
    matrix.drawPixel(x+9, y+4, blue);
  } else {
    drawBitmap(x-2, y, GHOST_EYES, white);
    matrix.drawPixel(x+3, y+4, blue);
    matrix.drawPixel(x+6, y+4, blue);
  }    
}

void animateGhost() {
  if (currentGhostBitmap == 0) {
    currentGhostBitmap++;
  } else {
    currentGhostBitmap--;
  }
}


void loop() {

  pacmanGameDemo();
  clear();
  matrix.swapBuffers(false);
  delay(1000);

  nootropicDesign();
  clear();
  matrix.swapBuffers(false);
  delay(500);

  invaderDemo();
  clear();
  matrix.swapBuffers(false);
  delay(1000);
  
  nootropicDesign();
  clear();
  matrix.swapBuffers(false);
  delay(500);

  pacmanCharacters();
  clear();
  matrix.swapBuffers(false);
  delay(1000);

  nootropicDesign();
  clear();
  matrix.swapBuffers(false);
  delay(500);


}

void invaderDemo() {
  int d = 70;
  int toggleCounter = 0;
  for(int y=-5;y<1;y++) {
    for(int x=-10;x<10;x++) {
      drawInvaders(x, y, toggleCounter%2);
      toggleCounter++;
      delay(d);
    }
    d -= 3;
    y++;
    for(int x=10;x>-10;x--) {
      drawInvaders(x, y, toggleCounter%2);
      toggleCounter++;
      delay(d);
    }
    d -= 3;
  }
}


void drawInvaders(int x, int y, int offset) {
      clear();
      for(int i=0;i<3;i++) {
	drawBitmap(x+(i*12), y, INVADER0_BITMAP+(SIZEOF_INVADER_BITMAP * offset), green);
      }
      for(int i=0;i<3;i++) {
	drawBitmap(x+(i*12), y+9, INVADER1_BITMAP+(SIZEOF_INVADER_BITMAP * offset), green);
      }
      for(int i=0;i<3;i++) {
	drawBitmap(x+(i*12), y+18, INVADER2_BITMAP+(SIZEOF_INVADER_BITMAP * offset), green);
      }
      matrix.swapBuffers(false);
}


void nootropicDesign() {
  int y = 1;
  int offset = 0;
  for(int x=32;x>-140;x--) {
    offset = 0;
    clear();
    offset += drawBitmap(x+offset, y, letterBitmaps[N], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[O], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[O], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[T], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[R], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[O], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[P], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[I], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[C], darkOrange) + 1;
    offset += 3;
    offset += drawBitmap(x+offset, y, letterBitmaps[D], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[E], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[S], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[I], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[G], darkOrange) + 1;
    offset += drawBitmap(x+offset, y, letterBitmaps[N], darkOrange) + 1;
    matrix.swapBuffers(false);
    delay(15);
  }
}


void pacmanCharacters() {
  pacmanX = PACMAN_START;
  int ghostStart = -40;
  ghost1X = ghostStart;
  ghost2X = ghostStart-13;
  ghost3X = ghostStart-26;
  ghost4X = ghostStart-39;
  direction = 1;
  ghostDirection = 1;
  loopCounter = 0;
  int d = 15;
  while (ghost4X < 45) {
    loopCounter++;
    if ((loopCounter % 2) == 0) {
      animatePacMan();
    }

    if ((loopCounter % 4) == 0) {
      animateGhost();
    }

    pacmanX += direction;
    ghost1X += ghostDirection;
    ghost2X += ghostDirection;
    ghost3X += ghostDirection;
    ghost4X += ghostDirection;

    clear();
    drawPacMan(pacmanX, Y);
    drawGhost(ghost1X, Y, red, ghostDirection);
    drawGhost(ghost2X, Y, cyan, ghostDirection);
    drawGhost(ghost3X, Y, pink, ghostDirection);
    drawGhost(ghost4X, Y, orange, ghostDirection);
    matrix.swapBuffers(false);
    delay(d);
  }

  delay(500);
  
  ghostStart = 32;
  ghost1X = ghostStart;
  ghost2X = ghostStart+13;
  ghost3X = ghostStart+26;
  ghost4X = ghostStart+39;
  pacmanX = ghostStart+64;
  direction = -1;
  ghostDirection = -1;
  loopCounter = 0;

  while (pacmanX > PACMAN_START) {
    loopCounter++;
    if ((loopCounter % 2) == 0) {
      animatePacMan();
    }

    if ((loopCounter % 4) == 0) {
      animateGhost();
    }

    pacmanX += direction;
    ghost1X += ghostDirection;
    ghost2X += ghostDirection;
    ghost3X += ghostDirection;
    ghost4X += ghostDirection;

    clear();
    drawPacMan(pacmanX, Y);
    drawDeadGhost(ghost1X, Y);
    drawDeadGhost(ghost2X, Y);
    drawDeadGhost(ghost3X, Y);
    drawDeadGhost(ghost4X, Y);
    matrix.swapBuffers(false);
    delay(d);
  }
}

void pacmanGameDemo() {
  ghost1X = GHOST_START;
  pacmanX = PACMAN_START;
  ghostDirection = 1;
  direction = 1;
  caught = false;
  loopCounter = 0;
  int d = 15;
  while (true) {
    loopCounter++;

    int mod;
    if (direction > 0) {
      mod = 2;
    } else {
      mod = 2;
    }
    if ((loopCounter % mod) == 0) {
      animatePacMan();
    }

    if ((loopCounter % 5) == 0) {
      animateGhost();
    }

    // move 
    if (direction > 0) {
      mod = 3;
    } else {
      mod = 3;
    }
    if ((loopCounter % mod) == 0) {
      pacmanX += direction;
    }


    if (ghostDirection > 0) {
      mod = 2;
    } else {
      mod = 4;
    }
    if ((loopCounter % mod) == 0) {
      ghost1X += ghostDirection;
    }


    if (pacmanX >= 18) {
      ghostDirection = -1;
    }
    if (pacmanX >= 19) {
      direction = -1;
    }
    if ((!caught) && (direction < 0) && (ghost1X == -4)) {
      caught = true;
      clear();
      drawMaze();
      drawDots();
      drawBitmap(2, Y, SCORE, cyan);
      matrix.swapBuffers(false);
      delay(700);
    }
    if (pacmanX < PACMAN_START) {
      return;
    }


    clear();
    drawMaze();
    drawDots();
    drawPacMan(pacmanX, Y);
    if (!caught) {
      if (ghostDirection > 0) {
	drawGhost(ghost1X, Y, red, ghostDirection);
      } else {
	drawDeadGhost(ghost1X, Y);
      }
      
    }
    matrix.swapBuffers(false);
    delay(d);
  }
}

void drawDots() {
  int x, y;
  if ((loopCounter % 5) == 0) {
    if ((loopCounter % 10) == 0) {
      pillColor = palePink;
    } else {
      pillColor = black;
    }
  }

  if ((direction < 0) || (pacmanX >= 17)) {
    pillColor = black;
  }

  int pillX = 22;
  int pillY = 6;

  for(y=0;y<5;y++) {
    for(x=0;x<5;x++) {
      matrix.drawPixel(pillX+x, pillY+y, pillColor);
    }
  }
  matrix.drawPixel(pillX, pillY, black);
  matrix.drawPixel(pillX+4, pillY, black);
  matrix.drawPixel(pillX, pillY+4, black);
  matrix.drawPixel(pillX+4, pillY+4, black);


  for(x=1;x<21;x+=3) {
    if ((pacmanX+8 < x) && (direction > 0)) {
      matrix.drawPixel(x, 8, palePink);
    }
  }
  matrix.drawPixel(24, 0, palePink);
  matrix.drawPixel(24, 3, palePink);
}

void drawMaze() {
  int x, y;
  for(x=0;x<31;x++) {
    matrix.drawPixel(x, 15, blue);
  }
  for(x=0;x<18;x++) {
    matrix.drawPixel(x, 1, blue);
  }
  matrix.drawPixel(18, 0, blue);
  for(y=0;y<15;y++) {
    matrix.drawPixel(31, y, blue);
  }
}

void clear() {
  matrix.fillScreen(black);
}

uint8_t drawBitmap(int x, int y, const unsigned char *bmp, uint16_t color) {
  uint8_t width = pgm_read_byte(bmp);
  uint8_t height = pgm_read_byte(bmp+1);
  const unsigned char *p = bmp+2;
  uint8_t b;
  uint8_t bit;

  for (uint8_t j=0;j<height;j++) {
    for (uint8_t i=0;i<width;i++) {
      if ((i % 8) == 0) {
	b = pgm_read_byte(p);
	p++;
	bit = 7;
      }
      if ((b >> bit) & 0x1) {
	matrix.drawPixel(x+i, y+j, color);
      }
      bit--;
    }
  }
  return width;
}