// #include <Adafruit_LiquidCrystal.h>
#include <tinyexpr.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
byte rows[] = {8, 9, 10, 11, 12, 13};
const int rowCount = sizeof(rows) / sizeof(rows[0]);
char tecla='h';
double res = 0;
String str1="";
char str[100];
int error=0;
int count2 = 0;
// Adafruit_LiquidCrystal lcd_1(0);

// JP2 and JP3 are outputs
byte cols[] = {4, 5, 6, 7};
const int colCount = sizeof(cols) / sizeof(cols[0]);

byte keys[colCount][rowCount];

void setup() {
    // lcd_1.begin(16, 2);
    // lcd_1.setBacklight(1);
    // lcd_1.clear();
    Serial.begin(115200);
    // lcd_1.setCursor(0, 1);

    for (int x = 0; x < rowCount; x++) {
        //Serial.print(rows[x]);
        //Serial.println(" as input");
        pinMode(rows[x], INPUT);
    }

    for (int x = 0; x < colCount; x++) {
        //Serial.print(cols[x]);
        //Serial.println(" as input-pullup");
        pinMode(cols[x], INPUT_PULLUP);
    }
}

void readMatrix() {
    // iterate the columns
    for (int colIndex = 0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        byte curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);

        // row: iterate through the rows
        for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
            byte rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            keys[colIndex][rowIndex] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}

void printMatrix() {
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
        if (rowIndex < 10)
            Serial.print(F("0"));
        Serial.print(rowIndex);
        Serial.print(F(": "));

        for (int colIndex = 0; colIndex < colCount; colIndex++) {
            Serial.print(keys[colIndex][rowIndex]);
            if (colIndex < colCount - 1)
                Serial.print(F(", "));
        }
        Serial.println("");
    }
    Serial.println("");
    delay(100);
}

void loop() {
    readMatrix();
    //printMatrix();
    operador();
}

void cleear(){
char tecla='h';
str1="";
int count2 = 0;
Serial.println("Clear");
  
}

void operador() {
    //Serial.print("\nTo no operador\n");
    int coluna = -1;
    int linha = -1;
  	int count = 0;  	
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
        linha++;
        for (int colIndex = 0; colIndex < colCount; colIndex++) {
            coluna++;
          	if (keys[colIndex][rowIndex] == HIGH){
          		count++;
          	}
            if (keys[colIndex][rowIndex] == LOW && tecla=='h') {
            	int ValorBotao = (linha * 10) + colIndex;
                //Serial.print(ValorBotao);
             	
                switch (ValorBotao) {
                  	case 0:
                  		tecla='0';str1+=tecla;break;
                  	case 1:
                  		tecla='c';cleear();break;
                  	case 2:
                  		tecla='r';break;
                  	case 3:
                  		tecla='sqrt(';str1+=tecla;break;
                  	case 10:
                  		tecla='(';str1+=tecla;break;
                  	case 11:
                  		tecla=')';str1+=tecla;break;
                    case 12:
                  		tecla='p';break;
                  	case 13:
                  		tecla='%';str1+=tecla;break;                  	
                  	case 20:                  	
                  		tecla = '7';str1+=tecla;break;
                  	case 21:                  	
                  		tecla = '8';str1+=tecla;break;
                  	case 22:
                  		tecla = '9';str1+=tecla;break;
                  	case 23:
                  		tecla = '+';str1+=tecla;break;                	
                  	case 30:
                  		tecla = '4';str1+=tecla;break;
                  	case 31:
                  		tecla = '5';str1+=tecla;break;
                  	case 32:
                  		tecla = '6';str1+=tecla;break;
                  	case 33:
                  		tecla = '-';str1+=tecla;break;        	
                  	case 40:
                  		tecla='1';str1+=tecla;break;
                  	case 41:
                  		tecla='2';str1+=tecla;break;
                  	case 42:
                  		tecla='3';str1+=tecla;break;
                  	case 43:
                  		tecla='*';str1+=tecla;break;
                  	case 50:
                  		tecla ='=';
                      res = te_interp(str1.c_str(), &error);
                      if(error == 0){
                        Serial.print("Result: ");
                        Serial.println(res, 2);
                        str1="";
                        }
                      else{
                        while(--error) Serial.print(' ');
                        Serial.println("^~~");
                        Serial.println("Error in expression");
                      }
                      break;
                  	case 51:
                  		tecla='0';str1.concat(tecla);break;
                  	case 52:
                  		tecla=',';str1.concat(tecla);break;
                  	case 53:
                  		tecla='/';str1.concat(tecla);break;
                }
              Serial.println(str1);
              
              count2++;
            }
          if (count==24 && tecla!='h'){
          	tecla='h';
          }
        }
        coluna = -1;
    }
}