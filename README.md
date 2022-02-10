# Ret Spoofing
A simple and minimalistic way to spoof return addresses without using an exception handler

# Pros & Cons
Pros:
* Very easy to implement
* Very easy to use
* Little to no performance decrease

Cons:
* Relies on the preservation of the nonvolatile GPRs of the x64 calling convention
  * Which in this case means it always expects these registers to be preserved, in very rare cases it might not be
  * Read [MSDN Documentation for Caller/Callee Saved registers](https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170#callercallee-saved-registers)
