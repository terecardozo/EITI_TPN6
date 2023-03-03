/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @file plantilla.c
 **
 ** @brief Plantilla de archivos fuente
 **
 ** Plantilla para los archivos de codigo fuente de prácticos de las
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 **
 ** | RV | YYYY.MM.DD | Autor       | Descripción de los cambios              |
 ** |----|------------|-------------|-----------------------------------------|
 ** |  1 | 2022.08.27 | evolentini  | Version inicial del archivo             |
 **
 ** @defgroup plantilla Plantilals de Archivos
 ** @brief Plantillas de archivos normalizadas
 ** @{
 */

/* === Inclusiones de cabeceras ============================================ */
#include "pantalla.h"

#include <string.h>

/* === Definicion y Macros privados ======================================== */
#ifndef DISPLAY_MAX_DIGITS
    #define DISPLAY_MAX_DIGITS 8
#endif

/* === Declaraciones de tipos de datos privados ============================ */
struct display_s {
    uint8_t digits;
    uint8_t active_digit;
	uint8_t flashing_from;
    uint8_t flashing_to;
    uint16_t flashing_frecuency;
    uint16_t flashing_count;
    uint8_t memory[DISPLAY_MAX_DIGITS];
    struct display_driver_s driver;
};
/* === Definiciones de variables privadas ================================== */
static struct display_s instances[1];

static const uint8_t IMAGES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,
    SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,
};

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */

/* === Definiciones de funciones privadas ================================== */

/* === Definiciones de funciones publicas ================================== */
display_t DisplayCreate(uint8_t digit, display_driver_t driver) {
    display_t display = instances;

    display->digits = digit;
    display->active_digit = digit - 1;
	display-> flashing_from = 0;
    display->flashing_to = 0;
    display->flashing_frecuency = 0 ;
    memset(display->memory, 0, sizeof(display->memory));
    display->driver.ScreenTurnOff = driver->ScreenTurnOff;
    display->driver.SegmentsTurnOn = driver->SegmentsTurnOn;
    display->driver.DigitTurnOn = driver->DigitTurnOn;

    display->driver.ScreenTurnOff();

    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size) {
    memset(display->memory, 0, sizeof(display->memory));
    for (int index = 0; index < size; index++) {
        if (index == display->digits) break;
        display->memory[index] = IMAGES[number[index]];
    }
}

void DisplayRefresh(display_t display) {
	uint8_t segments;
    
    if (display->active_digit == display->digits - 1) {
        display->active_digit = 0;
    } else {
        display->active_digit = display->active_digit + 1;
    }

    display->driver.ScreenTurnOff();

    if(display->active_digit == 0){ 
        display-> flashing_count++;
        if(display->flashing_count >= display->flashing_frecuency){
            display->flashing_count = 0;
        }
    }
    segments = display->memory[display->active_digit];

    if(display->flashing_frecuency > 0){
        if(display->flashing_count >= display->flashing_frecuency / 2){ 
            if(display->active_digit >= display->flashing_from && display->active_digit <= display->flashing_to){ 
                segments = 0;
            } 
        }
    }

    display->driver.SegmentsTurnOn(segments);
    display->driver.DigitTurnOn(display->active_digit);
}

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frecuency){
    display-> flashing_from = from;
    display->flashing_to = to;
    display->flashing_frecuency = frecuency;
    display->flashing_count = 0;    
}

void DisplayToggleDots(display_t display, uint8_t from, uint8_t to){
    for(int index=from ; index <= to ; index++){        
        display->memory[index] ^= (1<<7);
    }       
}
/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */
