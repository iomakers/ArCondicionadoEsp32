# Ar Condicionado & Esp32

O objetivo deste projeto é controlar um Ar Condicionado Remotamente.

---

## Equipamentos Necessários
- Fios, Jumpers e Ferramentas
- 01 Ar Condicionado
- 01 Esp32
- 01 Módulo Relé
- 01 Contactor

## Começando
- Baixe e instale o ambiente de desenvolvimento do [Arduino](https://www.arduino.cc/en/Main/Software)
- Instale o Esp32 no ambiente de desenvolvimento do Arduino
  - [Tutorial de como Instalar](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/windows.md) (No futuro será adicionado um tutorial em Português)
- Baixe e instale o [ScadaBR](http://www.scadabr.com.br/)
- Instale as bibliotecas da pasta [lib](https://github.com/iomakers/ArCondicionadoEsp32/tree/master/lib) no seu arquivo local de bibliotecas
  - No futuro será adicionado um tutorial ensinando, por enquanto pesquise no google.
- Insira sua rede wifi no código
```
#define SSID   nome_do_wifi
#define PASSWD senha_do_wifi 
```
- Configure o pino que você quer usar 
  - Pesquise por [Esp 32 pinout](https://www.google.com.br/imghp?q=esp32+pinout) no Google, e troque o número da constante pelo pino selecionado
  - Geralmente utilizam GPIOxx, onde xx é o número a ser substituído na constante
```
const unsigned int ar_condicionado_001 = 33;
```

## Modbus IP
Aqui vamos entender um pouco sobre o que é usado no código.

- Bibliotecas necessárias para usar o protocolo Modbus IP com Esp32
```
#include <Modbus.h>
#include <ModbusIP_ESP32.h>
```
- Inicia o Modbus IP, chamando-o de mb
```
ModbusIP mb;
```
- Configura o Modbus IP com a rede wifi
```
mb.config("SSID", "PASSWD");
```
- A função *addCoil()* adiciona uma saída digital do tipo boolean (0 ou 1), que será enviada pelo Modbus IP
  - Recebe como parâmetro o registrador que será configurado no ScadaBR para ler o valor
  - O registrador é um número entre 1 e 9999, e não pode se repetir
  - O registrador pode ser modificado na linha seguinte
```
const unsigned int mb_reg_ar_condicionado_001 = 1;
mb.addCoil(mb_reg_ar_condicionado_001);
```
- A função *task()* é responsável por fazer o necessário para o Modbus IP funcionar. Deve ser chamada uma vez, no início do loop
- A função *Coil()* será responsável por acionar o relé, recebendo essa informação remotamente, com tudo o que foi configurado
  - Neste caso, estamos enviando nível lógico baixo (0V) para o módulo relé, pois é assim que ele funciona
  - Você pode ver como usamos a função *DigitalWrite()* normalmente para enviar LOW/HIGH no Arduino, mas no lugar de LOW/HIGH, ele envia para o pino, o que recebe do Modbus IP
  - Quando o loop começa, a função *task()* recebe o que foi enviado remotamente, e modifica o valor do *Coil()* que será escrito com *DigitalWrite()*
  ```
  digitalWrite(ar_condicionado_001, !mb.Coil(mb_reg_ar_condicionado_001));
  ```

Se quiser saber mais sobre Modbus IP, recomendo que leia [este tutorial](https://github.com/andresarmento/modbus-arduino/blob/master/README_pt_BR.md) da biblioteca que estamos utilizando.


A partir deste ponto, você já pode gravar o programa no microcontrolador, seguir para a montagem do circuito, e configuração do Scada

## ScadaBR
Aqui você verá como configurar o ScadaBR para controlar o Ar Condicionado.

## Montagem do Circuito
Aqui você aprenderá como o circuito funciona, e como montá-lo.
