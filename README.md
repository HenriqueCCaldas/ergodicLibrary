# Ergodic Theory Library — C++

A computational library for numerically investigating ergodic properties of discrete dynamical maps.

## Structure
```
ergodicLibrary/
├── CMakeLists.txt
├── include/
│   ├── map.h                    # Abstract base class for all maps (includes private tag_ and params_ vector to store name and parameters)
│   ├── classicMaps.h            # Concrete maps: Doubling, Logistic Map (more to be added)
│   └── ergodicAnalyzer.h        # Ergodic quantity computations
├── src/
│   ├── map.cpp                  # Map::orbit() implementation
│   ├── ergodicAnalyzer.cpp      # Birkhoff, Lyapunov, Trajectory divergence, Invariant measure, etc.
│   └── classicMaps.cpp          # Map implementations (in progress)
├── scripts/
│   ├── plot.py                  # Matplotlib visualization    
│   └── animated_phase_space.py  # Matplotlib animated visualization of the doubling map for 150 points
├── data/                        # CSV output — generated at runtime, not tracked by git
└── main.cpp                     # Demo: demonstrate currently available maps and modules
```

## Dependencies

- C++17 compiler, CMake ≥ 3.16
- **[Boost.Multiprecision](https://www.boost.org/doc/libs/release/libs/multiprecision/)** — provides 
sthe `real` type (`cpp_bin_float_100`) used in the library instead of `double`.
- Fetched  via CMake `FetchContent`.

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run 

Running requires that a build already exists

To run the main program separately from the plotting script:

```bash
./build/ergodic
```

and then to generate plots (requires matplotlib in a virtual environment):

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install matplotlib pandas
cmake --build build --target plot
```

To run simultaneosly
```bash
cmake --build build --target run_and_plot
```

## Clean 
To clean the build:
```bash
rm -rf build
```

and the data:
```bash
rm -rf data
```

## Modules

| Module | What it computes |
|---|---|
| Birkhoff average | (1/N) Σ f(Tⁿx₀) |
| Invariant measure | Histogram of orbit visits |
| Lyapunov exponent | (1/N) Σ log\|DT(xₙ)\|


## Vector Modules

| Module | What it computes |
|---|---|
| Birkhoff convergence | Vector of size N of iterations (1/N) Σ f(Tⁿx₀) |
| Running Lyapunov convergence | Vector of size N of iterations (1/N) Σ log\|DT(xₙ)\|
| Trajectory Divergence | Vector that stores the log(\|xₙ-yₙ\|)|


## Available Maps

| Module |
|---|
| Doubling Map |
| Gauss Iterated |
| Logistic Map |

*More maps to be added.*
## C++ Design

- Polymorphic `Map` hierarchy via abstract base class and virtual functions
- `unique_ptr` / `shared_ptr` for map ownership; `Analyzer` borrows via `const Map&`
- `std::filesystem` for automatic CSV output directory creation
- CMake custom target for integrated Python plotting

## Numerical considerations


### Floating point 

- For chaotic maps like the Doubling map, floating point introduces 
a fundamental limitation regardless of precision. Since `x0 = 0.2` cannot be represented exactly in 
binary, the stored value carries a small error `ε`. The Doubling map multiplies by 2 at each step, 
so this error grows as `2^n*ε` - exactly the rate predicted by the Lyapunov exponent `λ = ln 2 ≈ 0.693`. 
- With `double` (16 digits), the error dominates after ~50 iterations and the orbit collapses to 0; 
- With `cpp_bin_float_100` (storing 100 digits), this instead happens around n ≈ 100 · log₂(10) ≈ 330 iterations —
which is why `main.cpp` runs `N = 300`, staying just inside the precision window.

### Arbitrary precision (Boost.Multiprecision)

- All maps and variables use `real = boost::multiprecision::cpp_bin_float_100` (100 digits) instead 
of `double` (16 digit).
- **Always construct `real` values from a string literal**, e.g. `real x0("0.2")`, never `real x0 = 0.2`.
 This allows to parse the value in its at the precision from `real`.


## Note on AI usage
The plotting files were generated with assistance from Claude to better represent the data generated.
This README file was also written with assistance from Claude. The rest of the code was manually designed as exercise,
Claude was punctually used to help debugging the software.

