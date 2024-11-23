# draw-and-recognize-mnist

This project implements a **Convolutional Neural Network (CNN)** for handwritten digit recognition using the MNIST dataset. It features a terminal-based interface that allows users to draw digits in real-time using their mouse. The drawn digit is then processed and classified by the CNN model.

## Features

- **Real-time Drawing Interface**: Draw digits using your mouse in a terminal-based environment.
- **MNIST-based Digit Recognition**: Uses a trained CNN model to classify drawn digits with high accuracy.
- **Interactive User Experience**: See instant predictions after drawing digits.

## Table of Contents

1. [Installation](#installation)
2. [Training the Model](#training-the-model)
3. [Running the Application](#running-the-application)
4. [Dependencies](#dependencies)
5. [Usage](#usage)
6. [Contributing](#contributing)
7. [License](#license)

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/draw-and-recognize-mnist.git
    cd draw-and-recognize-mnist
    ```

2. **Install the required Python packages**:
    Make sure you have Python installed. Then, install the dependencies using:
    ```bash
    pip install -r requirements.txt
    ```

## Training the Model

The training of the CNN model is done using the **MNIST dataset** in a Jupyter Notebook. To train the model:

1. Open the Jupyter Notebook `mnist.ipynb`:
    ```bash
    jupyter notebook mnist.ipynb
    ```

2. Follow the instructions in the notebook to train the CNN model. Once trained, save the model weights as `model.pth`.

## Running the Application

To run the application, you need to have the trained model (`model.pth`) in the project directory. Then, follow these steps:

1. **Compile the code** (if necessary):
    If you have a C++ component, compile it using:
    ```bash
    g++ -o draw_digit draw_digit.cpp -lsfml-graphics -lsfml-window -lsfml-system
    ```

2. **Run the application**:
    ```bash
    python main.py
    ```

This will launch the terminal-based drawing interface.

## Dependencies

- **Python 3.7+**
- **PyTorch** (for training and loading the CNN model)
- **Jupyter Notebook** (for model training)
- **SFML** (if a graphical interface is implemented in C++)
- **NumPy** (for numerical operations)
- **OpenCV** (for image processing)
- **Matplotlib** (for visualizations)

Install all Python dependencies using:
```bash
pip install -r requirements.txt
