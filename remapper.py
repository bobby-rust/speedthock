import os
import shutil

windows = {
    1: "Esc",
    59: "F1",
    60: "F2",
    61: "F3",
    62: "F4",
    63: "F5",
    64: "F6",
    65: "F7",
    66: "F8",
    67: "F9",
    68: "F10",
    87: "F11",
    88: "F12",
    91: "F13",
    92: "F14",
    93: "F15",
    41: "`",
    2: "1",
    3: "2",
    4: "3",
    5: "4",
    6: "5",
    7: "6",
    8: "7",
    9: "8",
    10: "9",
    11: "0",
    12: "-",
    13: "=",
    14: "Backspace",
    15: "Tab",
    58: "CapsLock",
    30: "A",
    48: "B",
    46: "C",
    32: "D",
    18: "E",
    33: "F",
    34: "G",
    35: "H",
    23: "I",
    36: "J",
    37: "K",
    38: "L",
    50: "M",
    49: "N",
    24: "O",
    25: "P",
    16: "Q",
    19: "R",
    31: "S",
    20: "T",
    22: "U",
    47: "V",
    17: "W",
    45: "X",
    21: "Y",
    44: "Z",
    26: "[",
    27: "]",
    43: "\\",
    39: ";",
    40: "'",
    28: "Enter",
    51: ",",
    52: ".",
    53: "/",
    57: "Space",
    3639: "PrtSc",
    70: "ScrLk",
    3653: "Pause",

    61010: "Ins",
    61011: "Del",
    60999: "Home",
    61007: "End",
    61001: "PgUp",
    61009: "PgDn",
    57416: "↑",
    57419: "←",
    57421: "→",
    57424: "↓",

    3675: "Win",
    3676: "Win",

    42: "Shift",
    54: "Shift",
    29: "Ctrl",
    3613: "Ctrl",
    56: "Alt",
    3640: "Alt",
    3675: "Meta",
    3676: "Meta",
    3677: "Menu",

    # Numpad
    69: "NumLock",
    3637: "/",  # Numpad
    55: "*",  # Numpad """
    74: "-",  # Numpad """
    3597: "=",  # Numpad
    78: "+",  # Numpad
    3612: "Enter",  # Numpad
    83: ".",  # Numpad
    79: "1",  # Numpad
    80: "2",  # Numpad
    81: "3",  # Numpad
    75: "4",  # Numpad
    76: "5",  # Numpad
    77: "6",  # Numpad
    71: "7",  # Numpad
    72: "8",  # Numpad
    73: "9",  # Numpad
    82: "0",  # Numpad
}

cwd = os.getcwd()
print(cwd)
soundpack_dir = os.path.join(cwd, "sounds", "cherrymx-red-pbt")
output_dir = os.path.join(cwd, "sounds", "cherrymx-red-pbt-individual")
dir_contents = os.listdir(soundpack_dir)

if not os.path.exists(output_dir):
    os.makedirs(output_dir)
    print("directory created")

for filename_with_extension in dir_contents:
    
    l_filename_ext = filename_with_extension.split(".")
    ext = l_filename_ext[1]
    name = l_filename_ext[0]
    print(ext)

    if ext != "ogg" or name == "sound":
        print("something return true")
        continue
    
    
    filename = l_filename_ext[0] 
    
    if int(filename) in windows.keys():
        new_name = windows[int(filename)] + ".ogg"
        if new_name == "*.ogg":
            new_name = "asterisk.ogg"
        elif new_name == "/.ogg":
            new_name = "backslash.ogg"
        elif new_name == "\\.ogg":
            new_name = "fwd_slash.ogg"

        # copy source path to new directory
        source_path = os.path.join(soundpack_dir, filename_with_extension) 
        shutil.copy(source_path, output_dir)
    
        # rename new sound file with old name to new sound file with new name
        old_name_path = os.path.join(output_dir, filename_with_extension)
        new_name_path = os.path.join(output_dir, new_name.lower())
    
        try: 
            os.rename(old_name_path, new_name_path)
        except OSError as e: 
            print(f"Error: {e}")
        

        print(f"renamed {filename} to {windows[int(filename)]}")


import subprocess

def convert_ogg_to_wav(input_directory, output_directory):
    # Ensure the output directory exists, create it if needed
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    # Get all Ogg files in the input directory
    ogg_files = [file for file in os.listdir(input_directory) if file.endswith(".ogg")]

    # Loop through each Ogg file and convert to WAV
    for ogg_file in ogg_files:
        input_path = os.path.join(input_directory, ogg_file)
        output_path = os.path.join(output_directory, os.path.splitext(ogg_file)[0] + ".wav")

        # Use FFmpeg to perform the conversion
        ffmpeg_command = ['ffmpeg', '-i', input_path, output_path]
        subprocess.run(ffmpeg_command)

    print("Conversion complete.")

# Specify the path to the directory containing Ogg files
input_directory = "C:/Code/C/speedthock/sounds/cherrymx-red-pbt-individual"

# Specify the path to the directory where you want to save the converted WAV files
output_directory = "C:/Code/C/speedthock/sounds/cherrymx-red-pbt-individual"

convert_ogg_to_wav(input_directory, output_directory)



