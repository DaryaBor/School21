import os
import subprocess
from pathlib import Path
import sys

def check_venv():
    env = os.environ.get('VIRTUAL_ENV')
    if "DS_Bootcamp.Day03-1\\src\\ex02\\urr" not in env:
        raise RuntimeError("Не найдено нужное виртуальное окружение.")
    else:
        print(f"Вы находитесь в виртуальном окружении: {env}")

def install():
    try:
        result = subprocess.run(["pip", "install", "-r", "requirements.txt"], capture_output=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Ошибка: {e}")

def print_list():
    lines= subprocess.check_output(["pip", "freeze"]).decode().strip().split("\n")
    for line in lines:
        print(line)
    return lines

def save(lines):
    with open("requirements.txt", "w") as f:
        for k in lines:
            f.write(k)

if __name__ == '__main__':
    check_venv()
    install()
    res=print_list()
    save(res)


