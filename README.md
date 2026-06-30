# Ergodic Theory Library — C++

A computational library for numerically investigating ergodic properties of discrete dynamical maps.

## Structure
```
ergodic_lib/
├── CMakeLists.txt
├── include/
│   ├── map.h          # Abstract base class for all maps
│   ├── classicMaps.h         # Concrete maps: Doubling (more to be added)
│   └── ergodicAnalyzer.h     # Ergodic quantity computations
├── src/
│   ├── map.cpp        # Map::orbit() implementation
│   ├── ergodicAnalyzer.cpp        # Map::orbit() implementation
│   └── classicMaps.cpp        #So far, empty
 
Analyzer.cpp   # Birkhoff, Lyapunov, measure, autocorrelation
├── scripts/
│   └── plot.py        # Matplotlib visualization
├── data/              # CSV output (to be generated at runtime)
└── main.cpp           # to demonstrate the current available map
```

## Build & Run

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/ergodic
python3 scripts/plot.py   # requires matplotlib
```

To clean:
```bash
rm -rf build data/*.csv data/*.png
```

## Modules

| Module | What it computes | Expected result (Logistic r=4) |
|---|---|---|
| Birkhoff average | (1/N) Σ f(Tⁿx₀) | Converges to 0.5 |
| Invariant measure | Histogram of orbit visits | Arcsine distribution |
| Lyapunov exponent | (1/N) Σ log\|DT(xₙ)\| | ln 2 ≈ 0.693 |