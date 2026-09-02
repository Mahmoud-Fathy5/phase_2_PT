# Visual Flowchart IDE, Simulator & C++ Code Generator

> **Programming Techniques (PT) Course Project — Phase 2**  
> An interactive visual programming environment for designing, validating, simulating, debugging, and compiling flowcharts into executable C++ source code.

---

## 📌 Project Overview

This project is a desktop graphical Integrated Development Environment (IDE) built in **C++** using **CMUgraphicsLib** as part of the **Programming Techniques** university course.

The application allows users to visually assemble algorithmic logic using standard flowchart symbols, connect them through intelligent orthogonal arrows, validate syntactic and semantic correctness, simulate execution step-by-step with real-time memory/variable inspection, and automatically translate the flowchart into structured, compilable **C++ (`.cpp`)** source code.

---

## 🚀 Key Features

### 1. Dual Mode System
The application provides two specialized operational modes toggled directly from the toolbar:
* **Design Mode**: Full canvas editor for placing, arranging, editing, cutting, copying, pasting, and connecting flowchart statements.
* **Simulation Mode**: Runtime environment for verifying graph integrity, running simulations, stepping through instructions, and generating C++ code.

---

### 2. Comprehensive Flowchart Statements
The engine supports all foundational imperative programming constructs modeled via Object-Oriented polymorphism:

| Statement | Shape | Description | Example Syntax |
| :--- | :--- | :--- | :--- |
| **Start** | Oval / Ellipse | Entry point of the flowchart (enforced unique) | `Start` |
| **End** | Oval / Ellipse | Termination node of the flowchart (enforced unique) | `End` |
| **Variable Declaration** | Rectangle | Declares a double-precision variable | `double x;` |
| **Value Assignment** | Rectangle | Assigns a numeric literal to a variable | `x = 5.0;` |
| **Variable Assignment** | Rectangle | Assigns the value of one variable to another | `x = y;` |
| **Operator Assignment** | Rectangle | Computes binary arithmetic (`+`, `-`, `*`, `/`) | `x = a + 10;` |
| **Condition (`If` / Loop)** | Diamond / Rhombus | Decision node (`==`, `!=`, `<`, `<=`, `>`, `>=`) with dual branch outlets (True & False) | `If x >= 5` |
| **Read (Input)** | Parallelogram | Requests numerical input from the user at runtime | `cin >> x;` |
| **Write (Output)** | Parallelogram | Prints a variable's value or a string literal to the console | `cout << x;` or `"Hello"` |

---

### 3. Intelligent Connectors & Loopback Routing
* **Directed Connections**: Outlets connect to Inlets with rendered arrowheads indicating control flow.
* **Orthogonal Routing**: Automatically calculates straight lines, single bends, or multi-segment orthogonal paths.
* **Loopback Routing**: When an outlet connects backward to an earlier statement (e.g., upward connection for `while` loops), the connector automatically routes around the side of the diagram to prevent visual overlap.
* **Topology Validation**:
  - `End` cannot have outgoing connections.
  - `Start` cannot have incoming connections.
  - Statements cannot connect to themselves.
  - Standard statements allow only 1 outgoing connector.
  - `If` conditions require exactly 2 outgoing connectors (True and False branches).

---

### 4. Editing & Canvas Manipulation
* **Interactive Selection**: Click any statement or connector to select and highlight it with a distinct red stroke.
* **In-Place Editing**: Select any node and press the edit button to update its variables, expressions, or operators through interactive prompts.
* **Clipboard Engine**:
  - **Copy**: Stores the selected statement to the clipboard.
  - **Cut**: Stores the statement to the clipboard and marks it for relocation.
  - **Paste**: Places a clone at the clicked location with collision detection and canvas boundary enforcement.
* **Safe Deletion**: Deleting a statement automatically cascades to all connected incoming and outgoing connectors, preventing dangling pointers and memory leaks.
* **File Persistence**:
  - **Save**: Serializes the full graph state (statements, IDs, coordinates, parameters, and connector routing) to `.txt` files in `SavedCharts/`.
  - **Load**: Clears the canvas and reconstructs the flowchart graph from saved files.

---

### 5. Validation, Simulation & Code Generation

#### 🔍 Static Validation
Before simulation or code generation, the flowchart undergoes graph and semantic validation:
* Validates presence of both `Start` and `End` terminals.
* Checks that all statements are reachable and connected (no disconnected nodes).
* **Symbol Table Checking**:
  - Variables must be declared before assignment or use.
  - Variables cannot be redeclared.
  - Variables must be initialized before evaluation in expressions or conditions.
* Verifies that both branches of each `If` block are properly terminated or looped.

#### ▶️ Continuous Simulation (`Run`)
* Starts at `Start` and traverses through connectors until `End`.
* Interactively prompts the user in the status bar whenever a `Read` statement is encountered.
* Prints execution steps and output values to the dedicated right-hand side **Output Window**.

#### 🐞 Step-by-Step Debugger (`Debug`)
* Advances execution one statement at a time on mouse click.
* Visually highlights the statement currently being executed.
* Dumps the real-time variable memory state (variable names and current values) to the output panel at each step.

#### 💻 C++ Code Generation
* Automatically converts the visual flowchart into clean, formatted, standard C++ code.
* Detects cyclic conditional paths and generates structured `while (...) { ... }` loops.
* Writes ready-to-compile `.cpp` files into the `Codes/` directory with standard headers (`#include <iostream>`) and `main()` function wrapper.

---

## 🏛️ Software Architecture & Design Patterns

The project follows clean Object-Oriented design principles and design patterns:

```
                  +-----------------------+
                  |  ApplicationManager   | <------+
                  +-----------------------+        |
                   |          |          |         | (Mediator)
     +-------------+          |          +---------+----+
     |                        |                         |
     v                        v                         v
+----------+          +---------------+          +--------------+
|  Input   |          | Statement (A) |          |  Action (A)  |
+----------+          +---------------+          +--------------+
     |                       |                          |
     v                +------+------+            +------+------+
+----------+          |             |            |             |
|  Output  |       Start, End,   If, Read,    AddStart,     Validate,
+----------+       Declare, ...  Write, ...   AddConn, ...  Run, Debug, ...
```

### Key Design Patterns
1. **Command Pattern (`Action` hierarchy)**:
   - Base class `Action` defines pure virtual methods `ReadActionParameters()` and `Execute()`.
   - Every user action (`AddStart`, `AddIf`, `AddConn`, `Select`, `Edit`, `Delete`, `Copy`, `Paste`, `Validate`, `Run`, `Debug`, `GenerateCode`, `Save`, `Load`) is an independent encapsulated command object.
2. **Mediator / Application Controller (`ApplicationManager`)**:
   - Coordinates between the UI (`Input`/`Output`), data structures (`StatList`, `ConnList`, `Vars`), clipboard, and command lifecycle.
3. **Polymorphic Statement Hierarchy (`Statement` base class)**:
   - Abstract base class declaring virtual contracts:
     - `Draw(Output* pOut)`
     - `Simulate(ApplicationManager* pManager)`
     - `Valid(ApplicationManager* pManager)`
     - `GenerateCode(ofstream& OutFile)`
     - `Save(ofstream& OutFile)` / `Load(ifstream& InFile)`
     - `Edit(ApplicationManager* pManager)`
4. **Separation of Concerns**:
   - `GUI/`: Windows presentation and mouse/keyboard event handling.
   - `Statements/`: Business logic, validation rules, evaluation, and code emission per node.
   - `Actions/`: User workflow orchestration and state transitions.

---

## 📁 Repository Structure

```plaintext
phase_2_PT/
├── Actions/                  # Command classes for all operations
│   ├── Action.h              # Abstract base command class
│   ├── AddStart.{h,cpp}      # Add Start statement
│   ├── AddEnd.{h,cpp}        # Add End statement
│   ├── AddDeclare.{h,cpp}    # Add variable declaration
│   ├── AddValueAssign.{h,cpp}# Add value assignment
│   ├── AddAssignVariable.{h,cpp} # Add variable assignment
│   ├── AddAssignOperator.{h,cpp} # Add arithmetic operator assignment
│   ├── AddIf.{h,cpp}         # Add conditional branching / loop
│   ├── AddRead.{h,cpp}       # Add Read (input) statement
│   ├── AddWrite.{h,cpp}      # Add Write (output) statement
│   ├── AddConn.{h,cpp}       # Add connector between statements
│   ├── Select.{h,cpp}        # Select statement or connector
│   ├── Edit.{h,cpp}          # In-place parameter editing
│   ├── Delete.{h,cpp}        # Delete element with cascading connector cleanup
│   ├── Copy.{h,cpp}          # Copy to clipboard
│   ├── Cut.{h,cpp}           # Cut to clipboard
│   ├── Paste.{h,cpp}         # Paste from clipboard
│   ├── Validate.{h,cpp}      # Semantic and syntax validation engine
│   ├── Run.{h,cpp}           # Full simulation runner
│   ├── Debug.{h,cpp}         # Step-by-step interactive debugger
│   ├── GenerateCode.{h,cpp}  # C++ code generation engine
│   ├── Save.{h,cpp}          # File export / save
│   └── Load.{h,cpp}          # File import / load
├── Statements/               # Flowchart node models (Inheritance hierarchy)
│   ├── Statement.{h,cpp}     # Abstract base class
│   ├── Start.{h,cpp}         # Start node implementation
│   ├── End.{h,cpp}           # End node implementation
│   ├── Declare.{h,cpp}       # Declare variable node
│   ├── ValueAssign.{h,cpp}   # Value assignment node
│   ├── VariableAssign.{h,cpp}# Variable assignment node
│   ├── AssignOperator.{h,cpp}# Binary arithmetic node
│   ├── If.{h,cpp}            # Conditional decision node (2 outlets)
│   ├── Read.{h,cpp}          # Console input node
│   └── Write.{h,cpp}         # Console output node
├── GUI/                      # User interface abstraction layer
│   ├── Input.{h,cpp}         # Mouse clicks, keyboard strings/numbers/operators
│   ├── Output.{h,cpp}        # Primitives drawing, toolbars, output console
│   └── UI_Info.h             # Global UI dimensions, colors, and coordinates
├── CMUgraphicsLib/           # Simple Win32 2D graphics library
├── images/                   # Toolbar icons (PNG / JPG)
├── SavedCharts/              # Saved flowchart graph files (.txt)
│   ├── test.txt              # Linear chart example
│   ├── test1.txt             # Simple conditional / while loop example
│   └── test2.txt             # Multi-variable branching example
├── Codes/                    # Generated C++ source files (.cpp)
│   ├── test.cpp              # Generated C++ code from test.txt
│   ├── test1.cpp             # Generated C++ code from test1.txt
│   └── test2.cpp             # Generated C++ code from test2.txt
├── ApplicationManager.{h,cpp}# Central orchestrator / mediator
├── Connector.{h,cpp}         # Directed edge representation & hitbox routing
├── HelperFn.{h,cpp}          # String parsers and validator utilities
├── DEFS.h                    # Global enums, modes, and action identifiers
├── main.cpp                  # Application entry point (event loop)
├── PT Project.sln            # Visual Studio Solution
└── PT Project.vcxproj        # Visual Studio Project File
```

---

## 📝 Flowchart Serialization & Code Generation Example

### 1. Saved Chart File Format (`SavedCharts/test2.txt`)
```plaintext
9
START 2 303 82
DECLARE 3 270 159 x
DECLARE 4 271 236 y
READ 5 268 303 x
COND 6 244 373 x >= 5
VAR_ASSIGN 9 416 422 x y
OP_ASSIGN 10 64 441 x y + 10
WRITE 11 208 496 y
END 12 667 496
9
2 3 0
3 4 0
4 5 0
5 6 0
6 9 1
6 10 2
10 11 0
9 11 0
11 12 0
```

### 2. Automatically Generated C++ Code (`Codes/test2.cpp`)
```cpp
#include <iostream>
using namespace std;
int main(){
	double x;
	double y;
	cin >> x;
	while(x>=5){
		x = y;
		cout << y << endl;
		return 0;
	}
	x = y + 10;
	cout << y << endl;
	return 0;
}
```

---

## 🛠️ Build and Setup Instructions

### Prerequisites
* **Operating System**: Microsoft Windows 10 or 11.
* **IDE**: Microsoft Visual Studio (2019 or 2022 recommended) with the **Desktop development with C++** workload installed.
* **Platform Toolset**: `v142` or `v143` (MSVC).

### Building in Visual Studio
1. Clone or download the repository:
   ```bash
   git clone https://github.com/Mahmoud-Fathy5/phase_2_PT.git
   ```
2. Open `PT Project.sln` in **Visual Studio**.
3. In the toolbar, set the build configuration to:
   * **Configuration**: `Debug` or `Release`
   * **Platform**: `Win32` / `x86` *(CMUgraphicsLib requires 32-bit compilation)*
4. Build the solution by pressing `Ctrl + Shift + B` or selecting **Build > Build Solution**.
5. Run the project by pressing `F5` (with debugging) or `Ctrl + F5` (without debugging).

---

## 🎮 How to Use the Application

### Creating a Flowchart
1. **Add Start / End**: Click the `Start` icon and place it on the drawing canvas.
2. **Add Statements**: Click any statement icon (`Declare`, `Assign`, `Read`, `Write`, `If`) and click on the canvas to place it. Enter the required parameters (variable names, values, operators) in the bottom status bar.
3. **Connect Nodes**:
   - Click the `Connector` (arrow) icon.
   - Click the source statement.
   - Click the target statement.
   - For `If` statements, the first connector created represents the **True** branch, and the second connector represents the **False** branch.
4. **Edit / Relocate**: Use the `Select` tool to select nodes, then use `Edit`, `Cut`, `Copy`, `Paste`, or `Delete`.
5. **Save**: Click `Save` and enter a filename to save your diagram to `SavedCharts/<filename>.txt`.

### Running, Debugging & Generating Code
1. Click the **Simulation Mode** icon in the toolbar.
2. **Validate**: Click `Validate` to inspect your flowchart for errors (errors appear in the right-hand output bar).
3. **Run**: Click `Run` to execute the flowchart continuously.
4. **Debug**: Click `Debug` and click anywhere on the canvas to advance step-by-step while watching variable values update in the output window.
5. **Generate Code**: Click `Generate Code`, enter a file name, and find your generated C++ program under `Codes/<filename>.cpp`.

---

## 👥 Contributors

Developed as part of the **Programming Techniques** course by:

* **Mahmoud Fathy** ([@Mahmoud-Fathy5](https://github.com/Mahmoud-Fathy5))
* **Mohamed Medhat** ([@mohamedmedhat](https://github.com/momedhat736))
* **Mahmoud Taha** ([@Mahmouedtaha75](https://github.com/Mahmouedtaha75))

---

## 📄 License
This project was developed for educational purposes as part of academic coursework. Feel free to reference it for learning software design patterns, C++ OOP, and visual compiler/simulator architectures.
