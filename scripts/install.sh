#!/bin/bash
set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
INSTALL_DIR="/opt/embedded-linux-health-monitor"

echo "Installing Embedded Linux Health Monitor..."

# Copy project files
sudo mkdir -p "$INSTALL_DIR"
sudo cp -a "$PROJECT_DIR/." "$INSTALL_DIR/"

# Remove the copied build directory to avoid CMake cache conflicts
sudo rm -rf "$INSTALL_DIR/build"

# Build the application
# Build the application
sudo cmake -S "$INSTALL_DIR" -B "$INSTALL_DIR/build"
sudo cmake --build "$INSTALL_DIR/build" -j"$(nproc)"
# Install the systemd service file
sudo cp "$INSTALL_DIR/systemd/device-health-monitor.service" \
    /etc/systemd/system/device-health-monitor.service

# Register and start the service
sudo systemctl daemon-reload
sudo systemctl enable --now device-health-monitor.service

echo "Installation completed successfully!"
echo "Check status using:"
echo "sudo systemctl status device-health-monitor"
