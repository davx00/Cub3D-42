# Cub3D

A 3D raycasting project inspired by Wolfenstein 3D.

## Requirements

- gcc
- make
- libx11-dev
- libxext-dev

## Installation

### 1. Install system dependencies

```bash
sudo apt-get update
sudo apt-get install libx11-dev libxext-dev
```

### 2. Clone minilibx

The project requires minilibx-linux. If it's not included in the repository:

```bash
git clone https://github.com/42paris/minilibx-linux.git
```

Or if you use submodules:

```bash
git submodule update --init --recursive
```

### 3. Build

```bash
make
```

## Usage

```bash
./cub3D include/maps/abadie.cub
```

## Controls

- `W` - Move forward
- `S` - Move backward
- `A` - Move left
- `D` - Move right
- `←` - Turn left
- `→` - Turn right
- `ESC` - Exit

## Map format

The `.cub` file must contain:

```
no textures/north.xpm
so textures/south.xpm
we textures/west.xpm
ea textures/east.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
1000N00001
1000000001
1111111111
```

- `no`, `so`, `we`, `ea`: Paths to the textures
- `F`: Floor RGB color
- `C`: Ceiling RGB color
- `N`, `S`, `E`, `W`: Player starting position

## Project structure

```
.
├── include/         # Headers
├── libft/           # Personal library
├── minilibx-linux/  # Graphics library
├── parser/          # Map parser
├── raycasting/      # Raycasting engine
├── player/          # Player controls
├── print/           # Rendering
├── free/            # Memory management
├── maps/            # Example maps
└── textures/        # XPM textures
```

## Authors

- despanol 
- mela121212