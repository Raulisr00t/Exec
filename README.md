# 🔧 EXEC - TinyCC JIT Executor

A minimal example of using [TinyCC (TCC)](https://bellard.org/tcc/) as a JIT (Just-In-Time) compiler to execute C code at runtime — written in C, using the `libtcc` API.

---

## ✨ Features

- Embeds and compiles C code on the fly
- Relocates and executes dynamically at runtime
- Uses `libtcc` (TinyCC API)
- Works on **Linux** and can be compiled for **Windows**

---

## 🧱 Requirements

- **Linux** or **Windows**
- `libtcc-dev` (TinyCC development library)

### On Debian/Ubuntu:

```bash
sudo apt install tcc libtcc-dev
```

## 🛠️ Build
On Linux:
```bash
gcc exec.c -ltcc -ldl -o exec
```

On Windows (MinGW):
```bash
gcc exec.c -ltcc -o exec.exe
.\exec.exe
```

Cross-compiling for Windows on Linux:
```bash
x86_64-w64-mingw32-gcc exec.c -ltcc -o exec.exe
```

🧪 Example Output
```bash
Code :
void run() {
printf("Hello from Raul!\nWhat do you think about JIT in C");
}

Hello from Raul!
What do you think about JIT in C
```

### 📚 Resources
TinyCC Website -> https://bellard.org/tcc/

libtcc API Reference -> https://repo.or.cz/tinycc.git/blob/HEAD:/libtcc.h

## ⚠️ Notes
This example uses tcc_add_symbol() to expose standard C functions like printf to the JIT'd code.

Ensure your system libtcc.a and libtcc1.a are correctly linked if building manually.
