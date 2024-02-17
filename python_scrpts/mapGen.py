import os
from PIL import Image

def png_to_hex_bitmap(file_path):
    with Image.open(file_path) as img:
        img = img.convert('1')  # Convert to black and white

        hex_bitmap = []

        for y in range(400):  # Update for 400 pixels in height
            row = ""
            for x in range(640):  # Update for 640 pixels in width
                pixel = img.getpixel((x, y))
                row += '1' if pixel == 0 else '0'  # Assuming black pixel is 1, white is 0

            # Convert each 4 bits in the row to a hex value
            for i in range(0, len(row), 4):
                hex_value = '{:01X}'.format(int(row[i:i+4], 2))
                hex_bitmap.append(hex_value)

        return hex_bitmap

def process_folder_to_c_file(folder_path, output_file):
    with open(output_file, 'w') as file:
        sprite_count = 1

        for filename in os.listdir(folder_path):
            if filename.endswith(".png"):
                file_path = os.path.join(folder_path, filename)
                hex_bitmap = png_to_hex_bitmap(file_path)

                # Update the format for the larger array size
                file.write(f"const UINT32 sprite{sprite_count}[400][20] = {{\n")  # 400 rows, 20 UINT32s per row
                for i in range(0, len(hex_bitmap), 20):  # Process 20 hex values (80 bits) at a time
                    file.write(f"{{0x{''.join(hex_bitmap[i:i+20])}}},\n")
                file.write("};\n\n")
                
                sprite_count += 1

# Example usage
folder_path = 'map'  # Replace with your folder path
output_file = 'map.c'  # The output C file
process_folder_to_c_file(folder_path, output_file)
