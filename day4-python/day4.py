def mark_draw(board: list[list[int]], draw: int) -> tuple[int, int]:
    for row in range(len(board)):
        for col in range(len(board[0])):
            if board[row][col] == draw:
                board[row][col] = -1
                return (row, col)

    return (0, 0)


def check_win_condition(board: list[list[int]], position: tuple[int, int]) -> bool:
    row, col = position
    if all(col == -1 for col in board[row]):
        return True

    if all(board[row][col] == -1 for row in range(len(board))):
        return True

    return False

def calculate_score(board: list[list[int]], draw: int) -> int:
    score = 0
    for row in board:
        for col in row:
            if col != -1:
                score += col

    return (score * draw)

file = open('input.txt', 'r')

draws = list(map(int, file.readline().strip().split(',')))
file.readline()
lines = file.readlines()

boards = []
board = []
for line in lines:
    if not line.strip():
        boards.append(list(board))
        board.clear()
        continue

    board.append(list(map(int, line.strip().split())))

scores = []
for draw in draws:
    for board in list(boards):
        position = mark_draw(board, draw)
        if check_win_condition(board, position):
            scores.append(calculate_score(board, draw))
            boards.remove(board)

print(f"part 1: {scores[0]} part 2: {scores[-1]}")
