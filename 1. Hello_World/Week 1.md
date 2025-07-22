# Module 1: Getting Started With C

Welcome to C. This is the foundation of everything else you’ll do in this course, and arguably, much of modern computing itself.

---

## What Is C? Why Does It Matter?

C is a **low-level, high-performance programming language** created in the early 1970s by Dennis Ritchie at Bell Labs. It was used to write **UNIX**, and its design directly influenced most modern languages: C++, Java, Rust, Go, and even Python (which is implemented in C under the hood).

Why C still matters:
- **Speed**: C compiles to raw machine code. There’s no runtime like Python or Java.
- **Control**: You can manage memory directly. No garbage collector. This is a double-edged sword.
- **Relevance**: C is the backbone of systems programming, operating systems, embedded development, reverse engineering, and CNO (Cyber Network Operations).

> If you're trying to understand how software *really* works — how it talks to hardware, where bugs and vulnerabilities live — C is the right place to start.

---

## Setting Up Your C Development Environment

You’ll need a compiler, a terminal, and a text editor. Here’s the simplest setup for a Unix-like environment (Linux, macOS, or WSL on Windows):

### Step 1: Install GCC or Clang
```bash
# Debian/Ubuntu
sudo apt update && sudo apt install build-essential
```
#### Fedora
```bash
sudo dnf groupinstall "Development Tools"
```
#### macOS (via Homebrew)
```bash
brew install gcc
```
You can verify installation with:

```bash
gcc --version
clang --version
```

---

## Step 2: Choose a Text Editor
Recommended:

VSCode: Lightweight but powerful, with C/C++ extensions.

Vim or Neovim: For terminal power-users.

Emacs: Popular among academics and hackers.

---

Step 3: Create Your Workspace
```bash
mkdir ~/Learning-C && cd ~/Learning-C
```
## Writing Your First C Program
Save this as hello.c:

```c
#include <stdio.h>
int main() {
    printf("Hello, world!\n");
    return 0;
}
```
Compile and run:

```bash

gcc hello.c -o hello
./hello
```
---

Understanding Errors, Warnings, and Compiler Flags
Compilation Errors
Syntax mistakes will stop the compiler cold. Example:

c ```
printf("Hello"  // missing semicolon and closing parenthesis
```
You’ll get errors like:

``` css
error: expected ‘;’ before ‘}’
```
## Warnings
Warnings don't stop compilation, but they indicate potential bugs. Always enable them:

``` bash
gcc -Wall -Wextra -o myprog myprog.c
```
## Common Compiler Flags
-o output: Set output binary name

-Wall: Show common warnings

-g: Include debug info for tools like gdb

-O0 to -O3: Set optimization level

---

Why the Command Line Matters
In C, you’re close to the metal. The terminal is your cockpit:

Run and compile programs

Debug using gdb

Use tools like strace, objdump, and valgrind

Set environment variables and pass CLI arguments

Mastering the command line is non-negotiable if you want to become proficient in systems programming, reverse engineering, or offensive security.

---

## Next Steps
### You should now:

Know what C is and why it matters

Have a working compiler and workspace

Be able to write and run a basic C program

Understand compiler warnings and errors

Be comfortable using the command line

---

## 🧠 Check Yourself
What is C primarily used for?

Why are compiler warnings just as important as errors?

Can you compile a file called test.c into an executable named out?

What does return 0 do in main()?

What happens if you omit a semicolon in your code?

---

## ✅ Practice
Write a program that prints your name and age.

Write a program that prints two integers and their sum.

Try compiling your program with -Wall and intentionally introduce a warning.

Explore: What happens if you call main() from inside main()?

