# 🎮 DreamCast SH4 Optimized Routines

![Dreamcast Logo](https://raw.githubusercontent.com/dreamcast-scene/resources/main/dreamcast_logo.png)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub stars](https://img.shields.io/github/stars/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/username/dreamcast-sh4-optimized.svg)](https://github.com/username/dreamcast-sh4-optimized/issues)

## 📜 Overview

A collection of highly optimized assembly and C routines specifically designed for the Hitachi SH4 processor found in the Sega Dreamcast. These routines leverage the SH4's unique hardware features including its Store Queues (SQ), dual-issue pipeline, and SIMD-like capabilities to achieve maximum performance on this legendary hardware.

## 🚀 Features

- **Store Queue (SQ) Optimized Memory Transfers** - Ultra-fast memory copies that utilize the SH4's dedicated Store Queue hardware
- **movca.l instruction for optimized cache handling** - Uses pre-decrement addressing mode which is faster on SH4 

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
