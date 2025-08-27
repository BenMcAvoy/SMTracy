# SMTracy

SMTracy is a DLL mod for Scrap Mechanic that demonstrates advanced profiling and memory instrumentation using Tracy and MinHook. This project hooks memory allocation functions (`malloc` and `realloc`) in the Scrap Mechanic process, enabling real-time profiling of memory usage via Tracy zones. MinHook is used for reliable function interception at runtime.

## Features

- **Profiling with Tracy:** Injects Tracy zones into CRT memory allocation functions for live performance and allocation profiling.
- **Function Hooking:** Uses MinHook to hook and redirect allocation calls, allowing for detailed instrumentation of memory operations.
- **DLL Injection Utility:** Includes a DebugInjector tool that automates the process of injecting DLLs into the Scrap Mechanic game process.
- **Console Logging:** Optional debug console for runtime logging and diagnostics.

## How It Works

1. **DLL Injection:** The DebugInjector utility detects when Scrap Mechanic starts and injects the DLL(s) into the process automatically.
2. **Hook Setup:** On DLL load, MinHook initializes hooks for `malloc` and `realloc`. These hooks wrap the functions with Tracy profiling zones.
3. **Profiling:** All calls to `malloc` and `realloc` are profiled, allowing developers to analyze the game's memory allocation behavior in detail.

## Building & Usage

1. Clone this repository.
2. Open `SMTracy.sln` in Visual Studio.
3. Build the solution. This will produce the DLL and the injector utility.
4. Launch the DebugInjector. It will wait for Scrap Mechanic to start and inject the DLL automatically.
5. Use Tracy's viewer to analyze the profiling data captured during gameplay.

## Modifying

- Make changes to the DLL logic in `SMTracy/src/dllmain.cpp`.
- The DebugInjector logic is in `DebugInjector/src/main.cpp`.
- For logging, see `SMTracy/include/log.h`.

## License

SMTracy is released under the MIT license. See [LICENSE](LICENSE) for details.

---

For questions or contributions, open an issue or pull request!
