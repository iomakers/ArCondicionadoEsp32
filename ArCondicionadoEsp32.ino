/*
Controle de Ar Condicionado
Autor: Will Douglas (github.com/willdowglas)
*/

/*    Bibliotecas    */
#include <Arduino.h>
#include <Modbus.h>
#include <ModbusIP_ESP32.h>

/*    Constantes    */
#define SSID 	nome_do_wifi 	// Insira aqui nome e senha do wifi.
#define PASSWD  senha_do_wifi	
	//Portas do ESP32
const unsigned int ar_condicionado_001 = 33;
	//Registradores do Modbus IP
const unsigned int mb_reg_ar_condicionado_001 = 1;

/*    Objetos    */
ModbusIP mb;

void setup(){
	mb.config("SSID", "PASSWD");
	pinMode(ar_condicionado_001, OUTPUT);
	mb.addCoil(mb_reg_ar_condicionado_001);
}


void loop(){
	mb.task();
	digitalWrite(ar_condicionado_001, !mb.Coil(mb_reg_ar_condicionado_001)); //envia 0v para acionar relé
}