# CPU
So this programm simulates the work of Central Proccessing Unit. It has 3 parts: Stack, Translator and actually Cpu.
Let's talk about each of them.
## Stack
This part answers for Stack of Cpu. It has constructor, distructor, push, pop, resize and security verification. The main perpose of verification is to protect the stack safety. It is released by canary technology.
## Translator
This part answers for translation an "assambler" file to numerical file, which will be understandable for Cpu. It is made with the help of #define-s and headers, which seems not to be obvious and readable, but it helps to solve copy-paste problem.
## Cpu
