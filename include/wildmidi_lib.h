/*
	wildmidi_lib.h

	Midi Wavetable Processing library

    Copyright (C) Chris Ison 2001-2011
    Copyright (C) Bret Curtis 2013-2014

    This file is part of WildMIDI.

    WildMIDI is free software: you can redistribute and/or modify the player
    under the terms of the GNU General Public License and you can redistribute
    and/or modify the library under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation, either version 3 of
    the licenses, or(at your option) any later version.

    WildMIDI is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License and
    the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU General Public License and the
    GNU Lesser General Public License along with WildMIDI.  If not,  see
    <http://www.gnu.org/licenses/>.
*/

#ifndef WILDMIDI_LIB_H
#define WILDMIDI_LIB_H

/* library version number */
#define LIBWILDMIDI_VER_MAJOR 0L
#define LIBWILDMIDI_VER_MINOR 4L
#define LIBWILDMIDI_VER_MICRO 0L
#define LIBWILDMIDI_VERSION	\
      ((LIBWILDMIDI_VER_MAJOR << 16) | \
       (LIBWILDMIDI_VER_MINOR <<  8) | \
       (LIBWILDMIDI_VER_MICRO      ))

/* public constants */
#define WM_MO_LOG_VOLUME	0x0001
#define WM_MO_ENHANCED_RESAMPLING 0x0002
#define WM_MO_REVERB		0x0004
#define WM_MO_WHOLETEMPO	0x8000
#define WM_MO_ROUNDTEMPO	0x2000

/* conversion options */
#define WM_CO_XMI_TYPE		0x0010
#define WM_CO_FREQUENCY		0x0020

/* for WildMidi_GetString */
#define WM_GS_VERSION		0x0001

/* set our symbol export visiblity */
#if defined _WIN32 || defined __CYGWIN__
  /* ========== NOTE TO WINDOWS DEVELOPERS:
   * If you are compiling for Windows and will link to the static library
   * (libWildMidi.a with MinGW, or wildmidi_static.lib with MSVC, etc),
   * you must define WILDMIDI_STATIC in your project. Otherwise dllimport
   * will be assumed. */
# if defined(WILDMIDI_BUILD) && defined(DLL_EXPORT)		/* building libWildMidi as a dll for windows */
#  define WM_SYMBOL __declspec(dllexport)
# elif defined(WILDMIDI_BUILD) || defined(WILDMIDI_STATIC)	/* building or using static libWildMidi for windows */
#  define WM_SYMBOL
# else									/* using libWildMidi dll for windows */
#  define WM_SYMBOL __declspec(dllimport)
# endif
#elif defined(WILDMIDI_BUILD)
# if defined(SYM_VISIBILITY)	/* __GNUC__ >= 4, or older gcc with backported feature */
#  define WM_SYMBOL __attribute__ ((visibility ("default")))
/*
# elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#  define WM_SYMBOL __attribute__ ((visibility ("default")))
*/
# elif defined(SYM_LDSCOPE)	/* __SUNPRO_C >= 0x550 */
#  define WM_SYMBOL __global
# else
#  define WM_SYMBOL
# endif
#else
#  define WM_SYMBOL
#endif

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct _WM_Info {
	char *copyright;
	uint32_t current_sample;
	uint32_t approx_total_samples;
	uint16_t mixer_options;
	uint32_t total_midi_time;
};

typedef void midi;

WM_SYMBOL const char * WildMidi_GetString (uint16_t info);
WM_SYMBOL long WildMidi_GetVersion (void);
WM_SYMBOL int WildMidi_Init (const char *config_file, uint16_t rate, uint16_t mixer_options);
WM_SYMBOL int WildMidi_MasterVolume (uint8_t master_volume);
WM_SYMBOL midi * WildMidi_Open (const char *midifile);
WM_SYMBOL midi * WildMidi_OpenBuffer (uint8_t *midibuffer, uint32_t size);
WM_SYMBOL int WildMidi_GetOutput (midi *handle, int8_t *buffer, uint32_t size);
WM_SYMBOL int WildMidi_SetOption (midi *handle, uint16_t options, uint16_t setting);
WM_SYMBOL int WildMidi_ConvertToMidi (const char *file, uint8_t **out, uint32_t *size);
WM_SYMBOL int WildMidi_ConvertBufferToMidi (uint8_t *in, uint32_t insize,
							uint8_t **out, uint32_t *size);
WM_SYMBOL struct _WM_Info * WildMidi_GetInfo (midi * handle);
WM_SYMBOL int WildMidi_FastSeek (midi * handle, unsigned long int *sample_pos);
WM_SYMBOL int WildMidi_Close (midi * handle);
WM_SYMBOL int WildMidi_Shutdown (void);

/* NOTE: Not Yet Implemented Or Tested Properly */
/*int WildMidi_Live (midi * handle, uint32_t midi_event);*/

#if defined(__cplusplus)
}
#endif

#endif /* WILDMIDI_LIB_H */

