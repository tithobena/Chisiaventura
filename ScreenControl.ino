#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

MCUFRIEND_kbv tft;
#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define FONDO     0x6595 
#define COLOR_BG      0x4208 
#define COLOR_BORDER  0xAD75 
#define COLOR_SHADOW  0x2104 
#define COLOR_SELECT  0xFFFF 
const int slots = 9;         
const int slotSize = 50;     
const int hotbarWidth = slots * slotSize; 
const int startX = (480 - hotbarWidth) / 2; 
const int startY = 320 - slotSize - 20;     

int currentSlot = 0; 

void setup() {
  Serial.begin(9600); // Iniciar comunicación Serial
  
  uint16_t ID = tft.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  
  tft.begin(ID);
  tft.setRotation(1); 
  tft.fillScreen(FONDO); 
  
  for (int i = 0; i < slots; i++) {
    drawSlot(i, i == currentSlot);
  }
}

void loop() {
  TSPoint p = ts.getPoint();

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > 10 && p.z < 1000) {
    int px = map(p.x, 150, 900, 0, 480); 
    int py = map(p.y, 150, 900, 0, 320); 
    
    if (py > startY && py < startY + slotSize) {
      if (px > startX && px < startX + hotbarWidth) {
        int touchedSlot = (px - startX) / slotSize;
        
        if (touchedSlot >= 0 && touchedSlot < 9) {
          if (touchedSlot != currentSlot) {
            int oldSlot = currentSlot;
            currentSlot = touchedSlot;
            
            drawSlot(oldSlot, false);
            drawSlot(currentSlot, true);

            // Transmitir la selección por Serial
            Serial.write(currentSlot); // Envía un solo byte (0-8)
            
            delay(150); 
          }
        }
      }
    }
  }
}

void drawSlot(int index, bool isSlcted) {
  int x = startX + (index * slotSize);
  int y = startY;
  int marco = 4; 
  
  tft.fillRect(x, y, slotSize, slotSize, COLOR_BG);
  tft.fillRect(x, y, slotSize, marco, COLOR_SHADOW);       
  tft.fillRect(x, y, marco, slotSize, COLOR_SHADOW);       
  tft.fillRect(x, y + slotSize - marco, slotSize, marco, COLOR_BORDER); 
  tft.fillRect(x + slotSize - marco, y, marco, slotSize, COLOR_BORDER); 

  if (isSlcted) {
    for (int w = 0; w < (marco + 1); w++) { 
      tft.drawRect(x + w, y + w, slotSize - (w*2), slotSize - (w*2), COLOR_SELECT);
    }
  }
}
