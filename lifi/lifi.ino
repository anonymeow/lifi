
int led = 9; // Initializes the led pin
int led2 = 8;
int led3 = 7;
int led4 = 6;
int led5 = 5;
int led6 = 4;
int led7 = 3;
int led8 = 2;

int photo, photo2;

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
			char char_array[256]; // creates an array to store characters of string.
			letter.toCharArray(char_array, 256); // converts string to character array.
			for (int i = 0; char_array[i]; i++) { // loops through array and matches characters.
			}

		}
	}
}



//// This code should only be run on Com 7
//// This is for the recieving end
//
//
//// com 7
//int diodes = 3; // Sets photoresistors to pin A3
//int diodes2 = 0; // Sets photoresistors to pin A0
//String command;
//void setup() {
//  Serial.begin(115200); // Starts serial monitor on baude rate 115200
//  while (!Serial); // Allows commands
//  Serial.println("----------------------------------");
//  Serial.println("   Welcome to Li-Fi v. 1.0.7");
//  Serial.println("Li-Fi:  Type !help for commands.");
//  Serial.println("----------------------------------");
//}
//
//void loop() {
//
//  if (Serial.available()) {
//    char ch = Serial.read(); // reads prefix for commands or word sending.
//    if (ch == '!') { // checks if command.
//      String command = Serial.readString();
//      // Will read photoresistor 1's strength
//      if (command == "read 1") { 
//        Serial.println("Laser 1");
//        Serial.println(analogRead(diodes));
//      }
//      // Will read photoresistor 2's strength
//      if (command == "read 2") {
//        Serial.println("Laser 2");
//        Serial.println(analogRead(diodes2));
//      }
//      // Will test start, 1, 0, and null points.
//      if (command == "test") {
//        if (analogRead(diodes) > 1) {
//          if (analogRead(diodes2) > 1) { Serial.println("Start"); }
//          else { Serial.println('1'); }
//        }
//        else {
//          if (analogRead(diodes2) > 1) { Serial.println('0'); }
//          else { Serial.println("Null"); }
//        }
//      }
//
//      while (command == "on") {
//        delay(30);
//        if (analogRead(diodes) > 1) {
//          if (analogRead(diodes2) > 1) { Serial.println("Start"); }
//          else { Serial.println('1'); }
//        }
//        else {
//          if (analogRead(diodes2) > 1) { Serial.println('0'); }
//          else { Serial.println("Null"); }
//        }
//
//        if (Serial.available()) {
//          char ch = Serial.read();
//          if (ch == '!') {
//            String command = Serial.readString();
//            if (command == "off") {
//              break;
//            }
//
//          }
//        }
//      }
//    }
//  }
//}






