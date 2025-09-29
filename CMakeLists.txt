cmake_minimum_required(VERSION 3.20)

# explizit Standard-Compiler setzen
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_ASM_NASM_COMPILER nasm)

project(KernalOS CXX ASM_NASM)

set(CMAKE_CXX_STANDARD 20)

# Verzeichnisse
set(SRC_DIR ${CMAKE_SOURCE_DIR}/kernel/src)
set(DRIVER_DIR ${CMAKE_SOURCE_DIR}/driver/video/VGA)
set(KEYBOARD_DIR ${CMAKE_SOURCE_DIR}/driver/input/Keyboard)   # <— NEU
set(BUILD_DIR ${CMAKE_BINARY_DIR})
set(ISO_DIR ${BUILD_DIR}/iso)

enable_language(ASM_NASM)

# Boot.asm → boot.o
set(BOOT_OBJ ${BUILD_DIR}/boot.o)
add_custom_command(
        OUTPUT ${BOOT_OBJ}
        COMMAND nasm -f elf32 ${SRC_DIR}/boot.asm -o ${BOOT_OBJ}
        DEPENDS ${SRC_DIR}/boot.asm
)

# Kernel.cpp + Treiber → Objekte
set(KERNEL_OBJS
        ${BUILD_DIR}/kernel.o
        ${BUILD_DIR}/VgaDriver.o
)

add_custom_command(
        OUTPUT ${BUILD_DIR}/kernel.o
        COMMAND ${CMAKE_CXX_COMPILER} -m32 -ffreestanding -fno-pic -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -c ${SRC_DIR}/kernel.cpp -o ${BUILD_DIR}/kernel.o
        DEPENDS ${SRC_DIR}/kernel.cpp
)

add_custom_command(
        OUTPUT ${BUILD_DIR}/VgaDriver.o
        COMMAND ${CMAKE_CXX_COMPILER} -m32 -ffreestanding -fno-pic -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -c ${DRIVER_DIR}/VgaDriver.cpp -o ${BUILD_DIR}/VgaDriver.o
        DEPENDS ${DRIVER_DIR}/VgaDriver.cpp
)

# --- NEU: Keyboard.cpp bauen und einlinken ---
add_custom_command(
        OUTPUT ${BUILD_DIR}/Keyboard.o
        COMMAND ${CMAKE_CXX_COMPILER} -m32 -ffreestanding -fno-pic -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -c ${KEYBOARD_DIR}/keyboard.cpp -o ${BUILD_DIR}/Keyboard.o
        DEPENDS ${KEYBOARD_DIR}/keyboard.cpp
)
list(APPEND KERNEL_OBJS ${BUILD_DIR}/Keyboard.o)

# (Optional) IRQ1-Stub, falls vorhanden
# set(KBD_STUB_OBJ ${BUILD_DIR}/isr_keyboard.o)
# add_custom_command(
#         OUTPUT ${KBD_STUB_OBJ}
#         COMMAND nasm -f elf32 ${KEYBOARD_DIR}/isr_keyboard.asm -o ${KBD_STUB_OBJ}
#         DEPENDS ${KEYBOARD_DIR}/isr_keyboard.asm
# )
# list(APPEND KERNEL_OBJS ${KBD_STUB_OBJ})

# Linken → kernel.bin
set(KERNEL_BIN ${BUILD_DIR}/kernel.bin)
add_custom_command(
        OUTPUT ${KERNEL_BIN}
        COMMAND ld -m elf_i386 -T ${SRC_DIR}/linker.ld -nostdlib -o ${KERNEL_BIN} ${BOOT_OBJ} ${KERNEL_OBJS}
        DEPENDS ${BOOT_OBJ} ${KERNEL_OBJS} ${SRC_DIR}/linker.ld
)

add_custom_target(kernel ALL DEPENDS ${KERNEL_BIN})

# ISO erstellen
set(KERNEL_ISO ${BUILD_DIR}/kernel.iso)
add_custom_command(
        OUTPUT ${KERNEL_ISO}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${KERNEL_BIN} ${ISO_DIR}/boot/kernel.bin
        COMMAND ${CMAKE_COMMAND} -E echo "set timeout=0" > ${ISO_DIR}/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E echo "set default=0" >> ${ISO_DIR}/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E echo "menuentry \"My Kernel\" { multiboot /boot/kernel.bin }" >> ${ISO_DIR}/boot/grub/grub.cfg
        COMMAND grub-mkrescue -o ${KERNEL_ISO} ${ISO_DIR}
        DEPENDS ${KERNEL_BIN}
)
add_custom_target(iso ALL DEPENDS ${KERNEL_ISO})

# QEMU Run Target
add_custom_target(run
        COMMAND qemu-system-i386 -cdrom ${KERNEL_ISO}
        DEPENDS iso
)
