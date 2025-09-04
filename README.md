# Crime Investigation System — README

A small client–server project demonstrating OOP, exceptions, and sockets:

- **C++ (client)**: console menu app (Windows/WinSock) that manages detectives & suspects and can query a server.
- **Python (server)**: simple TCP server that returns info for a suspect name.

This README is a *work log / how‑to* for the files you provided.

---

## Contents (files you shared)

**C++ (headers + main)**
- `main.cpp` — Menu UI; seeds detectives & suspects; allows search; can query server.
- `InvestigationControl.h` — Controller managing vectors of `Detective` and `Suspect`, search logic, and output helpers.
- `Person.h` — Abstract base with `name`, `age`, and pure virtual `describe()`.
- `Detective.h` — Derived from `Person`, adds `skill`, overrides `describe()`.
- `Suspect.h` — Derived from `Person`, adds `alibi`, `caughtBy`, `reasonCaught`, `isGuilty`, overrides `describe()`.
- `CustomExceptions.h` — `EmptyCaseException`, `SuspectNotFoundException`, `InvalidInputException`, `ServerQueryException`.
- `WinsockClient.h` — WinSock client (`initialize`, `connectToServer`, `sendAndReceive`, `cleanup`) using `InetPton`.
- `Evidence.h` — Simple evidence class with `showEvidence()`.
- `Case.h` — Aggregates suspects & evidence; `showDetails()` (not yet used by `main.cpp`).

**Python (server)**
- `server.py` — TCP server on `127.0.0.1:8080` with a small in‑memory suspect DB.

> Note: The C++ code is header‑only (no `.cpp` beside `main.cpp`). Ensure all headers are in the same folder, or add include paths accordingly.

---

## Quick Start

### 1) Start the Python server
Requirements: Python 3.9+

```bash
# (Recommended) create a virtual environment, then:
python server.py
```
You should see:
```
Server is running on 127.0.0.1:8080...
```

### 2) Build the C++ client (Windows)

**Option A — Visual Studio (MSVC)**  
- Create a *Console App* project (C++17 or later).
- Add all `.h` headers and `main.cpp` to the project.
- Ensure **C++ Language Standard** is set to `/std:c++17` or newer.
- Linking: `WinsockClient.h` already has `#pragma comment(lib, "ws2_32.lib")`, so no manual linker step is required.
- Build and run.

**Option B — MSVC command line**
```bat
cl /std:c++17 /EHsc main.cpp /Fe:client.exe
client.exe
```

**Option C — MinGW‑w64 (g++)**
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o client.exe main.cpp -lws2_32
./client.exe
```

> ⚠️ The client uses **WinSock**; building on Linux/macOS without porting will fail. For cross‑platform sockets, consider rewriting `WinsockClient` with BSD sockets or Boost.Asio.

---

## How it works

### Python server (`server.py`)
- Listens on `127.0.0.1:8080`
- Accepts a single line (suspect name) from a client.
- Looks up the name in the `suspects` dict and returns a text description or `"Suspect not found!"`.

### C++ client (`main.cpp`)
- Seeds **10 detectives** and **10 suspects**.
- Menu options:
  1. View Suspect Database
  2. View Detective Database
  3. Search for a Suspect (local data; throws `SuspectNotFoundException` if missing)
  4. Query Server for Suspect Information (TCP to Python server)
  5. Exit

**Query flow (menu option 4):**
1. User enters suspect name.  
2. `WinsockClient.initialize("127.0.0.1", 8080)`  
3. `connectToServer()`  
4. `sendAndReceive(name)` → prints server response  
5. `cleanup()`

---

## Example session

**Server (terminal 1):**
```
$ python server.py
Server is running on 127.0.0.1:8080...
Connection from ('127.0.0.1', 54321)
Received query: John Doe
```

**Client (terminal 2):**
```
--- Crime Investigation System Menu ---
1. View Suspect Database
2. View Detective Database
3. Search for a Suspect
4. Query Server for Suspect Information
5. Exit
Enter your choice: 4

Enter the suspect's name to query: John Doe
Attempting to connect to server...
Connected to server successfully!
Sending query to server: John Doe
Response received from server.
Server Response: Caught with fingerprints on the safe. Status: Guilty.
```

---

## Architecture & Design Notes

- **OOP & Polymorphism**: `Person` is abstract; `Detective` & `Suspect` override `describe()`.  
- **Controller**: `InvestigationControl` owns collections and exposes domain operations (SRP).  
- **Error handling**: custom exceptions report empty datasets and search failures.  
- **Networking**: `WinsockClient` encapsulates connection lifecycle.  
- **Extensibility**: `Case` and `Evidence` are ready for future features (link suspects ↔ evidence, multiple cases).

### Invariants / Assumptions
- Names are unique identifiers in the simple, in‑memory demo.
- Server returns plain text (no protocol framing beyond a single send/recv).

---

## Build/Run Troubleshooting

- **“Failed to connect to server.”**  
  - Ensure the Python server is running and the port `8080` is free.
  - Check Windows Firewall; allow both Python and your client app.
- **`Invalid IP address.` from `InetPton`**  
  - Keep server IP as `"127.0.0.1"` or use a valid IPv4 literal.
- **Unicode conversion (`codecvt`) warnings**  
  - `std::codecvt` is deprecated in C++17 and removed in C++20. If you build with C++20+, replace the converter with `MultiByteToWideChar` (WinAPI) or switch `InetPtonA` (ANSI) to avoid wide conversion.
- **MinGW link errors about WinSock**  
  - Ensure `-lws2_32` is the **last** argument to g++ link line.
- **Server returns “Suspect not found!”**  
  - The Python dict currently has only `John Doe`, `Jane Smith`, `Robert Brown`. Add more entries to match your seeded suspects, e.g.:
    ```python
    suspects["Emily White"] = "Her DNA was found on the weapon. Status: Innocent."
    ```

---

## Extending the project

- **Use `Case` & `Evidence`**:  
  - Add a `vector<shared_ptr<Case>>` to `InvestigationControl`.  
  - Provide menu actions to create a case, attach suspects/evidence, and print `Case::showDetails()`.
- **Stronger protocol**:  
  - Use JSON (e.g., `{"query":"John Doe"}`) and parse on the server for richer responses.
- **Persistence**:  
  - Save suspects/detectives to JSON/SQLite; load on start.
- **Cross‑platform networking**:  
  - Replace `WinsockClient` with Boost.Asio or BSD sockets wrapper.

---

## File-by-file API recap

- **`Person.h`**  
  - `virtual void describe() = 0;`  
  - `string getName() const;`

- **`Detective.h`**  
  - `Detective(string n, int a, string skill)`  
  - `void describe() override;`  
  - `string getSkill() const;`

- **`Suspect.h`**  
  - `Suspect(string n, int a, string alibi, string caughtBy, string reason, bool guilty)`  
  - `void describe() override;`  
  - `string getCaughtBy() const;` `string getReasonCaught() const;` `bool getGuiltStatus() const;`

- **`InvestigationControl.h`**  
  - Add/get vectors; `validateCase()`; `shared_ptr<Suspect> findSuspect(const string&)`; `showCaughtDetails(...)`.

- **`CustomExceptions.h`**  
  - `EmptyCaseException`, `SuspectNotFoundException`, `InvalidInputException`, `ServerQueryException`.

- **`WinsockClient.h`**  
  - `initialize(ip, port)`, `connectToServer()`, `sendAndReceive(query)`, `cleanup()`.

- **`Evidence.h` / `Case.h`**  
  - Utility classes for building richer cases (`addSuspect`, `addEvidence`, `showDetails`).

---

## License & Credits
- Educational project for demonstrating **OOP**, **exceptions**, and **client–server** basics.
- Winsock code requires Windows. Python server is cross‑platform.

---
