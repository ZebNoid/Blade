from pathlib import Path

# Список папок для обхода
FOLDERS = [
    "Api",
    "Backend",
    "Blade",
    "Example",
]

# Список расширений файлов
EXTENSIONS = [
    ".c",
    ".cpp",
    ".h",
]

# Итоговый файл
OUTPUT_FILE = "BladeSourceAll.cpp"


def collect_files(folders, extensions):
    result = []

    for folder in folders:
        folder_path = Path(folder)

        if not folder_path.exists():
            print(f"Folder not found: {folder}")
            continue

        for file_path in folder_path.rglob("*"):
            if (
                file_path.is_file()
                and file_path.suffix.lower() in extensions
            ):
                result.append(file_path)

    return result


def merge_files(files, output_file):
    with open(output_file, "w", encoding="utf-8") as out:
        for file_path in files:
            try:
                content = file_path.read_text(encoding="utf-8")

                out.write(f"// {file_path}\n\n")
                out.write(content)
                out.write("\n\n")

            except Exception as e:
                print(f"Ошибка чтения {file_path}: {e}")


if __name__ == "__main__":
    files = collect_files(FOLDERS, EXTENSIONS)

    print(f"Found files: {len(files)}")

    merge_files(files, OUTPUT_FILE)

    print(f"Complete: {OUTPUT_FILE}")