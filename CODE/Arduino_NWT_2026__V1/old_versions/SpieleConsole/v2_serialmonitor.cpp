#include <Arduino.h>

// Spielfeldgröße
const int W = 10;
const int H = 16;

unsigned long lastDraw = 0;
const int drawInterval = 500; // 100 ms = 10 FPS


byte field[H][W];

struct Piece {
  byte s[4][4];
  int x, y;
};

Piece cur;

Piece pieces[7] = {
  {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},3,0}, // I
  {{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},3,0}, // O
  {{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},3,0}, // T
  {{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},3,0}, // J
  {{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},3,0}, // L
  {{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},3,0}, // S
  {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},3,0}  // Z
};


void clearScreen() {
  Serial.write(27);   // ESC
  Serial.print("[2J"); // Clear screen
  Serial.write(27);
  Serial.print("[H");  // Cursor to home
}


bool coll(Piece &p, int nx, int ny) {
  for(int y=0;y<4;y++)
    for(int x=0;x<4;x++)
      if(p.s[y][x]) {
        int fx = nx + x;
        int fy = ny + y;
        if(fx<0 || fx>=W || fy<0 || fy>=H) return true;
        if(field[fy][fx]) return true;
      }
  return false;
}

bool tryRotate(Piece &p) {
  Piece t = p;
  byte tmp[4][4];

  for(int y=0;y<4;y++)
    for(int x=0;x<4;x++)
      tmp[x][3-y] = t.s[y][x];

  memcpy(t.s, tmp, 16);

  int kicks[5] = {0, -1, 1, -2, 2};

  for(int i=0;i<5;i++) {
    if(!coll(t, t.x + kicks[i], t.y)) {
      t.x += kicks[i];
      p = t;
      return true;
    }
  }
  return false;
}

void place(Piece &p) {
  for(int y=0;y<4;y++)
    for(int x=0;x<4;x++)
      if(p.s[y][x])
        field[p.y+y][p.x+x] = 1;
}

void clearLines() {
  for(int y=0;y<H;y++) {
    bool full = true;
    for(int x=0;x<W;x++)
      if(!field[y][x]) full = false;

    if(full) {
      for(int yy=y;yy>0;yy--)
        memcpy(field[yy], field[yy-1], W);
      memset(field[0], 0, W);
    }
  }
}

void newPiece() {
  cur = pieces[random(0,7)];
  cur.x = 3;
  cur.y = 0;
}

void drawHeader() {
  Serial.println();
  Serial.println("[ a ] links   [ d ] rechts   [ w ] drehen   [ s ] schneller");
  Serial.println("------------------------------------------------------------");
}
void draw() {

  clearScreen();
  drawHeader();


  for(int y=0;y<H;y++) {
    for(int x=0;x<W;x++) {
      bool filled = field[y][x];

      for(int py=0;py<4;py++)
        for(int px=0;px<4;px++)
          if(cur.s[py][px] && cur.y+py==y && cur.x+px==x)
            filled = true;

      Serial.print(filled ? "#" : ".");
    }
    Serial.println();
  }
}


unsigned long lastFall = 0;
int speed = 500;

void setup() {
  Serial.begin(115200);
  memset(field,0,sizeof(field));
  randomSeed(analogRead(0));
  newPiece();
  Serial.println("TETRIS STARTED");
}

void loop() {

  // Eingabe lesen
  if(Serial.available()) {
    char c = Serial.read();

    if(c=='a' && !coll(cur,cur.x-1,cur.y)) cur.x--;
    if(c=='d' && !coll(cur,cur.x+1,cur.y)) cur.x++;
    if(c=='w') tryRotate(cur);
    if(c=='s') speed = 50;
  } else {
    speed = 500;
  }

  // Fallen
  if(millis()-lastFall > speed) {
    if(!coll(cur,cur.x,cur.y+1)) cur.y++;
    else {
      place(cur);
      clearLines();
      newPiece();

      if(coll(cur,cur.x,cur.y)) {
        Serial.println("GAME OVER");
        delay(4000);
        memset(field,0,sizeof(field));
        newPiece();
      }
    }
    lastFall = millis();
  }
  if (millis() - lastDraw > drawInterval) {
    draw();
    lastDraw = millis();
  }

}
