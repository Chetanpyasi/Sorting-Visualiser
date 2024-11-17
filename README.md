# Sorting Visualizer

Sorting Visualizer is a project designed to help users understand and visualize how various sorting algorithms work. It provides a graphical interface to demonstrate sorting step-by-step, making it an excellent tool for educational purposes.

---

## Features

- **Multiple Sorting Algorithms**: Visualize algorithms like Merge Sort, Insertion Sort, and more.
- **Interactive UI**: Built using Qt for an engaging and user-friendly experience.
- **Real-time Updates**: See the sorting process unfold in real-time.
- **Modular Codebase**: Includes separate components like `algo.h` for algorithm definitions and `Input.h` for input handling.

---

## Getting Started

### Prerequisites

To use this project, ensure you have the following installed:

- **Qt Creator** (version 6.9 or higher recommended)
- A compatible C++ compiler
- CMake

---

### Setting Up the Environment

1. **Install Qt Creator**:

   Download and install the latest version of Qt Creator from the [official website](https://www.qt.io/download).

2. **Clone the Repository**:

   ```bash
   git clone [<repository_url>](https://github.com/Chetanpyasi/Sorting-Visualiser)
   cd Sorting_Visualizer
   ```

3. **Open the Project in Qt Creator**:

   - Launch Qt Creator.
   - Click on `Open File or Project`.
   - Navigate to the cloned repository folder and select the `CMakeLists.txt` file.

4. **Configure the Project**:

   - Qt Creator will automatically detect your CMake configuration.
   - Choose a build kit (e.g., Desktop Qt 6.9 MinGW 64-bit).
   - Click `Configure Project`.

5. **Build and Run**:

   - Click the Build button in Qt Creator to compile the project.
   - Once built, click the Run button to launch the application.

---

## File Structure

```
.
├── sortingvisualizer.h         # Header file defining sorting algorithms
├── sortingvisualizer.cpp       # Implementation file for sorting algorithms
├── main.cpp                    # Entry point for the application
├── CMakeLists.txt              # Project build configuration
└── README.md                   # Project documentation
```

---

## Usage

1. Run the application.
2. Select a sorting algorithm from the menu.
3. Provide input data (manual entry or predefined datasets).
4. Click `Visualize` to see the sorting process in action.

---

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

---

## Acknowledgments

- Inspired by various sorting visualizer projects and educational tools.
- Built using Qt Creator for a robust graphical interface.
