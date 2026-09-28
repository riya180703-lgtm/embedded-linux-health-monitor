#!/bin/bash
set -e

echo "=========================================="
echo " Embedded Linux Health Monitor"
echo " CPU Failure Simulation"
echo "=========================================="

if ! command -v stress-ng >/dev/null 2>&1; then
    echo "Error: stress-ng is not installed."
    echo "Install it using: sudo apt install stress-ng"
    exit 1
fi

echo "Starting controlled CPU load for 20 seconds..."
echo "Watch the health monitor logs in another terminal."

stress-ng --cpu 2 --timeout 20s --metrics-brief

echo "CPU simulation completed."
