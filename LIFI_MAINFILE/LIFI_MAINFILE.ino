#include <stdio.h>
#include <string.h>
using namespace std;

int led = 9; // Initializes the led pin
int led2 = 8;
int led3 = 7;
int led4 = 6;
int led5 = 5;
int led6 = 4;
int led7 = 3;
int led8 = 2;

int photo, photo2;

char binary_list[25][8]; // This is the array where the byte (8 bit) arrays are stored.
class Laser { // Creates the class laser. This contains all the functions of a laser.
public:
  int lednum;
  void on(int delay_set = 0, int delay_set2 = 0) { // Can set before and after delays.
    delay(delay_set);
    digitalWrite(lednum, HIGH);
    delay(delay_set2);
  }
  void off(int delay_set = 0, int delay_set2 = 0) { // Turns off lasers.
    delay(delay_set);
    digitalWrite(lednum, LOW);
    delay(delay_set2);
  }

};
void text_to_binary(const char* input) {
  int ascii; // Used to store the ASCII number of a character
  int length = strlen(input); // Find the length of the user's input

  for (int x = 0; x < length; x++)
  { // Repeat until user's input have all been read
    // x < length because the last character is "\0"
    ascii = input[x]; // Store a character in its ASCII number

    char* binary_reverse = new char[9]; // Dynamic memory allocation
    char* binary = new char[9];

    int y = 0; // Counter used for arrays

    while (ascii != 1)
    { // Continue until ASCII == 1
      if (ascii % 2 == 0)
      { // if ASCII is divisible by 2
        binary_reverse[y] = '0'; // Then put a zero
      }
      else if (ascii % 2 == 1)
      { // If not divisible by 2
        binary_reverse[y] = '1'; // Then put a 1
      }
      ascii /= 2; // Find quotient of ASCII / 2
      y++; // add 1 to y for next loop
    }
    if (ascii == 1)
    { // When ASCII is 1, we have to add 1 to the beginning
      binary_reverse[y] = '1';
      y++;
    }
    if (y < 7)
    { // Add zeros to the end of string if not 8 characters (1 byte)
      for (; y < 8; y++)
      { // Add until binary_reverse[7] (8th element)
        binary_reverse[y] = 0;
      }
    }
    for (int z = 0; z < 8; z++)
    { // Our array is reversed, put the number in the right order.
      binary[z] = binary_reverse[7 - z];
    }
    for (int i = 0; i < 9; i++) { // This will store each 8 bits in an array within the binary list.
                    // This will store the 8 bits in row x and column i.
                    // x is the same value as that characters position in the input char array.
                    // So, if a is the second letter in the input, x = 2, and i = 0, 1, 2, 3, 4, 5, 6, 7
      binary_list[x][i] = binary[i]; // This will store the 8 bits in row x and column i.
      binary_list[x][0] = '0'; // This guarantees that the start of a new character will start with 0.
    }
    delete[] binary_reverse; // Frees data for next iteration
    delete[] binary; // Frees data for next iteration. This is important.
  }
}

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  Serial.begin(9600); // Starts serial monitor
  while (!Serial);
  Serial.println("----------------------------------");
  Serial.println("   Welcome to Li-Fi v. 1.0.8");
  Serial.println("Li-Fi:  Type !help for commands.");
  Serial.println("----------------------------------");
}
void loop() {
  if (Serial.available()) { // reads input.
    char ch = Serial.read(); // reads prefix for commands or word sending.
    if (ch == '!') { // checks if command.
      String command = Serial.readString();
      if (command == "read") {
        Serial.println(analogRead(photo));
        Serial.println("-");
        Serial.println(analogRead(photo2));
      }
      if (command == "test") {
        for (int i = 9; i > 0; i--) {
          Laser lazerzz;
          lazerzz.lednum = i;
          lazerzz.on(0, 35);
          lazerzz.off();
        }


      }

      if (command == "on") {
        for (int i = 9; i > 0; i--) {
          Laser laserzz;
          laserzz.lednum = i;
          laserzz.on(1000);
          Serial.println(laserzz.lednum);
          delay(1000);
        }
      }

      if (command == "off") {
        for (int i = 9; i > 0; i--) {
          Laser laserzz;
          laserzz.lednum = i;
          laserzz.off();
          Serial.println(laserzz.lednum);
          delay(1000);
        }

      }

      if (command == "clear") {
        Serial.println("--------------------------");
        Serial.println("Li-Fi: Cleared");
        Serial.println("--------------------------");
      }
      if (command == "help") {
        Serial.println("--------------------------");
        Serial.println("Li-Fi: ![command]");
        Serial.println("  !off - turns off laser.");
        Serial.println("  !on - turns laser on.");
        Serial.println("  !clear - clears last command.");
        Serial.println("  !test - will test resistor input.");
        Serial.println("  !read - will give current raw resistor value.");
        Serial.println("  To transmit words, @[sentence]");
        Serial.println("---------------------------");
      }
    }
    else if (ch == '@') {
      String letter = Serial.readString(); // takes string.
      char char_array[25]; // creates an array to store characters of string.
      letter.toCharArray(char_array, 25); // converts string to character array.
      text_to_binary(char_array);
      
      for (unsigned int i = 0; i < strlen(char_array); i++) {
        for (int j = 0; j < 9; j++) {
          if (binary_list[i][j] == '0') {
            Laser laser;
            laser.lednum = 8;
            laser.on();
            delay(500);
            laser.off();
            delay(500);
          }
          if (binary_list[i][j] == '1') {
            Laser laser;
            laser.lednum = 9;
            laser.on();
            delay(500);
            laser.off();
            delay(500);
          }
        }
      
      }
    }
  }
}


