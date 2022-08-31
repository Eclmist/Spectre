<h1 align="center">
  <br>
    <img src="https://raw.githubusercontent.com/eclmist/spectre/master/docs/img/spectre.png" alt="Spectre Logo" width="200"></a>
  <br>
    Spectre
  <br>
</h1>
<h4 align="center">A (WIP) physically based spectral raytracing library.</h4>

<p align="center">
  <a href="https://github.com/Eclmist/Spectre/actions">
    <img src="https://github.com/eclmist/Spectre/workflows/build/badge.svg" alt="Build Status">
  </a>
  <a href="#------">
    <img src="https://img.shields.io/badge/stability-experimental-orange.svg">
  </a>
  <a href="https://www.gnu.org/licenses/gpl-3.0.en.html">
    <img src="https://img.shields.io/badge/license-GPL3--or--later-blue.svg">
  </a>
</p>

# Introduction
Spectre is the successor to [Elixir](https://github.com/Eclmist/Elixir), with emphasis on clean, highly tested code.

Written from the ground up in modern C++ (C++20), Spectre improves upon Elixir in the following areas:
  - Code quality improvements - adheres better to SE principles
  - Less over-enginnered - complexity only when it offers significant advantages
  - Test driven development - close to full unit-test coverage
  - SIMD acceleration with AVX2
  - Physically-based spectral rendering as a foundation
  
Spectre continues to take inspiration from [SORT](http://sort-renderer.com/) and [PBRT](http://www.pbr-book.org/). 

# Requirements
- Only CMake versions 3.8 and up is supported
- If compiling with GCC, use GCC10 and above

# Screenshots
<p align="center">
  <img src="https://i.imgur.com/OBbM46z.png" width=700>
</p>

