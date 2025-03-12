#!/bin/python3
import sys

def read_map_from_file(file_path):
    """Reads the map from a file and returns a list of strings representing the map."""
    with open(file_path, "r") as file:
        # Skip the first line (the number of lines)
        map_data = file.readlines()[1:]

    # Strip any trailing newline characters
    map_data = [line.strip() for line in map_data]
    return map_data


def largest_square(map_data):
    """Finds the largest square of empty spaces and fills it with 'x'."""
    rows = len(map_data)
    cols = len(map_data[0])

    # Initialize the DP table with zeros
    dp = [[0] * cols for _ in range(rows)]
    max_square_size = 0
    max_square_pos = (0, 0)

    # Iterate through the map
    for i in range(rows):
        for j in range(cols):
            # If the cell is not an obstacle and is not the first row or column
            if map_data[i][j] == ".":
                if i == 0 or j == 0:
                    dp[i][j] = (
                        1  # Edge case: The first row/column can only form squares of size 1
                    )
                else:
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1

                # Track the maximum square size and its position
                if dp[i][j] > max_square_size:
                    max_square_size = dp[i][j]
                    max_square_pos = (i, j)
                elif dp[i][j] == max_square_size:
                    # If there is a tie, we choose the upper-leftmost square
                    if i < max_square_pos[0] or (
                        i == max_square_pos[0] and j < max_square_pos[1]
                    ):
                        max_square_pos = (i, j)

    # Now fill the biggest square found with 'x'
    i, j = max_square_pos
    for x in range(i - max_square_size + 1, i + 1):
        for y in range(j - max_square_size + 1, j + 1):
            map_data[x] = map_data[x][:y] + "x" + map_data[x][y + 1 :]

    return map_data,max_square_pos,max_square_size


def main():
    if len(sys.argv) != 2:
        print("Usage: python program.py <map_file_path>")
        sys.exit(1)

    file_path = sys.argv[1]

    try:
        # Read the map from the file
        map_data = read_map_from_file(file_path)

        # Solve for the largest square and fill it with 'x'
        result,res_pos,res_size = largest_square(map_data)

        # Output the result
        for row in result:
            print(row)
        # print(f"biggest -> size: {res_size}, x: {res_pos[1]}, y: {res_pos[0]}")

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()