# Test Report

## Project
Embedded Linux Device Health Monitor & Auto-Recovery Agent

## Test Environment
- Operating System: Ubuntu on WSL2
- Language: C++17
- Build System: CMake
- Test Framework: CTest

## Test Cases

| Test | Purpose | Result |
|---|---|---|
| ConfigTest | Verify configuration loading and thresholds | Passed |
| CpuTest | Verify CPU usage monitoring | Passed |
| MemoryTest | Verify memory usage monitoring | Passed |
| ServiceMonitorTest | Verify service status monitoring | Passed |
| Automatic Recovery | Verify recovery after service failure | Passed |

## Environment Limitations

- Temperature monitoring depends on the availability of a
  Linux thermal sensor.
- Network checks depend on network connectivity and whether
  the configured host responds to ping.
- Service recovery requires systemd and sufficient privileges.

## Conclusion

The project successfully monitors system resources and
critical services. It supports logging, configurable
thresholds, and automatic service recovery.
