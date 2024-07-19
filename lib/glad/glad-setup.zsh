# lib/glad/glad-setup.zsh - A script to compile glad.c into a shared library.

#!/usr/bin/env zsh

# Set the directories for the include and source files.
INCLUDE_DIR="./include"
SRC_DIR="./src"
OUTPUT_DIR="/usr"
LIB_DIR="$OUTPUT_DIR/lib"
INCLUDE_DEST_DIR="$OUTPUT_DIR/include"

# Names of the files
GLAD_C_FILE="$SRC_DIR/glad.c"
LIB_NAME="libglad.so"

# Ensure output directories exist.
if [ ! -d "$LIB_DIR" ]; then
  echo "Creating library directory $LIB_DIR..."
  sudo mkdir --parents "$LIB_DIR"
fi

if [ ! -d "$INCLUDE_DEST_DIR" ]; then
  echo "Creating include directory $INCLUDE_DEST_DIR..."
  sudo mkdir --parents "$INCLUDE_DEST_DIR"
fi

# Copy the include files to $INCLUDE_DEST_DIR.
echo "Copying include files to $INCLUDE_DEST_DIR..."
sudo cp --recursive "$INCLUDE_DIR/glad" "$INCLUDE_DEST_DIR/"
sudo cp --recursive "$INCLUDE_DIR/KHR" "$INCLUDE_DEST_DIR/"
if [ $? -ne 0 ]; then
  echo "Error: Failed to copy include files to $INCLUDE_DEST_DIR"
  exit 1
fi

# Ensure you have the correct OpenGL version and extensions # (If necessary, download or replace the glad.c and glad.h with the correct ones)
echo "Generating glad loader with the correct OpenGL version and extensions..."

# Compile the glad.c file into an object file.
echo "Compiling glad.c into glad.o..."
gcc -std=c11 -fPIC -c "$GLAD_C_FILE" -o glad.o
if [ $? -ne 0 ]; then
  echo "Error: Failed to compile glad.c"
  exit 1
fi

# Create the shared library $LIB_NAME from the object file.
echo "Creating the shared library $LIB_NAME..."
gcc -shared -o "$LIB_NAME" glad.o
if [ $? -ne 0 ]; then
  echo "Error: Failed to create the shared library"
  rm glad.o
  exit 1
fi

# Copy the library to $LIB_DIR.
echo "Copying $LIB_NAME to $LIB_DIR..."
sudo cp "$LIB_NAME" "$LIB_DIR/"
if [ $? -ne 0 ]; then
  echo "Error: Failed to copy $LIB_NAME to $LIB_DIR"
  rm glad.o "$LIB_NAME"
  exit 1
fi

# Refresh the shared library cache.
echo "Running ldconfig to update shared library cache..."
sudo ldconfig
if [ $? -ne 0 ]; then
  echo "Error: Failed to run ldconfig"
  rm glad.o "$LIB_NAME"
  exit 1
fi

# Clean up the object file and the shared library.
echo "Cleaning up..."
rm glad.o "$LIB_NAME"

# Final message
echo "Installation completed! libglad.so has been installed to $LIB_DIR and headers to $INCLUDE_DEST_DIR."
