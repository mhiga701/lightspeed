#include <APA102.h>

const uint8_t dataPin = 23;
const uint8_t clockPin = 18;
APA102<dataPin, clockPin> ledStrip;

const uint16_t ledCount = 93; // Total number of LEDs on the strip
const uint8_t brightness = 1;

int inVal[9999];
int currentIndex = 0;

// Define arrays to hold data for each wing
rgb_color wing1[31]; // Assuming each wing has 31 LEDs
rgb_color wing2[31];
rgb_color wing3[31];
rgb_color wing4[31];

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char inchar = Serial.read();
    if (isdigit(inchar)) {
      inVal[currentIndex] = inchar;
      currentIndex++;
      if (currentIndex >= 9999) {
	      currentIndex = 0; // Reset index if it exceeds array size
      }
    }
   } else {
      // Calculate the number of LEDs per wing
      int ledsPerWing = 31;


      for (int i = 0; i < currentIndex; i += 6) { // Assuming each color is represented by 6 characters (e.g., "FF00FF")
	      int wingIndex = (i / 6) % ledsPerWing;
	      uint32_t color = 0;
	      for (int j = 0; j < 6; j++) {
	        color <<= 4; // Shift the bits to make space for the next hexadecimal digit
	        if (isdigit(inVal[i + j])) {
	          color |= inVal[i + j] - '0';
	        } else {
	          color |= (toupper(inVal[i + j]) - 'A' + 10);
	        }
	      } // end  inner for loop
	      
	      uint8_t red = (color >> 16) & 0xFF;
	      uint8_t green = (color >> 8) & 0xFF;
	      uint8_t blue = color & 0xFF;

	      if (i < ledsPerWing) {
	        wing1[wingIndex] = rgb_color(red, green, blue);
	      } else if (i < 2 * ledsPerWing) {
	        wing2[wingIndex] = rgb_color(red, green, blue);
	      } else if (i < 3 * ledsPerWing) {
	        wing3[wingIndex] = rgb_color(red, green, blue);
	      } else {
	        wing4[wingIndex] = rgb_color(red, green, blue);
	      }
      	Serial.print("Red: ");
      	Serial.print(red);
      	Serial.print(", Green: ");
      	Serial.print(green);
      	Serial.print(", Blue: ");
      	Serial.println(blue);
      } // end outer for loop


      // Write to LED strips
      // Assign rgb_color object to each element of wing1 array

      //wing1[1] = rgb_color(255,0,255);
      ledStrip.write(wing1, ledsPerWing, brightness);
      delay(50); // Delay between writing each wing to allow visualization
      ledStrip.write(wing2, ledsPerWing, brightness);
      delay(50);
      ledStrip.write(wing3, ledsPerWing, brightness);
      delay(50);
      ledStrip.write(wing4, currentIndex % ledsPerWing, brightness);
      delay(50);

      // Reset currentIndex for next cycle
      currentIndex = 0;

      delay(500);
  } 
}
