#!/usr/bin/urrasmar/python3
import os

virtual_env_path = os.environ.get('VIRTUAL_ENV')

if virtual_env_path:
    print(f"Your current virtual env is {virtual_env_path}")
else:
    print("You are not in a virtual environment.")