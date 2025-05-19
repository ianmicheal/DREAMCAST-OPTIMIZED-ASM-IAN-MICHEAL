# SH4-Optimized Memory Copy

![Dreamcast Logo](https://raw.githubusercontent.com/dreamcast-scene/resources/main/dreamcast_logo.png)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub stars](https://img.shields.io/github/stars/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/issues)

- **Cache Line Optimization**: Functions process memory in 32-byte chunks to match the SH4's cache line size
- **Prefetch Instructions**: Strategic placement of `pref` instructions exactly one cache line ahead
- **Write Allocation**: Using `movca.l` to optimize cache line allocation for write operations
- **Pipeline Utilization**: Careful instruction ordering to maximize the SH4's dual-issue capabilities
- **Loop Unrolling**: Partial loop unrolling to reduce branch prediction penalties

## 📊 Benchmark Results

Performance comparison in clock cycles (lower is better):

| Buffer Size (bytes) | memcpy | memcpy_fast | **MemCpy32** |
|---------------------|-------:|------------:|-------------:|
| 0                   |   1030 |        1100 |        **665** |
| 32                  |   1435 |         995 |        **805** |
| 64                  |   1485 |        1725 |        **905** |
| 96                  |   1645 |        1785 |       **1005** |
| 128                 |   1805 |        1845 |       **1105** |
| 1024                |   6315 |        3650 |        3905 |


![Dreamcast Logo](https://raw.githubusercontent.com/dreamcast-scene/resources/main/dreamcast_logo.png)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub stars](https://img.shields.io/github/stars/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/issues)

## 📜 Overview

A collection of highly optimized assembly and C routines specifically designed for the Hitachi SH4 processor found in the Sega Dreamcast. These routines leverage the SH4's unique hardware features including its Store Queues (SQ), dual-issue pipeline, and SIMD-like capabilities to achieve maximum performance on this legendary hardware.

## 🚀 Features

- **Store Queue (SQ) Optimized Memory Transfers** - Ultra-fast memory copies that utilize the SH4's dedicated Store Queue hardware
- **movca.l instruction for optimized cache handling** - Uses pre-decrement addressing mode which is faster on SH4
- **Highly Optimized MemCpy32 Function** - Up to 60% faster than standard memcpy for common transfer sizes
- **Cache-Aware Design** - Functions aligned with SH4's 32-byte cache line size for optimal performance
- **Strategic Cache Prefetching** - Intelligent prefetch instructions to minimize memory latency
- **movca.l Instruction Optimization** - Leverages specialized SH4 cache allocation instruction
- **Pipeline-Optimized Code** - Carefully structured to maximize the SH4's execution pipeline

## 🔧 Technical Details

These routines take advantage of specific SH4 processor features:

- **Store Queues (SQ)**: The SH4 has special hardware for efficiently transferring data to and from external devices
- **Prefetch Instructions**: Strategic use of cache prefetching reduces memory latency
- **Dual-Issue Pipeline**: Instructions carefully arranged to maximize parallel execution
- **PREF and OCBI Instructions**: Optimal cache management for predictable memory patterns
- **Register Allocation Optimization**: Careful use of the SH4's register file to minimize memory access

## 📚 Documentation

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.


## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- The Dreamcast development community for their tireless work in keeping the platform alive
- [KallistiOS](http://gamedev.allusion.net/softprj/kos/) - The open-source Dreamcast development environment
- Hitachi for the amazing SH4 processor architecture documentation
- Created by Ian Micheal - 2025
