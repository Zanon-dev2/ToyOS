# 🖥️ ToyOS

My journey into bare-metal operating system development! Every operating system in this repository is built from scratch in freestanding C++ without the standard library—and following tradition, each one is named after an anime character.

## 🚀 Evolution of the Project

I have built two hobby operating systems so far, representing a big leap from a simple text-based terminal to a pseudo-graphical desktop environment:

| Folder | OS Name | Architecture & Style | Key Highlights |
| :--- | :--- | :--- | :--- |
| [`00 - Edward`](./00%20-%20Edward) | **Edward** | Text-Mode CLI | Custom I/O streams (`zout`/`zin`), DJB2 password hashing, and an in-memory file system. |
| [`01 - Tanya`](./01%20-%20Tanya) | **Tanya** | Pseudo-Graphical Desktop | Simulates graphics and windows using VGA text-mode cells, featuring a calculator, pixel drawing app, text editor, and a playable Snake game. |

## 🛠️ Shared Technical Architecture

* **Zero Standard Library:** Built with `-ffreestanding` and `-nostdlib`, implementing custom memory helpers, string containers, and inline assembly port I/O (`inb`, `outb`).
* **Direct Hardware Control:** Renders directly to VGA text-mode memory (`0xB8000`, 80×25 grid) and polls raw PS/2 keyboard scan codes (`0x60`/`0x64`).
* **Compile-Time Optimization:** Uses `constexpr` string hashing for fast command parsing.

## 📂 Repository Structure

```text
ToyOS/
├── 00 - Edward/     # First OS: Command-line driven kernel
│   └── README.md
├── 01 - Tanya/      # Second OS: Pseudo-graphical desktop & apps
│   └── README.md
├── LICENSE.md       # MIT License
└── README.md        # Main repository overview
```

## 📄 License

This project is licensed under the **MIT License**.
