import os
import sys
import platform
from pathlib import Path
import shutil
import subprocess

def reprint(text):
    print(f"\033[A\033[K\r{text}", end="", flush=True)

def get_install_root():
    system = platform.system()
    if system == "Windows":
        return Path(os.getenv("SystemDrive", "C:")) / "Program Files" / "Rinegine"
    elif system == "Linux":
        return Path("/usr/local/Rinegine")
    else:
        print(f"OS not supported: {system}")
        sys.exit(1)

count_copy = 0
count_files = 0
width_terminal = 0

BLUE_FG = "\033[34m"        
BLUE_BG = "\033[44m"        
GREEN_FG = "\033[32m"       
GREEN_BG = "\033[42m"      
RESET = "\033[0m"           

SHELL_CONFIGS = {
    "bash": [Path.home() / ".bashrc", Path.home() / ".profile"],
    "zsh": [Path.home() / ".zshenv", Path.home() / ".zshrc"],
    "fish": [Path.home() / ".config/fish/config.fish"],  # special syntax
    "dash": [Path.home() / ".profile"],
    "tcsh": [Path.home() / ".cshrc"],
}

INSTALL_ROOT = Path("/usr/local/Rinegine")
BIN_DIR = INSTALL_ROOT / "bin"

def get_installed_shells():
    shells = []
    common_shells = ["bash", "zsh", "fish", "dash", "tcsh"]
    for shell in common_shells:
        if shutil.which(shell):
            shells.append(shell)
    return shells

def file_contains(path, text):
    if not path.exists():
        return False
    try:
        content = path.read_text(encoding="utf-8")
        return text in content
    except (UnicodeDecodeError, PermissionError):
        return False

def add_line_to_file(path, line):
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        content = path.read_text(encoding="utf-8")
        if line not in content:
            with open(path, "a", encoding="utf-8") as f:
                f.write(f"\n{line}\n")
            return True
    else:
        print(f"{path} does not exist, creating")
        with open(path, "w", encoding="utf-8") as f:
            f.write(f"{line}\n\n")
        return True
    return False
def setup_shell_config(shell):
    global countdeb
    configs = SHELL_CONFIGS.get(shell)
    if not configs:
        return

    modified = False

    for config_path in configs:
        if config_path.exists():
            path_line = f'export PATH="$PATH:{BIN_DIR}"'
            rinegine_line = f'export RINEGINE="{INSTALL_ROOT}"'

            if add_line_to_file(config_path, path_line):
                print(f"PATH added to {config_path}")
                modified = True
            if add_line_to_file(config_path, rinegine_line):
                print(f"RINEGINE added to {config_path}")
                modified = True

        elif shell == "fish" and "fish" in str(config_path):
            # Special syntax for fish
            path_line = f'set -gx PATH $PATH "{BIN_DIR}"'
            rinegine_line = f'set -gx RINEGINE "{INSTALL_ROOT}"'

            if add_line_to_file(config_path, path_line):
                print(f"PATH added to fish: {config_path}")
                modified = True
            if add_line_to_file(config_path, rinegine_line):
                print(f"RINEGINE added to fish: {config_path}")
                modified = True
    return modified

def scan_and_setup():
    print("Scanning installed shells...")

    shells = get_installed_shells()
    if not shells:
        print("No known shells found")
        return

    print(f"Found: {', '.join(shells)}")

    for shell in shells:
        print(f"\nSetting up {shell}...")
        if setup_shell_config(shell):
            print(f"Done. Variables added.")
            if(shell == "zsh"):
                print("     For proper installation, you need to relogin!")
        else:
            print(f"Already set up")
#copy
def smart_copy(src_file, dst_file):
    if not dst_file.exists():
        shutil.copy2(src_file, dst_file)
        return

    src_mtime = src_file.stat().st_mtime
    dst_mtime = dst_file.stat().st_mtime

    if src_mtime > dst_mtime:
        shutil.copy2(src_file, dst_file)

def loading_bar(count_copy, count_files, width_terminal,text):
    if (count_copy/count_files * width_terminal)<len(text):
        text_front = text[0:int(count_copy/count_files*width_terminal)]
        text_back = text[int(count_copy/count_files*width_terminal):-1]
        text = f"{text_front}{GREEN_FG}{BLUE_BG}{text_back}"
    spaces = " "*int((count_copy/count_files * width_terminal)-len(text))
    bar = (f"{BLUE_FG}{GREEN_BG}{text}{spaces}{GREEN_FG}{BLUE_BG}")
    print("\r")
    reprint(f"{bar}")
    
def sync_dir(src, dst):
    dst.mkdir(parents=True, exist_ok=True)
    global width_terminal
    width_terminal = shutil.get_terminal_size((80, 24)).columns
    for item in src.iterdir():
        global count_copy
        count_copy += 1
        loading_bar(count_copy, count_files, width_terminal,f"Copying... {count_copy}/{count_files}")
        src_item = item
        dst_item = dst / item.name

        if item.is_dir():
            sync_dir(src_item, dst_item)
        else:
            smart_copy(src_item, dst_item)
#count
def count_dir(src):
    for item in src.iterdir():
        global count_files
        count_files += 1
        src_item = item
        if item.is_dir():
            count_dir(src_item)

def main():
    src_dir = Path(".").resolve()
    install_root = get_install_root()
    bin_dir = install_root / "bin"
    if "--stage1" in sys.argv:
        print("src_dir:", src_dir)
        print("install_root:", install_root)
        print("bin_dir:", bin_dir)
        if not (src_dir / "include").exists():
            print("Run from the engine directory")
            sys.exit(1)

        print(f"Copying: {src_dir} → {install_root}")
        count_dir(src_dir)
        sync_dir(src_dir, install_root)
        print(RESET)
    elif "--stage2" in sys.argv:
        scan_and_setup()
    else:
        if os.getuid() == 0:
            print("Script cannot be run as root (via sudo)")
            exit(1)
        print("Starting Rinegine installation...")

        print("Requesting rights to copy...")
        subprocess.run([
            "sudo", sys.executable, __file__, "--stage1"
        ], check=True)

        print("Setting up environment variables...")
        subprocess.run([
            sys.executable, __file__, "--stage2"
        ], check=True)

        print("\nInstallation completed!")
        print("Restart the terminal")

if __name__ == "__main__":
    main()
