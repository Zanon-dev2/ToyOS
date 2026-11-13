# 🎖️ Tanya OS (`01 - Tanya`)

**Tanya** is my second hobby operating system—a major leap forward from **Edward**. Instead of a plain command prompt, **Tanya** uses the 80×25 VGA text-mode driver to simulate a full pseudo-graphical desktop environment with windows, icons, pixel art, and interactive apps.

## 📖 Overview

Written in freestanding C++ with zero external dependencies, **Tanya** introduces a custom dynamic string class (`var::ztring`), a pseudo-random number generator, window rendering primitives, and a desktop workspace navigable entirely via keyboard.

## 🖥️ Desktop & Built-in Applications

* **Workspace Launcher:** Navigate desktop icons using the arrow keys (or `I`/`J`/`K`/`L`) and press `Enter` to launch applications.
* **Terminal:** Interactive command shell featuring system password management (`defPassword`), screen clearing (`Clean`), and command help (`Help`).
* **Calculator:** Supports 64-bit integer addition (`+`), subtraction (`-`), multiplication (`*`), and formatted division (`/`) with decimal precision.
* **Files & Media Suite:**
  * **Draw:** An 80×25 VGA color-block pixel editor supporting 16 background colors (`0–9`, `A–F`), cursor movement, and optional password locking when saving (`P`).
  * **Zimgs:** Image gallery viewer to browse and unlock saved VGA pixel drawings.
  * **Write:** Multi-line text editor supporting custom titles, line breaks, and optional password protection.
  * **Texts:** Document reader to open and view saved text files.
* **Snake Game:** A playable VGA Snake game featuring wall and self-collision detection, score tracking (*Current*, *Last*, and *Best* scores), and real-time speed control (`W` to speed up, `S` to slow down).

## 🎮 Controls

* **Navigation:** Arrow Keys or `I` (Up), `K` (Down), `J` (Left), `L` (Right)
* **Select / Confirm:** `Enter`
* **Exit / Back to Desktop:** `Esc` (or `Q` inside Snake)

## 🚀 Building & Running

Compile in 64-bit freestanding mode without standard libraries or RTTI, link with your bootloader, and test on an emulator like QEMU:

```bash
nasm -f elf64 boot.asm -o boot.o && g++ -m64 -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -mno-red-zone -c Tanya.cpp -o Tanya.o && \
ld -m elf_x86_64 -T linker.ld boot.o Tanya.o -o mykernel.bin --no-warn-rwx-segments -z noexecstack && \
cp mykernel.bin raiz/boot/mykernel.bin && \
grub-mkrescue -o Tanya.iso raiz && \
qemu-system-x86_64 -cdrom Tanya.iso -boot d -no-reboot
```

---
Part of the [ToyOS](../README.md) project by [Zanon-dev2](https://github.com/Zanon-dev2).
