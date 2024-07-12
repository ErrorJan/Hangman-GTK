#!/bin/bash

meson compile -C build_debug
python3 ./setup_bin_dir.py ./build_debug/hangman