#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

// Le damos el nombre "pantalla" a nuestra pantalla y "tactil" al sensor de toques
MCUFRIEND_kbv pantalla; 
#define YP A2  
#define XM A3  
#define YM 8   
#define XP 9   
TouchScreen tactil = TouchScreen(XP, YP, XM, YM, 300);

// Definimos los colores que vamos a usar en formato hexadecimal (RGB565)
#define COLOR_FONDO       0x6595 
#define COLOR_CASILLA     0x4208 
#define COLOR_BORDE       0xAD75 
#define COLOR_SOMBRA      0x2104 
#define COLOR_SELECCION   0xFFFF // Blanco brillante

// Variables para organizar las casillas (la barra de abajo)
const int cantidadDeCasillas = 9;         
const int tamanoCasilla = 50;     
const int anchoDeLaBarra = cantidadDeCasillas * tamanoCasilla; 

// Calculamos dónde empieza la barra para que quede centrada
const int posicionXInicial = (480 - anchoDeLaBarra) / 2; 
const int posicionYInicial = 320 - tamanoCasilla - 20;     

// Esta variable guarda qué casilla está seleccionada actualmente
int casillaActual = 0; 

void setup() {
  // Iniciamos la comunicación con el otro Arduino a 9600 de velocidad
  Serial.begin(9600); 
  
  // Configuramos y encendemos la pantalla
  uint16_t ID = pantalla.readID();
  if (ID == 0xD3D3) ID = 0x9486; 
  
  pantalla.begin(ID);
  pantalla.setRotation(1); // Ponemos la pantalla en horizontal (apaisada)
  pantalla.fillScreen(COLOR_FONDO); // Pintamos todo el fondo
  
  // Dibujamos las 9 casillas por primera vez cuando arranca el Arduino
  for (int i = 0; i < cantidadDeCasillas; i++) {
    bool estaSeleccionada = (i == casillaActual);
    dibujarCasilla(i, estaSeleccionada);
  }
}

void loop() {
  // Leer si alguien está tocando la pantalla
  TSPoint toque = tactil.getPoint();

  // Es obligatorio restaurar estos pines después de leer el táctil
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  // Si la presión del toque es lo suficientemente fuerte...
  if (toque.z > 10 && toque.z < 1000) {
    
    // Convertimos las coordenadas del sensor a píxeles reales de la pantalla
    int pixelX = map(toque.x, 150, 900, 0, 480); 
    int pixelY = map(toque.y, 150, 900, 0, 320); 
    
    // Comprobamos si el dedo tocó a la altura de nuestra barra de casillas
    if (pixelY > posicionYInicial && pixelY < posicionYInicial + tamanoCasilla) {
      
      // Comprobamos si el dedo tocó dentro del ancho de la barra
      if (pixelX > posicionXInicial && pixelX < posicionXInicial + anchoDeLaBarra) {
        
        // Calculamos matemáticamente qué número de casilla (del 0 al 8) se tocó
        int casillaTocada = (pixelX - posicionXInicial) / tamanoCasilla;
        
        // Verificamos que sea una casilla válida y que no sea la que ya estaba seleccionada
        if (casillaTocada >= 0 && casillaTocada < 9) {
          if (casillaTocada != casillaActual) {
            
            // Guardamos la casilla vieja para borrarle el marco blanco
            int casillaAnterior = casillaActual;
            casillaActual = casillaTocada; // Actualizamos a la nueva casilla
            
            // Redibujamos las dos casillas que cambiaron
            dibujarCasilla(casillaAnterior, false); // Apaga el marco de la vieja
            dibujarCasilla(casillaActual, true);    // Prende el marco de la nueva

            // ¡IMPORTANTE! Enviamos el número de la nueva casilla al otro Arduino
            Serial.write(casillaActual); 
            
            delay(150); // Pausa para que no lea dos toques muy rápidos por error
          }
        }
      }
    }
  }
}

// Esta es una herramienta (función) que creamos para dibujar una sola casilla
void dibujarCasilla(int numeroDeCasilla, bool estaSeleccionada) {
  // Calculamos en qué posición X va esta casilla en particular
  int x = posicionXInicial + (numeroDeCasilla * tamanoCasilla);
  int y = posicionYInicial;
  int grosorDelMarco = 4; 
  
  // Dibujamos el cuadrado base y los bordes para que tenga efecto 3D
  pantalla.fillRect(x, y, tamanoCasilla, tamanoCasilla, COLOR_CASILLA);
  pantalla.fillRect(x, y, tamanoCasilla, grosorDelMarco, COLOR_SOMBRA);       
  pantalla.fillRect(x, y, grosorDelMarco, tamanoCasilla, COLOR_SOMBRA);       
  pantalla.fillRect(x, y + tamanoCasilla - grosorDelMarco, tamanoCasilla, grosorDelMarco, COLOR_BORDE); 
  pantalla.fillRect(x + tamanoCasilla - grosorDelMarco, y, grosorDelMarco, tamanoCasilla, COLOR_BORDE); 

  // Si esta casilla está seleccionada, le dibujamos un marco extra de color blanco brillante
  if (estaSeleccionada) {
    for (int grosor = 0; grosor < (grosorDelMarco + 1); grosor++) { 
      pantalla.drawRect(x + grosor, y + grosor, tamanoCasilla - (grosor*2), tamanoCasilla - (grosor*2), COLOR_SELECCION);
    }
  }
}