# Ergodic Theory Library — C++

A computational library for numerically investigating ergodic properties of discrete dynamical maps.

## Structure
```
ergodicLibrary/
├── CMakeLists.txt
├── include/
│   ├── map.h          # Abstract base class for all maps
│   ├── classicMaps.h         # Concrete maps: Doubling, Logistic Map (more to be added)
│   └── ergodicAnalyzer.h     # Ergodic quantity computations
├── src/
│   ├── map.cpp            # Map::orbit() implementation
│   ├── ergodicAnalyzer.cpp # Birkhoff, Lyapunov, measure
│   └── classicMaps.cpp    # Map implementations (in progress)
├── scripts/
│   └── plot.py            # Matplotlib visualization
├── data/                  # CSV output — generated at runtime, not tracked by git
└── main.cpp               # Demo: currently available maps and modules
```

## Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run 

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

| Module | What it computes | Expected result (Doubling map) |
|---|---|---|
| Birkhoff average | (1/N) Σ f(Tⁿx₀) | Converges to 0.5 |
| Invariant measure | Histogram of orbit visits | Lebesgue (uniform) measure |
| Lyapunov exponent | (1/N) Σ log\|DT(xₙ)\| | ln 2 ≈ 0.693 |
## Maps

| Map | Definition | Invariant measure | Lyapunov exponent |
|---|---|---|---|
| Doubling | T(x) = 2x mod 1 | Lebesgue | ln 2 |
| Logistic (r=4) | T(x) = 4x(1−x) | Arcsine 1/π√(x(1−x)) | ln 2 |
*More maps to be added.*

## C++ Design

- Polymorphic `Map` hierarchy via abstract base class and virtual functions
- `unique_ptr` / `shared_ptr` for map ownership; `Analyzer` borrows via `const Map&`
- `std::filesystem` for automatic CSV output directory creation
- CMake custom target for integrated Python plotting
