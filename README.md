# KernalOS – Minimal Operating System Kernel

KernalOS is a hobby operating system project built from scratch with **C++** and **x86 Assembly**.  
The main goal is to learn the fundamentals of operating system development by gradually adding functionality step by step.

Currently, the kernel boots through GRUB, enters 32-bit protected mode, and displays a simple "Hello World" in VGA text mode.  
This project follows the **Multiboot specification** so that it can be booted easily using GRUB and tested in QEMU.

---

## ✨ Current Features
- Multiboot-compatible kernel (GRUB can boot it directly)
- Minimal bootloader (`boot.asm`)
- VGA text mode output (`Hello World from my kernel!`)
- Clean project structure:
    - `src/` → source files (C++/ASM + headers + linker script)
    - `build/` → build artifacts (`.o`, `.bin`, `.iso`)
    - `iso/` → bootable ISO filesystem layout
- Automated build system using `Makefile`
- Bootable ISO generated with `grub-mkrescue`
- Runs in QEMU on Linux and Windows (via WSL)

---

## 🔧 Requirements

### Linux (Debian/Ubuntu recommended)
Install the required toolchain and utilities:

```bash
sudo apt update
sudo apt install build-essential gcc-multilib g++-multilib nasm \
                 xorriso mtools grub-pc-bin qemu-system
```
### Windows
The recommended setup is **WSL2 (Windows Subsystem for Linux)**, since all build scripts rely on Linux tools.

1. [Install WSL2](https://learn.microsoft.com/en-us/windows/wsl/install)
2. Install Ubuntu from the Microsoft Store
3. Run the Linux setup commands (from above) inside your WSL terminal

Optional:  
If you want to run QEMU on Windows natively, download:
- [QEMU for Windows](https://qemu.weilnetz.de/w64/)  
- [NASM for Windows](https://www.nasm.us/pub/nasm/releasebuilds/)  
- [GNU Binutils (via MSYS2/MinGW)](https://www.msys2.org/)  

⚠️ Note: Native Windows setup is more complex. WSL2 is highly recommended.

---

## ▶️ Building & Running

Clone the project:
```bash
git clone https://github.com/<your-username>/KernalOs.git
cd KernalOs/kernal
```
Build the kernel:
```bash
make
```
Run the kernel in QEMU:
```bash
make run
```

---

## 📅 Roadmap / Planned Features

### 🛠 Tooling
- [ ] Build a proper **cross-compiler (`i686-elf-gcc`)** instead of relying on host `g++ -m32`
- [ ] Improve build scripts and CI/CD for GitHub

### 🧩 Kernel Core
- [ ] VGA text console library (cursor movement, multiple lines, scrolling)
- [ ] Basic memory management
    - [ ] Paging (virtual memory)
    - [ ] Heap allocator

### ⌨️ Drivers
- [ ] PIT (Programmable Interval Timer) → required for multitasking & precise timing
- [ ] PIC (Programmable Interrupt Controller) → for hardware IRQ handling
- [ ] PS/2 Keyboard driver → to handle user input
- [ ] (optional) Disk drivers (ATA/SATA) for basic storage support
- [ ] Later: Mouse, Serial (COM), simple framebuffer graphics

### 💻 OS Functionality
- [ ] Simple kernel shell (command-line interface)
- [ ] Task switching / multitasking
- [ ] Userland support (running simple programs)

---
