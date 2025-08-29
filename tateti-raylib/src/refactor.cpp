#include <raylib.h>
#include <vector>
#include <iostream>

#define GRID_SIZE 3
#define SQUARE_SIZE 150

// Estados para el tablero y el juego
typedef enum { NONE, CROSS, CIRCLE } Player;
typedef enum { PLAYING, WIN, DRAW } GameState;

std::vector<std::vector<Player>> board;
GameState gameState;
Player currentPlayer;
Player winner;

void InitGame();
void UpdateGame();
void DrawGame();
bool CheckWin();
bool CheckDraw();

int main(void) {
    const int screenWidth = GRID_SIZE * SQUARE_SIZE;
    const int screenHeight = GRID_SIZE * SQUARE_SIZE;

    InitWindow(screenWidth, screenHeight, "raylib - Ta-Te-Ti");
    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();
    }
    CloseWindow();
    return 0;
}

void InitGame() {
    // Redimensiona el vector y llena con el estado NONE   
    board.assign(GRID_SIZE, std::vector<Player>(GRID_SIZE, NONE));
    gameState = PLAYING;
    currentPlayer = CIRCLE;
    winner = NONE;
}

void UpdateGame() {
    if (gameState != PLAYING) {
        if (IsKeyPressed(KEY_ENTER)) {
            InitGame();
        }
    } 
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

    Vector2 mousePosition = GetMousePosition();
    int row = (int)mousePosition.y / SQUARE_SIZE;
    int col = (int)mousePosition.x / SQUARE_SIZE;

    // Condiciones inválidas
    if (row < 0 || row >= GRID_SIZE) return;
    if (col < 0 || col >= GRID_SIZE) return;
    if (board.at(row).at(col) != NONE) return;

    board.at(row).at(col) = currentPlayer;

    if (CheckWin()) {
        gameState = WIN;
        winner = currentPlayer;
        return;
    }
    if (CheckDraw()) {
        gameState = DRAW;
        return;
    }

    currentPlayer = (currentPlayer == CIRCLE) ? CROSS : CIRCLE;
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dibuja la grilla y las fichas
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            DrawRectangleLines(j * SQUARE_SIZE, i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);

            Vector2 center = {
                (float)(j * SQUARE_SIZE) + (SQUARE_SIZE / 2.0f),
                (float)(i * SQUARE_SIZE) + (SQUARE_SIZE / 2.0f)
            };
            float radius = SQUARE_SIZE / 3.0f;

            if (board[i][j] == CIRCLE) {
                DrawCircle(center.x, center.y, radius, BLUE);
                DrawCircle(center.x, center.y, radius * 0.8f, RAYWHITE);
                continue; 
            }

            if (board[i][j] == CROSS) {
                float lineThickness = 5.0f;
                DrawLineEx({ center.x - radius, center.y - radius }, { center.x + radius, center.y + radius }, lineThickness, RED);
                DrawLineEx({ center.x + radius, center.y - radius }, { center.x - radius, center.y + radius }, lineThickness, RED);
            }
        }
    }

    //Si el juego terminó, mostramos el mensaje y salimos
    if (gameState != PLAYING) {
        const char* message =
            (gameState == WIN) ? ((winner == CIRCLE) ? "Círculos Ganan!" : "Cruces Ganan!") 
                               : "Empate!";

        DrawText(message,
                 GetScreenWidth() / 2 - MeasureText(message, 30) / 2,
                 GetScreenHeight() / 2 - 20,
                 30, BLACK);

        DrawText("Presiona ENTER para jugar de nuevo",
                 GetScreenWidth() / 2 - MeasureText("Presiona ENTER para jugar de nuevo", 20) / 2,
                 GetScreenHeight() / 2 + 30,
                 20, DARKGRAY);

        EndDrawing();
        return;
    }

    // Si el juego sigue, mostramos el turno
    const char* turnMessage = (currentPlayer == CIRCLE) ? "Turno de Círculos" : "Turno de Cruces";
    DrawText(turnMessage, 10, GetScreenHeight() - 30, 20, DARKGRAY);

    EndDrawing();
}

bool CheckWin() {
    for (int i = 0; i < GRID_SIZE; i++) {
        // Filas
        if (board[i][0] != NONE && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        // Columnas
        if (board[0][i] != NONE && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }

    // Verifica diagonales
    if (board[0][0] != NONE && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != NONE && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

bool CheckDraw() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == NONE) return false; 
        }
    }
    return true; 
}