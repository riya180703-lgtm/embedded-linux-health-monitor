#!/bin/bash
set -e

SERVICE_NAME="device-health-monitor.service"
INSTALL_DIR="/opt/embedded-linux-health-monitor"

echo "Uninstalling Embedded Linux Health Monitor..."

# Stop and disable the service if it exists
if systemctl list-unit-files "$SERVICE_NAME" --no-legend \
    | grep -q "$SERVICE_NAME"; then
    sudo systemctl disable --now "$SERVICE_NAME" || true
fi

# Remove the systemd service file
sudo rm -f "/etc/systemd/system/$SERVICE_NAME"

# Reload systemd configuration
sudo systemctl daemon-reload
sudo systemctl reset-failed

# Remove the installed application
sudo rm -rf "$INSTALL_DIR"

echo "Uninstallation completed successfully."
