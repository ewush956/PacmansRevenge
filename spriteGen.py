import os
from PIL import Image

def png_to_hex_bitmap(file_path):
    with Image.open(file_path) as img:
        img = img.convert('1')  # Convert to black and white

        hex_bitmap = []

        for y in range(32):
            row = ""
            for x in range(32):
                pixel = img.getpixel((x, y))
                row += '1' if pixel == 0 else '0'  # Assuming black pixel is 1, white is 0

            hex_value = '{:08X}'.format(int(row, 2))
            hex_bitmap.append(hex_value)

        return hex_bitmap

def process_folder_to_c_file(folder_path, output_file):
    with open(output_file, 'w') as file:
        sprite_count = 1

        for filename in os.listdir(folder_path):
            if filename.endswith(".png"):
                file_path = os.path.join(folder_path, filename)
                hex_bitmap = png_to_hex_bitmap(file_path)

                file.write(f"const UINT32 sprite{sprite_count}[32] = {{\n")
                for line in hex_bitmap:
                    file.write(f"0x{line},\n")
                file.write("};\n\n")
                
                sprite_count += 1

# Example usage
folder_path = 'sprites'  # Replace with your folder path
output_file = 'sprites.c'  # The output C file
process_folder_to_c_file(folder_path, output_file)
