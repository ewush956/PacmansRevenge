import os
from PIL import Image

def png_to_hex_bitmap(file_path):
    with Image.open(file_path) as img:
        img = img.convert('1')  # Convert to black and white

        hex_bitmap = []

        for y in range(16):
            row = ""
            for x in range(16):
                pixel = img.getpixel((x, y))
                row += '1' if pixel == 0 else '0'  # Assuming black pixel is 1, white is 0

            hex_value = '{:08X}'.format(int(row, 2))
            hex_bitmap.append(hex_value)

        return hex_bitmap

def process_folder_to_c_file(folder_path, output_file):
    with open(output_file, 'w') as file:

        for filename in os.listdir(folder_path):
            if filename.endswith(".png"):
                base_name = os.path.splitext(filename)[0]  # Extract the base name without extension

                file_path = os.path.join(folder_path, filename)
                hex_bitmap = png_to_hex_bitmap(file_path)

                file.write(f"const ULONG32 {base_name}[32] = {{\n")
                for line in hex_bitmap:
                    file.write(f"\t0x{line},\n")
                file.write("};\n\n")

# Example usage
folder_path = 'wall'  # Replace with your folder path
output_file = 'new_wall.c'  # The output C file
process_folder_to_c_file(folder_path, output_file)
