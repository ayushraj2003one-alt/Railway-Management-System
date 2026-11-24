<div align="center">

# 🚆 Railway Tracking & Route Optimization System
### High-Performance Shortest Path & Fast-Transit Network Simulator in C

[![C Standard](https://img.shields.io/badge/Language-C99-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C99)
[![Compiler](https://img.shields.io/badge/Compiler-GCC%20%7C%20MinGW-4B6A9B?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Build Tool](https://img.shields.io/badge/Build-GNU%20Make-064F8C?style=for-the-badge&logo=gnu-make&logoColor=white)](https://www.gnu.org/software/make/)
[![Algorithm](https://img.shields.io/badge/Algorithm-Dijkstra's%20SSSP-8A2BE2?style=for-the-badge)](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
[![Data Structure](https://img.shields.io/badge/Data%20Structure-Binary%20Min--Heap-FF6F00?style=for-the-badge)](https://en.wikipedia.org/wiki/Binary_heap)
[![Complexity](https://img.shields.io/badge/Time%20Complexity-O((V%2BE)logV)-brightgreen?style=for-the-badge)](#algorithmic-complexity)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue?style=for-the-badge&logo=windows&logoColor=white)](#how-to-build--run)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

<br/>

<p align="center">
  <b>A production-grade Data Structures & Algorithms project modeling an intercity railway network.</b><br/>
  Computes optimal train routes using an accelerated <b>Binary Min-Heap Priority Queue Dijkstra's Algorithm</b> with dynamic dataset loading, live fare estimates, and multi-criteria optimization.
</p>

</div>

---

## 🛠️ Technology Stack & Tooling

<table>
  <tr>
    <td align="center" width="25%"><b>Category</b></td>
    <td align="center"><b>Technologies & Colorful Cards</b></td>
  </tr>
  <tr>
    <td align="center"><b>Core Language</b></td>
    <td>
      <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
      <img src="https://img.shields.io/badge/Standard-C99%20%2F%20ANSI%20C-008080?style=for-the-badge" alt="C99" />
    </td>
  </tr>
  <tr>
    <td align="center"><b>Compilers & Toolchain</b></td>
    <td>
      <img src="https://img.shields.io/badge/GCC-MinGW--w64-orange?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC" />
      <img src="https://img.shields.io/badge/Build-GNU%20Make-4B6A9B?style=for-the-badge&logo=gnu-make&logoColor=white" alt="Make" />
      <img src="https://img.shields.io/badge/Windows-Batch%20Scripts-4D4D4D?style=for-the-badge&logo=windows-terminal&logoColor=white" alt="Batch" />
    </td>
  </tr>
  <tr>
    <td align="center"><b>Data Structures</b></td>
    <td>
      <img src="https://img.shields.io/badge/Graph-Adjacency%20List-success?style=for-the-badge" alt="Adjacency List" />
      <img src="https://img.shields.io/badge/Priority%20Queue-Binary%20Min--Heap-FF8C00?style=for-the-badge" alt="Min-Heap" />
      <img src="https://img.shields.io/badge/Lookup-Position%20Tracker%20Array-blueviolet?style=for-the-badge" alt="Pos Array" />
    </td>
  </tr>
  <tr>
    <td align="center"><b>Algorithms & Complexity</b></td>
    <td>
      <img src="https://img.shields.io/badge/Pathfinding-Dijkstra's%20SSSP-8A2BE2?style=for-the-badge" alt="Dijkstra" />
      <img src="https://img.shields.io/badge/Time-O((V%2BE)%20log%20V)-brightgreen?style=for-the-badge" alt="O((V+E)logV)" />
      <img src="https://img.shields.io/badge/Space-O(V%20%2B%20E)-blue?style=for-the-badge" alt="O(V+E)" />
    </td>
  </tr>
  <tr>
    <td align="center"><b>Data & Persistence</b></td>
    <td>
      <img src="https://img.shields.io/badge/Dataset-CSV%20File%20Format-239120?style=for-the-badge&logo=files&logoColor=white" alt="CSV" />
      <img src="https://img.shields.io/badge/File%20I%2FO-Dynamic%20Token%20Parser-107C41?style=for-the-badge" alt="File IO" />
    </td>
  </tr>
  <tr>
    <td align="center"><b>Version Control & Shell</b></td>
    <td>
      <img src="https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white" alt="Git" />
      <img src="https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white" alt="GitHub" />
      <img src="https://img.shields.io/badge/Shell-PowerShell%20%7C%20Bash-5391FE?style=for-the-badge&logo=powershell&logoColor=white" alt="PowerShell" />
    </td>
  </tr>
</table>

---

## 🌟 Key Highlights & Features

- **⚡ Min-Heap Accelerated Dijkstra**: Reduces linear node extraction $\mathcal{O}(V^2)$ down to $\mathcal{O}((V + E) \log V)$ using an in-place priority queue.
- **🎯 Dual-Criterion Optimization**: Seamlessly calculate either the **shortest track distance (km)** or the **fastest transit duration (minutes)**.
- **📂 Dynamic Dataset Loading**: Reads routes directly from `data/network.csv` with automatic fallback to an internal graph.
- **🔍 Smart Station Resolution**: Accepts either station names (case-insensitive, e.g., `delhi`, `jammu`) or numbered station indices.
- **🎟️ Multi-Tier Fare Calculator**: Simulates IRCTC-style ticket prices across 4 coach tiers: Sleeper (SL), AC 3-Tier (3A), AC 2-Tier (2A), and AC First Class (1A).
- **📋 Step-by-Step Leg Breakdown**: Displays intermediate stops, individual track distances, and segment runtimes.

---

## 🗺️ Railway Network Topology

```mermaid
graph LR
    Delhi((Delhi)) ---|200km / 180m| Ambala((Ambala))
    Delhi ---|250km / 300m| Dehradun((Dehradun))
    Delhi ---|210km / 240m| Haridwar((Haridwar))
    Delhi ---|260km / 240m| Chandigarh((Chandigarh))
    Ambala ---|50km / 45m| Chandigarh
    Ambala ---|110km / 90m| Ludhiana((Ludhiana))
    Ambala ---|150km / 200m| Shimla((Shimla))
    Chandigarh ---|110km / 180m| Shimla
    Chandigarh ---|100km / 110m| Ludhiana
    Ludhiana ---|140km / 120m| Amritsar((Amritsar))
    Ludhiana ---|170km / 160m| Pathankot((Pathankot))
    Amritsar ---|110km / 100m| Pathankot
    Pathankot ---|100km / 110m| Jammu((Jammu))
    Dehradun ---|50km / 60m| Haridwar
    Dehradun ---|220km / 360m| Shimla

    style Delhi fill:#2B6CB0,stroke:#fff,stroke-width:2px,color:#fff
    style Jammu fill:#2B6CB0,stroke:#fff,stroke-width:2px,color:#fff
    style Chandigarh fill:#2B6CB0,stroke:#fff,stroke-width:2px,color:#fff
    style Amritsar fill:#2B6CB0,stroke:#fff,stroke-width:2px,color:#fff
```

---

## 📊 Algorithmic Complexity Matrix

| Operation | Standard Implementation | This Project's Implementation | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Graph Storage** | Adjacency Matrix | **Adjacency List** | $\mathcal{O}(1)$ insertion | $\mathcal{O}(V + E)$ |
| **Minimum Extraction** | Linear Scan $\mathcal{O}(V)$ | **Min-Heap (`extractMin`)** | $\mathcal{O}(\log V)$ | $\mathcal{O}(V)$ |
| **Distance Update** | Linear Assignment | **Heap `decreaseKey` via `pos[]`** | $\mathcal{O}(\log V)$ | $\mathcal{O}(1)$ auxiliary |
| **Pathfinding (SSSP)** | Array-based Dijkstra | **Min-Heap Dijkstra** | **$\mathcal{O}((V + E) \log V)$** | $\mathcal{O}(V)$ auxiliary |
| **Path Reconstruction** | Manual scan | **Parent Pointer Backtracking** | $\mathcal{O}(V)$ | $\mathcal{O}(V)$ |

---

## 📁 Repository Organization

```text
Railway-Management-System/
├── 📁 data/
│   └── network.csv           # Railway tracks, distances (km), and runtimes (min)
├── 📁 include/
│   ├── graph.h               # Adjacency list & station structure definitions
│   ├── minheap.h             # Priority queue structure & heapify prototypes
│   └── dijkstra.h            # Pathfinding & fare calculation prototypes
├── 📁 src/
│   ├── graph.c               # Dynamic CSV parser & adjacency list builder
│   ├── minheap.c             # O(log V) Min-Heap (heapify, decreaseKey)
│   ├── dijkstra.c            # Shortest route finder & itinerary generator
│   └── main.c                # Interactive command-line interface
├── 📄 build.bat              # One-click Windows build script
├── 📄 Makefile               # Unix/Linux/macOS automated compilation
├── 📄 .gitignore             # Compiler artifact exclusions
└── 📄 README.md              # Project documentation with tech stack cards
```

---

## ⚡ How to Build & Run

### 🪟 Windows (MinGW / GCC)
Run the automated build script:
```powershell
.\build.bat
.\railway_tracker.exe
```

Or compile directly with GCC:
```powershell
gcc -Wall -Wextra -std=c99 -Iinclude src/main.c src/graph.c src/minheap.c src/dijkstra.c -o railway_tracker.exe
.\railway_tracker.exe
```

### 🐧 Linux / 🍎 macOS
```bash
make
./railway_tracker
```

---

## 💻 Sample Terminal Output

```text
============================================================
            SHORTEST ROUTE (OPTIMIZED FOR DISTANCE)         
============================================================

Path Itinerary:
  [Start] Delhi
     | 
     +---> Ambala    (Leg: 200 km, 180 min)
     | 
     +---> Ludhiana  (Leg: 110 km, 90 min)
     | 
     +---> Pathankot (Leg: 170 km, 160 min)
     | 
     +---> Jammu     (Leg: 100 km, 110 min)

Summary:
  * Total Stops    : 5 stations (3 intermediate stops)
  * Total Distance : 580 km
  * Total Duration : 9 hours 0 minutes (540 mins)
============================================================

--- Estimated Ticket Fares ---
+----------------------+-------------------+
| Travel Class         | Approx. Fare (INR)|
+----------------------+-------------------+
| Sleeper Class (SL)   | Rs. 381           |
| AC 3-Tier (3A)       | Rs. 987           |
| AC 2-Tier (2A)       | Rs. 1536          |
| AC First Class (1A)  | Rs. 2358          |
+----------------------+-------------------+
```

---

## 🎓 Viva & Technical Interview Notes

<details>
<summary><b>Click to expand Viva Q&A Cheat Sheet</b></summary>
<br/>

1. **Why is Dijkstra preferred over Bellman-Ford here?**
   - Dijkstra's algorithm is optimal for graphs with **non-negative edge weights** (distances and durations can never be negative). It runs in $\mathcal{O}((V + E) \log V)$, whereas Bellman-Ford takes $\mathcal{O}(V \cdot E)$.
2. **Why use an Adjacency List instead of an Adjacency Matrix?**
   - Railway graphs are sparse ($E \ll V^2$). An Adjacency List consumes $\mathcal{O}(V + E)$ space compared to $\mathcal{O}(V^2)$ for a matrix, and allows iterating only over existing tracks rather than all $V$ potential vertices.
3. **How does `decreaseKey` achieve $\mathcal{O}(\log V)$ in C?**
   - We maintain an auxiliary `pos[]` array that maps each vertex ID to its current index in the heap array. This avoids searching through the heap in $\mathcal{O}(V)$ time, enabling direct $\mathcal{O}(1)$ lookup and $\mathcal{O}(\log V)$ bubble-up.

</details>

---

<div align="center">
  <sub>Developed by Ayush Raj • Built with ❤️ for Data Structures & Algorithms</sub>
</div>
