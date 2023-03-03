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

#ifndef PANTALLA_H   /*! @cond    */
#define PANTALLA_H   /*! @endcond */

/** @file plantilla.h
 **
 ** @brief Plantilla de archivos de cabecera 
 **
 ** Plantilla para los archivos de cabeceras de las prácticos de las 
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

/* === Inclusiones de archivos externos ==================================== */
#include <stdint.h>

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */
#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)

/* == Declaraciones de tipos de datos publicos ============================= */
//! Referencia a un descriptor para gestionar una pantalla de siete segmentos multiplexada
typedef struct display_s * display_t;

//!Funcion de callback para apagar los segmentos y digitos de la pantalla
typedef void(*display_screen_off_t)(void);

//!Funcion de callback para prender los segmentos  de la pantalla
typedef void(*display_segments_on_t)(uint8_t segments);

//!Funcion de callback para prender un digito  de la pantalla
typedef void(*display_digit_on_t)(uint8_t digit);

typedef struct display_driver_s{
    display_screen_off_t ScreenTurnOff;
    display_segments_on_t SegmentsTurnOn;
    display_digit_on_t DigitTurnOn;
} const *  display_driver_t;

/* === Declaraciones de variables publicas ================================= */
/** 
 * @brief Método para crear una pantalla multiplexada de siete segmentos
 *
 * @param digits        Cantidad de dígitos que forman la pantalla 
 * @param driver        Estructura que referencia a función
 * @return display_t    Puntero al descrtiptor de la pantalla creada
 */
display_t DisplayCreate(uint8_t digits, display_driver_t driver);

/**
 * @brief Función para escribir el numero BCD en la pantalla
 *
 * @param display       Puntero al descriptor de la pantalla en la que se escribe
 * @param number        Puntero al primer elemento de numero BCD a escribir
 * @param size          Cantidad de elementos en el vector que contiene al numero BCD
 */
void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size);

/** 
 * @brief Función para refrescar la pantalla
 *
 * @param display       Puntero al descriptor de la pantalla a refrescar
 */
void DisplayRefresh(display_t display);

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frecuency);

void DisplayToggleDots(display_t display, uint8_t from, uint8_t to);

/* === Declaraciones de funciones publicas ================================= */

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* PLANTILLA_H */
