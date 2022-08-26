#!/usr/bin/make -f

APP_NAME=app

ARCH= linux
CPUTYPE= posix
CPU= none

ARCH_DIR?= $(ARCH)
CPUTYPE_DIR?= $(CPUTYPE)

DEF_ARCH?= ARCH_$(shell echo '$(ARCH)' | tr '[:lower:]' '[:upper:]')
DEF_CPUTYPE?= CPUTYPE_$(shell echo '$(CPUTYPE)' | tr '[:lower:]' '[:upper:]')
DEF_CPU?= CPU_$(shell echo '$(CPU)' | tr '[:lower:]' '[:upper:]')

NUMCPUS=$(shell grep -c '^processor' /proc/cpuinfo)

MCU_FLAGS = 

TRGT = 
CC   = $(TRGT)gcc
CXX  = $(TRGT)g++

ARCH_NAME:=$(shell '$(TRGT)gcc' -dumpmachine)

ifeq ($(strip $(ARCH_NAME)),)
ARCH_NAME:=unknown
endif

CURDIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BASEDIR:=$(CURDIR)/../..

OUT_DIR:=$(CURDIR)/$(ARCH_NAME)/out
OBJ_DIR:=$(CURDIR)/$(ARCH_NAME)/obj
CFG_DIR:=$(CURDIR)/$(ARCH_NAME)/config

SRC_DIR:=$(CURDIR)/app/src
OIL_DIR:=$(CURDIR)/app/oil
OSEK_DIR:=$(CURDIR)/common/osek
TOOLS_DIR:=$(CURDIR)/tools

LD   = $(TRGT)gcc

CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
MOT  = $(CP) -O srec
BIN  = $(CP) -O binary

RM   = rm --force --verbose

PHP = php

PYTHON = python3

OIL_GENERATOR:=$(PHP) $(TOOLS_DIR)/generator/generator.php

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-value

# Define C++ warning options here.
CPPWARN = -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-value

# Compiler options here.
OPTS = \
	-O2 \
	-gdwarf-2 \
	-rdynamic \
	-fomit-frame-pointer \
	-fdiagnostics-color=always

# ASM specific options here.
ASM_OPTS = 

# C specific options here.
C_OPTS = 

# C++ specific options here.
CXX_OPTS = 

# Enable this if you want the linker to remove unused code and data.
USE_LINK_GC = yes

# Linker options here.
LD_OPTS = \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-Wl,--cref,--no-warn-mismatch,--library-path=,--gc-sections \
	-Wl,-Map="$(OUT_DIR)/$(APP_NAME).map"

CFLAGS= \
	-fwrapv \
	-fstack-protector-strong \
	-fdata-sections \
	-ffunction-sections \
	-fno-strict-aliasing \
	-Wformat \
	-Werror=format-security \
	-Wdate-time \
	-D_FORTIFY_SOURCE=2 \
	-no-pie

LDFLAGS= \
	-Wl,-O1 \
	-Wl,-Bsymbolic-functions \
	-Wl,-z,relro \
	-Wl,-z,now \
	-Wl,--as-needed \
	-Wl,--no-undefined \
	-Wl,--no-allow-shlib-undefined \
	-Wl,-Bsymbolic-functions \
	-Wl,--dynamic-list-cpp-new \
	-Wl,--dynamic-list-cpp-typeinfo \
	-no-pie

LIBS= -lpthread -lm

CSTD=-std=gnu99
CPPSTD=-std=gnu++98

DEFS= \
	-DARCH=$(DEF_ARCH) \
	-DCPUTYPE=$(DEF_CPUTYPE) \
	-DCPU=$(DEF_CPU) \
	-DDEBUG

INCS= \
	-I "$(CFG_DIR)/inc/$(ARCH_DIR)/" \
	-I "$(CFG_DIR)/inc/" \
	-I "$(CURDIR)/inc/$(ARCH_DIR)/$(CPUTYPE_DIR)/" \
	-I "$(CURDIR)/inc/$(ARCH_DIR)/" \
	-I "$(CURDIR)/inc/" \
	-I "$(CURDIR)/app/inc/" \
	-I "$(SRC_DIR)/"

OBJS= \
	$(OBJ_DIR)/app/Os_Cfg.o \
	$(OBJ_DIR)/app/Os_Internal_Cfg.o \
	$(OBJ_DIR)/app/$(ARCH_DIR)/Os_Internal_Arch_Cfg.o \
	$(OBJ_DIR)/app/main.o \
	$(OBJ_DIR)/osek/$(ARCH_DIR)/Os_Arch.o \
	$(OBJ_DIR)/osek/$(ARCH_DIR)/Os_Internal_Arch.o \
	$(OBJ_DIR)/osek/$(ARCH_DIR)/StartOs_Arch.o \
	$(OBJ_DIR)/osek/ActivateTask.o \
	$(OBJ_DIR)/osek/CancelAlarm.o \
	$(OBJ_DIR)/osek/ChainTask.o \
	$(OBJ_DIR)/osek/ClearEvent.o \
	$(OBJ_DIR)/osek/GetActiveApplicationMode.o \
	$(OBJ_DIR)/osek/GetAlarmBase.o \
	$(OBJ_DIR)/osek/GetAlarm.o \
	$(OBJ_DIR)/osek/GetEvent.o \
	$(OBJ_DIR)/osek/GetResource.o \
	$(OBJ_DIR)/osek/GetTaskID.o \
	$(OBJ_DIR)/osek/GetTaskState.o \
	$(OBJ_DIR)/osek/Os.o \
	$(OBJ_DIR)/osek/Os_Internal.o \
	$(OBJ_DIR)/osek/ReleaseResource.o \
	$(OBJ_DIR)/osek/Schedule.o \
	$(OBJ_DIR)/osek/SetAbsAlarm.o \
	$(OBJ_DIR)/osek/SetEvent.o \
	$(OBJ_DIR)/osek/SetRelAlarm.o \
	$(OBJ_DIR)/osek/ShutdownOS.o \
	$(OBJ_DIR)/osek/StartOS.o \
	$(OBJ_DIR)/osek/TerminateTask.o \
	$(OBJ_DIR)/osek/WaitEvent.o


all: $(OUT_DIR)/$(APP_NAME).elf

$(OUT_DIR)/$(APP_NAME).elf: $(OBJS) $(LD_OBJS)
	@mkdir -p "$$(dirname '$@')"
	$(LD) $(CPPSTD) $(CSTD) $(MCU_FLAGS) $(OPTS) $(LD_OPTS) $(LDFLAGS) -o $@ $+ $(LIBS)

# See: https://makefiletutorial.com/

%.hex: %.elf
	$(CP) -O ihex $< $@

%.mot: %.elf
	$(CP) -O srec $< $@

%.bin: %.elf
	$(CP) -O binary $< $@

%.dmp: %.elf
	$(OD) -x --syms $< > $@


$(OBJ_DIR)/app/%.o: $(CFG_DIR)/src/%.c
	@mkdir -p "$$(dirname '$@')"
	$(CC) $(CSTD) $(MCU_FLAGS) $(OPTS) $(C_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)


$(OBJ_DIR)/app/%.o: $(SRC_DIR)/%.s
	@mkdir -p "$$(dirname '$@')"
	$(AS) $(CSTD) $(MCU_FLAGS) $(OPTS) $(ASM_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/app/%.o: $(SRC_DIR)/%.c
	@mkdir -p "$$(dirname '$@')"
	$(CC) $(CSTD) $(MCU_FLAGS) $(OPTS) $(C_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/app/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p "$$(dirname '$@')"
	$(CXX) $(CPPSTD) $(MCU_FLAGS) $(OPTS) $(CXX_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CPPWARN)


$(OBJ_DIR)/osek/%.o: $(CURDIR)/src/%.s
	@mkdir -p "$$(dirname '$@')"
	$(AS) $(CSTD) $(MCU_FLAGS) $(OPTS) $(ASM_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/osek/%.o: $(CURDIR)/src/%.c
	@mkdir -p "$$(dirname '$@')"
	$(CC) $(CSTD) $(MCU_FLAGS) $(OPTS) $(C_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/osek/%.o: $(CURDIR)/src/%.cpp
	@mkdir -p "$$(dirname '$@')"
	$(CXX) $(CPPSTD) $(MCU_FLAGS) $(OPTS) $(CXX_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CPPWARN)


$(OBJ_DIR)/%.o: %.s
	@mkdir -p "$$(dirname '$@')"
	$(AS) $(CSTD) $(MCU_FLAGS) $(OPTS) $(ASM_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p "$$(dirname '$@')"
	$(CC) $(CSTD) $(MCU_FLAGS) $(OPTS) $(C_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CWARN)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p "$$(dirname '$@')"
	$(CXX) $(CPPSTD) $(MCU_FLAGS) $(OPTS) $(CXX_OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(CPPWARN)


$(CFG_DIR) \
$(CFG_DIR)/inc/Os_Cfg.h \
$(CFG_DIR)/src/Os_Cfg.c \
$(CFG_DIR)/inc/Os_Internal_Cfg.h \
$(CFG_DIR)/src/Os_Internal_Cfg.c \
$(CFG_DIR)/inc/$(ARCH_DIR)/Os_Internal_Arch_Cfg.h \
$(CFG_DIR)/src/$(ARCH_DIR)/Os_Internal_Arch_Cfg.c:
	mkdir -p '$(CFG_DIR)/inc'
	mkdir -p '$(CFG_DIR)/src'
	$(OIL_GENERATOR) \
		--cmdline -l -v \
		-DARCH='$(ARCH)' \
		-DCPUTYPE='$(CPUTYPE)' \
		-DCPU='$(CPU)' \
		-c '$(OIL_DIR)/config.oil' \
		-t '$(CURDIR)/gen/inc/Os_Internal_Cfg.h.php' \
		'$(CURDIR)/gen/inc/Os_Cfg.h.php' \
		'$(CURDIR)/gen/src/Os_Cfg.c.php' \
		'$(CURDIR)/gen/src/Os_Internal_Cfg.c.php' \
		'$(CURDIR)/gen/src/$(ARCH_DIR)/Os_Internal_Arch_Cfg.c.php' \
		'$(CURDIR)/gen/inc/$(ARCH_DIR)/Os_Internal_Arch_Cfg.h.php' \
		-H '$(CURDIR)/gen/ginc/Multicore.php' \
		-o '$(CFG_DIR)'


disasm: all
	cp $(OUT_DIR)/$(APP_NAME).elf $(OUT_DIR)/$(APP_NAME).strip.elf
	$(OD) -D $(OUT_DIR)/$(APP_NAME).strip.elf


clean:
	$(RM) $(OBJS)
	$(RM) --recursive "$(CFG_DIR)/inc/"
	$(RM) --recursive "$(CFG_DIR)/src/"
	$(RM) --recursive  $(OUT_DIR)/ $(OBJ_DIR)/ $(CFG_DIR)/ $(CURDIR)/$(ARCH_NAME)/
	@find . -name '*.o' -exec $(RM) {} +
	@find . -name '*.a' -exec $(RM) {} +
	@find . -name '*.so' -exec $(RM) {} +
	@find . -name '*.map' -exec $(RM) {} +
	@find . -name '*.elf' -exec $(RM) {} +
	@find . -name '*.hex' -exec $(RM) {} +
	@find . -name '*.bin' -exec $(RM) {} +
	@find . -name '*.dmp' -exec $(RM) {} +
	@find . -name '*.pyc' -exec $(RM) {} +
	@find . -name '*.pyo' -exec $(RM) {} +
	@find . -name '*.bak' -exec $(RM) {} +
	@find . -name '*.core' -exec $(RM) {} +
	@find . -name '*~' -exec $(RM) {} +
	@$(RM) core

.PHONY: all clean disasm
