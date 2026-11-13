# 🦾 Edward OS (`00 - Edward`)

**Edward** is my first hobby operating system—a lightweight, bare-metal x86-64 command-line kernel written from scratch in freestanding C++.

## 📖 Overview

Built to explore direct hardware interaction without an underlying OS or standard library, **Edward** provides a pure text-mode terminal interface. It interacts directly with the VGA text buffer (`0xB8000`) for output and reads raw PS/2 keyboard scan codes (`0x60` and `0x64`) for user input.

## ✨ Features

* **Custom C++ I/O Streams (`zio`, `zout`, `zin`):** Implements `<<` and `>>` stream operators over VGA memory, complete with cursor tracking, automatic scrolling, backspace handling, and Shift-key support.
* **Compile-Time Password Hashing:** Uses a `constexpr` DJB2 hash algorithm to set and verify system passwords without storing plain text in memory.
* **In-Memory File System:** Allows creating, listing, and reading virtual files stored in RAM, with optional password protection per file.

## 💻 Built-in Shell Commands

| Command | Description |
| :--- | :--- |
| `Help` | Displays the list of available shell commands. |
| `defSenha` | Sets or updates the system password (requires current password if already set). |
| `Senha` | Verifies if an entered password matches the stored system password. |
| `hashSenha` | Outputs the numeric DJB2 hash of a given string. |
| `writeAt` | Creates or overwrites a file in memory with optional password locking. |
| `Read` | Reads and displays the contents of a stored file (prompts for password if locked). |
| `ls` | Lists all files currently stored in memory. |
| `Clear` | Clears the VGA screen and resets the cursor position. |

## 🚀 Building & Running

Compile in 64-bit freestanding mode without the C++ standard library or runtime exceptions, then link with your bootloader (e.g., GRUB/Multiboot):

```bash
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti -O2 -c toy.cpp -o toy.o
# Link toy.o with your bootloader assembly and boot in QEMU:
qemu-system-i386 -kernel edward.bin
```

---
