# Assembler to Machine Code Translation and Simulation

## Overview

This project aims to translate a program written in assembly language into its equivalent hexadecimal machine code and then simulate its execution.  
It was developed as part of the **Computer Architecture** course at Université Paris Dauphine.

## Key Features

- **Translation: Assembly → Hexadecimal Machine Code**  
- **Execution of Hexadecimal Program**  
- **Interactive Menu** with stylized terminal display (colors, ASCII art)  
- **Error Detection** during translation and execution (syntax errors, stack overflow/underflow, illegal memory access, etc.)  
- **Label Management** for jump instructions

## Project Structure

```
Projet_Archi/
├── Source/
│   ├── assembleur_to_machine.c
│   ├── assembleur_to_machine.h
│   ├── executeur.c
│   ├── executeur.h
│   ├── main.c
├── exemples/         # Example assembly files
└── README.md
```

- `main.c`: Manages the menu and user interface.
- `assembleur_to_machine.c / .h`: Handles translation from assembly to hexadecimal.
- `executeur.c / .h`: Handles execution of the hexadecimal file.

## Installation

1. **Clone the repository:**

```bash
git clone https://github.com/your-username/projet-archi.git
cd projet-archi
```

2. **Compile:**

```bash
gcc Source/main.c Source/assembleur_to_machine.c Source/executeur.c -o executeur
```

3. **Run:**

```bash
./executeur
```

## How to Use

1. Launch the executable.
2. Select an assembly file from the examples or provide your own.
3. The program translates the file into hexadecimal (`hexa.txt`).
4. The simulator executes this file and displays results in the terminal.

## Examples

Example assembly files are available in the `exemples/` folder.

## Known Bugs and Possible Improvements

- No support for comments (`;`) in assembly code.
- No automatic correction of label typos.
- Potential complexity handling nested loops during error detection.

**Ideas for Improvements:**  
- Add typo detection in labels (e.g., using Levenshtein distance).
- Better memory management for very large files.

## Developers

- **William Miserolle**
- **Nicolas de Pellegars Malhortie**

---

*Project completed in April 2025.*
