# Draw-and-Recognize-MNIST

This project implements a Simple Feed Forward Neural Network and a Convolutional Neural Network (CNN) for handwritten digit recognition using the MNIST dataset. The project includes a terminal-based interface that allows users to draw digits in real time using their mouse. Once a digit is drawn, it is processed and classified by the trained model.

---

## Requirements

### For Training the Model
- Python 3.8+
- Libraries:
  - PyTorch
  - torchvision
  - tqdm
  - numpy
  - matplotlib
  - jupyter

### For Running the Interface
- g++ or clang (C++11 or later)
- LibTorch (PyTorch C++ API)
- ncurses library
- cmake 

---

## Getting Started

1. **Clone the Repository**
    ```bash
    git clone https://github.com/Xzanam/draw-and-recognize-mnist.git
    cd draw-and-recognize-mnist
    ```

2. **Install the required Python packages**:

## Training the Model

The training code is provided in `mnist.ipynb`. Follow these steps:

1. **Open the notebook**:
    ```bash
    jupyter notebook mnist.ipynb
    ```

2. **Run the cells** to train the model on the MNIST dataset. mnist.ipynb consists of training code for both Feed Forward Neural Network and Convolutional Neural Network. The notebook itself is self-explanatory. After training, the model is exported as 'model_cnn.pt' using PyTorch's JIT.

## Compiling the C++ interface

To compile the C++ interface, follow these steps:

1. **Create a build directory**:
   Open your terminal and navigate to the project folder. Create a separate directory for the build files to keep things organized:
   
    ```bash
    mkdir build
    cd build
    ```

2. **Run CMake**:
   Use CMake to generate the necessary build files. Make sure you are inside the `build` directory:

    ```bash
    cmake ..
    ```

3. **Compile the code**:
   Now, compile the code using `make`:

    ```bash
    make
    ```

After these steps, an executable named `draw-and-recognize-mnist` should be created in the `build` directory, ready to run with your trained model.


