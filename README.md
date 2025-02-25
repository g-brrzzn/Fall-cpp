# 🌨️ Fall-cpp  

A C++ particle simulation using SFML, capable of creating effects like **snow, rain, lasers**, or any particle-based motion influenced by **gravity** and **wind**. Each particle has a unique base speed, adding depth and immersion to the simulation.  

## 🎥 Demonstration  
https://github.com/user-attachments/assets/a805364b-ad7a-4d6d-8a80-6447570a0545

## 📦 Installation  

1. **Download and extract SFML**  
   - Download the SFML SDK (ZIP file) from [SFML Download Page](https://www.sfml-dev.org/download/)  
   - Extract it to your preferred location (e.g., `D:\libs\SFML-3.0.0`)  

2. **Configure Visual Studio**  
   In **Project's properties**, update the following paths:  

   - `C/C++ > General > Additional Include Directories` → `"<sfml-install-path>/include"`  
   - `Linker > General > Additional Library Directories` → `"<sfml-install-path>/lib"`  
   - `Linker > Input > Additional Dependencies` → Add `"sfml-graphics.lib"`, `"sfml-window.lib"`, `"sfml-system.lib"`  

3. **Need help setting up SFML?**  
   Check out my **SFML Visual Studio Template** for a preconfigured project: [SFML-VS-Template](https://github.com/g-brrzzn/SFML-VS-Template)  

## 🚀 Usage  

- Modify the simulation parameters for different effects.  
- Adjust **gravity** (affects Y-axis) and **wind** (affects X-axis) to create various particle behaviors.
- Change the RGB color of particles to customize their appearance.
  
| Key  | Action |
|------|--------|
| **Y** | Increase particle density (+100) |
| **T** | Decrease particle density (-100) |
| **H** | Increase gravity (+3.0) |
| **G** | Decrease gravity (-3.0) |
| **N** | Increase wind (+3.0) |
| **B** | Decrease wind (-3.0) |
| **O** | Activate **Snow Mode** preset (light gray particles, moderate wind & gravity) |
| **K** | Activate **Rain Mode** preset (blue particles, stronger gravity, negative wind) |
| **M** | Activate **Laser Mode** preset (red particles, negative gravity, no wind) |

## 🛠️ Requirements  

- C++17  
- SFML 3.0+  
- Visual Studio

