#!/bin/bash

BOARD=$1
PROJECT_DIR=$2
MODE=$3

WEST="${HOME}/zephyr-course/.venv/bin/west"

case ${BOARD} in
  nucleo_f401re)
    ZEPHYR_BOARD="nucleo_f401re"
    OVERLAY_ARG=""
    ;;
  esp32)
    ZEPHYR_BOARD="esp32_devkitc/esp32/procpu"

    OVERLAY_FILE="${PROJECT_DIR}/boards/esp32_devkitc.overlay"

    if [ ! -f "${OVERLAY_FILE}" ]; then
      echo "Error: ESP32 overlay not found at ${OVERLAY_FILE}"
      exit 1
    fi

    OVERLAY_ARG="-DDTC_OVERLAY_FILE=${OVERLAY_FILE}"
    ;;
  *)
    echo "Unknown board: ${BOARD}"
    exit 1
    ;;
esac

BUILD_DIR="${PROJECT_DIR}/build-${BOARD}"
LINK_DIR="${PROJECT_DIR}/build"

echo "======================================"
echo "Mode: ${MODE}"
echo "Board: ${ZEPHYR_BOARD}"
echo "Build dir: ${BUILD_DIR}"
echo "======================================"

cd "${PROJECT_DIR}"

case ${MODE} in
  incremental|"")
    ${WEST} build -b "${ZEPHYR_BOARD}" -d "${BUILD_DIR}" -- \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      ${OVERLAY_ARG}
    ;;
  rebuild)
    ${WEST} build -b "${ZEPHYR_BOARD}" -d "${BUILD_DIR}" -p always -- \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      ${OVERLAY_ARG}
    ;;
  *)
    echo "Unknown build mode: ${MODE}"
    exit 1
    ;;
esac

# Update symlink safely
echo "Updating build symlink → ${BUILD_DIR}"

if [ -L "${LINK_DIR}" ]; then
  rm "${LINK_DIR}"
fi

ln -s "${BUILD_DIR}" "${LINK_DIR}"

# Also expose compile_commands.json at root
ln -sf "${BUILD_DIR}/compile_commands.json" "${PROJECT_DIR}/compile_commands.json"

echo "Symlink updated:"
echo "  build → ${BUILD_DIR}"