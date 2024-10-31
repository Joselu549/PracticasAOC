#!/bin/bash

SCRIPT_DIR="$(readlink -fm "$(dirname "$0")")"

cd "$SCRIPT_DIR"
tar cJf aoc-docker-image.tar.xz aoc-docker-image README.aoc-docker-image.txt icc-hack --transform='s|^|aoc-docker-image/|'
