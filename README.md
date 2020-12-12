<h1 align="center">
  <br>
    RTCore
  <br>
</h1>
<h4 align="center">A (WIP) physically based spectral raytracing renderer.</h4>

<p align="center">
  <a href="https://travis-ci.com/Eclmist/Elixir">
    <img src="https://github.com/eclmist/RTCore/workflows/Build%20RTCore/badge.svg" alt="Build Status">
  </a>
  <a href="#------">
    <img src="https://img.shields.io/badge/stability-experimental-orange.svg">
  </a>
  <a href="https://www.gnu.org/licenses/gpl-3.0.en.html">
    <img src="https://img.shields.io/badge/license-GPL3--or--later-blue.svg">
  </a>
</p>

# Introduction
RTCore is the successor to [Elixir](github.com/Eclmist/Elixir), with emphasis on clean, highly tested code.

Written from the ground up in modern C++ (C++20), RTCore improves upon Elixir in the following areas:
  - Code quality improvements - adheres better to SE principles
  - Less over-enginnered - complexity only when it offers significant advantages
  - Test driven development - close to full unit-test coverage
  - SIMD acceleration with AVX2
  - Physically-based spectral rendering as a foundation
  
RTCore continues to take inspiration from [SORT](http://sort-renderer.com/) and [PBRT](http://www.pbr-book.org/). 

# Requirements
- Only CMake versions 3.8 and up is supported
- If compiling with GCC, use GCC10 and above
