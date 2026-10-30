#!/usr/bin/env bash
set -e

APP_NAME="one_at_a_time_please"
BUILD_DIR="build"
APP_DIR="AppDir"

echo "==> Cleaning previous build artifacts..."
# Grant write permissions back to everything in AppDir so rm can delete it
if [ -d "AppDir" ]; then
    chmod -R +w "AppDir"
fi
rm -rf "$APP_DIR" "$BUILD_DIR"
mkdir -p "$BUILD_DIR" "$APP_DIR"
echo "==> Configuring with qmake..."
cd "$BUILD_DIR"
# Runs qmake pointing to the parent directory containing your .pro file
qmake CONFIG+=release ..

echo "==> Building project..."
make -j$(nproc)

echo "==> Installing into AppDir..."
# qmake uses INSTALL_ROOT for staging the installation path
make INSTALL_ROOT="../$APP_DIR" install
cd ..

echo "==> Copying Qt platform plugins..."
QT_BASE_PATH=$(nix-store -qR $(which qmake 2>/dev/null || echo "") | grep qtbase | head -n 1)

if [ -z "$QT_BASE_PATH" ]; then
    QT_BASE_PATH=$(find /nix/store -maxdepth 1 -name "*-qtbase-*" | head -n 1)
fi

if [ -n "$QT_BASE_PATH" ]; then
    echo "Found qtbase at: $QT_BASE_PATH"
    
    mkdir -p "$APP_DIR/usr/lib/qt-6/plugins"
    
    if [ -d "$QT_BASE_PATH/lib/qt-6/plugins" ]; then
        cp -r "$QT_BASE_PATH/lib/qt-6/plugins/"* "$APP_DIR/usr/lib/qt-6/plugins/"
    elif [ -d "$QT_BASE_PATH/lib/qt6/plugins" ]; then
        cp -r "$QT_BASE_PATH/lib/qt6/plugins/"* "$APP_DIR/usr/lib/qt-6/plugins/"
    fi
    
    # CRITICAL FIX: Grant write permissions so patchelf can modify the copied plugins
    chmod -R +w "$APP_DIR/usr/lib/qt-6/plugins"
else
    echo "Warning: Could not automatically resolve qtbase path."
fi

echo "==> Running linuxdeploy..."
export QT_PLUGIN_PATH="$PWD/$APP_DIR/usr/lib/qt-6/plugins"

# Dynamically find libX11 and libglvnd paths from the current qmake closure or store paths safely
LIBX11_PATH=$(nix-store -qR "$QT_BASE_PATH" | grep -E 'libX11' | head -n 1)
LIBGLVND_PATH=$(nix-store -qR "$QT_BASE_PATH" | grep -E 'libglvnd' | head -n 1)

export LD_LIBRARY_PATH="${LIBX11_PATH:+$LIBX11_PATH/lib:}${LIBGLVND_PATH:+$LIBGLVND_PATH/lib:}$LD_LIBRARY_PATH"

linuxdeploy --appdir "$APP_DIR" \
    --plugin qt \
    --output appimage
echo "==> AppImage build complete!"
