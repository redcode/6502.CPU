/* MOS 6502 CPU Emulator
  ____    ____    ___ ___     ___
 / __ \  / ___\  / __` __`\  / __`\
/\ \/  \/\ \__/_/\ \/\ \/\ \/\  __/
\ \__/\_\ \_____\ \_\ \_\ \_\ \____\
 \/_/\/_/\/_____/\/_/\/_/\/_/\/____/
Copyright © 1999-2015 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU General Public License v3. */

#ifndef __emulation_CPU_6502_H__
#define __emulation_CPU_6502_H__

#include <Z/hardware/CPU/architecture/650x.h>
#include <Z/ABIs/emulation.h>

#ifdef CPU_6502_USE_SLOTS
#	include <Z/macros/slot.h>
#endif

#ifndef CPU_6502_API
#	if defined(CPU_6502_USE_STATIC)
#		define CPU_6502_API
#	else
#		define CPU_6502_API Z_API
#	endif
#endif

typedef struct {
	zsize	   cycles;
	Z6502State state;
	zuint8	   opcode;
	zuint16	   g_ea;
	zboolean   nmi;
	zboolean   irq;

#	ifdef CPU_6502_USE_SLOTS
		struct {ZSlot(Z16BitAddressRead8Bit ) read;
			ZSlot(Z16BitAddressWrite8Bit) write;
		} cb;
#	else
		void* cb_context;

		struct {Z16BitAddressRead8Bit  read;
			Z16BitAddressWrite8Bit write;
		} cb;
#	endif
} M6502;

Z_C_SYMBOLS_BEGIN

CPU_6502_API extern ZCPUEmulatorABI const abi_cpu_6502;

CPU_6502_API zsize m6502_run   (M6502*	 object,
				zsize	 cycles);

CPU_6502_API void  m6502_power (M6502*	 object,
				zboolean state);

CPU_6502_API void  m6502_reset (M6502*	 object);

CPU_6502_API void  m6502_nmi   (M6502*	 object);

CPU_6502_API void  m6502_irq   (M6502*	 object,
				zboolean state);

Z_C_SYMBOLS_END

#endif /* __emulation_CPU_6502_H__ */