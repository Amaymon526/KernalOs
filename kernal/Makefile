CXX = g++
AS = nasm
LD = ld -m elf_i386
CXXFLAGS = -m32 -ffreestanding -fno-pic -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib
LDFLAGS = -T src/linker.ld -nostdlib


SRC = src
BUILD = build
ISO = iso

build: $(ISO)/kernel.iso

$(BUILD)/boot.o: $(SRC)/boot.asm
	mkdir -p $(BUILD)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel.o: $(SRC)/kernel.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/kernel.bin: $(BUILD)/boot.o $(BUILD)/kernel.o
	$(LD) $(LDFLAGS) -o $@ $^

$(ISO)/kernel.iso: $(BUILD)/kernel.bin
	mkdir -p $(ISO)/boot/grub
	cp $< $(ISO)/boot/kernel.bin
	echo 'set timeout=0' > $(ISO)/boot/grub/grub.cfg
	echo 'set default=0' >> $(ISO)/boot/grub/grub.cfg
	echo 'menuentry "My Kernel" { multiboot /boot/kernel.bin }' >> $(ISO)/boot/grub/grub.cfg
	grub-mkrescue -o build/kernel.iso $(ISO)


run: $(ISO)/kernel.iso
	qemu-system-i386 -cdrom $<
