#include <torch/script.h>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <fstream>
#include <string>

#define SIZE 28
char fill_char = '@';
char stroke_char = '*';

void print_matrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mvprintw(i + 1, j * 2, "%c", matrix[i][j]);
        }
    }
    refresh();
}

void clear_matrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i][j] = fill_char; // Set to empty character
}

std::vector<float> prepare_input(char matrix[SIZE][SIZE]) {
    std::vector<float> input(SIZE * SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            input[i * SIZE + j] = (matrix[i][j] == stroke_char) ? 1.0f : 0.0f; // Normalize input (binary in this case)
        }
    }
    return input;
}

void export_matrix(const std::vector<float>& input) {
    FILE *fp = fopen("matrix.csv", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (size_t i = 0; i < input.size(); ++i) {
        fprintf(fp, "%.2f", input[i]);
        if (i < input.size() - 1) {
            fprintf(fp, ",");
        }
    }

    fclose(fp);
    printf("Matrix exported successfully to matrix.csv\n");
}

int predict(torch::jit::script::Module &model, const std::vector<float> &input) {
    // export_matrix(input); // Export the matrix before predicting
    auto tensor_input = torch::from_blob((void*)input.data(), {1, 1, SIZE, SIZE}, torch::kFloat32); // Add batch dimension and channel
    tensor_input = tensor_input.unsqueeze(0); // Ensure it has the correct shape

    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(tensor_input);
    at::Tensor output = model.forward(inputs).toTensor();

    auto max_result = output.argmax(1);
    return max_result.item<int>(); // Return the predicted class index
}

int main(int argc, const char* argv[]) {
    char matrix[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = fill_char; // Initialize with empty character
        }
    }

    MEVENT event;
    bool dragging = false;

    if (argc != 2) {
        std::cerr << "usage: character_recog <path-to-exported-script-module>\n";
        return -1;
    }

    // Load the model
    torch::jit::script::Module model;
    try {
        model = torch::jit::load(argv[1]);
    } catch (const c10::Error &e) {
        std::cerr << "Error loading the model: " << e.what() << "\n";
        return -1;
    }

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    printf("\033[?1003h\n"); // Enable mouse tracking

    mvprintw(0, 0, "Drag the mouse to update the matrix. Press 'q' to quit. Press 'p' to predict. Press 'c' to clear.");
    print_matrix(matrix);

    while (1) {
        int ch = getch();
        if (ch == 'q') {
            break;
        } else if (ch == 'c') {
            clear_matrix(matrix);
            print_matrix(matrix);
        } else if (ch == 'p') {
            std::vector<float> input = prepare_input(matrix);
            int prediction = predict(model, input);
            mvprintw(SIZE + 2, 0, "Predicted Digit: %d", prediction);
            refresh();
        } else if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                int x = event.x / 2; // Calculate the matrix column index
                int y = event.y - 1; // Adjusting for instruction line

                if (event.bstate & BUTTON1_PRESSED) {
                    dragging = true;
                } else if (event.bstate & BUTTON1_RELEASED) {
                    dragging = false;
                }

                if (dragging && x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
                    matrix[y][x] = '*';
                    
                    // Optional: Draw around the cursor
                    if (x + 1 < SIZE) matrix[y][x + 1] = stroke_char;
                    if (y + 1 < SIZE) matrix[y + 1][x] = stroke_char;
                    if (x - 1 >= 0) matrix[y][x - 1] = stroke_char;
                    if (y - 1 >= 0) matrix[y - 1][x] = stroke_char;

                    print_matrix(matrix);
                }
            }
        }
    }

    printf("\033[?1003l\n"); // Disable mouse tracking
    // End ncurses mode
    endwin();
    return 0;
}
