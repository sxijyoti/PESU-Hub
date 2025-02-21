import curses
import json
from PIL import Image

# Canvas size
WIDTH, HEIGHT = 16, 16
COLORS = [" ", "█", "▓", "▒", "░"]  # ASCII art characters

class PixelSmith:
    def __init__(self, stdscr):
        self.stdscr = stdscr
        self.canvas = [[0 for _ in range(WIDTH)] for _ in range(HEIGHT)]
        self.cursor_x, self.cursor_y = 0, 0
        self.selected_color = 1  # Default color
        self.run()

    def draw(self):
        self.stdscr.clear()
        for y in range(HEIGHT):
            for x in range(WIDTH):
                char = COLORS[self.canvas[y][x]]
                self.stdscr.addstr(y, x * 2, char)
        self.stdscr.addstr(self.cursor_y, self.cursor_x * 2, "[]")  # Cursor
        self.stdscr.refresh()

    def save_to_json(self, filename="art.json"):
        with open(filename, "w") as f:
            json.dump(self.canvas, f)

    def export_to_png(self, filename="art.png", scale=10):
        img = Image.new("RGB", (WIDTH * scale, HEIGHT * scale), "white")
        pixels = img.load()
        color_map = {1: (0, 0, 0), 2: (50, 50, 50), 3: (100, 100, 100), 4: (150, 150, 150)}

        for y in range(HEIGHT):
            for x in range(WIDTH):
                if self.canvas[y][x] in color_map:
                    for i in range(scale):
                        for j in range(scale):
                            pixels[x * scale + i, y * scale + j] = color_map[self.canvas[y][x]]
        img.save(filename)

    def run(self):
        curses.curs_set(0)
        self.stdscr.nodelay(1)
        self.stdscr.timeout(100)
        while True:
            self.draw()
            key = self.stdscr.getch()
            if key == ord("q"):  # Quit
                break
            elif key == ord("s"):  # Save
                self.save_to_json()
            elif key == ord("e"):  # Export to PNG
                self.export_to_png()
            elif key == curses.KEY_UP:
                self.cursor_y = max(0, self.cursor_y - 1)
            elif key == curses.KEY_DOWN:
                self.cursor_y = min(HEIGHT - 1, self.cursor_y + 1)
            elif key == curses.KEY_LEFT:
                self.cursor_x = max(0, self.cursor_x - 1)
            elif key == curses.KEY_RIGHT:
                self.cursor_x = min(WIDTH - 1, self.cursor_x + 1)
            elif key in [ord(str(i)) for i in range(1, len(COLORS))]:
                self.selected_color = int(chr(key))
            elif key == ord(" "):
                self.canvas[self.cursor_y][self.cursor_x] = self.selected_color

if __name__ == "__main__":
    curses.wrapper(PixelSmith)
